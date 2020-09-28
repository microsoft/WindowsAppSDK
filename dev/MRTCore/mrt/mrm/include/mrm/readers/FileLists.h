// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "mrm/common/file/FileBase.h"
#include "mrm/common/file/FileListBase.h"

namespace Microsoft::Resources
{

/*!
     * \addtogroup DefFile_Readers
     * @{
     * \defgroup DefFile_FileFileList Base classes for storing information about collections of files.
     * @{
     */

//! Represents a list of files and folders
class IFileList
{
public:
    typedef DEFFILE_FILE_INDEX FileIndex;
    static const FileIndex MaxFileIndex = DEFFILE_MAX_FILE_INDEX;

    //! Gets the number of root folders in the file list.
    virtual int GetNumRootFolders() const = 0;

    //! Gets the total number of folders in the file list.
    virtual int GetTotalNumFolders() const = 0;

    //! Gets the total number of files in the file list.
    virtual int GetTotalNumFiles() const = 0;

    //! Gets the length in characters of the longest absolute path stored in this file list.
    virtual int GetLongestPath() const = 0;

    /*! 
         * Determines if a supplied file index is valid.
         *
         * \param indexIn
         * The index to be tested.
         *
         * \param pStatus
         * Reports extended status if an error occurs.
         *
         * \return bool
         * Returns true if supplied index refers to a valid file
         * in this file list, false otherwise or if an error 
         * occurs.
         */
    virtual bool IsValidFileIndex(__inout int indexIn) const;

    /*! 
         * Determines if a supplied folder index is valid.
         * 
         * \param indexIn
         * The index to be tested.
         *
         * \param pStatus
         * Reports extended status if an error occurs.
         *
         * \return bool
         * Returns true if supplied index refers to a valid folder
         * in this file list, false otherwise or if an error 
         * occurs.
         */
    virtual bool IsValidFolderIndex(__inout int indexIn) const;

    /*!
         * Gets the name of a folder specified by index.
         *
         * \param folderIndex
         * Index of the folder to be queried.
         * 
         * \param pStatus
         * Reports extended status if an error occurs.
         *
         * \param pNameOut
         * Returns the name of the folder.
         */
    virtual HRESULT GetFolderName(__in int folderIndex, __inout StringResult* pNameOut) const = 0;

    /*! 
         * Gets the name of a file specified by index.
         * \param fileIndex
         * Index of the file to be queried.
         * 
         * \param pStatus
         * Reports extended status if an error occurs.
         *
         * \param pNameOut
         * Returns the name of the file.
         *
         * \return bool
         * Returns true on success, false if an error occurs.
         */
    virtual HRESULT GetFileName(__in int fileIndex, __inout StringResult* pNameOut) const = 0;

    /*!
         * Gets subfolder information for one of the folders in a file list.
         *
         * \param folderIndex
         * Index of the folder to be queried.
         *
         * \param pStatus
         * Reports extended status if an error occurs.
         * 
         * \param pFirstSubfolderOut
         * Returns the index of the first subfolder, or -1 if the specified
         * folder has no subfolders.
         *
         * \param pNumSubfoldersOut
         * Returns the number of subfolders, or 0 if the specified folder
         * has no subfolders.
         *
         * \return bool
         * Returns true on success, false if an error occurs.
         */
    virtual HRESULT GetSubfolders(__in int folderIndex, __out_opt int* pFirstSubfolderOut, __out_opt int* pNumSubfoldersOut) const = 0;

    /*!
         * Gets file information for one of the folders in a file list.
         *
         * \param folderIndex
         * Index of the folder to be queried.
         *
         * \param pStatus
         * Reports extended status if an error occurs.
         * 
         * \param pFirstFileOut
         * Returns the index of the first file, or -1 if the specified
         * folder contains no files.
         *
         * \param pNumFilesOut
         * Returns the number of files, or 0 if the specified folder
         * has no files.
         *
         * \return bool
         * Returns true on success, false if an error occurs.
         */
    virtual HRESULT GetFiles(__in int folderIndex, __out_opt int* pFirstFileOut, __out_opt int* pNumFilesOut) const = 0;

