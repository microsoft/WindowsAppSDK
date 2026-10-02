// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "stdafx.h"
#include "mrm/readers/hnames.h"

namespace Microsoft::Resources
{

int HierarchicalNamesConfig::CompareStoredAsciiSegment(_In_ PCSTR pStoredSegment, _In_ PCWSTR pRequestedSegment) const
{
    int len = static_cast<int>(strlen(pStoredSegment));
    return CompareStoredAsciiSegment(pStoredSegment, len, pRequestedSegment);
}

int HierarchicalNamesConfig::CompareStoredAsciiSegment(
    _In_reads_or_z_(cchStoredSegment) PCSTR pStoredSegment,
    _In_ int cchStoredSegment,
    _In_ PCWSTR pRequestedSegment) const
{
    for (int i = 0; (i < cchStoredSegment) && (pStoredSegment[i] != '\0'); i++)
    {
        if (pStoredSegment[i] != pRequestedSegment[i])
        {
            if (pRequestedSegment[i] == '\0')
            {
                // requested string is shorter,
                // so the stored name is greater
                return 1;
            }

            int diff = towupper(pStoredSegment[i]) - towupper(pRequestedSegment[i]);
            if (diff != 0)
            {
                return diff;
            }
        }
    }

    return 0;
}

bool HierarchicalNamesConfig::IsValidSegment(__in PCWSTR pSegment) const
{
    if (DefString_IsEmpty(pSegment))
    {
        return false;
    }
    PCWSTR pStr = pSegment;
    while ((*pStr) != L'\0')
    {
        if (!IsValidSegmentChar(*pStr))
        {
            return false;
        }
        pStr++;
    }

    // '.' and '..' not allowed as scope or item name
    if (pSegment[0] == L'.')
    {
        if ((pSegment[1] == L'\0') || ((pSegment[1] == L'.') && (pSegment[2] == L'\0')))
        {
            return false;
        }
    }
    return true;
}

_Success_(return ) _Post_satisfies_(*pSegmentLengthOut <= _String_length_(pFullName)) bool HierarchicalNamesConfig::TryGetNextSegmentLength(
    _Inout_ PCWSTR pFullName,
    _Out_ int* pSegmentLengthOut,
    _Out_ bool* pbMoreSegmentsOut) const
{
    *pSegmentLengthOut = -1;
    *pbMoreSegmentsOut = false;

    if (DefString_IsEmpty(pFullName))
    {
        return false;
    }

    // Lets see if our name contains any path characters
    int segmentLength = -1;
    PCWSTR pTmp = pFullName;
    while (*pTmp != L'\0')
    {
        if (!IsValidSegmentChar(*pTmp))
        {
            if (IsPathSeparator(*pTmp))
            {
                *pSegmentLengthOut = (pTmp - pFullName);
                *pbMoreSegmentsOut = true;
                return true;
            }
            return false;
        }
        pTmp++;
    }

    if (segmentLength == 0)
    {
        // empty segment not allowed
        return false;
    }

    // no separator, just record length
    *pSegmentLengthOut = (pTmp - pFullName);
    *pbMoreSegmentsOut = false;
    return true;
}

class HierarchicalNamesAtomPool : public IAtomPool
{
public:
    bool Contains(__in PCWSTR pString) const { return m_pNames->Contains(pString); }

    bool Contains(__in Atom atom) const
    {
        return (atom.GetPoolIndex() == m_poolIndex) && (atom.GetIndex() >= 0) && (atom.GetIndex() < m_numAtoms);
    }

    virtual bool Equals(__in Atom atom, __in PCWSTR pString) const
    {
        Atom foundAtom = Atom::NullAtom;
        return (TryGetAtom(pString, &foundAtom) && atom.IsEqual(foundAtom));
    }

    AtomPoolGroup* GetAtomPoolGroup() const { return m_pAtomPoolGroup; }

    PCWSTR GetDescription() const { return NULL; }

    bool GetIsCaseInsensitive() const { return true; }

    Atom::Index GetNumAtoms() const { return m_numAtoms; }

    Atom::PoolIndex GetPoolIndex() const { return m_poolIndex; }

    void SetAtomPoolGroup(AtomPoolGroup* pGroup) { m_pAtomPoolGroup = pGroup; }

    void SetPoolIndex(Atom::PoolIndex index) { m_poolIndex = index; }

    virtual bool TryGetAtom(__in PCWSTR pString, __out_opt Atom* pAtomOut) const = 0;

    virtual bool TryGetIndex(__in PCWSTR pString, __out_opt Atom::Index* pIndexOut) const = 0;

    virtual bool TryGetString(__in Atom atom, __inout_opt StringResult* pStringOut) const = 0;

    virtual bool TryGetString(__in Atom::Index index, __inout_opt StringResult* pStringOut) const = 0;

protected:
    HierarchicalNamesAtomPool(__in const IHierarchicalNames* pNames, __in int numAtoms) :
        m_pNames(pNames), m_numAtoms(numAtoms), m_poolIndex(Atom::PoolIndexNone), m_pAtomPoolGroup(nullptr)
    {}

    const IHierarchicalNames* m_pNames;
    int m_numAtoms;

    Atom::PoolIndex m_poolIndex;
    AtomPoolGroup* m_pAtomPoolGroup;
};

template<typename T>
class ScopesAtomPool : public HierarchicalNamesAtomPool
{
public:
    static HRESULT CreateInstance(
        __in const IHierarchicalNames* pNames,
        __in_ecount(numScopes) const T* pScopes,
        __in int numScopes,
        _Outptr_ ScopesAtomPool** result)
    {
        *result = nullptr;
        ScopesAtomPool* pRtrn = new ScopesAtomPool(pNames, pScopes, numScopes);
        RETURN_IF_NULL_ALLOC(pRtrn);

        *result = pRtrn;

        return S_OK;
    }

