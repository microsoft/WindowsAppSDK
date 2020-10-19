// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"

namespace Microsoft::Resources::Build
{

/*!
     * FileInfoPrivateData - abstract base class for per-file private data
     */

FileInfoPrivateData::FileInfoPrivateData(__in const void* pOwner, __in int index) : m_pOwner(pOwner), m_index(index), m_pNext(NULL) {}

FileInfoPrivateData::~FileInfoPrivateData()
{
    delete m_pNext;
    m_pNext = NULL;
}

HRESULT FileInfoPrivateData::SetNext(__in_opt FileInfoPrivateData* pNext)
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY), m_pNext != NULL);

    m_pNext = pNext;
    return S_OK;
}

bool FileInfoPrivateData::TryGetNext(__in_opt const void* pOwner, __in int index, __out FileInfoPrivateData** ppDataOut) const
{
    if ((ppDataOut == nullptr) || ((pOwner == nullptr) && (index >= 0)))
    {
        return false;
    }
    *ppDataOut = NULL;
    FileInfoPrivateData* pNext = m_pNext;
    while (pNext && (!pNext->Matches(pOwner, index)))
    {
        pNext = pNext->m_pNext;
    }
    *ppDataOut = pNext;
    return (pNext != NULL);
}

/*
     * FileInfo - describes a single file of interest
     */
FileInfo::FileInfo(__in FolderInfo* pParent) : m_pName(nullptr), m_pParentFolder(pParent), m_index(-1), m_pPrivates(nullptr), m_flags(0) {}

HRESULT FileInfo::Init(_In_ PCWSTR name)
{
    RETURN_IF_FAILED(DefString_Dup(name, &m_pName));
    m_nameIsAscii = (DefString_ChooseBestEncoding(name) == DEFSTRING_ENCODING_ASCII);

    return S_OK;
}

FileInfo::~FileInfo()
{
    if (m_pName)
    {
        _DefFree(m_pName);
        m_pName = NULL;
    }
    delete m_pPrivates;
    m_pPrivates = NULL;
}

HRESULT FileInfo::CreateInstance(__in PCWSTR pName, __in FolderInfo* pParent, _Outptr_ FileInfo** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pName) || (pParent == nullptr));

    AutoDeletePtr<FileInfo> pRtrn = new FileInfo(pParent);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pName));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT FileInfo::GetFileName(__inout StringResult* pNameOut) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pNameOut);

    RETURN_IF_FAILED(pNameOut->SetRef(m_pName));

    return S_OK;
}

HRESULT FileInfo::GetFullPath(__inout StringResult* pPathOut) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pPathOut);

    RETURN_IF_FAILED(m_pParentFolder->GetFullPath(pPathOut));
    RETURN_IF_FAILED(pPathOut->ConcatPathElement(m_pName));

    return S_OK;
}

bool FileInfo::TryGetPrivateData(__in_opt const void* pOwner, __in int index, __out FileInfoPrivateData** ppDataOut) const
{
    if (ppDataOut == nullptr)
    {
        return false;
    }
    *ppDataOut = NULL;
    if (!m_pPrivates)
    {
        return false;
    }

    if (m_pPrivates->Matches(pOwner, index))
    {
        *ppDataOut = m_pPrivates;
        return true;
    }
    return m_pPrivates->TryGetNext(pOwner, index, ppDataOut);
}

HRESULT FileInfo::AddPrivateData(__in FileInfoPrivateData* pPrivate, __in bool allowDuplicates)
{
    RETURN_HR_IF(E_INVALIDARG, (pPrivate == nullptr) || (pPrivate->GetNext() != nullptr));

    if (m_pPrivates != NULL)
    {
        if (!allowDuplicates)
        {
            FileInfoPrivateData* pNext = m_pPrivates;
            while (pNext)
            {
                if (pNext->Matches(pPrivate))
                {
                    return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
                }
            }
        }

        RETURN_IF_FAILED(pPrivate->SetNext(m_pPrivates));
    }

    m_pPrivates = pPrivate;
    return S_OK;
}

/*
     * FolderInfo - Describes a single folder of interest and its contents
     */
FolderInfo::FolderInfo(__in PCWSTR pName, __in_opt FolderInfo* pParent) :
    m_pParentFolder(pParent),
    m_pSubfolders(nullptr),
    m_pFiles(nullptr),
    m_pName(nullptr),
    m_numFiles(0),
    m_sizeFiles(0),
    m_numSubfolders(0),
    m_sizeSubfolders(0),
    m_totalNumFiles(0),
    m_totalNumFolders((pName && pName[0]) ? 1 : 0), // No files, and just this folder. Don't count this folder if it's a "hidden" root.
    m_index(-1)
{}

HRESULT FolderInfo::Init(_In_ PCWSTR name)
{
    RETURN_IF_FAILED(DefString_Dup(name, &m_pName));
    m_nameIsAscii = (DefString_ChooseBestEncoding(name) == DEFSTRING_ENCODING_ASCII);

    return S_OK;
}

FolderInfo::~FolderInfo()
{
    if (m_pName)
    {
        _DefFree(m_pName);
        m_pName = NULL;
    }

    if (m_pSubfolders)
    {
        for (int i = 0; i < m_numSubfolders; i++)
        {
            if (!m_pSubfolders[i])
                continue;
            delete m_pSubfolders[i];
            m_pSubfolders[i] = NULL;
        }
        _DefFree(m_pSubfolders);
        m_pSubfolders = NULL;
        m_numSubfolders = m_sizeSubfolders = 0;
    }

    if (m_pFiles)
    {
        for (int i = 0; i < m_numFiles; i++)
        {
            if (!m_pFiles[i])
                continue;
            delete m_pFiles[i];
            m_pFiles[i] = NULL;
        }
        _DefFree(m_pFiles);
        m_numFiles = m_sizeFiles = NULL;
    }
}

HRESULT FolderInfo::CreateInstance(__in PCWSTR pName, __in FolderInfo* pParent, _Outptr_ FolderInfo** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pName) || (pParent == nullptr));

    AutoDeletePtr<FolderInfo> pRtrn = new FolderInfo(pName, pParent);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pName));

    *result = pRtrn.Detach();
    return S_OK;
}

