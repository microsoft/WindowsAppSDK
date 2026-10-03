// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <Windows.h>
#include <Pathcch.h>
#include <appmodel.h>
#include "wil/win32_helpers.h"
#include "wil/filesystem.h"
#include "mrm/BaseInternal.h"
#include "mrm/common/platform.h"
#include "mrm/readers/MrmReaders.h"
#include "mrm/platform/WindowsCore.h"
#include "mrm/readers/MrmManagers.h"

#include "mrm/common/MrmTraceLogging.h"

#include "MRM.h"

#include <memory>
#include <string>
#include <cstdlib>

#include "wil/resource.h"

using namespace Microsoft::Resources;

typedef struct _MrmObjects
{
    CoreProfile* profile = nullptr;
    UnifiedResourceView* unifiedView = nullptr;
    const PriFile* priFile = nullptr;
    ProviderResolver* resolver = nullptr;
    // Serializes the on-demand merge of package-graph resources into the unified view.
    // Shared for the (common) resolve path; exclusive only while merging, mirroring the
    // reader/writer locking System MRT uses around its on-demand PRI load.
    wil::srwlock packageGraphLock;
} MrmObjects;

// Resolves a resource root map name to a package in the app's dependency graph and merges
// that package's resources into the unified view on demand. Declared here so the flat
// resource-resolution APIs can fall back to it. See the definition for details.
static HRESULT MergePackageResourceFilesForMapName(_In_ UnifiedResourceView* unifiedView, _In_ PCWSTR rootResourceMapName);

constexpr wchar_t ResourceUriPrefix[] = L"ms-resource://";
constexpr unsigned int ResourceUriPrefixLength = ARRAYSIZE(ResourceUriPrefix) - 1;
constexpr wchar_t ResourcesPriFileName[] = L"resources.pri";

#define INDEX_RESOURCE_ID -1
#define INDEX_RESOURCE_URI -2

bool IsResourceUri(_In_ PCWSTR resourceId)
{
    return ((wcslen(resourceId) > static_cast<size_t>(ResourceUriPrefixLength)) && (CompareStringOrdinal(ResourceUriPrefix, ResourceUriPrefixLength, resourceId, ResourceUriPrefixLength, TRUE) == CSTR_EQUAL));
}

HRESULT GetRootAndRelativeIdFromUri(
    _In_ PCWSTR resourceUri,
    _Out_writes_z_(rootSize) PWSTR root,
    unsigned int rootSize,
    _Out_ unsigned int* indexOfRelatvieId)
{
    // We should have checked resourceUri length is longer than ResourceUriPrefixLength before calling this
    unsigned int i = 0;
    for (; i < rootSize; i++)
    {
        wchar_t currentCharacter = resourceUri[ResourceUriPrefixLength + i];
        if (currentCharacter == L'\0')
        {
            // If the URI ends before it has any paths it is not a valid resource reference.
            return E_INVALIDARG;
        }

        if (currentCharacter == L'/')
        {
            break;
        }

        root[i] = currentCharacter;
    }

    if (i == rootSize)
    {
        // The root resource map was too long.
        return E_INVALIDARG;
    }

    root[i] = L'\0';

    // The above loop ends at the slash, so go one after.
    *indexOfRelatvieId = ResourceUriPrefixLength + i + 1;
    return S_OK;
}

static HRESULT StringResultReleaseOwnershipBuffer(_Inout_ StringResult& result, _Outptr_ PWSTR* buffer)
{
    size_t localStringLength;
    PWSTR localString;
    // Make sure result owns the data
    RETURN_IF_FAILED(result.GetWritableRef(&localString, &localStringLength));
    // Release the ownership
    RETURN_IF_FAILED(result.ReleaseContents(buffer, &localStringLength));

    return S_OK;
}

static HRESULT BlobResultReleaseOwnershipBuffer(
    _Inout_ BlobResult& result,
    _Outptr_result_bytebuffer_(*releasedBufferSizeInBytes) void** releasedBuffer,
    _Out_ UINT32* releasedBufferSizeInBytes)
{
    size_t localSize;
    // Make sure result owns the data
    RETURN_HR_IF(E_OUTOFMEMORY, result.GetWritableRef(&localSize) == nullptr);

    // Release the ownership
    size_t sizeInBytes;
    RETURN_IF_FAILED(result.ReleaseContents(releasedBuffer, &sizeInBytes));
    *releasedBufferSizeInBytes = static_cast<UINT32>(sizeInBytes);
    return S_OK;
}

static HRESULT GetQualifierInfoFromCandidateImpl(
    _In_ MrmObjects* resourceManager,
    _In_ const ResourceCandidateResult* candidate,
    _Out_ UINT32* qualifierCount,
    _Outptr_result_buffer_(*qualifierCount) PWSTR** qualifierNames,
    _Outptr_result_buffer_(*qualifierCount) PWSTR** qualifierValues)
{
    *qualifierCount = 0;
    *qualifierNames = nullptr;
    *qualifierValues = nullptr;

    QualifierSetResult qualifierSet;
    RETURN_IF_FAILED(candidate->GetQualifiers(&qualifierSet));

    int count = qualifierSet.GetNumQualifiers();

    if (count == 0)
    {
        return S_OK;
    }

    UINT32 bufferSize;
    RETURN_IF_FAILED(UInt32Mult(static_cast<UINT32>(count), sizeof(*qualifierNames), &bufferSize));
    *qualifierNames = reinterpret_cast<PWSTR*>(MrmAllocateBuffer(bufferSize));
    RETURN_IF_NULL_ALLOC(*qualifierNames);
    ZeroMemory(*qualifierNames, bufferSize);

    RETURN_IF_FAILED(UInt32Mult(static_cast<UINT32>(count), sizeof(*qualifierValues), &bufferSize));
    *qualifierValues = reinterpret_cast<PWSTR*>(MrmAllocateBuffer(bufferSize));
    RETURN_IF_NULL_ALLOC(*qualifierValues);
    ZeroMemory(*qualifierValues, bufferSize);

    PWSTR* oneName = *qualifierNames;
    PWSTR* oneValue = *qualifierValues;
    for (int i = 0; i < count; i++)
    {
        QualifierResult qualifierResult;
        RETURN_IF_FAILED(qualifierSet.GetQualifier(i, &qualifierResult, nullptr));

        Atom nameAtom;
        RETURN_IF_FAILED(qualifierResult.GetOperand1Attribute(&nameAtom));

        if (nameAtom == Atom::NullAtom)
        {
            continue;
        }

        StringResult name;
        RETURN_IF_FAILED(resourceManager->unifiedView->GetUnifiedEnvironment()->GetQualifierNameFromAtom(nameAtom, &name));

        StringResult value;
        bool isLiteral;
        if (SUCCEEDED(qualifierResult.Operand2IsLiteral(&isLiteral)) && isLiteral)
        {
            RETURN_IF_FAILED(qualifierResult.GetOperand2Literal(&value));
        }

        (*qualifierCount)++;

        RETURN_IF_FAILED(StringResultReleaseOwnershipBuffer(name, oneName));
        oneName++;

        RETURN_IF_FAILED(StringResultReleaseOwnershipBuffer(value, oneValue));
        oneValue++;
    }

    return S_OK;
}

