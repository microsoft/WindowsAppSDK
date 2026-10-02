// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "stdafx.h"

WCHAR g_lastFailedFile[MAX_PATH];

namespace Microsoft::Resources
{

HRESULT NormalizedFilePath::Init(_In_ PCWSTR pStr)
{
    StringResult path;
    RETURN_IF_FAILED(ManagedFile::NormalizeFilePath(pStr, &path));
    RETURN_IF_FAILED(this->SetContentsFromOther(&path));
    return S_OK;
}

NormalizedFilePath::NormalizedFilePath() : StringResult() {}

NormalizedFilePath::~NormalizedFilePath(void) {}

HRESULT ManagedFile::CreateInstance(_In_ const MrmFile* pBaseFile, _Outptr_ ManagedFile** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pBaseFile);

    ManagedFile* pRtrn = new ManagedFile(pBaseFile);
    RETURN_IF_NULL_ALLOC(pRtrn);

    *result = pRtrn;
    return S_OK;
}

HRESULT ManagedFile::CreateInstance(
    _In_ const PriFileManager* pManager,
    _In_ int globalIndex,
    _In_ PCWSTR pPath,
    _In_opt_ PCWSTR pPackageRoot,
    _In_ LoadPriFlags flags,
    _Outptr_ ManagedFile** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (pManager == nullptr) || DefString_IsEmpty(pPath));

    NormalizedFilePath normalizedPath;
    RETURN_IF_FAILED(normalizedPath.Init(pPath));

    AutoDeletePtr<ManagedFile> pRtrn = new ManagedFile(pManager, globalIndex);
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(pRtrn->Initialize(pManager, &normalizedPath, pPackageRoot));

    if ((flags & LoadPriFlags::Preload) == LoadPriFlags::Preload)
    {
        RETURN_IF_FAILED(pRtrn->Load());
    }

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT ManagedFile::CreateInstance(
    _In_ const PriFileManager* pManager,
    _In_ int globalIndex,
    _In_ const NormalizedFilePath* pNormalizedPath,
    _In_opt_ PCWSTR pPackageRoot,
    _In_ LoadPriFlags flags,
    _Outptr_ ManagedFile** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (pManager == nullptr) || (pNormalizedPath == nullptr) || DefString_IsEmpty(pNormalizedPath->GetRef()));

    AutoDeletePtr<ManagedFile> pRtrn = new ManagedFile(pManager, globalIndex);
    RETURN_IF_NULL_ALLOC(pRtrn);
    HRESULT hr = pRtrn->Initialize(pManager, pNormalizedPath, pPackageRoot);
    if (FAILED(hr))
    {
        if (((flags & (LoadPriFlags::ExcludeLogForFileNotFound | LoadPriFlags::LoadForDependentPackages)) == LoadPriFlags::Default) ||
            ((hr != HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) && (hr != HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND))))
        {
            WRITE_MRMMIN_INIT_TRACE_ERROR_MEASURE_CHECK(
                ((pNormalizedPath != nullptr) && (pNormalizedPath->GetRef() != nullptr)) ? pNormalizedPath->GetRef() : L"", hr);
            _DefStringCchPrintf(
                g_lastFailedFile,
                ARRAYSIZE(g_lastFailedFile),
                L"0,%x,%s",
                hr,
                ((pNormalizedPath != nullptr) && (pNormalizedPath->GetRef() != nullptr)) ? pNormalizedPath->GetRef() : L"");
        }

        return hr;
    }

    if ((flags & LoadPriFlags::Preload) == LoadPriFlags::Preload)
    {
        hr = pRtrn->Load();
        if (FAILED(hr))
        {
            WRITE_MRMMIN_INIT_TRACE_ERROR_MEASURE_CHECK(
                ((pNormalizedPath != nullptr) && (pNormalizedPath->GetRef() != nullptr)) ? pNormalizedPath->GetRef() : L"", hr);
            _DefStringCchPrintf(
                g_lastFailedFile,
                ARRAYSIZE(g_lastFailedFile),
                L"1,%x,%s",
                hr,
                ((pNormalizedPath != nullptr) && (pNormalizedPath->GetRef() != nullptr)) ? pNormalizedPath->GetRef() : L"");
            return hr;
        }
    }

    *result = pRtrn.Detach();
    return S_OK;
}

