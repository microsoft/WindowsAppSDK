// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "stdafx.h"

namespace Microsoft::Resources
{

HRESULT PriFileManager::CreateInstance(_In_ UnifiedEnvironment* pEnvironment, _Outptr_ PriFileManager** result)
{
    *result = nullptr;

    AutoDeletePtr<PriFileManager> pRtrn = new PriFileManager();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pEnvironment));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT PriFileManager::GetFile(_In_ int index, _Out_ ManagedFile** result) const
{
    *result = nullptr;

    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(index, &finfo))
    {
        *result = finfo.pFile;
        return S_OK;
    }
    return E_INVALIDARG;
}

HRESULT PriFileManager::GetFile(_In_ const NormalizedFilePath* pNormalizedPath, _Out_ ManagedFile** result) const
{
    *result = nullptr;

    ManagedFile* pRtrn = nullptr;
    // See if we already have the file
    for (int i = 0; i < m_pFiles->Count(); i++)
    {
        GetFile(i, &pRtrn);
        if ((pRtrn != nullptr) && (DefString_ICompare(pNormalizedPath->GetRef(), pRtrn->GetPath()) == Def_Equal))
        {
            *result = pRtrn;
            return S_OK;
        }
    }

    return E_INVALIDARG;
}

HRESULT PriFileManager::GetFile(_In_ PCWSTR pFilePath, _Out_ ManagedFile** result) const
{
    *result = nullptr;

    NormalizedFilePath normalizedPath;
    RETURN_IF_FAILED(normalizedPath.Init(pFilePath));

    RETURN_IF_FAILED(GetFile(&normalizedPath, result));

    return S_OK;
}

HRESULT PriFileManager::GetOrAddFile(
    _In_ const NormalizedFilePath* pNormalizedPath,
    _In_opt_ PCWSTR pPackageRoot,
    _In_ LoadPriFlags flags,
    _Out_ ManagedFile** result) const
{
    *result = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, pNormalizedPath);
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pNormalizedPath->GetRef()));

    FileManagerFileInfo finfo;
    StringResult rootPath;
    ManagedFile* pRtrn = nullptr;

    RETURN_IF_FAILED(ManagedFile::NormalizePackageRoot(pNormalizedPath->GetRef(), pPackageRoot, &rootPath));

    // See if we already have the file
    for (int i = 0; i < m_pFiles->Count(); i++)
    {
        if (m_pFiles->TryGet(i, &finfo))
        {
            pRtrn = finfo.pFile;
        }
        else
        {
            pRtrn = nullptr;
        }
        if ((pRtrn != nullptr) && (DefString_ICompare(pNormalizedPath->GetRef(), pRtrn->GetPath()) == Def_Equal))
        {
            RETURN_IF_FAILED(pRtrn->SetPackageRoot(rootPath.GetRef()));

            if ((flags & LoadPriFlags::Preload) == LoadPriFlags::Preload)
            {
                RETURN_IF_FAILED(pRtrn->Load());
            }
            *result = pRtrn;
            return S_OK;
        }
    }

    // not found - create a new file
    int index = -1;
    RETURN_IF_FAILED_WITH_EXPECTED(
        ManagedFile::CreateInstance(this, index, pNormalizedPath, rootPath.GetRef(), flags, &pRtrn),
        HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND),
        HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND));

    finfo.pFile = pRtrn;

    HRESULT hr = m_pFiles->Add(finfo, &index);
    if (FAILED(hr))
    {
        delete pRtrn;
        return hr;
    }

    pRtrn->SetGlobalIndex(index);
    *result = pRtrn;

    return S_OK;
}

HRESULT
PriFileManager::GetOrAddFile(_In_ PCWSTR pPath, _In_opt_ PCWSTR pPackageRoot, _In_ LoadPriFlags flags, _Out_ ManagedFile** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPath));

    NormalizedFilePath normalizedPath;
    RETURN_IF_FAILED(normalizedPath.Init(pPath));

    RETURN_IF_FAILED(GetOrAddFile(&normalizedPath, pPackageRoot, flags, result));

    return S_OK;
}

HRESULT PriFileManager::AddFile(
    _In_ const NormalizedFilePath* pNormalizedPath,
    _In_opt_ PCWSTR pPackageRoot,
    _In_ bool fPreload,
    _Out_ ManagedFile** result)
{
    *result = nullptr;

    RETURN_HR_IF_NULL(E_INVALIDARG, pNormalizedPath);
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pNormalizedPath->GetRef()));

    FileManagerFileInfo finfo;
    StringResult rootPath;
    ManagedFile* pRtrn = nullptr;

    RETURN_IF_FAILED(ManagedFile::NormalizePackageRoot(pNormalizedPath->GetRef(), pPackageRoot, &rootPath));

    // See if we already have the file
    for (int i = 0; i < m_pFiles->Count(); i++)
    {
        if (m_pFiles->TryGet(i, &finfo))
        {
            pRtrn = finfo.pFile;
        }
        else
        {
            pRtrn = nullptr;
        }
        if ((pRtrn != nullptr) && (DefString_ICompare(pNormalizedPath->GetRef(), pRtrn->GetPath()) == Def_Equal))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
        }
    }

    // not found - create a new file
    int index = -1;
    RETURN_IF_FAILED(ManagedFile::CreateInstance(
        this, index, pNormalizedPath, rootPath.GetRef(), fPreload ? LoadPriFlags::Preload : LoadPriFlags::Default, &pRtrn));

    finfo.pFile = pRtrn;

    HRESULT hr = m_pFiles->Add(finfo, &index);
    if (FAILED(hr))
    {
        delete pRtrn;
        return hr;
    }
    pRtrn->SetGlobalIndex(index);
    *result = pRtrn;

    return S_OK;
}

