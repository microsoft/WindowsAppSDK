// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"
#include "mrm/readers/MrmManagers.h"

using namespace Microsoft::Resources::Build;

namespace Microsoft::Resources
{

class UnifiedResourceView::UnifiedViewFileInfo : public DefObject
{
public:
    static HRESULT CreateInstance(
        _In_ UnifiedResourceView* pView,
        _In_ ManagedFile* pFile,
        _In_opt_ CoreProfile* pProfile,
        _Outptr_ UnifiedViewFileInfo** result)
    {
        *result = nullptr;
        RETURN_HR_IF(E_INVALIDARG, (pView == nullptr) || (pFile == nullptr));

        UnifiedViewFileInfo* pRtrn = new UnifiedViewFileInfo(pView, pFile, pProfile);
        RETURN_IF_NULL_ALLOC(pRtrn);

        *result = pRtrn;
        return S_OK;
    }

    ~UnifiedViewFileInfo()
    {
        m_pView = nullptr;

        // we own the PriFile, if it exists.
        delete m_pMyPri;
        m_pMyPri = nullptr;

        // file manager owns the ManagedFile
        // parent view owns the ManagedResourceMap
        m_pFile = nullptr;
        m_pPrimaryMap = nullptr;
    }

    UnifiedResourceView* GetView() const { return m_pView; }

    ManagedFile* GetManagedFile() const { return m_pFile; }

    HRESULT GetOriginalPri(_Out_ PriFile** result)
    {
        *result = nullptr;

        if ((m_pMyPri == nullptr) && (!m_bPriAttempted))
        {
            m_bPriAttempted = true;
            RETURN_IF_FAILED(PriFile::CreateInstance(m_pFile, m_pView, (const PriFile**)&m_pMyPri));
        }
        *result = m_pMyPri;

        return S_OK;
    }

    HRESULT GetPri(_Out_ PriFile** result) { return GetOriginalPri(result); }

    HRESULT GetPrimaryResourceMap(_Out_ ManagedResourceMap** result)
    {
        *result = nullptr;

        if ((m_pPrimaryMap == nullptr) && (!m_bPrimaryMapAttempted))
        {
            m_bPrimaryMapAttempted = true;

            PriFile* pPri;
            RETURN_IF_FAILED(GetPri(&pPri));

            if (pPri != nullptr)
            {
                const IResourceMapBase* pMap;
                RETURN_IF_FAILED(pPri->GetPrimaryResourceMap(&pMap));

                if (pMap != nullptr)
                {
                    RETURN_IF_FAILED(m_pView->GetOrAddManagedResourceMap(GetManagedFile(), pMap, &m_pPrimaryMap));
                }
            }
        }

        *result = m_pPrimaryMap;
        return S_OK;
    }

    HRESULT GetOrAddAllResourceMaps(_In_opt_ PCWSTR pPackageRootPath)
    {
        PriFile* pPri;
        RETURN_IF_FAILED(GetPri(&pPri));
        RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), pPri);

        int numAdded = 0;
        for (int i = 0; i < pPri->GetNumResourceMaps(); i++)
        {
            const IResourceMapBase* pMap = nullptr;
            if (SUCCEEDED(pPri->GetResourceMap(i, &pMap)))
            {
                if (SUCCEEDED(pMap->SetPackageRootPath(pPackageRootPath)))
                {
                    ManagedResourceMap* pMapOut = nullptr;
                    if (SUCCEEDED(m_pView->GetOrAddManagedResourceMap(GetManagedFile(), pMap, &pMapOut)))
                    {
                        DEF_ASSERT(pMapOut);
                        numAdded++;
                    }
                }
            }
        }

        return (numAdded > 0) ? S_OK : E_FAIL;
    }

    HRESULT ResolveFileFileList()
    {
        // Add referenced file in the FileList Section to the Managed file that needs to handle the fileIndex based
        // section retrieval from ResourceMap during runtime.
        PriFile* pPriFile;
        RETURN_IF_FAILED(GetPri(&pPriFile));
        RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), pPriFile);

        const FileFileList* pFileFileList;
        (void)pPriFile->GetFileList(0, &pFileFileList);

        if (pFileFileList)
        {
            RETURN_IF_FAILED(GetManagedFile()->ResolveFileFileList(pFileFileList));
        }
        // No FileList section is not a bug, which is normal for non-merged PRI file.

        return S_OK;
    }

protected:
    UnifiedViewFileInfo(_In_ UnifiedResourceView* pView, _In_ ManagedFile* pFile, _In_opt_ CoreProfile* pProfile) :
        m_pView(pView),
        m_pFile(pFile),
        m_pMyPri(nullptr),
        m_pPrimaryMap(nullptr),
        m_bPriAttempted(false),
        m_bPrimaryMapAttempted(false),
        m_pProfile(pProfile)
    {}

    UnifiedResourceView* m_pView;
    PriFile* m_pMyPri;
    ManagedFile* m_pFile;
    ManagedResourceMap* m_pPrimaryMap;

    bool m_bPriAttempted;
    bool m_bPrimaryMapAttempted;
    CoreProfile* m_pProfile;
};

HRESULT UnifiedResourceView::CreateInstance(_In_ CoreProfile* pProfile, _Outptr_ UnifiedResourceView** result)
{
    *result = nullptr;

    AutoDeletePtr<UnifiedResourceView> pRtrn = new UnifiedResourceView(pProfile);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init());

    *result = pRtrn.Detach();
    return S_OK;
}