static HRESULT GetQualifierInfoFromCandidate(
    _In_ MrmObjects* resourceManager,
    const ResourceCandidateResult* candidate,
    _Out_ UINT32* qualifierCount,
    _Outptr_result_buffer_(*qualifierCount) PWSTR** qualifierNames,
    _Outptr_result_buffer_(*qualifierCount) PWSTR** qualifierValues)
{
    HRESULT hr = GetQualifierInfoFromCandidateImpl(resourceManager, candidate, qualifierCount, qualifierNames, qualifierValues);
    if (FAILED(hr))
    {
        MrmFreeQualifierNamesOrValues(*qualifierCount, *qualifierNames);
        *qualifierNames = nullptr;

        MrmFreeQualifierNamesOrValues(*qualifierCount, *qualifierValues);
        *qualifierValues = nullptr;

        *qualifierCount = 0;
    }
    return hr;
}

static HRESULT LoadResourceCandidate(
    _In_ void* resourceManager,
    _In_opt_ void* resourceContext,
    _In_opt_ void* resourceMap,
    int index,
    _In_opt_ PCWSTR resourceIdOrUri,
    _Out_ ResourceCandidateResult* resourceCandidate,
    _Outptr_opt_result_maybenull_ PWSTR* resourceName,
    _Out_opt_ UINT32* qualifierCount,
    _Outptr_opt_result_buffer_(*qualifierCount) PWSTR** qualifierNames,
    _Outptr_opt_result_buffer_(*qualifierCount) PWSTR** qualifierValues)
{
    if (resourceName != nullptr)
    {
        *resourceName = nullptr;
    }

    if (qualifierCount != nullptr)
    {
        *qualifierCount = 0;
    }

    if (qualifierNames != nullptr)
    {
        *qualifierNames = nullptr;
    }

    if (qualifierValues != nullptr)
    {
        *qualifierValues = nullptr;
    }

    StringResult nameResult;
    size_t nameStringLength;

    MrmObjects* resourceManagerObjects = reinterpret_cast<MrmObjects*>(resourceManager);

    ProviderResolver* resolver;
    if (resourceContext == nullptr)
    {
        resolver = resourceManagerObjects->resolver;
    }
    else
    {
        resolver = reinterpret_cast<ProviderResolver*>(resourceContext);
    }

    NamedResourceResult namedResource;

    if (index == INDEX_RESOURCE_URI)
    {
        if (!IsResourceUri(resourceIdOrUri))
        {
            return E_INVALIDARG;
        }

        // Root resource maps are the authority of the URI, and are limited to 255 characters.
        wchar_t rootResourceMap[256] = {};
        unsigned int relativeIdIndex = 0;
        RETURN_IF_FAILED(GetRootAndRelativeIdFromUri(resourceIdOrUri, rootResourceMap, ARRAYSIZE(rootResourceMap), &relativeIdIndex));
        
        const wchar_t* relativeResourceId = &resourceIdOrUri[relativeIdIndex];
        if (relativeResourceId[0] == L'\0')
        {
            // There needs to be a resource left.
            return E_INVALIDARG;
        }

        const IResourceMapBase* internalResourceMap;

        if (rootResourceMap[0] == L'\0')
        {
            // In full MRT, ms-resource:/// is a valid shortcut that refers to the primary resource map. Retain this functionality here.
            RETURN_IF_FAILED(resourceManagerObjects->priFile->GetPrimaryResourceMap(&internalResourceMap));
        }
        else
        {
            // Resolve the named root resource map from the application PRI first. If it
            // isn't present there, follow System MRT: treat the root map name as a package
            // identity in the app's dependency graph and load that package's resources
            // (together with any applicable resource packages) on demand, then resolve the
            // map from the unified view. Root names that don't correspond to a package in
            // the graph remain unresolved, matching System MRT.
            HRESULT resourceMapHr = resourceManagerObjects->priFile->GetResourceMapById(rootResourceMap, &internalResourceMap);
            if (resourceMapHr == HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
            {
                // Fast path under a shared lock: another thread may have already merged the
                // matching package into the unified view.
                {
                    auto lock = resourceManagerObjects->packageGraphLock.lock_shared();
                    resourceMapHr = resourceManagerObjects->unifiedView->GetResourceMapById(rootResourceMap, &internalResourceMap);
                }

                if (resourceMapHr == HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
                {
                    // Merge under an exclusive lock, then resolve. MergePackageResourceFilesForMapName
                    // is idempotent, so a merge that raced ahead of us is a harmless no-op.
                    auto lock = resourceManagerObjects->packageGraphLock.lock_exclusive();
                    (void)MergePackageResourceFilesForMapName(resourceManagerObjects->unifiedView, rootResourceMap);
                    resourceMapHr = resourceManagerObjects->unifiedView->GetResourceMapById(rootResourceMap, &internalResourceMap);
                }
            }
            RETURN_IF_FAILED(resourceMapHr);
        }

        RETURN_IF_FAILED_WITH_EXPECTED(internalResourceMap->GetResource(relativeResourceId, &namedResource), HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));
    }
    else
    {
        const ResourceMapSubtree* internalResourceMap;
        if (resourceMap == nullptr)
        {
            // The primary resource map is the default.
            const IResourceMapBase* resourceMap;
            RETURN_IF_FAILED(resourceManagerObjects->priFile->GetPrimaryResourceMap(&resourceMap));
            internalResourceMap = resourceMap->GetRootSubtree();
        }
        else
        {
            // Use the supplied resource map.
            internalResourceMap = reinterpret_cast<ResourceMapSubtree*>(resourceMap);
        }

        if (index == INDEX_RESOURCE_ID)
        {
            RETURN_IF_FAILED_WITH_EXPECTED(internalResourceMap->GetResource(resourceIdOrUri, &namedResource), HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));
        }
        else
        {
            RETURN_IF_FAILED(internalResourceMap->GetDescendentResource(index, &namedResource));
            if (resourceName != nullptr)
            {
                RETURN_IF_FAILED(internalResourceMap->GetDescendentResourceName(index, &nameResult));

                // This ensures the string result holds a copy of the data we can return to the caller, not a pointer to the PRI file.
                PWSTR localNameString;
                RETURN_IF_FAILED(nameResult.GetWritableRef(&localNameString, &nameStringLength));
            }
        }
    }

    DecisionResult decision;
    RETURN_IF_FAILED(namedResource.GetDecision(&decision));

    QualifierSetResult qualifierSet;
    int resultIndex;
    RETURN_IF_FAILED(resolver->EvaluateDecision(&decision, &resultIndex, &qualifierSet));

    bool isMatch, isDefault, isMatchAsDefault;
    RETURN_IF_FAILED(resolver->EvaluateQualifierSet(&qualifierSet, &isMatch, &isDefault, &isMatchAsDefault, nullptr));

    if (!isMatch && !isDefault)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_NO_MATCH_OR_DEFAULT_CANDIDATE);
    }

    RETURN_IF_FAILED(namedResource.GetCandidate(resultIndex, resourceCandidate));

    if ((qualifierCount != nullptr) && (qualifierNames != nullptr) && (qualifierValues != nullptr))
    {
        RETURN_IF_FAILED(GetQualifierInfoFromCandidate(resourceManagerObjects, resourceCandidate, qualifierCount, qualifierNames, qualifierValues));
    }

    if (resourceName != nullptr)
    {
        if (!nameResult.IsEmpty())
        {
            // This will not fail
            nameResult.ReleaseContents(resourceName, &nameStringLength);
        }
    }
    return S_OK;
}

