// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    /*!
     * \defgroup DefFile_FileList Common file structure for information about collections of files.
     * @{
     */

    /*
      * NOTE:   These structures are all intended to be mapped directly into memory.  Always
      * use types with fixed sizes (e.g. INT32 instead of INT) and be careful to maintain natural
      * alignment across all architectures (i.e. insert padding if necessary).
      */

    //! Helper structure used to build specific file sections that contain lists of files.

    /*!
     * Index of a file in a file list.
     */
    typedef UINT16 DEFFILE_FILE_INDEX;
    __declspec(selectany) extern const DEFFILE_FILE_INDEX DEFFILE_MAX_FILE_INDEX = 0x7ffe;

    // Accepted FileInfo flag
    __declspec(selectany) extern const UINT16 INPLACE_MERGE_PRELOAD = 0x01;
    __declspec(selectany) extern const UINT16 INPLACE_AUTOMERGE = 0x02;
    /*!
     * The DEFFILE_FILELIST_HEADER describes a structured store of folder and file names
     * that defines indices for each file and folder that it contains.
     *
     * In a UID file, a file list is laid out as follows:
     * - DEFFILE_FILELIST_HEADER        hdr;
     * - DEFFILE_FILELIST_FOLDER_ENTRY  folders[hdr.sizeFolderEntries]
     * - DEFFILE_FILELIST_FILE_ENTRY    files[hdr.sizeFileEntries]
     *
     */
    typedef struct _DEFFILE_FILELIST_HEADER
    {
        UINT16 numRootFolders; //<! Reserved, must be 0
        UINT16 numFolderEntries; //<! Number of folder entries in use in the directory entries table.
        UINT16 numFileEntries; //<! Number of entries in use in the file entries table.
        UINT16 cchLongestPath; //<! Size of the longest complete path of any file or folder in the file list.
        UINT32 cchNamesPool; //<! Size of the string pool section that contains folder and file names, in wchar.
    } DEFFILE_FILELIST_HEADER, *PDEFFILE_FILELIST_HEADER;

    typedef struct _DEFFILE_FILELIST_HEADER_EX
    {
        UINT16 numRootFolders; //<! Reserved, must be 0
        UINT16 numFolderEntries; //<! Number of folder entries in use in the directory entries table.
        UINT16 numFileEntries; //<! Number of entries in use in the file entries table.
        UINT16 cchLongestPath; //<! Size of the longest complete path of any file or folder in the file list.
        UINT32 cchUtf16NamesPool; //<! Size of the string pool section that contains UTF-16 folder in filenames, in wchar
        UINT32 cchAsciiNamesPool; //<! Size of the string pool section that contains ascii folder and file names, in char
    } DEFFILE_FILELIST_HEADER_EX, *PDEFFILE_FILELIST_HEADER_EX;

    typedef struct _DEFFILE_FILELIST_FOLDER_ENTRY
    {
        UINT16 flags; //<! Reserved, must be 0.
        INT16 parentFolderIndex; //<! Index of the parent of this folder.
        UINT16 numSubfolders; //<! Number of subfolders
        INT16 firstSubfolder; //<! Index in the folders array of the first sub-folder
        UINT16 numFiles; //<! Number of files
        INT16 firstFile; //<! Index in the files array of the first file.
        UINT16 cchName; //<! Length of the name of the file itself, in characters.
        UINT16 cchFullPath; //<! Length (in characters) of the full path to this folder.
        UINT32 nameOffset; //<! Offset of the name of this folder in the associated string pool.
    } DEFFILE_FILELIST_FOLDER_ENTRY, *PDEFFILE_FILELIST_FOLDER_ENTRY;

    typedef struct _DEFFILE_FILELIST_FILE_ENTRY
    {
        UINT16 flags; //<! Flags of the FileInfo
        INT16 parentFolderIndex; //<! Index of the folder that contains this file.
        UINT16 cchFullPath; //<! Length (in characters) of the full path to this file.
        UINT16 cchName; //<! Length of the name of the folder itself, in characters.
        UINT32 nameOffset; //<! Offset of the name of this file in the associated string pool.
    } DEFFILE_FILELIST_FILE_ENTRY, *PDEFFILE_FILELIST_FILE_ENTRY;

    //! Type for a a section containing a file list with no additional data.
    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID
        gFileListSectionType = {'[', 'd', 'e', 'f', '_', 'f', 'i', 'l', 'e', '_', 'l', 'i', 's', 't', ']'};

    //! Type for a a section containing a file list with no additional data,
    //  in which filenames are stored in ASCII where possible.
    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID
        gFileListExSectionType = {'[', 'd', 'e', 'f', '_', 'f', 'i', 'l', 'e', '_', 'l', 's', 't', 'x', ']'};

    //! Type for a section containing a generic file list plus size and access time information.
    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID
        gFileInfoSectionType = {'[', 'd', 'e', 'f', '_', 'f', 'i', 'l', 'e', '_', 'i', 'n', 'f', 'o', ']'};

    //! Lists the sizes and last access time of a collection of files.
    /*!
     * A File Info section is laid out in the file as follows:
     *      DEFFILE_FILEINFO_SECTION_HEADER header;
     *      [ Generic File List ]           files;
     *      DEFFILE_FILEINFO_FILE_ENTRY     fileInfo[files.hdr.sizeFileEntries];
     * 
     * File Info sections can be chained together, so that files can be expanded
     * without shifting large chunks of data.  If header.nextSectionIndex is defined,
     * it specifies the index of another FileInfo section that contains information
     * about additional files
     */
    typedef struct _DEFFILE_FILEINFO_SECTION_HEADER
    {
        DEFFILE_SECTION_INDEX nextSectionIndex; //<! Index of an
        UINT16 pad; //<! Reserved, must be 0
        UINT32 pad1; //<! Reserved, must be 0
    } DEFFILE_FILEINFO_SECTION_HEADER, *PDEFFILE_FILEINFO_SECTION_HEADER;

    //! Contains the size in bytes and last modified time of the associated file.
    typedef struct _DEFFILE_FILEINFO_FILE_ENTRY
    {
        UINT64 filesize;
        UINT64 lastModifiedTime;
    } DEFFILE_FILEINFO_FILE_ENTRY, *PDEFFILE_FILEINFO_FILE_ENTRY;

    /*@}*/

#ifdef __cplusplus
}
#endif
