// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"

namespace Microsoft::Resources
{

bool IFileList::IsValidFileIndex(__inout int indexIn) const { return ((indexIn >= 0) && (indexIn < GetTotalNumFiles())); }
bool IFileList::IsValidFolderIndex(__inout int indexIn) const { return ((indexIn >= 0) && (indexIn < GetTotalNumFolders())); }

bool IFileList::TryGetFileIndex(__in PCWSTR pFilePath, __out int* pIndexOut) const
{
    if ((pFilePath == nullptr) || (pIndexOut == nullptr))
    {
        return false;
    }

    int index = -1;
    int cchUsed = 0;
    if (!TryGetPrefixFolderIndex(pFilePath, &index, &cchUsed))
    {
        return false;
    }

    if ((index < 0) || (index > GetTotalNumFolders()) || (cchUsed < 1))
    {
        // shouldn't happen
        return false;
    }

    int firstFile = -1;
    int numFiles = 0;
    if (FAILED(GetFiles(index, &firstFile, &numFiles)) || (!IsValidFileRange(firstFile, numFiles)))
    {
        return false;
    }

    const WCHAR* pLookingFor = &pFilePath[cchUsed];
    StringResult fileName;

    *pIndexOut = -1;
    for (int i = 0; i < numFiles; i++)
    {
        Def_IfFailedReturnFalse(GetFileName(firstFile + i, &fileName));

        if (DefString_ICompare(fileName.GetRef(), pLookingFor) == 0)
        {
            *pIndexOut = firstFile + i;
            break;
        }
    }
    return ((*pIndexOut) >= 0);
}

bool IFileList::TryGetFolderIndex(__in PCWSTR pPath, __out int* pIndexOut) const
{
    if ((pPath == nullptr) || (pIndexOut == nullptr))
    {
        return false;
    }

    int index = -1;
    int cchUsed = 0;
    if (!TryGetPrefixFolderIndex(pPath, &index, &cchUsed))
    {
        return false;
    }

    if ((index < 0) || (index > GetTotalNumFolders()) || (cchUsed < 1))
    {
        // shouldn't happen
        return false;
    }

    int firstSubfolder = -1;
    int numSubfolders = 0;
    if (FAILED(GetSubfolders(index, &firstSubfolder, &numSubfolders)) || (!IsValidFolderRange(firstSubfolder, numSubfolders)))
    {
        return false;
    }

    const WCHAR* pLookingFor = &pPath[cchUsed];
    StringResult folderName;
    *pIndexOut = -1;

    for (int i = 0; i < numSubfolders; i++)
    {
        Def_IfFailedReturnFalse(GetFolderName(firstSubfolder + i, &folderName));

        if (DefString_ICompare(folderName.GetRef(), pLookingFor) == 0)
        {
            *pIndexOut = firstSubfolder + i;
            break;
        }
    }
    return ((*pIndexOut) >= 0);
}

bool IFileList::TryGetPrefixFolderIndex(__in PCWSTR pFullPath, __out int* pIndexOut, __out_opt int* pcchUsedOut) const
{
    if ((pFullPath == nullptr) || (pIndexOut == nullptr))
    {
        return false;
    }

    *pIndexOut = -1;
    if (pcchUsedOut)
    {
        *pcchUsedOut = 0;
    }

    int cchFullPath = (int)wcslen(pFullPath);
    int thisFolder = -1;
    int cchUsed = 0;
    int lastMatchIndex = -1;
    const WCHAR* pLookingFor;
    StringResult name;

    for (int root = 0; root < GetNumRootFolders(); root++)
    {
        // new root, start looking again from the beginning
        thisFolder = root;
        cchUsed = 0;
        pLookingFor = pFullPath;

        while (IsValidFolderIndex(thisFolder))
        {
            int firstSubfolder = -1;
            int numSubfolders = 0;

            if (FAILED(GetSubfolders(thisFolder, &firstSubfolder, &numSubfolders)) || (!IsValidFolderRange(firstSubfolder, numSubfolders)))
            {
                return false;
            }

            bool found = false;
            for (int i = 0; i < numSubfolders; i++)
            {
                Def_IfFailedReturnFalse(GetFolderName(firstSubfolder + i, &name));

                if (DefString_IsPrefixI(pLookingFor, name.GetRef()))
                {
                    size_t localName;
                    name.GetLength(&localName);
                    int cchName = static_cast<int>(localName);
                    if (cchUsed + cchName >= cchFullPath)
                    {
                        return false;
                    }
                    if (pLookingFor[cchName - 1] == '\\')
                    {
                        // This folder matches.  Note the index and skip over
                        // the name.
                        found = true;
                        lastMatchIndex = firstSubfolder + i;
                        pLookingFor += cchName;
                        cchUsed += cchName;
                        thisFolder = firstSubfolder + i;
                        break;
                    }
                }
            }
            if (!found)
            {
                break;
            }
        }
        // we matched something
        if (cchUsed > 0)
        {
            break;
        }
    }

    if (cchUsed > GetLongestPath())
    {
        return false;
    }
    if (pcchUsedOut)
    {
        *pcchUsedOut = cchUsed;
    }
    *pIndexOut = lastMatchIndex;
    if ((lastMatchIndex >= 0) && (!IsValidFolderIndex(lastMatchIndex)))
    {
        return false;
    }
    return (cchUsed != 0);
}

const DEFFILE_SECTION_TYPEID FileFileList::GetSectionTypeId() { return gFileListSectionType; }

FileFileList::FileFileList() :
    FileSectionBase(), m_pHeader(NULL), m_pFolders(NULL), m_pFiles(NULL), m_pAsciiNames(NULL), m_pUtf16Names(NULL)
{}

HRESULT FileFileList::Init(__in_opt const IFileSection* pSection, __in_bcount(cbData) const void* pData, __in int cbData)
{
    RETURN_IF_FAILED(FileSectionBase::Init(pSection, pData, cbData));
    RETURN_IF_FAILED(Validate(pData, cbData));

    SectionParser data;
    RETURN_IF_FAILED(data.Set(pData, cbData));

    HRESULT hr = S_OK;
    const DEFFILE_FILELIST_HEADER* pHeader = _SECTION_PARSER_NEXT(data, DEFFILE_FILELIST_HEADER, &hr);
    RETURN_IF_FAILED(hr);

    m_header.numRootFolders = pHeader->numRootFolders;
    m_header.numFolderEntries = pHeader->numFolderEntries;
    m_header.numFileEntries = pHeader->numFileEntries;
    m_header.cchLongestPath = pHeader->cchLongestPath;
    m_header.cchUtf16NamesPool = pHeader->cchNamesPool;
    m_header.cchAsciiNamesPool = 0;

    m_pHeader = &m_header;
    m_pFolders = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numFolderEntries, DEFFILE_FILELIST_FOLDER_ENTRY, &hr);
    m_pFiles = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numFileEntries, DEFFILE_FILELIST_FILE_ENTRY, &hr);
    m_pAsciiNames = nullptr;
    m_pUtf16Names = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->cchUtf16NamesPool, WCHAR, &hr);
    RETURN_IF_FAILED(hr);

    m_root.flags = 0;
    m_root.parentFolderIndex = -1;
    m_root.numSubfolders = m_pHeader->numRootFolders;
    m_root.firstSubfolder = 0;
    m_root.numFiles = 0;
    m_root.firstFile = -1;
    m_root.cchName = 0;
    m_root.cchFullPath = 0;
    m_root.nameOffset = 0;

    return S_OK;
}

