// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "mrm/common/file/FileBase.h"
#include "mrm/common/file/FileListBase.h"
#include "mrm/common/file/HNamesSection.h"

namespace Microsoft::Resources
{

class HierarchicalNamesConfig
{
public:
    WCHAR GetDefaultPathSeparator() const { return L'/'; }
    bool IsPathSeparator(__in WCHAR ch) const { return (ch == L'/') || (ch == L'\\'); }
    bool IsValidSegmentChar(__in WCHAR ch) const { return (!IsPathSeparator(ch)); }
    WCHAR GetSegmentInitialChar(__in PCWSTR str) const { return (((str != NULL) && (str[0] != L'\0')) ? towupper(str[0]) : 0); }

    int CompareSegments(__in_ecount(cchStr1) PCWSTR pStr1, __in int cchStr1, __in_ecount(cchStr2) PCWSTR pStr2, __in int cchStr2) const
    {
        // CompareStringOrdinal returns constants.  MSDN says subtract 2
        // to be consistent with the C runtime.
        int rtrn = CompareStringOrdinal(pStr1, cchStr1, pStr2, cchStr2, TRUE) - 2;
        return rtrn;
    }

    int CompareSegments(__in PCWSTR pStr1, __in PCWSTR pStr2) const
    {
        // CompareStringOrdinal returns constants.  MSDN says subtract 2
        // to be consistent with the C runtime.
        int rtrn = CompareStringOrdinal(pStr1, -1, pStr2, -1, TRUE) - 2;
        return rtrn;
    }

    int CompareStoredAsciiSegment(_In_ PCSTR pStoredSegment, _In_ PCWSTR pRequestedSegment) const;

    int CompareStoredAsciiSegment(
        _In_reads_or_z_(cchStoredSegment) PCSTR pStoredSegment,
        _In_ int cchStoredSegment,
        _In_ PCWSTR pRequestedSegment) const;

    bool IsValidSegment(__in PCWSTR pSegment) const;

    _Success_(return ) _Post_satisfies_(*pSegmentLengthOut <= _String_length_(pFullName)) bool TryGetNextSegmentLength(
        _Inout_ PCWSTR pFullName,
        _Out_ int* pSegmentLengthOut,
        _Out_ bool* pbMoreSegmentsOut) const;

protected:
    HierarchicalNamesConfig() {}
};

class IHierarchicalNames : protected DefObject
{
public:
    using DefObject::operator delete;

    virtual int GetNumNames() const = 0;
    virtual int GetMaxNameLength() const = 0;

    virtual bool TryGetName(
        __in int nodeIndex,
        __inout_opt StringResult* pNameOut,
        __out_opt int* pScopeIndexOut = NULL,
        __out_opt int* pItemIndexOut = NULL) const = 0;

    virtual bool TryGetName(
        __in int nodeIndex,
        __in int relativeToScope,
        __inout_opt StringResult* pNameOut,
        __out_opt int* pScopeIndexOut = NULL,
        __out_opt int* pItemIndexOut = NULL) const = 0;

    virtual bool Contains(
        __in PCWSTR path,
        __out_opt int* pScopeIndexOut = NULL,
        __out_opt int* pItemIndexOut = NULL,
        __out_opt int* pNameIndexOut = NULL) const = 0;

    virtual bool Contains(
        __in PCWSTR path,
        __in int relativeToScope,
        __out_opt int* pScopeIndexOut = NULL,
        __out_opt int* pItemIndexOut = NULL,
        __out_opt int* pNameIndexOut = NULL) const = 0;

    virtual int GetNumScopes() const = 0;
    virtual IAtomPool* GetScopeNames() const = 0;

    virtual bool TryGetScopeInfo(__in int scopeIndex, __out StringResult* pNameOut, __out_opt int* numChildren = 0) const = 0;

    virtual bool TryGetScopeChild(
        __in int scopeIndex,
        __in int childIndex,
        __out_opt int* pChildScopeIndexOut,
        __out_opt int* pChildItemIndexOut) const = 0;

    virtual bool TryGetScopeChildName(__in int scopeIndex, __in int childIndex, __inout StringResult* pNameOut) const = 0;

    virtual int GetNumItems() const = 0;
    virtual IAtomPool* GetItemNames() const = 0;

    virtual bool TryGetItemInfo(__in int itemIndex, __inout StringResult* pNameOut) const = 0;
};

class HierarchicalNames : public IHierarchicalNames, public FileSectionBase, public HierarchicalNamesConfig
{
public:
    using IHierarchicalNames::operator delete;