UnifiedResourceView::UnifiedResourceView(_In_ CoreProfile* pProfile) :
    m_pFileManager(nullptr),
    m_pProfile(pProfile),
    m_pAtoms(nullptr),
    m_pEnvironment(nullptr),
    m_pDecisions(nullptr),
    m_pResolver(nullptr),
    m_pReferencedFiles(nullptr),
    m_pSchemas(nullptr),
    m_pMaps(nullptr),
    m_pAppFile(nullptr)
{}

HRESULT UnifiedResourceView::Init()
{
    RETURN_IF_FAILED(AtomPoolGroup::CreateInstance(8, &m_pAtoms));
    RETURN_IF_FAILED(UnifiedEnvironment::CreateInstance(m_pProfile, m_pAtoms, &m_pEnvironment));
    RETURN_IF_FAILED(UnifiedDecisionInfo::CreateInstance(m_pEnvironment, nullptr, nullptr, &m_pDecisions));
    RETURN_IF_FAILED(ProviderResolver::CreateInstance(m_pProfile, m_pEnvironment, m_pDecisions, &m_pResolver));
    RETURN_IF_FAILED(PriFileManager::CreateInstance(m_pEnvironment, &m_pFileManager));

    return S_OK;
}

UnifiedResourceView::~UnifiedResourceView()
{
    if (m_pMaps != nullptr)
    {
        for (int i = 0; i < m_pMaps->Count(); i++)
        {
            ManagedResourceMap* pMap;
            if (SUCCEEDED(m_pMaps->Get(i, &pMap)))
            {
                m_pMaps->Set(i, nullptr);
                delete pMap;
            }
        }
        delete m_pMaps;
    }

    if (m_pSchemas != nullptr)
    {
        for (int i = 0; i < m_pSchemas->Count(); i++)
        {
            ManagedSchema* pSchema;
            if (SUCCEEDED(m_pSchemas->Get(i, &pSchema)))
            {
                m_pSchemas->Set(i, nullptr);
                delete pSchema;
            }
        }
        delete m_pSchemas;
    }

    if (m_pReferencedFiles != nullptr)
    {
        for (int i = 0; i < m_pReferencedFiles->Count(); i++)
        {
            UnifiedViewFileInfo* pFile;
            if (SUCCEEDED(m_pReferencedFiles->Get(i, &pFile)))
            {
                m_pReferencedFiles->Set(i, nullptr);
                delete pFile;
            }
        }
        delete m_pReferencedFiles;
    }

    delete m_pResolver;
    delete m_pDecisions;
    delete m_pEnvironment;
    delete m_pAtoms;
    delete m_pFileManager;

    m_pResolver = nullptr;
    m_pDecisions = nullptr;
    m_pEnvironment = nullptr;
    m_pAtoms = nullptr;
    m_pFileManager = nullptr;
}

HRESULT UnifiedResourceView::GetPrimaryResourceMap(_Out_ const IResourceMapBase** result) const
{
    *result = nullptr;
    if (m_pAppFile)
    {
        ManagedResourceMap* map;
        RETURN_IF_FAILED(m_pAppFile->GetPrimaryResourceMap(&map));
        *result = map;
    }

    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND), *result);

    return S_OK;
}

HRESULT UnifiedResourceView::SetApplicationFile(_In_ PCWSTR pPath, _In_opt_ PCWSTR pRoot, _Out_ const ManagedResourceMap** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPath));
    RETURN_HR_IF(E_DEF_ALREADY_INITIALIZED, m_pAppFile != nullptr);

    int index = -1;
    const ManagedResourceMap* pPrimary;
    RETURN_IF_FAILED(GetOrAddReferencedFile(pPath, pRoot, &pPrimary, &index));

    RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND), pPrimary);

    RETURN_IF_FAILED(m_pReferencedFiles->Get(index, &m_pAppFile));

    *result = pPrimary;
    return S_OK;
}

HRESULT UnifiedResourceView::SetApplicationPriFile(_In_ PCWSTR pPath, _In_opt_ PCWSTR pRoot, _Out_ const PriFile** result)
{
    *result = nullptr;

    const ManagedResourceMap* map;
    RETURN_IF_FAILED(SetApplicationFile(pPath, pRoot, &map));

    RETURN_IF_FAILED(GetApplicationPriFile(result));

    return S_OK;
}

HRESULT UnifiedResourceView::GetApplicationFileInfo(
    _Inout_opt_ StringResult* pPriFilePathOut,
    _Inout_opt_ StringResult* pPackageRootOut,
    _Out_opt_ size_t* pSizeOut,
    _Out_opt_ UINT64* pDateOut) const
{
    RETURN_HR_IF_NULL(E_DEF_NOT_INITIALIZED, m_pAppFile);

    const ManagedFile* pFile = m_pAppFile->GetManagedFile();
    RETURN_HR_IF_NULL(E_DEF_NOT_INITIALIZED, pFile);

    if (pPriFilePathOut != nullptr)
    {
        RETURN_IF_FAILED(pPriFilePathOut->SetRef(pFile->GetPath()));
    }

    if (pPackageRootOut != nullptr)
    {
        RETURN_IF_FAILED(pPackageRootOut->SetRef(pFile->GetPackageRoot()));
    }

    if (pSizeOut != nullptr)
    {
        *pSizeOut = pFile->GetSizeInBytes();
    }

    if (pDateOut != nullptr)
    {
        *pDateOut = pFile->GetLastModifiedDate();
    }
    return S_OK;
}