bool FolderInfo::NoteSubfolderChanges(__in int numFoldersAdded, __in int numFilesAdded)
{
    m_totalNumFolders += numFoldersAdded;
    m_totalNumFiles += numFilesAdded;
    return (m_pParentFolder ? m_pParentFolder->NoteSubfolderChanges(numFoldersAdded, numFilesAdded) : true);
}

HRESULT FolderInfo::ExtendSubfolders()
{
    if (!m_pSubfolders)
    {
        m_sizeSubfolders = 0;
        m_pSubfolders = _DefArray_Alloc(FolderInfo*, 5);
        RETURN_IF_NULL_ALLOC(m_pSubfolders);

        m_sizeSubfolders = 5;
        return S_OK;
    }

    if (m_numSubfolders >= m_sizeSubfolders)
    {
        UINT32 newSize = m_sizeSubfolders * 2;
        FolderInfo** pTmp;
        RETURN_IF_FAILED(_DefArray_Expand(m_pSubfolders, FolderInfo*, m_sizeSubfolders, newSize, &pTmp));

        m_sizeSubfolders = newSize;
        m_pSubfolders = pTmp;
    }
    return S_OK;
}

HRESULT FolderInfo::ExtendFiles()
{
    if (!m_pFiles)
    {
        m_sizeFiles = 0;
        m_pFiles = _DefArray_Alloc(FileInfo*, 5);
        RETURN_IF_NULL_ALLOC(m_pFiles);

        m_sizeFiles = 5;
        return S_OK;
    }

    if (m_numFiles >= m_sizeFiles)
    {
        UINT32 newSize = m_sizeFiles * 2;
        FileInfo** pTmp;
        RETURN_IF_FAILED(_DefArray_Expand(m_pFiles, FileInfo*, m_sizeFiles, newSize, &pTmp));

        m_sizeFiles = newSize;
        m_pFiles = pTmp;
    }
    return S_OK;
}

HRESULT FolderInfo::NewRootFolder(_Outptr_ FolderInfo** result)
{
    *result = nullptr;

    AutoDeletePtr<FolderInfo> pRtrn = new FolderInfo(L"", nullptr);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(L""));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT FolderInfo::GetFolderName(__inout StringResult* pPathOut) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pPathOut);

    RETURN_IF_FAILED(pPathOut->SetRef(m_pName));

    return S_OK;
}

HRESULT FolderInfo::GetFullPath(__inout StringResult* pPathOut) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pPathOut);

    if (!m_pParentFolder)
    {
        RETURN_IF_FAILED(pPathOut->SetRef(m_pName));
    }
    else
    {
        RETURN_IF_FAILED(m_pParentFolder->GetFullPath(pPathOut));
        RETURN_IF_FAILED(pPathOut->ConcatPathElement(m_pName));
    }
    return S_OK;
}

HRESULT FolderInfo::GetSubfolder(__in int index, _Out_ FolderInfo** result) const
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > m_numSubfolders - 1));

    *result = m_pSubfolders[index];
    return S_OK;
}

HRESULT FolderInfo::GetSubfolder(__in PCWSTR pName, _Out_ FolderInfo** result) const
{
    if (!TryGetSubfolder(pName, result))
    {
        return E_DEF_FOLDER_NOT_FOUND;
    }

    return S_OK;
}

bool FolderInfo::TryGetSubfolder(__in PCWSTR pName, __inout FolderInfo** ppFolderOut) const
{
    if (ppFolderOut)
    {
        *ppFolderOut = NULL;
    }
    if (DefString_IsEmpty(pName) || (ppFolderOut == nullptr) || (!m_pSubfolders))
    {
        return false;
    }
    for (int i = 0; i < m_numSubfolders; i++)
    {
        if (!m_pSubfolders[i])
        {
            continue;
        }
        if (DefString_ICompare(pName, m_pSubfolders[i]->GetFolderName()) == Def_Equal)
        {
            *ppFolderOut = m_pSubfolders[i];
            return true;
        }
    }
    return false;
}

int FolderInfo::GetSubfolderIndex(__in PCWSTR pName) const
{
    int index = -1;
    if (!TryGetSubfolderIndex(pName, &index))
    {
        return -1;
    }
    return index;
}

bool FolderInfo::TryGetSubfolderIndex(__in PCWSTR pName, __out int* ppIndexOut) const
{
    if (ppIndexOut)
    {
        *ppIndexOut = -1;
    }
    if (DefString_IsEmpty(pName) || (ppIndexOut == nullptr) || (!m_pSubfolders))
    {
        return false;
    }
    for (int i = 0; i < m_numSubfolders; i++)
    {
        if (!m_pSubfolders[i])
        {
            continue;
        }
        if (DefString_ICompare(pName, m_pSubfolders[i]->GetFolderName()) == Def_Equal)
        {
            *ppIndexOut = i;
            return true;
        }
    }
    return false;
}

HRESULT FolderInfo::GetOrAddSubfolder(__in PCWSTR pName, _Out_ FolderInfo** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pName));

    if (TryGetSubfolder(pName, result))
    {
        return S_OK;
    }
    if (m_numSubfolders >= m_sizeSubfolders)
    {
        RETURN_IF_FAILED(ExtendSubfolders());
    }

    FolderInfo* pRtrn;
    RETURN_IF_FAILED(FolderInfo::CreateInstance(pName, this, &pRtrn));

    m_pSubfolders[m_numSubfolders++] = pRtrn;
    NoteSubfolderChanges(1, 0);

    *result = pRtrn;
    return S_OK;
}

HRESULT FolderInfo::GetFile(__in int index, _Out_ FileInfo** result) const
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > m_numFiles - 1));

    *result = m_pFiles[index];
    return S_OK;
}

HRESULT FolderInfo::GetFile(__in PCWSTR pName, _Out_ FileInfo** result) const
{
    *result = nullptr;

    if (!TryGetFile(pName, result))
    {
        return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    }
    return S_OK;
}

