// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"
#include <strsafe.h>

using namespace Microsoft::Resources::Build;

#include <mrm/build/ResourcePackMerge.h>

namespace Microsoft::Resources
{

HRESULT ResourcePackMerge::CreateInstance(_In_ CoreProfile* pProfile, _Outptr_ ResourcePackMerge** result)
{
    *result = nullptr;

    AutoDeletePtr<ResourcePackMerge> pRtrn = new (nothrow) ResourcePackMerge(pProfile);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init());

    *result = pRtrn.Detach();
    return S_OK;
}

ResourcePackMerge::ResourcePackMerge(_In_ CoreProfile* pProfile) :
    m_pEnvironment(nullptr),
    m_pPriFileManager(nullptr),
    m_pFileBuilder(nullptr),
    m_pProfile(pProfile),
    bFinalized(false),
    m_pFirstEntrySchema(nullptr),
    m_pPriFileList(nullptr),
    m_pAtoms(nullptr)
{
    // Constructor will receive the CoreProfile interface that is implemented by DEHClientProfile, which can give merged file path and additional information such as perf optimization.
}

HRESULT ResourcePackMerge::Init()
{
    RETURN_IF_FAILED(AtomPoolGroup::CreateInstance(&m_pAtoms));
    RETURN_IF_FAILED(UnifiedEnvironment::CreateInstance(m_pProfile, m_pAtoms, &m_pEnvironment));
    RETURN_IF_FAILED(PriFileManager::CreateInstance(m_pEnvironment, &m_pPriFileManager));
    RETURN_IF_FAILED(DynamicArray<PriFile*>::CreateInstance(5, &m_pPriFileList));
    return S_OK;
}

ResourcePackMerge::~ResourcePackMerge()
{
    delete m_pPriFileManager;
    delete m_pEnvironment;
    delete m_pAtoms;
    delete m_pFileBuilder;

    if (m_pPriFileList != nullptr)
    {
        for (int i = 0; i < m_pPriFileList->Count(); i++)
        {
            PriFile* pLocalPriFile;
            if (SUCCEEDED(m_pPriFileList->Get(i, &pLocalPriFile)))
            {
                delete pLocalPriFile;
            }
        }
        delete m_pPriFileList;
    }
}

