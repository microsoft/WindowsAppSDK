// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "mrm/readers/SectionParser.h"
#include "mrm/readers/HNames.h"
#include "mrm/build/FileBuilder.h"
#include "mrm/Collections.h"
#include "mrm/Checksums.h"

namespace Microsoft::Resources::Build
{

class ScopeInfo;
class ItemInfo;
class HierarchicalNamesBuilder;

class IHNamesGlobalNodes
{
public:
    virtual HRESULT AddScope(__in ScopeInfo* pScope, __out int* pIndexOut) = 0;

    virtual HRESULT AddItem(__in ItemInfo* pItem, __out int* pIndexOut) = 0;

    virtual const HierarchicalNamesConfig* GetConfig() const = 0;
};

class HierarchicalNameSegment
{
public:
    HierarchicalNameSegment(_In_ const HierarchicalNamesConfig* pConfig) :
        m_pConfig(pConfig), m_pMySegmentBuf(nullptr), m_pSegmentRef(nullptr), m_segmentHash(0), m_segmentInitialChar(L'\0')
    {}

    ~HierarchicalNameSegment()
    {
        if (m_pMySegmentBuf != nullptr)
        {
            Def_Free(m_pMySegmentBuf);
            m_pMySegmentBuf = nullptr;
        }
    }

    const HierarchicalNamesConfig* GetConfig() const { return m_pConfig; }

    DEF_CHECKSUM GetHash() const
    {
        if (m_segmentHash == 0)
        {
            (void)DefChecksum::ComputeStringChecksum(0, true, m_pSegmentRef, &m_segmentHash);
        }
        return m_segmentHash;
    }

    WCHAR GetInitialChar() const { return m_segmentInitialChar; }

    PCWSTR GetName() const { return m_pSegmentRef; }

    bool HaveName() const { return (m_pSegmentRef != nullptr) && (m_pSegmentRef[0] != L'\0'); }

    bool SetByRef(_In_opt_ PCWSTR pRef)
    {
        if (m_pMySegmentBuf != nullptr)
        {
            Def_Free(m_pMySegmentBuf);
        }

        m_pMySegmentBuf = nullptr;
        m_pSegmentRef = pRef;
        m_segmentInitialChar = m_pConfig->GetSegmentInitialChar(pRef);
        m_segmentHash = 0;
        return true;
    }

    HRESULT SetCopy(_In_opt_ PCWSTR pRef)
    {
        if (m_pMySegmentBuf != nullptr)
        {
            Def_Free(m_pMySegmentBuf);
        }

        if (pRef != nullptr)
        {
            RETURN_IF_FAILED(DefString_Dup(pRef, &m_pMySegmentBuf));
        }
        else
        {
            m_pMySegmentBuf = nullptr;
        }

        m_pSegmentRef = m_pMySegmentBuf;
        m_segmentInitialChar = m_pConfig->GetSegmentInitialChar(pRef);
        m_segmentHash = 0;
        return S_OK;
    }

    bool SetByRef(_In_ const HierarchicalNameSegment* pOther)
    {
        if (m_pMySegmentBuf != nullptr)
        {
            Def_Free(m_pMySegmentBuf);
        }

        m_pMySegmentBuf = nullptr;
        m_pSegmentRef = pOther->m_pSegmentRef;
        m_segmentInitialChar = pOther->m_segmentInitialChar;
        m_segmentHash = pOther->m_segmentHash;
        return true;
    }

    HRESULT SetCopy(_In_ const HierarchicalNameSegment* pOther)
    {
        if (m_pMySegmentBuf != nullptr)
        {
            Def_Free(m_pMySegmentBuf);
        }

        if (pOther != nullptr)
        {
            RETURN_IF_FAILED(DefString_Dup(pOther->m_pSegmentRef, &m_pMySegmentBuf));
        }
        else
        {
            m_pMySegmentBuf = nullptr;
        }

        m_pSegmentRef = m_pMySegmentBuf;
        m_segmentInitialChar = pOther->m_segmentInitialChar;
        m_segmentHash = pOther->m_segmentHash;
        return S_OK;
    }

protected:
    const HierarchicalNamesConfig* m_pConfig;