    bool TryGetAtom(__in PCWSTR pString, __out_opt Atom* pAtomOut) const
    {
        int scopeIndex = -1;

        if (m_pNames->Contains(pString, &scopeIndex) && (scopeIndex >= 0) && (scopeIndex < m_numAtoms))
        {
            if (pAtomOut != NULL)
            {
                *pAtomOut = Atom(scopeIndex, m_poolIndex);
            }
            return true;
        }

        if (pAtomOut != NULL)
        {
            *pAtomOut = Atom::NullAtom;
        }
        return false;
    }

    bool TryGetIndex(__in PCWSTR pString, __out_opt Atom::Index* pIndexOut) const
    {
        int scopeIndex = Atom::NullAtomIndex;

        if (m_pNames->Contains(pString, &scopeIndex) && (scopeIndex >= 0) && (scopeIndex < m_numAtoms))
        {
            if (pIndexOut != NULL)
            {
                *pIndexOut = scopeIndex;
            }
            return true;
        }

        if (pIndexOut != NULL)
        {
            *pIndexOut = Atom::NullAtomIndex;
        }
        return false;
    }

    bool TryGetString(__in Atom atom, __inout_opt StringResult* pStringOut) const
    {
        if (Contains(atom))
        {
            return m_pNames->TryGetName(m_pScopes[atom.GetIndex()].nameNodeIndex, pStringOut);
        }
        return false;
    }

    bool TryGetString(__in Atom::Index index, __inout_opt StringResult* pStringOut) const
    {
        if ((index >= 0) && (index < m_numAtoms))
        {
            return m_pNames->TryGetName(m_pScopes[index].nameNodeIndex, pStringOut);
        }
        return false;
    }

    HRESULT Clone(_Outptr_ IAtomPool** clonedPool) override
    {
        return ScopesAtomPool::CreateInstance(m_pNames, m_pScopes, m_numAtoms, (ScopesAtomPool**)clonedPool);
    }

protected:
    ScopesAtomPool(__in const IHierarchicalNames* pNames, __in_ecount(numScopes) const T* pScopes, __in int numScopes) :
        HierarchicalNamesAtomPool(pNames, numScopes)
    {
        m_pScopes = pScopes;
    }

    const T* m_pScopes;
};

template<typename T>
class ItemsAtomPool : public HierarchicalNamesAtomPool
{
public:
    static HRESULT CreateInstance(
        __in const IHierarchicalNames* pNames,
        __in_ecount(numItems) const T* pItems,
        __in int numItems,
        _Outptr_ ItemsAtomPool** result)
    {
        *result = nullptr;
        ItemsAtomPool* pRtrn = new ItemsAtomPool(pNames, pItems, numItems);
        RETURN_IF_NULL_ALLOC(pRtrn);

        *result = pRtrn;
        return S_OK;
    }

    bool TryGetAtom(__in PCWSTR pString, __out_opt Atom* pAtomOut) const
    {
        int itemIndex = -1;

        if (m_pNames->Contains(pString, nullptr, &itemIndex) && (itemIndex >= 0) && (itemIndex < m_numAtoms))
        {
            if (pAtomOut != NULL)
            {
                *pAtomOut = Atom(itemIndex, m_poolIndex);
            }
            return true;
        }

        if (pAtomOut != NULL)
        {
            *pAtomOut = Atom::NullAtom;
        }
        return false;
    }

    bool TryGetIndex(__in PCWSTR pString, __out_opt Atom::Index* pIndexOut) const
    {
        int itemIndex = Atom::NullAtomIndex;

        if (m_pNames->Contains(pString, nullptr, &itemIndex) && (itemIndex >= 0) && (itemIndex < m_numAtoms))
        {
            if (pIndexOut != NULL)
            {
                *pIndexOut = itemIndex;
            }
            return true;
        }

        if (pIndexOut != NULL)
        {
            *pIndexOut = Atom::NullAtomIndex;
        }
        return false;
    }

    bool TryGetString(__in Atom atom, __inout_opt StringResult* pStringOut) const
    {
        if (Contains(atom))
        {
            return m_pNames->TryGetName(m_pItems[atom.GetIndex()], pStringOut);
        }
        return false;
    }

    bool TryGetString(__in Atom::Index index, __inout_opt StringResult* pStringOut) const
    {
        if ((index >= 0) && (index < m_numAtoms))
        {
            return m_pNames->TryGetName(m_pItems[index], pStringOut);
        }
        return false;
    }

    HRESULT Clone(_Outptr_ IAtomPool** clonedPool) override
    {
        return ItemsAtomPool::CreateInstance(m_pNames, m_pItems, m_numAtoms, (ItemsAtomPool**)clonedPool);
    }

protected:
    ItemsAtomPool(__in const IHierarchicalNames* pNames, __in_ecount(numItems) const T* pItems, __in int numItems) :
        HierarchicalNamesAtomPool(pNames, numItems)
    {
        m_pItems = pItems;
    }

