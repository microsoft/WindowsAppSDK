// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "StdAfx.h"
#include "mrm/build/HNamesBuilder.h"
#include "mrm/Checksums.h"

namespace Microsoft::Resources::Build
{

// HNamesNode - common to ItemInfo and ScopeInfo

HNamesNode::HNamesNode(__in const HierarchicalNamesConfig* pConfig) :
    m_pParentScope(nullptr), m_segment(pConfig), m_index(-1), m_nameIndex(-1)
{}

HNamesNode::HNamesNode(_In_ ScopeInfo* pParent) : m_segment(pParent->GetGlobalNodes()->GetConfig())
{
    m_pParentScope = pParent;
    m_index = -1;
    m_nameIndex = -1;
}

HRESULT HNamesNode::Init(_In_ const HierarchicalNameSegment* name)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, m_pParentScope);
    RETURN_IF_FAILED(m_segment.SetCopy(name));
    return S_OK;
}

int HNamesNode::CompareTo(__in PCWSTR pOtherName) const
{
    WCHAR otherInitial = GetConfig()->GetSegmentInitialChar(pOtherName);
    if (m_segment.GetInitialChar() > otherInitial)
    {
        return 1;
    }
    else if (otherInitial > m_segment.GetInitialChar())
    {
        return -1;
    }

    return GetConfig()->CompareSegments(m_segment.GetName(), pOtherName);
}

int HNamesNode::CompareTo(__in const HNamesNode* pOther) const
{
    if (m_segment.GetInitialChar() > pOther->GetInitialChar())
    {
        return 1;
    }
    else if (pOther->GetInitialChar() > m_segment.GetInitialChar())
    {
        return -1;
    }

    return GetConfig()->CompareSegments(m_segment.GetName(), pOther->GetName());
}

bool HNamesNode::Equals(_In_ const HNamesNode* pOther) const
{
    return ((m_segment.GetHash() == pOther->GetHash()) && (CompareTo(pOther) == Def_Equal));
}

HRESULT HNamesNode::GetFullPath(__inout StringResult* pPathOut) const
{
    // Use SetEmptyContents here to ensure that there _is_ a buffer.
    // Using truncate could lead to pPathOut containing a NULL. From
    // a version checksum perspective (Null != ""), so this function
    // has to guarantee a buffer on return or checksum version
    // becomes non-deterministic.
    RETURN_IF_FAILED(pPathOut->SetEmptyContents(1));
    RETURN_IF_FAILED(ConcatPath(pPathOut));
    return S_OK;
}

HRESULT HNamesNode::ConcatPath(__inout StringResult* pPathOut) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pPathOut);

    if (m_pParentScope != nullptr)
    {
        RETURN_IF_FAILED(m_pParentScope->ConcatPath(pPathOut));
    }

    if (!DefString_IsEmpty(m_segment.GetName()))
    {
        RETURN_IF_FAILED(pPathOut->ConcatPathElement(m_segment.GetName(), GetConfig()->GetDefaultPathSeparator()));
    }
    return S_OK;
}

int HNamesNode::GetFullPathLength() const
{
    size_t len = (DefString_IsEmpty(m_segment.GetName()) ? 0 : wcslen(m_segment.GetName()));
    ScopeInfo* pParent = m_pParentScope;

    while (pParent != nullptr)
    {
        PCWSTR pParentName = pParent->GetName();
        if (!DefString_IsEmpty(pParentName))
        {
            len += wcslen(pParentName) + 1; // +1 for separator
        }
        pParent = pParent->GetParentScope();
    }
    return static_cast<int>(len);
}

// ItemInfo - describes a single item of interest
ItemInfo::ItemInfo(_In_ ScopeInfo* pParent) : HNamesNode(pParent) {}

ItemInfo::~ItemInfo() {}

HRESULT ItemInfo::CreateInstance(_In_ const HierarchicalNameSegment* pName, _In_ ScopeInfo* pParent, _Outptr_ ItemInfo** result)
{
    *result = nullptr;

    AutoDeletePtr<ItemInfo> pRtrn = new ItemInfo(pParent);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pName, pParent));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT ItemInfo::Init(_In_ const HierarchicalNameSegment* pName, _In_ ScopeInfo*)
{
    RETURN_IF_FAILED(HNamesNode::Init(pName));
    return S_OK;
}

HRESULT ItemInfo::AddToGlobal(_In_ ScopeInfo* parent)
{
    RETURN_IF_FAILED(parent->GetGlobalNodes()->AddItem(this, &m_index));
    return S_OK;
}

// ScopeInfo - Describes a single scope of interest and its contents

ScopeInfo::ScopeInfo(_In_ ScopeInfo* pParent) :
    HNamesNode(pParent),
    m_pChildren(nullptr),
    m_numChildScopes(0),
    m_numChildItems(0),
    m_totalNumItems(0),
    m_totalNumScopes(1),
    m_pGlobalNodes(nullptr)
{
    m_pGlobalNodes = pParent->GetGlobalNodes();
}

ScopeInfo::ScopeInfo(__in IHNamesGlobalNodes* pGlobalNodes) :
    HNamesNode(pGlobalNodes->GetConfig()),
    m_pChildren(nullptr),
    m_numChildScopes(0),
    m_numChildItems(0),
    m_totalNumItems(0),
    m_totalNumScopes(1),
    m_pGlobalNodes(nullptr)
{
    m_pGlobalNodes = pGlobalNodes;
}

HRESULT ScopeInfo::Init()
{
    RETURN_IF_FAILED(DynamicArray<HNamesNode*>::CreateInstance(20, &m_pChildren));
    return S_OK;
}

HRESULT ScopeInfo::Init(_In_ const HierarchicalNameSegment* name)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, name);
    RETURN_IF_FAILED(HNamesNode::Init(name));
    RETURN_IF_FAILED(DynamicArray<HNamesNode*>::CreateInstance(20, &m_pChildren));

    return S_OK;
}

ScopeInfo::~ScopeInfo()
{
    delete m_pChildren;
    // GlobalNodes owns the scopes and items and is responsible for deleting them
}

HRESULT ScopeInfo::CreateInstance(_In_ const HierarchicalNameSegment* pName, _In_ ScopeInfo* pParent, _Outptr_ ScopeInfo** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pName->GetName()) || (pParent == nullptr));

    AutoDeletePtr<ScopeInfo> pRtrn = new ScopeInfo(pParent);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pName));

    *result = pRtrn.Detach();
    return S_OK;
}

bool ScopeInfo::NoteSubscopeChanges(__in int numScopesAdded, __in int numItemsAdded)
{
    m_totalNumScopes += numScopesAdded;
    m_totalNumItems += numItemsAdded;
    return (m_pParentScope ? m_pParentScope->NoteSubscopeChanges(numScopesAdded, numItemsAdded) : true);
}

