// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources::Build
{

_Use_decl_annotations_ HierarchicalSchemaVersionInfoBuilder::HierarchicalSchemaVersionInfoBuilder(
    const IHierarchicalSchema* pSchema,
    UINT16 majorVersion,
    UINT16 minorVersion)
{
    m_pSchema = pSchema;
    m_major = majorVersion;
    m_minor = minorVersion;
}

HRESULT HierarchicalSchemaVersionInfoBuilder::CreateInstance(
    const IHierarchicalSchema* pSchema,
    int majorVersion,
    int minorVersion,
    HierarchicalSchemaVersionInfoBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (majorVersion < 0) || (majorVersion > 0xffff));
    RETURN_HR_IF(E_INVALIDARG, (minorVersion < 0) || (minorVersion > 0xffff));

    HierarchicalSchemaVersionInfoBuilder* ret =
        new HierarchicalSchemaVersionInfoBuilder(pSchema, static_cast<UINT16>(majorVersion), static_cast<UINT16>(minorVersion));
    RETURN_IF_NULL_ALLOC(ret);

    *result = ret;
    return S_OK;
}

size_t HierarchicalSchemaVersionInfoBuilder::GetMaxSizeInBytes() const { return sizeof(MRMFILE_HSCHEMA_VERSION_INFO); }

_Use_decl_annotations_ HRESULT HierarchicalSchemaVersionInfoBuilder::Build(void* pBuffer, size_t cbBuffer, UINT32* pcbWrittenOut) const
{
    RETURN_HR_IF(E_INVALIDARG, cbBuffer < sizeof(MRMFILE_HSCHEMA_VERSION_INFO));

    _Analysis_assume_(cbBuffer >= sizeof(MRMFILE_HSCHEMA_VERSION_INFO));

    MRMFILE_HSCHEMA_VERSION_INFO* pVersion = reinterpret_cast<MRMFILE_HSCHEMA_VERSION_INFO*>(pBuffer);
    pVersion->major = m_major;
    pVersion->minor = m_minor;
    pVersion->numScopes = m_pSchema->GetNumScopes();
    pVersion->numItems = m_pSchema->GetNumItems();
    pVersion->csType = MRMFILE_HSCHEMA_CSTYPE_DEFAULT;
    pVersion->checksum = 0;

    RETURN_IF_FAILED(ComputeHierarchicalSchemaVersionChecksum(m_pSchema, this, &pVersion->checksum));

    if (pcbWrittenOut != nullptr)
    {
        *pcbWrittenOut = sizeof(MRMFILE_HSCHEMA_VERSION_INFO);
    }
    return S_OK;
}

DEF_CHECKSUM
HierarchicalSchemaVersionInfoBuilder::GetVersionChecksum() const
{
    DEF_CHECKSUM cs = 0;
    if (SUCCEEDED(ComputeHierarchicalSchemaVersionChecksum(m_pSchema, this, &cs)))
    {
        return cs;
    }
    return 0;
}

HierarchicalSchemaSectionBuilder::HierarchicalSchemaSectionBuilder() :
    m_finalized(false),
    m_numFinalizedScopes(-1),
    m_numFinalizedItems(-1),
    m_cchUniqueId(-1),
    m_cchSimpleId(-1),
    m_cbNamesBlob(-1),
    m_sectionIndex(BaseFile::SectionIndexNone),
    m_pVersionInfo(nullptr),
    m_pPriBuilder(nullptr),
    m_numPreviousScopes(-1),
    m_pSimpleId(nullptr),
    m_pUniqueId(nullptr),
    m_priBuildType(PriBuildType::PriBuildFromScratch),
    m_majorVersion(0),
    m_minorVersion(0),
    m_pNames(nullptr),
    m_pScopeNames(nullptr),
    m_pItemNames(nullptr),
    m_bIsVersionUpdated(false),
    m_pPreviousSchema(nullptr),
    m_buildFlags(0)
{}