    /*! 
         * Gets the parent of a folder.  Both the folder and the parent
         * are specified by index.
         *
         * \param folderIndex
         * Index of the folder to be queried.
         *
         * \param pStatus
         * Reports extended status if an error occurs.  Does not 
         * report an error if the folder in question is a root
         * folder with an absolute path.
         *
         * \param pParentFolderIndexOut
         * Returns the index of the parent folder, or -1 if the folder
         * in question is a root folder.
         * 
         * \return bool
         * Returns true if a valid parent is returned.  Returns false if
         * the folder in question is a root folder or if an error occurs.
         */
    virtual HRESULT GetFolderParentFolderIndex(__in int folderIndex, __out int* pParentFolderIndexOut) const = 0;

    /*!
         * Gets the parent folder of a file.  Both the file and parent folder
         * are specified by index.
         *
         * \param fileIndex
         * Index of the file to be queried.
         *
         * \param pStatus
         * Reports extended status if an error occurs.
         *
         * \param pParentFolderIndexOut
         * Returns the index of the parent folder.
         * 
         * \return bool
         * Returns true if a valid parent is returned, or false
         * if an error occurs.
         */
    virtual HRESULT GetFileParentFolderIndex(__in int fileIndex, __out int* pParentFolderIndexOut) const = 0;

    /*! 
         * Gets the full, absolute path of a file specified by index.
         *
         * \param fileIndex
         * Index of the file to be queried.
         *
         * \param pStatus
         * Reports extended status if an error occurs.
         *
         * \param pPathOut
         * Returns the path of the file.
         * 
         * \return bool
         * Returns true on success, false if an error occurs.
         */
    virtual HRESULT GetFilePath(__in int fileIndex, __inout StringResult* pPathOut) const = 0;

    /*! 
         * Gets the full, absolute path of a file specified by index.
         *
         * \param fileIndex
         * Index of the file to be queried.
         *
         * \param pStatus
         * Reports extended status if an error occurs.
         *
         * \param pPathOut
         * Returns the path of the file.
         * 
         * \param pFlag
         * Returns the flag info of the returned file
         * 
         * \return bool
         * Returns true on success, false if an error occurs.
         */
    virtual HRESULT GetFilePath(_In_ int fileIndex, _Inout_ StringResult* pPathOut, _Out_opt_ UINT16* pFlag) const = 0;

    /*!
         * Gets the full, absolute path of a folder specified by index.
         *
         * \param folderIndex
         * Index of the folder to be queried.
         *
         * \param pStatus
         * Reports extended status if an error occurs.
         *
         * \param pPathOut
         * Returns the path of the folder.
         * 
         * \return bool
         * Returns true on success, false if an error occurs.
         */
    virtual HRESULT GetFolderPath(__in int folderIndex, __inout StringResult* pPathOut) const = 0;

    /*!
         * Tries to get the file index corresponding to a supplied absolute path.
         *
         * Does not report an error if no matching file is found.
         * 
         * \param pPath
         * The path to be searched for.
         *
         * \param pStatus
         * Reports status if an error occurs.
         *
         * \param pIndexOut
         * Returns the index of the matching file, or -1 if no
         * matching file is found.
         * 
         * \return bool
         * Returns true if a matching file is found, or false
         * if an error occurs or if no matching file is found.
         */
    virtual bool TryGetFileIndex(__in PCWSTR pPath, __out int* pIndexOut) const;

    /*!
         * Tries to get the folder index corresponding to a supplied absolute path.
         * Does not report an error if no matching folder is found.
         * 
         * \param pPath
         * The path to be searched for.
         *
         * \param pStatus
         * Reports status if an error occurs.
         *
         * \param pIndexOut
         * Returns the index of the matching folder, or -1 if no
         * matching folder is found.
         * 
         * \return bool
         * Returns true if a matching folder is found, or false
         * if an error occurs or if no matching folder is found.
         */
    virtual bool TryGetFolderIndex(__in PCWSTR pPath, __out int* pIndexOut) const;