ManagedFile::ManagedFile(_In_ const MrmFile* pBaseFile) :
    m_pManager(nullptr),
    m_globalIndex(-1),
    m_loadFailed(false),
    m_pBaseFile(pBaseFile),
    m_pMyBaseFile(nullptr),
    m_pPath(nullptr),
    m_fileSizeInBytes(0),
    m_fileLastModifiedDate(0),
    m_pPackageRoot(nullptr),
    m_pEnvironment(pBaseFile->GetUnifiedEnvironment())
{}

HRESULT
ManagedFile::Initialize(_In_ const PriFileManager* pManager, _In_ const NormalizedFilePath* pNormalizedPath, _In_opt_ PCWSTR pPackageRoot)
{
    RETURN_HR_IF(E_INVALIDARG, (pManager == nullptr) || (pNormalizedPath == nullptr) || DefString_IsEmpty(pNormalizedPath->GetRef()));

    WIN32_FILE_ATTRIBUTE_DATA finfo = {0};
    RETURN_IF_WIN32_BOOL_FALSE_EXPECTED(GetFileAttributesExW(pNormalizedPath->GetRef(), GetFileExInfoStandard, &finfo));
    ULARGE_INTEGER tmp;
    tmp.u.LowPart = finfo.ftLastWriteTime.dwLowDateTime;
    tmp.u.HighPart = finfo.ftLastWriteTime.dwHighDateTime;
    m_fileLastModifiedDate = tmp.QuadPart;

    tmp.u.LowPart = finfo.nFileSizeLow;
    tmp.u.HighPart = finfo.nFileSizeHigh;
    m_fileSizeInBytes = tmp.QuadPart;

    size_t size;
    StringResult path;
    RETURN_IF_FAILED(DefString_Dup(pNormalizedPath->GetRef(), &m_pPath));

    RETURN_IF_FAILED(NormalizePackageRoot(m_pPath, pPackageRoot, &path));
    RETURN_IF_FAILED(path.ReleaseContents(&m_pPackageRoot, &size));

    return S_OK;
}

ManagedFile::ManagedFile(_In_ const PriFileManager* pManager, _In_ int globalIndex) :
    m_pManager(pManager),
    m_globalIndex(globalIndex),
    m_loadFailed(false),
    m_pBaseFile(nullptr),
    m_pMyBaseFile(nullptr),
    m_pPath(nullptr),
    m_fileSizeInBytes(0),
    m_fileLastModifiedDate(0),
    m_pPackageRoot(nullptr),
    m_pEnvironment(pManager->GetUnifiedEnvironment())
{}

ManagedFile::~ManagedFile()
{
    if (m_pMyBaseFile)
    {
        (void)Unload();
    }

    if (m_pPath != nullptr)
    {
        Def_Free(m_pPath);
        m_pPath = nullptr;
    }

    if (m_pPackageRoot != nullptr)
    {
        Def_Free(m_pPackageRoot);
        m_pPackageRoot = nullptr;
    }
}

HRESULT ManagedFile::InnerLoad() const
{
    if (m_pBaseFile != nullptr)
    {
        return S_OK;
    }

    RETURN_IF_FAILED(MrmFile::CreateInstance(const_cast<PriFileManager*>(m_pManager), m_pPath, (MrmFile**)&m_pMyBaseFile));
    m_pBaseFile = m_pMyBaseFile;

    m_loadFailed = false;

    return S_OK;
}

HRESULT ManagedFile::InnerUnload() const
{
    if (m_pBaseFile == nullptr)
    {
        return S_OK;
    }
    else if (m_pMyBaseFile == nullptr)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE);
    }

    delete m_pMyBaseFile;
    m_pMyBaseFile = nullptr;
    m_pBaseFile = nullptr;
    return S_OK;
}

HRESULT ManagedFile::SetPackageRoot(_In_ PCWSTR pPackageRoot)
{
    // Nothing to do if the path hasn't changed
    if (DefString_ICompare(pPackageRoot, m_pPackageRoot) == Def_Equal)
    {
        return S_OK;
    }

    // Can't change the path if we're currently loaded
    RETURN_HR_IF(E_MRM_PACKAGE_ROOT_MISMATCH, IsLoaded());

    // Not loaded. Change the path.
    if (m_pPackageRoot != nullptr)
    {
        Def_Free(m_pPackageRoot);
        m_pPackageRoot = nullptr;
    }

    if (pPackageRoot != nullptr)
    {
        RETURN_IF_FAILED(DefString_Dup(pPackageRoot, &m_pPackageRoot));
    }
    return S_OK;
}

HRESULT ManagedFile::GetBaseFile(_Out_ const BaseFile** result) const
{
    *result = nullptr;
    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetBaseFile(result));

    return S_OK;
}