HRESULT HierarchicalSchemaSectionBuilder::Init(
    _In_ PriSectionBuilder* pPriBuilder,
    _In_ PCWSTR pSimpleId,
    _In_ PCWSTR pUniqueId,
    UINT16 majorVersion)
{
    m_pPriBuilder = pPriBuilder;
    m_majorVersion = majorVersion;

    m_pSimpleId = _DefDuplicateString(pSimpleId);
    RETURN_IF_NULL_ALLOC(m_pSimpleId);

    m_pUniqueId = _DefDuplicateString(pUniqueId);
    RETURN_IF_NULL_ALLOC(m_pUniqueId);

    m_buildFlags = pPriBuilder->GetBuildConfiguration()->GetFlags();
    UINT32 namesBuildFlags =
        (((m_buildFlags & MrmBuildConfiguration::UseOptimalSchemaEncodingFlag) == 0) ? HierarchicalNamesBuilder::BuildUtf16Only :
                                                                                       HierarchicalNamesBuilder::BuildAsciiOrUtf16);

    RETURN_IF_FAILED(HierarchicalNamesBuilder::CreateInstance(namesBuildFlags, pPriBuilder->GetAtoms(), &m_pNames));

    return S_OK;
}

HRESULT
HierarchicalSchemaSectionBuilder::Init(
    _In_ PriSectionBuilder* pPriBuilder,
    _In_ const IHierarchicalSchema* const pPreviousSchema,
    PriBuildType priBuildType)
{
    m_pPriBuilder = pPriBuilder;
    m_priBuildType = priBuildType;
    m_majorVersion = pPreviousSchema->GetMajorVersion();
    m_minorVersion = pPreviousSchema->GetMinorVersion();
    m_pPreviousSchema = pPreviousSchema;

    // schema name is needed for schema identity
    m_pSimpleId = _DefDuplicateString(m_pPreviousSchema->GetSimpleId());
    RETURN_IF_NULL_ALLOC(m_pSimpleId);

    m_pUniqueId = _DefDuplicateString(m_pPreviousSchema->GetUniqueId());
    RETURN_IF_NULL_ALLOC(m_pUniqueId);

    m_buildFlags = pPriBuilder->GetBuildConfiguration()->GetFlags();
    UINT32 namesBuildFlags =
        (((m_buildFlags & MrmBuildConfiguration::UseOptimalSchemaEncodingFlag) == 0) ? HierarchicalNamesBuilder::BuildUtf16Only :
                                                                                       HierarchicalNamesBuilder::BuildAsciiOrUtf16);

    RETURN_IF_FAILED(HierarchicalNamesBuilder::CreateInstance(namesBuildFlags, pPriBuilder->GetAtoms(), &m_pNames));

    if ((m_priBuildType & PriBuildType::PriBuildForDeploymentMerge) == 0)
    {
        // When PriBuildForDeploymentMerge is set, the previous schema should not
        // be unmapped as it can be read at the end of Build of the schema section.
        RETURN_IF_FAILED(ReadPreviousSchemaContents());
    }

    return S_OK;
}

HRESULT HierarchicalSchemaSectionBuilder::CreateInstance(
    _In_ PriSectionBuilder* pPriBuilder,
    _In_ PCWSTR pDisplayName,
    _In_ PCWSTR pUniqueName,
    UINT16 majorVersion,
    _Outptr_ HierarchicalSchemaSectionBuilder** result)
{
    *result = nullptr;

    AutoDeletePtr<HierarchicalSchemaSectionBuilder> ret = new HierarchicalSchemaSectionBuilder();
    RETURN_IF_NULL_ALLOC(ret);
    RETURN_IF_FAILED(ret->Init(pPriBuilder, pDisplayName, pUniqueName, majorVersion));

    *result = ret.Detach();
    return S_OK;
}

HRESULT HierarchicalSchemaSectionBuilder::CreateInstance(
    _In_ PriSectionBuilder* pPriBuilder,
    _In_ const IHierarchicalSchema* const pPreviousSchema,
    PriBuildType priBuildType,
    _Outptr_ HierarchicalSchemaSectionBuilder** result)
{
    *result = nullptr;

    AutoDeletePtr<HierarchicalSchemaSectionBuilder> ret = new HierarchicalSchemaSectionBuilder();
    RETURN_IF_NULL_ALLOC(ret);
    RETURN_IF_FAILED(ret->Init(pPriBuilder, pPreviousSchema, priBuildType));

    *result = ret.Detach();
    return S_OK;
}

HRESULT HierarchicalSchemaSectionBuilder::CreateInstanceFromDescription(
    PriSectionBuilder* pPriBuilder,
    const IHierarchicalSchemaDescription* pDescription,
    PriBuildType priBuildType,
    HierarchicalSchemaSectionBuilder** result)
{
    *result = nullptr;

    AutoDeletePtr<HierarchicalSchemaSectionBuilder> ret = new HierarchicalSchemaSectionBuilder();
    RETURN_IF_NULL_ALLOC(ret);
    RETURN_IF_FAILED(ret->Init(pPriBuilder, pDescription->GetSimpleId(), pDescription->GetUniqueId(), pDescription->GetMajorVersion()));

    RETURN_IF_FAILED(ret->ReadSchemaDescription(pDescription));

    ret->m_priBuildType = priBuildType;
    ret->m_minorVersion = pDescription->GetMinorVersion();

    *result = ret.Detach();
    return S_OK;
}