HRESULT FileFileList::CreateInstance(__in_bcount(cbData) const BYTE* pData, __in int cbData, _Outptr_ FileFileList** result)
{
    *result = nullptr;

    AutoDeletePtr<FileFileList> pRtrn = new FileFileList();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(nullptr, pData, cbData));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT FileFileList::CreateInstance(__in IFileSection* pSection, _Outptr_ FileFileList** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pSection);

    AutoDeletePtr<FileFileList> pRtrn = new FileFileList();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pSection, pSection->GetData(), pSection->GetDataSize()));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT FileFileList::GetFolderName(__in int folderIndex, __inout StringResult* pNameOut) const
{
    RETURN_HR_IF(E_INVALIDARG, (folderIndex < 0) || (folderIndex > m_pHeader->numFolderEntries - 1) || (pNameOut == nullptr));

    const DEFFILE_FILELIST_FOLDER_ENTRY* pFolder = &m_pFolders[folderIndex];
    PCWSTR pName;
    RETURN_IF_FAILED(GetUtf16Name(pFolder->nameOffset, pFolder->cchName, &pName));
    RETURN_IF_FAILED(pNameOut->SetRef(pName));

    return S_OK;
}

HRESULT FileFileList::GetFileName(__in int fileIndex, __inout StringResult* pNameOut) const
{
    RETURN_HR_IF(E_INVALIDARG, (fileIndex < 1) || (fileIndex > m_pHeader->numFileEntries - 1) || (pNameOut == nullptr));

    int fileBasedFileIndex = fileIndex - 1;

    const DEFFILE_FILELIST_FILE_ENTRY* pFile = &m_pFiles[fileBasedFileIndex];
    PCWSTR pName;
    RETURN_IF_FAILED(GetUtf16Name(pFile->nameOffset, pFile->cchName, &pName));
    RETURN_IF_FAILED(pNameOut->SetRef(pName));

    return S_OK;
}

