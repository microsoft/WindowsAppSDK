// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "mrm/readers/FileLists.h"
#include "mrm/build/FileBuilder.h"
#include "mrm/build/WriteableStringPool.h"

namespace Microsoft::Resources::Build
{

/*!
     * \addtogroup DefBuild
     * @{
     * \addtogroup DefBuild_Common
     * @{
     * \defgroup FileListBuilder File list section builder
     * @{
     */

class FolderInfo;

/*! 
     * Base class for per-file private data.  Must be subclassed and
     * cannot be instantiated directly.
     * 
     * Per-file private data is identified by the object that
     * owns it and a data index.  The data index is used to enforce uniqueness
     * when appropriate and cannot be negative.  Otherwise the interpretation
     * of the index is left to the section that define the data.
     */
class FileInfoPrivateData : public DefObject
{
private:
    const void* m_pOwner;
    int m_index;
    FileInfoPrivateData* m_pNext;

protected:
    FileInfoPrivateData(__in const void* pOwner, __in int index);

public:
    /*!
         * Deletes this \ref FileInfoPrivateData and any that are
         * linked to it.
         */
    virtual ~FileInfoPrivateData();

    /*! 
         * Gets the owner of this private data.
         * 
         * \return const IFileSection*
         * Returns a pointer to the object that owns this private
         * data.
         */
    const void* GetOwner() const { return m_pOwner; }

    /*! 
         * Gets the index of this private data.
         * 
         * \return const int
         * Returns the owner-supplied index of this private data.
         */
    const int GetIndex() const { return m_index; }

    /*! 
         * Determines if a this \ref FileInfoPrivateData object matches
         * a supplied owner and index.
         * 
         * \param pOwner
         * Pointer to the desired owner, or NULL to accept any owner. 
         * 
         * \param index
         * Specifies the \ref index to be matched, or a value less than 0
         * to accept any index.
         *
         * \return bool
         * Returns true if the owner and index match, false otherwise
         * or if an error occurs.
         * 
         * If pOwner is NULL, index _must_ be less than 0, or an
         * INVALID_ARG error results.
         */
    bool Matches(__in_opt const void* pOwner, __in int index) const
    {
        if (!pOwner && (index >= 0))
        {
            return false;
        }
        return ((!pOwner) || (pOwner == m_pOwner)) && ((index < 0) || (index == m_index));
    }

    /*! 
         * Determines if a this object matches a supplied \ref FileInfoPrivateData.
         * A \ref FileInfePrivateData matches if both the owner and index are
         * equal to that of this object. 
         * 
         * \param pOther
         * Pointer to \ref FileInfoPrivateData to be matched.
         * 
         * \return bool
         * Returns true if the supplied \ref FileInfoPrivate data matches this
         * one, false otherwise or if an error occurs.
         */
    bool Matches(__in FileInfoPrivateData* pOther) const
    {
        if (pOther == nullptr)
        {
            return false;
        }
        return pOther->Matches(m_pOwner, m_index);
    }

    /*! 
         * Sets the next chained private element for this object.
         * 
         * \param pNext
         * Pointer to the \ref FileInfoPrivateData to be added.
         * 
         * \return HRESULT
         * Returns S_OK if the private data was added, failure if an
         * error occurred.
         *
         * Fails with an ENTRY_ALREADY_EXISTS error if this object
         * already has chained data.
         */
    HRESULT SetNext(__in_opt FileInfoPrivateData* pNext);

    /*! 
         * Gets the next chained \ref FileInfoPrivateData.
         * 
         * \return FileInfoPrivateData*
         * Returns a pointer to the next chained \ref FileInfoPrivateData,
         * or NULL if no chained elements are present.
         */
    FileInfoPrivateData* GetNext() const { return m_pNext; }