static HRESULT LoadStringResource(
    _In_ void* resourceManager,
    _In_opt_ void* resourceContext,
    _In_opt_ void* resourceMap,
    int index,
    _In_opt_ PCWSTR resourceIdOrUri,
    _Outptr_ PWSTR* resourceString)
{
    ResourceCandidateResult candidate;
    RETURN_IF_FAILED_WITH_EXPECTED(LoadResourceCandidate(resourceManager, resourceContext, resourceMap, index, resourceIdOrUri, &candidate, nullptr, nullptr, nullptr, nullptr),
        HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));

    StringResult stringResult;
    if (!candidate.TryGetStringValue(&stringResult))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH);
    }

    // This ensures the string result holds a copy of the data we can return to the caller, not a pointer to the PRI file.
    RETURN_IF_FAILED(StringResultReleaseOwnershipBuffer(stringResult, resourceString));

    return S_OK;
}

static HRESULT LoadEmbeddedResource(
    _In_ void* resourceManager,
    _In_opt_ void* resourceContext,
    _In_opt_ void* resourceMap,
    int index,
    _In_opt_ PCWSTR resourceIdOrUri,
    _Out_ MrmResourceData* data)
{
    data->data = nullptr;
    data->size = 0;

    ResourceCandidateResult candidate;
    RETURN_IF_FAILED_WITH_EXPECTED(LoadResourceCandidate(resourceManager, resourceContext, resourceMap, index, resourceIdOrUri, &candidate, nullptr, nullptr, nullptr, nullptr),
        HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));

    BlobResult blobResult;
    if (!candidate.TryGetBlobValue(&blobResult))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_RESOURCE_TYPE_MISMATCH);
    }

    // This ensures the blob result holds a copy of the data we can return to the caller, not a pointer to the PRI file.
    RETURN_IF_FAILED(BlobResultReleaseOwnershipBuffer(blobResult, &data->data, &data->size));

    return S_OK;
}

static HRESULT LoadStringOrEmbeddedResource(
    _In_ void* resourceManager,
    _In_opt_ void* resourceContext,
    _In_opt_ void* resourceMap,
    int index,
    _In_opt_ PCWSTR resourceIdOrUri,
    _Out_ MrmType* resourceType,
    _Outptr_result_maybenull_ PWSTR* resourceString,
    _Out_ MrmResourceData* data,
    _Outptr_opt_result_maybenull_ PWSTR* resourceName,
    _Out_opt_ UINT32* qualifierCount,
    _Outptr_opt_result_buffer_(*qualifierCount) PWSTR** qualifierNames,
    _Outptr_opt_result_buffer_(*qualifierCount) PWSTR** qualifierValues)
{
    data->data = nullptr;
    data->size = 0;

    ResourceCandidateResult candidate;
    PWSTR localName = nullptr;
    RETURN_IF_FAILED_WITH_EXPECTED(LoadResourceCandidate(
        resourceManager,
        resourceContext,
        resourceMap,
        index,
        resourceIdOrUri,
        &candidate,
        &localName,
        qualifierCount,
        qualifierNames,
        qualifierValues),
        HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));
    std::unique_ptr<wchar_t[], decltype(&MrmFreeResource)> name(localName, MrmFreeResource);

    MrmEnvironment::ResourceValueType internalResourceType;
    RETURN_IF_FAILED(candidate.GetResourceValueType(&internalResourceType));

    if (MrmEnvironment::IsBinaryResourceValueType(internalResourceType))
    {
        BlobResult blobResult;
        if (!candidate.TryGetBlobValue(&blobResult))
        {
            return E_UNEXPECTED;
        }

        // This ensures the blob result holds a copy of the data we can return to the caller, not a pointer to the PRI file.
        RETURN_IF_FAILED(BlobResultReleaseOwnershipBuffer(blobResult, &data->data, &data->size));

        *resourceString = nullptr;
        *resourceType = MrmType_Embedded;
    }
    else
    {
        StringResult stringResult;
        if (!candidate.TryGetStringValue(&stringResult))
        {
            return E_UNEXPECTED;
        }

        // This ensures the string result holds a copy of the data we can return to the caller, not a pointer to the PRI file.
        RETURN_IF_FAILED(StringResultReleaseOwnershipBuffer(stringResult, resourceString));

        if (MrmEnvironment::IsStringResourceValueType(internalResourceType))
        {
            *resourceType = MrmType_String;
        }
        else if (MrmEnvironment::IsPathResourceValueType(internalResourceType))
        {
            *resourceType = MrmType_Path;
        }
        else
        {
            return E_UNEXPECTED;
        }
    }

    if (resourceName != nullptr)
    {
        *resourceName = name.release();
    }

    return S_OK;
}

static void DestroyResourceManager(_In_ void* resourceManager)
{
    MrmObjects* resourceManagerObjects = reinterpret_cast<MrmObjects*>(resourceManager);

    if (resourceManagerObjects->profile != nullptr)
    {
        delete resourceManagerObjects->profile;
        resourceManagerObjects->profile = nullptr;
    }

    if (resourceManagerObjects->unifiedView != nullptr)
    {
        delete resourceManagerObjects->unifiedView;
        resourceManagerObjects->unifiedView = nullptr;
    }

    if (resourceManagerObjects->resolver != nullptr)
    {
        delete resourceManagerObjects->resolver;
        resourceManagerObjects->resolver = nullptr;
    }

    delete resourceManagerObjects;

    return;
}

// Returns true if the given path refers to an existing file (not a directory).
static bool ResourcePriFileExists(_In_ PCWSTR priFilePath)
{
    const DWORD attributes = GetFileAttributesW(priFilePath);
    return (attributes != INVALID_FILE_ATTRIBUTES) && ((attributes & FILE_ATTRIBUTE_DIRECTORY) == 0);
}