bool FolderInfo::TryGetFile(__in PCWSTR pName, __out FileInfo** ppFileOut) const
{
    if (ppFileOut)
    {
        *ppFileOut = NULL;
    }
    if (DefString_IsEmpty(pName) || (ppFileOut == nullptr) || (!m_pFiles))
    {
        return false;
    }
    for (int i = 0; i < m_numFiles; i++)
    {
        if (!m_pFiles[i])
        {
            continue;
        }
        if (DefString_ICompare(pName, m_pFiles[i]->GetFileName()) == Def_Equal)
        {
            *ppFileOut = m_pFiles[i];
            return true;
        }
    }
    return false;
}

int FolderInfo::GetFileIndex(__in PCWSTR pName) const
{
    int index = -1;
    if (!TryGetFileIndex(pName, &index))
    {
        return -1;
    }
    return index;
}

bool FolderInfo::TryGetFileIndex(__in PCWSTR pName, __out int* ppIndexOut) const
{
    if (ppIndexOut)
    {
        *ppIndexOut = -1;
    }

    if (DefString_IsEmpty(pName) || (ppIndexOut == nullptr) || (!m_pFiles))
    {
        return false;
    }

    for (int i = 0; i < m_numFiles; i++)
    {
        if (!m_pFiles[i])
        {
            continue;
        }
        if (DefString_ICompare(pName, m_pFiles[i]->GetFileName()) == Def_Equal)
        {
            *ppIndexOut = i;
            return true;
        }
    }
    return false;
}

HRESULT FolderInfo::GetOrAddFile(__in PCWSTR pName, _Out_ FileInfo** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pName));

    if (TryGetFile(pName, result))
    {
        return S_OK;
    }

    if (m_numFiles >= m_sizeFiles)
    {
        RETURN_IF_FAILED(ExtendFiles());
    }

    FileInfo* pRtrn;
    RETURN_IF_FAILED(FileInfo::CreateInstance(pName, this, &pRtrn));

    m_pFiles[m_numFiles++] = pRtrn;
    NoteSubfolderChanges(0, 1);

    *result = pRtrn;
    return S_OK;
}

/*!
 * An \ref IFileList representation of the finalized contents of
 * an \ref FileListBuilder.
 */
class FileListBuilder::FinalizedBuilder : public DefObject, public IFileList
{
protected:
    const FileListBuilder* m_pBuilder;

    int m_numFolders;
    int m_numFiles;
    FolderInfo** m_pAllFolders;
    FileInfo** m_pAllFiles;

    int m_cchLongestPath;

    FinalizedBuilder(__in const FileListBuilder* pBuilder, __in int numFolders, __in int numFiles) :
        m_pBuilder(pBuilder), m_numFolders(numFolders), m_numFiles(numFiles), m_pAllFolders(NULL), m_pAllFiles(NULL), m_cchLongestPath(-1)
    {}

    HRESULT Init(__in const FileListBuilder* pBuilder, __in int numFolders, __in int numFiles)
    {
        RETURN_HR_IF(E_INVALIDARG, (pBuilder == nullptr) || (numFolders < 0) || (numFiles < 0));

        if (m_numFolders > 0)
        {
            m_pAllFolders = _DefArray_AllocZeroed(FolderInfo*, m_numFolders);
            RETURN_IF_NULL_ALLOC(m_pAllFolders);
        }

        if (m_numFiles > 0)
        {
            m_pAllFiles = _DefArray_AllocZeroed(FileInfo*, m_numFiles);
            RETURN_IF_NULL_ALLOC(m_pAllFiles);
        }

        return S_OK;
    }

public:
    ~FinalizedBuilder()
    {
        m_numFolders = 0;
        m_numFiles = 0;
        if (m_pAllFolders != NULL)
        {
            Def_Free(m_pAllFolders);
            m_pAllFolders = NULL;
        }
        if (m_pAllFiles != NULL)
        {
            Def_Free(m_pAllFiles);
            m_pAllFiles = NULL;
        }
    }

    static HRESULT CreateInstance(
        __in const FileListBuilder* pBuilder,
        __in int numFolders,
        __in int numFiles,
        _Outptr_ FinalizedBuilder** result)
    {
        *result = nullptr;
        RETURN_HR_IF(E_INVALIDARG, (pBuilder == nullptr) || (numFolders < 0) || (numFiles < 0));

        AutoDeletePtr<FinalizedBuilder> pRtrn = new FinalizedBuilder(pBuilder, numFolders, numFiles);
        RETURN_IF_NULL_ALLOC(pRtrn);
        RETURN_IF_FAILED(pRtrn->Init(pBuilder, numFolders, numFiles));

        *result = pRtrn.Detach();
        return S_OK;
    }

    int GetNumFolders() const { return m_numFolders; }
    int GetNumFiles() const { return m_numFiles; }

    FolderInfo** GetFolders() { return m_pAllFolders; }
    FileInfo** GetFiles() { return m_pAllFiles; }