    /*! 
         * Gets the next chained private \ref FileInfoPrivateData element
         * that matches the supplied criteria.
         * 
         * \param pOwner
         * Specifies the owner to be matched, or NULL to match any owner.
         * 
         * \param index
         * Specifies the private data index to be matched, or a value less than
         * zero to match any index.
         *
         * \param ppDataOut
         * Returns a pointer to the requested object.  Returns NULL if no
         * matching element was found or if an error occurs.
         *
         * \return bool
         * Returns true if matching data was found.  Returns false if no
         * matching data was found or if an error occurs.   If an error
         * occurs, pStatus will contain extended information.
         *
         * If pParentSection is NULL, index must be less than 0 or an
         * INVALID_ARG results.
         */
    bool TryGetNext(__in_opt const void* pOwner, __in int index, __out FileInfoPrivateData** ppDataOut) const;

    /*! 
         * Gets the next chained private \ref FileInfoPrivateData element
         * with the specified owner.
         * 
         * \param pOwner
         * Specifies the owner to be matched, or NULL to match any owner.
         *
         * \param ppDataOut
         * Returns a pointer to the requested object.  Returns NULL if no
         * matching element was found or if an error occurs.
         *
         * \return bool
         * Returns true if matching data was found.  Returns false if no
         * matching data was found or if an error occurs.   If an error
         * occurs, pStatus will contain extended information.
         */
    bool TryGetNext(__in_opt const void* pOwner, __out FileInfoPrivateData** ppDataOut) const { return TryGetNext(pOwner, -1, ppDataOut); }
};

//! Build-time information about a single file contained in a FileListBuilder.
class FileInfo : public DefObject
{
protected:
    PWSTR m_pName;
    FolderInfo* m_pParentFolder;
    int m_index;
    FileInfoPrivateData* m_pPrivates;
    UINT16 m_flags;
    bool m_nameIsAscii;

    FileInfo(__in FolderInfo* pParent);

    HRESULT Init(_In_ PCWSTR name);

public:
    virtual ~FileInfo();

    /*!
         * Constructs a new FileInfo with a specified name and parent folder.
         * This constructor just creates the object.
         * It does not validate names, check for collisions or
         * add add it to the parent folder.   To ensure proper
         * semantics and consistency, use FolderInfo::GetOrAddFile
         * to create new files.
         * 
         * \param pName
         * The name of the file to be added.
         * 
         * \param pParent
         * Parent folder that will contain the new file.
         *
         * \param result
         * Returns a pointer to the new FileInfo, or NULL if an error
         * occurs.
         * 
         * \return HRESULT
         */
    static HRESULT CreateInstance(__in PCWSTR pName, __in FolderInfo* pParent, _Outptr_ FileInfo** result);

    /*!
         * Gets the name of the file.  Does not include path components other than the file name itself.
         *
         * \param pNameOut
         * Returns the name of the file.
         * 
         * \return HRESULT
         * Returns S_OK for success, failure if an error occurs.
         */
    HRESULT GetFileName(__inout StringResult* pNameOut) const;

    /*!
         * Gets the name of the file.  Does not include path components other than the file name itself.
         */
    PCWSTR GetFileName() const { return m_pName; }

    /*!
         * Gets the parent folder of this file.
         */
    FolderInfo* GetParentFolder() const { return m_pParentFolder; }

    /*! 
         * Gets the full path of a file.
         *
         * \param pStatus
         * Reports error details if an error occurs.
         *
         * \param pPathOut
         * Returns the full (absolute) path of the referenced file.
         * 
         * \return bool
         * Returns true for success, false if an error occurs.
         */
    HRESULT GetFullPath(__inout StringResult* pPathOut) const;

    /*! 
         * Gets the index of this file in the generated file list section.
         * Note that the file index is typically undefined (-1) until the file
         * list section is finalized.
         *
         * \return int
         * Returns the index of this file in the generated file list section, or
         * -1 if the file list section has not been finalized.
         */
    int GetIndex() const { return m_index; }

    /*!
         * Sets the index of this file in the generated file list section.
         *
         * \param index
         * The index to be assigned.
         */
    void SetIndex(int index) { m_index = index; }