    const T* m_pItems;
};

HierarchicalNames::HierarchicalNames() :
    m_pHeader(nullptr),
    m_pNodes(nullptr),
    m_pScopes(nullptr),
    m_pItems(nullptr),
    m_pNodesLarge(nullptr),
    m_pScopesLarge(nullptr),
    m_pItemsLarge(nullptr),
    m_pUtf16Names(nullptr),
    m_pAsciiNames(nullptr),
    m_pScopeNames(nullptr),
    m_pItemNames(nullptr),
    m_largeNode(false)
{}

HRESULT HierarchicalNames::Init(
    _In_ const DEFFILE_SECTION_TYPEID& type,
    _In_opt_ const IFileSection* pSection,
    _In_reads_bytes_(cbData) const void* pData,
    _In_ int cbData)
{
    RETURN_IF_FAILED(FileSectionBase::Init(pSection, pData, cbData));

    SectionParser data;
    RETURN_IF_FAILED(data.Set(pData, cbData));

    HRESULT hr = S_OK;
    if (BaseFile::SectionTypesEqual(type, gHierarchicalNamesSectionType))
    {
        const DEFFILE_HNAMES_HEADER* pHeader = _SECTION_PARSER_NEXT(data, DEFFILE_HNAMES_HEADER, &hr);
        RETURN_IF_FAILED(hr);

        m_header.cchLongestPath = pHeader->cchLongestPath;
        m_header.flags = pHeader->flags;
        m_header.numNodes = pHeader->numNodes;
        m_header.numScopes = pHeader->numScopes;
        m_header.numItems = pHeader->numItems;
        m_header.cchUtf16NamesPool = pHeader->cchNames;
        m_header.cbTotal = pHeader->cbTotal;
        m_header.cchAsciiNamesPool = 0;
        m_pHeader = &m_header;
    }
    else if (BaseFile::SectionTypesEqual(type, gHierarchicalNamesExSectionType))
    {
        m_pHeader = _SECTION_PARSER_NEXT(data, DEFFILE_HNAMES_HEADER_EX, &hr);
        RETURN_IF_FAILED(hr);
        m_header = *m_pHeader;
    }
    else
    {
        return E_NOTIMPL;
    }

    // Support for > 64k resources is not currently implemented
    if ((m_pHeader->flags & DEFFILE_HNAMES_FLAGS_LARGE) != 0)
    {
        m_largeNode = true;
    }

    UINT32 maxItems = DEFFILE_MAX_STANDARD_SIZE;
    if (m_largeNode)
    {
        maxItems = INT_MAX;
    }

    if ((m_pHeader->numScopes > maxItems) || (m_pHeader->numItems > maxItems) ||
        ((m_pHeader->numScopes + m_pHeader->numItems) > maxItems) || (m_pHeader->numNodes < (m_pHeader->numScopes + m_pHeader->numItems)))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    if (m_largeNode)
    {
        m_pNodesLarge = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numNodes, DEFFILE_HNAMES_NODE_LARGE, &hr);
        m_pScopesLarge = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numScopes, DEFFILE_HNAMES_SCOPE_LARGE, &hr);
        m_pItemsLarge = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numItems, UINT32, &hr);
    }
    else
    {
        m_pNodes = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numNodes, DEFFILE_HNAMES_NODE, &hr);
        m_pScopes = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numScopes, DEFFILE_HNAMES_SCOPE, &hr);
        m_pItems = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->numItems, UINT16, &hr);
    }

    m_pUtf16Names = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->cchUtf16NamesPool, WCHAR, &hr);
    m_pAsciiNames = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->cchAsciiNamesPool, char, &hr);
    RETURN_IF_FAILED(hr);

    if (m_largeNode)
    {
        RETURN_IF_FAILED(ScopesAtomPool<DEFFILE_HNAMES_SCOPE_LARGE>::CreateInstance(
            this, m_pScopesLarge, m_pHeader->numScopes, (ScopesAtomPool<DEFFILE_HNAMES_SCOPE_LARGE>**)&m_pScopeNames));
        RETURN_IF_FAILED(
            ItemsAtomPool<UINT32>::CreateInstance(this, m_pItemsLarge, m_pHeader->numItems, (ItemsAtomPool<UINT32>**)&m_pItemNames));
    }
    else
    {
        RETURN_IF_FAILED(ScopesAtomPool<DEFFILE_HNAMES_SCOPE>::CreateInstance(
            this, m_pScopes, m_pHeader->numScopes, (ScopesAtomPool<DEFFILE_HNAMES_SCOPE>**)&m_pScopeNames));
        RETURN_IF_FAILED(
            ItemsAtomPool<UINT16>::CreateInstance(this, m_pItems, m_pHeader->numItems, (ItemsAtomPool<UINT16>**)&m_pItemNames));
    }

    return S_OK;
}

HRESULT HierarchicalNames::CreateInstance(_In_ const IFileSection* pSection, _Outptr_ HierarchicalNames** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pSection);

    AutoDeletePtr<HierarchicalNames> pRtrn = new HierarchicalNames();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pSection->GetSectionType(), pSection, pSection->GetData(), pSection->GetDataSize()));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT HierarchicalNames::CreateInstance(
    _In_ const DEFFILE_SECTION_TYPEID& type,
    _In_reads_bytes_(cbData) const void* pData,
    _In_ int cbData,
    _Outptr_ HierarchicalNames** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pData);

    AutoDeletePtr<HierarchicalNames> pRtrn = new HierarchicalNames();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(type, nullptr, pData, cbData));

    *result = pRtrn.Detach();
    return S_OK;
}

HierarchicalNames::~HierarchicalNames()
{
    delete m_pScopeNames;
    delete m_pItemNames;

    m_pScopeNames = NULL;
    m_pItemNames = NULL;
}

_Success_(return ) bool HierarchicalNames::TryGetName(
    __in int index,
    __inout_opt StringResult* pResult,
    __out_opt int* pScopeIndexOut,
    __out_opt int* pItemIndexOut) const
{
    return TryGetName(index, 0, pResult, pScopeIndexOut, pItemIndexOut);
}