HRESULT ResourcePackMerge::AddPriFile(_In_ PCWSTR pszPriFileName, _In_ PriFileMerger::PriMergeFlags priMergeFlags)
{
    if (IsFinalized())
    {
        return HRESULT_FROM_WIN32(ERROR_INVALID_OPERATION);
    }

    // Validate passed merge flag
    if (!ValidatePriFileMergeFlag(priMergeFlags))
    {
        return E_INVALIDARG;
    }

    // AddFile will detect if the same file is added
    ManagedFile* pManagedFile;
    RETURN_IF_FAILED(m_pPriFileManager->AddFile(pszPriFileName, nullptr, true, &pManagedFile));

    // The main PRI file always comes first and is resource complete, so we can use its schema in case the resource pack doesn't have one.
    AutoDeletePtr<PriFile> pPriFile;
    if (m_pPriFileList->Count() > 0)
    {
        PriFile* priFile;
        RETURN_IF_FAILED(m_pPriFileList->Get(0, &priFile));
        RETURN_IF_FAILED(PriFile::CreateInstance(pManagedFile, priFile, (const PriFile**)&pPriFile));
    }
    else
    {
        RETURN_IF_FAILED(PriFile::CreateInstance(pManagedFile, (const PriFile**)&pPriFile));
    }

    // It is possible that a windows 8 Pri file is in the "to be merged" location.
    // To avoid adding it to the list of files to merge, skip it here witout producing a failure.
    // Windows 8 Pri files are not eligible for merging, but we don't want to fail the merge
    // since we can't always guarantee that such a file is not present.
    BaseFile* pBaseFile;
    RETURN_IF_FAILED(pPriFile->GetBaseFile((const BaseFile**)&pBaseFile));
    DEF_ASSERT(pBaseFile != nullptr);
    _Analysis_assume_(pBaseFile != nullptr);

    auto pHeader = pBaseFile->GetFileHeader();
    DEF_ASSERT(pHeader != nullptr);
    _Analysis_assume_(pHeader != nullptr);

    if (pHeader->magic.ullMagic == gWin8PriFileMagic.ullMagic)
    {
        WRITE_MRMMIN_TRACE_WARNING_CHECK(L"Windows 8 PRI files do not support merging", pszPriFileName, S_OK);
        return S_OK; // Treat as a success case.
    }

    // Validate if Pri file format is allowed for resource pack merge
    if ((priMergeFlags & PriFileMerger::InPlaceMergeForAutoMerge) == 0)
    {
        // validate if it is called from DEH for StoreApp.
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_UNSUPPORTED_FILE_TYPE_FOR_MERGE), !ValidateInPlaceMergeEnabled(pPriFile));
    }

    RETURN_IF_FAILED(m_pPriFileList->Add(pPriFile));
    PriFile* localPriFile = pPriFile.Detach();

    // It expect single PRI file has single resource map
    if (localPriFile->GetNumResourceMaps() > 1)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
    }

    if (!m_pFileBuilder)
    {
        // The first added file SHOULD be main resource package that will define what schem and major version that decide
        // subsequent resource pack's compatibility.
        const IHierarchicalSchema* pHSchema;
        RETURN_IF_FAILED(localPriFile->GetPrimarySchema(&pHSchema));

        RETURN_IF_FAILED(PriFileBuilder::CreateInstance(
            pHSchema,
            m_pProfile,
            PriBuildType::PriBuildForDeploymentMerge, // resourcepack merge
            &m_pFileBuilder));

        UINT32 priFileFlags = 0;

        if ((priMergeFlags & PriFileMerger::InPlaceMergeForAutoMerge) != 0)
        {
            priFileFlags = MRMFILE_PRI_FLAGS_IS_AUTOMERGE_MERGE_RESULT;
        }
        else
        {
            priFileFlags = MRMFILE_PRI_FLAGS_IS_DEPLOYMENT_MERGE_RESULT;
        }

        RETURN_IF_FAILED(m_pFileBuilder->GetDescriptor()->SetPriFileFlags(priFileFlags));
    }

    FileInfo* pFielInfo = NULL;
    RETURN_IF_FAILED(AddFileToFileList(pszPriFileName, priMergeFlags, &pFielInfo));

    IResourceMapBase* pPrimaryResourceMap;
    RETURN_IF_FAILED((localPriFile->GetPrimaryResourceMap((const IResourceMapBase**)(&pPrimaryResourceMap))));

    // Set the package root that will return full path based candidate value for path type
    RETURN_IF_FAILED(pPrimaryResourceMap->SetPackageRootPath(pManagedFile->GetPackageRoot()));

    PriFileMerger::PriMergeFlags localMergeFlags = priMergeFlags;
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND), !ValidateResourceMap(pPrimaryResourceMap, priMergeFlags, &localMergeFlags));

    RETURN_IF_FAILED(AddResourceMap(pFielInfo, pPrimaryResourceMap, localMergeFlags));

    return S_OK;
}

bool ResourcePackMerge::IsFinalized() const { return bFinalized; }

HRESULT ResourcePackMerge::WriteToFile(_In_ PCWSTR pszOutputFile)
{
    // It is possible that there are no eligible files to merge. This should only happen
    // when the machine is corrupted, but when it does we want to make sure we fail gracefully.
    // Otherwise, if the missing file is loaded by explorer it will just chain crash.
    if (m_pFileBuilder == nullptr)
    {
        return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    }

    bFinalized = true;

    // Write to the file of the merged opearation.
    RETURN_IF_FAILED(m_pFileBuilder->WriteToFile(pszOutputFile));

    return S_OK;
}