    /*!
         * Matches as much as it can from the front of a supplied path.
         * Returns the deepest matching subfolder and the number
         * of characters matched.
         *
         * Matches _only_ subfolders (i.e. requires a trailing slash), so:
         *     "\\this\that\other\dir" 
         * Matches "\\this\that\other\", even if "dir" is a valid subdirectory.
         * Add a trailing slash or use \ref TryGetFolderIndex (without a slash)
         * to match the full folder path.
         * 
         * \param pFullPath
         * The full path to be matched.
         *
         * \param pStatus
         * Reports extended status if an error occurs.   Does not report an error
         * if no matching subfolder is found.
         *
         * \param pIndexOut
         * Returns the index of the deepest matching subfolder, or -1 if no match is
         * found.
         *
         * \param pcchUsedOut
         * If non-NULL, returns the number of characters from \ref pFullPath that were
         * used by the match.
         * 
         * \return bool
         * Returns true on success, false if no matching folder is found or if an error
         * occurred.
         */
    bool TryGetPrefixFolderIndex(__in PCWSTR pFullPath, __out int* pIndexOut, __out_opt int* pcchUsedOut = NULL) const;

protected:
    IFileList() {}

    bool IsValidFolderRange(__in int startIndex, __in int numFolders) const
    {
        if ((startIndex < 0) || (numFolders < 1) || ((startIndex + numFolders) >= GetTotalNumFolders()))
        {
            return false;
        }
        return true;
    }

    bool IsValidFileRange(__in int startIndex, __in int numFiles) const
    {
        if ((startIndex < 0) || (numFiles < 1) || ((startIndex + numFiles) >= GetTotalNumFiles()))
        {
            return false;
        }
        return true;
    }
};

//! Represents a read-only file list, typically mapped in from a file.
class FileFileList : public FileSectionBase, public IFileList
{
private:
    DEFFILE_FILELIST_HEADER_EX m_header;
    const DEFFILE_FILELIST_HEADER_EX* m_pHeader;
    const DEFFILE_FILELIST_FOLDER_ENTRY* m_pFolders;
    const DEFFILE_FILELIST_FILE_ENTRY* m_pFiles;

    // Not null-terminated
    const char* m_pAsciiNames;
    const WCHAR* m_pUtf16Names;

    // It simplifies a lot of code to have a hidden
    // root folder.
    DEFFILE_FILELIST_FOLDER_ENTRY m_root;

public:
    /*!
         * Creates and initializes a \ref FileFileList from a supplied read-only data blob.
         *
         * \param pData
         * Pointer to the blob used to initialize the \ref FileFileList.
         *
         * \param cbData
         * Size of the data blob, in bytes.
         *
         * \param IDefStatus
         * Reports extended status if an error occurs.
         *
         * \return FileFileList*
         * Returns a pointer to a \ref FileFileList representing the file list
         * described by the supplied blob, or NULL if an error occurs.
         */
    static HRESULT CreateInstance(__in_bcount(cbData) const BYTE* pData, __in int cbData, _Outptr_ FileFileList** result);

    /*!
         * Allocates and initializes a \ref FileFileList from a 
         * supplied \ref IFileSection.
         *
         * \param IFileSection
         * Description of the file section containing the file list.
         *
         * \param IDefStatus
         * Reports extended status if an error occurs.
         *
         * \return FileFileList*
         * Returns a pointer to a \ref FileFileList representing the file list
         * described by the supplied file section, or NULL if an error occurs.
         */
    static HRESULT CreateInstance(__in IFileSection* pSection, _Outptr_ FileFileList** result);

    /*! 
         * Delete a \ref FileFileList.
         */
    virtual ~FileFileList() {}

    /*!
         * \name IFileList Implementation
         * @{
         */

    //! \see IFileList::GetNumRootFolders
    int GetNumRootFolders() const { return m_pHeader->numRootFolders; }

    //! \see IFileList::GetTotalNumFolders
    int GetTotalNumFolders() const { return m_pHeader->numFolderEntries; }

    //! \see IFileList::GetTotalNumFiles
    int GetTotalNumFiles() const { return m_pHeader->numFileEntries; }