_Success_(return ) bool HierarchicalNames::TryGetName(
    __in int nodeIndex,
    __in int relativeToScope,
    __inout_opt StringResult* pNameOut,
    __out_opt int* pScopeIndexOut,
    __out_opt int* pItemIndexOut) const
{
    if (m_pHeader->numNodes == 0 || m_pHeader->numScopes == 0)
    {
        return false;
    }

    if ((nodeIndex < 0) || (nodeIndex > m_pHeader->numNodes - 1))
    {
        return false;
    }

    if ((relativeToScope < 0) || (relativeToScope > m_pHeader->numScopes - 1))
    {
        return false;
    }

    if (pScopeIndexOut != nullptr)
    {
        *pScopeIndexOut = -1;
    }

    if (pItemIndexOut != nullptr)
    {
        *pItemIndexOut = -1;
    }

    // Get the name node for our scope
    int relativeToNode = m_largeNode ? m_pScopesLarge[relativeToScope].nameNodeIndex : m_pScopes[relativeToScope].nameNodeIndex;
    if ((relativeToNode < 0) || (relativeToNode > m_pHeader->numNodes - 1))
    {
        return false;
    }

    const DEFFILE_HNAMES_NODE_LARGE* pNode; // node we're resolving
    DEFFILE_HNAMES_NODE_LARGE node;
    if (m_largeNode)
    {
        pNode = &m_pNodesLarge[nodeIndex];
    }
    else
    {
        node = HNAMES_NODE_TO_HNAMES_NODE_LARGE(&m_pNodes[nodeIndex]);
        pNode = &node;
    }

    // first get info about the node, if our caller wants it
    if (pScopeIndexOut != nullptr)
    {
        if ((pNode->flagsAndNameOffsetHigh & DEFFILE_HNAMES_FLAGS_NODE_IS_SCOPE) != 0)
        {
            *pScopeIndexOut = pNode->payload;
        }
        else
        {
            *pScopeIndexOut = -1;
        }
    }

    if (pItemIndexOut != nullptr)
    {
        if ((pNode->flagsAndNameOffsetHigh & DEFFILE_HNAMES_FLAGS_NODE_IS_SCOPE) == 0)
        {
            *pItemIndexOut = pNode->payload;
        }
        else
        {
            *pItemIndexOut = -1;
        }
    }

    if (pNameOut != nullptr)
    {
        // Now we'll have to build up the file name from back to front.  First we
        // make sure that our StringResult contains a buffer with enough room
        // for our full path (up to our logical root).
        // If we're at the root we need a leading slash, otherwise the slash is part of the prefix
        int cchPrefix =
            ((relativeToNode > 0) ?
                 (m_largeNode ? m_pNodesLarge[relativeToNode].cchFullPath + 1 : m_pNodes[relativeToNode].cchFullPath + 1) :
                 0); // size of path to logical root
        int cchThis = pNode->cchFullPath - cchPrefix; // size of path to absolute root
        int cchNext = cchThis;

        if (cchThis < 0)
        {
            return false;
        }
        else
        {
            PWSTR pName;
            pNameOut->SetEmptyContents(cchThis + 1, &pName, nullptr);
            if (!pName)
            {
                return false;
            }
            // Remember, we're writing from back to front.
            // First, write the NULL terminator.
            pName[cchNext] = L'\0';

            // don't bother walking the root node
            if (pNode->cchFullPath > 0)
            {
                // Make sure the name is inside the names pool and fits in the buffer.
                UINT32 nameOffset = HNamesGetNodeNameOffsetLarge(pNode);
                cchNext -= pNode->cchName;
                if ((cchNext < 0) || FAILED(CopyNameSegment(pNode->flagsAndNameOffsetHigh, nameOffset, pNode->cchName, &pName[cchNext])))
                {
                    return false;
                }

                // If we aren't at the beginning of the string, prepend a slash
                if (cchNext > 0)
                {
                    pName[--cchNext] = GetDefaultPathSeparator();
                }

                // Now walk the tree and write our parent scopes...
                const DEFFILE_HNAMES_NODE_LARGE* pScopeNode;
                DEFFILE_HNAMES_NODE_LARGE scopeNode;
                int scopeNodeIndex = pNode->parentNodeIndex;

                // Keep going until we hit the root or our scopeNode
                while ((scopeNodeIndex > 0) && (scopeNodeIndex != relativeToNode))
                {

                    // Make sure our folder reference is legal
                    if ((scopeNodeIndex < 0) || (scopeNodeIndex > m_pHeader->numNodes - 1))
                    {
                        return false;
                    }

                    if (m_largeNode)
                    {
                        pScopeNode = &m_pNodesLarge[scopeNodeIndex];
                    }
                    else
                    {
                        scopeNode = HNAMES_NODE_TO_HNAMES_NODE_LARGE(&m_pNodes[scopeNodeIndex]);
                        pScopeNode = &scopeNode;
                    }
                    cchNext -= pScopeNode->cchName;

                    // Now make sure that the scope name is in the string pool and fits
                    // in the remaining buffer.
                    nameOffset = HNamesGetNodeNameOffsetLarge(pScopeNode);
                    if ((cchNext < 0) ||
                        FAILED(CopyNameSegment(pScopeNode->flagsAndNameOffsetHigh, nameOffset, pScopeNode->cchName, &pName[cchNext])))
                    {
                        // most likely our supposed scope isn't a parent.
                        return false;
                    }

                    // If we aren't at the beginning of the string, prepend a slash
                    if (cchNext > 0)
                    {
                        pName[--cchNext] = GetDefaultPathSeparator();
                    }

                    scopeNodeIndex = pScopeNode->parentNodeIndex;
                }

                if (cchNext != 0)
                {
                    // We should be at the start of the buffer.
                    // Fail if we aren't.
                    return false;
                }
            }
        }
    }
    return true;
}

bool HierarchicalNames::Contains(
    __in PCWSTR pPath,
    __out_opt int* pScopeIndexOut,
    __out_opt int* pItemIndexOut,
    __out_opt int* pNameIndexOut) const
{
    return Contains(pPath, 0, pScopeIndexOut, pItemIndexOut, pNameIndexOut);
}