HRESULT UnifiedResourceView::GetApplicationPriFile(_Out_ const PriFile** result) const
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_DEF_NOT_INITIALIZED, m_pAppFile);

    return m_pAppFile->GetPri((PriFile**)result);
}

HRESULT UnifiedResourceView::GetReferencedFileInfo(
    _In_ int index,
    _Inout_opt_ StringResult* pPriFilePathOut,
    _Inout_opt_ StringResult* pPackageRootOut,
    _Out_opt_ size_t* pSizeOut,
    _Out_opt_ UINT64* pDateOut) const
{
    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > GetNumReferencedFiles() - 1));
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), m_pReferencedFiles == nullptr);

    const UnifiedViewFileInfo* pFileInfo;
    RETURN_IF_FAILED(m_pReferencedFiles->Get(index, (UnifiedViewFileInfo**)&pFileInfo));

    const ManagedFile* pFile = pFileInfo->GetManagedFile();
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), pFile == nullptr);

    if (pPriFilePathOut != nullptr)
    {
        RETURN_IF_FAILED(pPriFilePathOut->SetRef(pFile->GetPath()));
    }

    if (pPackageRootOut != nullptr)
    {
        RETURN_IF_FAILED(pPackageRootOut->SetRef(pFile->GetPackageRoot()));
    }

    if (pSizeOut != nullptr)
    {
        *pSizeOut = pFile->GetSizeInBytes();
    }

    if (pDateOut != nullptr)
    {
        *pDateOut = pFile->GetLastModifiedDate();
    }
    return S_OK;
}

HRESULT UnifiedResourceView::GetOrAddReferencedFile(
    _In_ PCWSTR pPath,
    _In_opt_ PCWSTR pRoot,
    _Out_ const ManagedResourceMap** result,
    _Out_opt_ int* pFileIndexOut)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPath));

    NormalizedFilePath normalizedPath;
    RETURN_IF_FAILED(normalizedPath.Init(pPath));

    StringResult root;

    RETURN_IF_FAILED(ManagedFile::NormalizePackageRoot(normalizedPath.GetRef(), pRoot, &root));

    UnifiedViewFileInfo* pFileInfo = nullptr;

    HRESULT hr;
    if (!TryFindReferencedFile(normalizedPath.GetRef(), root.GetRef(), &pFileInfo, pFileIndexOut))
    {
        ManagedFile* pAppFile;
        hr = m_pFileManager->GetOrAddFile(&normalizedPath, root.GetRef(), LoadPriFlags::Preload, &pAppFile);
        if (pAppFile != nullptr)
        {
            AutoDeletePtr<UnifiedViewFileInfo> pMyFileInfo;
            RETURN_IF_FAILED(UnifiedViewFileInfo::CreateInstance(this, pAppFile, m_pProfile, &pMyFileInfo));

            RETURN_IF_FAILED(pMyFileInfo->ResolveFileFileList());
            RETURN_IF_FAILED(AddReferencedFile(pMyFileInfo, pFileIndexOut));

            pFileInfo = pMyFileInfo.Detach();
        }
        else
        {
            WRITE_MRMMIN_INIT_TRACE_ERROR_CHECK(normalizedPath.GetRef(), hr);
            return hr;
        }
    }

    hr = pFileInfo->GetOrAddAllResourceMaps(root.GetRef());
    if (FAILED(hr))
    {
        // AddAll only returns failure if it was completely
        // unable to load any schemas
        WRITE_MRMMIN_INIT_TRACE_ERROR(root.GetRef(), hr);
        return hr;
    }

    // Primary resource map is best effort. Don't report errors
    // if we can't load it.
    ManagedResourceMap* map;
    RETURN_IF_FAILED(pFileInfo->GetPrimaryResourceMap(&map));
    *result = map;

    return S_OK;
}