HRESULT
ResourcePackMerge::AddFileToFileList(_In_ PCWSTR pszFilePath, _In_ PriFileMerger::PriMergeFlags priMergeFlags, _Out_ FileInfo** ppFileInfo)
{
    FolderInfo* pFolderInfo = NULL;
    *ppFileInfo = NULL;

    if (!m_pFileListBuilder)
    {
        RETURN_IF_FAILED(FileListBuilder::CreateInstance(m_pFileBuilder, FileListBuilder::BuildUtf16Only, &m_pFileListBuilder));

        PriSectionBuilder* pMergedPriSectionBuilder = m_pFileBuilder->GetDescriptor();
        RETURN_IF_FAILED(pMergedPriSectionBuilder->AddFileListSectionBuilder(m_pFileListBuilder));
    }

    RETURN_IF_FAILED(ValidateFilePath(pszFilePath));

    StringResult strResult;
    RETURN_IF_FAILED(strResult.SetCopy(pszFilePath));
    PWSTR pszLocalFilePath = const_cast<PWSTR>(strResult.GetRef());
    RETURN_IF_FAILED(AddRootFolder(pszLocalFilePath, &pszLocalFilePath, &pFolderInfo));

    StringResult strFolderOrFileName;
    bool bFolder;
    FileInfo* pFileInfo = nullptr;
    UINT16 fileFlag = 0;
    while (SUCCEEDED(GetFolderOrFileName(pszLocalFilePath, &strFolderOrFileName, &bFolder, &pszLocalFilePath)))
    {
        if (bFolder)
        {
            RETURN_IF_FAILED(pFolderInfo->GetOrAddSubfolder(strFolderOrFileName.GetRef(), &pFolderInfo));
        }
        else
        {
            RETURN_IF_FAILED(pFolderInfo->GetOrAddFile(strFolderOrFileName.GetRef(), &pFileInfo));

            if (priMergeFlags & PriFileMerger::SetPreLoad)
            {
                fileFlag |= INPLACE_MERGE_PRELOAD;
            }

            if (priMergeFlags & PriFileMerger::InPlaceMergeForAutoMerge)
            {
                fileFlag |= INPLACE_AUTOMERGE;
            }

            pFileInfo->SetFlag(fileFlag);

            *ppFileInfo = pFileInfo;
            break;
        }
    }

    return S_OK;
}

HRESULT ResourcePackMerge::AddRootFolder(_In_ PWSTR pszLocalFilePath, _Out_ PWSTR* ppszFilePathNext, _Out_ FolderInfo** ppFolderInfo)
{
    PWSTR pFilePathNoDriveLetter = const_cast<PWSTR>(wcschr(pszLocalFilePath, L':'));
    if (!pFilePathNoDriveLetter)
    {
        return E_INVALIDARG;
    }

    ++pFilePathNoDriveLetter; // "\Abc"
    if (*pFilePathNoDriveLetter == L'\\')
    {
        *pFilePathNoDriveLetter = L'\0';
        ++pFilePathNoDriveLetter;
    }
    else
    {
        DEF_ASSERT(FALSE);
        return E_INVALIDARG;
    }

    wchar_t p = *pFilePathNoDriveLetter; // p = "A"
    RETURN_IF_FAILED(m_pFileListBuilder->GetOrAddRootFolder(pszLocalFilePath, ppFolderInfo)); // "C:\" or "C:" or "\\?\C:\" or "\\?\C:"
    *pFilePathNoDriveLetter = p;

    *ppszFilePathNext = pFilePathNoDriveLetter;

    return S_OK;
}