    HRESULT GetFolder(__in int index, __out FolderInfo** ppFolderOut) const
    {
        RETURN_HR_IF(E_INVALIDARG, (ppFolderOut == nullptr) || (index < 0) || (index > m_numFolders - 1));

        *ppFolderOut = this->m_pAllFolders[index];
        return ((*ppFolderOut) != nullptr) ? S_OK : HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    HRESULT GetFile(__in int index, __out FileInfo** ppFileOut) const
    {
        RETURN_HR_IF(E_INVALIDARG, (ppFileOut == nullptr) || (index < 0) || (index > m_numFiles - 1));

        *ppFileOut = this->m_pAllFiles[index];
        return ((*ppFileOut) != nullptr) ? S_OK : HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    HRESULT InitFolderIndex(__in FolderInfo* pFolderInfo, __inout int* pNumInitialized) const
    {
        RETURN_HR_IF(E_INVALIDARG, (pFolderInfo == nullptr) || (pNumInitialized == nullptr));
        RETURN_HR_IF(E_ABORT, (!m_pAllFolders) || (m_numFolders < 0));

        int index = pFolderInfo->GetIndex();
        if ((index < 0) || (index >= m_numFolders) || (m_pAllFolders[index] != NULL))
        {
            return E_ABORT;
        }
        m_pAllFolders[index] = pFolderInfo;
        *pNumInitialized = (*pNumInitialized) + 1;
        for (int i = 0; i < pFolderInfo->GetNumSubfolders(); i++)
        {
            FolderInfo* pSubFolder;
            RETURN_IF_FAILED(pFolderInfo->GetSubfolder(i, &pSubFolder));

            RETURN_IF_FAILED(InitFolderIndex(pSubFolder, pNumInitialized));
        }
        return S_OK;
    }

    HRESULT InitFileIndex(__in FolderInfo* pFolderInfo, __inout int* pNumInitialized) const
    {
        RETURN_HR_IF(E_INVALIDARG, (pFolderInfo == nullptr) || (pNumInitialized == nullptr));
        RETURN_HR_IF(E_ABORT, (!m_pAllFolders) || (m_numFiles < 0));

        int i;
        for (i = 0; i < pFolderInfo->GetNumFiles(); i++)
        {
            FileInfo* pFile;
            RETURN_IF_FAILED(pFolderInfo->GetFile(i, &pFile));

            int index = pFile->GetIndex();
            if ((index < 0) || (index >= m_numFiles) || (m_pAllFiles[index] != NULL))
            {
                return E_ABORT;
            }
            m_pAllFiles[index] = pFile;
            *pNumInitialized = (*pNumInitialized) + 1;
        }
        for (i = 0; i < pFolderInfo->GetNumSubfolders(); i++)
        {
            FolderInfo* pSubFolder;
            RETURN_IF_FAILED(pFolderInfo->GetSubfolder(i, &pSubFolder));

            RETURN_IF_FAILED(InitFileIndex(pSubFolder, pNumInitialized));
        }
        return S_OK;
    }

    /*!
     * \name IFileList Implementation
     * @{
     */

    //! \see IFileList::GetNumRootFolders
    int GetNumRootFolders() const { return m_pBuilder->GetNumRootFolders(); }

    //! \see IFileList::GetTotalNumFolders
    int GetTotalNumFolders() const { return m_pBuilder->GetTotalNumFolders(); }

    //! \see IFileList::GetTotalNumFiles
    int GetTotalNumFiles() const { return m_pBuilder->GetTotalNumFiles(); }

    //! \see IFileList::GetLongestPath
    int GetLongestPath() const { return 0; /* return m_pBuilder->GetLongestPath();*/ }

    //! \see IFileList::GetFolderName
    HRESULT GetFolderName(__in int folderIndex, __inout StringResult* pNameOut) const
    {
        RETURN_HR_IF(E_INVALIDARG, (folderIndex < 0) || (folderIndex > m_numFolders - 1) || (pNameOut == nullptr));
        RETURN_HR_IF(E_DEF_NOT_READY, m_pAllFolders[folderIndex] == nullptr);

        RETURN_IF_FAILED(m_pAllFolders[folderIndex]->GetFolderName(pNameOut));

        return S_OK;
    }

    //! \see IFileList::GetFileName
    HRESULT GetFileName(__in int fileIndex, __inout StringResult* pNameOut) const
    {
        RETURN_HR_IF(E_INVALIDARG, (fileIndex < 0) || (fileIndex > m_numFiles - 1) || (pNameOut == nullptr));
        RETURN_HR_IF(E_DEF_NOT_READY, m_pAllFiles[fileIndex] == nullptr);

        RETURN_IF_FAILED(m_pAllFiles[fileIndex]->GetFileName(pNameOut));

        return S_OK;
    }

    //! \see IFileList::GetSubfolders
    HRESULT GetSubfolders(__in int folderIndex, __out_opt int* pFirstSubfolderOut, __out_opt int* pNumSubfoldersOut) const
    {
        RETURN_HR_IF(E_INVALIDARG, (folderIndex < 0) || (folderIndex > m_numFolders - 1));
        RETURN_HR_IF(E_DEF_NOT_READY, m_pAllFolders[folderIndex] == nullptr);

        FolderInfo* pFolder = m_pAllFolders[folderIndex];
        if (pNumSubfoldersOut != NULL)
        {
            *pNumSubfoldersOut = pFolder->GetNumSubfolders();
        }
        if (pFirstSubfolderOut != NULL)
        {
            if (pFolder->GetNumSubfolders() > 0)
            {
                FolderInfo* pSubFolder;
                RETURN_IF_FAILED(pFolder->GetSubfolder(0, &pSubFolder));

                *pFirstSubfolderOut = pSubFolder->GetIndex();
            }
            else
            {
                *pFirstSubfolderOut = -1;
            }
        }
        return S_OK;
    }

    //! \see IFileList::GetFiles
    HRESULT GetFiles(__in int folderIndex, __out_opt int* pFirstFileOut, __out_opt int* pNumFilesOut) const
    {
        RETURN_HR_IF(E_INVALIDARG, (folderIndex < 0) || (folderIndex > m_numFolders - 1));
        RETURN_HR_IF(E_DEF_NOT_READY, m_pAllFolders[folderIndex] == nullptr);

        FolderInfo* pFolder = m_pAllFolders[folderIndex];
        if (pNumFilesOut != NULL)
        {
            *pNumFilesOut = pFolder->GetNumFiles();
        }
        if (pFirstFileOut != NULL)
        {
            if (pFolder->GetNumFiles() > 0)
            {
                FileInfo* pFile;
                RETURN_IF_FAILED(pFolder->GetFile(0, &pFile));

                *pFirstFileOut = pFile->GetIndex();
            }
            else
            {
                *pFirstFileOut = -1;
            }
        }
        return S_OK;
    }

    //! \see IFileList::GetFolderParentIndex
    HRESULT GetFolderParentFolderIndex(__in int folderIndex, __out int* pParentFolderIndexOut) const
    {
        RETURN_HR_IF(E_INVALIDARG, (folderIndex < 0) || (folderIndex > m_numFolders - 1) || (pParentFolderIndexOut == nullptr));
        RETURN_HR_IF(E_DEF_NOT_READY, m_pAllFolders[folderIndex] == nullptr);

        FolderInfo* pParent = m_pAllFolders[folderIndex]->GetParentFolder();
        *pParentFolderIndexOut = (pParent ? pParent->GetIndex() : -1);
        return S_OK;
    }

    //! \see IFileList::GetFileParentFolderIndex
    HRESULT GetFileParentFolderIndex(__in int fileIndex, __out int* pParentFolderIndexOut) const
    {
        RETURN_HR_IF(E_INVALIDARG, (fileIndex < 0) || (fileIndex > m_numFiles - 1) || (pParentFolderIndexOut == nullptr));
        RETURN_HR_IF(E_DEF_NOT_READY, m_pAllFiles[fileIndex] == nullptr);

        FolderInfo* pParent = m_pAllFiles[fileIndex]->GetParentFolder();
        *pParentFolderIndexOut = (pParent ? pParent->GetIndex() : -1);
        return S_OK;
    }

    //! \see IFileList::GetFilePath
    HRESULT GetFilePath(__in int fileIndex, __inout StringResult* pPathOut) const { return GetFilePath(fileIndex, pPathOut, nullptr); }

    //! \see IFileList::GetFilePath
    HRESULT GetFilePath(_In_ int fileIndex, _Inout_ StringResult* pPathOut, _Out_ UINT16* /*pFlags*/) const
    {
        RETURN_HR_IF(E_INVALIDARG, (fileIndex < 0) || (fileIndex > m_numFiles - 1) || (pPathOut == nullptr));
        RETURN_HR_IF(E_DEF_NOT_READY, m_pAllFiles[fileIndex] == nullptr);

        RETURN_IF_FAILED(m_pAllFiles[fileIndex]->GetFullPath(pPathOut));

        return S_OK;
    }

    //! \see IFileList::GetFolderPath
    HRESULT GetFolderPath(__in int folderIndex, __inout StringResult* pPathOut) const
    {
        RETURN_HR_IF(E_INVALIDARG, (folderIndex < 0) || (folderIndex > m_numFolders - 1) || (pPathOut == nullptr));
        RETURN_HR_IF(E_DEF_NOT_READY, m_pAllFolders[folderIndex] == nullptr);

        RETURN_IF_FAILED(m_pAllFolders[folderIndex]->GetFullPath(pPathOut));

        return S_OK;
    }

    /*!@}*/
};

/*!
 * Section builder for a file list section.
 */

FileListBuilder::FileListBuilder(_In_ FileBuilder* pParentFile, _In_ UINT32 flags) :
    m_pParentFile(pParentFile),
    m_sectionIndex(-1),
    m_numFinalizedFiles(-1),
    m_numFinalizedFolders(-1),
    m_pFinalized(nullptr),
    m_flags(flags),
    m_pRootFolder(nullptr)
{}

HRESULT FileListBuilder::Init()
{
    RETURN_IF_FAILED(FolderInfo::NewRootFolder(&m_pRootFolder));
    return S_OK;
}

HRESULT FileListBuilder::CreateInstance(_In_ FileBuilder* pParentFile, _In_ UINT32 flags, _Outptr_ FileListBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pParentFile);

    AutoDeletePtr<FileListBuilder> builder = new FileListBuilder(pParentFile, flags);
    RETURN_IF_NULL_ALLOC(builder);
    RETURN_IF_FAILED(builder->Init());

    *result = builder.Detach();
    return S_OK;
}

FileListBuilder::~FileListBuilder()
{
    delete m_pRootFolder;
    delete m_pFinalized;

    m_pRootFolder = NULL;
    m_pFinalized = NULL;
}

int FileListBuilder::GetNumRootFolders() const { return m_pRootFolder->GetNumSubfolders(); }

int FileListBuilder::GetTotalNumFolders() const { return m_pRootFolder->GetTotalNumFolders(); }

int FileListBuilder::GetTotalNumFiles() const { return m_pRootFolder->GetTotalNumFiles(); }

HRESULT FileListBuilder::GetRootFolder(__in int index, _Out_ FolderInfo** result) const
{
    return m_pRootFolder->GetSubfolder(index, result);
}

HRESULT FileListBuilder::GetRootFolder(__in PCWSTR pPath, _Out_ FolderInfo** result) const
{
    return m_pRootFolder->GetSubfolder(pPath, result);
}

bool FileListBuilder::TryGetRootFolder(__inout PCWSTR pPath, __inout FolderInfo** ppFolderOut) const
{
    return m_pRootFolder->TryGetSubfolder(pPath, ppFolderOut);
}

HRESULT FileListBuilder::GetOrAddRootFolder(__in PCWSTR pPath, _Out_ FolderInfo** result)
{
    return m_pRootFolder->GetOrAddSubfolder(pPath, result);
}

bool FileListBuilder::TryGetFolderByIndex(__in int index, __out FolderInfo** ppFolderOut) const
{
    if ((ppFolderOut == nullptr) || (m_numFinalizedFolders < 0) || (index < 0) || (index > m_numFinalizedFolders - 1))
    {
        return false;
    }

    IFileList* tmp = NULL;
    if ((!m_pFinalized) && (FAILED(GetFileList(&tmp))))
    {
        return false;
    }
    return SUCCEEDED(m_pFinalized->GetFolder(index, ppFolderOut));
}

bool FileListBuilder::TryGetFileByIndex(__in int index, __out FileInfo** ppFileOut) const
{
    if ((ppFileOut == nullptr) || (m_numFinalizedFiles < 0) || (index < 0) || (index > m_numFinalizedFiles - 1))
    {
        return false;
    }
    IFileList* tmp = NULL;
    if ((!m_pFinalized) && (FAILED(GetFileList(&tmp))))
    {
        return false;
    }
    return SUCCEEDED(m_pFinalized->GetFile(index, ppFileOut));
}

size_t FileListBuilder::ComputeTotalStringsSizeInBytes(_In_ const FolderInfo* pFolder, _In_ UINT32 flags)
{
    size_t cchUtf16Total = 0;
    size_t cchAsciiTotal = 0;

    if (SUCCEEDED(ComputeTotalStringsSize(pFolder, flags, &cchAsciiTotal, &cchUtf16Total)))
    {
        size_t cbRaw = _DEFFILE_PAD(cchAsciiTotal, 2) + (cchUtf16Total * sizeof(WCHAR));
        return _DEFFILE_PAD(cbRaw, 4);
    }

    return 0;
}

HRESULT
FileListBuilder::ComputeTotalStringsSize(
    _In_ const FolderInfo* pFolder,
    _In_ UINT32 flags,
    _Inout_ size_t* pCchAsciiTotal,
    _Inout_ size_t* pCchUtf16Total)
{
    int i;
    size_t cchName;
    StringResult name;
    PCWSTR pName;
    bool buildAscii = ((flags & BuildEncodingFlags) == BuildAsciiOrUtf16);

    RETURN_HR_IF_NULL(E_INVALIDARG, pFolder);

    // Reserve space for the name of this folder, unless it's the root folder.
    RETURN_IF_FAILED(pFolder->GetFolderName(&name));

    pName = name.GetRef();
    if (pName && pName[0])
    {
        cchName = wcslen(pName) + 1;
        if (buildAscii && pFolder->NameIsAscii())
        {
            (*pCchAsciiTotal) += cchName;
        }
        else
        {
            (*pCchUtf16Total) += cchName;
        }
    }

    // Now reserve space for each of the files in this folder
    for (i = 0; i < pFolder->GetNumFiles(); i++)
    {
        FileInfo* pFile;
        RETURN_IF_FAILED(pFolder->GetFile(i, &pFile));
        RETURN_IF_FAILED(pFile->GetFileName(&name));

        pName = name.GetRef();
        cchName = wcslen(pName) + 1;

        if (buildAscii && pFile->NameIsAscii())
        {
            (*pCchAsciiTotal) += cchName;
        }
        else
        {
            (*pCchUtf16Total) += cchName;
        }
    }

    // Reserve space for all subfolders
    for (i = 0; i < pFolder->GetNumSubfolders(); i++)
    {
        FolderInfo* pSubfolder;
        RETURN_IF_FAILED(pFolder->GetSubfolder(i, &pSubfolder));

        RETURN_IF_FAILED(ComputeTotalStringsSize(pSubfolder, flags, pCchAsciiTotal, pCchUtf16Total));
    }

    return S_OK;
}

bool FileListBuilder::IsFinalized() const
{
    return ((m_numFinalizedFolders == GetTotalNumFolders()) && (m_numFinalizedFiles == GetTotalNumFiles()));
}

HRESULT FileListBuilder::GetFileList(__out IFileList** ppFileListOut) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, ppFileListOut);

    RETURN_HR_IF(E_DEF_NOT_READY, !IsFinalized());

    if (m_pFinalized == NULL)
    {
        AutoDeletePtr<FinalizedBuilder> builder;
        RETURN_IF_FAILED(FinalizedBuilder::CreateInstance(this, m_numFinalizedFolders, m_numFinalizedFiles, &builder));

        int numFilesInitialized = 0;
        int numFoldersInitialized = 0;
        for (int i = 0; i < GetNumRootFolders(); i++)
        {
            FolderInfo* pFolder;
            RETURN_IF_FAILED(m_pRootFolder->GetSubfolder(i, &pFolder));
            RETURN_IF_FAILED(builder->InitFolderIndex(pFolder, &numFoldersInitialized));
            RETURN_IF_FAILED(builder->InitFileIndex(pFolder, &numFilesInitialized));
        }
        if ((numFoldersInitialized != m_numFinalizedFolders) || (numFilesInitialized != m_numFinalizedFiles))
        {
            return E_ABORT;
        }
        m_pFinalized = builder.Detach();
    }
    *ppFileListOut = m_pFinalized;
    return S_OK;
}