HRESULT UnifiedResourceView::LoadPriFiles(
    _In_ MRMPROFILE_PHASE mrmProfilePhase,
    _In_ DynamicArray<StringResult*>* pFilePathsCollection,
    _In_ LoadPriFlags flags,
    _Out_ DynamicArray<PriFileInfo*>** ppLoadedPriFilesInfo)
{
    *ppLoadedPriFilesInfo = nullptr;

    RETURN_HR_IF(E_INVALIDARG, pFilePathsCollection->Count() < 1);

    UINT uiNumPriFiles = pFilePathsCollection->Count();
    DynamicArray<PriFileInfo*>* pUnifiedViewFileInfoCollection;
    RETURN_IF_FAILED(DynamicArray<PriFileInfo*>::CreateInstance(uiNumPriFiles, &pUnifiedViewFileInfoCollection));

    auto cleanupOnFailure = wil::scope_exit([&] {
        for (UINT uItr = 0; uItr < pUnifiedViewFileInfoCollection->Count(); uItr++)
        {
            PriFileInfo* pPriFileInfo;
            if (SUCCEEDED(pUnifiedViewFileInfoCollection->Get(uItr, &pPriFileInfo)))
            {
                delete pPriFileInfo;
            }
        }

        delete pUnifiedViewFileInfoCollection;
        pUnifiedViewFileInfoCollection = nullptr;
    });

    HRESULT hr = S_OK;
    for (UINT uItr = 0; uItr < uiNumPriFiles; uItr++)
    {
        StringResult* pStrFilePath;
        RETURN_IF_FAILED(pFilePathsCollection->Get(uItr, &pStrFilePath));
        DEF_ASSERT(pStrFilePath && pStrFilePath->GetRef());

        NormalizedFilePath path;
        RETURN_IF_FAILED(path.Init(pStrFilePath->GetRef()));

        StringResult root;
        RETURN_IF_FAILED(ManagedFile::NormalizePackageRoot(path.GetRef(), nullptr, &root));

        UnifiedViewFileInfo* pUnifiedViewFileInfo = nullptr;
        int nFileIndexOut = -1;
        if (!TryFindReferencedFile(path.GetRef(), root.GetRef(), &pUnifiedViewFileInfo, &nFileIndexOut))
        {
            ManagedFile* pAppFile;
            hr = m_pFileManager->GetOrAddFile(&path, root.GetRef(), flags | LoadPriFlags::Preload, &pAppFile);
            if (!pAppFile)
            {
                // Empty resourceManager and dependency package can failed to map, which is just warning.
                WRITE_MRMMIN_TRACE_WARNING_CHECK(L"GetOrAddFile Failed", path.GetRef(), hr);
                return hr;
            }

            AutoDeletePtr<UnifiedViewFileInfo> autoUnifiedViewFileInfo;
            RETURN_IF_FAILED(UnifiedViewFileInfo::CreateInstance(this, pAppFile, m_pProfile, &autoUnifiedViewFileInfo));

            pUnifiedViewFileInfo = autoUnifiedViewFileInfo;

            if (mrmProfilePhase == MRMPROFILE_PHASE::EXPLICIT_LOAD_FROM_API)
            {
                PriFile* pPriFile;
                RETURN_IF_FAILED(pUnifiedViewFileInfo->GetOriginalPri(&pPriFile));
                RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), pPriFile);

                if ((pPriFile->GetIsDeploymentMergeable() || pPriFile->GetIsDeploymentMergeResult()) &&
                    (!m_pProfile->IsUnsafeLoadPriFileAllowed()))
                {
                    DEF_ASSERT(pPriFile->GetAutoMergeEnabled() == false);
                    return HRESULT_FROM_WIN32(ERROR_MRM_UNSUPPORTED_FILE_TYPE_FOR_LOAD_UNLOAD_PRI_FILE);
                    ;
                }
            }

            // Resolve Referenced file in the FileList section
            RETURN_IF_FAILED(pUnifiedViewFileInfo->ResolveFileFileList());

            nFileIndexOut = -1;
            AutoDeletePtr<PriFileInfo> pPriFileInfo;
            RETURN_IF_FAILED(PriFileInfo::CreateInstance(path.GetRef(), root.GetRef(), false, &pPriFileInfo));

            pPriFileInfo->SetUnifiedViewFileInfo(
                autoUnifiedViewFileInfo.Detach()); // pass the lifetime of pUnifiedViewFileInfo to the PriFileInfo
            pPriFileInfo->SetInputFilesIndex(uItr);
            pPriFileInfo->SetLoadedFileIndex(nFileIndexOut);
            RETURN_IF_FAILED(pUnifiedViewFileInfoCollection->Add(pPriFileInfo));

            pPriFileInfo.Detach();
        }
        else
        {
            RETURN_IF_FAILED(pUnifiedViewFileInfo->GetOrAddAllResourceMaps(root.GetRef()));
        }
        DEF_ASSERT(pUnifiedViewFileInfo != nullptr);
    }

    // Verify resource map name and other constraints for UnifiedViewFileInfos.
    for (UINT uItr = 0; uItr < pUnifiedViewFileInfoCollection->Count(); uItr++)
    {
        PriFileInfo* pPriFileInfo;
        RETURN_IF_FAILED(pUnifiedViewFileInfoCollection->Get(uItr, &pPriFileInfo));
        DEF_ASSERT(pPriFileInfo);

        UnifiedViewFileInfo* pUnifiedViewFileInfo = pPriFileInfo->GetUnifiedViewFileInfo();
        DEF_ASSERT(pUnifiedViewFileInfo);

        PriFile* pPriFile;
        hr = pUnifiedViewFileInfo->GetPri(&pPriFile);
        if (FAILED(hr) || pPriFile == nullptr)
        {
            hr = (SUCCEEDED(hr) ? E_ABORT : hr);
            WRITE_MRMMIN_INIT_TRACE_ERROR_CHECK(pPriFileInfo->GetPriFilePath(), hr);
            return hr;
        }
        // Check for a single resource map
        if (pPriFile->GetNumResourceMaps() > 1)
        {
            WRITE_MRMMIN_INIT_TRACE_ERROR_CHECK(pPriFileInfo->GetPriFilePath(), HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND));
            return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
        }
        // Check for a primary resource map
        const IResourceMapBase* pPrimaryResourceMap;
        hr = pPriFile->GetPrimaryResourceMap(&pPrimaryResourceMap);
        if ((FAILED(hr) || pPrimaryResourceMap == nullptr))
        {
            hr = (SUCCEEDED(hr) ? HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND) : hr);
            WRITE_MRMMIN_INIT_TRACE_ERROR_CHECK(pPriFileInfo->GetPriFilePath(), hr);
            return hr;
        }
        // Check for valid resource map name
        DEF_ASSERT(pPrimaryResourceMap != nullptr);
        PCWSTR pszResourceMapSimpleName = pPrimaryResourceMap->GetSchema()->GetSimpleId();
        if (!m_pProfile->IsLoadResourceMapAllowed(pszResourceMapSimpleName, mrmProfilePhase, nullptr))
        {
            return E_ACCESSDENIED;
        }
        // Check for compatibility of the new schema with already present schemas in this UnifiedResourceView
        if (m_pSchemas != nullptr)
        {
            bool bFoundCandidateSchema = false;
            bool bVerifiedSchemaCompatibility = (m_pSchemas->Count() == 0) ? true : false;
            const IHierarchicalSchema* pSchema = pPrimaryResourceMap->GetSchema();
            const IHierarchicalSchemaVersionInfo* pSchemaVersionInfo = pSchema->GetVersionInfo(0);
            for (int i = 0; i < m_pSchemas->Count(); i++)
            {
                ManagedSchema* pHaveManagedSchema;
                RETURN_IF_FAILED(m_pSchemas->Get(i, &pHaveManagedSchema));

                if (pHaveManagedSchema->GetCurrentSchema() == pSchema)
                {
                    // exact match
                    bFoundCandidateSchema = true;
                    bVerifiedSchemaCompatibility = true;
                    break;
                }

                if (DefString_ICompare(pSchema->GetSimpleId(), pHaveManagedSchema->GetSimpleId()) == Def_Equal)
                {
                    bFoundCandidateSchema = true;
                    // Some version of this schema is already present. Make sure new one about to be added is compatible.
                    if (DefString_ICompare(pSchema->GetUniqueId(), pHaveManagedSchema->GetUniqueId()) == Def_Equal)
                    {
                        if (pSchemaVersionInfo->GetMajorVersion() == pHaveManagedSchema->GetVersionInfo()->GetMajorVersion())
                        {
                            // compatible match
                            bVerifiedSchemaCompatibility = true;
                            break;
                        }
                        else
                        {
                            // Error out if same simple, unique names but incompatible versions
                            bVerifiedSchemaCompatibility = false;
                            break;
                        }
                    }
                    else
                    {
                        // Error out if same simple names but different unique names
                        bVerifiedSchemaCompatibility = false;
                        break;
                    }
                }
            }
            if (bFoundCandidateSchema && !bVerifiedSchemaCompatibility)
            {
                WRITE_MRMMIN_INIT_TRACE_ERROR(pSchema->GetUniqueId(), HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND));
                return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
            }
        }
    }

    // Load UnifiedViewFileInfos into UnifiedView if all are verified successfully above.
    for (UINT uItr = 0; uItr < pUnifiedViewFileInfoCollection->Count(); uItr++)
    {
        PriFileInfo* pPriFileInfo;
        RETURN_IF_FAILED(pUnifiedViewFileInfoCollection->Get(uItr, &pPriFileInfo));

        UnifiedViewFileInfo* pUnifiedViewFileInfo = pPriFileInfo->GetUnifiedViewFileInfo();
        DEF_ASSERT(pUnifiedViewFileInfo != nullptr);
        int nFileIndexOut = 0;
        RETURN_IF_FAILED(AddReferencedFile(pUnifiedViewFileInfo, &nFileIndexOut));

        pPriFileInfo->SetFileLoadedStatus(true);
        pPriFileInfo->SetLoadedFileIndex(nFileIndexOut);
        if ((mrmProfilePhase == MRMPROFILE_PHASE::PACKAGE_INIT) && !m_pAppFile)
        {
            RETURN_IF_FAILED(m_pReferencedFiles->Get(nFileIndexOut, &m_pAppFile));
            pPriFileInfo->SetAppFile();
        }

        RETURN_IF_FAILED(pUnifiedViewFileInfo->GetOrAddAllResourceMaps(pPriFileInfo->GetPriFileRoot()));

        ManagedResourceMap* resourceMap;
        RETURN_IF_FAILED(pUnifiedViewFileInfo->GetPrimaryResourceMap(&resourceMap));
        pPriFileInfo->SetManagedResourceMap(resourceMap);
    }

    cleanupOnFailure.release();
    *ppLoadedPriFilesInfo = pUnifiedViewFileInfoCollection;

    return S_OK;
}

