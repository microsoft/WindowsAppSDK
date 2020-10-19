// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"
#include <accctrl.h> // OBJECTS_AND_SID
#include <aclapi.h> // GetNamedSecurityInfo etc.
#include <strsafe.h>

using namespace Microsoft::Resources::Build;
#include "mrm/build/ResourcePackMerge.h"

namespace Microsoft::Resources::Build
{

const int PriFileMerger::CLEANUP_MIN_DAYS = 32;
const int PriFileMerger::CLEANUP_MAX_FILES = 10;

HRESULT PriFileMerger::AddAllApplicationPackagesSid(_In_ PCWSTR pszFilePath, _In_ bool bPathIsFolder)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pszFilePath));

    auto logOnFailure = wil::scope_exit([&] { WRITE_MRMMIN_INIT_TRACE_ERROR_CHECK(pszFilePath, 0); });

    // Get current DACL
    PACL pDaclCurrent = nullptr;
    wil::unique_hlocal_security_descriptor securityDescriptor;
    RETURN_IF_WIN32_ERROR(GetNamedSecurityInfo(
        pszFilePath, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, &pDaclCurrent, nullptr, &securityDescriptor));

    // Get ANY PACKAGE SID
    wil::unique_sid pAppPackagesSid;
    SID_IDENTIFIER_AUTHORITY appPackageAuthority = SECURITY_APP_PACKAGE_AUTHORITY;
    RETURN_IF_WIN32_BOOL_FALSE(AllocateAndInitializeSid(
        &appPackageAuthority,
        SECURITY_BUILTIN_APP_PACKAGE_RID_COUNT,
        SECURITY_APP_PACKAGE_BASE_RID,
        SECURITY_BUILTIN_PACKAGE_ANY_PACKAGE,
        0,
        0,
        0,
        0,
        0,
        0,
        &pAppPackagesSid));

    ACE_HEADER* aceHeader = nullptr;
    for (UINT aceIndex = 0; aceIndex < pDaclCurrent->AceCount; aceIndex++)
    {
        RETURN_IF_WIN32_BOOL_FALSE(GetAce(pDaclCurrent, aceIndex, (LPVOID*)&aceHeader));

        if ((aceHeader->AceType == ACCESS_ALLOWED_ACE_TYPE) && (!(aceHeader->AceFlags & INHERIT_ONLY)))
        {
            ACCESS_ALLOWED_ACE* accessAllowedAce = (ACCESS_ALLOWED_ACE*)aceHeader;
            if (EqualSid((PSID)&accessAllowedAce->SidStart, pAppPackagesSid.get()))
            {
                if (accessAllowedAce->Mask & FILE_GENERIC_READ)
                {
                    logOnFailure.release();
                    return S_OK;
                }
            }
        }
    }

    // Set updated DACL using SetNamedSecurityInfo
    ULONG daclNewSize = 0;
    RETURN_IF_FAILED(DWordAdd(daclNewSize, GetLengthSid(pAppPackagesSid.get()), &daclNewSize));
    RETURN_IF_FAILED(DWordAdd(daclNewSize, sizeof(ACCESS_ALLOWED_ACE), &daclNewSize));
    RETURN_IF_FAILED(DWordAdd(daclNewSize, pDaclCurrent->AclSize, &daclNewSize));

    unique_deffree_ptr<ACL> pDaclNew((PACL)_DefPlatformAllocZeroed(daclNewSize));
    RETURN_IF_NULL_ALLOC(pDaclNew.get());

    memcpy_s(pDaclNew.get(), daclNewSize, pDaclCurrent, pDaclCurrent->AclSize);
    pDaclNew->AclSize = (WORD)daclNewSize;
    RETURN_IF_WIN32_BOOL_FALSE(AddAccessAllowedAceEx(
        pDaclNew.get(),
        ACL_REVISION,
        bPathIsFolder ? (CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) : 0,
        FILE_GENERIC_READ,
        pAppPackagesSid.get()));

    RETURN_IF_WIN32_ERROR(SetNamedSecurityInfo(
        const_cast<PWSTR>(pszFilePath), SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, nullptr, nullptr, pDaclNew.get(), nullptr));

    logOnFailure.release();

    return S_OK;
}

PriFileMerger::PriMergeFlags PriFileMerger::DefaultPriMergeFlags = static_cast<Build::PriFileMerger::PriMergeFlags>(
    Build::PriFileMerger::MergeDefaultFlags | Build::PriFileMerger::AcceptCompatiblePriorVersion | Build::PriFileMerger::SuppressErrors);