_Success_(return == true)
bool HierarchicalNames::Contains(
    __in PCWSTR pPath,
    __in int relativeToScope,
    __out_opt int* pScopeIndexOut,
    __out_opt int* pItemIndexOut,
    __out_opt int* pNameIndexOut) const
{
    if (m_pHeader->numNodes == 0 || m_pHeader->numScopes == 0)
    {
        return false;
    }

    if (DefString_IsEmpty(pPath))
    {
        return false;
    }

    if ((relativeToScope < 0) || (relativeToScope > m_pHeader->numScopes - 1))
    {
        return false;
    }

    if (pScopeIndexOut != nullptr)
    {
        *pScopeIndexOut = -1;
    }
    if (pItemIndexOut != nullptr)
    {
        *pItemIndexOut = -1;
    }
    if (pNameIndexOut != nullptr)
    {
        *pNameIndexOut = -1;
    }

    // Start at 'relativeTo'
    const DEFFILE_HNAMES_SCOPE_LARGE* pScope;
    DEFFILE_HNAMES_SCOPE_LARGE scopeNode;
    if (m_largeNode)
    {
        pScope = &m_pScopesLarge[relativeToScope];
    }
    else
    {
        scopeNode = HNAMES_SCOPE_TO_HNAMES_SCOPE_LARGE(&m_pScopes[relativeToScope]);
        pScope = &scopeNode;
    }

    if ((pScope->nameNodeIndex < 0) || (pScope->nameNodeIndex > m_pHeader->numNodes - 1))
    {
        return false;
    }

    // Local copy to step through.
    PCWSTR pStr = pPath;
    WCHAR initialChar = 0;
    // ignore leading separator, if present
    if (IsPathSeparator(pStr[0]))
    {
        pStr++;
    }

    const DEFFILE_HNAMES_NODE_LARGE* pMatch = nullptr;
    DEFFILE_HNAMES_NODE_LARGE matchNode;
    PCWSTR pSegmentEnd = nullptr;
    int nameIndex = 0;

    while (pStr[0] != L'\0')
    {
        // multiple separators not allowed
        if (IsPathSeparator(pStr[0]))
        {
            return false;
        }

        // make sure we don't overrun the nodes array
        if ((pScope->firstChildNameNode + pScope->numChildNames) > m_pHeader->numNodes)
        {
            return false;
        }

        int numChildren = pScope->numChildNames;
        const DEFFILE_HNAMES_NODE* pChildren = nullptr;
        const DEFFILE_HNAMES_NODE_LARGE* pChildrenLarge = nullptr;

        if (m_largeNode)
        {
            pChildrenLarge = &m_pNodesLarge[pScope->firstChildNameNode];
        }
        else
        {
            pChildren = &m_pNodes[pScope->firstChildNameNode];
        }

        pMatch = nullptr;
        pSegmentEnd = nullptr;
        initialChar = towupper(pStr[0]);

        for (int i = 0; (i < numChildren); i++)
        {
            WCHAR initChildChar = (m_largeNode ? pChildrenLarge[i].initialChar : pChildren[i].initialChar);
            // WORKING HERE - NEED TO HANDLE ASCII IN COMPARISON
            if ((initChildChar == initialChar) || (initChildChar == 0))
            {
                int diff;
                if (m_largeNode)
                {
                    if (FAILED(CompareNameSegment<DEFFILE_HNAMES_NODE_LARGE>(&pChildrenLarge[i], pStr, &diff)) || (diff > 0))
                    {
                        // we've either hit an error
                        // or passed the last possiblse match.
                        return false;
                    }
                }
                else
                {
                    if (FAILED(CompareNameSegment<DEFFILE_HNAMES_NODE>(&pChildren[i], pStr, &diff)) || (diff > 0))
                    {
                        // we've either hit an error
                        // or passed the last possiblse match.
                        return false;
                    }
                }

                if (diff == 0)
                {
                    if (m_largeNode)
                    {
                        pMatch = &pChildrenLarge[i];
                        pSegmentEnd = &pStr[pChildrenLarge[i].cchName];
                        nameIndex = static_cast<int>(&pChildrenLarge[i] - m_pNodesLarge);
                    }
                    else
                    {
                        matchNode = HNAMES_NODE_TO_HNAMES_NODE_LARGE(&pChildren[i]);
                        pMatch = &matchNode;
                        pSegmentEnd = &pStr[pChildren[i].cchName];
                        nameIndex = static_cast<int>(&pChildren[i] - m_pNodes);
                    }
                    break;
                }
            }
        }

        if (pMatch == nullptr)
        {
            // no match found
            return false;
        }

        // if we get here, pMatch is the child node that exactly matches the next segment we're
        // looking for & pSegmentEnd is the character at the end of the segment (either NUL
        // or a path separator)

        if (pSegmentEnd[0] == L'\0')
        {
            // Hit the end of the input string. We're done.
            break;
        }

        // Else we're at a separator.

        if ((pMatch->flagsAndNameOffsetHigh & DEFFILE_HNAMES_FLAGS_NODE_IS_SCOPE) == 0)
        {
            // We're not done with our input but we hit a leaf.  Can't match.
            return false;
        }

        // Not an exact match but we're at an interior (scope) node.  Skip over this segment
        // and separator and keep looking.
        if (pMatch->payload >= m_pHeader->numScopes)
        {
            // illegal offset. file is bad.
            return false;
        }

        if (m_largeNode)
        {
            pScope = &m_pScopesLarge[pMatch->payload];
        }
        else
        {
            scopeNode = HNAMES_SCOPE_TO_HNAMES_SCOPE_LARGE(&m_pScopes[pMatch->payload]);
            pScope = &scopeNode;
        }
        pStr = pSegmentEnd + 1;
    }

    if (pMatch != nullptr)
    {
        // We're at the end of the input string.  Return this node.
        bool isScope = ((pMatch->flagsAndNameOffsetHigh & DEFFILE_HNAMES_FLAGS_NODE_IS_SCOPE) != 0);
        if (pScopeIndexOut != nullptr)
        {
            *pScopeIndexOut = (isScope ? pMatch->payload : -1);
        }

        if (pItemIndexOut != nullptr)
        {
            *pItemIndexOut = (isScope ? -1 : pMatch->payload);
        }

        if (pNameIndexOut != nullptr)
        {
            *pNameIndexOut = nameIndex;
        }
        return true;
    }
    return false;
}

