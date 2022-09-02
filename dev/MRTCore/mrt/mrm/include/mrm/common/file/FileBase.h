// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "mrm/common/Base.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /*
      * NOTE:   These structures are all intended to be mapped directly into memory.  Always
      * use types with fixed sizes (e.g. INT32 instead of INT) and be careful to maintain natural
      * alignment across all architectures (i.e. insert padding if necessary).
      */

    /*!
     * A convenience union for defining eight-byte "magic numbers" at the head of
     * all DEF files.   The magic number can be specified as some
     * recognizable (ANSI) string but used as a single 64-bit integer value.
     */
    typedef union _DEFFILE_MAGIC
    {
        BYTE bMagic[sizeof(UINT64) / sizeof(BYTE)]; //!< Magic number as bytes
        UINT64 ullMagic; //!< Magic number as UINT64
    } DEFFILE_MAGIC, *PDEFFILE_MAGIC;

    //! Version number of the file format described in this file
    __declspec(selectany) extern const UINT16 DEFFILE_VERSION_MAJOR = 0;
    __declspec(selectany) extern const UINT16 DEFFILE_VERSION_MINOR = 1;

    /*!
     * A convenience union for defining 16-byte section type identifiers at the head of
     * the sections of DEF files. 
     */
    typedef union _DEFFILE_SECTION_TYPEID
    {
        BYTE bType[16]; //!< Section type identifier as bytes
        UINT32 ulType[4]; //!< Section type identifier as UINT32
        UINT64 ullType[2]; //!< Section type identifier as UINT64
    } DEFFILE_SECTION_TYPEID, *PDEFFILE_SECTION_TYPEID;

    /*!
     * Convenience type for referring to sections within a file by index.
     */
    typedef INT16 DEFFILE_SECTION_INDEX;
    typedef INT16 DEFFILE_SECTION_COUNT;

    __declspec(selectany) extern const DEFFILE_SECTION_COUNT DEFFILE_MAX_SECTION_COUNT = 0x7fff;
    __declspec(selectany) extern const DEFFILE_SECTION_INDEX DEFFILE_MAX_SECTION_INDEX = 0x7ffe;
    __declspec(selectany) extern const DEFFILE_SECTION_INDEX DEFFILE_SECTION_INDEX_NONE = -1;

#define DefFile_Section_GetStructureOverhead() (sizeof(DEFFILE_SECTION_HEADER) + sizeof(DEFFILE_SECTION_TRAILER))

#define DefFile_Section_GetTrailer(HDR) \
    ((DEFFILE_SECTION_TRAILER*)(((BYTE*)HDR) + _DEFFILE_PAD_SECTION((HDR)->cbSectionTotal) - sizeof(DEFFILE_SECTION_TRAILER)))