HRESULT PriFileMerger::CreateInstance(_In_ CoreProfile* pProfile, _Outptr_ PriFileMerger** result)
{
    *result = nullptr;

    AutoDeletePtr<PriFileMerger> pPriFileMerger = new PriFileMerger();
    RETURN_IF_NULL_ALLOC(pPriFileMerger);

    RETURN_IF_FAILED(pPriFileMerger->Init(pProfile));

    *result = pPriFileMerger.Detach();

    return S_OK;
}

HRESULT PriFileMerger::Init(_In_ CoreProfile* pProfile)
{
    m_pProfile = pProfile;

    RETURN_IF_FAILED(PriFileBuilder::CreateInstance(pProfile, &m_pPriFileBuilder));

    m_pPriMapMerger = NULL;

    m_priBuilderPhase = PriBuilderPhase::PriInitialized;
    return S_OK;
}

PriFileMerger::PriFileMerger() : m_priBuilderPhase(PriBuilderPhase::PriUninitialized), m_pPriFileBuilder(nullptr) {}

PriFileMerger::~PriFileMerger()
{
    if (m_priBuilderPhase != PriBuilderPhase::PriReleasedOwnership)
    {
        delete m_pPriFileBuilder;
    }
}

PriFileBuilder* PriFileMerger::GetPriFileBuilder() { return m_pPriFileBuilder; }

HRESULT PriFileMerger::SetPriFileFlags(_In_ UINT32 nFlags)
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriInitialized);

    return m_pPriFileBuilder->GetDescriptor()->SetPriFileFlags(nFlags);
}

HRESULT PriFileMerger::WriteToFile(_In_ PCWSTR pFilePath)
{
    m_priBuilderPhase = PriBuilderPhase::PriFinalizedAll;
    RETURN_IF_FAILED(m_pPriFileBuilder->WriteToFile(pFilePath));

    // Set GENERIC_READ for ALL APPLICATION PACKAGES for the output merged files
    RETURN_IF_FAILED(AddAllApplicationPackagesSid(pFilePath, true));

    return S_OK;
}

HRESULT PriFileMerger::WriteToUniqueTempDirectory(_In_ PCWSTR pFileName, _Inout_ StringResult* pStrOutputTempPath)
{
    wchar_t wszMrtMergeTempPath[MAX_PATH] = {};
    PWSTR pszMrtMergeTempPath = wszMrtMergeTempPath;
    RETURN_IF_FAILED(CreateUniqueTempDirectory(MAX_PATH, pszMrtMergeTempPath));

    StringResult strOutputTempFilePath;
    RETURN_IF_FAILED(strOutputTempFilePath.SetCopy(pszMrtMergeTempPath));
    RETURN_IF_FAILED(strOutputTempFilePath.ConcatPathElement(pFileName));
    RETURN_IF_FAILED(WriteToFile(strOutputTempFilePath.GetRef()));
    RETURN_IF_FAILED(pStrOutputTempPath->SetCopy(strOutputTempFilePath.GetRef()));

    return S_OK;
}

HRESULT PriFileMerger::CleanupMergeFolder(_In_ PCWSTR pszMergeFolder, _In_ PCWSTR pszPattern, _In_ PCWSTR pszFilePathNotToDelete)
{
    HRESULT hr = DeleteOldMergedFiles(
        pszMergeFolder, pszPattern, PriFileMerger::CLEANUP_MIN_DAYS, PriFileMerger::CLEANUP_MAX_FILES, pszFilePathNotToDelete);
    if (FAILED(hr))
    {
        WRITE_MRMMIN_INIT_TRACE_ERROR_CHECK(pszMergeFolder, hr);
    }
    return hr;
}