_Success_(return ) bool HierarchicalNames::TryGetScopeInfo(
    __in int scopeIndex,
    __inout StringResult* pNameOut,
    __out_opt int* pNumChildrenOut) const
{
    if (m_pHeader->numScopes == 0)
    {
        return false;
    }

    if ((scopeIndex < 0) || (scopeIndex > m_pHeader->numScopes - 1))
    {
        return false;
    }

    if (pNameOut == nullptr)
    {
        return false;
    }

    const DEFFILE_HNAMES_SCOPE_LARGE* pScope;
    DEFFILE_HNAMES_SCOPE_LARGE scope;
    if (m_largeNode)
    {
        pScope = &m_pScopesLarge[scopeIndex];
    }
    else
    {
        scope = HNAMES_SCOPE_TO_HNAMES_SCOPE_LARGE(&m_pScopes[scopeIndex]);
        pScope = &scope;
    }

    if (pNumChildrenOut != nullptr)
    {
        *pNumChildrenOut = pScope->numChildNames;
    }

    return TryGetName(pScope->nameNodeIndex, pNameOut);
}

_Success_(return ) bool HierarchicalNames::TryGetScopeChild(
    __in int scopeIndex,
    __in int childIndex,
    __out_opt int* pChildScopeIndexOut,
    __out_opt int* pChildItemIndexOut) const
{
    if (m_pHeader->numScopes == 0)
    {
        return false;
    }

    if ((scopeIndex < 0) || (scopeIndex > m_pHeader->numScopes - 1))
    {
        return false;
    }

    if ((pChildScopeIndexOut == nullptr) || (pChildItemIndexOut == nullptr))
    {
        return false;
    }

    const DEFFILE_HNAMES_SCOPE_LARGE* pScope;
    DEFFILE_HNAMES_SCOPE_LARGE scope;
    if (m_largeNode)
    {
        pScope = &m_pScopesLarge[scopeIndex];
    }
    else
    {
        scope = HNAMES_SCOPE_TO_HNAMES_SCOPE_LARGE(&m_pScopes[scopeIndex]);
        pScope = &scope;
    }

    // Make sure they're asking for a child that exists.
    if (pScope->numChildNames == 0)
    {
        return false;
    }

    if ((childIndex < 0) || (childIndex > pScope->numChildNames - 1))
    {
        return false;
    }

    // make sure the child refers to a name node that exists
    if ((pScope->firstChildNameNode + childIndex) >= m_pHeader->numNodes)
    {
        return false;
    }

    const DEFFILE_HNAMES_NODE_LARGE* pChildNode;
    DEFFILE_HNAMES_NODE_LARGE childNode;
    if (m_largeNode)
    {
        pChildNode = &m_pNodesLarge[pScope->firstChildNameNode + childIndex];
    }
    else
    {
        childNode = HNAMES_NODE_TO_HNAMES_NODE_LARGE(&m_pNodes[pScope->firstChildNameNode + childIndex]);
        pChildNode = &childNode;
    }

    // Now report either the schema or item index, depending on flag
    if ((pChildNode->flagsAndNameOffsetHigh & DEFFILE_HNAMES_FLAGS_NODE_IS_SCOPE) != 0)
    {

        if (pChildNode->payload <= scopeIndex)
        {
            // Scopes are a tree in order of declaration, so a child scope
            // with a lower index means a possible cycle and is illegal.
            *pChildScopeIndexOut = -1;
            *pChildItemIndexOut = -1;
            return false;
        }

        if (pChildScopeIndexOut != nullptr)
        {
            *pChildScopeIndexOut = pChildNode->payload;
        }

        if (pChildItemIndexOut != nullptr)
        {
            *pChildItemIndexOut = -1;
        }
    }
    else
    {
        if (pChildScopeIndexOut != nullptr)
        {
            *pChildScopeIndexOut = -1;
        }

        if (pChildItemIndexOut != nullptr)
        {
            *pChildItemIndexOut = pChildNode->payload;
        }
    }
    return true;
}

_Success_(
    return ) bool HierarchicalNames::TryGetScopeChildName(__in int scopeIndex, __in int childIndex, __inout StringResult* pNameOut) const
{
    if (m_pHeader->numScopes == 0)
    {
        return false;
    }

    if ((scopeIndex < 0) || (scopeIndex > m_pHeader->numScopes - 1))
    {
        return false;
    }

    if (pNameOut == nullptr)
    {
        return false;
    }

    const DEFFILE_HNAMES_SCOPE_LARGE* pScope;
    DEFFILE_HNAMES_SCOPE_LARGE scope;
    if (m_largeNode)
    {
        pScope = &m_pScopesLarge[scopeIndex];
    }
    else
    {
        scope = HNAMES_SCOPE_TO_HNAMES_SCOPE_LARGE(&m_pScopes[scopeIndex]);
        pScope = &scope;
    }

    // Make sure they're asking for a child that exists.
    if (pScope->numChildNames == 0)
    {
        return false;
    }

    if ((childIndex < 0) || (childIndex > pScope->numChildNames - 1))
    {
        return false;
    }

    // make sure the child refers to a name node that exists
    if ((pScope->firstChildNameNode + childIndex) >= m_pHeader->numNodes)
    {
        return false;
    }

    if (m_largeNode)
    {
        const DEFFILE_HNAMES_NODE_LARGE* pChildNode = &m_pNodesLarge[pScope->firstChildNameNode + childIndex];
        return SUCCEEDED(GetName<DEFFILE_HNAMES_NODE_LARGE>(pChildNode, pNameOut));
    }

    const DEFFILE_HNAMES_NODE* pChildNode = &m_pNodes[pScope->firstChildNameNode + childIndex];
    return SUCCEEDED(GetName<DEFFILE_HNAMES_NODE>(pChildNode, pNameOut));
}