    PWSTR m_pMySegmentBuf;
    PCWSTR m_pSegmentRef;
    mutable DEF_CHECKSUM m_segmentHash;
    mutable WCHAR m_segmentInitialChar;
};

class HierarchicalName
{
public:
    HierarchicalName(_In_ const HierarchicalNamesConfig* pConfig) :
        m_current(pConfig), m_pPathRef(nullptr), m_pPathBuf(nullptr), m_pNextSegment(nullptr)
    {}

    ~HierarchicalName()
    {
        if (m_pPathBuf != nullptr)
        {
            Def_Free(m_pPathBuf);
            m_pPathBuf = nullptr;
        }
    }

    const HierarchicalNamesConfig* GetConfig() const { return m_current.GetConfig(); }
    const PCWSTR GetFullPath() const { return m_pPathRef; }

    const HierarchicalNameSegment* GetCurrentSegment() const { return &m_current; }

    PCWSTR GetCurrentSegmentText() const { return m_current.GetName(); }
    DEF_CHECKSUM GetCurrentSegmentHash() const { return m_current.GetHash(); }
    WCHAR GetCurrentSegmentInitialChar() const { return m_current.GetInitialChar(); }

    HRESULT SetPathByRef(_In_ PCWSTR pPath)
    {
        if (m_pPathBuf != nullptr)
        {
            Def_Free(m_pPathBuf);
            m_pPathBuf = nullptr;
        }

        m_pPathRef = pPath;

        if (pPath != nullptr)
        {
            int segmentLength = -1;
            bool more = true;
            if (!GetConfig()->TryGetNextSegmentLength(pPath, &segmentLength, &more))
            {
                return E_FAIL;
            }

            if (!more)
            {
                // no more segments.  Just use the referenced path directly.
                m_pPathBuf = nullptr;
                m_pNextSegment = nullptr;
                m_current.SetByRef(m_pPathRef);
            }
            else
            {
                // Copy path to local buffer so we can null-terminate
                // the segments
                RETURN_IF_FAILED(DefString_Dup(m_pPathRef, &m_pPathBuf));
                // Null-terminate the first segment and use it as ours
                m_pPathBuf[segmentLength] = L'\0';
                m_pNextSegment = &m_pPathBuf[segmentLength + 1];
                m_current.SetByRef(m_pPathBuf);
            }
        }
        else
        {
            m_current.SetByRef((PCWSTR) nullptr);
        }

        return S_OK;
    }

    bool HaveCurrentSegment() const { return m_current.HaveName(); }
    bool HaveNextSegment() const { return (m_pNextSegment != nullptr); }

    bool AdvanceToNextSegment()
    {
        if (m_pNextSegment == nullptr)
        {
            // we're done
            m_current.SetByRef((PCWSTR) nullptr);
            return false;
        }

        m_current.SetByRef(m_pNextSegment);

        int segmentLength = -1;
        bool more = true;
        if (!GetConfig()->TryGetNextSegmentLength(m_pNextSegment, &segmentLength, &more))
        {
            return false;
        }

        if (more)
        {
            // There's more.  Null-terminate and set up the next segment.
            m_pNextSegment[segmentLength] = L'\0';
            m_pNextSegment = &m_pNextSegment[segmentLength + 1];
        }
        else
        {
            // last segment.  Just use it.
            m_pNextSegment = nullptr;
        }

        return true;
    }

protected:
    PCWSTR m_pPathRef;
    PWSTR m_pPathBuf;

    PWSTR m_pNextSegment;

    HierarchicalNameSegment m_current;
};

class HNamesNode : public DefObject
{
public:
    virtual ~HNamesNode() {}