#define DEFFILE_IS_VALID_SECTION_INDEX(NDX) (((NDX) >= 0) && ((NDX) <= DEFFILE_MAX_SECTION_INDEX))

    /*!
     * Common header structure used by DEF files.  Specific sub-formats can extend this structure but 
     * they must no redefine existing fields, including reserved values.
     */
    typedef struct _DEFFILE_HEADER
    {
        DEFFILE_MAGIC magic; //!< Identifies the type of file.
        UINT16 majorVersion; //!< Identifies incompatible format changes.
        UINT16 minorVersion; //!< Identifies backwardly compatible file format changes.
        UINT32 cbTotal; //!< Total size in bytes of all DEF data, including trailer and this header.
        UINT32 tocOffset; //!< Offset in bytes of the first TOC entry from the start of the file.
        UINT32 sectionDataOffset; //!< Offset in bytes of the start of section data from the head of the file.
        DEFFILE_SECTION_COUNT sizeToc; //!< Number of entries in the TOC for this file.
        DEFFILE_SECTION_INDEX descriptorIndex; //!< Index of the file descriptor, if any.
        UINT32 pad; //!< Reserved, must be 0.
    } DEFFILE_HEADER, *PDEFFILE_HEADER;

    /*!
     * Common trailer structure to mark end of DEF files.
     */
    typedef struct _DEFFILE_TRAILER
    {
        UINT32 marker; //!< end-of-file marker
        UINT32 cbTotal; //!< Total size in bytes of all DEF data, including header and this trailer.
        DEFFILE_MAGIC magic; //!< Identifies the type of file
    } DEFFILE_TRAILER, *PDEFFILE_TRAILER;

    /*!
      * Common TOC structure to locate sections of a DEF file.
      */
    typedef struct _DEFFILE_TOC_ENTRY
    {
        DEFFILE_SECTION_TYPEID type; //!< Identifies the type of the section.
        UINT16 flags; //!< Global flags have common meaning across all section types.
        UINT16 sectionFlags; //!< Interpretation of section flags depends on section type.
        UINT32 qualifier; //!< Qualifier used to distinguish between multiple sections with the same type
        UINT32 offset; /*!< Byte offset of the section data from the start of the DEF data (i.e. after
                                                     all TOC entries. */
        UINT32 cbSectionTotal; //!< Size of section data, in bytes.
    } DEFFILE_TOC_ENTRY, *PDEFFILE_TOC_ENTRY;

    //! If DEFFILE_TOC_IS_ATOM_POOL is set in flags, the qualifier is the index of the atom pool defined by the section
    //! If DEFFILE_TOC_IS_ATOM_METADATA is set in flags, the qualifier is the index of the atom pool referenced by the section
    __declspec(selectany) extern const UINT16 DEFFILE_IS_ATOM_POOL_SECTION = 0x0001;
    __declspec(selectany) extern const UINT16 DEFFILE_IS_ATOM_METADATA_SECTION = 0x0002;

    /*!
      * Common header for a section of a DEF file.
      */
    typedef struct _DEFFILE_SECTION_HEADER
    {
        DEFFILE_SECTION_TYPEID type; //!< Identifies the type of the section
        UINT32 qualifier; //!< Qualifier used to distinguish between sections with the same type
        UINT16 flags; //!< Global flags have common meaning across all section types.
        UINT16 sectionFlags; //!< Interpretation of section flags depends on section type.
        UINT32 cbSectionTotal; //!< Size of section data in bytes, including header and trailer
        UINT32 pad; //!< Reserved, must be 0.
    } DEFFILE_SECTION_HEADER, *PDEFFILE_SECTION_HEADER;

    //! Marker for the end of a file section
    __declspec(selectany) extern const UINT32 DEFFILE_SECTION_END_MARKER = 0xdef5fade;

    //! Marker for the end of a file
    __declspec(selectany) extern const UINT32 DEFFILE_FILE_END_MARKER = 0xdefffade;

    /*!
      * Common trailer for a section of a DEF file.
      */
    typedef struct _DEFFILE_SECTION_TRAILER
    {
        UINT32 marker; //!< end-of-section marker
        UINT32 cbSectionTotal; //!< Size of section data in bytes, including header and trailer.
    } DEFFILE_SECTION_TRAILER, *PDEFFILE_SECTION_TRAILER;

    __declspec(selectany) extern const UINT32 DEFFILE_DEFAULT_ALIGN = 8;

/*!
     * Pad or truncate a number (typically a byte count) to some boundary.
     */
#define _DEFFILE_PAD(SIZE, BOUNDARY) ((((SIZE) + (BOUNDARY)-1) / (BOUNDARY)) * (BOUNDARY))
#define _DEFFILE_TRUNC(SIZE, BOUNDARY) (((SIZE) / (BOUNDARY)) * (BOUNDARY))

#define _DEFFILE_PAD_SECTION(SIZE) _DEFFILE_PAD((SIZE), DEFFILE_DEFAULT_ALIGN)
#define _DEFFILE_IS_ALIGNED(SIZE, PAD) ((SIZE) == _DEFFILE_PAD((SIZE), (PAD)))

#define _DEFFILE_PTR_IS_ALIGNED(PTR, PAD) _DEFFILE_IS_ALIGNED(reinterpret_cast<UINT_PTR>(PTR), PAD)
#define _DEFFILE_ALIGN_PTR(TYPE, PTR, PAD) reinterpret_cast<TYPE>(_DEFFILE_PAD(reinterpret_cast<UINT_PTR>(PTR), PAD))