    /*! 
         * Gets the head of the list of private data associated with this
         * file entry.
         * 
         * \return const FileInfoPrivateData*
         * The first element in the list of private data associated with this
         * file entry.
         */
    FileInfoPrivateData* GetPrivateData() const { return m_pPrivates; }

    /*! 
         * Gets the first element associated with a specified owner from the 
         * private data list for this file element.
         * 
         * \param pOwner
         * Pointer to the desired owner, or NULL to match any owner.
         * 
         * \param ppDataOut
         * Returns a pointer to the requested private data structure.  Returns
         * NULL if no matching private data is found or if an error occurs.
         *
         * \return bool
         * Returns true if matching data was found.  Returns false if no
         * matching data was found or if an error occurs.   If an error
         * occurs, pStatus will contain extended information.

         */
    bool TryGetPrivateData(__in_opt const void* pOwner, __out FileInfoPrivateData** ppDataOut) const
    {
        return TryGetPrivateData(pOwner, -1, ppDataOut);
    }

    /*! 
         * Gets the first element with a specified owner and index from the 
         * private data list for this file element.
         * 
         * \param pOwner
         * Pointer to the desired owner, or NULL to accept any owner.
         *
         * \param index
         * Index of the private data to be found, or a negative value to
         * accept any index.
         * 
         * \param ppDataOut
         * Returns a pointer to the requested private data structure.  Returns
         * NULL if no matching private data is found or if an error occurs.
         *
         * \return bool
         * Returns true if matching data was found.  Returns false if no
         * matching data was found or if an error occurs.   If an error
         * occurs, pStatus will contain extended information.

         */
    bool TryGetPrivateData(__in_opt const void* pOwner, __in int index, __out FileInfoPrivateData** ppDataOut) const;

    /*! 
         * Adds a supplied \ref FileInfoPrivateData to the chain
         * of private data associated with this file.
         * 
         * \param pPrivate
         * The \ref FileInfoPrivateData to be added.
         *
         * \param allowDuplicates
         * If true, the private data will be added even if data already 
         * exists with the same parent and index.  If false, adding duplicate
         * private data yields an E_DEF_ENTRY_ALREADY_EXISTS error.
         * 
         * \return HRESULT
         * Returns S_OK if the private data was successfully added, failure
         * otherwise.
         */
    HRESULT AddPrivateData(__in FileInfoPrivateData* pPrivate, __in bool allowDuplicates);

    /*! 
         * Get the flag information that can have preload set
         * 
         * \return bool
         * Returns UINT16 flags, it always return success
         */
    UINT16 GetFlag() const { return m_flags; }

    /*!
         * Sets the flag of this file if it exist, or the flag is 0 as default.
         *
         * \param index
         * The flag to be assigned.
         */
    void SetFlag(UINT16 flag) { m_flags = flag; }

    bool NameIsAscii() const { return m_nameIsAscii; }
};

//! Build-time information about a single folder in a FileListBuilder.
class FolderInfo : public DefObject
{
protected:
    PWSTR m_pName;
    FolderInfo* m_pParentFolder;

    int m_numSubfolders;
    int m_sizeSubfolders;
    FolderInfo** m_pSubfolders;

    int m_numFiles;
    int m_sizeFiles;
    FileInfo** m_pFiles;

    int m_totalNumFiles;
    int m_totalNumFolders;

    int m_index;

    bool m_nameIsAscii;

    FolderInfo(__in PCWSTR pName, __in_opt FolderInfo* pParent);

    HRESULT Init(_In_ PCWSTR name);

    bool NoteSubfolderChanges(__in int numFoldersAdded, __in int numFilesAdded);

    HRESULT ExtendSubfolders();

    HRESULT ExtendFiles();

public:
    virtual ~FolderInfo();