HRESULT PriFileMerger::DeleteOldMergedFiles(
    _In_ PCWSTR pszMergeFolder,
    _In_ PCWSTR pszPattern,
    _In_ UINT nMinDaysOlder,
    _In_ UINT nMaxFilesToDelete,
    _In_ PCWSTR pszFilePathNotToDelete)
{
    static double dTotalSecondsInAday = 24 * 60 * 60;
    WIN32_FIND_DATA FindFileData;
    SYSTEMTIME curSysTime;
    FILETIME lCurSysFileTime;
    FILETIME lLastAccessFileTime;
    ULONGLONG lLastAccessTimer;
    ULARGE_INTEGER uliLastAcessTimer;
    ULONGLONG lCurrentTimer;
    ULARGE_INTEGER uliCurrentTimer;
    ULONGLONG lDiff;
    __int64 nDiff;
    UINT nNumFilesAttempted;

    // Get current system time as file time
    GetSystemTime(&curSysTime);
    SystemTimeToFileTime(&curSysTime, &lCurSysFileTime);
    // Use ULARGE_INTEGER.QuadPart to convert FILETIME to a ULONGLONG
    uliCurrentTimer.LowPart = lCurSysFileTime.dwLowDateTime;
    uliCurrentTimer.HighPart = lCurSysFileTime.dwHighDateTime;
    lCurrentTimer = uliCurrentTimer.QuadPart;

    // Find all .pri files in given folder
    StringResult strCandidateFileDir;
    RETURN_IF_FAILED(strCandidateFileDir.SetCopy(pszMergeFolder));
    RETURN_IF_FAILED(strCandidateFileDir.ConcatPathElement(pszPattern));

    wil::unique_hfind hFindFile(FindFirstFile(strCandidateFileDir.GetRef(), &FindFileData));
    if (hFindFile.get() != INVALID_HANDLE_VALUE)
    {
        nNumFilesAttempted = 0;
        do
        {
            if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                // Check for files older than nMinDaysOlder days
                lLastAccessFileTime = FindFileData.ftLastAccessTime;
                // Use ULARGE_INTEGER.QuadPart to convert FILETIME to a ULONGLONG
                uliLastAcessTimer.LowPart = lLastAccessFileTime.dwLowDateTime;
                uliLastAcessTimer.HighPart = lLastAccessFileTime.dwHighDateTime;
                lLastAccessTimer = uliLastAcessTimer.QuadPart;
                lDiff = lCurrentTimer - lLastAccessTimer;
                // FILETIME structure is a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601
                // Represent the difference in seconds by dividing by 10 to the power of 7 (100 nano)
                lDiff = lDiff / 10000000;
                // Check whether this difference in seconds is atleast nMinDaysOlder days
                nDiff = (lDiff - (nMinDaysOlder * dTotalSecondsInAday));
                WRITE_MRMMIN_INIT_TRACE_INFO(FindFileData.cFileName, S_OK);

                if (nDiff > 0)
                {
                    // best effort deletion
                    PCWSTR pszFileName = (PCWSTR)FindFileData.cFileName;
                    StringResult strFilePath;
                    RETURN_IF_FAILED(strFilePath.SetCopy(pszMergeFolder));
                    RETURN_IF_FAILED(strFilePath.ConcatPathElement(pszFileName));

                    /*
                                    We always accept the recently written file and will not delete it at any case.
                                    Please refer msdn article on File Times - 
                                    Timestamps are updated at various times and for various reasons. The only guarantee about a file timestamp 
                                    is that the file time is correctly reflected when the handle that makes the change is closed.
                                    Not all file systems can record creation and last access times, and not all file systems record them in the same manner. 
                                    For example, the resolution of create time on FAT is 10 milliseconds, while write time has a resolution of 2 seconds and 
                                    access time has a resolution of 1 day, so it is really the access date. The NTFS file system delays updates to the last 
                                    access time for a file by up to 1 hour after the last access.
                                    */
                    if (DefString_ICompare(strFilePath.GetRef(), pszFilePathNotToDelete) != Def_Equal)
                    {
                        WRITE_MRMMIN_INIT_TRACE_INFO_CHECK(strFilePath.GetRef(), S_OK);
                        DeleteFile(strFilePath.GetRef());
                        nNumFilesAttempted++;
                    }
                }
            }
        } while ((nNumFilesAttempted < nMaxFilesToDelete) && FindNextFile(hFindFile.get(), &FindFileData));
    }

    return S_OK;
}

HRESULT PriFileMerger::CreateUniqueTempDirectory(_In_ DWORD nUniqueTempDirLength, _Out_writes_(nUniqueTempDirLength) PWSTR pszUniqueTempDir)
{
    RETURN_LAST_ERROR_IF(GetTempPath(nUniqueTempDirLength, pszUniqueTempDir) == 0);

    UUID guid;
    RETURN_LAST_ERROR_IF(RPC_S_OK != UuidCreate(&guid));

    WCHAR* pwszUuid = nullptr;
    RETURN_LAST_ERROR_IF(RPC_S_OK != UuidToString(&guid, reinterpret_cast<RPC_WSTR*>(&pwszUuid)));

    wchar_t pszUuid[MAX_PATH] = {};
    HRESULT hr = StringCchPrintf(pszUuid, MAX_PATH, L"%s", (PCWSTR)pwszUuid);
    RpcStringFree(reinterpret_cast<RPC_WSTR*>(&pwszUuid));
    if (FAILED(hr))
    {
        return hr;
    }

    RETURN_IF_FAILED(StringCchCat(pszUniqueTempDir, nUniqueTempDirLength, pszUuid));
    if (!CreateDirectory(pszUniqueTempDir, nullptr) && (GetLastError() != ERROR_ALREADY_EXISTS))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}