// Returns the length of the package "Name" segment of a package full name, i.e. the text
// before the first '_' in "<Name>_<Version>_<Architecture>_<ResourceId>_<PublisherId>".
// Returns 0 if the full name is malformed (no '_'), so callers can ignore it.
static int GetPackageNameSegmentLength(_In_ PCWSTR packageFullName)
{
    const wchar_t* underscore = wcschr(packageFullName, L'_');
    return (underscore != nullptr) ? static_cast<int>(underscore - packageFullName) : 0;
}

// Resolves a resource root map name to the package(s) in the app's dependency graph whose
// identity matches it, and merges those packages' resources.pri into the unified view as
// referenced (named) resource maps. This mirrors System MRT: a resource root map name
// identifies a package by identity - its package "Name", which is also the authored
// resource-map name - and that package's resources are loaded on demand. Because a main
// package and its resource packages (language/scale/DPI splits) share the same package
// Name, matching on Name pulls in the resource packages too, which is how a package's
// merged resources are obtained. Root names that don't correspond to a package in the
// graph are left unresolved, matching System MRT. Best effort and a no-op for unpackaged
// apps, which have no package graph.
static HRESULT MergePackageResourceFilesForMapName(_In_ UnifiedResourceView* unifiedView, _In_ PCWSTR rootResourceMapName)
{
    // Enumerate the head package and the full dependency graph that can contribute
    // resources: framework/static, dynamic, optional, host-runtime, and resource
    // packages - the same set System MRT considers. PACKAGE_INFORMATION_BASIC keeps the
    // query cheap since only each package's identity and install path are required.
    //
    // The graph is re-enumerated on each cross-package miss rather than cached for the
    // resource manager's lifetime, because the app's package graph can change at runtime
    // (for example when dynamic dependencies are added) and a cached snapshot could go
    // stale. Re-enumeration only runs on the cold path: once a package is merged, later
    // lookups of its maps resolve directly from the unified view without reaching here.
    const UINT32 filter = PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT | PACKAGE_FILTER_OPTIONAL | PACKAGE_FILTER_HOSTRUNTIME |
                          PACKAGE_FILTER_STATIC | PACKAGE_FILTER_DYNAMIC | PACKAGE_FILTER_RESOURCE | PACKAGE_INFORMATION_BASIC;

    UINT32 bufferLength = 0;
    UINT32 packageCount = 0;
    const LONG sizeResult = GetCurrentPackageInfo(filter, &bufferLength, nullptr, &packageCount);
    if ((sizeResult == APPMODEL_ERROR_NO_PACKAGE) || (sizeResult == ERROR_SUCCESS))
    {
        // Running unpackaged (or with an empty package graph): there is nothing to
        // merge, so preserve the existing single-PRI behavior.
        return S_OK;
    }
    RETURN_HR_IF(HRESULT_FROM_WIN32(sizeResult), sizeResult != ERROR_INSUFFICIENT_BUFFER);

    std::unique_ptr<BYTE[]> buffer(new (std::nothrow) BYTE[bufferLength]);
    RETURN_IF_NULL_ALLOC(buffer.get());
    RETURN_IF_WIN32_ERROR(GetCurrentPackageInfo(filter, &bufferLength, buffer.get(), &packageCount));

    // The application's own resources.pri is already loaded as the primary map; skip it.
    StringResult applicationPriPath;
    PCWSTR applicationPriPathRef = nullptr;
    if (SUCCEEDED(unifiedView->GetApplicationFileInfo(&applicationPriPath, nullptr, nullptr, nullptr)))
    {
        applicationPriPathRef = applicationPriPath.GetRef();
    }

    const PACKAGE_INFO* packages = reinterpret_cast<const PACKAGE_INFO*>(buffer.get());
    for (UINT32 i = 0; i < packageCount; i++)
    {
        const PACKAGE_INFO& package = packages[i];
        PCWSTR packagePath = package.path;
        PCWSTR packageFullName = package.packageFullName;
        if ((packagePath == nullptr) || (*packagePath == L'\0') || (packageFullName == nullptr))
        {
            continue;
        }

        // Match the requested root map name against the package identity. Mirror System MRT,
        // which compares the package full name case-sensitively and the package "Name"
        // case-insensitively. The Name segment is derived from the full name so it does not
        // depend on PACKAGE_INFORMATION_FULL identity fields being populated.
        bool matches = (CompareStringOrdinal(packageFullName, -1, rootResourceMapName, -1, FALSE) == CSTR_EQUAL);
        if (!matches)
        {
            const int nameLength = GetPackageNameSegmentLength(packageFullName);
            matches = (nameLength > 0) && (CompareStringOrdinal(packageFullName, nameLength, rootResourceMapName, -1, TRUE) == CSTR_EQUAL);
        }
        if (!matches)
        {
            continue;
        }

        const size_t priPathLength = wcslen(packagePath) + 1 + ARRAYSIZE(ResourcesPriFileName);
        std::unique_ptr<wchar_t[]> priPath(new (std::nothrow) wchar_t[priPathLength]);
        RETURN_IF_NULL_ALLOC(priPath.get());

        if (FAILED(PathCchCombineEx(priPath.get(), priPathLength, packagePath, ResourcesPriFileName, PATHCCH_ALLOW_LONG_PATHS)))
        {
            continue;
        }

        if ((applicationPriPathRef != nullptr) &&
            (CompareStringOrdinal(priPath.get(), -1, applicationPriPathRef, -1, TRUE) == CSTR_EQUAL))
        {
            continue;
        }

        if (!ResourcePriFileExists(priPath.get()))
        {
            continue;
        }

        // Best effort: a package whose resources cannot be loaded should not fail
        // resolution for the rest of the graph.
        const ManagedResourceMap* referencedMap = nullptr;
        int referencedFileIndex = -1;
        (void)unifiedView->GetOrAddReferencedFile(priPath.get(), packagePath, &referencedMap, &referencedFileIndex);
    }

    return S_OK;
}

STDAPI MrmCreateResourceManager(_In_ PCWSTR priFileName, _Out_ MrmManagerHandle* resourceManager)
{
    *resourceManager = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (priFileName == nullptr) || (*priFileName == L'\0'));

    MrtRuntimeTraceLoggingProvider::MrmCreateResourceManager();

    std::unique_ptr<MrmObjects, decltype(&DestroyResourceManager)> resourceManagerObjects(
        new (std::nothrow) MrmObjects(), &DestroyResourceManager);
    RETURN_IF_NULL_ALLOC(resourceManagerObjects);

    RETURN_IF_FAILED(CoreProfile::ChooseDefaultProfile(&resourceManagerObjects->profile));
    RETURN_IF_FAILED(UnifiedResourceView::CreateInstance(resourceManagerObjects->profile, &resourceManagerObjects->unifiedView));

    HRESULT hr = S_OK;
    if (wcschr(priFileName, L'\\') == nullptr)
    {
        // If it's filename without path, use the module path.
        PWSTR filepath = nullptr;
        RETURN_IF_FAILED(MrmGetFilePathFromName(priFileName, &filepath));

        std::unique_ptr<wchar_t, decltype(&MrmFreeResource)> priPath(filepath, MrmFreeResource);
        hr = resourceManagerObjects->unifiedView->SetApplicationPriFile(priPath.get(), nullptr, &resourceManagerObjects->priFile);
    }
    else
    {
        hr = resourceManagerObjects->unifiedView->SetApplicationPriFile(priFileName, nullptr, &resourceManagerObjects->priFile);
    }
    RETURN_IF_FAILED(hr);

    const IResourceMapBase* primaryMap;
    RETURN_IF_FAILED(resourceManagerObjects->priFile->GetPrimaryResourceMap(&primaryMap));

    RETURN_IF_FAILED(ProviderResolver::CreateInstance(
        resourceManagerObjects->profile,
        resourceManagerObjects->priFile->GetUnifiedEnvironment(),
        primaryMap->GetDecisionInfo(),
        &resourceManagerObjects->resolver));

    *resourceManager = reinterpret_cast<MrmManagerHandle>(resourceManagerObjects.release());
    return S_OK;
}

