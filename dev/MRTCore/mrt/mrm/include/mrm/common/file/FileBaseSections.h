// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "mrm/common/file/FileBase.h"

#ifdef __cplusplus
extern "C"
{
#endif

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gDataSectionType = {
        '[',
        'm',
        'r',
        'm',
        '_',
        'd',
        'a',
        't',
        'a',
        ']',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
    };

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gDataItemsSectionType = {
        '[',
        'm',
        'r',
        'm',
        '_',
        'd',
        'a',
        't',
        'a',
        'i',
        't',
        'e',
        'm',
        ']',
        ' ',
    };

    /*
      * NOTE:   These structures are all intended to be mapped directly into memory.  Always
      * use types with fixed sizes (e.g. INT32 instead of INT) and be careful to maintain natural
      * alignment across all architectures (i.e. insert padding if necessary).
      */

    /*!
      * Describes a file data items section.  Layout in memory is:
     *      DATAITEMS_HEADER            hdr
     *      DATA_ITEM_SMALL             smallItems[hdr.numSmallItems]
     *      DATA_ITEM_LARGE             largeItems[hdr.numLargItems]
     *      BYTE*                       itemData[cbData]
     *      PAD
     */
    typedef struct _DEFFILE_DATAITEMS_HEADER
    {
        UINT32 flags; //!< flags describing the rest of the structure
        UINT16 numSmallItems; //!< Total number of small items in the section
        UINT16 numLargeItems; //!< Total number of large items in the section
        UINT32 cbData; //!< Size of the item data, in bytes
    } DEFFILE_DATAITEMS_HEADER, *PDEFFILE_DATAITEMS_HEADER;

    typedef struct _DEFFILE_DATA_ITEM_SMALL
    {
        UINT16 offset;
        UINT16 cbData;
    } DEFFILE_DATA_ITEM_SMALL;

    typedef struct _DEFFILE_DATA_ITEM_LARGE
    {
        UINT32 offset;
        UINT32 cbData;
    } DEFFILE_DATA_ITEM_LARGE;

    __declspec(selectany) extern const int DEFFILE_SMALL_DATA_ITEM_MAX_SIZE = 0x7fff;

// Flags for DEFFILE_DATAITEMS_HEADER
#define DEFFILE_DATAITEMS_EXTENDED_LARGE_ITEMS 0x1

    inline UINT32 GetNumberOfLargeItems(_In_ const DEFFILE_DATAITEMS_HEADER* header)
    {
        if (header->flags & DEFFILE_DATAITEMS_EXTENDED_LARGE_ITEMS)
        {
            // When the flag is set, use the top 2nd byte of flags to extend
            // number of large items to 16M.
            return ((header->flags & 0x00ff0000) | header->numLargeItems);
        }

        return header->numLargeItems;
    }

#ifdef __cplusplus
}
#endif