    /*!
         * Sets the index of this file in the generated file list section.
         *
         * Note that this constructor just creates the object.
         * It does not validate names, check for collisions or
         * add add it to the parent folder.   To ensure proper
         * semantics and consistency, use FolderInfo::GetOrAddSubfolder
         * to create new subfolders.
         * 
         * \param pName
         * The name of the folder to be added.
         * 
         * \param pParent
         * Parent folder that will contain the new subfolder.
         *
         * \param result
         * Returns a pointer to the new FolderInfo, or NULL if an error
         * occurs.
         * 
         * \return HRESULT
         */
    static HRESULT CreateInstance(__in PCWSTR pName, __in FolderInfo* pParent, _Outptr_ FolderInfo** result);

    /*!
         * Sets the index of this file in the generated file list section.
         *
         * \param result
         * Returns a pointer to the new FolderInfo, or NULL if an error
         * occurs.
         * 
         * \return HRESULT
         */
    static HRESULT NewRootFolder(_Outptr_ FolderInfo** result);

    /*!
         * Gets the base name of the folder.
         * 
         * \param pNameOut
         * Returns the base name of the referenced folder.
         *
         * \return bool
         * Returns true on success, false if an error occurs.
         */
    HRESULT GetFolderName(__inout StringResult* pNameOut) const;

    //! Gets the base name of the folder.
    PCWSTR GetFolderName() const { return m_pName; }

    /*! 
         * Gets the number of immediate subfolders.
         * Does not include children of subfolders of the referenced folder.
         * 
         * \return int
         * Returns the number of referenced subfolders.
         */
    int GetNumSubfolders() const { return m_numSubfolders; }

    /*!
         * Gets the number of files contained in the referenced folder itself.
         * Does not include files contained in subfolders.
         * 
         * \return int
         * Returns the number of referenced files.
         */
    int GetNumFiles() const { return m_numFiles; }

    /*! 
         * Gets the total number of referenced folders at or below the supplied folder.
         * Includes the folder itself, plus all children of subfolders.
         * 
         * \return int
         * Returns the total number of referenced folders at or below the
         * supplied folder. 
         */
    int GetTotalNumFolders() const { return m_totalNumFolders; }

    /*!
         * Gets the total number of referenced files at or below the supplied folder.
         *
         * Includes referenced files in the folder itself, plus any referenced files
         * contained in subfolders of any depth.
         * 
         * \return int
         * Returns the total number of referenced files at or below the
         * supplied folder.
         */
    int GetTotalNumFiles() const { return m_totalNumFiles; }

    //! Gets the parent of this folder, if defined.
    FolderInfo* GetParentFolder() const { return m_pParentFolder; }

    /*! 
         * Gets the full absolute path of the supplied folder.
         *
         * \param pPathOut
         * Returns the full absolute path of the supplied folder.
         * 
         * \return HRESULT
         * Returns S_OK on success, failure if an error occurs.
         */
    HRESULT GetFullPath(__inout StringResult* pPathOut) const;

    /*!
         * Gets a subfolder by index.
         *
         * \param index
         * Index of the folder to be returned.
         *
         * \param result
         * Returns a pointer to an IFolderInfo describing 
         * the requested subdirectory, or NULL if an error occurs.
         *
         * \return HRESULT
         */
    HRESULT GetSubfolder(_In_ int index, _Out_ FolderInfo** result) const;

    /*!
         * Gets a subfolder by name.
         *
         * Reports an error if no matching folder is found.
         * \param pName
         * The name of the subfolder to be returned.
         *
         * \param result
         * Returns a pointer to an IFolderInfo describing
         * the requested subdirectory, or NULL if an error occurs.
         * 
         * \return HRESULT
         * Returns E_DEF_FOLDER_NOT_FOUND if no matching folder is found.
         */
    HRESULT GetSubfolder(_In_ PCWSTR pName, _Out_ FolderInfo** result) const;

    /*!
         * Tries to get a subfolder by name.
         *
         * Returns false but doesn not set an error if no matching
         * folder is found.
         * 
         * \param pName
         * The name of the subfolder to be returned.
         *
         * \param ppFolderOut
         * Returns the matching folder, or NULL if no matching folder
         * is found. 
         *
         * \return bool
         * Returns true if a matching folder was found, false if no match
         * was found or if an error occured.
         */
    bool TryGetSubfolder(__in PCWSTR pName, __inout FolderInfo** ppFolderOut) const;