HRESULT ScopeInfo::NewRootScope(__in IHNamesGlobalNodes* pGlobalNodes, _Outptr_ ScopeInfo** result)
{
    *result = nullptr;

    AutoDeletePtr<ScopeInfo> pRtrn = new ScopeInfo(pGlobalNodes);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init());
    RETURN_IF_FAILED(pRtrn->AddToGlobal(nullptr));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT ScopeInfo::AddToGlobal(_In_ ScopeInfo* /*parent*/)
{
    RETURN_IF_FAILED(m_pGlobalNodes->AddScope(this, &m_index));
    return S_OK;
}

HNamesNode* ScopeInfo::GetChild(UINT i) const
{
    if (i < m_pChildren->Count())
    {
        HNamesNode* node;
        if (SUCCEEDED(m_pChildren->Get(i, &node)))
        {
            return node;
        }
    }

    return nullptr;
}

HNamesNode* ScopeInfo::GetFirstChild() const { return GetChild(0); }

bool ScopeInfo::TryGetChild(_In_ int index, _Outptr_opt_result_maybenull_ HNamesNode** ppChildOut) const
{
    if (ppChildOut != nullptr)
    {
        *ppChildOut = nullptr;
    }

    if ((index < 0) || (static_cast<UINT>(index) >= m_pChildren->Count()))
    {
        return false;
    }

    return (SUCCEEDED(m_pChildren->Get(static_cast<UINT>(index), ppChildOut)));
}

bool ScopeInfo::TryGetChild(_In_ const HierarchicalNameSegment* pName, _Outptr_opt_result_maybenull_ HNamesNode** ppChildOut) const
{
    if (ppChildOut != nullptr)
    {
        *ppChildOut = nullptr;
    }

    int startSearch = -1;
    int endSearch = -1;
    int insert = -1;

    if (FAILED(FindSearchRange(pName->GetName(), &startSearch, &endSearch, &insert)))
    {
        return false;
    }

    if (insert != -1)
    {
        return false;
    }

    int diff = 0;
    PCWSTR nodeName = pName->GetName();
    UINT insertPoint = FindInsertionPoint(nodeName, startSearch, endSearch, &diff);

    if (diff == 0)
    {
        if (SUCCEEDED(m_pChildren->Get(insertPoint, ppChildOut)))
        {
            return true;
        }
    }

    return false;
}

_Success_(return == true)
bool ScopeInfo::TryGetDescendent(_In_ PCWSTR pFullName, _Outptr_opt_result_maybenull_ HNamesNode** ppChildOut) const
{
    if (DefString_IsEmpty(pFullName))
    {
        return false;
    }

    if (ppChildOut != nullptr)
    {
        *ppChildOut = nullptr;
    }

    // process each segment
    HierarchicalName name(GetConfig());
    const ScopeInfo* pScope = this;
    HNamesNode* pChild = nullptr;

    (void)name.SetPathByRef(pFullName);

    while (name.HaveCurrentSegment())
    {
        if (!pScope->TryGetChild(name.GetCurrentSegment(), &pChild))
        {
            return false;
        }

        if (name.AdvanceToNextSegment())
        {
            if (!pChild->IsScope())
            {
                // Reached a leaf but have segments left in the name
                return false;
            }

            // descend to the selected child
            pScope = pChild->ToScope();
        }
    }

    // We've exhausted our input, this is it.
    if (ppChildOut != nullptr)
    {
        *ppChildOut = pChild;
    }
    return (pChild != nullptr);
}

HRESULT ScopeInfo::GetOrAddScope(__in PCWSTR pFullName, _Out_ ScopeInfo** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pFullName));

    // process each segment
    HierarchicalName name(GetConfig());
    ScopeInfo* pScope = this;

    RETURN_IF_FAILED(name.SetPathByRef(pFullName));

    while (name.HaveCurrentSegment())
    {
        RETURN_IF_FAILED(pScope->GetOrAddChildScope(name.GetCurrentSegment(), &pScope));

        name.AdvanceToNextSegment();
    }

    *result = pScope;
    return S_OK;
}

HRESULT ScopeInfo::GetOrAddItem(__in PCWSTR pFullName, _Out_ ItemInfo** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pFullName));

    // process each segment
    HierarchicalName name(GetConfig());
    ScopeInfo* pScope = this;

    RETURN_IF_FAILED(name.SetPathByRef(pFullName));

    while (name.HaveNextSegment())
    {
        RETURN_IF_FAILED(pScope->GetOrAddChildScope(name.GetCurrentSegment(), &pScope));

        name.AdvanceToNextSegment();
    }

    if (name.HaveCurrentSegment())
    {
        return pScope->GetOrAddChildItem(name.GetCurrentSegment(), result);
    }

    return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
}

HRESULT ScopeInfo::GetOrAddChildScope(_In_ const HierarchicalNameSegment* pSegment, _Out_ ScopeInfo** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pSegment->GetName()));

    if (!GetConfig()->IsValidSegment(pSegment->GetName()))
    {
        return HRESULT_FROM_WIN32(ERROR_BAD_FORMAT);
    }

    AutoDeletePtr<ScopeInfo> pRtrn;
    RETURN_IF_FAILED(ScopeInfo::CreateInstance(pSegment, this, &pRtrn));

    HNamesNode* foundNode;
    RETURN_IF_FAILED(GetOrAddChildNode(pRtrn, &foundNode));

    if (foundNode != nullptr)
    {
        // already exists
        if (!foundNode->IsScope())
        {
            // Oops. It exists but it's an item!
            return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
        }

        *result = foundNode->ToScope();
        return S_OK;
    }

    RETURN_IF_FAILED(pRtrn->AddToGlobal(this));

    m_numChildScopes++;
    NoteSubscopeChanges(1, 0);
    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT ScopeInfo::GetOrAddChildItem(_In_ const HierarchicalNameSegment* pName, _Out_ ItemInfo** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pName->GetName()));

    if (!GetConfig()->IsValidSegment(pName->GetName()))
    {
        return HRESULT_FROM_WIN32(ERROR_BAD_FORMAT);
    }

    AutoDeletePtr<ItemInfo> pRtrn;
    RETURN_IF_FAILED(ItemInfo::CreateInstance(pName, this, &pRtrn));

    HNamesNode* foundNode;
    RETURN_IF_FAILED(GetOrAddChildNode(pRtrn, &foundNode));

    if (foundNode != nullptr)
    {
        // already exists
        if (foundNode->IsScope())
        {
            // Oops. It exists but it's a scope!
            return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
        }

        *result = foundNode->ToItem();
        return S_OK;
    }

    RETURN_IF_FAILED(pRtrn->AddToGlobal(this));

    m_numChildItems++;
    NoteSubscopeChanges(0, 1);
    *result = pRtrn.Detach();
    return S_OK;
}