STDAPI_(void) MrmDestroyResourceManager(MrmManagerHandle resourceManager)
{
    if (resourceManager != nullptr)
    {
        DestroyResourceManager(resourceManager);
        resourceManager = nullptr;
    }

    return;
}

STDAPI MrmCreateResourceContext(_In_ MrmManagerHandle resourceManager, _Out_ MrmContextHandle* resourceContext)
{
    MrmObjects* resourceManagerObjects = reinterpret_cast<MrmObjects*>(resourceManager);

    const IResourceMapBase* primaryMap;
    RETURN_IF_FAILED(resourceManagerObjects->priFile->GetPrimaryResourceMap(&primaryMap));

    ProviderResolver* resolver;
    RETURN_IF_FAILED(ProviderResolver::CreateInstance(
        resourceManagerObjects->profile,
        resourceManagerObjects->priFile->GetUnifiedEnvironment(),
        primaryMap->GetDecisionInfo(),
        &resolver));

    *resourceContext = reinterpret_cast<MrmContextHandle>(resolver);
    return S_OK;
}

STDAPI_(void) MrmFreeQualifierNamesOrValues(UINT32 size, _In_reads_(size) PWSTR* names)
{
    if (names != nullptr)
    {
        PWSTR* eachName = names;
        for (UINT32 i = 0; i < size; i++)
        {
            MrmFreeResource(*eachName);
            *eachName = nullptr;
            eachName++;
        }
        MrmFreeResource(names);
    }
}

STDAPI MrmGetAllQualifierNamesImpl(_In_ MrmContextHandle resourceContext, _Out_ UINT32* size, _Outptr_result_buffer_(*size) PWSTR** names)
{
    *size = 0;
    *names = nullptr;

    const UnifiedEnvironment* environment = reinterpret_cast<ProviderResolver*>(resourceContext)->GetEnvironment();

    AutoDeletePtr<DynamicArray<Atom>> qualifierNameAtoms;
    RETURN_IF_FAILED(environment->GetAllAtoms(UnifiedEnvironment::QualifierNames, &qualifierNameAtoms));

    *size = qualifierNameAtoms->Count();
    UINT32 bufferSize;
    RETURN_IF_FAILED(UInt32Mult(*size, sizeof(*names), &bufferSize));

    *names = reinterpret_cast<PWSTR*>(MrmAllocateBuffer(bufferSize));
    RETURN_IF_NULL_ALLOC(*names);

    ZeroMemory(*names, bufferSize);

    PWSTR* eachName = *names;
    for (UINT32 i = 0; i < *size; i++)
    {
        Atom nameAtom;
        RETURN_IF_FAILED(qualifierNameAtoms->Get(i, &nameAtom));

        StringResult result;
        RETURN_IF_FAILED(environment->GetName(UnifiedEnvironment::QualifierNames, nameAtom, &result));

        // This ensures the string result holds a copy of the data we can return to the caller, not a pointer to the PRI file.
        RETURN_IF_FAILED(StringResultReleaseOwnershipBuffer(result, eachName));
        eachName++;
    }

    return S_OK;
}

STDAPI MrmGetAllQualifierNames(_In_ MrmContextHandle resourceContext, _Out_ UINT32* size, _Outptr_result_buffer_(*size) PWSTR** names)
{
    HRESULT hr = MrmGetAllQualifierNamesImpl(resourceContext, size, names);
    if (FAILED(hr))
    {
        MrmFreeQualifierNamesOrValues(*size, *names);

        *names = nullptr;
        *size = 0;
    }
    return hr;
}

STDAPI MrmGetQualifier(_In_ MrmContextHandle resourceContext, _In_ PCWSTR qualifierName, _Outptr_ PWSTR* qualifierValue)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, resourceContext);

    StringResult stringResult;
    RETURN_IF_FAILED(reinterpret_cast<ProviderResolver*>(resourceContext)->GetQualifierValue(qualifierName, &stringResult));

    // This ensures the string result holds a copy of the data we can return to the caller, not a pointer to the internal cache.
    RETURN_IF_FAILED(StringResultReleaseOwnershipBuffer(stringResult, qualifierValue));

    return S_OK;
}

STDAPI MrmSetQualifier(_In_ MrmContextHandle resourceContext, _In_ PCWSTR qualifierName, _In_ PCWSTR qualifierValue)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, resourceContext);

    return reinterpret_cast<ProviderResolver*>(resourceContext)->SetQualifier(qualifierName, qualifierValue);
}

STDAPI_(void) MrmDestroyResourceContext(_In_opt_ MrmContextHandle resourceContext)
{
    if (resourceContext != nullptr)
    {
        ProviderResolver* resolver = reinterpret_cast<ProviderResolver*>(resourceContext);
        delete resolver;

        resourceContext = nullptr;
    }

    return;
}