HRESULT PriFileMerger::GetOrCreateSubDirectory(_In_ PCWSTR pszSubDirName, _Inout_ StringResult* pStrRootDir)
{
    StringResult strCreateDir;
    RETURN_IF_FAILED(strCreateDir.SetCopy(pStrRootDir->GetRef()));
    RETURN_IF_FAILED(strCreateDir.ConcatPathElement(pszSubDirName));
    if (!CreateDirectory(strCreateDir.GetRef(), nullptr) && (GetLastError() != ERROR_ALREADY_EXISTS))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    RETURN_IF_FAILED(pStrRootDir->ConcatPathElement(pszSubDirName));
    return S_OK;
}

HRESULT
PriFileMerger::MergeMap(
    _In_ const IResourceMapBase* pResMap,
    _In_ bool bIsPrimary,
    _In_ PriFileMerger::PriMergeFlags mergeFlags,
    _In_opt_ PCWSTR pRootFolder)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pResMap);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriInitialized);

    return PriMapMerger::MergeMap(pResMap, bIsPrimary, mergeFlags, pRootFolder, m_pPriFileBuilder->GetDescriptor());
}

HRESULT PriFileMerger::GetRelativeFolderFromPriFilePath(_In_ PCWSTR pPriFilePath, _Inout_ StringResult* pRelativeFolderPath)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPriFilePath) || (pRelativeFolderPath == nullptr));
    RETURN_IF_FAILED(PriFileBuilder::VerifyPriFilePath(pPriFilePath));

    RETURN_IF_FAILED(pRelativeFolderPath->SetRef(NULL));

    StringResult strPriFileName;
    StringResult strPriName;
    size_t cbLastSlash;
    size_t cbDot;
    RETURN_IF_FAILED(strPriFileName.SetRef(pPriFilePath));

    if (strPriFileName.TryFindLastOf(L'\\', &cbLastSlash))
    {
        RETURN_IF_FAILED(strPriName.SetCopy(strPriFileName.GetRef() + cbLastSlash + 1));
    }
    else
    {
        RETURN_IF_FAILED(strPriName.SetCopy(strPriFileName.GetRef()));
    }

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), !strPriName.TryFindLastOf(L'.', &cbDot));

    size_t cchLanguage = 0;
    PWSTR pszLanguage;
    RETURN_IF_FAILED(strPriName.GetWritableRef(&pszLanguage, &cchLanguage)); // pszLanguage: Windows.Search.en-US.pri"

    DEF_ASSERT(cbDot < cchLanguage);
    pszLanguage[cbDot] = L'\0'; // "Windows.Search.en-US"

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), !strPriName.TryFindLastOf(L'.', &cbDot));

    RETURN_IF_FAILED(pRelativeFolderPath->SetCopy(&pszLanguage[cbDot + 1]));
    return S_OK;
}

int PriFileMerger::CompareFuncStringResult(_In_ const StringResult** ppStringResult1, _In_ const StringResult** ppStringResult2)
{
    // Case insensitive comparison
    return DefString_ICompare((*ppStringResult1)->GetRef(), (*ppStringResult2)->GetRef());
}

bool PriFileMerger::HashFuncStringResult(_In_ const StringResult** ppStringResult1, _In_ INT* pHashOut)
{
    return SUCCEEDED(DefChecksum::ComputeStringChecksum(
        0,
        true, // case insensitive
        (*ppStringResult1)->GetRef(),
        (DefChecksum::Checksum*)pHashOut));
}

int PriFileMerger::CompareFuncPriFileInfoCollection(_In_ PriFileInfo** ppPriFileInfo1, _In_ PriFileInfo** ppPriFileInfo2)
{
    DEF_ASSERT(ppPriFileInfo1 != NULL);
    DEF_ASSERT(ppPriFileInfo2 != NULL);

    const PriFileInfo* pPriFileInfo1 = *ppPriFileInfo1;
    const PriFileInfo* pPriFileInfo2 = *ppPriFileInfo2;
    DEF_ASSERT(pPriFileInfo1 != NULL);
    DEF_ASSERT(pPriFileInfo2 != NULL);

    // Latest modified file needs to come first in this collection
    FILETIME ft1 = pPriFileInfo1->GetFileLastWriteTime();
    FILETIME ft2 = pPriFileInfo2->GetFileLastWriteTime();
    LONG nCompareVal = CompareFileTime(&ft1, &ft2);
    if (nCompareVal > 0)
    {
        return Def_Greater;
    }
    else if (nCompareVal < 0)
    {
        return Def_Less;
    }
    else
    {
        return Def_Equal;
    }
}