bool FileListBuilder::IsValidFileIndex(__inout int indexIn) const
{
    if ((indexIn < 0) || (indexIn > IFileList::MaxFileIndex) || (!IsFinalized()))
    {
        return false;
    }
    return (indexIn < m_numFinalizedFiles);
}

bool FileListBuilder::IsValidFolderIndex(__inout int indexIn) const
{
    if ((indexIn < 0) || (indexIn > IFileList::MaxFileIndex) || (!IsFinalized()))
    {
        return false;
    }
    return (indexIn < m_numFinalizedFolders);
}

UINT32 FileListBuilder::GetMaxSizeInBytes() const
{
    size_t totalSize = sizeof(DEFFILE_FILELIST_HEADER);
    totalSize += GetTotalNumFolders() * sizeof(DEFFILE_FILELIST_FOLDER_ENTRY);
    totalSize += GetTotalNumFiles() * sizeof(DEFFILE_FILELIST_FILE_ENTRY);
    // add a WCHAR to string size for leading NUL on string pool

    size_t cbStringPool = sizeof(WCHAR) + ComputeTotalStringsSizeInBytes(m_pRootFolder, m_flags);

    totalSize += _DEFFILE_PAD(cbStringPool, 4);
    totalSize = _DEFFILE_PAD_SECTION(totalSize);

    return static_cast<UINT32>(totalSize);
}