STDAPI MrmGetChildResourceMap(
    _In_ MrmManagerHandle resourceManager,
    _In_opt_ MrmMapHandle resourceMap,
    _In_ PCWSTR childResourceMapName,
    _Out_ MrmMapHandle* childResourceMap)
{
    MrmObjects* resourceManagerObjects = reinterpret_cast<MrmObjects*>(resourceManager);
    const ResourceMapSubtree* originalMapSubtree;
    if (IsResourceUri(childResourceMapName))
    {
        // If a full URI is passed in, we will respect the URI instead of trying to get the child map.
        
        // Root resource maps are the authority of the URI, and are limited to 255 characters.
        wchar_t rootResourceMap[256] = {};
        unsigned int relativeIdIndex = 0;
        RETURN_IF_FAILED(GetRootAndRelativeIdFromUri(childResourceMapName, rootResourceMap, ARRAYSIZE(rootResourceMap), &relativeIdIndex));
        
        const IResourceMapBase* internalRootResourceMap;
        if (rootResourceMap[0] == L'\0')
        {
            // In full MRT, ms-resource:/// is a valid shortcut that refers to the primary resource map. Retain this functionality here.
            RETURN_IF_FAILED(resourceManagerObjects->priFile->GetPrimaryResourceMap(&internalRootResourceMap));
        }
        else
        {
            // Resolve the named root map from the application PRI first, then follow
            // System MRT: treat the root map name as a package identity in the app's
            // dependency graph, load that package's resources (and any applicable resource
            // packages) on demand, and resolve the subtree/property bag from the unified
            // view. Root names that don't correspond to a package in the graph remain
            // unresolved, matching System MRT.
            HRESULT rootMapHr = resourceManagerObjects->priFile->GetResourceMapById(rootResourceMap, &internalRootResourceMap);
            if (rootMapHr == HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
            {
                // Fast path under a shared lock: another thread may have already merged the
                // matching package into the unified view.
                {
                    auto lock = resourceManagerObjects->packageGraphLock.lock_shared();
                    rootMapHr = resourceManagerObjects->unifiedView->GetResourceMapById(rootResourceMap, &internalRootResourceMap);
                }

                if (rootMapHr == HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
                {
                    // Merge under an exclusive lock, then resolve. MergePackageResourceFilesForMapName
                    // is idempotent, so a merge that raced ahead of us is a harmless no-op.
                    auto lock = resourceManagerObjects->packageGraphLock.lock_exclusive();
                    (void)MergePackageResourceFilesForMapName(resourceManagerObjects->unifiedView, rootResourceMap);
                    rootMapHr = resourceManagerObjects->unifiedView->GetResourceMapById(rootResourceMap, &internalRootResourceMap);
                }
            }
            RETURN_IF_FAILED(rootMapHr);
        }

        originalMapSubtree = internalRootResourceMap->GetRootSubtree();

        const wchar_t* relativeResourceId = &childResourceMapName[relativeIdIndex];
        if (relativeResourceId[0] != L'\0')
        {
            const ResourceMapSubtree* childSubTree;
            RETURN_IF_FAILED_WITH_EXPECTED(originalMapSubtree->GetSubtree(relativeResourceId, &childSubTree), HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND));

            *childResourceMap = reinterpret_cast<MrmMapHandle>(const_cast<ResourceMapSubtree*>(childSubTree));

        }
        else
        {
            *childResourceMap = reinterpret_cast<MrmMapHandle>(const_cast<ResourceMapSubtree*>(originalMapSubtree));
        }
    }
    else
    {
        if (resourceMap == nullptr)
        {
            const IResourceMapBase* internalResourceMap;
            RETURN_IF_FAILED(resourceManagerObjects->priFile->GetPrimaryResourceMap(&internalResourceMap));

            originalMapSubtree = internalResourceMap->GetRootSubtree();
        }
        else
        {
            originalMapSubtree = reinterpret_cast<ResourceMapSubtree*>(resourceMap);
        }

        const ResourceMapSubtree* childSubTree;
        RETURN_IF_FAILED_WITH_EXPECTED(originalMapSubtree->GetSubtree(childResourceMapName, &childSubTree), HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND));

        *childResourceMap = reinterpret_cast<MrmMapHandle>(const_cast<ResourceMapSubtree*>(childSubTree));
    }
    return S_OK;
}

STDAPI MrmGetResourceCount(_In_ MrmManagerHandle resourceManager, _In_opt_ MrmMapHandle resourceMap, _Out_ UINT32* count)
{
    const ResourceMapSubtree* mapSubtree;

    if (resourceMap == nullptr)
    {
        MrmObjects* resourceManagerObjects = reinterpret_cast<MrmObjects*>(resourceManager);

        const IResourceMapBase* internalResourceMap;
        RETURN_IF_FAILED(resourceManagerObjects->priFile->GetPrimaryResourceMap(&internalResourceMap));

        mapSubtree = internalResourceMap->GetRootSubtree();
    }
    else
    {
        mapSubtree = reinterpret_cast<ResourceMapSubtree*>(resourceMap);
    }

    *count = static_cast<UINT32>(mapSubtree->GetNumDescendentResources());

    return S_OK;
}

STDAPI MrmLoadStringResource(
    _In_ MrmManagerHandle resourceManager,
    _In_opt_ MrmContextHandle resourceContext,
    _In_opt_ MrmMapHandle resourceMap,
    _In_ PCWSTR resourceId,
    _Outptr_ PWSTR* resourceString)
{
    RETURN_IF_FAILED_WITH_EXPECTED(LoadStringResource(resourceManager, resourceContext, resourceMap, INDEX_RESOURCE_ID, resourceId, resourceString), HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));
    return S_OK;
}

STDAPI MrmLoadStringResourceFromResourceUri(
    _In_ MrmManagerHandle resourceManager,
    _In_opt_ MrmContextHandle resourceContext,
    _In_ PCWSTR resourceUri,
    _Outptr_ PWSTR* resourceString)
{
    RETURN_IF_FAILED_WITH_EXPECTED(LoadStringResource(resourceManager, resourceContext, nullptr, INDEX_RESOURCE_URI, resourceUri, resourceString), HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));
    return S_OK;
}

STDAPI MrmLoadEmbeddedResource(
    _In_ MrmManagerHandle resourceManager,
    _In_opt_ MrmContextHandle resourceContext,
    _In_opt_ MrmMapHandle resourceMap,
    _In_ PCWSTR resourceId,
    _Out_ MrmResourceData* data)
{
    RETURN_IF_FAILED_WITH_EXPECTED(LoadEmbeddedResource(resourceManager, resourceContext, resourceMap, INDEX_RESOURCE_ID, resourceId, data), HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));
    return S_OK;
}

STDAPI MrmLoadEmbeddedResourceFromResourceUri(
    _In_ MrmManagerHandle resourceManager,
    _In_opt_ MrmContextHandle resourceContext,
    _In_ PCWSTR resourceUri,
    _Out_ MrmResourceData* data)
{
    RETURN_IF_FAILED_WITH_EXPECTED(LoadEmbeddedResource(resourceManager, resourceContext, nullptr, INDEX_RESOURCE_URI, resourceUri, data), HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));
    return S_OK;
}

STDAPI MrmLoadStringOrEmbeddedResource(
    _In_ MrmManagerHandle resourceManager,
    _In_opt_ MrmContextHandle resourceContext,
    _In_opt_ MrmMapHandle resourceMap,
    _In_ PCWSTR resourceId,
    _Out_ MrmType* resourceType,
    _Outptr_result_maybenull_ PWSTR* resourceString,
    _Out_ MrmResourceData* data)
{
    if (IsResourceUri(resourceId))
    {
        RETURN_IF_FAILED_WITH_EXPECTED(LoadStringOrEmbeddedResource(
            resourceManager, resourceContext, nullptr, INDEX_RESOURCE_URI, resourceId, resourceType, resourceString, data, nullptr, nullptr, nullptr, nullptr),
            HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));
    }
    else
    {
        RETURN_IF_FAILED_WITH_EXPECTED(LoadStringOrEmbeddedResource(
            resourceManager, resourceContext, resourceMap, INDEX_RESOURCE_ID, resourceId, resourceType, resourceString, data, nullptr, nullptr, nullptr, nullptr),
            HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));
    }
    return S_OK;
}