    PCWSTR GetName() const { return m_segment.GetName(); }
    DEF_CHECKSUM GetHash() const { return m_segment.GetHash(); }
    WCHAR GetInitialChar() const { return m_segment.GetInitialChar(); }
    ScopeInfo* GetParentScope() const { return m_pParentScope; }

    HRESULT GetFullPath(__inout StringResult* pPathOut) const;

    int GetFullPathLength() const;

    int GetIndex() const { return m_index; }

    int GetNameIndex() const { return m_nameIndex; }
    void SetNameIndex(int index) { m_nameIndex = index; }

    virtual bool IsScope() const = 0;
    virtual ScopeInfo* ToScope() { return NULL; }
    virtual ItemInfo* ToItem() { return NULL; }
    virtual HRESULT AddToGlobal(_In_ ScopeInfo* parent) = 0;

    const HierarchicalNamesConfig* GetConfig() const { return m_segment.GetConfig(); }
    int CompareTo(__in const HNamesNode* pOther) const;
    int CompareTo(__in PCWSTR pOther) const;

    bool Equals(_In_ const HNamesNode* pOther) const;

protected:
    HNamesNode(_In_ ScopeInfo* pParent);

    HNamesNode(__in const HierarchicalNamesConfig* pConfig);

    HRESULT Init(_In_ const HierarchicalNameSegment* name);

    HRESULT ConcatPath(__inout StringResult* pPathOut) const;

    HierarchicalNameSegment m_segment;

    ScopeInfo* m_pParentScope;

    int m_index;
    int m_nameIndex;
};

//! Build-time information about a single item (leaf) in an
// HierarchicalNamesBuilder.
class ItemInfo : public HNamesNode
{
public:
    virtual ~ItemInfo();

    /*!
         * Constructs a new ItemInfo with a specified name, index
         * and parent scope.
         *
         * This constructor just creates the object.
         * It does not validate names, check for collisions or
         * add add it to the parent scope.   To ensure proper
         * semantics and consistency, use ScopeInfo::GetOrAddItem
         * to create new items.
         * 
         * \param pName
         * The name of the item to be added.
         *
         * \param pParent
         * Parent scope that will contain the new item.
         *
         * \param result
         * Returns a pointer to the new ItemInfo, or NULL if an error
         * occurs.
         * 
         * \return HRESULT
         */

    static HRESULT CreateInstance(_In_ const HierarchicalNameSegment* pName, _In_ ScopeInfo* pParent, _Outptr_ ItemInfo** result);

    bool IsScope() const { return false; }
    ItemInfo* ToItem() { return this; }

    HRESULT AddToGlobal(_In_ ScopeInfo* parent);

protected:
    ItemInfo(_In_ ScopeInfo* pParent);

    HRESULT Init(_In_ const HierarchicalNameSegment* pName, _In_ ScopeInfo* pParent);
};

//! Build-time information about a single scope in an HierarchicalNamesBuilder.
class ScopeInfo : public HNamesNode
{
public:
    virtual ~ScopeInfo();

    /*!
         * Sets the index of this scope in the generated hierarchical
         * names section.
         *
         * Note that this constructor just creates the object.
         * It does not validate names, check for collisions or
         * add add it to the parent scope.   To ensure proper
         * semantics and consistency, use ScopeInfo::GetOrAddScope
         * to create new child scopes.
         * 
         * \param pName
         * The name of the scope to be added.
         * 
         * \param pParent
         * Parent scope that will contain the new scope
         *
         * \param scopeIndex
         * Global index of the new scope
         *
         * \param result
         * Returns a pointer to the new ScopeInfo, or NULL if an error
         * occurs.
         * 
         * \return HRESULT
         */
    static HRESULT CreateInstance(_In_ const HierarchicalNameSegment* pName, _In_ ScopeInfo* pParent, _Outptr_ ScopeInfo** result);

    static HRESULT NewRootScope(__in IHNamesGlobalNodes* pGlobalNodes, _Outptr_ ScopeInfo** result);

    bool IsScope() const { return true; }
    ScopeInfo* ToScope() { return this; }
    ItemInfo* ToItem() { return NULL; }