    /*! 
         * Gets the index of a subfolder by name.
         * Reports an error if no matching folder is found.
         * 
         * \param pName
         * The name of the subfolder to be returned.
         * 
         * \return int
         * Returns the integer index of the requested subdirectory,
         * or -1 if an error occurs or if the subdirectory is not found.
         */
    int GetSubfolderIndex(__in PCWSTR pName) const;

    /*!
         * Tries to get the index of a subfolder by name.
         *
         * Returns false but does not report an error if no matching
         * folder is found.
         * 
         * \param pName
         * The name of the subfolder to be returned.
         *
         * \param ppIndexOut
         * Returns the index of the matching folder, or NULL if no matching folder
         * is found. 
         *
         * \return bool
         * Returns true if a matching folder was found, false if no match
         * was found or if an error occured.
         */
    bool TryGetSubfolderIndex(__in PCWSTR pName, __out int* pIndexOut) const;

    /*!
         * Gets or adds a named subfolder to a FolderInfo. 
         *
         * If a subfolder with a matching name already exists, returns
         * the existing subfolder.  If no matching subfolder exists,
         * adds a new subfolder and returns a pointer to it.
         * 
         * \param pName
         * Name of the new subfolder.
         *
         * \param result
         * Returns a pointer to a FolderInfo describing the
         * requested subfolder.
         * 
         * \return HRESULT
         */
    HRESULT GetOrAddSubfolder(_In_ PCWSTR pName, _Out_ FolderInfo** result);

    /*!
         * Gets a referenced file by index.
         *
         * \param index
         * Index of the file to be returned.
         *
         * \param result
         * Returns a pointer to an IFileInfo describing
         * the requested file.
         * 
         * \return HRESULT
         */
    HRESULT GetFile(_In_ int index, _Out_ FileInfo** result) const;

    /*!
         * Gets a file by name.
         * Reports an error if no matching file is found.
         * 
         * \param pName
         * The name of the file to be returned.
         *
         * \param result
         * Returns a pointer to an IFileInfo describing
         * the requested file, or NULL if an error occurs.
         * 
         * \return HRESULT
         */
    HRESULT GetFile(_In_ PCWSTR index, _Out_ FileInfo** result) const;

    /*!
         * Tries to get a file by name.
         * Returns false but does not set an error if no matching
         * file is found.
         * 
         * \param pName
         * The name of the file to be returned.
         *
         * \param ppFileOut
         * Returns the matching file, or NULL if no matching file
         * is found. 
         *
         * \return bool
         * Returns true if a matching file was found, false if no match
         * was found or if an error occured.
         */
    bool TryGetFile(__in PCWSTR pName, __out FileInfo** ppFileOut) const;

    /*!
         * Gets the index of a file by name.
         * Reports an error if no matching file is found.
         * 
         * \param pName
         * The name of the file to be returned.
         * 
         * \return int
         * Returns the integer index of the requested file,
         * or -1 if an error occurs or if the file is not found.
         */
    int GetFileIndex(__in PCWSTR index) const;

    /*!
         * Tries to get the index of a file by name.
         * Returns false but does not report an error if no matching
         * file is found.
         * 
         * \param pName
         * The name of the file to be returned.
         *
         * \param ppIndexOut
         * Returns the index of the matching file, or NULL if no matching file
         * is found. 
         *
         * \return bool
         * Returns true if a matching file was found, false if no match
         * was found or if an error occured.
         */
    bool TryGetFileIndex(__in PCWSTR pName, __out int* pIndexOut) const;