_Success_(return ) bool HierarchicalNames::TryGetItemInfo(__in int itemIndex, __inout StringResult* pNameOut) const
{
    if (m_pHeader->numItems == 0)
    {
        return false;
    }

    if ((itemIndex < 0) || (itemIndex > m_pHeader->numItems - 1))
    {
        return false;
    }

    if (pNameOut == nullptr)
    {
        return false;
    }

    return TryGetName(m_largeNode ? m_pItemsLarge[itemIndex] : m_pItems[itemIndex], pNameOut);
}

_Success_(return ) bool HierarchicalNames::TryGetItemLocalName(__in int itemIndex, __inout StringResult* pNameOut) const
{
    if (m_pHeader->numItems == 0)
    {
        return false;
    }

    if ((itemIndex < 0) || (itemIndex > m_pHeader->numItems - 1))
    {
        return false;
    }

    if (pNameOut == nullptr)
    {
        return false;
    }

    int nodeIndex = m_largeNode ? m_pItemsLarge[itemIndex] : m_pItems[itemIndex];

    if ((nodeIndex < 0) || (nodeIndex >= m_pHeader->numNodes))
    {
        return false;
    }

    const DEFFILE_HNAMES_NODE_LARGE* pNode;
    DEFFILE_HNAMES_NODE_LARGE node;

    if (m_largeNode)
    {
        pNode = &m_pNodesLarge[nodeIndex];
    }
    else
    {
        node = HNAMES_NODE_TO_HNAMES_NODE_LARGE(&m_pNodes[nodeIndex]);
        pNode = &node;
    }

    UINT32 nameOffset = HNamesGetNodeNameOffsetLarge(pNode);

    if ((pNode->flagsAndNameOffsetHigh & DEFFILE_HNAMES_FLAGS_NAME_IS_ASCII) == 0)
    {
        if ((nameOffset + pNode->cchName) >= m_pHeader->cchUtf16NamesPool)
        {
            return false;
        }
    }
    else if ((nameOffset + pNode->cchName) >= m_pHeader->cchAsciiNamesPool)
    {
        return false;
    }

    return SUCCEEDED(GetName<DEFFILE_HNAMES_NODE_LARGE>(pNode, pNameOut));
}

_Success_(return ) bool HierarchicalNames::TryGetRelativeItemName(
    _In_ int relativeToScope,
    _Inout_ int itemIndex,
    _Inout_ StringResult* pNameOut) const
{
    if (m_pHeader->numItems == 0)
    {
        return false;
    }

    if ((itemIndex < 0) || (itemIndex > m_pHeader->numItems - 1))
    {
        return false;
    }

    return TryGetName(m_largeNode ? m_pItemsLarge[itemIndex] : m_pItems[itemIndex], relativeToScope, pNameOut);
}

_Success_(return ) bool HierarchicalNames::TryGetRelativeScopeName(
    _In_ int relativeToScope,
    _Inout_ int scopeIndex,
    _Inout_ StringResult* pNameOut) const
{
    if (m_pHeader->numScopes == 0)
    {
        return false;
    }

    if ((scopeIndex < 0) || (scopeIndex > m_pHeader->numScopes - 1))
    {
        return false;
    }

    return TryGetName(
        m_largeNode ? m_pScopesLarge[scopeIndex].nameNodeIndex : m_pScopes[scopeIndex].nameNodeIndex, relativeToScope, pNameOut);
}

template<typename T>
HRESULT HierarchicalNames::CompareNameSegment(_In_ const T* pNode, _In_ PCWSTR pRequestedSegment, _Out_ int* result) const
{
    *result = -1;

    UINT32 nameOffset = GetNodeNameOffset(pNode);
    int diff = -1;

    if ((pNode->flagsAndNameOffsetHigh & DEFFILE_HNAMES_FLAGS_NAME_IS_ASCII) == 0)
    {
        if ((nameOffset + pNode->cchName) >= m_pHeader->cchUtf16NamesPool)
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        int cchRequested = static_cast<int>(wcslen(pRequestedSegment));
        int cchCompare = min(pNode->cchName, cchRequested);

#pragma prefast(suppress : 26035, "The names segment is terminated, and we ensure that we don't go over the end above.")
        diff = CompareSegments(&m_pUtf16Names[nameOffset], cchCompare, pRequestedSegment, cchCompare);

        if ((diff == 0) && (pNode->cchName > cchRequested))
        {
            diff = -1;
        }
    }
    else
    {
        if ((nameOffset + pNode->cchName) >= m_pHeader->cchAsciiNamesPool)
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        diff = CompareStoredAsciiSegment(&m_pAsciiNames[nameOffset], pNode->cchName, pRequestedSegment);
    }

    if (diff == 0)
    {
        // exact match for as far as the node name goes.  Check to see if the name we're looking for is longer
        PCWSTR pSegmentEnd = &pRequestedSegment[pNode->cchName];
        if ((*pSegmentEnd == L'\0') || IsPathSeparator(*pSegmentEnd))
        {
            diff = 0;
        }
        else
        {
            // the name we're looking for is longer, so we're smaller.
            diff = -1;
        }
    }

    *result = diff;
    return S_OK;
}