HRESULT PriFileManager::AddFile(_In_ PCWSTR pPath, _In_opt_ PCWSTR pPackageRoot, _In_ bool fPreload, _Out_ ManagedFile** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPath));

    NormalizedFilePath normalizedPath;
    RETURN_IF_FAILED(normalizedPath.Init(pPath));

    RETURN_IF_FAILED(AddFile(&normalizedPath, pPackageRoot, fPreload, result));

    return S_OK;
}

HRESULT PriFileManager::InsertFile(
    _In_ int newIndex,
    _In_ PCWSTR pPath,
    _In_opt_ PCWSTR pPackageRoot,
    _In_ bool fPreload,
    _Out_ ManagedFile** result)
{
    *result = nullptr;

    // Create ManagedFile before adjusting internal structure of m_pFiles so we don't have to roll anything back if it fails.
    AutoDeletePtr<ManagedFile> pRtrn;
    RETURN_IF_FAILED(
        ManagedFile::CreateInstance(this, newIndex, pPath, pPackageRoot, fPreload ? LoadPriFlags::Preload : LoadPriFlags::Default, &pRtrn));

    FileManagerFileInfo finfo;
    finfo.pFile = pRtrn;
    // Insert move all contents to
    RETURN_IF_FAILED(m_pFiles->Insert(finfo, pRtrn->GetGlobalIndex()));

    ManagedFile* mf = pRtrn.Detach();

    // Adjust ManagedFile global index by its new index in the m_pFiles
    for (int i = newIndex + 1; i < m_pFiles->Count(); i++)
    {
        ManagedFile* pManagedFile;
        RETURN_IF_FAILED(GetFile(i, &pManagedFile));

        pManagedFile->SetGlobalIndex(i);
    }

    *result = mf;
    return S_OK;
}

HRESULT PriFileManager::LoadFile(_In_ const ManagedFile* pFile)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pFile);
    RETURN_HR_IF(E_MRM_PRI_MANAGER_MISMATCH, pFile->GetFileManager() != this);

    FileManagerFileInfo finfo;
    if ((!m_pFiles->TryGet(pFile->GetGlobalIndex(), &finfo)) || (finfo.pFile != pFile))
    {
        return E_MRM_PRI_MANAGER_MISMATCH;
    }

    return finfo.pFile->Load();
}

HRESULT PriFileManager::UnloadFile(_In_ const ManagedFile* pFile)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pFile);
    RETURN_HR_IF(E_MRM_PRI_MANAGER_MISMATCH, pFile->GetFileManager() != this);

    FileManagerFileInfo finfo;
    if ((!m_pFiles->TryGet(pFile->GetGlobalIndex(), &finfo)) || (finfo.pFile != pFile))
    {
        return E_MRM_PRI_MANAGER_MISMATCH;
    }

    return finfo.pFile->Unload();
}

HRESULT PriFileManager::RemoveFile(_In_ const ManagedFile* pFile)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pFile);
    RETURN_HR_IF(E_MRM_PRI_MANAGER_MISMATCH, pFile->GetFileManager() != this);

    FileManagerFileInfo finfo;
    if ((!m_pFiles->TryGet(pFile->GetGlobalIndex(), &finfo)) || (finfo.pFile != pFile))
    {
        return E_MRM_PRI_MANAGER_MISMATCH;
    }

    FileManagerFileInfo finfoNull = {};
    RETURN_IF_FAILED(m_pFiles->Set(pFile->GetGlobalIndex(), finfoNull));

    delete finfo.pFile;
    return S_OK;
}

HRESULT PriFileManager::SetDefaultFileFlags(_In_ UINT32 flags)
{
    RETURN_HR_IF(E_INVALIDARG, (flags & ~BaseFile::ValidFlags) != 0);

    m_defaultFileFlags = flags;
    return S_OK;
}

HRESULT PriFileManager::GetSection(
    _In_ const ISchemaCollection* pSchemaCollection,
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ const IFileSection** result) const
{
    *result = nullptr;

    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->GetSection(pSchemaCollection, 0, sectionIndex, result);
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

_Success_(return == true)
const bool PriFileManager::TryGetSectionIndexByType(
    _In_ const DEFFILE_SECTION_TYPEID& sectionType,
    _In_ int fileIndex,
    _In_ int startAtSectionIndex,
    _Out_ int* nextSectionIndex) const
{
    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->TryGetSectionIndexByType(sectionType, 0, startAtSectionIndex, nextSectionIndex);
    }

    return false;
}