HierarchicalSchemaSectionBuilder::~HierarchicalSchemaSectionBuilder()
{
    Def_Free(m_pSimpleId);
    Def_Free(m_pUniqueId);

    delete m_pNames;
    delete m_pVersionInfo;

    m_pSimpleId = m_pUniqueId = nullptr;
    m_pNames = nullptr;
    m_pVersionInfo = nullptr;
}

bool HierarchicalSchemaSectionBuilder::Contains(PCWSTR pPath, int* pScopeIndexOut, int* pItemIndexOut) const
{
    if (m_pPreviousSchema != nullptr)
    {
        return m_pPreviousSchema->Contains(pPath, pScopeIndexOut, pItemIndexOut);
    }
    return m_pNames->Contains(pPath, pScopeIndexOut, pItemIndexOut);
}

bool HierarchicalSchemaSectionBuilder::Contains(PCWSTR pPath, int relativeToScope, int* pScopeIndexOut, int* pItemIndexOut) const
{
    if (m_pPreviousSchema != nullptr)
    {
        return m_pPreviousSchema->Contains(pPath, relativeToScope, pScopeIndexOut, pItemIndexOut);
    }

    return m_pNames->Contains(pPath, relativeToScope, pScopeIndexOut, pItemIndexOut);
}

bool HierarchicalSchemaSectionBuilder::ContainsScope(PCWSTR scopeName, int* foundScopeIndex) const
{
    int scopeIndex = -1;
    int itemIndex = -1;

    (m_pPreviousSchema != nullptr ? m_pPreviousSchema->Contains(scopeName, &scopeIndex, &itemIndex) :
                                    m_pNames->Contains(scopeName, &scopeIndex, &itemIndex));

    if (foundScopeIndex != nullptr)
    {
        *foundScopeIndex = scopeIndex;
    }

    return (scopeIndex >= 0);
}

bool HierarchicalSchemaSectionBuilder::ContainsItem(PCWSTR itemName, int* foundItemIndex) const
{
    int scopeIndex = -1;
    int itemIndex = -1;

    (m_pPreviousSchema != nullptr ? m_pPreviousSchema->Contains(itemName, &scopeIndex, &itemIndex) :
                                    m_pNames->Contains(itemName, &scopeIndex, &itemIndex));

    if (foundItemIndex != nullptr)
    {
        *foundItemIndex = itemIndex;
    }

    return (itemIndex >= 0);
}

HRESULT HierarchicalSchemaSectionBuilder::GetOrAddScope(PCWSTR pScopeName, int* index)
{
    *index = -1;
    if (m_pPreviousSchema != nullptr)
    {
        RETURN_IF_FAILED(ReadPreviousSchemaContents());
    }

    if (!m_pNames->Contains(pScopeName))
    {
        if ((m_priBuildType == PriBuildType::PriBuildFromPrevReadOnlySchema))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE);
        }
    }

    ScopeInfo* pScope;
    RETURN_IF_FAILED(m_pNames->GetOrAddScope(pScopeName, &pScope));

    *index = pScope->GetIndex();
    return S_OK;
}

HRESULT HierarchicalSchemaSectionBuilder::GetOrAddItem(PCWSTR pItemName, int* index)
{
    *index = -1;
    if (m_pPreviousSchema != nullptr)
    {
        RETURN_IF_FAILED(ReadPreviousSchemaContents());
    }

    if (!m_pNames->Contains(pItemName))
    {
        if ((m_priBuildType == PriBuildType::PriBuildFromPrevReadOnlySchema))
        {
            return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_FILE_TYPE);
        }
    }

    ItemInfo* pItem;
    RETURN_IF_FAILED(m_pNames->GetOrAddItem(pItemName, &pItem));

    *index = pItem->GetIndex();
    return S_OK;
}