    HRESULT AddToGlobal(_In_ ScopeInfo* parent);

    /*! 
         * Gets the number of immediate children
         * Does not include further descendents of child scopes
         * of the referenced scope.
         * 
         * \return int
         * Returns the number of children
         */
    int GetNumChildren() const { return m_numChildScopes + m_numChildItems; }

    int GetNumChildScopes() const { return m_numChildScopes; }
    int GetNumChildItems() const { return m_numChildItems; }

    /*! 
         * Gets the total number of referenced scopes at or below the supplied scope.
         * Includes the scope itself, plus all descendents.
         * 
         * \return int
         * Returns the total number of referenced scopes at or below the
         * supplied scope. 
         */
    int GetTotalNumScopes() const { return m_totalNumScopes; }

    /*!
         * Gets the total number of referenced items at or below the supplied scope.
         *
         * Includes referenced items in the scope itself, plus any referenced items
         * contained in subscopes of any depth.
         * 
         * \return int
         * Returns the total number of referenced items at or below the
         * supplied scope.
         */
    int GetTotalNumItems() const { return m_totalNumItems; }

    //! Gets the global node collection to which this scope belongs
    IHNamesGlobalNodes* GetGlobalNodes() { return m_pGlobalNodes; }

    HNamesNode* GetChild(UINT i) const;
    HNamesNode* GetFirstChild() const;

    /*!
         * Gets an immediate child by name.
         *
         * Reports an error if no matching child is found.
         * \param pName
         * The name of the immediate child to be returned.
         * 
         * \return HNamesNode*
         * Returns a pointer to an HNamesNode describing
         * the requested child, or NULL if an error occurs.
         */
    bool TryGetChild(_In_ int index, _Outptr_opt_result_maybenull_ HNamesNode** ppChildOut) const;

    bool TryGetChild(_In_ const HierarchicalNameSegment* pName, _Outptr_opt_result_maybenull_ HNamesNode** ppChildOut) const;

    /*!
         * Gets an descendent node by name, parsing path 
         * separators as appropriate.
         *
         * Reports an error if no matching descendent is found.
         * \param pName
         * The name of the descendent to be returned.
         * 
         * \return HNamesNode*
         * Returns a pointer to an HNamesNode describing
         * the requested descendent, or NULL if an error occurs.
         */
    bool TryGetDescendent(_In_ PCWSTR pName, _Outptr_opt_result_maybenull_ HNamesNode** pChildOut) const;

    /*!
         * Gets or adds a named scope to a ScopeInfo.   Traverses
         * or creates intermediate scopes as necessary.
         *
         * If a child scope with a matching name already exists, returns
         * the existing scope.  If no matching child scope exists,
         * adds a new scope and returns a pointer to it.
         * 
         * \param pName
         * Name of the new child scope.
         *
         * \param result
         * Returns a pointer to a ScopeInfo describing the
         * requested child scope.
         * 
         * \return HRESULT
         */
    HRESULT GetOrAddScope(_In_ PCWSTR pName, _Out_ ScopeInfo** result);

    /*!
         * Gets or adds an item with the specified name.  Traverses
         * or creates intermediat scope nodes if necessary.
         *
         * If a item with a matching name already exists, returns a
         * pointer to the existing ItemInfo.  If no matching item exists,
         * adds a new ItemInfo and returns a pointer to it.
         * 
         * \param pName
         * Name of the new item.
         *
         * \param result
         * Returns a pointer to a ItemInfo describing the
         * requested item.
         * 
         * \return HRESULT
         */
    HRESULT GetOrAddItem(_In_ PCWSTR pName, _Out_ ItemInfo** result);

protected:
    DynamicArray<HNamesNode*>* m_pChildren;

    int m_numChildScopes;
    int m_numChildItems;

    int m_totalNumItems;
    int m_totalNumScopes;

    IHNamesGlobalNodes* m_pGlobalNodes;