// Find the range where the initial char matches.
// startSearch, endSearch: start and end locations of the matching range. -1 if no match
// insert: -1 if range found, otherwise the location to insert the new node.
HRESULT ScopeInfo::FindSearchRange(_In_ PCWSTR nodeName, _Out_ int* startSearch, _Out_ int* endSearch, _Out_ int* insert) const
{
    *startSearch = -1;
    *endSearch = -1;
    *insert = -1;
    WCHAR newInitial = GetConfig()->GetSegmentInitialChar(nodeName);

    int size = static_cast<int>(m_pChildren->Count());
    if (size == 0)
    {
        *insert = 0;
        return S_OK;
    }

    int low = 0;
    int high = size - 1;
    int mid;
    // find the start location
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        HNamesNode* currentNode;
        RETURN_IF_FAILED(m_pChildren->Get(static_cast<UINT>(mid), &currentNode));
        WCHAR nodeInitial = currentNode->GetInitialChar();
        if (nodeInitial == newInitial)
        {
            *startSearch = mid;
            high = mid - 1;
        }
        else if (nodeInitial > newInitial)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    if (*startSearch == -1)
    {
        // no match
        *insert = low;
        return S_OK;
    }

    low = 0;
    high = size - 1;

    // find the end location
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        HNamesNode* currentNode;
        RETURN_IF_FAILED(m_pChildren->Get(static_cast<UINT>(mid), &currentNode));
        WCHAR nodeInitial = currentNode->GetInitialChar();
        if (nodeInitial == newInitial)
        {
            *endSearch = mid;
            low = mid + 1;
        }
        else if (nodeInitial > newInitial)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return S_OK;
}

UINT ScopeInfo::FindInsertionPoint(_In_ PCWSTR pName, _In_ UINT first, _In_ UINT last, _Out_ int* pDiffOut) const
{
    UINT mid = (first + last) / 2;

    DEFCOMPARISON firstDiff = Def_CompareError;
    DEFCOMPARISON midDiff = Def_CompareError;
    DEFCOMPARISON lastDiff = Def_CompareError;
    HNamesNode* pFirst = nullptr;
    HNamesNode* pMid = nullptr;
    HNamesNode* pLast = nullptr;

    int nNodes = (last - first + 1);

    while (true)
    {
        // index should always be in range. Don't check the error
        m_pChildren->Get(first, &pFirst);
        m_pChildren->Get(last, &pLast);

        if (firstDiff == Def_CompareError)
        {
            firstDiff = DefString_ICompare(pName, pFirst->GetName());
        }

        if ((firstDiff == Def_Less) || (firstDiff == Def_Equal))
        {
            // less than or equal to the first
            *pDiffOut = firstDiff;
            return first;
        }

        if (lastDiff == Def_CompareError)
        {
            lastDiff = DefString_ICompare(pName, pLast->GetName());
        }

        if ((lastDiff == Def_Greater) || (lastDiff == Def_Equal))
        {
            // greater than or equal to the last
            *pDiffOut = lastDiff;
            return last;
        }

        // somewhere in the middle.
        if (nNodes > 3)
        {
            // if we still have a bunch of nodes, continue to divide and conquer
            m_pChildren->Get(mid, &pMid);
            midDiff = DefString_ICompare(pName, pMid->GetName());
            if (midDiff == Def_Equal)
            {
                *pDiffOut = midDiff;
                return mid;
            }
            else if (midDiff == Def_Less)
            {
                last = mid;
                mid = (first + last) / 2;
                nNodes = (last - first + 1);

                lastDiff = midDiff;
                midDiff = Def_CompareError;
            }
            else if (midDiff == Def_Greater)
            {
                first = mid;
                mid = (first + last) / 2;
                nNodes = (last - first + 1);

                firstDiff = midDiff;
                midDiff = Def_CompareError;
            }
        }
        else
        {
            // Down to (approximately) three. Go linear.
            while (pFirst != nullptr)
            {
                if (firstDiff == Def_CompareError)
                {
                    firstDiff = DefString_ICompare(pName, pFirst->GetName());
                }

                if ((firstDiff == Def_Greater) && (pFirst != pLast))
                {
                    // keep looking
                    first++;
                    m_pChildren->Get(first, &pFirst);
                    firstDiff = Def_CompareError;
                }
                else
                {
                    // Hit one of:
                    // 1) A match
                    // 2) The next largest entry
                    // 3) The end of our range
                    *pDiffOut = firstDiff;
                    return first;
                }
            }
        }
    }

    // should never get here
    return -1;
}

HRESULT ScopeInfo::GetOrAddChildNode(_In_ HNamesNode* newNode, _Out_ HNamesNode** foundNode)
{
    *foundNode = nullptr;

    int startSearch = -1;
    int endSearch = -1;
    int insert = -1;
    PCWSTR nodeName = newNode->GetName();

    RETURN_IF_FAILED(FindSearchRange(nodeName, &startSearch, &endSearch, &insert));
    if (insert != -1)
    {
        RETURN_IF_FAILED(m_pChildren->Insert(newNode, (UINT)insert));
        return S_OK;
    }

    int diff = 0;
    UINT insertPoint = FindInsertionPoint(nodeName, startSearch, endSearch, &diff);

    if (diff == 0)
    {
        RETURN_IF_FAILED(m_pChildren->Get(insertPoint, foundNode));
        return S_OK;
    }

    // Not found. Insert at insertPoint if diff < 0, or insert after insertPoint if diff > 0.
    RETURN_IF_FAILED(m_pChildren->Insert(newNode, diff > 0 ? insertPoint + 1 : insertPoint));
    return S_OK;
}

class HNamesNodeAtomPool : public IAtomPool
{
public:
    virtual ~HNamesNodeAtomPool() {}

    bool Contains(__in PCWSTR pString) const
    {
        Atom atom;
        return TryGetAtom(pString, &atom);
    }

    bool Contains(__in Atom atom) const
    {
        return (atom.GetPoolIndex() == m_poolIndex) && (atom.GetIndex() >= 0) && (atom.GetIndex() < GetNumNames());
    }

    bool Equals(__in Atom atom, __in PCWSTR pString) const
    {
        Atom foundAtom = Atom::NullAtom;
        return (TryGetAtom(pString, &foundAtom) && atom.IsEqual(foundAtom));
    }

    AtomPoolGroup* GetAtomPoolGroup() const { return m_pPoolGroup; }

    PCWSTR GetDescription() const { return nullptr; }

    bool GetIsCaseInsensitive() const { return true; }

    Atom::Index GetNumAtoms() const { return GetNumNames(); }

    Atom::PoolIndex GetPoolIndex() const { return m_poolIndex; }

    void SetAtomPoolGroup(AtomPoolGroup* pGroup) { m_pPoolGroup = pGroup; }

