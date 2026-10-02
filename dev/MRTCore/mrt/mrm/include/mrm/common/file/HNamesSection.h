// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    /*!
     * \defgroup DefFile_HNames Common file structure for information about a hierarchy of names
     * @{
     */

    /*
      * NOTE:   These structures are all intended to be mapped directly into memory.  Always
      * use types with fixed sizes (e.g. INT32 instead of INT) and be careful to maintain natural
      * alignment across all architectures (i.e. insert padding if necessary).
      */

    /*!
     * Describes a single name node in a resource hierarchy of < 64k total
     * scopes and nodes.
     * - parentNodeIndex is the index of the parent of this node in the 
     *   global nodes table.
     * - cchFullPath is the size in characters of the full path to this node
     * - initialChar is the first character of the name, uppercased
     * - cchName is the length of the name for this node in characters, not including separators
     * - flagsAndNameOffsetHigh - combined field:
     *   - (flagsAndNameOffsetHigh & 0x0f) is the high four bits of the offset of the
     *     name of this node in the names table.
     *   - (flagsAndNameOffsetHigh & 0xf0) is reserved for flags.  If DEFFILE_HNAMES_FLAGS_NODE_IS_SCOPE
     *     is set, the payload refers to a scope.  Else it refers to an item.
     * - payload is the index of the scope or file referenced by this node,
     *   depending on the value of the flagsAndNameOffsetHigh
     */
    typedef struct _DEFFILE_HNAMES_NODE
    {
        UINT16 parentNodeIndex;
        UINT16 cchFullPath;
        WCHAR initialChar;
        BYTE cchName;
        BYTE flagsAndNameOffsetHigh;
        UINT16 nameOffsetLow;
        UINT16 payload;
    } DEFFILE_HNAMES_NODE, *PDEFFILE_HNAMES_NODE;

    // Describes a single name node in a resource hierarchy of > 64k total
    // scopes and nodes. The limit is 2GB due to int being used in many places.
    // Fields are similar to DEFFILE_HNAMES_NODE. nameOffsetMiddle is the
    // middle 8 bits of the offset of the name of this node in the names table.
    // This brings a total 4 + 8 + 16 = 28 bits (i.e. 256MB) for names.
    typedef struct _DEFFILE_HNAMES_NODE_LARGE
    {
        UINT32 parentNodeIndex;
        UINT16 cchFullPath;
        WCHAR initialChar;
        BYTE cchName;
        BYTE flagsAndNameOffsetHigh;
        UINT8 nameOffsetMiddle;
        UINT16 nameOffsetLow;
        UINT32 payload;
    } DEFFILE_HNAMES_NODE_LARGE, *PDEFFILE_HNAMES_NODE_LARGE;

    __declspec(selectany) extern const BYTE DEFFILE_HNAMES_FLAGS_NODE_IS_SCOPE = 0x10;
    __declspec(selectany) extern const BYTE DEFFILE_HNAMES_FLAGS_NAME_IS_ASCII = 0x20;

    // Turns out, the original size limit on the names pool was too low for demanding applications.
    // Changing the structure would be a major format rev. But we can use the unused flags bits to extend the limit somewhat.
    __declspec(selectany) extern const BYTE DEFFILE_HNAMES_FLAGS_POOL_SIZE_2MB = 0x40;
    __declspec(selectany) extern const BYTE DEFFILE_HNAMES_FLAGS_POOL_SIZE_4MB = 0x80;

    inline UINT32 HNamesGetNodeNameOffset(_In_ const DEFFILE_HNAMES_NODE* pNode)
    {
        UINT32 ret = ((pNode->flagsAndNameOffsetHigh & 0xf) << 16) | pNode->nameOffsetLow;
        if (pNode->flagsAndNameOffsetHigh & DEFFILE_HNAMES_FLAGS_POOL_SIZE_2MB)
        {
            ret |= 0x100000;
        }

        if (pNode->flagsAndNameOffsetHigh & DEFFILE_HNAMES_FLAGS_POOL_SIZE_4MB)
        {
            ret |= 0x200000;
        }

        return ret;
    }

    inline UINT32 HNamesGetNodeNameOffsetLarge(_In_ const DEFFILE_HNAMES_NODE_LARGE* pNode)
    {
        // This accommodates 256MB of names, which should be enough. Not using the top 2 bits of
        // flagsAndNameOffsetHigh for now.
        return ((pNode->flagsAndNameOffsetHigh & 0xf) << 24) | (pNode->nameOffsetMiddle << 16) | pNode->nameOffsetLow;
    }

    inline const DEFFILE_HNAMES_NODE_LARGE HNAMES_NODE_TO_HNAMES_NODE_LARGE(_In_ const DEFFILE_HNAMES_NODE* node)
    {
        DEFFILE_HNAMES_NODE_LARGE largeNode;
        largeNode.parentNodeIndex = node->parentNodeIndex;
        largeNode.cchFullPath = node->cchFullPath;
        largeNode.initialChar = node->initialChar;
        largeNode.cchName = node->cchName;
        largeNode.flagsAndNameOffsetHigh = (node->flagsAndNameOffsetHigh & 0x30);
        largeNode.nameOffsetMiddle = (((node->flagsAndNameOffsetHigh >> 2) & 0x30) | (node->flagsAndNameOffsetHigh & 0xf));
        largeNode.nameOffsetLow = node->nameOffsetLow;
        largeNode.payload = node->payload;
        return largeNode;
    }

    /*!
     * Describes an interior node (scope) in a hierarchy of < 64k total
     * scopes and items.
     */
    typedef struct _DEFFILE_HNAMES_SCOPE_INFO
    {
        UINT16 nameNodeIndex;
        UINT16 numChildNames;
        UINT16 firstChildNameNode;
        UINT16 flags;
    } DEFFILE_HNAMES_SCOPE, *PDEFFILE_HNAMES_SCOPE;

    typedef struct _DEFFILE_HNAMES_SCOPE_INFO_LARGE
    {
        UINT32 nameNodeIndex;
        UINT32 numChildNames;
        UINT32 firstChildNameNode;
        UINT32 flags;
    } DEFFILE_HNAMES_SCOPE_LARGE, *PDEFFILE_HNAMES_SCOPE_LARGE;

    inline const DEFFILE_HNAMES_SCOPE_LARGE HNAMES_SCOPE_TO_HNAMES_SCOPE_LARGE(_In_ const DEFFILE_HNAMES_SCOPE* scope)
    {
        DEFFILE_HNAMES_SCOPE_LARGE largeScope;
        largeScope.nameNodeIndex = scope->nameNodeIndex;
        largeScope.numChildNames = scope->numChildNames;
        largeScope.firstChildNameNode = scope->firstChildNameNode;
        largeScope.flags = scope->flags;
        return largeScope;
    }

    /*!
     * Header for a Hierarchical names section.
     * If HNAMES_FLAGS_LARGE is _not_ set in hdr.flags, layout
     * in memory is:
     *      HNAMES_HEADER               hdr
     *      HNAMES_NODE                 nodes[hdr.numNodes]
     *      HNAMES_SCOPE                scopes[hdr.numScopes]
     *      UINT16                      items[hdr.numItems]
     *      WCHAR                       names[hdr.cchNames];
     *
     * If HNAMES_FLAGS_LARGE is set in hdr.flags, layout in memory
     * is:
     *      HNAMES_HEADER               hdr
     *      HNAMES_NODE_LARGE           nodes[hdr.numNodes]
     *      HNAMES_SCOPE_LARGE          scopes[hdr.numScopes]
     *      UINT32                      items[hdr.numItems]
     *      WCHAR                       names[hdr.cchNames];
     */
    typedef struct _DEFFILE_HNAMES_HEADER
    {
        UINT16 cchLongestPath;
        UINT16 flags;
        UINT32 numNodes;
        UINT32 numScopes;
        UINT32 numItems;
        UINT32 cchNames;
        UINT32 cbTotal;
    } DEFFILE_HNAMES_HEADER, *PDEFFILE_HNAMES_HEADER;

    typedef struct _DEFFILE_HNAMES_HEADER_EX
    {
        UINT16 cchLongestPath;
        UINT16 flags;
        UINT32 numNodes;
        UINT32 numScopes;
        UINT32 numItems;
        UINT32 cchUtf16NamesPool;
        UINT32 cbTotal;
        UINT32 cchAsciiNamesPool;
    } DEFFILE_HNAMES_HEADER_EX, *PDEFFILE_HNAMES_HEADER_EX;

    __declspec(selectany) extern const UINT32 DEFFILE_HNAMES_FLAGS_LARGE = 0x0001;
    __declspec(selectany) extern const UINT32 DEFFILE_MAX_STANDARD_SIZE = 0xffff;

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gHierarchicalNamesSectionType = {
        '[',
        'd',
        'e',
        'f',
        '_',
        'h',
        'n',
        'a',
        'm',
        'e',
        's',
        ']',
        ' ',
        ' ',
        ' ',
    };

    __declspec(selectany) extern const DEFFILE_SECTION_TYPEID gHierarchicalNamesExSectionType = {
        '[',
        'd',
        'e',
        'f',
        '_',
        'h',
        'n',
        'a',
        'm',
        'e',
        's',
        'x',
        ']',
        ' ',
        ' ',
    };

    /*@}*/

#ifdef __cplusplus
}
#endif