    //! \see IFileList::GetLongestPath
    int GetLongestPath() const { return m_pHeader->cchLongestPath; }

    //! \see IFileList::GetFolderName
    HRESULT GetFolderName(__in int folderIndex, __inout StringResult* pNameOut) const;

    //! \see IFileList::GetFileName
    HRESULT GetFileName(__in int fileIndex, __inout StringResult* pNameOut) const;

    //! \see IFileList::GetSubfolders
    HRESULT GetSubfolders(__in int folderIndex, __out_opt int* pFirstSubfolderOut, __out_opt int* pNumSubfoldersOut) const;

    //! \see IFileList::GetFiles
    HRESULT GetFiles(__in int folderIndex, __out_opt int* pFirstFileOut, __out_opt int* pNumFilesOut) const;

    //! \see IFileList::GetFolderParentIndex
    HRESULT GetFolderParentFolderIndex(__in int folderIndex, __out int* pParentFolderIndexOut) const;

    //! \see IFileList::GetFileParentFolderIndex
    HRESULT GetFileParentFolderIndex(__in int fileIndex, __out int* pParentFolderOutIndexOut) const;

    //! \see IFileList::GetFilePath
    HRESULT GetFilePath(__in int fileIndex, __inout StringResult* pPathOut) const;

    //! \see IFileList::GetFilePath
    HRESULT GetFilePath(_In_ int fileIndex, _Inout_ StringResult* pPathOut, _Out_opt_ UINT16* pFlag) const;

    //! \see IFileList::GetFolderPath
    HRESULT GetFolderPath(__in int folderIndex, __inout StringResult* pPathOut) const;

    /*!@}*/

    //! Gets the typeid for a file list section.
    static const DEFFILE_SECTION_TYPEID GetSectionTypeId();

protected:
    FileFileList();

    HRESULT Init(__in_opt const IFileSection* pSection, __in_bcount(cbData) const void* pData, __in int cbData);

    static HRESULT Validate(__in_bcount(cbData) const void* pData, __in size_t cbData);

    HRESULT CopyNameSegment(_In_ UINT32 flags, _In_ int firstCharOffset, _In_ int cchName, _Out_writes_(cchName) WCHAR* pNameOut) const
    {
        if ((flags & DEFFILE_HNAMES_FLAGS_NAME_IS_ASCII) != 0)
        {
            const char* pName;
            RETURN_IF_FAILED(GetAsciiName(firstCharOffset, cchName, &pName));
            if (pName != nullptr)
            {
                for (int i = 0; i < cchName; i++)
                {
                    pNameOut[i] = pName[i];
                }
                return S_OK;
            }
        }
        else
        {
            PCWSTR pName;
            RETURN_IF_FAILED(GetUtf16Name(firstCharOffset, cchName, &pName));
            if (pName != nullptr)
            {
                memcpy(pNameOut, pName, cchName * sizeof(WCHAR));
                return S_OK;
            }
        }
        return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
    }

    HRESULT GetAsciiName(_In_ int firstChar, _In_ int cchName, _Out_ PCSTR* result) const
    {
        *result = nullptr;

        // report an error if the string is out of range or
        // isn't null terminated
        if ((firstChar < 0) || (cchName < 1) || ((firstChar + cchName) >= static_cast<int>(m_pHeader->cchAsciiNamesPool)) ||
            (m_pAsciiNames[firstChar + cchName] != L'\0'))
        {
            return E_ABORT;
        }
        *result = &m_pAsciiNames[firstChar];
        return S_OK;
    }

    HRESULT GetUtf16Name(_In_ int firstChar, _In_ int cchName, _Out_ PCWSTR* result) const
    {
        *result = nullptr;

        // report an error if the string is out of range or
        // isn't null terminated
        if ((firstChar < 0) || (cchName < 1) || ((firstChar + cchName) >= static_cast<int>(m_pHeader->cchUtf16NamesPool)) ||
            (m_pUtf16Names[firstChar + cchName] != L'\0'))
        {
            return E_ABORT;
        }
        *result = &m_pUtf16Names[firstChar];
        return S_OK;
    }
};

} // namespace Microsoft::Resources