_Success_(return == true)
bool HierarchicalSchemaSectionBuilder::TryGetScopeInfo(_In_ int scopeIndex, _Out_ StringResult* pNameOut, _Out_opt_ int* pNumChildrenOut) const
{
    if (m_pPreviousSchema != nullptr)
    {
        return m_pPreviousSchema->TryGetScopeInfo(scopeIndex, pNameOut, pNumChildrenOut);
    }

    ScopeInfo* pScope = nullptr;

    if (!m_pNames->TryGetScopeByIndex(scopeIndex, &pScope))
    {
        return false;
    }

    if (pNumChildrenOut != nullptr)
    {
        *pNumChildrenOut = pScope->GetNumChildren();
    }
    return SUCCEEDED(pScope->GetFullPath(pNameOut));
}

_Success_(return == true)
bool HierarchicalSchemaSectionBuilder::TryGetScopeChild(_In_ int scopeIndex, _In_ int childIndex, _Out_opt_ int* pChildScopeIndexOut, _Out_opt_ int* pChildItemIndexOut)
    const
{
    if (m_pPreviousSchema != nullptr)
    {
        return m_pPreviousSchema->TryGetScopeChild(scopeIndex, childIndex, pChildScopeIndexOut, pChildItemIndexOut);
    }

    ScopeInfo* pScope = nullptr;

    if (!m_pNames->TryGetScopeByIndex(scopeIndex, &pScope))
    {
        return false;
    }

    if ((childIndex < 0) || childIndex > pScope->GetNumChildren())
    {
        return false;
    }

    HNamesNode* pChild;
    if (!pScope->TryGetChild(childIndex, &pChild))
    {
        return false;
    }

    if (pChildScopeIndexOut != nullptr)
    {
        *pChildScopeIndexOut = (pChild->IsScope() ? pChild->GetIndex() : -1);
    }

    if (pChildItemIndexOut != nullptr)
    {
        *pChildItemIndexOut = (pChild->IsScope() ? -1 : pChild->GetIndex());
    }

    return true;
}

bool HierarchicalSchemaSectionBuilder::TryGetScopeChildName(int scopeIndex, int childIndex, StringResult* pNameOut) const
{
    if (m_pPreviousSchema != nullptr)
    {
        return m_pPreviousSchema->TryGetScopeChildName(scopeIndex, childIndex, pNameOut);
    }

    ScopeInfo* pScope = nullptr;

    if (!m_pNames->TryGetScopeByIndex(scopeIndex, &pScope))
    {
        return false;
    }

    if ((childIndex < 0) || childIndex > pScope->GetNumChildren())
    {
        return false;
    }

    HNamesNode* pChild;
    if (!pScope->TryGetChild(childIndex, &pChild))
    {
        return false;
    }

    if (pNameOut != nullptr)
    {
        Def_IfFailedReturnFalse(pNameOut->SetRef(pScope->GetName()));
    }
    return true;
}

bool HierarchicalSchemaSectionBuilder::TryGetItemInfo(int itemIndex, StringResult* pNameOut) const
{
    if (m_pPreviousSchema != nullptr)
    {
        return m_pPreviousSchema->TryGetScopeInfo(itemIndex, pNameOut);
    }

    ItemInfo* pItem = nullptr;

    if (!m_pNames->TryGetItemByIndex(itemIndex, &pItem))
    {
        return false;
    }
    return SUCCEEDED(pItem->GetFullPath(pNameOut));
}

bool HierarchicalSchemaSectionBuilder::TryGetItemLocalName(int /*itemIndex*/, StringResult* pNameOut) const
{
    pNameOut->SetRef(nullptr);
    return false;
}

bool HierarchicalSchemaSectionBuilder::TryGetRelativeItemName(int /*relativeToScope*/, int /*itemIndex*/, StringResult* pNameOut) const
{
    pNameOut->SetRef(nullptr);
    return false;
}

bool HierarchicalSchemaSectionBuilder::TryGetRelativeScopeName(int /*relativeToScope*/, int /*scopeIndex*/, StringResult* pNameOut) const
{
    pNameOut->SetRef(nullptr);
    return false;
}

HRESULT HierarchicalSchemaSectionBuilder::GetNumDescendents(int /*scopeIndex*/, int* /*pNumScopes*/, int* /*pNumItems*/) const
{
    return E_NOTIMPL;
}

HRESULT HierarchicalSchemaSectionBuilder::GetDescendents(
    int /*scopeIndex*/,
    int /*sizeScopes*/,
    int* /*pScopesOut*/,
    int* /*pNumScopesWritten*/,
    int /*sizeItems*/,
    int* /*pItemsOut*/,
    int* /*pNumItemsWritten*/) const
{
    return E_NOTIMPL;
}