    void SetPoolIndex(Atom::PoolIndex index) { m_poolIndex = index; }

    bool TryGetAtom(__in PCWSTR pString, __out_opt Atom* pAtomOut) const
    {
        Atom::Index index = Atom::NullAtomIndex;
        if (TryGetIndex(pString, &index))
        {
            if (pAtomOut != nullptr)
            {
                pAtomOut->Set(index, m_poolIndex);
            }
            return true;
        }
        if (pAtomOut != nullptr)
        {
            *pAtomOut = Atom::NullAtom;
        }
        return false;
    }

    bool TryGetString(__in Atom atom, __inout_opt StringResult* pStringOut) const
    {
        if (atom.GetPoolIndex() == m_poolIndex)
        {
            return TryGetString(atom.GetIndex(), pStringOut);
        }
        return false;
    }

    bool TryGetString(__in Atom::Index index, __inout_opt StringResult* pStringOut) const
    {
        const HNamesNode* pNode;
        (void)GetName(index, &pNode);
        if (pNode != nullptr)
        {
            if (pStringOut != nullptr)
            {
                return SUCCEEDED(pNode->GetFullPath(pStringOut));
            }
            return true;
        }
        return false;
    }

protected:
    AtomPoolGroup* m_pPoolGroup { nullptr };
    Atom::Index m_poolIndex{ DEF_ATOM_INDEX_NONE };
    const HierarchicalNamesBuilder* m_pBuilder;

    HNamesNodeAtomPool(__in const HierarchicalNamesBuilder* pBuilder) : m_pBuilder(pBuilder) {}

    virtual int GetNumNames() const = 0;
    virtual HRESULT GetName(__in int index, _Out_ const HNamesNode** result) const = 0;
};

class ScopeInfoAtomPool : public HNamesNodeAtomPool
{
public:
    static HRESULT CreateInstance(
        __in const HierarchicalNamesBuilder* pBuilder,
        __in const DynamicArray<ScopeInfo*>* pScopes,
        _Outptr_ ScopeInfoAtomPool** result)
    {
        *result = nullptr;
        ScopeInfoAtomPool* pRtrn = new ScopeInfoAtomPool(pBuilder, pScopes);
        RETURN_IF_NULL_ALLOC(pRtrn);

        *result = pRtrn;
        return S_OK;
    }

    _Success_(return == true)
    bool TryGetIndex(__in PCWSTR pString, __out_opt Atom::Index* pIndexOut) const
    {
        int index = -1;
        if (m_pBuilder->Contains(pString, &index))
        {
            *pIndexOut = static_cast<Atom::Index>(index);
            return true;
        }
        return false;
    }

protected:
    const DynamicArray<ScopeInfo*>* m_pScopes;

    ScopeInfoAtomPool(__in const HierarchicalNamesBuilder* pBuilder, __in const DynamicArray<ScopeInfo*>* pScopes) :
        HNamesNodeAtomPool(pBuilder), m_pScopes(pScopes)
    {}

    virtual int GetNumNames() const { return m_pScopes->Count(); }
    virtual HRESULT GetName(__in int index, _Out_ const HNamesNode** result) const { return m_pScopes->Get(index, (ScopeInfo**)result); }
};

class ItemInfoAtomPool : public HNamesNodeAtomPool
{
public:
    static HRESULT CreateInstance(
        __in const HierarchicalNamesBuilder* pBuilder,
        __in const DynamicArray<ItemInfo*>* pItems,
        _Outptr_ ItemInfoAtomPool** result)
    {
        *result = nullptr;
        ItemInfoAtomPool* pRtrn = new ItemInfoAtomPool(pBuilder, pItems);
        RETURN_IF_NULL_ALLOC(pRtrn);

        *result = pRtrn;
        return S_OK;
    }

    _Success_(return == true)
    bool TryGetIndex(__in PCWSTR pString, __out_opt Atom::Index* pIndexOut) const
    {
        int index = -1;
        if (m_pBuilder->Contains(pString, nullptr, &index))
        {
            if (pIndexOut != nullptr)
            {
                *pIndexOut = static_cast<Atom::Index>(index);
            }
            return true;
        }
        return false;
    }

protected:
    const DynamicArray<ItemInfo*>* m_pItems;

    ItemInfoAtomPool(__in const HierarchicalNamesBuilder* pBuilder, __in const DynamicArray<ItemInfo*>* pItems) :
        HNamesNodeAtomPool(pBuilder), m_pItems(pItems)
    {}

    virtual int GetNumNames() const { return m_pItems->Count(); }
    virtual HRESULT GetName(__in int index, _Out_ const HNamesNode** result) const { return m_pItems->Get(index, (ItemInfo**)result); }
};

// Section builder for a hierarchical names section.

HierarchicalNamesBuilder::HierarchicalNamesBuilder(_In_ UINT32 flags) :
    m_sectionIndex(-1),
    m_numFinalizedNames(-1),
    m_pScopeNames(nullptr),
    m_pItemNames(nullptr),
    m_flags(flags),
    m_pAllScopes(nullptr),
    m_pAllItems(nullptr),
    m_pRootScope(nullptr)
{}

HRESULT HierarchicalNamesBuilder::Init(_In_opt_ AtomPoolGroup* pAtoms)
{
    RETURN_IF_FAILED(DynamicArray<ScopeInfo*>::CreateInstance(10, &m_pAllScopes));
    RETURN_IF_FAILED(DynamicArray<ItemInfo*>::CreateInstance(20, &m_pAllItems));

    // "NewRootScope" automatically adds the scope to globalNodes
    RETURN_IF_FAILED(ScopeInfo::NewRootScope(this, &m_pRootScope));

    RETURN_IF_FAILED(ScopeInfoAtomPool::CreateInstance(this, m_pAllScopes, (ScopeInfoAtomPool**)&m_pScopeNames));
    RETURN_IF_FAILED(ItemInfoAtomPool::CreateInstance(this, m_pAllItems, (ItemInfoAtomPool**)&m_pItemNames));

    if (pAtoms != nullptr)
    {
        RETURN_IF_FAILED(pAtoms->AddAtomPool(m_pScopeNames, false));
        RETURN_IF_FAILED(pAtoms->AddAtomPool(m_pItemNames, false));
    }

    return S_OK;
}

HRESULT HierarchicalNamesBuilder::CreateInstance(_In_ UINT32 flags, _Outptr_ HierarchicalNamesBuilder** result)
{
    return CreateInstance(flags, nullptr, result);
}

HRESULT HierarchicalNamesBuilder::CreateInstance(_In_ UINT32 flags, _In_ AtomPoolGroup* pAtoms, _Outptr_ HierarchicalNamesBuilder** result)
{
    *result = nullptr;

    AutoDeletePtr<HierarchicalNamesBuilder> pRtrn = new HierarchicalNamesBuilder(flags);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pAtoms));

    *result = pRtrn.Detach();
    return S_OK;
}