    /*!
         * Gets or adds a file with the specified name to a FolderInfo.
         * If a file with a matching name already exists, returns a
         * pointer to the existing FileInfo.  If no matching file exists,
         * adds a new FileInfo and returns a pointer to it.
         * 
         * \param pName
         * Name of the new file.
         *
         * \param result
         * Returns a pointer to a FileInfo describing the
         * requested file.
         * 
         * \return HRESULT
         */
    HRESULT GetOrAddFile(_In_ PCWSTR pName, _Out_ FileInfo** result);

    /*! 
         * Gets the index of this folder in the generated file list section.
         * Note that the folder index is typically undefined (-1) until the file
         * list section is finalized.
         *
         * \return int
         * Returns the index of this folder in the generated file list section, or
         * -1 if the file list section has not been finalized.
         */
    int GetIndex() const { return m_index; }

    /*! 
         * Sets the index of this folder in the generated file list section.
         * 
         * \param index
         * The index to be assigned.
         */
    void SetIndex(int index) { m_index = index; }

    bool NameIsAscii() const { return m_nameIsAscii; }
};

/*!
     * Class used to construct a file list section.
     * The builder holds one or more "root" folders, specified as an 
     * absolute path, and any number of subfolders or files.  Subfolders
     * and files are specified by name, relative to one of the folders.
     */
class FileListBuilder : public ISectionBuilder
{
private:
    FileBuilder* m_pParentFile;
    BaseFile::SectionIndex m_sectionIndex;

    FolderInfo* m_pRootFolder;

    UINT32 m_flags;

    class FinalizedBuilder;

    int m_numFinalizedFolders;
    int m_numFinalizedFiles;
    size_t m_cchFinalizedAsciiNames;
    size_t m_cchFinalizedUtf16Names;
    mutable FinalizedBuilder* m_pFinalized;
    /*
        mutable FolderInfo**            m_pAllFolders;
        mutable FileInfo**              m_pAllFiles;
        */

protected:
    FileListBuilder(_In_ FileBuilder* pParentFile, _In_ UINT32 flags);

    HRESULT Init();

    /*!
         * Computes maximum string pool size, in bytes.
         * A string pool containing all of the strings from a specified folder
         * and all of its contents might need fewer characters than reported
         * by this function, but it will not require more.
         * 
         * \param pFolder
         * The folder to be checked.
         * 
         * \return int
         * The total size in bytes needed to hold the strings.
         */

    static size_t ComputeTotalStringsSizeInBytes(_In_ const FolderInfo* pFolder, _In_ UINT32 flags);

    /*!
         * Computes maximum string pool size for both ascii and Utf-16 strings.
         * A string pool containing all of the strings from a specified folder
         * and all of its contents might need fewer characters than reported
         * by this function, but it will not require more.
         * 
         * \param pFolder
         * The folder to be checked.
         * 
         * \return HRESULT
         */

    static HRESULT ComputeTotalStringsSize(
        _In_ const FolderInfo* pFolder,
        _In_ UINT32 flags,
        _Inout_ size_t* pCchAsciiTotal,
        _Inout_ size_t* pCchUtf16Total);

    /*!
         * Assigns indices to a folder and its contents.
         * Updates the folder itself, all of its contents, and recursively
         * updates all children. Once assigned, file and folder indices are immutable.
         * 
         * \param pFolderInfo
         * The folder to which indices will be assigned.
         * 
         * \param index
         * The index to be assigned to pFolder.
         *
         * \param pNextFolder
         * The next available index for subfolders.
         *
         * \param sizeFolders
         * The total size in elements of the subfolders array.
         *
         * \param pNextFile
         * The next available index for files.
         *
         * \param sizeFiles
         * The total size in elements of the files array.
         * 
         * \return HRESULT
         * Returns S_OK on success, failure if an error occurs.
         */
    HRESULT AssignFolderIndices(
        __in FolderInfo* pFolderInfo,
        __in int index,
        __inout UINT32* pNextFolder,
        __in UINT32 sizeFolders,
        __inout UINT32* pNextFile,
        __in UINT32 sizeFiles);