HRESULT PriFileManager::GetAtomPoolSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileAtomPool** result) const
{
    *result = nullptr;

    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->GetAtomPoolSection(0, sectionIndex, result);
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT PriFileManager::GetDecisionInfoSection(
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ DecisionInfoFileSection** result) const
{
    *result = nullptr;

    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->GetDecisionInfoSection(0, sectionIndex, result);
    }
    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT
PriFileManager::GetSchemaSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ HierarchicalSchema** result) const
{
    *result = nullptr;

    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->GetSchemaSection(0, sectionIndex, result);
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT PriFileManager::GetResourceMapSection(
    _In_ const ISchemaCollection* pSchemaCollection,
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ ResourceMapBase** result) const
{
    *result = nullptr;

    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->GetResourceMapSection(pSchemaCollection, 0, sectionIndex, result);
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT PriFileManager::GetPriDescriptorSection(
    _In_ const ISchemaCollection* pSchemaCollection,
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ PriDescriptor** result) const
{
    *result = nullptr;

    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->GetPriDescriptorSection(pSchemaCollection, 0, sectionIndex, result);
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT PriFileManager::GetFileListSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileFileList** result) const
{
    *result = nullptr;

    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->GetFileListSection(0, sectionIndex, result);
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT
PriFileManager::GetDataItemsSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataItemsSection** result) const
{
    *result = nullptr;

    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->GetDataItemsSection(0, sectionIndex, result);
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT PriFileManager::GetDataSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataSection** result) const
{
    *result = nullptr;

    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->GetDataSection(0, sectionIndex, result);
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT
PriFileManager::GetReverseFileMapSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ ReverseFileMap** result) const
{
    *result = nullptr;

    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->GetReverseFileMapSection(0, sectionIndex, result);
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT PriFileManager::GetEnvironmentMappingSection(
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ const EnvironmentMapping** result) const
{
    *result = nullptr;

    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->GetEnvironmentMappingSection(0, sectionIndex, result);
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT PriFileManager::GetResourceLinkSection(
    _In_opt_ const ISchemaCollection* schemas,
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ const ResourceLinkSection** result) const
{
    *result = nullptr;

    FileManagerFileInfo finfo;
    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->GetResourceLinkSection(schemas, 0, sectionIndex, result);
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT PriFileManager::GetAbsoluteFolderPath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const
{
    FileManagerFileInfo finfo;
    if (!m_pFiles->TryGet(fileIndex, &finfo))
    {
        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    // Unloaded file is loaded this time when GetBaseMrmFile is called
    PCWSTR pszFilePath = finfo.pFile->GetPackageRoot();
    if (!pszFilePath)
    {
        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    return pStringResult->SetRef(pszFilePath);
}

HRESULT PriFileManager::GetFilePath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const
{
    FileManagerFileInfo finfo;
    if (!m_pFiles->TryGet(fileIndex, &finfo))
    {
        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    // Unloaded file is loaded this time when GetBaseMrmFile is called
    PCWSTR pszFilePath = finfo.pFile->GetPath();
    if (!pszFilePath)
    {
        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    return pStringResult->SetRef(pszFilePath);
}

HRESULT PriFileManager::GetFileDefaultEnvironment(
    _In_ int fileIndex,
    _Inout_opt_ StringResult* fileEnvironmentName,
    _Inout_opt_ EnvironmentVersionInfo* fileEnvironmentVersion) const
{
    FileManagerFileInfo finfo;

    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        return finfo.pFile->GetFileDefaultEnvironment(0, fileEnvironmentName, fileEnvironmentVersion);
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT PriFileManager::GetDefaultQualifierMapping(_In_ int fileIndex, _Out_ const RemapAtomPool** result) const
{
    *result = nullptr;
    FileManagerFileInfo finfo;

    if (m_pFiles->TryGet(fileIndex, &finfo) && (finfo.pFile != nullptr))
    {
        RETURN_IF_FAILED(finfo.pFile->GetDefaultQualifierMapping(0, result));
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT PriFileManager::Init(_In_ UnifiedEnvironment* pEnvironment)
{
    m_pEnvironment = pEnvironment;
    m_defaultFileFlags = BaseFile::MapFileFlag;
    RETURN_IF_FAILED(DynamicArray<FileManagerFileInfo>::CreateInstance(DefaultInitialFilesSize, &m_pFiles));

    return S_OK;
}

PriFileManager::~PriFileManager()
{
    if (m_pFiles != nullptr)
    {
        FileManagerFileInfo finfo;
        FileManagerFileInfo finfoNull = {};

        for (int i = 0; i < m_pFiles->Count(); i++)
        {
            if (m_pFiles->TryGet(i, &finfo))
            {
                m_pFiles->Set(i, finfoNull);

                delete finfo.pFile;
                finfo.pFile = nullptr;
            }
        }
        delete m_pFiles;
        m_pFiles = nullptr;
    }
}

} // namespace Microsoft::Resources