#define _DEF_DECLARE_FILE_STATUS(NAME, INDEX) static const DEFRESULT E_DEFFILE_##NAME = _DEF_MAKE_STATUS(_DEF_FACILITY_FILE, INDEX)

    _DEF_DECLARE_FILE_STATUS(BAD_MAGIC_NUMBER, 0x01);
    _DEF_DECLARE_FILE_STATUS(BAD_TOC_ENTRY, 0x02);
    _DEF_DECLARE_FILE_STATUS(TOC_MISMATCH, 0x03);
    _DEF_DECLARE_FILE_STATUS(BAD_SECTION_TRAILER, 0x04);
    _DEF_DECLARE_FILE_STATUS(BAD_FILE_TRAILER, 0x05);
    _DEF_DECLARE_FILE_STATUS(FILE_DATA_TOO_SMALL, 0x06);
    _DEF_DECLARE_FILE_STATUS(BAD_TOC_OFFSET, 0x07);
    _DEF_DECLARE_FILE_STATUS(BAD_DATA_OFFSET, 0x08);
    _DEF_DECLARE_FILE_STATUS(BAD_SECTION_HEADER, 0x09);
    _DEF_DECLARE_FILE_STATUS(BAD_SECTION_TYPE, 0x0A);
    _DEF_DECLARE_FILE_STATUS(BAD_SECTION_QUALIFIER, 0x0B);
    _DEF_DECLARE_FILE_STATUS(SECTION_DATA_TOO_SMALL, 0x0C);
    _DEF_DECLARE_FILE_STATUS(BAD_ALIGNMENT, 0x0D);
    _DEF_DECLARE_FILE_STATUS(NO_SECTIONS, 0x0E);
    _DEF_DECLARE_FILE_STATUS(NO_ATOMS, 0x0F);
    _DEF_DECLARE_FILE_STATUS(ATOM_COUNT_MISMATCH, 0x10);
    _DEF_DECLARE_FILE_STATUS(DUPLICATE_SECTION, 0x11);
    _DEF_DECLARE_FILE_STATUS(SECTION_NOT_FOUND, 0x12);
    _DEF_DECLARE_FILE_STATUS(ATOMPOOL_MISMATCH, 0x13);
    _DEF_DECLARE_FILE_STATUS(UNDEFINED_FLAGS, 0x14);
    _DEF_DECLARE_FILE_STATUS(UNABLE_TO_WRITE, 0x16);
    _DEF_DECLARE_FILE_STATUS(UNABLE_TO_OPEN_FOR_READ, 0x17);
    _DEF_DECLARE_FILE_STATUS(UNABLE_TO_READ, 0x18);
    _DEF_DECLARE_FILE_STATUS(UNDEFINED_MAPPING, 0x19);
    _DEF_DECLARE_FILE_STATUS(BAD_SECTION_INDEX, 0x1A);
    _DEF_DECLARE_FILE_STATUS(FORMAT_ERROR, 0x1B);
    _DEF_DECLARE_FILE_STATUS(UNSUPPORTED_SECTION_TYPE, 0x1C);

    _DEF_DECLARE_FILE_STATUS(ATOMPOOL_ATOMS_FULL, 0x20);
    _DEF_DECLARE_FILE_STATUS(ATOMPOOL_POOL_FULL, 0x21);
    _DEF_DECLARE_FILE_STATUS(ATOMPOOL_DUPLICATE_POOL_INDEX, 0x22);

    //referenced file
    _DEF_DECLARE_FILE_STATUS(REFERENCE_NOT_FOUND, 0x23);

    //File Manager
    _DEF_DECLARE_FILE_STATUS(UNABLE_TO_OPEN, 0x24);
    _DEF_DECLARE_FILE_STATUS(UNABLE_TO_CREATE_MAPPING, 0x25);

    // Namespace-specific status/error codes
    _DEF_DECLARE_FILE_STATUS(NAMESPACE_INVALID_DESCRIPTOR, 0x30);
    _DEF_DECLARE_FILE_STATUS(ATTRIBUTE_NOT_FOUND, 0x31);

    // instance bundle
    _DEF_DECLARE_FILE_STATUS(ITEM_TYPE_NOT_CONTAINED, 0x81);
    _DEF_DECLARE_FILE_STATUS(FAIL_FIND_INSTANCE, 0x82);
    _DEF_DECLARE_FILE_STATUS(INVALID_INSTANCEBUNDLE, 0x83);
    _DEF_DECLARE_FILE_STATUS(FAIL_TO_FIND_HASH_UID, 0x84);
    _DEF_DECLARE_FILE_STATUS(VALID_SIGNATURE_NOT_FOUND, 0x85);
    _DEF_DECLARE_FILE_STATUS(NAMESPACE_NOT_SUPPORTED, 0x86);
    _DEF_DECLARE_FILE_STATUS(INVALID_CATALOG_RAW_PATH, 0x87);
    _DEF_DECLARE_FILE_STATUS(INVALID_SEGMENT_PATH, 0x88);

    // additional file format
    _DEF_DECLARE_FILE_STATUS(SECTION_DATA_TOO_LARGE, 0x90);
    _DEF_DECLARE_FILE_STATUS(FILE_DATA_EMPTY, 0x91);

    /*@}*/

#ifdef __cplusplus
}
#endif