    /*!
         * Builds the in-memory representation of a folder and its contents.
         *
         * \param pFolderInfo
         * The folder to be generated.
         *
         * \param index
         * The index at which the folder itself should be generated.
         *
         * \param parentIndex
         * The index of the folder's parent.
         * 
         * \return HRESULT
         * Return S_OK on success, failure if an error occurs.
         */
    HRESULT BuildFolderInfo(
        __in const FolderInfo* pFolderInfo,
        __in int index,
        __in int parentIndex,
        __inout_ecount(sizeFolders) DEFFILE_FILELIST_FOLDER_ENTRY* pFolders,
        __inout UINT32* pNextFolder,
        __in UINT32 sizeFolders,
        __out_ecount(sizeFiles) DEFFILE_FILELIST_FILE_ENTRY* pFile,
        __inout UINT32* pNextFile,
        __in UINT32 sizeFiles,
        __in WriteableStringPool* pNames) const;

public:
    static const UINT32 BuildUtf16Only = 0x0;
    static const UINT32 BuildAsciiOrUtf16 = 0x1;
    static const UINT32 BuildEncodingFlags = 0x1;

    /*!
         * \name Constructors/Destructors
         * @{
         */

    /*!
         * Creates a new FileListBuilder.
         * Builds a file list section as part of a supplied FileBuilder.
         * 
         * \param pParentFile
         * The FileBuilder to which the section will belong.
         *
         * \param result
         * Returns a pointer to the newe FileListBuilder, or NULL
         * if an error occurs.
         * 
         * \return HRESULT
         */
    static HRESULT CreateInstance(_In_ FileBuilder* pParentFile, _In_ UINT32 flags, _Outptr_ FileListBuilder** result);

    virtual ~FileListBuilder();

    /*!@}*/

    //! Gets the number of root folders in this builder.
    int GetNumRootFolders() const;

    //! Gets the total number of folders referenced by this builder.
    int GetTotalNumFolders() const;

    //! Gets the total number of files referenced by this builder.
    int GetTotalNumFiles() const;

    /*! 
         * Gets a root folder specified by index.
         *
         * \param index
         * Index of the root folder to be returned.
         *
         * \param result
         * A FolderInfo describing the requested root
         * folder, or NULL if an error occurs.
         * 
         * \return HRESULT
         */
    HRESULT GetRootFolder(_In_ int index, _Out_ FolderInfo** result) const;

    /*!
         * Gets a root folder specified by name.
         * Reports an error if no matching folder is found.
         * 
         * \param pPath
         * Name of the root folder to be returned.
         *
         * \param result
         * A FolderInfo describing the requested root 
         * folder, or NULL if an error occurs.
         * 
         * \return HRESULT
         */
    HRESULT GetRootFolder(_In_ PCWSTR pPath, _Out_ FolderInfo** result) const;

    /*!
         * Tries to get a root folder specified by name.
         * Returns false but does not report an error if no
         * matching folder is found.
         * 
         * \param pPath
         * Name of the root folder to be returned.
         * 
         * \param ppFolderOut
         * Returns a pointer to a FolderInfo describing the
         * requested root folder, or NULL if no match is found
         * or if an error occurs.
         * 
         * \return bool
         * Returns true if a matching folder is found, false
         * if no match is found or if an error occurs.
         */
    bool TryGetRootFolder(__inout PCWSTR pPath, __inout FolderInfo** ppFolderOut) const;

    /*!
         * Gets or adds a root folder with the specified name to a FileListBuilder.
         * If a root folder with a matching name already exists,
         * returns a pointer to the existing IFolderInfo.
         * If no matching folder exists, adds a new IFolderInfo
         * and returns a pointer to it.
         * 
         * \param pPath
         * Name of the new root folder.
         *
         * \param result
         * Returns a pointer to an IFileInfo describing the
         * requested file.
         * 
         * \return HRESULT
         */
    HRESULT GetOrAddRootFolder(_In_ PCWSTR pPath, _Out_ FolderInfo** result);