HRESULT
HierarchicalNames::GetNumDescendents(_In_ int scopeIndex, _In_ UINT32 currentDepth, _Out_opt_ int* pNumScopes, _Out_opt_ int* pNumItems)
    const
{
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), m_pHeader->numScopes == 0);
    RETURN_HR_IF(E_INVALIDARG, (scopeIndex < 0) || (scopeIndex > m_pHeader->numScopes - 1));

    const DEFFILE_HNAMES_SCOPE_LARGE* pScope;
    DEFFILE_HNAMES_SCOPE_LARGE scope;
    if (m_largeNode)
    {
        pScope = &m_pScopesLarge[scopeIndex];
    }
    else
    {
        scope = HNAMES_SCOPE_TO_HNAMES_SCOPE_LARGE(&m_pScopes[scopeIndex]);
        pScope = &scope;
    }

    int numScopes = 0;
    int numItems = 0;

    for (int i = 0; i < pScope->numChildNames; i++)
    {
        // make sure the child refers to a name node that exists
        if ((pScope->firstChildNameNode + i) >= m_pHeader->numNodes)
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        BYTE flags;
        int payload;
        if (m_largeNode)
        {
            const DEFFILE_HNAMES_NODE_LARGE* pChildNode = &m_pNodesLarge[pScope->firstChildNameNode + i];
            flags = pChildNode->flagsAndNameOffsetHigh;
            payload = pChildNode->payload;
        }
        else
        {
            const DEFFILE_HNAMES_NODE* pChildNode = &m_pNodes[pScope->firstChildNameNode + i];
            flags = pChildNode->flagsAndNameOffsetHigh;
            payload = pChildNode->payload;
        }

        // Now report either the schema or item index, depending on flag
        if ((flags & DEFFILE_HNAMES_FLAGS_NODE_IS_SCOPE) != 0)
        {
            int nChildItems = 0;
            int nChildScopes = 0;

            if ((payload == scopeIndex) || (currentDepth > m_pHeader->numScopes))
            {
                return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
            }

            RETURN_IF_FAILED(GetNumDescendents(payload, currentDepth + 1, &nChildScopes, &nChildItems));

            numScopes += nChildScopes + 1;
            numItems += nChildItems;
        }
        else
        {
            numItems++;
        }
    }

    if (pNumScopes != nullptr)
    {
        *pNumScopes = numScopes;
    }

    if (pNumItems != nullptr)
    {
        *pNumItems = numItems;
    }
    return S_OK;
}

HRESULT HierarchicalNames::GetDescendents(
    _In_ int scopeIndex,
    _In_ int sizeScopes,
    _Out_writes_to_opt_(sizeScopes, *pNumScopesWritten) int* pScopesOut,
    _Out_opt_ int* pNumScopesWritten,
    _In_ int sizeItems,
    _Out_writes_to_opt_(sizeItems, *pNumItemsWritten) int* pItemsOut,
    _Out_opt_ int* pNumItemsWritten) const
{
    if (pNumScopesWritten != nullptr)
    {
        *pNumScopesWritten = 0;
    }

    if (pNumItemsWritten != nullptr)
    {
        *pNumItemsWritten = 0;
    }

    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), m_pHeader->numScopes == 0);
    RETURN_HR_IF(E_INVALIDARG, (scopeIndex < 0) || (scopeIndex > m_pHeader->numScopes - 1));

    const DEFFILE_HNAMES_SCOPE_LARGE* pScope;
    DEFFILE_HNAMES_SCOPE_LARGE scope;
    if (m_largeNode)
    {
        pScope = &m_pScopesLarge[scopeIndex];
    }
    else
    {
        scope = HNAMES_SCOPE_TO_HNAMES_SCOPE_LARGE(&m_pScopes[scopeIndex]);
        pScope = &scope;
    }

    int numScopesWritten = 0;
    int numItemsWritten = 0;

    for (int i = 0; i < pScope->numChildNames; i++)
    {
        // make sure the child refers to a name node that exists
        if ((pScope->firstChildNameNode + i) >= m_pHeader->numNodes)
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
        }

        BYTE flags;
        int payload;

        if (m_largeNode)
        {
            const DEFFILE_HNAMES_NODE_LARGE* pChildNode = &m_pNodesLarge[pScope->firstChildNameNode + i];
            flags = pChildNode->flagsAndNameOffsetHigh;
            payload = pChildNode->payload;
        }
        else
        {
            const DEFFILE_HNAMES_NODE* pChildNode = &m_pNodes[pScope->firstChildNameNode + i];
            flags = pChildNode->flagsAndNameOffsetHigh;
            payload = pChildNode->payload;
        }

        // Now report either the schema or item index, depending on flag
        if ((flags & DEFFILE_HNAMES_FLAGS_NODE_IS_SCOPE) != 0)
        {
            if (pScopesOut != nullptr)
            {
                if (numScopesWritten >= sizeScopes)
                {
                    return HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
                }
                pScopesOut[numScopesWritten] = payload;
                numScopesWritten++;
            }

            int nChildItemsWritten = 0;
            int nChildScopesWritten = 0;
            RETURN_IF_FAILED(GetDescendents(
                payload,
                (sizeScopes - numScopesWritten),
                (pScopesOut ? &pScopesOut[numScopesWritten] : nullptr),
                &nChildScopesWritten,
                (sizeItems - numItemsWritten),
                (pItemsOut ? &pItemsOut[numItemsWritten] : nullptr),
                &nChildItemsWritten));

            numScopesWritten += nChildScopesWritten;
            numItemsWritten += nChildItemsWritten;
        }
        else if (pItemsOut != nullptr)
        {
            if (numItemsWritten >= sizeItems)
            {
                return HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
            }
            pItemsOut[numItemsWritten] = payload;
            numItemsWritten++;
        }
    }

    if (pNumScopesWritten != nullptr)
    {
        *pNumScopesWritten = numScopesWritten;
    }

    if (pNumItemsWritten != nullptr)
    {
        *pNumItemsWritten = numItemsWritten;
    }
    return S_OK;
}

const DEFFILE_SECTION_TYPEID HierarchicalNames::GetSectionTypeId() { return gHierarchicalNamesSectionType; }

} // namespace Microsoft::Resources