bool PriFileMerger::HashFuncPriFileInfoCollection(_In_ const PriFileInfo** ppPriFileInfo1, _In_ INT* pHashOut)
{
    DEF_CHECKSUM crcPriFile = 0;
    DEF_ASSERT(ppPriFileInfo1 != NULL);
    const PriFileInfo* pPriFileInfo1 = *ppPriFileInfo1;
    DEF_ASSERT(pPriFileInfo1 != NULL);
    DEF_ASSERT(pHashOut != NULL);

    if (SUCCEEDED(DefChecksum::ComputeStringChecksum(0, true, pPriFileInfo1->GetFileName()->GetRef(), &crcPriFile)))
    {
        *pHashOut = static_cast<INT>(crcPriFile);
        return true;
    }

    return false;
}

HRESULT PriMapMerger::MergeMap(
    _In_ const IResourceMapBase* pResMap,
    _In_ bool bIsPrimary,
    _In_ PriFileMerger::PriMergeFlags mergeFlags,
    _In_opt_ PCWSTR pRootFolder,
    _Inout_ PriSectionBuilder* pMergedPriSectionBuilder)
{
    RETURN_HR_IF(E_INVALIDARG, (pResMap == nullptr) || (pMergedPriSectionBuilder == nullptr));

    const IHierarchicalSchema* pHSchema = pResMap->GetSchema();
    HierarchicalSchemaSectionBuilder* pHSchemaBuilder = nullptr;
    ResourceMapSectionBuilder* pMergedMapBuilder = nullptr;
    DecisionInfoSectionBuilder* pMergedDecisions = nullptr;
    const UnifiedEnvironment* pMergedEnvironment = nullptr;
    const IDecisionInfo* pDecisionInfo = nullptr;
    NamedResourceResult namedResource;
    ResourceCandidateResult resCandidate;
    QualifierSetResult qualifierSet;
    int nQualifierSetIndex;
    int nMergedMapBuilderIndex;
    UINT16 nRemappedQualifierSetIndex;
    StringResult strResourceName;
    MrmEnvironment::ResourceValueType valueType;
    RemapUInt16 qualifierMap;
    RemapUInt16 qualifierSetMap;
    RemapUInt16 decisionMap;

    pMergedMapBuilder = pMergedPriSectionBuilder->GetResourceMapBuilder(pHSchema->GetSimpleId());
    if (pMergedMapBuilder == nullptr)
    {
        RETURN_IF_FAILED(pMergedPriSectionBuilder->AddResourceMapBuilder(
            pHSchema, bIsPrimary, PriBuildType::PriBuildFromScratch, &nMergedMapBuilderIndex));
        pMergedMapBuilder = pMergedPriSectionBuilder->GetResourceMapBuilder(nMergedMapBuilderIndex);

        DEF_ASSERT(pMergedMapBuilder != nullptr);
    }
    else
    {
        // Schema already exists, check for compatibility.
        pHSchemaBuilder = pMergedPriSectionBuilder->GetSchemaBuilder(pHSchema->GetSimpleId());
        RETURN_IF_FAILED(PriMapMerger::CheckIsCompatible(pHSchemaBuilder, pHSchema, mergeFlags));
    }

    pMergedDecisions = pMergedMapBuilder->GetDecisionInfo();
    pMergedEnvironment = pMergedMapBuilder->GetEnvironment();
    pDecisionInfo = pResMap->GetDecisionInfo();
    RETURN_IF_FAILED(pMergedDecisions->Merge(pDecisionInfo, &qualifierMap, &qualifierSetMap, &decisionMap));

    for (int nResItr = 0; nResItr < pResMap->GetNumResources(); nResItr++)
    {
        RETURN_IF_FAILED(pResMap->GetResourceByIndex(nResItr, &namedResource));

        RETURN_IF_FAILED(namedResource.GetResourceName(&strResourceName));
        for (int nResCandItr = 0; nResCandItr < namedResource.GetNumCandidates(); nResCandItr++)
        {
            RETURN_IF_FAILED(namedResource.GetCandidate(nResCandItr, &resCandidate));
            RETURN_IF_FAILED(resCandidate.GetQualifiers(&qualifierSet));
            RETURN_IF_FAILED(qualifierSet.GetIndex(&nQualifierSetIndex));
            RETURN_IF_FAILED(resCandidate.GetResourceValueType(&valueType));
            if (qualifierSetMap.TryGetMapping(static_cast<UINT16>(nQualifierSetIndex), &nRemappedQualifierSetIndex))
            {
                if (MrmEnvironment::IsBinaryResourceValueType(valueType))
                {
                    BlobResult brCandidateValue;
                    if (resCandidate.TryGetBlobValue(&brCandidateValue))
                    {
                        size_t cbBlobSize;
                        const BYTE* blob = static_cast<const BYTE*>(brCandidateValue.GetRef(&cbBlobSize));

                        DataItemOrchestrator* dataItems = pMergedPriSectionBuilder->GetDataItemOrchestrator();
                        IBuildInstanceReference* pBuildInstanceReference;
                        RETURN_IF_FAILED(dataItems->AddDataAndCreateInstanceReference(
                            blob, static_cast<UINT>(cbBlobSize), static_cast<int>(nRemappedQualifierSetIndex), &pBuildInstanceReference));

                        HRESULT hr = pMergedMapBuilder->AddCandidate(
                            strResourceName.GetRef(), valueType, pBuildInstanceReference, static_cast<int>(nRemappedQualifierSetIndex));
                        if ((hr == E_DEF_ALREADY_INITIALIZED) || (hr == HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY)))
                        {
                            // ignore failure for duplicate candidates and duplicate invalid entries
                            hr = S_OK;
                        }
                        RETURN_IF_FAILED(hr);
                    }
                }
                else
                {
                    StringResult strCandidateValue;
                    if (resCandidate.TryGetStringValue(&strCandidateValue))
                    {
                        StringResult strNewCandidateValue;
                        RETURN_IF_FAILED(strNewCandidateValue.SetRef(strCandidateValue.GetRef()));

                        if (MrmEnvironment::IsPathResourceValueType(valueType))
                        {
                            bool absolutePath;
                            RETURN_IF_FAILED(strCandidateValue.IsAbsolutePath(&absolutePath));

                            if ((pRootFolder != nullptr) && !absolutePath)
                            {
                                RETURN_IF_FAILED(strNewCandidateValue.SetCopy(pRootFolder));
                                RETURN_IF_FAILED(strNewCandidateValue.ConcatPathElement(strCandidateValue.GetRef()));
                            }

                            valueType = MrmEnvironment::ResourceValueType_Utf16Path;
                        }
                        else
                        {
                            valueType = MrmEnvironment::ResourceValueType_Utf16String;
                        }

                        HRESULT hr = pMergedMapBuilder->AddCandidateWithInternalString(
                            strResourceName.GetRef(),
                            valueType,
                            strNewCandidateValue.GetRef(),
                            static_cast<int>(nRemappedQualifierSetIndex));
                        if ((hr == E_DEF_ALREADY_INITIALIZED) || (hr == HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY)))
                        {
                            // Ignore failure for duplicate candidates and duplicate invalid entries.
                            hr = S_OK;
                        }
                        RETURN_IF_FAILED(hr);
                    }
                }
            }
        }
    }

    return S_OK;
}