    /*! 
         * Gets a folder by index.  Can only be called once the
         * builder has been finalized.
         * 
         * \param index
         * The index of the folder to be returned.
         * 
         * \param ppFolderOut
         * Returns the requested \ref FolderInfo, or NULL if an
         * error occurs.
         *
         * \return bool
         * Returns true if the requested folder is found.  Returns
         * false if an error occurs.
         */
    bool TryGetFolderByIndex(__in int index, __out FolderInfo** ppFolderOut) const;

    /*! 
         * Gets a file by index.  Can only be called once the
         * builder has been finalized.
         * 
         * \param index
         * The index of the file to be returned.
         * 
         * \param ppFileOut
         * Returns the requested \ref FileInfo, or NULL if an
         * error occurs.
         *
         * \return bool
         * Returns true if the requested folder is found.  Returns
         * false if an error occurs.
         */
    bool TryGetFileByIndex(__in int index, __out FileInfo** ppFileOut) const;

    /*! 
         * Gets an \ref IFileList that represents the contents of 
         * this builder.  The return \ref IFileList is owned by 
         * the builder and should not be deleted.
         * 
         * Can only be called once this \ref FileListBuilder
         * has been finalized. Reports a NOT_READY error if 
         * the builder has not been finalized.
         *
         * \param ppFileListOut
         * Returns a pointer to an \ref IFileList that represents
         * this file list.
         * 
         * \return HRESULT
         * Returns S_OK on success, failure if an error occurs.
         */
    HRESULT GetFileList(__out IFileList** ppFileListOut) const;

    /*! 
         * Determines if a supplied file index is valid.
         *
         * Can only be called once this \ref FileListBuilder
         * has been finalized. Reports a NOT_READY error if 
         * the builder has not been finalized.
         * 
         * \param indexIn
         * The index to be tested.
         *
         * \return bool
         * Returns true if the builder has been finalized and the
         * supplied index refers to a valid file in this file 
         * list, false otherwise.
         */
    bool IsValidFileIndex(__inout int indexIn) const;

    /*! 
         * Determines if a supplied folder index is valid.
         *
         * Can only be called once this \ref FileListBuilder
         * has been finalized. Reports a NOT_READY error if 
         * the builder has not been finalized.
         * 
         * \param indexIn
         * The index to be tested.
         *
         * \return bool
         * Returns true if the builder has been finalized and the
         * supplied index refers to a valid folder in this file 
         * list, false otherwise.
         */
    bool IsValidFolderIndex(__inout int indexIn) const;

    bool IsFinalized() const;

    /*!
         * \name ISectionBuilder Implementation
         * @{
         */

    //! Implements ISectionBuilder::IsValid
    bool IsValid() const { return true; }

    //! Implements ISectionBuilder::Finalize
    HRESULT Finalize();

    //! Implements ISectionBuilder::GetMaxSizeInBytes
    UINT32 GetMaxSizeInBytes() const;

    //! Implements ISectionBuilder::Build
    virtual HRESULT Build(_Out_writes_to_(cbBuffer, *pcbWrittenOut) VOID* pBuffer, UINT32 cbBuffer, _Out_opt_ UINT32* pcbWrittenOut) const;

    //! Implements ISectionBuilder::GetSectionType
    DEFFILE_SECTION_TYPEID GetSectionType() const { return FileFileList::GetSectionTypeId(); }

    //! Implements ISectionBuilder::GetFlags
    UINT16 GetFlags() const { return 0; }

    //! Implements ISectionBuilder::GetSectionFlags
    UINT16 GetSectionFlags() const { return 0; }

    //! Implements ISectionBuilder::GetSectionQualifier
    UINT32 GetSectionQualifier() const { return 0; }

    //! Implements ISectionBuilder::SetSectionIndex
    void SetSectionIndex(BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }

    //! Implements ISectionBuilder::GetSectionIndex
    BaseFile::SectionIndex GetSectionIndex() const { return m_sectionIndex; }
};

} // namespace Microsoft::Resources::Build