HierarchicalNamesBuilder::~HierarchicalNamesBuilder()
{
    // we're responsible for cleaning out AllItems & AllScopes
    if (m_pAllItems)
    {
        for (int i = 0; i < m_pAllItems->Count(); i++)
        {
            ItemInfo* item;
            if (SUCCEEDED(m_pAllItems->Get(i, &item)))
            {
                delete item;
            }
        }
    }

    if (m_pAllScopes)
    {
        for (int i = 0; i < m_pAllScopes->Count(); i++)
        {
            ScopeInfo* scope;
            if (SUCCEEDED(m_pAllScopes->Get(i, &scope)))
            {
                delete scope;
            }
        }
    }
    delete m_pAllItems;
    delete m_pAllScopes;

    delete m_pScopeNames;
    delete m_pItemNames;

    m_pRootScope = nullptr;
    m_pAllScopes = nullptr;
    m_pAllItems = nullptr;
    m_pScopeNames = nullptr;
    m_pItemNames = nullptr;
}

HRESULT HierarchicalNamesBuilder::AddScope(__in ScopeInfo* pScope, __out int* pIndexOut) { return m_pAllScopes->Add(pScope, pIndexOut); }

HRESULT HierarchicalNamesBuilder::AddItem(__in ItemInfo* pItem, __out int* pIndexOut) { return m_pAllItems->Add(pItem, pIndexOut); }

int HierarchicalNamesBuilder::GetNumRootScopes() const { return m_pRootScope->GetNumChildScopes(); }

int HierarchicalNamesBuilder::GetNumNames() const { return GetNumScopes() + GetNumItems(); }

int HierarchicalNamesBuilder::GetNumScopes() const { return m_pRootScope->GetTotalNumScopes(); }

int HierarchicalNamesBuilder::GetNumItems() const { return m_pRootScope->GetTotalNumItems(); }

bool HierarchicalNamesBuilder::Contains(__in PCWSTR pName, __out_opt int* pScopeIndexOut, __out_opt int* pItemIndexOut) const
{
    HNamesNode* pNode = nullptr;
    if (pScopeIndexOut != nullptr)
    {
        *pScopeIndexOut = -1;
    }

    if (pItemIndexOut != nullptr)
    {
        *pItemIndexOut = -1;
    }

    if (m_pRootScope->TryGetDescendent(pName, &pNode))
    {
        if (pNode->IsScope())
        {
            if (pScopeIndexOut != nullptr)
            {
                *pScopeIndexOut = pNode->GetIndex();
            }
        }
        else if (pItemIndexOut != nullptr)
        {
            *pItemIndexOut = pNode->GetIndex();
        }
        return true;
    }
    return false;
}

bool HierarchicalNamesBuilder::Contains(
    __in PCWSTR pName,
    __in int relativeToScope,
    __out_opt int* pScopeIndexOut,
    __out_opt int* pItemIndexOut) const
{
    HNamesNode* pNode = nullptr;
    if (pScopeIndexOut != nullptr)
    {
        *pScopeIndexOut = -1;
    }

    if (pItemIndexOut != nullptr)
    {
        *pItemIndexOut = -1;
    }

    ScopeInfo* pScope;
    (void)m_pAllScopes->Get(relativeToScope, &pScope);
    if (pScope == nullptr)
    {
        return false;
    }

    if (pScope->TryGetDescendent(pName, &pNode))
    {
        if (pNode->IsScope())
        {
            if (pScopeIndexOut != nullptr)
            {
                *pScopeIndexOut = pNode->GetIndex();
            }
        }
        else if (pItemIndexOut != nullptr)
        {
            *pItemIndexOut = pNode->GetIndex();
        }
        return true;
    }
    return false;
}

ScopeInfo* HierarchicalNamesBuilder::GetFirstRootScope() const { return m_pRootScope->GetFirstChild()->ToScope(); }

HRESULT HierarchicalNamesBuilder::GetRootScope(__in PCWSTR pPath, _Out_ ScopeInfo** result) const
{
    HierarchicalNameSegment path(GetConfig());
    HNamesNode* pChild = nullptr;

    path.SetByRef(pPath);

    if ((!m_pRootScope->TryGetChild(&path, &pChild)) || (!pChild->IsScope()))
    {
        return HRESULT_FROM_WIN32(ERROR_BAD_ENVIRONMENT);
    }
    *result = pChild->ToScope();
    return S_OK;
}

bool HierarchicalNamesBuilder::TryGetRootScope(_In_ PCWSTR pPath, _Outptr_result_maybenull_ ScopeInfo** ppScopeOut) const
{
    HierarchicalNameSegment path(GetConfig());
    HNamesNode* pChild = nullptr;

    *ppScopeOut = nullptr;

    path.SetByRef(pPath);

    if (m_pRootScope->TryGetChild(&path, &pChild) && pChild->IsScope())
    {
        *ppScopeOut = pChild->ToScope();
    }
    return ((*ppScopeOut) != nullptr);
}

HRESULT HierarchicalNamesBuilder::GetOrAddRootScope(__in PCWSTR pPath, _Out_ ScopeInfo** result)
{
    return m_pRootScope->GetOrAddScope(pPath, result);
}

HRESULT HierarchicalNamesBuilder::GetOrAddScope(__in PCWSTR pPath, _Out_ ScopeInfo** result)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPath));

    if (IsPathSeparator(pPath[0]))
    {
        pPath++;
    }
    return m_pRootScope->GetOrAddScope(pPath, result);
}

HRESULT HierarchicalNamesBuilder::GetOrAddItem(__in PCWSTR pPath, _Out_ ItemInfo** result)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pPath));

    if (IsPathSeparator(pPath[0]))
    {
        pPath++;
    }
    return m_pRootScope->GetOrAddItem(pPath, result);
}

bool HierarchicalNamesBuilder::TryGetScopeByIndex(_In_ int index, _Outptr_result_maybenull_ ScopeInfo** ppScopeOut) const
{
    if (ppScopeOut == nullptr)
    {
        return false;
    }

    (void)m_pAllScopes->Get(index, ppScopeOut);
    return ((*ppScopeOut) != nullptr);
}

bool HierarchicalNamesBuilder::TryGetItemByIndex(_In_ int index, _Outptr_result_maybenull_ ItemInfo** ppItemOut) const
{
    if (ppItemOut == nullptr)
    {
        return false;
    }

    (void)m_pAllItems->Get(index, ppItemOut);
    return ((*ppItemOut) != nullptr);
}