HRESULT FileListBuilder::AssignFolderIndices(
    __in FolderInfo* pFolderInfo,
    __in int index,
    __inout UINT32* pNextFolder,
    __in UINT32 sizeFolders,
    __inout UINT32* pNextFile,
    __in UINT32 sizeFiles)
{
    RETURN_HR_IF(E_INVALIDARG, (pFolderInfo == nullptr) || (pNextFile == nullptr) || (pNextFolder == nullptr));
    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > ((INT32)sizeFolders) - 1));

    // Let OACR know what's going on
    __analysis_assume(index >= 0);
    __analysis_assume(index < sizeFolders);

    pFolderInfo->SetIndex(index);

    UINT32 numSubfolders = pFolderInfo->GetNumSubfolders();
    UINT32 numFiles = pFolderInfo->GetNumFiles();
    INT32 nFirstSubfolder = ((numSubfolders > 0) ? (*pNextFolder) : -1);
    INT32 nFirstFile = ((numFiles > 0) ? (*pNextFile) : -1);

    if (numFiles > 0)
    {
        if (nFirstFile + numFiles > sizeFiles)
        {
            return E_DEFFILE_BUILD_SECTION_DATA_TOO_LARGE;
        }
        *pNextFile += numFiles;
        for (int i = 0; i < (int)numFiles; i++)
        {
            FileInfo* pFileInfo;
            RETURN_IF_FAILED(pFolderInfo->GetFile(i, &pFileInfo));

            pFileInfo->SetIndex(nFirstFile + i + 1); // 1 based file index since runtime use 0 index as its own file
        }
    }

    if (numSubfolders > 0)
    {
        if (nFirstSubfolder + numSubfolders > sizeFolders)
        {
            return E_DEFFILE_BUILD_SECTION_DATA_TOO_LARGE;
        }
        *pNextFolder += numSubfolders;
        for (int i = 0; i < (int)numSubfolders; i++)
        {
            FolderInfo* pSubfolder;
            RETURN_IF_FAILED(pFolderInfo->GetSubfolder(i, &pSubfolder));

            RETURN_IF_FAILED(AssignFolderIndices(
                pSubfolder, // folder
                nFirstSubfolder + i, // folder index
                pNextFolder,
                sizeFolders,
                pNextFile,
                sizeFiles));
        }
    }
    return S_OK;
}