    ScopeInfo(_In_ ScopeInfo* pParent);

    ScopeInfo(__in IHNamesGlobalNodes* pGlobalNodes);

    HRESULT Init();

    HRESULT Init(_In_ const HierarchicalNameSegment* name);

    bool NoteSubscopeChanges(__in int numScopesAdded, __in int numItemsAdded);

    /*!
         * _INTERNAL ONLY_
         * Gets or adds a specific named scope to a ScopeInfo. 
         * Does _not_ look for separators or validate the 
         * requested path.
         *
         * If a child scope with a matching name already exists, returns
         * the existing scope.  If no matching child scope exists,
         * adds a new scope and returns a pointer to it.
         * 
         * \param pName
         * Name of the new child scope.
         *
         * \param result
         * Returns a pointer to a ScopeInfo describing the
         * requested child scope.
         * 
         * \return HRESULT
         */
    HRESULT GetOrAddChildScope(_In_ const HierarchicalNameSegment* pName, _Out_ ScopeInfo** result);

    /*!
         * _INTERNAL ONLY_
         * Gets or adds an item with the specified name to a ScopeInfo.
         * If a item with a matching name already exists, returns a
         * pointer to the existing ItemInfo.  If no matching item exists,
         * adds a new ItemInfo and returns a pointer to it.
         * 
         * Does _not_ look for separators or validate the requested path.
         * 
         * \param pName
         * Name of the new item.
         *
         * \param result
         * Returns a pointer to a ItemInfo describing the
         * requested item.
         * 
         * \return HRESULT
         */
    HRESULT GetOrAddChildItem(_In_ const HierarchicalNameSegment* pName, _Out_ ItemInfo** result);

    HRESULT FindSearchRange(_In_ PCWSTR nodeName, _Out_ int* startSearch, _Out_ int* endSearch, _Out_ int* insert) const;

    UINT FindInsertionPoint(_In_ PCWSTR pName, _In_ UINT first, _In_ UINT last, _Out_ int* pDiffOut) const;

    HRESULT GetOrAddChildNode(_In_ HNamesNode* newNode, _Out_ HNamesNode** foundNode);
};

/*!
     * Class used to construct a hierarchical names section.
     * The builder holds one or more "root" scopes, and any
     * number of descendent scopes or items.  Subscopes
     * and items are specified by name, relative to one of the root
     * scopes.
     */
class HierarchicalNamesBuilder : public ISectionBuilder, public HierarchicalNamesConfig, protected IHNamesGlobalNodes
{
public:
    static const UINT32 BuildUtf16Only = 0x0;
    static const UINT32 BuildAsciiOrUtf16 = 0x1;
    static const UINT32 BuildEncodingFlagsMask = 0x1;
    static const UINT32 BuildLargeHNamesNode = 0x2;

    static HRESULT CreateInstance(_In_ UINT32 flags, _Outptr_ HierarchicalNamesBuilder** result);
    static HRESULT CreateInstance(_In_ UINT32 flags, _In_ AtomPoolGroup* pAtoms, _Outptr_ HierarchicalNamesBuilder** result);

    virtual ~HierarchicalNamesBuilder();

    //! Gets the number of root scopes in this builder.
    int GetNumRootScopes() const;

    int GetNumNames() const;

    //! Gets the total number of scopes referenced by this builder.
    int GetNumScopes() const;

    IAtomPool* GetScopeNames() const { return m_pScopeNames; }

    //! Gets the total number of items referenced by this builder.
    int GetNumItems() const;

    IAtomPool* GetItemNames() const { return m_pItemNames; }

    ScopeInfo* GetFirstRootScope() const;

    bool Contains(__in PCWSTR pName, __out_opt int* pScopeIndexOut = NULL, __out_opt int* pItemIndexOut = NULL) const;
    bool Contains(__in PCWSTR pName, __in int relativeToScope, __out_opt int* pScopeIndexOut = NULL, __out_opt int* pItemIndexOut = NULL)
        const;