HRESULT FileFileList::GetSubfolders(__in int folderIndex, __out_opt int* pFirstSubfolderOut, __out_opt int* pNumSubfoldersOut) const
{
    RETURN_HR_IF(E_INVALIDARG, (folderIndex < 0) || (folderIndex > m_pHeader->numFolderEntries - 1));

    const DEFFILE_FILELIST_FOLDER_ENTRY* pFolder = &m_pFolders[folderIndex];
    if (pFirstSubfolderOut)
    {
        *pFirstSubfolderOut = pFolder->firstSubfolder;
    }
    if (pNumSubfoldersOut)
    {
        *pNumSubfoldersOut = pFolder->numSubfolders;
    }
    return ((pFolder->firstSubfolder >= 0) && (pFolder->numSubfolders > 0)) ? S_OK : HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT FileFileList::GetFiles(__in int folderIndex, __out_opt int* pFirstFileOut, __out_opt int* pNumFilesOut) const
{
    RETURN_HR_IF(E_INVALIDARG, (folderIndex < 0) || (folderIndex > m_pHeader->numFolderEntries - 1));

    const DEFFILE_FILELIST_FOLDER_ENTRY* pFolder = &m_pFolders[folderIndex];
    if (pFirstFileOut)
    {
        *pFirstFileOut = pFolder->firstFile;
    }
    if (pNumFilesOut)
    {
        *pNumFilesOut = pFolder->numFiles;
    }
    return ((pFolder->firstFile >= 0) && (pFolder->numFiles > 0)) ? S_OK : HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT FileFileList::GetFolderParentFolderIndex(__in int folderIndex, __out int* pParentFolderIndexOut) const
{
    RETURN_HR_IF(E_INVALIDARG, (folderIndex < 0) || (folderIndex > m_pHeader->numFolderEntries - 1) || (pParentFolderIndexOut == nullptr));

    *pParentFolderIndexOut = m_pFolders[folderIndex].parentFolderIndex;
    return ((*pParentFolderIndexOut) >= 0) ? S_OK : HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT FileFileList::GetFileParentFolderIndex(__in int fileIndex, __out int* pParentFolderIndexOut) const
{
    RETURN_HR_IF(E_INVALIDARG, (fileIndex < 0) || (fileIndex > m_pHeader->numFileEntries - 1) || (pParentFolderIndexOut == nullptr));

    *pParentFolderIndexOut = m_pFiles[fileIndex].parentFolderIndex;
    return ((*pParentFolderIndexOut) >= 0) ? S_OK : HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT FileFileList::GetFilePath(__in int fileIndex, __inout StringResult* pPathOut) const
{
    return GetFilePath(fileIndex, pPathOut, nullptr);
}

HRESULT FileFileList::GetFilePath(__in int fileIndex, __inout StringResult* pPathOut, _Out_opt_ UINT16* pFlags) const
{
    // The function is intened to handle the flags in addition to the file path for supporting
    // preload set during resource pack merge. If there is more that to be returned, then consider
    // creating separate FileInfoResult object.
    RETURN_HR_IF(E_INVALIDARG, (pPathOut == nullptr) || (fileIndex < 1));

    // fileIndex is based on the its entry from the list so it is 0 based in the fileformat, however
    // ResourceMap reference of fileIndex is 1 based since 0 mean its own file in the runtime.
    int fileBasedFileIndex = fileIndex - 1;

    if (fileBasedFileIndex - 1 >= GetTotalNumFiles())
    {
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    // We'll have to build up the file name from back to front.  First we
    // make sure that our StringResult contains a buffer with enough room
    // for our full path.
    const DEFFILE_FILELIST_FILE_ENTRY* pFile = &m_pFiles[fileBasedFileIndex];
    int cchNext = pFile->cchFullPath;
    PWSTR pPath;
    RETURN_IF_FAILED(pPathOut->SetEmptyContents(pFile->cchFullPath + 1, &pPath, NULL));

    // Remember, we're writing from back to front.
    // First, write the NULL terminator.
    pPath[cchNext] = L'\0';

    // Make sure the file name fits in the buffer and then copy it
    cchNext -= pFile->cchName;
    RETURN_HR_IF(E_ABORT, cchNext < 0);
    RETURN_IF_FAILED(CopyNameSegment(0, pFile->nameOffset, pFile->cchName, &pPath[cchNext]));

    // If we aren't at the beginning of the string, prepend a backslash
    if (cchNext > 0)
    {
        pPath[--cchNext] = L'\\';
    }

    // Now walk the tree and write our parent folders...
    const DEFFILE_FILELIST_FOLDER_ENTRY* pFolder = NULL;
    int folderIndex = pFile->parentFolderIndex;

    while (folderIndex >= 0)
    {
        // Make sure our folder reference is legal
        if (folderIndex >= GetTotalNumFolders())
        {
            return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
        }
        pFolder = &m_pFolders[folderIndex];
        cchNext -= pFolder->cchName;

        // Now make sure that the folder name fits and then copy it.
        RETURN_HR_IF(E_ABORT, cchNext < 0);
        RETURN_IF_FAILED(CopyNameSegment(0, pFolder->nameOffset, pFolder->cchName, &pPath[cchNext]));

        // If we aren't at the beginning of the string, prepend a backslash
        if (cchNext > 0)
        {
            pPath[--cchNext] = L'\\';
        }
        folderIndex = pFolder->parentFolderIndex;
    }

    // We should be at the start of the buffer.
    // Fail if we aren't.
    RETURN_HR_IF(E_ABORT, cchNext != 0);

    if (pFlags)
    {
        *pFlags = pFile->flags;
    }

    return S_OK;
}

HRESULT FileFileList::GetFolderPath(__in int folderIndex, __inout StringResult* pPathOut) const
{
    RETURN_HR_IF(E_INVALIDARG, (pPathOut == nullptr) || (folderIndex < 0));

    if (folderIndex >= GetTotalNumFolders())
    {
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    // We'll have to build up the path from back to front.  First we
    // make sure that our StringResult contains a buffer with enough room
    // for our full path.
    const DEFFILE_FILELIST_FOLDER_ENTRY* pFolder = &m_pFolders[folderIndex];
    int cchNext = pFolder->cchFullPath;
    PWSTR pPath;
    RETURN_IF_FAILED(pPathOut->SetEmptyContents(pFolder->cchFullPath + 1, &pPath, NULL));

    // Remember, we're writing from back to front.
    // First, write the NULL terminator.
    pPath[cchNext] = L'\0';

    while (folderIndex >= 0)
    {
        // Make sure our folder reference is legal
        if (folderIndex >= GetTotalNumFolders())
        {
            return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
        }
        pFolder = &m_pFolders[folderIndex];
        cchNext -= pFolder->cchName;

        // Now make sure that the folder name fits in the remaining buffer
        // and then copy it.
        RETURN_HR_IF(E_ABORT, cchNext < 0);
        RETURN_IF_FAILED(CopyNameSegment(0, pFolder->nameOffset, pFolder->cchName, &pPath[cchNext]));

        // If we aren't at the beginning of the string, prepend a backslash
        if (cchNext > 0)
        {
            pPath[--cchNext] = L'\\';
        }

        folderIndex = pFolder->parentFolderIndex;
    }

    // We should be at the start of the buffer.
    // Fail if we aren't.
    RETURN_HR_IF(E_ABORT, cchNext != 0);

    return S_OK;
}

HRESULT FileFileList::Validate(__in_bcount(cbData) const void* pData, __in size_t cbData)
{
    RETURN_HR_IF(E_INVALIDARG, (pData == nullptr) || (cbData < sizeof(DEFFILE_FILELIST_HEADER)));

    const DEFFILE_FILELIST_HEADER* pHeader = reinterpret_cast<const DEFFILE_FILELIST_HEADER*>(pData);
    int minSize = sizeof(DEFFILE_FILELIST_HEADER) + pHeader->numFolderEntries * sizeof(DEFFILE_FILELIST_FOLDER_ENTRY) +
                  pHeader->numFileEntries * sizeof(DEFFILE_FILELIST_FILE_ENTRY) + pHeader->cchNamesPool * sizeof(WCHAR);
    minSize = _DEFFILE_PAD_SECTION(minSize);
    // Could also validate internal structure here.
    if (pHeader->numFolderEntries == 0 && pHeader->numFileEntries == 0)
    {

        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    if ((minSize > 0) && (((UINT32)minSize) <= cbData))
    {
        return S_OK;
    }
    else
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }
}

} // namespace Microsoft::Resources