// Method to check whether the two given schemas are compatible.
HRESULT PriMapMerger::CheckIsCompatible(
    _In_ const IHierarchicalSchema* pHSchema,
    _In_ const IHierarchicalSchema* pNewHSchema,
    _In_ PriFileMerger::PriMergeFlags mergeFlags)
{
    RETURN_HR_IF(E_INVALIDARG, (pHSchema == nullptr) || (pNewHSchema == nullptr));

    PCWSTR pSchemaUniqueName = NULL;
    PCWSTR pNewSchemaUniqueName = NULL;
    PCWSTR pSchemaDisplayName = NULL;
    PCWSTR pNewSchemaDisplayName = NULL;
    UINT16 nSchemaMajorVersion = 0;
    UINT16 nSchemaMinorVersion = 0;
    UINT16 nNewSchemaMajorVersion = 0;
    UINT16 nNewSchemaMinorVersion = 0;

    pSchemaDisplayName = pHSchema->GetSimpleId();
    pNewSchemaDisplayName = pNewHSchema->GetSimpleId();

    RETURN_HR_IF_EXPECTED(
        HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND), (nullptr == pSchemaDisplayName) || (nullptr == pNewSchemaDisplayName));

    RETURN_HR_IF_EXPECTED(HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND), !DefString_IEqual(pSchemaDisplayName, pNewSchemaDisplayName));

    pSchemaUniqueName = pHSchema->GetUniqueId();
    pNewSchemaUniqueName = pNewHSchema->GetUniqueId();

    RETURN_HR_IF_EXPECTED(HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND), (nullptr == pSchemaUniqueName) || (nullptr == pNewSchemaUniqueName));

    RETURN_HR_IF_EXPECTED(HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND), !DefString_IEqual(pSchemaUniqueName, pNewSchemaUniqueName));

    nSchemaMajorVersion = pHSchema->GetMajorVersion();
    nSchemaMinorVersion = pHSchema->GetMinorVersion();
    nNewSchemaMajorVersion = pNewHSchema->GetMajorVersion();
    nNewSchemaMinorVersion = pNewHSchema->GetMinorVersion();

    RETURN_HR_IF_EXPECTED(HRESULT_FROM_WIN32(ERROR_PRI_MERGE_VERSION_MISMATCH), nSchemaMajorVersion != nNewSchemaMajorVersion);

    RETURN_HR_IF_EXPECTED(
        HRESULT_FROM_WIN32(ERROR_PRI_MERGE_VERSION_MISMATCH),
        (nSchemaMinorVersion > nNewSchemaMinorVersion) && (!(mergeFlags & PriFileMerger::AcceptCompatiblePriorVersion)));

    RETURN_HR_IF_EXPECTED(
        HRESULT_FROM_WIN32(ERROR_PRI_MERGE_VERSION_MISMATCH),
        (nSchemaMinorVersion < nNewSchemaMinorVersion) && (mergeFlags & PriFileMerger::BlockCompatibleNewerVersion));

    return S_OK;
}