HRESULT HierarchicalNamesBuilder::ComputeTotalStringsSize(
    _In_ UINT32 flags,
    _In_ const ScopeInfo* pScope,
    _Out_ int* pCchAsciiStringsOut,
    _Out_ int* pCchUtf16StringsOut,
    _Out_ int* pCchLongestPathOut)
{
    int cchAsciiStrings = 0;
    int cchUtf16Strings = 0;
    int cchLongestPath = 0;

    RETURN_HR_IF_NULL(E_INVALIDARG, pScope);

    // Reserve space for the name of this scope if name
    // isn't empty (only the root scope is allowed to
    // have an empty name).
    PCWSTR pName = pScope->GetName();
    if (pName && pName[0])
    {
        if (((flags & BuildEncodingFlagsMask) == BuildUtf16Only) || (DefString_ChooseBestEncoding(pName) != DEFSTRING_ENCODING_ASCII))
        {
            cchUtf16Strings += static_cast<int>(wcslen(pName) + 1);
        }
        else
        {
            cchAsciiStrings += static_cast<int>(wcslen(pName) + 1);
        }
    }

    HNamesNode* pChild = pScope->GetFirstChild();
    int cchChildPath;
    UINT index = 1;

    // Reserve space for each of the items in this scope
    while (pChild != nullptr)
    {
        // Add child name size. Only do this if child is an item. Child scope size will be added
        // during the below ComputeTotalStringsSize() call.
        if (!pChild->IsScope())
        {
            if (((flags & BuildEncodingFlagsMask) == BuildUtf16Only) ||
                (DefString_ChooseBestEncoding(pChild->GetName()) != DEFSTRING_ENCODING_ASCII))
            {
                cchUtf16Strings += static_cast<int>(wcslen(pChild->GetName()) + 1);
            }
            else
            {
                cchAsciiStrings += static_cast<int>(wcslen(pChild->GetName()) + 1);
            }
        }

        cchChildPath = pChild->GetFullPathLength();
        if (cchChildPath > cchLongestPath)
        {
            cchLongestPath = cchChildPath;
        }

        if (pChild->IsScope())
        {
            int cchChildAsciiStrings = 0;
            int cchChildUtf16Strings = 0;
            int cchChildLongestPath = 0;

            RETURN_IF_FAILED(
                ComputeTotalStringsSize(flags, pChild->ToScope(), &cchChildAsciiStrings, &cchChildUtf16Strings, &cchChildLongestPath));

            cchAsciiStrings += cchChildAsciiStrings;
            cchUtf16Strings += cchChildUtf16Strings;
            if (cchChildLongestPath > cchLongestPath)
            {
                cchLongestPath = cchChildLongestPath;
            }
        }

        pChild = pScope->GetChild(index++);
    }

    *pCchAsciiStringsOut = cchAsciiStrings;
    *pCchUtf16StringsOut = cchUtf16Strings;
    *pCchLongestPathOut = cchLongestPath;
    return S_OK;
}

bool HierarchicalNamesBuilder::IsValidItemIndex(__in int indexIn) const { return (indexIn >= 0) && (indexIn < m_pAllItems->Count()); }

bool HierarchicalNamesBuilder::IsValidScopeIndex(__in int indexIn) const { return (indexIn >= 0) && (indexIn < m_pAllScopes->Count()); }

UINT32
HierarchicalNamesBuilder::GetMaxSizeInBytes() const
{
    if (!IsFinalized())
    {
        return 0;
    }

    UINT32 totalSize = ((m_cchFinalizedAsciiNames > 0) ? sizeof(DEFFILE_HNAMES_HEADER_EX) : sizeof(DEFFILE_HNAMES_HEADER));
    totalSize += GetNumNames() * ((m_flags & BuildLargeHNamesNode) ? sizeof(DEFFILE_HNAMES_NODE_LARGE) : sizeof(DEFFILE_HNAMES_NODE));
    totalSize += GetNumScopes() * ((m_flags & BuildLargeHNamesNode) ? sizeof(DEFFILE_HNAMES_SCOPE_LARGE) : sizeof(DEFFILE_HNAMES_SCOPE));
    totalSize += GetNumItems() * ((m_flags & BuildLargeHNamesNode) ? sizeof(UINT32) : sizeof(UINT16));
    totalSize += m_cchFinalizedUtf16Names * sizeof(WCHAR);
    totalSize += m_cchFinalizedAsciiNames * sizeof(char);
    totalSize = _DEFFILE_PAD_SECTION(totalSize);
    return totalSize;
}

bool HierarchicalNamesBuilder::AssignChildNameIndices(__in ScopeInfo* pScope, __in int* pNextNameIndex)
{
    int childIndex = *pNextNameIndex;
    HNamesNode* pChild = pScope->GetFirstChild();

    *pNextNameIndex += pScope->GetNumChildren();

    UINT index = 1;

    while (pChild != nullptr)
    {
        pChild->SetNameIndex(childIndex++);
        if (pChild->IsScope())
        {
            AssignChildNameIndices(pChild->ToScope(), pNextNameIndex);
        }
        pChild = pScope->GetChild(index++);
    }
    return true;
}

HRESULT HierarchicalNamesBuilder::Finalize()
{
    m_pRootScope->SetNameIndex(0);

    int nextIndex = 1;
    if (!AssignChildNameIndices(m_pRootScope, &nextIndex))
    {
        return E_ABORT;
    }

    if (nextIndex != (int)GetNumNames())
    {
        return E_ABORT;
    }

    if (GetNumNames() > DEFFILE_MAX_STANDARD_SIZE)
    {
        if (GetNumNames() > INT_MAX)
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_TOO_MANY_RESOURCES);
        }
        m_flags |= BuildLargeHNamesNode;
    }

    m_numFinalizedNames = nextIndex;

    m_cchFinalizedAsciiNames = 0;
    m_cchFinalizedUtf16Names = 0;
    m_cchLongestFinalizedName = 0;
    RETURN_IF_FAILED(
        ComputeTotalStringsSize(m_flags, m_pRootScope, &m_cchFinalizedAsciiNames, &m_cchFinalizedUtf16Names, &m_cchLongestFinalizedName));

    // Add one to total because we always start the buffer with a NULL.
    // Ensure that we add to each that has content, and to UTF-16 if neither has content since the format requires at least a pool with a NULL.
    if (m_cchFinalizedAsciiNames > 0)
    {
        m_cchFinalizedAsciiNames++;

        if (m_cchFinalizedUtf16Names > 0)
        {
            m_cchFinalizedUtf16Names++;
        }
    }
    else
    {
        m_cchFinalizedUtf16Names++;
    }

    return S_OK;
}