HRESULT ManagedFile::GetBaseMrmFile(_Out_ const IMrmFile** result) const
{
    *result = nullptr;
    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }
    *result = m_pBaseFile;
    return S_OK;
}

HRESULT ManagedFile::GetSection(
    _In_ const ISchemaCollection* pSchemaCollection,
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ const IFileSection** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetSection(pSchemaCollection, fileIndex, sectionIndex, result));

    return S_OK;
}

_Success_(return == true)
const bool ManagedFile::TryGetSectionIndexByType(
    _In_ const DEFFILE_SECTION_TYPEID& sectionType,
    _In_ int fileIndex,
    _In_ int startAtSectionIndex,
    _Out_ int* nextSectionIndex) const
{
    if ((fileIndex != 0) || ((m_pBaseFile == nullptr) && FAILED(InnerLoad())))
    {
        return false;
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    return m_pBaseFile->TryGetSectionIndexByType(sectionType, fileIndex, startAtSectionIndex, nextSectionIndex);
}

HRESULT ManagedFile::GetAtomPoolSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileAtomPool** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetAtomPoolSection(fileIndex, sectionIndex, result));

    return S_OK;
}

HRESULT
ManagedFile::GetDecisionInfoSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ DecisionInfoFileSection** result)
    const
{
    *result = nullptr;

    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetDecisionInfoSection(fileIndex, sectionIndex, result));

    return S_OK;
}

HRESULT ManagedFile::GetSchemaSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ HierarchicalSchema** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetSchemaSection(fileIndex, sectionIndex, result));

    return S_OK;
}

HRESULT ManagedFile::GetResourceMapSection(
    _In_ const ISchemaCollection* pSchemaCollection,
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ ResourceMapBase** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetResourceMapSection(pSchemaCollection, fileIndex, sectionIndex, result));

    return S_OK;
}

HRESULT ManagedFile::GetPriDescriptorSection(
    _In_ const ISchemaCollection* pSchemaCollection,
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ PriDescriptor** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetPriDescriptorSection(pSchemaCollection, fileIndex, sectionIndex, result));

    return S_OK;
}

HRESULT ManagedFile::GetFileListSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileFileList** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetFileListSection(fileIndex, sectionIndex, result));

    return S_OK;
}

HRESULT
ManagedFile::GetDataItemsSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataItemsSection** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetDataItemsSection(fileIndex, sectionIndex, result));

    return S_OK;
}

HRESULT ManagedFile::GetDataSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ FileDataSection** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetDataSection(fileIndex, sectionIndex, result));

    return S_OK;
}

HRESULT
ManagedFile::GetReverseFileMapSection(_In_ int fileIndex, _In_ BaseFile::SectionIndex sectionIndex, _Out_ ReverseFileMap** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetReverseFileMapSection(fileIndex, sectionIndex, result));

    return S_OK;
}

HRESULT ManagedFile::GetEnvironmentMappingSection(
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ const EnvironmentMapping** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetEnvironmentMappingSection(fileIndex, sectionIndex, result));

    return S_OK;
}

HRESULT ManagedFile::GetResourceLinkSection(
    _In_opt_ const ISchemaCollection* schemas,
    _In_ int fileIndex,
    _In_ BaseFile::SectionIndex sectionIndex,
    _Out_ const ResourceLinkSection** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetResourceLinkSection(schemas, fileIndex, sectionIndex, result));

    return S_OK;
}

HRESULT ManagedFile::GetFileDefaultEnvironment(
    _In_ int fileIndex,
    _Inout_opt_ StringResult* fileEnvironmentName,
    _Inout_opt_ EnvironmentVersionInfo* fileEnvironmentVersion) const
{
    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    return m_pBaseFile->GetFileDefaultEnvironment(fileIndex, fileEnvironmentName, fileEnvironmentVersion);
}

HRESULT ManagedFile::GetDefaultQualifierMapping(_In_ int fileIndex, _Out_ const RemapAtomPool** result) const
{
    *result = nullptr;
    RETURN_HR_IF(E_DEF_NOT_READY, fileIndex != 0);

    if (m_pBaseFile == nullptr)
    {
        RETURN_IF_FAILED(InnerLoad());
    }

    DEF_ASSERT(m_pBaseFile != nullptr);

    RETURN_IF_FAILED(m_pBaseFile->GetDefaultQualifierMapping(fileIndex, result));

    return S_OK;
}