    /*!
         * Gets a root scope specified by name.
         * Reports an error if no matching scope is found.
         * 
         * \param pPath
         * Name of the root scope to be returned.
         *
         * \param result
         * A ScopeInfo describing the requested root 
         * folder, or NULL if an error occurs.
         * 
         * \return HRESULT
         */
    HRESULT GetRootScope(_In_ PCWSTR pPath, _Out_ ScopeInfo** result) const;

    /*!
         * Tries to get a root scope specified by name.
         * Returns false but does not report an error if no
         * matching scope is found.
         * 
         * \param pPath
         * Name of the root scope to be returned.
         * 
         * \param ppScopeOut
         * Returns a pointer to a ScopeInfo describing the
         * requested root scope, or NULL if no match is found
         * or if an error occurs.
         * 
         * \return bool
         * Returns true if a matching scope is found, false
         * if no match is found or if an error occurs.
         */
    bool TryGetRootScope(_In_ PCWSTR pPath, _Outptr_result_maybenull_ ScopeInfo** ppScopeOut) const;

    /*!
         * Gets or adds a root scope with the specified name to
         * a HierarchicalNamesBuilder.
         * If a root scope with a matching name already exists,
         * returns a pointer to the existing ScopeInfo.
         * If no matching scope exists, adds a new ScopeInfo
         * and returns a pointer to it.
         * 
         * \param pPath
         * Name of the new root scope.
         *
         * \param result
         * Returns a pointer to an ItemInfo describing the
         * requested file.
         * 
         * \return HRESULT
         */
    HRESULT GetOrAddRootScope(_In_ PCWSTR pPath, _Out_ ScopeInfo** result);

    HRESULT GetOrAddScope(_In_ PCWSTR pPath, _Out_ ScopeInfo** result);

    HRESULT GetOrAddItem(_In_ PCWSTR pPath, _Out_ ItemInfo** result);

    /*! 
         * Gets a scope by index.
         * 
         * \param index
         * The index of the scope to be returned.
         * 
         * \param ppScopeOut
         * Returns the requested \ref ScopeInfo, or NULL if an
         * error occurs.
         *
         * \return bool
         * Returns true if the requested scope is found.  Returns
         * false if an error occurs.
         */
    bool TryGetScopeByIndex(_In_ int index, _Outptr_result_maybenull_ ScopeInfo** ppScopeOut) const;

    /*! 
         * Gets an item by index.
         * 
         * \param index
         * The index of the item to be returned.
         * 
         * \param ppItemOut
         * Returns the requested \ref ItemInfo, or NULL if an
         * error occurs.
         *
         * \return bool
         * Returns true if the requested item is found.  Returns
         * false if an error occurs.
         */
    bool TryGetItemByIndex(_In_ int index, _Outptr_result_maybenull_ ItemInfo** ppItemOut) const;

    /*! 
         * Determines if a supplied item index is valid.
         *
         * \param indexIn
         * The index to be tested.
         *
         * \return bool
         * Returns true if the supplied index refers to a
         * valid item in this names builder, false otherwise.
         */
    bool IsValidItemIndex(__in int indexIn) const;

    /*! 
         * Determines if a supplied scope index is valid.
         *
         * \param indexIn
         * The index to be tested.
         *
         * \return bool
         * Returns true if the supplied index refers to a
         * valid scope in this builder, false otherwise.
         */
    bool IsValidScopeIndex(__in int indexIn) const;

    const HierarchicalNamesConfig* GetConfig() const { return this; }

    bool IsFinalized() const { return (m_numFinalizedNames == (int)GetNumNames()); }
    bool IsValid() const { return true; }
    HRESULT Finalize();
    UINT32 GetMaxSizeInBytes() const;

    virtual HRESULT Build(__out_bcount(cbBuffer) VOID* pBuffer, UINT32 cbBuffer, __out_opt UINT32* pcbWrittenOut) const;