HRESULT PriFileMerger::InitWithPri(
    _In_reads_bytes_(cbPriData) const BYTE* pPriData,
    _In_ size_t cbPriData,
    _In_ PriFileMerger::PriMergeFlags mergeFlags,
    _In_opt_ PCWSTR pPackageRootFolder,
    _In_ CoreProfile* pProfile)
{
    RETURN_HR_IF(E_INVALIDARG, (pPriData == nullptr) || (cbPriData <= 0));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase != PriBuilderPhase::PriInitialized);

    AutoDeletePtr<StandalonePriFile> pPriFile;
    RETURN_IF_FAILED(StandalonePriFile::CreateInstance(0, pPriData, cbPriData, pProfile, &pPriFile));

    const IResourceMapBase* pResourceMap;
    RETURN_IF_FAILED(pPriFile->GetResourceMap(0, &pResourceMap));

    _Analysis_assume_(pResourceMap != nullptr);

    RETURN_IF_FAILED(MergeMap(pResourceMap, true, mergeFlags, pPackageRootFolder));

    return S_OK;
}

HRESULT PriFileMerger::ReleasePriBuilder(_Out_ PriFileBuilder** ppPriBuilder)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, ppPriBuilder);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION), m_priBuilderPhase < PriBuilderPhase::PriInitialized);

    *ppPriBuilder = m_pPriFileBuilder;
    m_pPriFileBuilder = NULL;

    m_priBuilderPhase = PriBuilderPhase::PriReleasedOwnership;
    return S_OK;
}

//
// PriFileInfo Implementation
//
HRESULT PriFileMerger::PriFileInfo::CreateInstance(
    _In_ PCWSTR pFileName,
    _In_ DWORD dwFileAttr,
    _In_ DWORD nFileSizeHigh,
    _In_ DWORD nFileSizeLow,
    _In_ FILETIME ftFileLastWriteTime,
    _Outptr_ PriFileMerger::PriFileInfo** result)
{
    *result = nullptr;

    AutoDeletePtr<PriFileInfo> pPriFileInfo = new PriFileInfo();
    RETURN_IF_NULL_ALLOC(pPriFileInfo);

    RETURN_IF_FAILED(pPriFileInfo->Init(pFileName, dwFileAttr, nFileSizeHigh, nFileSizeLow, ftFileLastWriteTime));

    *result = pPriFileInfo.Detach();

    return S_OK;
}

HRESULT PriFileMerger::PriFileInfo::Init(
    _In_ PCWSTR pFileName,
    _In_ DWORD dwFileAttr,
    _In_ DWORD nFileSizeHigh,
    _In_ DWORD nFileSizeLow,
    _In_ FILETIME ftFileLastWriteTime)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pFileName));

    RETURN_IF_FAILED(SetFileName(pFileName));

    SetFileAttributes(dwFileAttr);
    SetFileSizeHigh(nFileSizeHigh);
    SetFileSizeLow(nFileSizeLow);
    SetFileLastWriteTime(ftFileLastWriteTime);

    return S_OK;
}