    static HRESULT CreateInstance(_In_ const IFileSection* pSection, _Outptr_ HierarchicalNames** result);

    static HRESULT CreateInstance(
        _In_ const DEFFILE_SECTION_TYPEID& type,
        _In_reads_bytes_(cbData) const void* pData,
        _In_ int cbData,
        _Outptr_ HierarchicalNames** result);

    ~HierarchicalNames();

    int GetNumNames() const { return m_pHeader->numNodes; }
    int GetMaxNameLength() const { return m_pHeader->cchLongestPath; }

    _Success_(return ) bool TryGetName(
        __in int nodeIndex,
        __inout_opt StringResult* pNameOut,
        __out_opt int* pScopeIndexOut = NULL,
        __out_opt int* pItemIndexOut = NULL) const;

    _Success_(return ) bool TryGetName(
        __in int nodeIndex,
        __in int relativeToScope,
        __inout_opt StringResult* pNameOut,
        __out_opt int* pScopeIndexOut = NULL,
        __out_opt int* pItemIndexOut = NULL) const;

    bool Contains(
        __in PCWSTR path,
        __out_opt int* pScopeIndexOut = NULL,
        __out_opt int* pItemIndexOut = NULL,
        __out_opt int* pNameIndexOut = NULL) const;

    _Success_(return == true)
    bool Contains(
        __in PCWSTR path,
        __in int relativeToScope,
        __out_opt int* pScopeIndexOut = NULL,
        __out_opt int* pItemIndexOut = NULL,
        __out_opt int* pNameIndexOut = NULL) const;

    int GetNumScopes() const { return m_pHeader->numScopes; }
    IAtomPool* GetScopeNames() const { return m_pScopeNames; }

    _Success_(
        return ) bool TryGetScopeInfo(__in int scopeIndex, __inout StringResult* pNameOut, __out_opt int* numChildrenOut = NULL) const;

    _Success_(return ) bool TryGetScopeChild(
        __in int scopeIndex,
        __in int childIndex,
        __out_opt int* pChildScopeIndexOut,
        __out_opt int* pChildItemIndexOut) const;

    _Success_(return ) bool TryGetScopeChildName(__in int scopeIndex, __in int childIndex, __inout StringResult* pNameOut) const;

    int GetNumItems() const { return m_pHeader->numItems; }
    IAtomPool* GetItemNames() const { return m_pItemNames; }

    _Success_(return ) bool TryGetItemInfo(__in int itemIndex, __inout StringResult* pNameOut) const;

    _Success_(return ) bool TryGetItemLocalName(__in int itemIndex, __inout StringResult* pNameOut) const;

    static const DEFFILE_SECTION_TYPEID GetSectionTypeId();

    _Success_(return ) bool TryGetRelativeItemName(_In_ int relativeToScope, _Inout_ int itemIndex, _Inout_ StringResult* pNameOut) const;

    _Success_(return ) bool TryGetRelativeScopeName(_In_ int relativeToScope, _Inout_ int scopeIndex, _Inout_ StringResult* pNameOut) const;

    HRESULT GetNumDescendents(_In_ int scopeIndex, _Out_opt_ int* pNumScopes, _Out_opt_ int* pNumItems) const
    {
        return GetNumDescendents(scopeIndex, 0, pNumScopes, pNumItems);
    }

    HRESULT GetDescendents(
        _In_ int scopeIndex,
        _In_ int sizeScopes,
        _Out_writes_to_opt_(sizeScopes, *pNumScopesWritten) int* pScopesOut,
        _Out_opt_ int* pNumScopesWritten,
        _In_ int sizeItems,
        _Out_writes_to_opt_(sizeItems, *pNumItemsWritten) int* pItemsOut,
        _Out_opt_ int* pNumItemsWritten) const;

private:
    bool m_largeNode;
    DEFFILE_HNAMES_HEADER_EX m_header{};
    const DEFFILE_HNAMES_HEADER_EX* m_pHeader;
    __field_ecount(m_pHeader->numNodes) const DEFFILE_HNAMES_NODE* m_pNodes;
    __field_ecount(m_pHeader->numScopes) const DEFFILE_HNAMES_SCOPE* m_pScopes;
    __field_ecount(m_pHeader->numItems) const UINT16* m_pItems;
    __field_ecount(m_pHeader->numNodes) const DEFFILE_HNAMES_NODE_LARGE* m_pNodesLarge;
    __field_ecount(m_pHeader->numScopes) const DEFFILE_HNAMES_SCOPE_LARGE* m_pScopesLarge;
    __field_ecount(m_pHeader->numItems) const UINT32* m_pItemsLarge;
    // not PCWSTR - not null terminated
    __field_ecount(m_pHeader->cchUtf16NamesPool) const WCHAR* m_pUtf16Names;
    __field_ecount(m_pHeader->cchAsciiNamesPool) const char* m_pAsciiNames;