HRESULT UnifiedResourceView::RemoveFileReference(_In_ PCWSTR pPriPath)
{
    UnifiedViewFileInfo* pFileInfo = nullptr;
    int index = -1;

    if (!TryFindReferencedFile(pPriPath, nullptr, &pFileInfo, &index))
    {
        // check if this file exist in the PriFileManager where resource pack will be in.
        ManagedFile* pManagedFile;
        RETURN_IF_FAILED(m_pFileManager->GetFile(pPriPath, &pManagedFile));

        // ResourcePack can not be unloaded exclusively
        PriFile* pPriFile;
        RETURN_IF_FAILED(PriFile::CreateInstance(pManagedFile, this, (const PriFile**)&pPriFile));

        HRESULT hr;
        if (pPriFile->GetIsDeploymentMergeable())
        {
            hr = HRESULT_FROM_WIN32(ERROR_MRM_UNSUPPORTED_FILE_TYPE_FOR_LOAD_UNLOAD_PRI_FILE);
        }
        else
        {
            // Auto merged file can be here, and keep old behavior for that.
            hr = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
        }
        delete pPriFile;
        return hr;
    }

    _Analysis_assume_(pFileInfo != nullptr);

    RETURN_IF_FAILED(RemoveFileResourceInfo(pFileInfo));

    ManagedFile* pFile = pFileInfo->GetManagedFile();
    RETURN_IF_FAILED(m_pFileManager->UnloadFile(pFile));
    RETURN_IF_FAILED(RemoveReferencedFile(pFileInfo));

    return S_OK;
}