PriFileMerger::PriFileInfo::PriFileInfo() : m_pStrFileName(nullptr), m_dwFileAttributes(0), m_nFileSizeHigh(0), m_nFileSizeLow(0)
{
    FILETIME ft = {0, 0};
    m_ftLastWriteTime = ft;
}

PriFileMerger::PriFileInfo::~PriFileInfo() { delete m_pStrFileName; }

HRESULT PriFileMerger::PriFileInfo::ComputeChecksum(_In_ PCWSTR pFilePath, _Inout_ DEF_CHECKSUM* pCrcChecksum)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pFilePath) || (pCrcChecksum == nullptr));

    WIN32_FIND_DATA FindFileData;
    wil::unique_hfind hFindFile(FindFirstFile(pFilePath, &FindFileData));
    RETURN_LAST_ERROR_IF(hFindFile.get() == INVALID_HANDLE_VALUE);
    RETURN_HR_IF(E_INVALIDARG, (BOOL)(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));

    AutoDeletePtr<PriFileInfo> pPriFileInfo;
    RETURN_IF_FAILED(PriFileInfo::CreateInstance(
        pFilePath,
        FindFileData.dwFileAttributes,
        FindFileData.nFileSizeHigh,
        FindFileData.nFileSizeLow,
        FindFileData.ftLastWriteTime,
        &pPriFileInfo));
    RETURN_IF_FAILED(pPriFileInfo->ComputeChecksum(pCrcChecksum));

    return S_OK;
}

HRESULT PriFileMerger::PriFileInfo::ComputeChecksum(_Inout_ DEF_CHECKSUM* pCrcChecksum) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pCrcChecksum);

    RETURN_IF_FAILED(DefChecksum::ComputeStringChecksum(*pCrcChecksum, true, m_pStrFileName->GetRef(), pCrcChecksum));

    *pCrcChecksum = DefChecksum::ComputeUInt32Checksum(*pCrcChecksum, m_nFileSizeHigh);
    *pCrcChecksum = DefChecksum::ComputeUInt32Checksum(*pCrcChecksum, m_nFileSizeLow);
    *pCrcChecksum = DefChecksum::ComputeUInt32Checksum(*pCrcChecksum, static_cast<UINT32>(m_ftLastWriteTime.dwLowDateTime));
    *pCrcChecksum = DefChecksum::ComputeUInt32Checksum(*pCrcChecksum, static_cast<UINT32>(m_ftLastWriteTime.dwHighDateTime));

    return S_OK;
}

HRESULT PriFileMerger::PriFileInfo::SetFileName(_In_ PCWSTR pFileName)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pFileName));

    if (!m_pStrFileName)
    {
        m_pStrFileName = new StringResult();
        RETURN_IF_NULL_ALLOC(m_pStrFileName);
    }
    RETURN_IF_FAILED(m_pStrFileName->SetCopy(pFileName));

    return S_OK;
}

bool PriFileMerger::PriFileInfo::SetFileAttributes(_In_ DWORD dwFileAttr)
{
    m_dwFileAttributes = dwFileAttr;
    return true;
}

bool PriFileMerger::PriFileInfo::SetFileSizeHigh(_In_ DWORD nFileSizeHigh)
{
    m_nFileSizeHigh = nFileSizeHigh;
    return true;
}

bool PriFileMerger::PriFileInfo::SetFileSizeLow(_In_ DWORD nFileSizeLow)
{
    m_nFileSizeLow = nFileSizeLow;
    return true;
}

bool PriFileMerger::PriFileInfo::SetFileLastWriteTime(_In_ FILETIME ftFileLastWriteTime)
{
    m_ftLastWriteTime = ftFileLastWriteTime;
    return true;
}

StringResult* PriFileMerger::PriFileInfo::GetFileName() const { return m_pStrFileName; }

DWORD
PriFileMerger::PriFileInfo::GetFileAttributes() const { return m_dwFileAttributes; }

DWORD
PriFileMerger::PriFileInfo::GetFileSizeHigh() const { return m_nFileSizeHigh; }

DWORD
PriFileMerger::PriFileInfo::GetFileSizeLow() const { return m_nFileSizeLow; }

FILETIME
PriFileMerger::PriFileInfo::GetFileLastWriteTime() const { return m_ftLastWriteTime; }

} // namespace Microsoft::Resources::Build