    IAtomPool* m_pScopeNames;
    IAtomPool* m_pItemNames;

    HierarchicalNames();

    HRESULT Init(
        _In_ const DEFFILE_SECTION_TYPEID& type,
        _In_opt_ const IFileSection* pSection,
        _In_reads_bytes_(cbData) const void* pData,
        _In_ int cbData);

    HRESULT GetNumDescendents(_In_ int scopeIndex, _In_ UINT32 currentDepth, _Out_opt_ int* pNumScopes, _Out_opt_ int* pNumItems) const;

    HRESULT GetAsciiName(_In_ int firstChar, _In_ int cchName, _Out_ PCSTR* result) const
    {
        *result = nullptr;
        // report an error if the string is out of range or
        // isn't null terminated
        if ((firstChar < 0) || (cchName < 0) || ((firstChar + cchName) >= (int)m_pHeader->cchAsciiNamesPool) ||
            (m_pAsciiNames[firstChar + cchName] != L'\0'))
        {
            return E_ABORT;
        }
        *result = &m_pAsciiNames[firstChar];
        return S_OK;
    }

    HRESULT GetUtf16Name(_In_ int firstChar, _In_ int cchName, _Out_ PCWSTR* result) const
    {
        // report an error if the string is out of range or
        // isn't null terminated
        if ((firstChar < 0) || (cchName < 0) || ((firstChar + cchName) >= (int)m_pHeader->cchUtf16NamesPool) ||
            (m_pUtf16Names[firstChar + cchName] != L'\0'))
        {
            return E_ABORT;
        }
        *result = &m_pUtf16Names[firstChar];
        return S_OK;
    }

    template<typename T>
    UINT32 GetNodeNameOffset(_In_ const T* node) const
    {
        return HNamesGetNodeNameOffset(node);
    }

    template<>
    UINT32 GetNodeNameOffset(_In_ const DEFFILE_HNAMES_NODE_LARGE* node) const
    {
        return HNamesGetNodeNameOffsetLarge(node);
    }

    template<typename T>
    HRESULT GetName(_In_ const T* pNode, _Inout_ StringResult* pNameOut) const
    {
        int nameOffset = GetNodeNameOffset(pNode);
        if ((pNode->flagsAndNameOffsetHigh & DEFFILE_HNAMES_FLAGS_NAME_IS_ASCII) != 0)
        {
            PCSTR pName;
            RETURN_IF_FAILED(GetAsciiName(nameOffset, pNode->cchName, &pName));

            PWSTR pBuf;
            RETURN_IF_FAILED(pNameOut->SetEmptyContents(pNode->cchName + 1, &pBuf));

            for (int i = 0; i < pNode->cchName; i++)
            {
                pBuf[i] = pName[i];
            }
            pBuf[pNode->cchName] = L'\0';
            return S_OK;
        }
        PCWSTR name;
        RETURN_IF_FAILED(GetUtf16Name(nameOffset, pNode->cchName, &name));
        RETURN_IF_FAILED(pNameOut->SetRef(name));
        return S_OK;
    }

    template<typename T>
    HRESULT CompareNameSegment(_In_ const T* pNode, _In_ PCWSTR pRequestedSegment, _Out_ int* result) const;

    HRESULT CopyNameSegment(_In_ UINT32 flags, _In_ int firstCharOffset, _In_ int cchName, _Out_writes_(cchName) WCHAR* pNameOut) const
    {
        if ((flags & DEFFILE_HNAMES_FLAGS_NAME_IS_ASCII) != 0)
        {
            PCSTR pName;
            RETURN_IF_FAILED(GetAsciiName(firstCharOffset, cchName, &pName));
            for (int i = 0; i < cchName; i++)
            {
                pNameOut[i] = pName[i];
            }
        }
        else
        {
            PCWSTR pName;
            RETURN_IF_FAILED(GetUtf16Name(firstCharOffset, cchName, &pName));
            memcpy(pNameOut, pName, cchName * sizeof(WCHAR));
        }
        return S_OK;
    }
};

} // namespace Microsoft::Resources