HRESULT FileListBuilder::BuildFolderInfo(
    __in const FolderInfo* pFolderInfo,
    __in int index,
    __in int parentIndex,
    __inout_ecount(sizeFolders) DEFFILE_FILELIST_FOLDER_ENTRY* pFolders,
    __inout UINT32* pNextFolder,
    __in UINT32 sizeFolders,
    __out_ecount(sizeFiles) DEFFILE_FILELIST_FILE_ENTRY* pFiles,
    __inout UINT32* pNextFile,
    __in UINT32 sizeFiles,
    __in WriteableStringPool* pNames) const
{
    DEFFILE_FILELIST_FOLDER_ENTRY* pParent = NULL;
    UINT32 parentPathLen = 0;

    RETURN_HR_IF(E_INVALIDARG, (pFolderInfo == nullptr) || (pNextFile == nullptr) || (pNextFolder == nullptr) || (pNames == nullptr));
    RETURN_HR_IF(E_INVALIDARG, (index < 0) || (index > ((INT32)sizeFolders) - 1) || (parentIndex >= (INT32)sizeFolders));

    // let OACR know what we've figured out
    __analysis_assume(index >= 0);
    __analysis_assume(index < sizeFolders);

    // If we've been assigned an index, we have to build to it.  If we haven't
    // been assigned an index, any index is okay.
    if ((pFolderInfo->GetIndex() >= 0) && (pFolderInfo->GetIndex() != index))
    {
        return E_ABORT;
    }

    if (parentIndex >= 0)
    {
        pParent = &pFolders[parentIndex];
        parentPathLen = pParent->cchFullPath + 1;
    }

    StringResult name;
    RETURN_IF_FAILED(pFolderInfo->GetFolderName(&name));

    UINT32 numSubfolders = pFolderInfo->GetNumSubfolders();
    UINT32 numFiles = pFolderInfo->GetNumFiles();
    INT32 nFirstSubfolder = ((numSubfolders > 0) ? (*pNextFolder) : -1);
    INT32 nFirstFile = ((numFiles > 0) ? (*pNextFile) : -1);

    pFolders[index].flags = 0;
    pFolders[index].parentFolderIndex = (INT16)parentIndex;
    pFolders[index].numSubfolders = (UINT16)numSubfolders;
    pFolders[index].firstSubfolder = (INT16)nFirstSubfolder;
    pFolders[index].numFiles = (UINT16)numFiles;
    pFolders[index].firstFile = (INT16)nFirstFile;
    pFolders[index].cchName = (UINT16)wcslen(name.GetRef());
    pFolders[index].cchFullPath = (UINT16)(parentPathLen + pFolders[index].cchName);
    pFolders[index].nameOffset = pNames->GetOrAddStringOffset(name.GetRef());
    RETURN_HR_IF(E_ABORT, pFolders[index].nameOffset == -1);

    if (numFiles > 0)
    {
        DEFFILE_FILELIST_FILE_ENTRY* pFile = &pFiles[nFirstFile];
        if (nFirstFile + numFiles > sizeFiles)
        {
            return E_DEFFILE_BUILD_SECTION_DATA_TOO_LARGE;
        }
        *pNextFile += numFiles;
        for (int i = 0; i < (int)numFiles; i++, pFile++)
        {
            FileInfo* pFileInfo;
            RETURN_IF_FAILED(pFolderInfo->GetFile(i, &pFileInfo));
            RETURN_IF_FAILED(pFileInfo->GetFileName(&name));

            if ((pFileInfo->GetIndex() >= 0) && (pFileInfo->GetIndex() != (nFirstFile + i + 1)))
            { // fileIndex is based on 1 during Finalize
                return E_ABORT;
            }
            pFile->flags = pFileInfo->GetFlag();
            pFile->parentFolderIndex = (INT16)index;
            pFile->cchName = (UINT16)wcslen(name.GetRef());
            pFile->cchFullPath = (UINT16)(pFolders[index].cchFullPath + 1 + pFile->cchName);
            pFile->nameOffset = pNames->GetOrAddStringOffset(name.GetRef());
            RETURN_HR_IF(E_ABORT, pFile->nameOffset == -1);
        }
    }

    if (numSubfolders > 0)
    {
        if (nFirstSubfolder + numSubfolders > sizeFolders)
        {
            return E_DEFFILE_BUILD_SECTION_DATA_TOO_LARGE;
        }
        *pNextFolder += numSubfolders;
        for (int i = 0; i < (int)numSubfolders; i++)
        {
            FolderInfo* pSubfolder;
            RETURN_IF_FAILED(pFolderInfo->GetSubfolder(i, &pSubfolder));

            RETURN_IF_FAILED(BuildFolderInfo(
                pSubfolder, // folder
                nFirstSubfolder + i, // folder index
                index, // parent folder index
                pFolders,
                pNextFolder,
                sizeFolders,
                pFiles,
                pNextFile,
                sizeFiles,
                pNames));
        }
    }
    return S_OK;
}