template<typename T>
HRESULT HierarchicalNamesBuilder::BuildNameNode(
    _In_ HNamesNode* pNode,
    _Inout_ T* pNameNode,
    _Inout_ SectionBuilderParser* pAsciiNamesData,
    _Inout_ SectionBuilderParser* pUtf16NamesData) const
{
    size_t cchName = 0;
    size_t nameOffset = 0;
    UINT32 parentNodeIndex = 0;
    BYTE flagsAndNameOffsetHigh = 0;
    UINT8 nameOffsetMiddle = 0;
    UINT32 payload = 0;
    bool isAscii = false;
    HRESULT hr = S_OK;

    if (pNode->GetName() != nullptr)
    {
        // Copy the string into the string buffer
        cchName = wcslen(pNode->GetName());

        if (((m_flags & BuildEncodingFlagsMask) == BuildUtf16Only) ||
            (DefString_ChooseBestEncoding(pNode->GetName()) != DEFSTRING_ENCODING_ASCII))
        {
            nameOffset = (pUtf16NamesData->UsedBufferSizeInBytes() / sizeof(WCHAR));

            // get a pointer to the spot that'll hold the string
            PWSTR pName = _SECTION_BUILDER_NEXT_ARRAY(*pUtf16NamesData, static_cast<UINT32>(cchName + 1), WCHAR, &hr);
            RETURN_IF_FAILED(hr);

            RETURN_IF_FAILED(DefString_CchCopy(pName, cchName + 1, pNode->GetName()));
        }
        else
        {
            nameOffset = pAsciiNamesData->UsedBufferSizeInBytes() / sizeof(char);

            PSTR pName = _SECTION_BUILDER_NEXT_ARRAY(*pAsciiNamesData, static_cast<UINT32>(cchName + 1), char, &hr);
            RETURN_IF_FAILED(hr);

            PCWSTR pNodeName = pNode->GetName();
            for (int i = 0; i < cchName; i++)
            {
                pName[i] = pNodeName[i];
            }
            pName[cchName] = '\0';
            isAscii = true;
        }

        parentNodeIndex = pNode->GetParentScope()->GetNameIndex();
    }
    else
    {
        // Root node is special
        cchName = 0;
        nameOffset = 0;
    }

    BYTE flags = 0;
    if (m_flags & BuildLargeHNamesNode)
    {
        // Up to 256MB. (seven f)
        if (nameOffset > 0xfffffff)
        {
            return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
        }
    }
    else
    {
        if (nameOffset & 0x100000)
        {
            nameOffset = nameOffset ^ 0x100000;
            flags |= DEFFILE_HNAMES_FLAGS_POOL_SIZE_2MB;
        }

        if (nameOffset & 0x200000)
        {
            nameOffset = nameOffset ^ 0x200000;
            flags |= DEFFILE_HNAMES_FLAGS_POOL_SIZE_4MB;
        }

        // If after setting the overflow bits we are still out of bounds we have no choice but to fail.
        if (nameOffset > 0xfffff)
        {
            return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
        }
    }

    // Initialize the name node
    pNameNode->cchFullPath = static_cast<UINT16>(pNode->GetFullPathLength());
    pNameNode->initialChar = GetConfig()->GetSegmentInitialChar(pNode->GetName());
    pNameNode->cchName = ((cchName < 256) ? static_cast<BYTE>(cchName) : 0);
    pNameNode->nameOffsetLow = (nameOffset & 0xffff);
    payload = pNode->GetIndex();
    if (m_flags & BuildLargeHNamesNode)
    {
        nameOffsetMiddle = ((nameOffset >> 16) & 0xff);
        flagsAndNameOffsetHigh = ((nameOffset >> 24) & 0xf);
    }
    else
    {
        flagsAndNameOffsetHigh = (nameOffset >> 16) & 0xf;
    }

    if (pNode->IsScope())
    {
        flagsAndNameOffsetHigh |= DEFFILE_HNAMES_FLAGS_NODE_IS_SCOPE;
    }

    if (isAscii)
    {
        flagsAndNameOffsetHigh |= DEFFILE_HNAMES_FLAGS_NAME_IS_ASCII;
    }

    flagsAndNameOffsetHigh |= flags;

    SetNameNodeValue(pNameNode, parentNodeIndex, flagsAndNameOffsetHigh, nameOffsetMiddle, payload);

    return S_OK;
}

/*!
 * Serializes the file list into the provided buffer.
 *
 * \param pBuffer
 * The buffer into which the file list is generated.
 *
 * \param cbBuffer
 * Size of the destination buffer, in bytes.
 *
 * \param pStatus
 * If the Build method returns false, pStatus contains additional
 * information about the cause of the error.
 *
 * \param cbWrittenOut
 * If pcbWrittenOut is non-NULL, the Build method uses it to return
 * the number of bytes actually written.
 *
 * \return bool
 * Returns true on success, false if an error occurs.
 */