HRESULT ResourcePackMerge::ValidateFilePath(_In_ PCWSTR pszFilePath) const
{
    // Get the file name and set the last backslash with null terminator so GetOrAddSubfolder will not
    // be confused with the file name.

    //  1. C:\resouces.pri
    //  2. C:\Folder\resources.pri
    //  3. \\?\C:\resources.pri
    //  4. \\?\C:\Folder\Resources.pri
    size_t strLen = wcslen(pszFilePath);
    if (strLen < 8 || // "C:\a.pri"
        (pszFilePath[0] == L'\\' && pszFilePath[1] == L'\\' && pszFilePath[2] == L'?' && pszFilePath[3] == L'\\' && // "\\?\C:\a.pri"
         strLen < 12))
    {

        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT
ResourcePackMerge::GetFolderOrFileName(
    _In_ PWSTR pszFilePath,
    _Inout_ StringResult* pStringResult,
    _Out_ bool* pbFolder,
    _Out_ PWSTR* ppszFilePathNext) const
{
    *pbFolder = true;

    while (*pszFilePath != L'\0')
    {
        if (*pszFilePath == L'\\')
        {
            pszFilePath++;
        }
        else
        {
            break;
        }
    }

    if (*pszFilePath == L'\0')
    {
        return E_INVALIDARG;
    }

    PWSTR pszNext = const_cast<PWSTR>(wcschr(pszFilePath, L'\\'));
    if (pszNext == NULL)
    {
        RETURN_IF_FAILED(pStringResult->SetRef(pszFilePath));
        pszNext = pszFilePath + wcslen(pszFilePath);
        *pbFolder = false;
    }
    else
    {
        *pszNext = L'\0';
        RETURN_IF_FAILED(pStringResult->SetCopy(pszFilePath));
        *pszNext = L'\\';
    }
    *ppszFilePathNext = pszNext;

    return S_OK;
}

HRESULT ResourcePackMerge::AddResourceMap(
    _In_ const FileInfo* pFileInfo,
    _In_ const IResourceMapBase* pResourceMapBase,
    _In_ PriFileMerger::PriMergeFlags localMergeFlags)
{
    ResourceMapSectionBuilder* pMergedMapBuilder = nullptr;
    DecisionInfoSectionBuilder* pMergedDecisions = nullptr;
    const UnifiedEnvironment* pMergedEnvironment = nullptr;
    NamedResourceResult namedResource;
    ResourceCandidateResult resCandidate;
    QualifierSetResult qualifierSet;
    int nMergedMapBuilderIndex;
    Atom resourceAtomName;
    StringResult strResourceName;
    StringResult strCandidateValue;
    StringResult strInstanceType;
    MrmEnvironment::ResourceValueType valueType;
    RemapUInt16 qualifierMap;
    RemapUInt16 qualifierSetMap;
    RemapUInt16 decisionMap;
    DynamicArray<int> qualifierSetIndexes;

    const IHierarchicalSchema* pHSchema = pResourceMapBase->GetSchema();
    PriSectionBuilder* pMergedPriSectionBuilder = m_pFileBuilder->GetDescriptor();
    pMergedMapBuilder = pMergedPriSectionBuilder->GetResourceMapBuilder(pHSchema->GetSimpleId());
    if (pMergedMapBuilder == nullptr)
    {
        RETURN_IF_FAILED(
            pMergedPriSectionBuilder->AddResourceMapBuilder(pHSchema, true, PriBuildType::PriBuildFromScratch, &nMergedMapBuilderIndex));

        pMergedMapBuilder = pMergedPriSectionBuilder->GetResourceMapBuilder(nMergedMapBuilderIndex);

        DEF_ASSERT(pMergedMapBuilder != nullptr);
    }

    pMergedDecisions = pMergedMapBuilder->GetDecisionInfo();
    pMergedEnvironment = pMergedMapBuilder->GetEnvironment();

    // Do NOT merge decision info as its qualifier set will be added during AddCandidate time

    for (int nResItr = 0; nResItr < pResourceMapBase->GetNumResources(); nResItr++)
    {
        RETURN_IF_FAILED(pResourceMapBase->GetResourceByIndex(nResItr, &namedResource));

        if ((localMergeFlags & PriFileMerger::AddItemToSchema) != 0)
        {
            // The added schema has higher minor version that means it has additonal item than existing one. we need to
            // add the item name to the schema section through string item name based AddCandidate that will addItem
            // to the schema
            RETURN_IF_FAILED(namedResource.GetResourceName(&strResourceName));
        }
        else
        {
            RETURN_IF_FAILED(namedResource.GetResourceName(&resourceAtomName));
        }

        for (int nResCandItr = 0; nResCandItr < namedResource.GetNumCandidates(); nResCandItr++)
        {
            RETURN_IF_FAILED(namedResource.GetCandidate(nResCandItr, &resCandidate));
            RETURN_IF_FAILED(resCandidate.GetQualifiers(&qualifierSet));

            int newQualifierSetIndex = -1;
            RETURN_IF_FAILED(GetOrAddQualifierSet(pMergedDecisions, &qualifierSet, &qualifierSetIndexes, &newQualifierSetIndex));

            DEF_ASSERT(newQualifierSetIndex != -1);

            RETURN_IF_FAILED(resCandidate.GetResourceValueType(&valueType));

            IBuildInstanceReference* pBuildInstanceReference;
            RETURN_IF_FAILED(ExternalFileStaticDataInstanceReference::CreateInstance(
                &resCandidate, pFileInfo, (ExternalFileStaticDataInstanceReference**)&pBuildInstanceReference));

            HRESULT hr;
            if ((localMergeFlags & PriFileMerger::AddItemToSchema) != 0)
            {
                hr = pMergedPriSectionBuilder->AddCandidateByReference(
                    nullptr, strResourceName.GetRef(), valueType, pBuildInstanceReference, newQualifierSetIndex);
            }
            else
            {
                hr = pMergedPriSectionBuilder->AddCandidateByReference(
                    nullptr, resourceAtomName.GetIndex(), valueType, pBuildInstanceReference, newQualifierSetIndex);
            }

            if (FAILED(hr))
            {
                delete pBuildInstanceReference;
                if ((hr == E_DEF_ALREADY_INITIALIZED) || ((hr == HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY)) &&
                                                          ((localMergeFlags & PriFileMerger::DropDuplicateCandidates) != 0)))
                {
                    // We accept the following errors and move on:
                    //    1. It has been initialized
                    //    2. There is already a dupe built in and the caller allows this scenario.
                }
                else
                {
                    return hr;
                }
            }
        }
    }

    return S_OK;
}

HRESULT ResourcePackMerge::GetOrAddQualifierSet(
    _In_ DecisionInfoSectionBuilder* pMergedDecisions,
    _In_ IQualifierSet* pQualifierSet,
    _Inout_ DynamicArray<int>* pQualifierSetIndexes,
    _Out_ int* pNewQualifierSetIndex)
{
    // Use the new qualifer set once that allow single call of GetOrAddQualifierSet per resource pack since resource pack has single qualiferSet
    // or support as many as different qualifers just in case.
    int oldQualifierSetIndex;
    RETURN_IF_FAILED(pQualifierSet->GetIndex(&oldQualifierSetIndex));

    if (oldQualifierSetIndex == 0)
    {
        *pNewQualifierSetIndex = 0; // neutral quaifier set
        return S_OK;
    }

    if (!pQualifierSetIndexes->TryGet(oldQualifierSetIndex, pNewQualifierSetIndex) || (*pNewQualifierSetIndex == 0))
    {
        RETURN_IF_FAILED(pMergedDecisions->GetOrAddQualifierSet(pQualifierSet, pNewQualifierSetIndex));

        if (oldQualifierSetIndex >= pQualifierSetIndexes->Count())
        {
            RETURN_IF_FAILED(pQualifierSetIndexes->SetExtent(oldQualifierSetIndex + 1));
        }

        RETURN_IF_FAILED(pQualifierSetIndexes->Set(oldQualifierSetIndex, *pNewQualifierSetIndex));
    }
    return S_OK;
}

bool ResourcePackMerge::ValidateResourceMap(
    _In_ const IResourceMapBase* pResourceMapBase,
    _In_ PriFileMerger::PriMergeFlags mergeFlags,
    _Inout_ PriFileMerger::PriMergeFlags* pUpdatedMergeFlags) const
{
    // Validate the added resource map whether it can be added or not by comparing the schema name or schema version
    if (m_pFirstEntrySchema)
    {
        const IHierarchicalSchema* pSchema = pResourceMapBase->GetSchema();
        if (FAILED(PriMapMerger::CheckIsCompatible(m_pFirstEntrySchema, pSchema, mergeFlags)))
        {
            return false;
        }

        UINT16 nSchemaMinorVersion = m_pFirstEntrySchema->GetMinorVersion();
        UINT16 nNewSchemaMinorVersion = pSchema->GetMinorVersion();

        if ((nSchemaMinorVersion < nNewSchemaMinorVersion))
        {
            *pUpdatedMergeFlags |= PriFileMerger::AddItemToSchema;
        }
    }
    else
    {
        m_pFirstEntrySchema = pResourceMapBase->GetSchema();
    }

    return true;
}

bool ResourcePackMerge::ValidatePriFileMergeFlag(_In_ PriFileMerger::PriMergeFlags mergeFlags) const
{
    // Validate the merge flag and make sure it is compatible previous merge flags
    return (((PriFileMerger::InPlaceMerge | PriFileMerger::InPlaceMergeForAutoMerge) & mergeFlags) != 0) &&
           ((PriFileMerger::FatMerge & mergeFlags) == 0);
}

bool ResourcePackMerge::ValidateInPlaceMergeEnabled(_In_ const PriFile* pPriFile) const
{
    if (pPriFile->GetAutoMergeEnabled())
    {
        // Auto merge enabled resource file can't be used for resource pack merge
        return false;
    }

    if (!pPriFile->GetIsDeploymentMergeable())
    {
        // The file is not suitable for resource pack merge
        return false;
    }

    return true;
}

} // namespace Microsoft::Resources
