// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "mrm/common/file/FileBase.h"

#ifdef __cplusplus
extern "C"
{
#endif

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gAtomPoolSectionType = {
        '[',
        'd',
        'e',
        'f',
        '_',
        '1',
        'a',
        't',
        'o',
        'm',
        '1',
        '2',
        ':',
        '-',
        ']',
    };

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gSequentialAtomPoolSectionType = {
        '[',
        's',
        'e',
        'q',
        'u',
        'e',
        'n',
        't',
        'i',
        'a',
        'l',
        '_',
        'A',
        'P',
        ']',
    };

    /*
      * NOTE:   These structures are all intended to be mapped directly into memory.  Always
      * use types with fixed sizes (e.g. INT32 instead of INT) and be careful to maintain natural
      * alignment across all architectures (i.e. insert padding if necessary).
      */

    /*!
      * Flags that describe the hash data stored in the file representation of an atom pool.
      */
    typedef enum
    {
        DEFFILE_ATOMPOOL_HASH_DEFAULT = 0x0000, //!< Uses default hash method
        DEFFILE_ATOMPOOL_HASH_CASE_INSENSITIVE = 0x0001, //!< Uses case-insensitive hash method
        DEFFILE_ATOMPOOL_HASH_NONE = 0x0002, //!< No hash table present
        DEFFILE_ATOMPOOL_HASH_UNSORTED = 0x0004, //!< Hash table is unsorted
        DEFFILE_ATOMPOOL_HASH_SMALL = 0x0008 //!< Hash table uses small atom index for hash table
    } DefFileAtomPoolHashFlags;

#define DEFFILE_ATOMPOOL_DESC_LENGTH 32

    /*!
      * Section header for an atom pool in a DEF file.  This header follows the generic
      * section header that appears at the head of all sections.
      */
    typedef struct _DEFFILE_ATOMPOOL_HEADER
    {
        UINT32 flags; //!< flags describing the rest of the structure
        DEF_ATOM_POOL_INDEX poolIndex; //!< index of the atom pool
        DEF_ATOM_COUNT nAtoms; //!< number of atoms in the pool
        UINT32 cchPool; //!< size of the string pool, in chararcters
        WCHAR desc[DEFFILE_ATOMPOOL_DESC_LENGTH]; //!< User-friendly description of the contents
    } DEFFILE_ATOMPOOL_HEADER, *PDEFFILE_ATOMPOOL_HEADER;

    /*!
     * Hash data for one atom in an atom pool.
     */
    typedef struct _DEFFILE_ATOMPOOL_HASHINDEX
    {
        DEF_ATOM_HASH hash; //!< Hash value for the corresponding string
        DEF_ATOM_INDEX index; //!< Index of the corresponding string in the hash table
    } DEFFILE_ATOMPOOL_HASHINDEX, *PDEFFILE_ATOMPOOL_HASHINDEX;

    /*!
     * Hash data for one atom in an atom pool with less than 64k atoms.
     * Use the small index when the SMALL flag is set, which should be
     * for any table with less than 64k entries.
     */
    typedef struct _DEFFILE_ATOMPOOL_HASHINDEX_SMALL
    {
        DEF_ATOM_HASH_SMALL hash; //!< Hash value for the corresponding string
        DEF_ATOM_INDEX_SMALL index; //!< Index of the corresponding string in the hash table
    } DEFFILE_ATOMPOOL_HASHINDEX_SMALL, *PDEFFILE_ATOMPOOL_HASHINDEX_SMALL;

    /*!
      * Describes the mapping from a range of one or more pools in another file to
      * a different range in this file.
      */
    typedef struct _DEFFILE_ATOMPOOL_MAPPING
    {
        DEF_ATOM_POOL_INDEX sourceIndex; //!< Index of the first pool in the source atomGroup
        DEF_ATOM_POOL_INDEX destIndex; //!< Index of the first pool in this destination atomGroup
        DEF_ATOM_POOL_COUNT nPools; //!< Number of consecutive pools to be mapped from the source AtomGroup
        UINT16 pad; //!< reserved. must be 0
    } DEFFILE_ATOMPOOL_MAPPING, *PDEFFILE_ATOMPOOL_MAPPING;

    /*!
      * Describes a sequential atom pool.
      */
#define DEFFILE_SEQUENTIAL_ATOMPOOL_PREFIX_LENGTH 32

    typedef struct _DEFFILE_SEQUENTIAL_ATOMPOOL
    {
        UINT32 flags; //!< flags describing the rest of the structure
        DEF_ATOM_POOL_INDEX poolIndex; //!< index of the atom pool
        DEF_ATOM_COUNT nAtoms; //!< number of atoms in the pool (indexes always start at zero)
        WCHAR desc[DEFFILE_ATOMPOOL_DESC_LENGTH]; //!< User-friendly description of the contents
        WCHAR prefix[DEFFILE_SEQUENTIAL_ATOMPOOL_PREFIX_LENGTH]; //!< Prefix for item names
        UINT32 pad;
    } DEFFILE_SEQUENTIAL_ATOMPOOL, *PDEFFILE_SEQUENTIAL_ATOMPOOL;

#ifdef __cplusplus
}
#endif