HRESULT UnifiedResourceView::RemoveFileResourceInfo(_In_ UnifiedViewFileInfo* pFileInfo)
{
    ManagedFile* pFile = pFileInfo->GetManagedFile();

    bool cancel = false;

    RETURN_IF_FAILED(m_pDecisions->NoteFileUnloading(pFile, &cancel));

    for (int i = 0; (i < m_pSchemas->Count()) && (!cancel); i++)
    {
        ManagedSchema* pSchema;
        (void)m_pSchemas->Get(i, &pSchema);
        if (pSchema != nullptr)
        {
            RETURN_IF_FAILED(pSchema->NoteFileRemoving(pFile, &cancel));
        }
    }

    if (!cancel)
    {
        for (int i = 0; i < m_pMaps->Count(); i++)
        {
            ManagedResourceMap* pMap;
            (void)m_pMaps->Get(i, &pMap);
            if (pMap != nullptr)
            {
                RETURN_IF_FAILED(pMap->NoteFileRemoving(pFile, &cancel));
            }
        }
    }

    if (cancel)
    {
        return E_DEF_NOT_READY;
    }

    return S_OK;
}

int UnifiedResourceView::GetNumSchemas() const { return (m_pSchemas ? m_pSchemas->Count() : 0); }

HRESULT UnifiedResourceView::GetSchema(_In_ int index, _Out_ const IHierarchicalSchema** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > GetNumSchemas() - 1));

    return m_pSchemas->Get(index, (ManagedSchema**)result);
}

HRESULT UnifiedResourceView::GetPrimarySchema(_Out_ const IHierarchicalSchema** result) const
{
    *result = nullptr;
    ManagedResourceMap* pMap = nullptr;

    if (m_pAppFile != nullptr)
    {
        RETURN_IF_FAILED(m_pAppFile->GetPrimaryResourceMap(&pMap));
    }

    *result = (pMap ? pMap->GetManagedSchema() : nullptr);
    return S_OK;
}

HRESULT UnifiedResourceView::GetSchemaById(_In_ PCWSTR pSchemaId, _Out_ const IHierarchicalSchema** result) const
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pSchemaId));

    if (m_pSchemas == nullptr)
    {
        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    for (int i = 0; i < m_pSchemas->Count(); i++)
    {
        ManagedSchema* pSchema;
        (void)m_pSchemas->Get(i, &pSchema);
        if ((pSchema != nullptr) && (DefString_ICompare(pSchema->GetSimpleId(), pSchemaId) == Def_Equal))
        {
            *result = pSchema;
            return S_OK;
        }
    }
    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT
UnifiedResourceView::FindSchema(_In_ const HierarchicalSchemaReference* pRef, _Outptr_ const IHierarchicalSchema** ppSchemaOut) const
{
    *ppSchemaOut = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pRef);

    if (m_pSchemas != nullptr)
    {
        for (int i = 0; i < m_pSchemas->Count(); i++)
        {
            ManagedSchema* pSchema;
            (void)m_pSchemas->Get(i, &pSchema);
            if ((pSchema != nullptr) && pRef->CheckIsCompatible(pSchema))
            {
                *ppSchemaOut = pSchema;
                return S_OK;
            }
        }
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

int UnifiedResourceView::GetNumResourceMaps() const { return (m_pMaps ? m_pMaps->Count() : 0); }

HRESULT UnifiedResourceView::GetResourceMap(_In_ int index, _Out_ const IResourceMapBase** result) const
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > GetNumResourceMaps() - 1));

    ManagedResourceMap* map;
    RETURN_IF_FAILED(m_pMaps->Get(index, &map));
    *result = map;

    return S_OK;
}

HRESULT UnifiedResourceView::GetManagedResourceMap(_In_ int index, _Out_ const ManagedResourceMap** result) const
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > GetNumResourceMaps() - 1));

    ManagedResourceMap* map;
    RETURN_IF_FAILED(m_pMaps->Get(index, &map));
    *result = map;
    return S_OK;
}