STDAPI MrmLoadStringOrEmbeddedResourceWithQualifierValues(
    _In_ MrmManagerHandle resourceManager,
    _In_opt_ MrmContextHandle resourceContext,
    _In_opt_ MrmMapHandle resourceMap,
    _In_ PCWSTR resourceId,
    _Out_ MrmType* resourceType,
    _Outptr_result_maybenull_ PWSTR* resourceString,
    _Out_ MrmResourceData* data,
    _Out_ UINT32* qualifierCount,
    _Outptr_result_buffer_(*qualifierCount) PWSTR** qualifierNames,
    _Outptr_result_buffer_(*qualifierCount) PWSTR** qualifierValues)
{
    if (IsResourceUri(resourceId))
    {
        RETURN_IF_FAILED_WITH_EXPECTED(LoadStringOrEmbeddedResource(
            resourceManager,
            resourceContext,
            nullptr,
            INDEX_RESOURCE_URI,
            resourceId,
            resourceType,
            resourceString,
            data,
            nullptr,
            qualifierCount,
            qualifierNames,
            qualifierValues),
            HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));
    }
    else
    {
        RETURN_IF_FAILED_WITH_EXPECTED(LoadStringOrEmbeddedResource(
            resourceManager,
            resourceContext,
            resourceMap,
            INDEX_RESOURCE_ID,
            resourceId,
            resourceType,
            resourceString,
            data,
            nullptr,
            qualifierCount,
            qualifierNames,
            qualifierValues),
            HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));
    }
    return S_OK;
}

STDAPI MrmLoadStringOrEmbeddedFromResourceUri(
    _In_ MrmManagerHandle resourceManager,
    _In_opt_ MrmContextHandle resourceContext,
    _In_ PCWSTR resourceUri,
    _Out_ MrmType* resourceType,
    _Outptr_result_maybenull_ PWSTR* resourceString,
    _Out_ MrmResourceData* data)
{
    RETURN_IF_FAILED_WITH_EXPECTED(LoadStringOrEmbeddedResource(
        resourceManager, resourceContext, nullptr, INDEX_RESOURCE_URI, resourceUri, resourceType, resourceString, data, nullptr, nullptr, nullptr, nullptr),
        HRESULT_FROM_WIN32(ERROR_MRM_NAMED_RESOURCE_NOT_FOUND));
    return S_OK;
}

STDAPI MrmLoadStringOrEmbeddedResourceByIndex(
    _In_ MrmManagerHandle resourceManager,
    _In_opt_ MrmContextHandle resourceContext,
    _In_opt_ MrmMapHandle resourceMap,
    UINT32 index,
    _Out_ MrmType* resourceType,
    _Outptr_ PWSTR* resourceName,
    _Outptr_result_maybenull_ PWSTR* resourceString,
    _Out_ MrmResourceData* data)
{
    RETURN_IF_FAILED(LoadStringOrEmbeddedResource(
        resourceManager, resourceContext, resourceMap, index, nullptr, resourceType, resourceString, data, resourceName, nullptr, nullptr, nullptr));
    return S_OK;
}

STDAPI MrmLoadStringOrEmbeddedResourceByIndexWithQualifierValues(
    _In_ MrmManagerHandle resourceManager,
    _In_opt_ MrmContextHandle resourceContext,
    _In_opt_ MrmMapHandle resourceMap,
    UINT32 index,
    _Out_ MrmType* resourceType,
    _Outptr_ PWSTR* resourceName,
    _Outptr_result_maybenull_ PWSTR* resourceString,
    _Out_ MrmResourceData* data,
    _Out_ UINT32* qualifierCount,
    _Outptr_result_buffer_(*qualifierCount) PWSTR** qualifierNames,
    _Outptr_result_buffer_(*qualifierCount) PWSTR** qualifierValues)
{
    RETURN_IF_FAILED(LoadStringOrEmbeddedResource(
        resourceManager,
        resourceContext,
        resourceMap,
        index,
        nullptr,
        resourceType,
        resourceString,
        data,
        resourceName,
        qualifierCount,
        qualifierNames,
        qualifierValues));
    return S_OK;
}

STDAPI_(void*) MrmAllocateBuffer(size_t size) { return Def_Alloc(size); }

STDAPI_(void) MrmFreeResource(_In_opt_ void* resource)
{
    if (resource != nullptr)
    {
        Def_Free(resource);
    }

    return;
}

// The base directory is communicated via the MICROSOFT_WINDOWSAPPRUNTIME_BASE_DIRECTORY process
// environment variable, which is inherited by child processes spawned via CreateProcess. Its owner
// also stamps its process id in MICROSOFT_WINDOWSAPPRUNTIME_BASE_DIRECTORY_PID. Honor the base
// directory only when that stamp matches the current process; otherwise it was inherited from a
// parent and must be ignored (a child would otherwise resolve resources from the parent's directory).
// See https://github.com/microsoft/WindowsAppSDK/issues/5987.
static bool IsBaseDirectoryStampedByCurrentProcess()
{
    wchar_t stampedPidText[16]{};
    const DWORD length{ ::GetEnvironmentVariableW(
        L"MICROSOFT_WINDOWSAPPRUNTIME_BASE_DIRECTORY_PID", stampedPidText, ARRAYSIZE(stampedPidText)) };
    if ((length == 0) || (length >= ARRAYSIZE(stampedPidText)))
    {
        // Not stamped (absent) or unexpectedly long: do not honor the base directory.
        return false;
    }

    return static_cast<DWORD>(wcstoul(stampedPidText, nullptr, 10)) == ::GetCurrentProcessId();
}

