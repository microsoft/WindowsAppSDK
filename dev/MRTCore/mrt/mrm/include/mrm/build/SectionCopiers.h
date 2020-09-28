// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "mrm/readers/RemapInfo.h"

namespace Microsoft::Resources::Build
{

/*!
     * \addtogroup DefBuild
     * @{
     * \defgroup DefBuild_SectionCopiers Copy and relocate file sections
     * @{
     * \defgroup SectionCopier Generic/base section copier
     * @{
     */

/*! 
     * The SectionCopier is an \see ISectionBuilder that copies data from
     * an existing file into a new section, possibly remapping section and
     * atom pools in the process.
     */
class SectionCopier : public ISectionBuilder
{
protected:
    const IFileSection* m_pFileSection;
    RemapInfo* m_pRemap;
    BaseFile::SectionIndex m_sectionIndex;

    SectionCopier();

    HRESULT Init(__in const IFileSection* const pFileSection, __in RemapInfo* pRemap);

public:
    /*!
         * \name Constructors & Destructors
         * @{
         */

    /*! 
         * Constructs a new section copier for an existing file section.
         * 
         * \param pFileSection
         * The \ref IFileSection "file section" to be copied.
         *
         * \param pRemap
         * Mappings for sections and atom pools.
         *
         * \param result
         * Returns the new SectionCopier, or NULL if an error occurs.
         * 
         * \return HRESULT
         */
    static HRESULT CreateInstance(_In_ const IFileSection* const pFileSection, _In_ RemapInfo* pRemap, _Outptr_ SectionCopier** result);

    virtual ~SectionCopier();

    /*!@}*/

    /*!
         * \name ISectionBuilder Implementation
         * @{
         */
    //! Implements ISectionBuilder::IsValid
    virtual bool IsValid() const { return true; }

    //! Implements ISectionBuilder::Finalize
    virtual HRESULT Finalize();

    //! Implements ISectionBuilder::GetMaxSizeInBytes
    virtual UINT32 GetMaxSizeInBytes() const;

    //! Implements ISectionBuilder::Build
    virtual HRESULT Build(__out_bcount(cbBuffer) VOID* pBuffer, UINT32 cbBuffer, __out_opt UINT32* pcbWrittenOut) const;

    //! Implements ISectionBuilder::GetSectionType
    virtual DEFFILE_SECTION_TYPEID GetSectionType() const;

    //! Implements ISectionBuilder::GetFlags
    virtual UINT16 GetFlags() const;

    //! Implements ISectionBuilder::GetSectionFlags
    virtual UINT16 GetSectionFlags() const;

    //! Implements ISectionBuilder::GetSectionQualifier
    virtual UINT32 GetSectionQualifier() const;

    //! Implements ISectionBuilder::SetSectionIndex
    virtual void SetSectionIndex(BaseFile::SectionIndex sectionIndex);

    //! Implements ISectionBuilder::GetSectionIndex
    virtual BaseFile::SectionIndex GetSectionIndex() const;

    /*!@}*/
protected:
    /*! 
         * Applies any appropriate mappings to the section data.  The
         * base implemenation does no remapping, but derived classes 
         * can override this method to provide type-specific remapping
         * behavior.  
         *
         * \param pHeader
         * Pointer to the destination section header.  Derived classes are
         * allowed to modify the qualifier, flags and sectionFlags fields of
         * the section header.
         *
         * \param pSectionData
         * Pointer to the destination section data.  Derived classes are allowed
         * to modify the section data in place, as appropriate.
         *
         * \param cbSectionData
         * Size of the destination section data, in bytes.
         * 
         * \return HRESULT
         * Returns S_OK on success, failure if an error occurs.
         */
    virtual HRESULT RemapSectionData(__inout_bcount(cbSectionData) void* pSectionData, __in UINT32 cbSectionData) const;
};

/*!@}*/
/*!@}*/
/*!@}*/

/*! 
     * \addtogroup DefBuild
     * @{
     * \addtogroup DefBuild_SectionCopiers
     * @{
     * \defgroup CopierFactory Factory for section copiers
     * @{
     */

/*!
     * Creates:
     *  FileAtomPoolCopier
     */
class SectionCopierFactory
{
public:
    static HRESULT Create(
        _In_ DEFFILE_SECTION_TYPEID sectionTypeId,
        _In_ const IFileSection* const pFileSection,
        _In_ RemapInfo* pRemap,
        _Outptr_ SectionCopier** result);
};

/*! 
     * \addtogroup DefBuild
     * @{
     * \addtogroup DefBuild_SectionCopiers
     * @{
     * \defgroup CommonCopiers Section copiers for common section types
     * @{
     */
class FileAtomPoolCopier : public SectionCopier
{
protected:
    Atom::PoolIndex m_originalIndex;

    FileAtomPoolCopier() {}

    HRESULT Init(_In_ const IFileSection* const pFileSection, _In_ RemapInfo* pRemap);

public:
    static HRESULT CreateInstance(
        _In_ const IFileSection* const pFileSection,
        _In_ RemapInfo* pRemap,
        _Outptr_ FileAtomPoolCopier** result);

    /*!
         * Gets the section qualifier for the file atom pool.  For atom
         * pools the qualifier is the atom pool index, which could get
         * remapped.
         */
    virtual UINT32 GetSectionQualifier() const;

    virtual ~FileAtomPoolCopier() {}

protected:
    /*! 
         * Applies pool mappings to the file atom pool.  Remaps the atom pool's
         * own index and the corresponding qualifier.
         *
         * \param pHeader
         * Pointer to the destination section header.  Derived classes are
         * allowed to modify the qualifier, flags and sectionFlags fields of
         * the section header.
         *
         * \param pSectionData
         * Pointer to the destination section data.  Derived classes are allowed
         * to modify the section data in place, as appropriate.
         *
         * \param cbSectionData
         * Size of the destination section data, in bytes.
         * 
         * \return HRESULT
         * Returns S_OK on success, failure if an error occurs.
         */
    virtual HRESULT RemapSectionData(__inout_bcount(cbSectionData) void* pSectionData, __in UINT32 cbSectionData) const;
};

} // namespace Microsoft::Resources::Build