HRESULT ManagedFile::NormalizeFilePath(_In_ PCWSTR pFilePath, _Inout_ StringResult* pPathOut)
{
    RETURN_HR_IF(E_INVALIDARG, (pPathOut == nullptr) || (DefString_IsEmpty(pFilePath)));

    PCWSTR pSlash = wcschr(pFilePath, L':');
    if (pSlash != nullptr && ((*(++pSlash) == L'\\') || (*(pSlash) == L'/')))
    {
        // We assume that it has absolute path
        //TODO: This is a hack until Lowbox supports GetFinalPathNameByHandleW
        RETURN_IF_FAILED(pPathOut->SetCopy(pFilePath));
    }
    else
    {
        wil::unique_handle hFile(::CreateFileW(pFilePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE, 0, OPEN_EXISTING, 0, 0));
        RETURN_LAST_ERROR_IF(hFile.get() == INVALID_HANDLE_VALUE);

        // Second arg to GetFinalPathNameByHandleW is _In_ not _In_opt, so
        // we need to pass _something_.
        wchar_t buf[1];
        ULONG ulRequiredSize = ::GetFinalPathNameByHandleW(hFile.get(), &buf[0], 1, 0);

        // GetFinalPathNameByHandleW() ALWAYS returns the file path with \\?\ prefix to indicate that
        // the filename is already resolved to the final form.
        // Therefore, the minimal length of ulRequiredSize is greater than 4.
        if (ulRequiredSize > 4)
        {
            unique_deffree_ptr<wchar_t> pszBuffer(_DefArray_AllocZeroed(wchar_t, ulRequiredSize));
            RETURN_IF_NULL_ALLOC(pszBuffer.get());

            RETURN_LAST_ERROR_IF(::GetFinalPathNameByHandleW(hFile.get(), pszBuffer.get(), static_cast<UINT16>(ulRequiredSize), 0) == 0);

            // GetFinalPathNameByHandleW() ALWAYS returns the file path with \\?\ prefix to indicate that
            // the filename is already resolved to the final form.
            // For the output of the API, the spec is to return the filename WITHOUT \\?\ prefix.
            // So we will truncate the 4 wchar_t from the beginning of returned path from GetFinalPathNameByHandleW().

            // If long path is prepended with UNC, remove UNC also.
            if (DefString_IsPrefixI(L"\\\\?\\UNC\\", pszBuffer.get()))
            {
                unsigned ulPrepended = sizeof(L"\\\\?\\UNC") / sizeof(WCHAR) - 1;
                DEF_ASSERT(ulRequiredSize > ulPrepended);
                ulRequiredSize -= ulPrepended;
                RETURN_IF_FAILED(pPathOut->SetCopy(L"\\"));
                RETURN_IF_FAILED(pPathOut->Concat(pszBuffer.get() + ulPrepended));
            }
            else
            {
                ulRequiredSize -= 4;
                RETURN_IF_FAILED(pPathOut->SetCopy(pszBuffer.get() + 4));
            }
        }
        else
        {
            RETURN_LAST_ERROR();
        }
    }

    return S_OK;
}

HRESULT ManagedFile::NormalizePackageRoot(_In_ PCWSTR pPriFile, _In_opt_ PCWSTR pPackageRoot, _Inout_ StringResult* pPathOut)
{
    if (pPackageRoot == nullptr)
    {
        RETURN_IF_FAILED(pPathOut->SetCopy(pPriFile));

        size_t size = 0;
        PWSTR pBuf;
        RETURN_IF_FAILED(pPathOut->GetWritableRef(&pBuf, &size));

        // Remove pri file name to get the package root.
        PWSTR pLastSlash = wcsrchr(pBuf, L'\\');
        if (pLastSlash != nullptr)
        {
            pLastSlash[0] = L'\0';
        }
    }
    else
    {
        RETURN_IF_FAILED(pPathOut->SetCopy(pPackageRoot));
    }
    return S_OK;
}

HRESULT ManagedFile::ResolveFileFileList(_In_ const FileFileList* pFileFileList)
{
    return const_cast<IMrmFile*>(m_pBaseFile)->ResolveFileFileList(pFileFileList);
}

HRESULT ManagedFile::GetAbsoluteFolderPath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const
{
    return m_pBaseFile->GetAbsoluteFolderPath(fileIndex, pStringResult);
}

HRESULT ManagedFile::GetFilePath(_In_ int fileIndex, _Inout_ StringResult* pStringResult) const
{
    return m_pBaseFile->GetFilePath(fileIndex, pStringResult);
}

} // namespace Microsoft::Resources