    DEFFILE_SECTION_TYPEID GetSectionType() const
    {
        return ((IsFinalized() && (m_cchFinalizedAsciiNames > 0)) ? gHierarchicalNamesExSectionType : gHierarchicalNamesSectionType);
    }

    UINT16 GetFlags() const { return 0; }
    UINT16 GetSectionFlags() const { return 0; }
    UINT32 GetSectionQualifier() const { return 0; }
    void SetSectionIndex(BaseFile::SectionIndex sectionIndex) { m_sectionIndex = sectionIndex; }
    BaseFile::SectionIndex GetSectionIndex() const { return m_sectionIndex; }

private:
    UINT32 m_flags;

    BaseFile::SectionIndex m_sectionIndex;

    ScopeInfo* m_pRootScope;
    DynamicArray<ScopeInfo*>* m_pAllScopes;
    DynamicArray<ItemInfo*>* m_pAllItems;

    IAtomPool* m_pScopeNames;
    IAtomPool* m_pItemNames;

    int m_numFinalizedNames;
    int m_cchFinalizedAsciiNames;
    int m_cchFinalizedUtf16Names;
    int m_cchLongestFinalizedName;

protected:
    HierarchicalNamesBuilder(_In_ UINT32 flags);

    HRESULT Init(_In_opt_ AtomPoolGroup* pAtoms);

    /*!
         * Computes maximum string pool size, in characters.
         * A string pool containing all of the strings from a specified scope
         * and all of its contents might need fewer characters than reported
         * by this function, but it will not require more.
         * 
         * \param pScopeInfo
         * The scope to be checked.
         *
         * \param pCchAsciiStringsOut
         * The unpadded size in char required to hold any ascii strings in the this
         * scope and below.
         * 
         * \param pCchUtf16StringsOut
         * The unpadded size in WCHAR required to hold any UTF-16 strings in this 
         * scope and below.
         *
         * \param pCchLongestPathOut
         * The length of the longest path below this scope, in characters.
         * 
         * \return HRESULT
         * S_OK on success, failure if an error occurs.
         */
    static HRESULT ComputeTotalStringsSize(
        _In_ UINT32 flags,
        _In_ const ScopeInfo* pScope,
        _Out_ int* pCchAsciiStringsOut,
        _Out_ int* pCchUtf16StringsOut,
        _Out_ int* pCchLongestPathOut);

    bool AssignChildNameIndices(__in ScopeInfo* pScopeInfo, __in int* pNextNameIndex);

    HRESULT AddScope(__in ScopeInfo* pScope, __out int* pIndexOut);

    HRESULT AddItem(__in ItemInfo* pItem, __out int* pIndexOut);

    template<typename T>
    HRESULT BuildNameNode(
        _In_ HNamesNode* pNode,
        _Inout_ T* pNameNode,
        _Inout_ SectionBuilderParser* pAsciiNamesData,
        _Inout_ SectionBuilderParser* pUtf16NamesData) const;

    template<typename T>
    void SetNameNodeValue(
        _Inout_ T* node,
        UINT32 parentNodeIndex,
        BYTE flagsAndNameOffsetHigh,
        UINT8 /* nameOffsetMiddle */,
        UINT32 payload) const
    {
        node->parentNodeIndex = static_cast<UINT16>(parentNodeIndex);
        node->flagsAndNameOffsetHigh = flagsAndNameOffsetHigh;
        node->payload = static_cast<UINT16>(payload);
    }

    template<>
    void SetNameNodeValue(
        _Inout_ DEFFILE_HNAMES_NODE_LARGE* node,
        UINT32 parentNodeIndex,
        BYTE flagsAndNameOffsetHigh,
        UINT8 nameOffsetMiddle,
        UINT32 payload) const
    {
        node->parentNodeIndex = parentNodeIndex;
        node->flagsAndNameOffsetHigh = flagsAndNameOffsetHigh;
        node->nameOffsetMiddle = nameOffsetMiddle;
        node->payload = payload;
    }
};

} // namespace Microsoft::Resources::Build