HRESULT HierarchicalNamesBuilder::Build(__out_bcount(cbBuffer) VOID* pBuffer, UINT32 cbBuffer, __out_opt UINT32* pcbWrittenOut) const
{
    DEFFILE_HNAMES_NODE* pNodes = nullptr;
    DEFFILE_HNAMES_SCOPE* pScopes = nullptr;
    UINT16* pItems = nullptr;
    DEFFILE_HNAMES_NODE_LARGE* pNodesLarge = nullptr;
    DEFFILE_HNAMES_SCOPE_LARGE* pScopesLarge = nullptr;
    UINT32* pItemsLarge = nullptr;
    WCHAR* pUtf16Names;
    char* pAsciiNames;

    RETURN_HR_IF(E_INVALIDARG, (pBuffer == nullptr) || (!IsFinalized()));

    if (pcbWrittenOut != nullptr)
    {
        *pcbWrittenOut = 0;
    }

    SectionBuilderParser data;
    RETURN_IF_FAILED(data.Set(pBuffer, cbBuffer));

    bool useExtendedHNames = (m_cchFinalizedAsciiNames > 0); // ASCII schema requires using the extended HNAMES header.
    void* pHeaderUnknownType;
    HRESULT hr = S_OK;

    if (useExtendedHNames)
    {
        pHeaderUnknownType = _SECTION_BUILDER_NEXT(data, DEFFILE_HNAMES_HEADER_EX, &hr);
    }
    else
    {
        pHeaderUnknownType = _SECTION_BUILDER_NEXT(data, DEFFILE_HNAMES_HEADER, &hr);
    }

    RETURN_IF_FAILED(hr);

    if (m_flags & BuildLargeHNamesNode)
    {
        pNodesLarge = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumNames(), DEFFILE_HNAMES_NODE_LARGE, &hr);
        pScopesLarge = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumScopes(), DEFFILE_HNAMES_SCOPE_LARGE, &hr);
        pItemsLarge = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumItems(), UINT32, &hr);
    }
    else
    {
        pNodes = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumNames(), DEFFILE_HNAMES_NODE, &hr);
        pScopes = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumScopes(), DEFFILE_HNAMES_SCOPE, &hr);
        pItems = _SECTION_BUILDER_NEXT_ARRAY(data, GetNumItems(), UINT16, &hr);
    }

    pUtf16Names = _SECTION_BUILDER_NEXT_ARRAY(data, m_cchFinalizedUtf16Names, WCHAR, &hr);
    pAsciiNames = _SECTION_BUILDER_NEXT_ARRAY(data, m_cchFinalizedAsciiNames, char, &hr);
    _SECTION_BUILDER_PAD(&data, &hr);

    RETURN_IF_FAILED(hr);

    if (useExtendedHNames)
    {
        DEFFILE_HNAMES_HEADER_EX* pHeaderEx = static_cast<DEFFILE_HNAMES_HEADER_EX*>(pHeaderUnknownType);

        pHeaderEx->cchLongestPath = static_cast<UINT16>(m_cchLongestFinalizedName);
        pHeaderEx->flags = (m_flags & BuildLargeHNamesNode) ? DEFFILE_HNAMES_FLAGS_LARGE : 0;
        pHeaderEx->numNodes = GetNumNames();
        pHeaderEx->numScopes = GetNumScopes();
        pHeaderEx->numItems = GetNumItems();
        pHeaderEx->cchAsciiNamesPool = m_cchFinalizedAsciiNames;
        pHeaderEx->cchUtf16NamesPool = m_cchFinalizedUtf16Names;
        pHeaderEx->cbTotal = static_cast<UINT32>(data.UsedBufferSizeInBytes());
    }
    else
    {
        DEFFILE_HNAMES_HEADER* pHeader = static_cast<DEFFILE_HNAMES_HEADER*>(pHeaderUnknownType);

        pHeader->cchLongestPath = static_cast<UINT16>(m_cchLongestFinalizedName);
        pHeader->flags = (m_flags & BuildLargeHNamesNode) ? DEFFILE_HNAMES_FLAGS_LARGE : 0;
        pHeader->numNodes = GetNumNames();
        pHeader->numScopes = GetNumScopes();
        pHeader->numItems = GetNumItems();
        pHeader->cchNames = m_cchFinalizedUtf16Names;
        pHeader->cbTotal = static_cast<UINT32>(data.UsedBufferSizeInBytes());
    }

    // initialize and null-terminate one or both buffers
    SectionBuilderParser utf16NamesData;
    if (m_cchFinalizedUtf16Names > 0)
    {
        RETURN_IF_FAILED(utf16NamesData.Set(pUtf16Names, m_cchFinalizedUtf16Names * sizeof(WCHAR)));

        WCHAR* pName = _SECTION_BUILDER_NEXT(utf16NamesData, WCHAR, &hr);
        RETURN_IF_FAILED(hr);
        *pName = L'\0';
    }

    SectionBuilderParser asciiNamesData;
    if (m_cchFinalizedAsciiNames > 0)
    {
        RETURN_IF_FAILED(asciiNamesData.Set(pAsciiNames, m_cchFinalizedAsciiNames * sizeof(char)));

        char* pName = _SECTION_BUILDER_NEXT(asciiNamesData, char, &hr);
        RETURN_IF_FAILED(hr);
        *pName = '\0';
    }

    for (int i = 0; i < m_pAllScopes->Count(); i++)
    {
        ScopeInfo* pScope;
        RETURN_IF_FAILED(m_pAllScopes->Get(i, &pScope));
        HNamesNode* pChild = nullptr;
        DEFFILE_HNAMES_SCOPE* pFileScope = nullptr;
        DEFFILE_HNAMES_NODE* pNameNode = nullptr;
        DEFFILE_HNAMES_SCOPE_LARGE* pFileScopeLarge = nullptr;
        DEFFILE_HNAMES_NODE_LARGE* pNameNodeLarge = nullptr;

        if (m_flags & BuildLargeHNamesNode)
        {
            pFileScopeLarge = &pScopesLarge[pScope->GetIndex()];
            pNameNodeLarge = &pNodesLarge[pScope->GetNameIndex()];
        }
        else
        {
            pFileScope = &pScopes[pScope->GetIndex()];
            pNameNode = &pNodes[pScope->GetNameIndex()];
        }

        if (pScope->GetNumChildren() > 0)
        {
            pChild = pScope->GetFirstChild();

            DEF_ASSERT(pChild != nullptr);
        }

        if (m_flags & BuildLargeHNamesNode)
        {
            RETURN_IF_FAILED(BuildNameNode<DEFFILE_HNAMES_NODE_LARGE>(pScope, pNameNodeLarge, &asciiNamesData, &utf16NamesData));

            // build the scope node
            pFileScopeLarge->nameNodeIndex = pScope->GetNameIndex();
            pFileScopeLarge->numChildNames = pScope->GetNumChildren();
            pFileScopeLarge->firstChildNameNode = ((pChild != nullptr) ? pChild->GetNameIndex() : 0);
            pFileScopeLarge->flags = 0;
        }
        else
        {
            RETURN_IF_FAILED(BuildNameNode<DEFFILE_HNAMES_NODE>(pScope, pNameNode, &asciiNamesData, &utf16NamesData));

            // build the scope node
            pFileScope->nameNodeIndex = static_cast<UINT16>(pScope->GetNameIndex());
            pFileScope->numChildNames = static_cast<UINT16>(pScope->GetNumChildren());
            pFileScope->firstChildNameNode = static_cast<UINT16>(((pChild != nullptr) ? pChild->GetNameIndex() : 0));
            pFileScope->flags = 0;
        }
    }

    for (int i = 0; i < m_pAllItems->Count(); i++)
    {
        ItemInfo* pItem;
        RETURN_IF_FAILED(m_pAllItems->Get(i, &pItem));
        DEFFILE_HNAMES_NODE* pNameNode = nullptr;
        DEFFILE_HNAMES_NODE_LARGE* pNameNodeLarge = nullptr;

        if (m_flags & BuildLargeHNamesNode)
        {
            pNameNodeLarge = &pNodesLarge[pItem->GetNameIndex()];
            RETURN_IF_FAILED(BuildNameNode<DEFFILE_HNAMES_NODE_LARGE>(pItem, pNameNodeLarge, &asciiNamesData, &utf16NamesData));

            // build the item index
            pItemsLarge[pItem->GetIndex()] = pItem->GetNameIndex();
        }
        else
        {
            pNameNode = &pNodes[pItem->GetNameIndex()];
            RETURN_IF_FAILED(BuildNameNode<DEFFILE_HNAMES_NODE>(pItem, pNameNode, &asciiNamesData, &utf16NamesData));

            // build the item index
            pItems[pItem->GetIndex()] = static_cast<UINT16>(pItem->GetNameIndex());
        }
    }

    if (pcbWrittenOut != nullptr)
    {
        *pcbWrittenOut = static_cast<UINT32>(data.UsedBufferSizeInBytes());
    }
    return S_OK;
}

} // namespace Microsoft::Resources::Build