const IHierarchicalSchemaVersionInfo* HierarchicalSchemaSectionBuilder::GetVersionInfo(int index) const
{
    if (m_pPreviousSchema)
    {
        return m_pPreviousSchema->GetVersionInfo(index);
    }

    if ((index != 0) || !IsFinalized())
    {
        return nullptr;
    }

    if (m_pVersionInfo == nullptr)
    {
        (void)HierarchicalSchemaVersionInfoBuilder::CreateInstance(this, m_majorVersion, m_minorVersion, &m_pVersionInfo);
    }

    return m_pVersionInfo;
}

HRESULT HierarchicalSchemaSectionBuilder::Clone(IHierarchicalSchema**) const { return E_NOTIMPL; }

HRESULT HierarchicalSchemaSectionBuilder::GetSchemaBlobFromFileSection(
    DEFFILE_SECTION_TYPEID* /*pSectionTypeResult*/,
    BlobResult* /*pBlobResult*/) const
{
    return E_NOTIMPL;
}

bool HierarchicalSchemaSectionBuilder::IsValid() const
{
    if (m_pPreviousSchema != nullptr)
    {
        return true;
    }

    return m_pNames->IsValid() && !DefString_IsEmpty(m_pUniqueId) && !DefString_IsEmpty(m_pSimpleId);
}

int HierarchicalSchemaSectionBuilder::GetNumNames() const
{
    if (m_pPreviousSchema != nullptr)
    {
        DEF_ASSERT(m_pPreviousSchema->GetItemNames() != nullptr);
        DEF_ASSERT(m_pPreviousSchema->GetScopeNames() != nullptr);

        return m_pPreviousSchema->GetItemNames()->GetNumAtoms() + m_pPreviousSchema->GetScopeNames()->GetNumAtoms();
    }

    return m_pNames->GetNumNames();
}

int HierarchicalSchemaSectionBuilder::GetNumScopes() const
{
    if (m_pPreviousSchema != nullptr)
    {
        DEF_ASSERT(m_pPreviousSchema->GetScopeNames() != nullptr);
        return m_pPreviousSchema->GetScopeNames()->GetNumAtoms();
        ;
    }

    return m_pNames->GetNumScopes();
}

int HierarchicalSchemaSectionBuilder::GetNumItems() const
{
    if (m_pPreviousSchema != nullptr)
    {
        DEF_ASSERT(m_pPreviousSchema->GetItemNames() != nullptr);
        return m_pPreviousSchema->GetItemNames()->GetNumAtoms();
    }

    return m_pNames->GetNumItems();
}

IAtomPool* HierarchicalSchemaSectionBuilder::GetScopeNames() const
{
    if (m_pPreviousSchema != nullptr)
    {
        return m_pPreviousSchema->GetScopeNames();
    }

    return m_pNames->GetScopeNames();
}
IAtomPool* HierarchicalSchemaSectionBuilder::GetItemNames() const
{
    if (m_pPreviousSchema != nullptr)
    {
        return m_pPreviousSchema->GetItemNames();
    }

    return m_pNames->GetItemNames();
}

HRESULT HierarchicalSchemaSectionBuilder::ReadPreviousSchemaContents()
{
    if (m_pPreviousSchema == nullptr)
    {
        // it already read it
        return S_OK;
    }

    // We're only going to try to read this once, so clear
    // it out whether this works or not.
    const IHierarchicalSchema* pSchema = m_pPreviousSchema;
    m_pPreviousSchema = nullptr;
    return ReadSchemaDescription(pSchema);
}

HRESULT HierarchicalSchemaSectionBuilder::ReadSchemaDescription(const IHierarchicalSchemaDescription* pDescription)
{
    //Save the values from the description
    m_numPreviousScopes = pDescription->GetNumScopes();
    m_numPreviousItems = pDescription->GetNumItems();
    m_numPreviousMinorVersion = pDescription->GetMinorVersion();

    m_pItemNames = m_pNames->GetItemNames();
    m_pScopeNames = m_pNames->GetScopeNames();

    StringResult name;

    const IAtomPool* pOldPool = pDescription->GetScopeNames();
    // start at 1 because scope 0, the root scope, always has
    // an empty name.
    for (int i = 1; i < pOldPool->GetNumAtoms(); i++)
    {
        if (!pOldPool->TryGetString(i, &name))
        {
            return E_ABORT;
        }

        const ScopeInfo* pScope;
        RETURN_IF_FAILED(m_pNames->GetOrAddScope(name.GetRef(), (ScopeInfo**)&pScope));
        if ((pScope == nullptr) || (pScope->GetIndex() != i))
        {
            return E_ABORT;
        }
    }

    pOldPool = pDescription->GetItemNames();
    for (int i = 0; i < pOldPool->GetNumAtoms(); i++)
    {
        if (!pOldPool->TryGetString(i, &name))
        {
            return E_ABORT;
        }

        const ItemInfo* pItem;
        RETURN_IF_FAILED(m_pNames->GetOrAddItem(name.GetRef(), (ItemInfo**)&pItem));
        if ((pItem == nullptr) || (pItem->GetIndex() != i))
        {
            return E_ABORT;
        }
    }

    return S_OK;
}