HRESULT UnifiedResourceView::GetResourceMapById(_In_ PCWSTR pSchemaId, _Out_ const IResourceMapBase** result) const
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pSchemaId));

    if (m_pMaps == nullptr)
    {
        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    for (int i = 0; i < m_pMaps->Count(); i++)
    {
        ManagedResourceMap* pMap;
        (void)m_pMaps->Get(i, &pMap);

        const IHierarchicalSchema* pSchema = (pMap ? pMap->GetSchema() : nullptr);
        if ((pSchema != nullptr) && (DefString_ICompare(pSchema->GetSimpleId(), pSchemaId) == Def_Equal))
        {
            *result = pMap;
            return S_OK;
        }
    }
    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

bool UnifiedResourceView::TryFindResourceMap(_In_ const HierarchicalSchemaReference* pRef, _Outptr_opt_ const IResourceMapBase** ppMapOut)
    const
{
    if (ppMapOut != nullptr)
    {
        *ppMapOut = nullptr;
    }

    if (pRef == nullptr)
    {
        return false;
    }

    if (m_pMaps != nullptr)
    {
        for (int i = 0; i < m_pMaps->Count(); i++)
        {
            ManagedResourceMap* pMap;
            (void)m_pMaps->Get(i, &pMap);
            const IHierarchicalSchema* pSchema = (pMap ? pMap->GetSchema() : nullptr);
            if ((pSchema != nullptr) && pRef->CheckIsCompatible(pSchema))
            {
                if (ppMapOut != nullptr)
                {
                    *ppMapOut = pMap;
                }
                return true;
            }
        }
    }

    return false;
}

bool UnifiedResourceView::TryFindReferencedFile(
    _In_ PCWSTR pPath,
    _In_opt_ PCWSTR pPackageRoot,
    _Outptr_opt_result_maybenull_ UnifiedViewFileInfo** ppFileInfoOut,
    _Out_opt_ int* pFileIndexOut)
{
    UnifiedViewFileInfo* pFileInfo = nullptr;

    if (ppFileInfoOut != nullptr)
    {
        *ppFileInfoOut = nullptr;
    }

    if (pFileIndexOut != nullptr)
    {
        *pFileIndexOut = -1;
    }

    if (m_pReferencedFiles != nullptr)
    {
        for (int i = 0; i < m_pReferencedFiles->Count(); i++)
        {
            (void)m_pReferencedFiles->Get(i, &pFileInfo);
            if (pFileInfo != nullptr)
            {
                if (DefString_ICompare(pPath, pFileInfo->GetManagedFile()->GetPath()) == Def_Equal)
                {
                    if ((pPackageRoot == nullptr) ||
                        (DefString_ICompare(pPackageRoot, pFileInfo->GetManagedFile()->GetPackageRoot()) == Def_Equal))
                    {
                        // found a match!
                        if (ppFileInfoOut != nullptr)
                        {
                            *ppFileInfoOut = pFileInfo;
                        }

                        if (pFileIndexOut != nullptr)
                        {
                            *pFileIndexOut = i;
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

HRESULT UnifiedResourceView::AddReferencedFile(_In_ UnifiedViewFileInfo* pFileInfo, _Out_opt_ int* pFileIndexOut)
{
    if (m_pReferencedFiles == nullptr)
    {
        RETURN_IF_FAILED(DynamicArray<UnifiedViewFileInfo*>::CreateInstance(2, &m_pReferencedFiles));
    }
    return m_pReferencedFiles->Add(pFileInfo, pFileIndexOut);
}

HRESULT UnifiedResourceView::RemoveReferencedFile(_In_ UnifiedViewFileInfo* pFileInfo)
{
    if (m_pReferencedFiles != nullptr)
    {
        for (int i = 0; i < m_pReferencedFiles->Count(); i++)
        {
            UnifiedViewFileInfo* fileInfo;
            (void)m_pReferencedFiles->Get(i, &fileInfo);
            if (fileInfo == pFileInfo)
            {
                if (SUCCEEDED(m_pReferencedFiles->Delete(i)))
                {
                    delete pFileInfo;
                    return S_OK;
                }
            }
        }
    }

    return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
}

HRESULT UnifiedResourceView::GetOrAddManagedSchema(
    _In_ const ManagedFile* pFile,
    _In_ const IHierarchicalSchema* pSchema,
    _Outptr_opt_result_maybenull_ ManagedSchema** ppSchemaOut)
{
    if (m_pSchemas != nullptr)
    {
        const IHierarchicalSchemaVersionInfo* pWantVersion = pSchema->GetVersionInfo(0);

        for (int i = 0; i < m_pSchemas->Count(); i++)
        {
            ManagedSchema* pHaveSchema;
            (void)m_pSchemas->Get(i, &pHaveSchema);
            if (pHaveSchema)
            {
                if (pHaveSchema->GetCurrentSchema() == pSchema)
                {
                    // exact match!
                    if (ppSchemaOut != nullptr)
                    {
                        *ppSchemaOut = pHaveSchema;
                    }

                    return S_OK;
                }
                else
                {
                    bool bExists = CheckHierarchicalSchemaVersionIsCompatible(pHaveSchema, pWantVersion);
                    if (!bExists)
                    {
                        bExists = CheckHierarchicalSchemaVersionIsCompatible(pSchema, pHaveSchema->GetVersionInfo());
                    }

                    if (bExists)
                    {
                        // Some version of this schema is already present. Make
                        // sure the existing managed schema knows about this
                        // file.
                        if (ppSchemaOut != nullptr)
                        {
                            *ppSchemaOut = pHaveSchema;
                        }
                        return pHaveSchema->NoteFileAdded(pFile, pSchema);
                    }
                }
            }
        }
    }

    // If we get here, this is a new schema
    if (m_pSchemas == nullptr)
    {
        RETURN_IF_FAILED(DynamicArray<ManagedSchema*>::CreateInstance(2, &m_pSchemas));
    }

    ManagedSchema* pNewSchema;
    RETURN_IF_FAILED(ManagedSchema::CreateInstance(pFile, pSchema, &pNewSchema));
    RETURN_IF_FAILED(m_pSchemas->Add(pNewSchema));

    if (ppSchemaOut != nullptr)
    {
        *ppSchemaOut = pNewSchema;
    }
    return S_OK;
}

HRESULT UnifiedResourceView::GetOrAddManagedResourceMap(
    _In_ const ManagedFile* pFile,
    _In_ const IResourceMapBase* pMap,
    _Outptr_opt_result_maybenull_ ManagedResourceMap** ppMapOut)
{
    ManagedSchema* pSchema = nullptr;

    if (ppMapOut != nullptr)
    {
        *ppMapOut = nullptr;
    }

    HRESULT hr = GetOrAddManagedSchema(pFile, pMap->GetOriginalSchema(), &pSchema);
    if (FAILED(hr))
    {
        WRITE_MRMMIN_INIT_TRACE_ERROR(pMap->GetOriginalSchema()->GetSimpleId(), hr);
        return hr;
    }

    if (m_pMaps != nullptr)
    {
        for (int i = 0; i < m_pMaps->Count(); i++)
        {
            ManagedResourceMap* pHaveMap;
            (void)m_pMaps->Get(i, &pHaveMap);

            if (pHaveMap != nullptr)
            {
                if (pHaveMap->GetCurrentResourceMap() == pMap)
                {
                    // exact match
                    if (ppMapOut != nullptr)
                    {
                        *ppMapOut = pHaveMap;
                    }
                    return S_OK;
                }

                if (pHaveMap->GetManagedSchema() == pSchema)
                {
                    // This is a new map for an existing schema.
                    // Just add it to the existing managed map and return.
                    if (ppMapOut != nullptr)
                    {
                        *ppMapOut = pHaveMap;
                    }
                    return pHaveMap->NoteFileAdded(pFile, pMap);
                }
            }
        }
    }

    // If we get here, this is a map for a new resource map
    if (m_pMaps == nullptr)
    {
        RETURN_IF_FAILED(DynamicArray<ManagedResourceMap*>::CreateInstance(2, &m_pMaps));
    }

    ManagedResourceMap* pNewMap;
    RETURN_IF_FAILED(ManagedResourceMap::CreateInstance(pFile, pMap, pSchema, m_pDecisions, this, &pNewMap));
    RETURN_IF_FAILED(m_pMaps->Add(pNewMap));

    if (ppMapOut != nullptr)
    {
        *ppMapOut = pNewMap;
    }
    return S_OK;
}

bool UnifiedResourceView::TryGetReverseFileMap(_Outptr_opt_ const ReverseFileMap** ppMapOut) const
{
    const PriFile* pPriFile;
    (void)GetApplicationPriFile(&pPriFile);
    if (pPriFile)
    {
        return pPriFile->TryGetReverseFileMap(ppMapOut);
    }
    return false;
}

HRESULT UnifiedResourceView::PriFileInfo::CreateInstance(
    _In_ PCWSTR pszPriFilePath,
    _In_ PCWSTR pszPriFileRoot,
    _In_ bool bFileLoaded,
    _Outptr_ UnifiedResourceView::PriFileInfo** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pszPriFilePath));

    PriFileInfo* pPriFileInfo = new PriFileInfo(pszPriFilePath, pszPriFileRoot, bFileLoaded);
    RETURN_IF_NULL_ALLOC(pPriFileInfo);

    *result = pPriFileInfo;

    return S_OK;
}

UnifiedResourceView::PriFileInfo::PriFileInfo(_In_ PCWSTR pszPriFilePath, _In_ PCWSTR pszPriFileRoot, _In_ bool bFileLoaded) :
    m_pUnifiedViewFileInfo(nullptr),
    m_bFileLoaded(bFileLoaded),
    m_bIsAppFile(false),
    m_nLoadedFileIndex(-1),
    m_uInputFilesIndex(-1),
    m_pManagedResourceMap(nullptr)
{
    m_strPriFilePath.SetCopy(pszPriFilePath);
    m_strPriFileRoot.SetCopy(pszPriFileRoot);
}

UnifiedResourceView::PriFileInfo::~PriFileInfo()
{
    if (!m_bFileLoaded)
    {
        delete m_pUnifiedViewFileInfo;
        m_pUnifiedViewFileInfo = nullptr;
    }
}

void UnifiedResourceView::PriFileInfo::SetUnifiedViewFileInfo(_In_ UnifiedResourceView::UnifiedViewFileInfo* pUnifiedViewFileInfo)
{
    m_pUnifiedViewFileInfo = pUnifiedViewFileInfo;
}

void UnifiedResourceView::PriFileInfo::SetFileLoadedStatus(_In_ bool bFileLoaded) { m_bFileLoaded = bFileLoaded; }

void UnifiedResourceView::PriFileInfo::SetLoadedFileIndex(_In_ int nLoadedFileIndex) { m_nLoadedFileIndex = nLoadedFileIndex; }

void UnifiedResourceView::PriFileInfo::SetInputFilesIndex(_In_ UINT uInputFilesIndex) { m_uInputFilesIndex = uInputFilesIndex; }

void UnifiedResourceView::PriFileInfo::SetManagedResourceMap(_In_ const ManagedResourceMap* pManagedResourceMap)
{
    m_pManagedResourceMap = pManagedResourceMap;
}

void UnifiedResourceView::PriFileInfo::SetAppFile() { m_bIsAppFile = true; }

UnifiedResourceView::UnifiedViewFileInfo* UnifiedResourceView::PriFileInfo::GetUnifiedViewFileInfo() const
{
    return m_pUnifiedViewFileInfo;
}

PCWSTR UnifiedResourceView::PriFileInfo::GetPriFilePath() const { return m_strPriFilePath.GetRef(); }

PCWSTR UnifiedResourceView::PriFileInfo::GetPriFileRoot() const { return m_strPriFileRoot.GetRef(); }

bool UnifiedResourceView::PriFileInfo::GetFileLoaded() const { return m_bFileLoaded; }

int UnifiedResourceView::PriFileInfo::GetLoadedFileIndex() const { return m_nLoadedFileIndex; }

UINT UnifiedResourceView::PriFileInfo::GetInputFilesIndex() const { return m_uInputFilesIndex; }

const ManagedResourceMap* UnifiedResourceView::PriFileInfo::GetManagedResourceMap() const { return m_pManagedResourceMap; }

bool UnifiedResourceView::PriFileInfo::GetAppFile() const { return m_bIsAppFile; }

} // namespace Microsoft::Resources