// When filename is provided, append filename to current module path. If the file doesn't exist, it will
// append the filename to parent path. If none exists, file in current module
// path will be returned.
// Visual Studio usually builds the executable to a subfolder with project name for packaged project
// unless TargetPlatformIdentifier is UAP. To accommodate this behavior, we will
// try to search resources.pri from both module path and parent path.
//
// When filename is not provided or empty, we will search resources.pri under current module
// path. If the file doesn't exist, search [modulename].pri instead.
// For unpackaged app, the built resource name is [modulename].pri. We still search resources.pri
// because that is a supported scenario for inbox MRT (Xaml islands).
//
// A file path is always returned even if none of the files under the above mentioned searching
// criteria exists. In that case, we will return filename (if provided) or resources.pri (if name not
// provided) under module file path. The reason is that we don't want to fail the creation of
// ResourceManager even if an app doesn't have PRI file.
STDAPI MrmGetFilePathFromName(_In_opt_ PCWSTR filename, _Outptr_ PWSTR* filePath)
{
    *filePath = nullptr;

    wil::unique_cotaskmem_string exeDir;
    RETURN_IF_FAILED(wil::GetModuleFileNameW(nullptr, exeDir));
    PCWSTR exeName = wil::find_last_path_segment(exeDir.get());
    wchar_t modulePriFileName[MAX_PATH];
    RETURN_IF_FAILED(StringCchCopyW(modulePriFileName, ARRAYSIZE(modulePriFileName), *exeName ? exeName : exeDir.get()));
    RETURN_IF_FAILED(PathCchRenameExtension(modulePriFileName, ARRAYSIZE(modulePriFileName), L"pri"));
    size_t exeDirCount;
    RETURN_IF_FAILED(StringCchLengthW(exeDir.get(), STRSAFE_MAX_CCH, &exeDirCount));
    RETURN_IF_FAILED(SizeTAdd(exeDirCount, 1, &exeDirCount));
    RETURN_IF_FAILED(PathCchRemoveFileSpec(exeDir.get(), exeDirCount));

    // The ParentPathForFileName pass truncates exeDir in place to reach the parent folder, so
    // preserve the original module directory here for the DefaultFallback pass, which must return
    // a path under the module directory (the documented behavior).
    std::wstring moduleDir(exeDir.get());

    enum SearchPass
    {
        exeDirForFileName,
        ParentPathForFileName,
        BaseDirForResourcesPri,
        BaseDirForModulePri,
        exeDirForResourcesPri,
        exeDirForModulePri,
        DefaultFallback,
        Final,
    };
    SearchPass searchStart = SearchPass::exeDirForFileName;
    wil::unique_cotaskmem_string baseDir;
    size_t baseDirCount{};
    if (filename == nullptr || *filename == L'\0')
    {
        searchStart = SearchPass::exeDirForResourcesPri;
        // Honor MICROSOFT_WINDOWSAPPRUNTIME_BASE_DIRECTORY only when it was stamped by the current
        // process. It is a process environment variable (inherited across CreateProcess), so without
        // this guard a child would load the parent's resources.pri from the parent's base directory.
        // When the stamp is foreign or absent, leave baseDir empty and fall back to the module (exe)
        // directory (handled by the passes below and DefaultFallback).
        // See https://github.com/microsoft/WindowsAppSDK/issues/5987.
        if (IsBaseDirectoryStampedByCurrentProcess() &&
            SUCCEEDED(wil::TryGetEnvironmentVariableW(L"MICROSOFT_WINDOWSAPPRUNTIME_BASE_DIRECTORY", baseDir)) && baseDir)
        {
            searchStart = SearchPass::BaseDirForResourcesPri;
            RETURN_IF_FAILED(StringCchLengthW(baseDir.get(), STRSAFE_MAX_CCH, &baseDirCount));
            RETURN_IF_FAILED(SizeTAdd(baseDirCount, 1, &baseDirCount));
        }
    }

    // If filename is provided:
    //   - search under exe path
    //   - search parent path
    // If filename is not provided:
    //   - if baseDir exists
    //      - search under baseDir for resources.pri
    //      - search under baseDir for [modulename].pri
    //   - if exeDir != baseDir
    //      - search under exeDir for resources.pri
    //      - search under exeDir for [modulename].pri
    PWSTR searchDir{};
    size_t searchDirCount{};
    PCWSTR searchFilename{};
    for (SearchPass pass = searchStart; pass < SearchPass::Final; pass = SearchPass(pass+1))
    {
        switch(pass)
        {
            // Search, given FileName
            case SearchPass::exeDirForFileName:
                searchDir = exeDir.get();
                searchDirCount = exeDirCount;
                searchFilename = filename;
                break;
            case SearchPass::ParentPathForFileName:
                // move to parent folder of previous search
                RETURN_IF_FAILED(PathCchRemoveFileSpec(searchDir, searchDirCount));
                // If the parent search misses, skip the no-FileName passes and fall through to
                // DefaultFallback so we still return a best-effort path (the documented
                // always-succeed contract). The loop's increment lands pass on DefaultFallback.
                pass = SearchPass(SearchPass::DefaultFallback - 1);
                break;

            // Search, given no FileName
            case SearchPass::BaseDirForResourcesPri:
                searchDir = baseDir.get();
                searchDirCount = baseDirCount;
                searchFilename = ResourcesPriFileName;
                break;
            case SearchPass::BaseDirForModulePri:
                // Change to [modulename].pri
                searchFilename = modulePriFileName;
                break;
            case SearchPass::exeDirForResourcesPri:
                searchDir = exeDir.get();
                searchDirCount = exeDirCount;
                searchFilename = ResourcesPriFileName;
                break;
            case SearchPass::exeDirForModulePri:
                searchFilename = modulePriFileName;
                // If this search misses, fall through to DefaultFallback (the next pass) so we
                // still return a best-effort path (the documented always-succeed contract).
                break;
            case SearchPass::DefaultFallback:
                // No file was found in any prior pass. Return a best-effort path even though it
                // doesn't exist, matching the documented contract: the provided filename (if any)
                // or resources.pri, under the base directory (if set) otherwise the module (exe)
                // directory. Callers (e.g. ResourceManager) tolerate a non-existent path.
                if (filename == nullptr || *filename == L'\0')
                {
                    if (baseDir)
                    {
                        searchDir = baseDir.get();
                        searchDirCount = baseDirCount;
                    }
                    else
                    {
                        searchDir = moduleDir.data();
                        searchDirCount = exeDirCount;
                    }
                    searchFilename = ResourcesPriFileName;
                }
                else
                {
                    searchDir = moduleDir.data();
                    searchDirCount = exeDirCount;
                    searchFilename = filename;
                }
                break;
        }

        size_t searchFilenameCount;
        RETURN_IF_FAILED(StringCchLengthW(searchFilename, STRSAFE_MAX_CCH, &searchFilenameCount));

        size_t searchPathCount;
        RETURN_IF_FAILED(SizeTAdd(searchDirCount, searchFilenameCount, &searchPathCount));

        size_t bufferByteSize;
        RETURN_IF_FAILED(SizeTMult(searchPathCount, sizeof(wchar_t), &bufferByteSize));
        PWSTR outputPathBuffer = reinterpret_cast<PWSTR>(MrmAllocateBuffer(bufferByteSize));
        RETURN_IF_NULL_ALLOC(outputPathBuffer);

        std::unique_ptr<wchar_t, decltype(&MrmFreeResource)> outputPath(outputPathBuffer, MrmFreeResource);
        RETURN_IF_FAILED(PathCchCombineEx(
            outputPath.get(),
            searchPathCount,
            searchDir,
            searchFilename,
            PATHCCH_ALLOW_LONG_PATHS));

        DWORD attributes = GetFileAttributes(outputPath.get());
        if ((pass == SearchPass::DefaultFallback) ||
            ((attributes != INVALID_FILE_ATTRIBUTES) && !(attributes & FILE_ATTRIBUTE_DIRECTORY)))
        {
            *filePath = outputPath.release();
            break;
        }
    }

    return S_OK;
}