bool HierarchicalSchemaSectionBuilder::IsFinalized() const
{
    if (m_pPreviousSchema != nullptr)
    {
        // There is no additional item/scope is added in addition to given previous schema, then
        // it return true all the time.
        return m_finalized && (m_numFinalizedScopes == GetNumScopes()) && (m_numFinalizedItems == GetNumItems());
    }
    else
    {
        return m_finalized && (m_pNames->GetNumScopes() == m_numFinalizedScopes) && (m_pNames->GetNumItems() == m_numFinalizedItems);
    }
}

HRESULT HierarchicalSchemaSectionBuilder::Finalize()
{
    if (m_pPreviousSchema != nullptr)
    {
        // There is no additional item/scope is added in addition to given previous schema, then
        // it return true all the time.
        m_numFinalizedScopes = GetNumScopes();
        m_numFinalizedItems = GetNumItems();
        m_finalized = true;
        return S_OK;
    }

    RETURN_HR_IF(E_FAIL, !IsValid());

    RETURN_IF_FAILED(m_pNames->Finalize());

    if (IsFinalized())
    {
        return S_OK;
    }

    delete m_pVersionInfo;
    m_pVersionInfo = nullptr;

    m_numFinalizedScopes = m_pNames->GetNumScopes();
    m_numFinalizedItems = m_pNames->GetNumItems();

    m_cchUniqueId = static_cast<int>(wcslen(m_pUniqueId) + 1);
    m_cchSimpleId = static_cast<int>(wcslen(m_pSimpleId) + 1);
    m_cbNamesBlob = m_pNames->GetMaxSizeInBytes();

    if (m_numPreviousScopes != -1)
    {
        if ((m_numPreviousScopes != m_numFinalizedScopes) || (m_numPreviousItems != m_numFinalizedItems))
        {
            m_minorVersion = m_numPreviousMinorVersion + 1;
        }
    }

    m_finalized = true;
    return S_OK;
}

UINT32 HierarchicalSchemaSectionBuilder::GetMaxSizeInBytes() const
{
    // If we end up using a schema reference instead of a schema, this section is blank.
    if (m_pPriBuilder->GetBuildConfiguration()->UseSchemaReference())
    {
        return 0;
    }

    if (m_pPreviousSchema != nullptr)
    {
        // There is no additional item/scope is added in addition to given previous schema, then
        // it return true all the time.
        BlobResult blobResult;
        if (FAILED(m_pPreviousSchema->GetSchemaBlobFromFileSection(nullptr, &blobResult)))
        {
            return 0;
        }

        DEF_ASSERT(blobResult.GetSize() != 0);

        return static_cast<UINT32>(blobResult.GetSize());
    }

    if (!IsFinalized())
    {
        return 0;
    }

    UINT32 cbTotal = 0;

    if ((m_buildFlags & MrmBuildConfiguration::UseOptimalSchemaEncodingFlag) == 0)
    {
        // legacy schema (UTF16 only)
        cbTotal = sizeof(MRMFILE_HSCHEMA_HEADER);
        cbTotal += sizeof(MRMFILE_HSCHEMA_VERSION_INFO);
        cbTotal += m_cchUniqueId * sizeof(WCHAR);
        cbTotal += m_cchSimpleId * sizeof(WCHAR);
        cbTotal = _DEFFILE_PAD_SECTION(cbTotal);
        cbTotal += m_cbNamesBlob;
        cbTotal = _DEFFILE_PAD_SECTION(cbTotal);
    }
    else
    {
        cbTotal = sizeof(MRMFILE_HSCHEMA_HEADER_EX);
        cbTotal += sizeof(MRMFILE_HSCHEMA_VERSION_INFO);
        cbTotal += m_cchUniqueId * sizeof(WCHAR);
        cbTotal += m_cchSimpleId * sizeof(WCHAR);
        cbTotal = _DEFFILE_PAD_SECTION(cbTotal);
        cbTotal += m_cbNamesBlob;
        cbTotal = _DEFFILE_PAD_SECTION(cbTotal);
    }
    return cbTotal;
}