HRESULT FileListBuilder::Finalize()
{
    UINT32 nextFile = 0;
    UINT32 nextFolder = GetNumRootFolders();
    UINT32 sizeFolders = GetTotalNumFolders();
    UINT32 sizeFiles = GetTotalNumFiles();

    if (m_pFinalized != NULL)
    {
        delete m_pFinalized;
        m_pFinalized = NULL;
    }

    for (int i = 0; i < GetNumRootFolders(); i++)
    {
        FolderInfo* pFolder;
        RETURN_IF_FAILED(m_pRootFolder->GetSubfolder(i, &pFolder));

        RETURN_IF_FAILED(AssignFolderIndices(pFolder, i, &nextFolder, sizeFolders, &nextFile, sizeFiles));
    }

    if ((nextFile != sizeFiles) || (nextFolder != sizeFolders))
    {
        return E_ABORT;
    }
    m_numFinalizedFolders = sizeFolders;
    m_numFinalizedFiles = sizeFiles;
    return S_OK;
}

/*! 
 * Serializes the file list into the provided buffer.
 * 
 * \param pBuffer
 * The buffer into which the file list is generated.
 *
 * \param cbBuffer
 * Size of the destination buffer, in bytes.
 *
 * \param pStatus
 * If the Build method returns false, pStatus contains additional
 * information about the cause of the error.
 *
 * \param cbWrittenOut
 * If pcbWrittenOut is non-NULL, the Build method uses it to return
 * the number of bytes actually written.
 *
 * \return bool
 * Returns true on success, false if an error occurs.
 */
_Use_decl_annotations_ HRESULT FileListBuilder::Build(VOID* pBuffer, UINT32 cbBuffer, UINT32* pcbWrittenOut) const
{
    DEFFILE_FILELIST_HEADER* pHeader;
    DEFFILE_FILELIST_FOLDER_ENTRY* pFolders;
    DEFFILE_FILELIST_FILE_ENTRY* pFiles;
    WCHAR* pNamesPool;
    AutoDeletePtr<WriteableStringPool> pStrings = NULL;
    UINT32 numFolders = GetTotalNumFolders();
    UINT32 numFiles = GetTotalNumFiles();
    UINT32 cbFixed = sizeof(DEFFILE_FILELIST_HEADER) + (numFolders * sizeof(DEFFILE_FILELIST_FOLDER_ENTRY)) +
                     (numFiles * sizeof(DEFFILE_FILELIST_FILE_ENTRY));

    RETURN_HR_IF(E_INVALIDARG, (pBuffer == nullptr) || (cbBuffer < cbFixed));

    pHeader = reinterpret_cast<DEFFILE_FILELIST_HEADER*>(pBuffer);
    pFolders = reinterpret_cast<DEFFILE_FILELIST_FOLDER_ENTRY*>(&pHeader[1]);
    pFiles = reinterpret_cast<DEFFILE_FILELIST_FILE_ENTRY*>(&pFolders[numFolders]);
    pNamesPool = reinterpret_cast<WCHAR*>(&pFiles[numFiles]);

    UINT32 cchRemaining = (cbBuffer - cbFixed) / sizeof(WCHAR);
    RETURN_IF_FAILED(
        WriteableStringPool::CreateInstance(pNamesPool, cchRemaining, WriteableStringPool::fCompareCaseInsensitive, &pStrings));

    RETURN_HR_IF(E_INVALIDARG, cbBuffer < sizeof(DEFFILE_FILELIST_HEADER));

    _Analysis_assume_(cbBuffer >= sizeof(DEFFILE_FILELIST_HEADER));

    // Initialize the header
    pHeader->numRootFolders = (UINT16)m_pRootFolder->GetNumSubfolders();
    pHeader->numFolderEntries = (UINT16)numFolders;
    pHeader->numFileEntries = (UINT16)numFiles;
    pHeader->cchLongestPath = 0;
    pHeader->cchNamesPool = 0;

    UINT32 nextFile = 0;
    UINT32 nextFolder = pHeader->numRootFolders;
    for (int i = 0; i < pHeader->numRootFolders; i++)
    {
        FolderInfo* pFolder;
        RETURN_IF_FAILED(m_pRootFolder->GetSubfolder(i, &pFolder));

        RETURN_IF_FAILED(BuildFolderInfo(
            pFolder, i, -1, pFolders, &nextFolder, pHeader->numFolderEntries, pFiles, &nextFile, pHeader->numFileEntries, pStrings));
    }

    if ((nextFile != pHeader->numFileEntries) || (nextFolder != pHeader->numFolderEntries) ||
        (pStrings->GetNumCharsInPool() > cchRemaining))
    {
        return E_ABORT;
    }
    pHeader->cchNamesPool = pStrings->GetNumCharsInPool();
    // Don't need to copy the pool because pStrings generated the pool
    // in the right spot directly.
    UINT32 totalSize = sizeof(DEFFILE_FILELIST_HEADER) + sizeof(DEFFILE_FILELIST_FOLDER_ENTRY) * pHeader->numFolderEntries +
                       sizeof(DEFFILE_FILELIST_FILE_ENTRY) * pHeader->numFileEntries + sizeof(WCHAR) * pHeader->cchNamesPool;
    totalSize = _DEFFILE_PAD_SECTION(totalSize);
    if (totalSize > cbBuffer)
    {
        return E_ABORT;
    }
    *pcbWrittenOut = totalSize;
    return S_OK;
}

} // namespace Microsoft::Resources::Build