DEFFILE_SECTION_TYPEID
HierarchicalSchemaSectionBuilder::GetSectionType() const
{
    if (m_finalized && (m_pPreviousSchema != nullptr))
    {
        DEFFILE_SECTION_TYPEID ret;

        if (SUCCEEDED(m_pPreviousSchema->GetSchemaBlobFromFileSection(&ret, nullptr)))
        {
            return ret;
        }
    }

    return (
        ((m_buildFlags & MrmBuildConfiguration::UseOptimalSchemaEncodingFlag) == 0) ? HierarchicalSchema::GetSectionTypeId() :
                                                                                      HierarchicalSchema::GetExSectionTypeId());
}

HRESULT HierarchicalSchemaSectionBuilder::Build(VOID* pBuffer, UINT32 cbBuffer, UINT32* pcbWrittenOut) const
{
    MRMFILE_HSCHEMA_HEADER_EX* pHeaderEx = nullptr;
    MRMFILE_HSCHEMA_HEADER* pHeader = nullptr;
    MRMFILE_HSCHEMA_VERSION_INFO* pVersion;
    WCHAR* pUniqueId;
    WCHAR* pSimpleId;
    BYTE* pNamesBlob;

    RETURN_HR_IF(E_DEF_NOT_READY, !IsFinalized());

    if (pcbWrittenOut != nullptr)
    {
        *pcbWrittenOut = 0;
    }

    if (m_pPriBuilder->GetBuildConfiguration()->UseSchemaReference())
    {
        return S_OK;
    }

    if (m_pPreviousSchema != nullptr)
    {
        // There is no additional item/scope is added in addition to given previous schema, then
        // it return true all the time.
        BlobResult blobResult;
        RETURN_IF_FAILED(m_pPreviousSchema->GetSchemaBlobFromFileSection(nullptr, &blobResult));

        if (cbBuffer < blobResult.GetSize())
        {
            return HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
        }

        DEF_ASSERT(blobResult.GetRef(nullptr) != nullptr);
        memcpy(pBuffer, blobResult.GetRef(nullptr), cbBuffer);
        *pcbWrittenOut = cbBuffer;
        return S_OK;
    }

    SectionBuilderParser data;
    RETURN_IF_FAILED(data.Set(pBuffer, cbBuffer));

    HRESULT hr = S_OK;
    if ((m_buildFlags & MrmBuildConfiguration::UseOptimalSchemaEncodingFlag) == 0)
    {
        pHeader = _SECTION_BUILDER_NEXT(data, MRMFILE_HSCHEMA_HEADER, &hr);
    }
    else
    {
        pHeaderEx = _SECTION_BUILDER_NEXT(data, MRMFILE_HSCHEMA_HEADER_EX, &hr);
    }

    pVersion = _SECTION_BUILDER_NEXT(data, MRMFILE_HSCHEMA_VERSION_INFO, &hr);
    pUniqueId = _SECTION_BUILDER_NEXT_ARRAY(data, m_cchUniqueId, WCHAR, &hr);
    pSimpleId = _SECTION_BUILDER_NEXT_ARRAY(data, m_cchSimpleId, WCHAR, &hr);
    _SECTION_BUILDER_PAD(&data, BaseFile::Align32Bit, &hr);

    // determine the size of what we've written so far
    // so we can correctly compute actual written size later
    UINT32 cbNonNames = static_cast<UINT32>(data.UsedBufferSizeInBytes());

    pNamesBlob = _SECTION_BUILDER_NEXT_ARRAY(data, m_cbNamesBlob, BYTE, &hr);
    RETURN_IF_FAILED(hr);

    // Initialize header
    if (pHeader != nullptr)
    {
        pHeader->numVersions = 1;
        pHeader->cchUniqueId = static_cast<UINT16>(m_cchUniqueId);
        pHeader->cchSimpleId = static_cast<UINT16>(m_cchSimpleId);
        pHeader->pad = 0;
    }
    else
    {
        pHeaderEx->numVersions = 1;
        pHeaderEx->cchUniqueId = static_cast<UINT16>(m_cchUniqueId);
        pHeaderEx->cchSimpleId = static_cast<UINT16>(m_cchSimpleId);
        pHeaderEx->pad = 0;
        pHeaderEx->hnamesTypeId = m_pNames->GetSectionType();
    }

    // Version
    if (m_pVersionInfo == nullptr)
    {
        if (GetVersionInfo(0) == nullptr)
        {
            return E_ABORT;
        }
        __analysis_assume(m_pVersionInfo != nullptr);
    }

    RETURN_IF_FAILED(m_pVersionInfo->Build(pVersion, sizeof(MRMFILE_HSCHEMA_VERSION_INFO), nullptr));

    // Unique & Simple Id
    RETURN_IF_FAILED(DefString_CchCopy(pUniqueId, m_cchUniqueId, m_pUniqueId));

    RETURN_IF_FAILED(DefString_CchCopy(pSimpleId, m_cchSimpleId, m_pSimpleId));

    UINT32 cbNamesWritten = 0;
    RETURN_IF_FAILED(m_pNames->Build(pNamesBlob, m_cbNamesBlob, &cbNamesWritten));

    if (pcbWrittenOut != nullptr)
    {
        cbNamesWritten = _DEFFILE_PAD_SECTION(cbNamesWritten);
        *pcbWrittenOut = cbNonNames + cbNamesWritten;
    }
    return S_OK;
}

HRESULT HierarchicalSchemaReferenceSectionBuilder::CreateInstance(
    IHierarchicalSchema* schemaToReference,
    HierarchicalSchemaReferenceSectionBuilder** result)
{
    *result = nullptr;
    HierarchicalSchemaReferenceSectionBuilder* ret = new HierarchicalSchemaReferenceSectionBuilder(schemaToReference);
    RETURN_IF_NULL_ALLOC(ret);

    *result = ret;
    return S_OK;
}

HierarchicalSchemaReferenceSectionBuilder::HierarchicalSchemaReferenceSectionBuilder(IHierarchicalSchema* schemaToReference) :
    m_sectionIndex(BaseFile::SectionIndexNone), m_schemaToReference(schemaToReference)
{}

bool HierarchicalSchemaReferenceSectionBuilder::IsValid() const { return (!DefString_IsEmpty(m_schemaToReference->GetUniqueId())); }

UINT32 HierarchicalSchemaReferenceSectionBuilder::GetUniqueIdLength() const
{
    return static_cast<UINT32>(wcslen(m_schemaToReference->GetUniqueId()) + 1);
}

UINT32 HierarchicalSchemaReferenceSectionBuilder::GetMaxSizeInBytes() const
{
    UINT32 cbTotal = static_cast<UINT32>(sizeof(MRMFILE_HSCHEMA_REF) + (GetUniqueIdLength() * sizeof(WCHAR)));

    return _DEFFILE_PAD_SECTION(cbTotal);
}

HRESULT HierarchicalSchemaReferenceSectionBuilder::Build(VOID* buffer, UINT32 bufferSize, UINT32* bytesWritten) const
{
    SectionBuilderParser data;
    RETURN_IF_FAILED(data.Set(buffer, bufferSize));

    HRESULT hr = S_OK;
    MRMFILE_HSCHEMA_REF* schemaReference = _SECTION_BUILDER_NEXT(data, MRMFILE_HSCHEMA_REF, &hr);
    RETURN_IF_FAILED(hr);

    AutoDeletePtr<HierarchicalSchemaVersionInfoBuilder> versionBuilder;
    RETURN_IF_FAILED(HierarchicalSchemaVersionInfoBuilder::CreateInstance(
        m_schemaToReference, m_schemaToReference->GetMajorVersion(), m_schemaToReference->GetMinorVersion(), &versionBuilder));

    RETURN_IF_FAILED(versionBuilder->Build(&schemaReference->version, sizeof(MRMFILE_HSCHEMA_VERSION_INFO), bytesWritten));

    schemaReference->cchUniqueId = static_cast<UINT16>(GetUniqueIdLength());
    schemaReference->flags = 0;
    schemaReference->scopesPoolIndex = m_schemaToReference->GetScopeNames()->GetPoolIndex();
    schemaReference->itemsPoolIndex = m_schemaToReference->GetScopeNames()->GetPoolIndex();

    WCHAR* uniqueId = _SECTION_BUILDER_NEXT_ARRAY(data, schemaReference->cchUniqueId, WCHAR, &hr);
    RETURN_IF_FAILED(hr);

    RETURN_IF_FAILED(DefString_CchCopy(uniqueId, schemaReference->cchUniqueId, m_schemaToReference->GetUniqueId()));

    _SECTION_BUILDER_PAD(&data, BaseFile::Align32Bit, &hr);
    RETURN_IF_FAILED(hr);

    return S_OK;
}

} // namespace Microsoft::Resources::Build