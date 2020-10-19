// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources::Build
{

BuilderCandidateResult::BuilderCandidateResult() : m_pDecisionInfo(NULL), m_instanceValueType(Atom::NullAtom) {}

void BuilderCandidateResult::Set(
    _In_ const BUILDER_CANDIDATE* pBuilderCandidate,
    _In_ DecisionInfoSectionBuilder* pDecisionInfoBuilder,
    _In_ Atom instanceValueType)
{
    m_builderCandidate = *pBuilderCandidate;
    m_instanceValueType = instanceValueType;
    m_pDecisionInfo = pDecisionInfoBuilder;
}

HRESULT BuilderCandidateResult::GetQualifierSet(_Inout_ QualifierSetResult* pQualifierSetOut) const
{
    return m_pDecisionInfo->GetQualifierSet(m_builderCandidate.qualifierSetIndex, pQualifierSetOut);
}

int BuilderCandidateResult::GetFileIndex() const { return m_builderCandidate.value.detail; }

int BuilderCandidateResult::GetSectionIndex() const { return m_builderCandidate.value.data2; }

int BuilderCandidateResult::GetItemIndex() const { return (m_builderCandidate.value.data3 << 16) | m_builderCandidate.value.data1; }

class BuilderItemInfo : protected DefObject
{
public:
    static HRESULT CreateInstance(_Outptr_ BuilderItemInfo** result)
    {
        *result = nullptr;
        BuilderItemInfo* pRtrn = new BuilderItemInfo();
        RETURN_IF_NULL_ALLOC(pRtrn);

        *result = pRtrn;
        return S_OK;
    }

    using DefObject::operator delete;

    ~BuilderItemInfo()
    {
        delete m_pCandidates;
        m_pCandidates = NULL;
    }

    int GetNumCandidates() const { return ((m_pCandidates != NULL) ? m_pCandidates->Count() : 0); }
    int GetHasLargeCandidates() const { return m_hasLargeCandidates; }

    BUILDER_CANDIDATE* GetCandidate(_In_ int index) const
    {
        if ((index >= 0) && (index < m_pCandidates->Count()))
        {
            return &m_pCandidates->GetAll()[index];
        }
        return NULL;
    }

    HRESULT AddCandidate(_In_ const BUILDER_CANDIDATE& candidate, _In_ bool clobber, bool needLargeValue)
    {
        if (m_pCandidates == NULL)
        {
            RETURN_IF_FAILED(DynamicArray<BUILDER_CANDIDATE>::CreateInstance(2, &m_pCandidates));
        }
        else
        {
            BUILDER_CANDIDATE* pExisting = m_pCandidates->GetAll();
            for (int i = 0; i < m_pCandidates->Count(); i++)
            {
                if (pExisting[i].qualifierSetIndex == candidate.qualifierSetIndex)
                {
                    if (!clobber)
                    {
                        return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
                    }
                    pExisting[i] = candidate;
                    return S_OK;
                }
            }
        }

        RETURN_IF_FAILED(m_pCandidates->Add(candidate));

        if (needLargeValue)
        {
            m_hasLargeCandidates = true;
        }

        return S_OK;
    }

    bool TryFindCandidateForQualifierSet(_In_ int qualifierSetIndex, _Out_ const BUILDER_CANDIDATE** ppCandidateOut) const
    {
        if (m_pCandidates != NULL)
        {
            const BUILDER_CANDIDATE* pExisting = m_pCandidates->GetAll();
            for (int i = 0; i < m_pCandidates->Count(); i++)
            {
                if (pExisting[i].qualifierSetIndex == qualifierSetIndex)
                {
                    *ppCandidateOut = &pExisting[i];
                    return true;
                }
            }
        }

        return false;
    }

    HRESULT FinalizeCandidateIndexes(_In_ DecisionBuilder* pDecision)
    {
        BUILDER_CANDIDATE* pExisting = m_pCandidates->GetAll();

        // Now go back and figure out the position of each candidate in the final decision
        for (int iCandidate = 0; iCandidate < m_pCandidates->Count(); iCandidate++)
        {

            RETURN_IF_FAILED(
                pDecision->GetQualifierSetIndexInDecision(pExisting[iCandidate].qualifierSetIndex, &pExisting[iCandidate].indexInDecision));
        }
        return S_OK;
    }

    int GetDecisionIndex() const { return m_decisionIndex; }
    void SetDecisionIndex(_In_ int decisionIndex) { m_decisionIndex = decisionIndex; }

    bool GetHasLink() const { return m_hasLink; }
    void SetHasLink() { m_hasLink = true; }

    int GetBuiltItemEntryIndex() const { return m_builtItemIndex; }
    int GetBuiltFirstValueIndex() const { return m_builtFirstValueIndex; }

    void SetBuiltItemInfo(_In_ int itemIndex, _In_ int firstValueIndex)
    {
        m_builtItemIndex = itemIndex;
        m_builtFirstValueIndex = firstValueIndex;
    }

    HRESULT VerifyLinkedResourceIsCompatible(_In_ const BuilderItemInfo* linksToResource) const
    {
        for (int i = 0; i < GetNumCandidates(); i++)
        {
            BUILDER_CANDIDATE* mine = GetCandidate(i);
            bool matched = false;

            for (int o = 0; (o < linksToResource->GetNumCandidates()); o++)
            {
                BUILDER_CANDIDATE* other = linksToResource->GetCandidate(o);
                if (mine->qualifierSetIndex == other->qualifierSetIndex)
                {
                    if (!mine->pBuildInstanceReference->IsReferenceEqual(other->pBuildInstanceReference))
                    {
                        return E_DEFFILE_BUILD_LINK_TO_INCOMPATIBLE_RESOURCE;
                    }

                    matched = true;
                    break;
                }
            }

            if (!matched)
            {
                return E_DEFFILE_BUILD_LINK_TO_INCOMPATIBLE_RESOURCE;
            }
        }

        return S_OK;
    }

private:
    BuilderItemInfo() : m_pCandidates(nullptr), m_decisionIndex(-1), m_hasLink(false), m_builtItemIndex(-1), m_builtFirstValueIndex(-1) {}

    DynamicArray<BUILDER_CANDIDATE>* m_pCandidates;
    int m_decisionIndex;
    bool m_hasLink;

    int m_builtItemIndex;
    int m_builtFirstValueIndex;

    bool m_hasLargeCandidates = false;
};

class ResourceMapSectionBuilder::MapBuilderItemData : protected DefObject
{
public:
    static HRESULT CreateInstance(_In_ ResourceMapSectionBuilder* pMap, _Outptr_ MapBuilderItemData** result)
    {
        *result = nullptr;
        MapBuilderItemData* pRtrn = new MapBuilderItemData(pMap);
        RETURN_IF_NULL_ALLOC(pRtrn);

        *result = pRtrn;
        return S_OK;
    }

    static HRESULT CreateInstance(
        _In_ ResourceMapSectionBuilder* pMap,
        _In_ PriBuildType priBuildType,
        _Outptr_ MapBuilderItemData** result)
    {
        *result = nullptr;
        MapBuilderItemData* pRtrn = new MapBuilderItemData(pMap, priBuildType);
        RETURN_IF_NULL_ALLOC(pRtrn);

        *result = pRtrn;
        return S_OK;
    }

    using DefObject::operator delete;

    virtual ~MapBuilderItemData()
    {
        if (m_ppItems)
        {
            for (int i = 0; i < m_itemsCapacity; i++)
            {
                if (m_ppItems[i] != nullptr)
                {
                    delete m_ppItems[i];
                    m_ppItems[i] = nullptr;
                }
            }

            Def_Free(m_ppItems);
            m_ppItems = nullptr;
        }
    }

    HRESULT AddInternalStringValue(_In_ int indexInSchema, _In_ int qualifierSetIndex, _In_ PCWSTR pValue, _In_ int typeIndex)
    {
        BuilderItemInfo* pItem;
        RETURN_IF_FAILED(GetOrAddResource(indexInSchema, &pItem));

        _Analysis_assume_(pItem != nullptr);

        // See if we already have a candidate for this qualifier set
        const BUILDER_CANDIDATE* pCandidate = NULL;
        if (pItem->TryFindCandidateForQualifierSet(qualifierSetIndex, &pCandidate))
        {
            // Yes.  If it's identical, just return.  If not, report an error.
            if (CandidateValueMatches(pCandidate, pValue, typeIndex))
            {
                return S_OK;
            }

            return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
        }

        // Not present.  Initialize a candidate for this value.
        BUILDER_CANDIDATE candidate = {};
        candidate.qualifierSetIndex = qualifierSetIndex;
        candidate.indexInDecision = -1;
        RETURN_IF_FAILED(InitDataLocator(m_pMap->m_pDataBuilder, pValue, typeIndex, &candidate.value));

        // Add and return
        return pItem->AddCandidate(candidate, false, false);
    }

    HRESULT
    AddReferenceValue(_In_ int indexInSchema, _In_ int qualifierSetIndex, _In_ IBuildInstanceReference* pReference, _In_ int typeIndex)
    {
        BuilderItemInfo* pItem;
        RETURN_IF_FAILED(GetOrAddResource(indexInSchema, &pItem));

        _Analysis_assume_(pItem != nullptr);

        // see if we already have a candidate for this qualifier set
        const BUILDER_CANDIDATE* pCandidate = NULL;
        if (pItem->TryFindCandidateForQualifierSet(qualifierSetIndex, &pCandidate))
        {
            // Yes.  If it's identical, just return.  If not, report an error.
            if (CandidateValueMatches(pCandidate, pReference, typeIndex))
            {
                //AddReferenceValue takes ownership of the object on successful return.
                //Callers should not use or free pReference if a call to AddReferenceValue succeeds
                delete pReference;
                return S_OK;
            }
            return HRESULT_FROM_WIN32(ERROR_MRM_DUPLICATE_ENTRY);
        }

        MRMFILE_INDEX_INSTANCE instanceValue;
        RETURN_IF_FAILED(pReference->GenerateInstance(&instanceValue));

        // Not present.  Initialize a candidate for this value.
        BUILDER_CANDIDATE candidate = {};
        candidate.qualifierSetIndex = qualifierSetIndex;
        candidate.indexInDecision = -1;
        candidate.value.resourceValueTypeOffset = static_cast<UINT8>(typeIndex);
        candidate.value.valueLocatorType = instanceValue.instanceLocatorTypeOffset;
        candidate.pBuildInstanceReference = pReference;
        // Add and return
        return pItem->AddCandidate(candidate, false, instanceValue.data3 != 0);
    }

    HRESULT AddResourceLink(_In_ int indexInSchema)
    {
        BuilderItemInfo* item;
        RETURN_IF_FAILED(GetOrAddResource(indexInSchema, &item));

        item->SetHasLink();
        return S_OK;
    }

    bool TryFindCandidateForQualifierSet(
        _In_ int itemIndex,
        _In_ int qualifierSetIndex,
        _Outptr_result_maybenull_ const BUILDER_CANDIDATE** ppCandidateOut) const
    {
        *ppCandidateOut = NULL;

        // Item isn't present, so it can't possibly have candidates
        if (itemIndex >= m_szItems)
        {
            return false;
        }
        else if (itemIndex < 0)
        {
            return false;
        }

        if (m_ppItems[itemIndex] == NULL)
        {
            return false;
        }
        return m_ppItems[itemIndex]->TryFindCandidateForQualifierSet(qualifierSetIndex, ppCandidateOut);
    }

    bool CandidateValueMatches(_In_ const BUILDER_CANDIDATE* pCandidate, _In_ PCWSTR pValue, _In_ int typeIndex) const
    {
        if (pCandidate->value.resourceValueTypeOffset != typeIndex)
        {
            return false;
        }

        StringResult existing;
        UINT32 offset = ((pCandidate->value.data2 << 16) | pCandidate->value.data1);
        if (!m_pMap->m_pDataBuilder->TryGetStringData(offset, &existing))
        {
            return false;
        }

        DEFCOMPARISON comp;
        return SUCCEEDED(existing.Compare(pValue, &comp)) && (comp == Def_Equal);
    }

    bool CandidateValueMatches(
        _In_ const BUILDER_CANDIDATE* pCandidate,
        _In_ IBuildInstanceReference* pReference,
        _In_ int typeIndex) const // no validation of typeIndex
    {
        // We disallow different instance types have same values in it: e.g. embedded type cannot have
        // file path candidate like path type
        if (pCandidate->value.resourceValueTypeOffset != typeIndex)
        {
            return false;
        }

        if (pCandidate->pBuildInstanceReference)
        {
            // It assume it will be same candidate when DataItemSection address (section index, file index) and its itemIndex is same.
            // This isn't perfect though since there is chance that same candidate (value) exist even though they come from different data item section,
            // but the chance is very low and it is expensive to detect that here.
            return pReference->IsReferenceEqual(pCandidate->pBuildInstanceReference);
        }

        return false;
    }

    int GetNumItems() const { return m_szItems; }

    BuilderItemInfo* GetItem(_In_ int index) const
    {
        if ((index >= 0) && (index < m_szItems))
        {
            return m_ppItems[index];
        }
        return nullptr;
    }

    HRESULT FinalizeDecisionIndexes()
    {
        DecisionInfoBuilder* pDecisionInfo = m_pMap->GetDecisionInfo();
        AutoDeletePtr<DecisionBuilder> pDecision;
        RETURN_IF_FAILED(DecisionBuilder::CreateInstance(pDecisionInfo, &pDecision));

        for (int iItem = 0; iItem < m_szItems; iItem++)
        {
            BuilderItemInfo* pItem = m_ppItems[iItem];

            if ((pItem != NULL) && (pItem->GetNumCandidates() > 0))
            {
                pDecision->Reset();

                // first build up our decision
                for (int iCandidate = 0; iCandidate < pItem->GetNumCandidates(); iCandidate++)
                {
                    const BUILDER_CANDIDATE* pCandidate = pItem->GetCandidate(iCandidate);
                    if ((m_priBuildType & PriBuildForDeploymentMerge) != 0)
                    {
                        RETURN_IF_FAILED(pDecision->AddQualifierSetForMerge(pCandidate->qualifierSetIndex));
                    }
                    else
                    {
                        RETURN_IF_FAILED(pDecision->AddQualifierSet(pCandidate->qualifierSetIndex));
                    }
                }

                // now get/add the decision to the decision info
                int decisionIndex = -1;
                RETURN_IF_FAILED(pDecisionInfo->GetOrAddDecision(pDecision, &decisionIndex));

                pItem->SetDecisionIndex(decisionIndex);
                RETURN_IF_FAILED(pItem->FinalizeCandidateIndexes(pDecision));
            }
        }
        return S_OK;
    }

    HRESULT
    InitDataLocator(_In_ DataBlobBuilder* pDataBuilder, _In_ PCWSTR pString, _In_ int typeIndex, _Out_ MRMFILE_MAP_VALUE_LARGE* pValueOut)
    {
        // Add our string to the internal data and note the offset
        size_t cbString = (wcslen(pString) + 1) * sizeof(WCHAR);
        UINT32 stringOffset = 0;

        if (cbString > ResourceMapSectionBuilder::MaxInternalDataSize)
        {
            return E_OUTOFMEMORY;
        }

        RETURN_IF_FAILED(pDataBuilder->AddData(reinterpret_cast<const BYTE*>(pString), static_cast<UINT32>(cbString), &stringOffset));

        pValueOut->resourceValueTypeOffset = static_cast<UINT8>(typeIndex);
        pValueOut->valueLocatorType = MRMFILE_MAP_VALUE_LOCATOR_INTERNAL;
        pValueOut->detail = static_cast<UINT16>(cbString);
        pValueOut->data1 = static_cast<UINT16>(stringOffset & 0xffff);
        pValueOut->data2 = static_cast<UINT16>(stringOffset >> 16);
        pValueOut->data3 = 0;
        return S_OK;
    }

private:
    ResourceMapSectionBuilder* m_pMap;

    int m_szItems;
    int m_itemsCapacity;
    _Field_size_part_(m_itemsCapacity, m_szItems) BuilderItemInfo** m_ppItems;
    PriBuildType m_priBuildType;

    MapBuilderItemData(_In_ ResourceMapSectionBuilder* pMap) :
        m_pMap(pMap), m_szItems(0), m_itemsCapacity(0), m_ppItems(nullptr), m_priBuildType(PriBuildType::PriBuildFromScratch)
    {}

    MapBuilderItemData(_In_ ResourceMapSectionBuilder* pMap, _In_ PriBuildType priBuildType) :
        m_pMap(pMap), m_szItems(0), m_itemsCapacity(0), m_ppItems(nullptr), m_priBuildType(priBuildType)
    {}

    HRESULT Extend(_In_ int itemIndex)
    {
        if ((m_szItems > 0) && (itemIndex < m_szItems))
        {
            return S_OK;
        }

        int numSchemaItems = m_pMap->GetSchema()->GetNumItems();
        RETURN_HR_IF(E_INVALIDARG, (itemIndex < 0) || (itemIndex > numSchemaItems - 1));

        if (numSchemaItems <= m_itemsCapacity)
        {
            m_szItems = numSchemaItems;
            return S_OK;
        }

        int newCapacity = (m_itemsCapacity != 0) ? m_itemsCapacity * 2 : 16;
        if (newCapacity < m_itemsCapacity)
        {
            // overflow
            return E_OUTOFMEMORY;
        }

        if (newCapacity < numSchemaItems)
        {
            // should not happen. but just in case.
            newCapacity = numSchemaItems;
        }

        if (!_DefArray_TryEnsureSize(&m_ppItems, ResourceMapSectionBuilder*, m_itemsCapacity, newCapacity))
        {
            return E_OUTOFMEMORY;
        }

        m_itemsCapacity = newCapacity;

        m_szItems = numSchemaItems;
        return S_OK;
    }

    HRESULT GetOrAddResource(_In_ int indexInSchema, _Outptr_result_maybenull_ BuilderItemInfo** ppItemOut)
    {
        *ppItemOut = NULL;

        RETURN_HR_IF(E_INVALIDARG, (indexInSchema < 0) || (indexInSchema > m_pMap->GetSchema()->GetNumItems() - 1));

        if (indexInSchema >= m_szItems)
        {
            RETURN_IF_FAILED(Extend(indexInSchema));
        }

        if (m_ppItems[indexInSchema] == NULL)
        {
            RETURN_IF_FAILED(BuilderItemInfo::CreateInstance(&m_ppItems[indexInSchema]));
        }

        *ppItemOut = m_ppItems[indexInSchema];
        return S_OK;
    }
};

class ResourceMapSectionBuilder::MapBuilderFileData : public DefObject
{
public:
    MapBuilderFileData() :
        m_pHeader(nullptr),
        m_pEnvironmentRefs(nullptr),
        m_pSchemaRef(nullptr),
        m_pResourceValueTypes(nullptr),
        m_pDir(nullptr),
        m_pRanges(nullptr),
        m_pItems(nullptr),
        m_pValues(nullptr),
        m_buildLargeValues(false),
        m_pValuesLarge(nullptr),
        m_pLargeHeader(nullptr),
        m_pLargeDir(nullptr),
        m_pLargeRanges(nullptr),
        m_pLargeItems(nullptr),
        m_pInternalData(nullptr),
        m_cbBeforeData(0),
        m_cbTotal(0)
    {}

    HRESULT Init(
        __out_bcount(cbBuffer) VOID* pBuffer,
        _In_ UINT32 cbBuffer,
        _In_ const MRMFILE_RESOURCE_MAP_HEADER* pHeader,
        _In_ const MRMFILE_RESOURCE_MAP_HEADER_LARGE* pLargeHeader)
    {
        BYTE* pLargeData;
        SectionBuilderParser data;
        RETURN_IF_FAILED(data.Set(pBuffer, cbBuffer));

        m_buildLargeValues = (pHeader->flags & MRMFILE_RESOURCE_MAP_BUILD_LARGE_VALUE);

        HRESULT hr = S_OK;
        m_pHeader = _SECTION_BUILDER_NEXT(data, MRMFILE_RESOURCE_MAP_HEADER, &hr);
        m_pEnvironmentRefs = _SECTION_BUILDER_NEXT_ARRAY(data, pHeader->cbEnvironmentRefs, BYTE, &hr);
        m_pSchemaRef = _SECTION_BUILDER_NEXT_ARRAY(data, pHeader->cbSchemaRef, BYTE, &hr);
        m_pResourceValueTypes = _SECTION_BUILDER_NEXT_ARRAY(data, pHeader->numResourceValueTypes, DEF_ATOM, &hr);
        m_pDir = _SECTION_BUILDER_NEXT_ARRAY(data, pHeader->numDirEntries, MRMFILE_MAP_DIR_ENTRY, &hr);
        m_pRanges = _SECTION_BUILDER_NEXT_ARRAY(data, pHeader->numRanges, MRMFILE_MAP_RANGE, &hr);
        m_pItems = _SECTION_BUILDER_NEXT_ARRAY(data, pHeader->numItems, MRMFILE_MAP_ITEM, &hr);
        pLargeData = _SECTION_BUILDER_NEXT_ARRAY(data, pHeader->cbLargeItemData, BYTE, &hr);
        if (m_buildLargeValues)
        {
            m_pValuesLarge = _SECTION_BUILDER_NEXT_ARRAY(data, pHeader->numValues, MRMFILE_MAP_VALUE_LARGE, &hr);
        }
        else
        {
            m_pValues = _SECTION_BUILDER_NEXT_ARRAY(data, pHeader->numValues, MRMFILE_MAP_VALUE, &hr);
        }

        m_cbBeforeData = data.UsedBufferSizeInBytes();
        m_pInternalData = _SECTION_BUILDER_NEXT_ARRAY(data, pHeader->cbInternalValueData, BYTE, &hr);
        _SECTION_BUILDER_PAD(&data, &hr);
        RETURN_IF_FAILED(hr);

        m_cbTotal = data.UsedBufferSizeInBytes();

        if (pHeader->cbLargeItemData > 0)
        {
            SectionBuilderParser largeData;
            RETURN_IF_FAILED(largeData.Set(pLargeData, pHeader->cbLargeItemData));

            m_pLargeHeader = _SECTION_BUILDER_NEXT(largeData, MRMFILE_RESOURCE_MAP_HEADER_LARGE, &hr);
            m_pLargeDir = _SECTION_BUILDER_NEXT_ARRAY(largeData, pLargeHeader->numDirEntries, MRMFILE_MAP_DIR_ENTRY_LARGE, &hr);
            m_pLargeRanges = _SECTION_BUILDER_NEXT_ARRAY(largeData, pLargeHeader->numRanges, MRMFILE_MAP_RANGE_LARGE, &hr);
            m_pLargeItems = _SECTION_BUILDER_NEXT_ARRAY(largeData, pLargeHeader->numItems, MRMFILE_MAP_ITEM_LARGE, &hr);
            RETURN_IF_FAILED(hr);
        }

        _Analysis_assume_(m_pHeader != nullptr);

        *m_pHeader = *pHeader;

        if (pHeader->cbLargeItemData > 0)
        {
            *m_pLargeHeader = *pLargeHeader;
        }

        return S_OK;
    }

    using DefObject::operator delete;

    ~MapBuilderFileData() {}

    UINT32 NumTotalDirEntries() const { return m_pHeader->numDirEntries + (m_pLargeHeader ? m_pLargeHeader->numDirEntries : 0); }
    UINT32 NumTotalRanges() const { return m_pHeader->numRanges + (m_pLargeHeader ? m_pLargeHeader->numRanges : 0); }
    UINT32 NumTotalItems() const { return m_pHeader->numItems + (m_pLargeHeader ? m_pLargeHeader->numItems : 0); }

    BYTE* GetEnvironmentRefsBlob() const { return m_pEnvironmentRefs; }
    BYTE* GetSchemaRefBlob() const { return m_pSchemaRef; }
    DEF_ATOM* GetResourceValueTypes() const { return m_pResourceValueTypes; }

    BYTE* GetInternalDataBlob(_Out_ UINT32* pcbBlobOut) const
    {
        *pcbBlobOut = m_pHeader->cbInternalValueData;
        return m_pInternalData;
    }

    size_t SizeInBytesExcludingInternalData() const { return m_cbBeforeData; }
    size_t SizeInBytes() const { return m_cbTotal; }

    void WriteRange(_In_ UINT32 rangeIndex, _In_ UINT32 firstItemOffset, _In_ UINT32 numItems)
    {
        DEF_ASSERT(rangeIndex < NumTotalRanges());

        if (rangeIndex < m_pHeader->numRanges)
        {
            DEF_ASSERT((firstItemOffset <= MRMFILE_MAP_MAX_STANDARD_VALUE) && (numItems <= MRMFILE_MAP_MAX_STANDARD_VALUE));
            m_pRanges[rangeIndex].firstItemOffset = static_cast<UINT16>(firstItemOffset);
            m_pRanges[rangeIndex].numItems = static_cast<UINT16>(numItems);
        }
        else
        {
            rangeIndex -= m_pHeader->numRanges;

            m_pLargeRanges[rangeIndex].firstItemOffset = static_cast<UINT32>(firstItemOffset);
            m_pLargeRanges[rangeIndex].numItems = static_cast<UINT32>(numItems);
        }
    }

    void WriteItem(_In_ UINT32 itemIndex, _In_ UINT32 decisionIndex, _In_ UINT32 firstCandidateValueOffset)
    {
        DEF_ASSERT(itemIndex < NumTotalItems());

        if (itemIndex < m_pHeader->numItems)
        {
            DEF_ASSERT((decisionIndex < MRMFILE_MAP_MAX_STANDARD_VALUE));

            m_pItems[itemIndex].decisionIndex = static_cast<UINT16>(decisionIndex);
            m_pItems[itemIndex].firstCandidateValueOffset = static_cast<UINT16>(firstCandidateValueOffset);
        }
        else
        {
            itemIndex -= m_pHeader->numItems;
            m_pLargeItems[itemIndex].decisionIndex = static_cast<UINT16>(decisionIndex);
            m_pLargeItems[itemIndex].pad = 0;
            m_pLargeItems[itemIndex].firstCandidateValueOffset = firstCandidateValueOffset;
        }
    }

    void WriteCandidateValue(_In_ UINT32 candidateIndex, _In_ const MRMFILE_MAP_VALUE* candidateValue)
    {
        DEF_ASSERT(!m_buildLargeValues);
        DEF_ASSERT(candidateIndex < m_pHeader->numValues);

        m_pValues[candidateIndex] = *candidateValue;
    }

    void WriteCandidateValueLarge(_In_ UINT32 candidateIndex, _In_ const MRMFILE_MAP_VALUE_LARGE* candidateValue)
    {
        DEF_ASSERT(m_buildLargeValues);
        DEF_ASSERT(candidateIndex < m_pHeader->numValues);

        m_pValuesLarge[candidateIndex] = *candidateValue;
    }

    void WriteRangeDirEntry(_In_ UINT32 dirEntryIndex, _In_ UINT32 itemIndexInSchema, _In_ UINT32 rangeInfoIndex)
    {
        DEF_ASSERT(dirEntryIndex < NumTotalDirEntries());

        if (dirEntryIndex < m_pHeader->numDirEntries)
        {
            DEF_ASSERT(itemIndexInSchema <= MRMFILE_MAP_MAX_STANDARD_VALUE);
            DEF_ASSERT(rangeInfoIndex <= MRMFILE_MAP_MAX_STANDARD_VALUE);

            m_pDir[dirEntryIndex].itemIndex = static_cast<UINT16>(itemIndexInSchema);
            m_pDir[dirEntryIndex].rangeOrItemOffset = static_cast<UINT16>(rangeInfoIndex);
        }
        else
        {
            dirEntryIndex -= m_pHeader->numDirEntries;
            m_pLargeDir[dirEntryIndex].itemIndex = itemIndexInSchema;
            m_pLargeDir[dirEntryIndex].rangeOrItemOffset = rangeInfoIndex;
        }
    }

    void WriteItemDirEntry(_In_ UINT32 dirEntryIndex, _In_ UINT32 itemIndexInSchema, _In_ UINT32 itemInfoIndex)
    {
        DEF_ASSERT(dirEntryIndex < (m_pHeader->numDirEntries + (m_pLargeHeader ? m_pLargeHeader->numDirEntries : 0)));

        // Items start after ranges
        itemInfoIndex += NumTotalRanges();

        if (dirEntryIndex < m_pHeader->numDirEntries)
        {
            DEF_ASSERT(itemInfoIndex <= MRMFILE_MAP_MAX_STANDARD_VALUE);
            DEF_ASSERT(itemIndexInSchema <= MRMFILE_MAP_MAX_STANDARD_VALUE);

            m_pDir[dirEntryIndex].itemIndex = static_cast<UINT16>(itemIndexInSchema);
            m_pDir[dirEntryIndex].rangeOrItemOffset = static_cast<UINT16>(itemInfoIndex);
        }
        else
        {
            dirEntryIndex -= m_pHeader->numDirEntries;
            m_pLargeDir[dirEntryIndex].itemIndex = itemIndexInSchema;
            m_pLargeDir[dirEntryIndex].rangeOrItemOffset = itemInfoIndex;
        }
    }

protected:
    MRMFILE_RESOURCE_MAP_HEADER* m_pHeader;
    BYTE* m_pEnvironmentRefs;
    BYTE* m_pSchemaRef;
    DEF_ATOM* m_pResourceValueTypes;
    MRMFILE_MAP_DIR_ENTRY* m_pDir;
    MRMFILE_MAP_RANGE* m_pRanges;
    MRMFILE_MAP_ITEM* m_pItems;

    MRMFILE_MAP_VALUE* m_pValues;
    MRMFILE_MAP_VALUE_LARGE* m_pValuesLarge;
    bool m_buildLargeValues;

    MRMFILE_RESOURCE_MAP_HEADER_LARGE* m_pLargeHeader;
    MRMFILE_MAP_DIR_ENTRY_LARGE* m_pLargeDir;
    MRMFILE_MAP_RANGE_LARGE* m_pLargeRanges;
    MRMFILE_MAP_ITEM_LARGE* m_pLargeItems;

    BYTE* m_pInternalData;

    size_t m_cbBeforeData;
    size_t m_cbTotal;
};

HRESULT ResourceMapSectionBuilder::CreateInstance(
    _In_ PriSectionBuilder* pPriBuilder,
    _In_ HierarchicalSchemaSectionBuilder* pSchemaBuilder,
    _In_ DecisionInfoSectionBuilder* pDecisionInfoBuilder,
    _In_ const UnifiedEnvironment* pEnvironment,
    _Outptr_ ResourceMapSectionBuilder** result)
{
    return CreateInstance(pPriBuilder, pSchemaBuilder, pDecisionInfoBuilder, pEnvironment, PriBuildType::PriBuildFromScratch, result);
}

HRESULT ResourceMapSectionBuilder::CreateInstance(
    _In_ PriSectionBuilder* pPriBuilder,
    _In_ HierarchicalSchemaSectionBuilder* pSchemaBuilder,
    _In_ DecisionInfoSectionBuilder* pDecisionInfoBuilder,
    _In_ const UnifiedEnvironment* pEnvironment,
    _In_ PriBuildType priBuildType,
    _Outptr_ ResourceMapSectionBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(
        E_INVALIDARG,
        (pPriBuilder == nullptr) || (pSchemaBuilder == nullptr) || (pDecisionInfoBuilder == nullptr) || (pEnvironment == nullptr));

    AutoDeletePtr<ResourceMapSectionBuilder> pRtrn =
        new ResourceMapSectionBuilder(pPriBuilder, pSchemaBuilder, pDecisionInfoBuilder, pEnvironment, priBuildType);
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init());

    *result = pRtrn.Detach();
    return S_OK;
}

ResourceMapSectionBuilder::ResourceMapSectionBuilder(
    _In_ PriSectionBuilder* pPriBuilder,
    _In_ HierarchicalSchemaSectionBuilder* pSchemaBuilder,
    _In_ DecisionInfoSectionBuilder* pDecisionInfoBuilder,
    _In_ const UnifiedEnvironment* pEnvironment,
    _In_ PriBuildType priBuildType) :
    m_sectionIndex(BaseFile::SectionIndexNone),
    m_finalized(false),
    m_pPriBuilder(pPriBuilder),
    m_pSchema(pSchemaBuilder),
    m_pDecisionInfo(pDecisionInfoBuilder),
    m_pEnvironment(pEnvironment),
    m_links(nullptr),
    m_schemaReferenceBuilder(nullptr),
    m_pDataBuilder(nullptr),
    m_pValueTypes(nullptr),
    m_pItems(nullptr),
    m_pFinalizedDir(nullptr),
    m_numFinalizedValues(0),
    m_hasLargeValues(false),
    m_cbFinalizedSchemaRef(0),
    m_priBuildType(priBuildType)
{}

HRESULT ResourceMapSectionBuilder::Init()
{
    RETURN_IF_FAILED(DataBlobBuilder::CreateInstance(&m_pDataBuilder));

    RETURN_IF_FAILED(m_pEnvironment->GetAllAtoms(UnifiedEnvironment::ResourceValueTypeNames, &m_pValueTypes));

    RETURN_IF_FAILED(MapBuilderItemData::CreateInstance(this, m_priBuildType, &m_pItems));

    return S_OK;
}

ResourceMapSectionBuilder::~ResourceMapSectionBuilder()
{
    delete m_pDataBuilder;
    delete m_pValueTypes;

    m_pDataBuilder = nullptr;
    m_pValueTypes = nullptr;

    if (m_pItems != nullptr)
    {
        for (int iItem = 0; iItem < m_pItems->GetNumItems(); iItem++)
        {
            const BuilderItemInfo* pItem = m_pItems->GetItem(iItem);
            if (pItem != nullptr)
            {
                for (int iCandidate = 0; iCandidate < pItem->GetNumCandidates(); iCandidate++)
                {
                    BUILDER_CANDIDATE* pCandidate = pItem->GetCandidate(iCandidate);

                    if (pCandidate && pCandidate->pBuildInstanceReference)
                    {
                        delete pCandidate->pBuildInstanceReference; // Delete here finally
                        pCandidate->pBuildInstanceReference = nullptr;
                    }
                }
            }
        }

        delete m_pItems;
    }

    delete m_pFinalizedDir;
    delete m_schemaReferenceBuilder;
}

HRESULT ResourceMapSectionBuilder::GetResourceValueTypeAtom(_In_ MrmEnvironment::ResourceValueType valueType, _Out_ Atom* pAtomOut) const
{
    return m_pEnvironment->GetResourceValueTypeAtom(valueType, pAtomOut);
}

HRESULT ResourceMapSectionBuilder::AddCandidateWithInternalString(
    _In_ PCWSTR pItemName,
    _In_ MrmEnvironment::ResourceValueType valueType,
    _In_ PCWSTR pValue,
    _In_opt_ IQualifierSet* pQualifiers)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pItemName));

    pValue = (pValue ? pValue : L"");

    // get the index of our item
    int itemIndex;
    RETURN_IF_FAILED(m_pSchema->GetOrAddItem(pItemName, &itemIndex));

    // get all of our other values
    int typeIndex = -1;
    int qualifierSetIndex = -1;

    RETURN_IF_FAILED(GetOrAddResourceValueTypeIndex(valueType, &typeIndex));
    if (pQualifiers != nullptr)
    {
        RETURN_IF_FAILED(m_pDecisionInfo->GetOrAddQualifierSet(pQualifiers, &qualifierSetIndex));
    }

    if (pQualifiers == NULL)
    {
        qualifierSetIndex = IDecisionInfo::UnconditionalQualifierSetIndex;
    }

    RETURN_IF_FAILED(m_pItems->AddInternalStringValue(itemIndex, qualifierSetIndex, pValue, typeIndex));

    m_finalized = false;
    return S_OK;
}

HRESULT ResourceMapSectionBuilder::AddCandidateWithInternalString(
    _In_ PCWSTR pItemName,
    _In_ MrmEnvironment::ResourceValueType valueType,
    _In_ PCWSTR pValue,
    _In_ int qualifierSetIndex)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pItemName));

    pValue = (pValue ? pValue : L"");

    // get the index of our item
    int itemIndex;
    RETURN_IF_FAILED(m_pSchema->GetOrAddItem(pItemName, &itemIndex));

    // get our other values
    int typeIndex = -1;

    RETURN_IF_FAILED(GetOrAddResourceValueTypeIndex(valueType, &typeIndex));

    RETURN_IF_FAILED(m_pItems->AddInternalStringValue(itemIndex, qualifierSetIndex, pValue, typeIndex));

    m_finalized = false;
    return S_OK;
}

HRESULT ResourceMapSectionBuilder::AddCandidate(
    _In_ PCWSTR pItemName,
    _In_ MrmEnvironment::ResourceValueType valueType,
    _In_ IBuildInstanceReference* pBuildInstanceReference,
    _In_ int qualifierSetIndex)
{
    RETURN_HR_IF(E_INVALIDARG, DefString_IsEmpty(pItemName) || (pBuildInstanceReference == nullptr));

    // get the index of our item
    int itemIndex;
    RETURN_IF_FAILED(m_pSchema->GetOrAddItem(pItemName, &itemIndex));

    return AddCandidate(itemIndex, valueType, pBuildInstanceReference, qualifierSetIndex);
}

HRESULT ResourceMapSectionBuilder::AddCandidate(
    _In_ Atom::Index itemIndex,
    _In_ MrmEnvironment::ResourceValueType valueType,
    _In_ IBuildInstanceReference* pBuildInstanceReference,
    _In_ int qualifierSetIndex)
{
    RETURN_HR_IF(E_INVALIDARG, (itemIndex < 0) || (itemIndex > m_pSchema->GetNumItems() - 1) || (pBuildInstanceReference == nullptr));

    int typeIndex = -1;
    RETURN_IF_FAILED(GetOrAddResourceValueTypeIndex(valueType, &typeIndex));

    m_finalized = false;
    return m_pItems->AddReferenceValue(itemIndex, qualifierSetIndex, pBuildInstanceReference, typeIndex);
}

HRESULT ResourceMapSectionBuilder::InitLinks()
{
    if (m_links == nullptr)
    {
        RETURN_IF_FAILED(m_pPriBuilder->GetOrAddResourceLinkBuilder(this, &m_links));
    }

    return S_OK;
}

HRESULT ResourceMapSectionBuilder::AddResourceLink(_In_ PCWSTR linkFromResourceName, _In_ PCWSTR linkToResourceName)
{
    int linkFromResourceIndex;
    RETURN_IF_FAILED(m_pSchema->GetOrAddItem(linkFromResourceName, &linkFromResourceIndex));

    return AddResourceLink(linkFromResourceIndex, linkToResourceName);
}

HRESULT ResourceMapSectionBuilder::AddResourceLink(_In_ int linkFromResourceIndex, _In_ PCWSTR linkToResourceName)
{
    RETURN_IF_FAILED(InitLinks());
    RETURN_IF_FAILED(m_pItems->AddResourceLink(linkFromResourceIndex));
    RETURN_IF_FAILED(m_links->AddResourceLink(linkFromResourceIndex, linkToResourceName));

    return S_OK;
}

HRESULT ResourceMapSectionBuilder::AddResourceLink(
    _In_ PCWSTR linkFromResourceName,
    _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
    _In_ PCWSTR linkToResourceName)
{
    int linkFromResourceIndex;
    RETURN_IF_FAILED(m_pSchema->GetOrAddItem(linkFromResourceName, &linkFromResourceIndex));

    return AddResourceLink(linkFromResourceIndex, linkToSchema, linkToResourceName);
}

HRESULT ResourceMapSectionBuilder::AddResourceLink(
    _In_ int linkFromResourceIndex,
    _In_ const HierarchicalSchemaSectionBuilder* linkToSchema,
    _In_ PCWSTR linkToResourceName)
{
    RETURN_IF_FAILED(InitLinks());
    RETURN_IF_FAILED(m_pItems->AddResourceLink(linkFromResourceIndex));
    RETURN_IF_FAILED(m_links->AddResourceLink(linkFromResourceIndex, linkToSchema, linkToResourceName));

    return S_OK;
}

int ResourceMapSectionBuilder::GetTotalNumFinalizedValues() const
{
    if (m_finalized)
    {
        return m_numFinalizedValues;
    }
    return -1;
}

bool ResourceMapSectionBuilder::TryGetResourceInfo(
    _In_ int indexInSchema,
    __inout_opt StringResult* pNameOut,
    _Out_opt_ int* pNumCandidatesOut) const
{
    if ((indexInSchema < 0) || (indexInSchema > m_pSchema->GetNumItems() - 1))
    {
        return false;
    }

    if (pNumCandidatesOut != NULL)
    {
        const BuilderItemInfo* pItem = m_pItems->GetItem(indexInSchema);
        if (pItem != NULL)
        {
            *pNumCandidatesOut = pItem->GetNumCandidates();
        }
        else
        {
            *pNumCandidatesOut = 0;
        }
    }

    if (pNameOut != NULL)
    {
        if (!m_pSchema->TryGetItemInfo(indexInSchema, pNameOut))
        {
            return false;
        }
    }

    return true;
}

bool ResourceMapSectionBuilder::TryGetResourceInfo(_In_ PCWSTR pResourceName, _Out_opt_ int* pIndexOut, _Out_opt_ int* pNumCandidatesOut)
    const
{
    int index = -1;

    if (!m_pSchema->ContainsItem(pResourceName, &index))
    {
        return false;
    }

    if (pIndexOut != NULL)
    {
        *pIndexOut = index;
    }

    if (pNumCandidatesOut != NULL)
    {
        const BuilderItemInfo* pItem = m_pItems->GetItem(index);
        *pNumCandidatesOut = ((pItem != NULL) ? pItem->GetNumCandidates() : 0);
    }
    return true;
}

bool ResourceMapSectionBuilder::TryGetCandidateInfo(
    _In_ int itemIndex,
    _In_ int candidateIndex,
    _Inout_opt_ QualifierSetResult* pQualifierSetOut,
    _Out_opt_ MrmEnvironment::ResourceValueType* pTypeOut,
    _Inout_opt_ StringResult* pValueOut) const
{
    if ((itemIndex < 0) || (itemIndex > m_pItems->GetNumItems() - 1))
    {
        return false;
    }

    const BuilderItemInfo* pItem = m_pItems->GetItem(itemIndex);
    if ((pItem == nullptr) || (candidateIndex < 0) || (candidateIndex > pItem->GetNumCandidates() - 1))
    {
        return false;
    }

    const BUILDER_CANDIDATE* pCandidate = pItem->GetCandidate(candidateIndex);

    // pCandidate should never be null due to range check above.
    DEF_ASSERT(pCandidate != nullptr);

    if (pQualifierSetOut != nullptr)
    {
        if (FAILED(m_pDecisionInfo->GetQualifierSet(pCandidate->qualifierSetIndex, pQualifierSetOut)))
        {
            return false;
        }
    }

    Atom typeAtom;
    if (!m_pValueTypes->TryGet(pCandidate->value.resourceValueTypeOffset, &typeAtom))
    {
        return false;
    }

    MrmEnvironment::ResourceValueType resourceType = MrmEnvironment::GetResourceValueTypeForAtom(typeAtom);

    if (pTypeOut != nullptr)
    {
        *pTypeOut = resourceType;
    }

    if (pValueOut != nullptr)
    {
        BlobResult blob;
        switch (pCandidate->value.valueLocatorType)
        {
        case MRMFILE_MAP_VALUE_LOCATOR_INTERNAL:
        {
            UINT32 offset = ((pCandidate->value.data2 << 16) | pCandidate->value.data1);
            if (!m_pDataBuilder->TryGetBlobData(offset, pCandidate->value.detail, &blob) ||
                FAILED(GetStringResultFromBlobResult(&blob, MrmEnvironment::MapResourceValueTypeToEncoding(resourceType), pValueOut)))
            {
                return false;
            }
            break;
        }
        case MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM:
            DEF_ASSERT(pCandidate->pBuildInstanceReference != nullptr);
            // Set the reference since it is called during Build time while ResourceMapSectionBuilder is alive (not yet Finalized)
            if (FAILED(pCandidate->pBuildInstanceReference->GetDataBlob(&blob)) ||
                FAILED(GetStringResultFromBlobResult(&blob, MrmEnvironment::MapResourceValueTypeToEncoding(resourceType), pValueOut)))
            {
                return false;
            }

            break;
        case MRMFILE_MAP_VALUE_LOCATOR_FILE_ITEM:
        default:
            // This method is part of prototype that won't be checked in in-place merge support
            return false;
        }
    }

    return true;
}

bool ResourceMapSectionBuilder::TryGetCandidateInfo(
    _In_ PCWSTR pItemName,
    _In_ int candidateIndex,
    _Inout_opt_ QualifierSetResult* pQualifierSetOut,
    _Out_opt_ MrmEnvironment::ResourceValueType* pTypeOut,
    _Inout_opt_ StringResult* pValueOut,
    _Out_opt_ int* pItemIndexOut) const
{
    int itemIndex = -1;

    if (!m_pSchema->ContainsItem(pItemName, &itemIndex))
    {
        return false;
    }

    if (pItemIndexOut != NULL)
    {
        *pItemIndexOut = itemIndex;
    }
    return TryGetCandidateInfo(itemIndex, candidateIndex, pQualifierSetOut, pTypeOut, pValueOut);
}

bool ResourceMapSectionBuilder::TryGetCandidateInfo(
    _In_ PCWSTR pItemName,
    _In_ int candidateIndex,
    _Inout_ BuilderCandidateResult* pBuilderCandidateResult) const
{
    int itemIndex = -1;

    if (!m_pSchema->ContainsItem(pItemName, &itemIndex))
    {
        return false;
    }

    const BuilderItemInfo* pItem = m_pItems->GetItem(itemIndex);
    if ((pItem == NULL) || (candidateIndex < 0) || (candidateIndex > pItem->GetNumCandidates() - 1))
    {
        return false;
    }

    const BUILDER_CANDIDATE* pCandidate = pItem->GetCandidate(candidateIndex);

    if (pCandidate->value.valueLocatorType != MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM)
    {

        return false;
    }

    Atom instanceValueType;
    if (!m_pValueTypes->TryGet(pCandidate->value.resourceValueTypeOffset, &instanceValueType))
    {
        return false;
    }

    pBuilderCandidateResult->Set(pCandidate, m_pDecisionInfo, instanceValueType);
    return true;
}

HRESULT
ResourceMapSectionBuilder::GetOrAddResourceValueTypeIndex(_In_ MrmEnvironment::ResourceValueType typeIndexIn, _Out_ int* pFileIndexOut)
{
    Atom typeAtom;
    RETURN_IF_FAILED(m_pEnvironment->GetResourceValueTypeAtom(typeIndexIn, &typeAtom, nullptr));

    for (int i = 0; i < m_pValueTypes->Count(); i++)
    {
        Atom haveAtom;
        if (m_pValueTypes->TryGet(i, &haveAtom) && haveAtom.IsEqual(typeAtom))
        {
            *pFileIndexOut = i;
            return S_OK;
        }
    }

    if (!m_pEnvironment->IsValidAtom(UnifiedEnvironment::ResourceValueTypeNames, typeAtom))
    {
        return E_ABORT;
    }

    m_finalized = false;
    return m_pValueTypes->Add(typeAtom, pFileIndexOut);
}

bool ResourceMapSectionBuilder::IsValid() const { return true; }

HRESULT ResourceMapSectionBuilder::Finalize()
{
    if (m_finalized)
    {
        return S_OK;
    }

    RETURN_IF_FAILED(m_pItems->FinalizeDecisionIndexes());

    if (m_links != nullptr)
    {
        RETURN_IF_FAILED(m_links->Finalize());
    }

    delete m_pFinalizedDir;

    if (m_pPriBuilder->GetBuildConfiguration()->UseFileGlobalEnvironment())
    {
        m_cbFinalizedEnvironmentRefs = 0;
    }
    else
    {
        m_cbFinalizedEnvironmentRefs = m_pEnvironment->GetNumEnvironments() * sizeof(MRMFILE_ENVIRONMENT_REF);
    }

    RETURN_IF_FAILED(DynamicArray<BuilderDirEntry>::CreateInstance(8, &m_pFinalizedDir));
    m_numFinalizedStandardDirEntries = m_numFinalizedLargeDirEntries = 0;
    m_numFinalizedTotalRanges = m_numFinalizedStandardRanges = m_numFinalizedLargeRanges = 0;
    m_numFinalizedTotalItems = m_numFinalizedStandardItems = m_numFinalizedLargeItems = 0;
    m_numFinalizedValues = 0;

    int firstLargeDirEntry = -1;
    int firstLargeRange = -1;
    int firstLargeItem = -1;

    int currentRangeStart = -1;
    int currentRangeEnd = -1;
    int currentRangeFirstValue = -1;

    bool buildingLargeEntries = false;

    for (int iItem = 0; iItem < m_pItems->GetNumItems(); iItem++)
    {
        const BuilderItemInfo* pItem = m_pItems->GetItem(iItem);

        // If the item is a link we'll fill in the candidates later.
        if ((pItem == nullptr) || ((pItem->GetNumCandidates() < 1) && (!pItem->GetHasLink())))
        {
            continue;
        }

        if (pItem->GetHasLink() && (pItem->GetNumCandidates() > 0))
        {
            int linksToSchemaIndex;
            int linksToResourceIndex;

            if (!m_links->TryGetResourceLinkByResourceIndex(iItem, &linksToSchemaIndex, &linksToResourceIndex))
            {
                return E_ABORT;
            }

            if (linksToSchemaIndex != 0)
            {
                // external links not supported yet
                return E_NOTIMPL;
            }

            const BuilderItemInfo* linksToResource = m_pItems->GetItem(linksToResourceIndex);
            if (linksToResource == nullptr)
            {
                return E_ABORT;
            }

            RETURN_IF_FAILED(pItem->VerifyLinkedResourceIsCompatible(linksToResource));
        }

        bool isLargeEntry =
            (buildingLargeEntries || (iItem > MRMFILE_MAP_MAX_STANDARD_VALUE) ||
             ((!pItem->GetHasLink()) && ((m_numFinalizedValues + pItem->GetNumCandidates()) > MRMFILE_MAP_MAX_STANDARD_VALUE)));

        // Now update our item directory
        if (currentRangeStart < 0)
        {
            // First item we've seen
            currentRangeStart = iItem;
            currentRangeEnd = iItem;
            currentRangeFirstValue = m_numFinalizedValues;
        }
        else if (((iItem - currentRangeEnd) < 3) && (buildingLargeEntries == isLargeEntry))
        {
            // Small gaps in a range are okay
            currentRangeEnd = iItem;
        }
        else
        {
            // Gap is too big.  Emit the current range or item and start a new one
            BuilderDirEntry entry;

            entry.itemIndexInSchema = currentRangeStart;
            entry.itemInfoIndex = m_numFinalizedTotalItems;
            entry.length = (currentRangeEnd - currentRangeStart + 1);
            entry.rangeInfoIndex = ((entry.length > 1) ? m_numFinalizedTotalRanges++ : -1);
            entry.firstValueIndex = currentRangeFirstValue;

            m_numFinalizedTotalItems += entry.length;

            RETURN_IF_FAILED(m_pFinalizedDir->Add(entry));

            // Start a new range
            currentRangeStart = iItem;
            currentRangeEnd = iItem;
            currentRangeFirstValue = m_numFinalizedValues;

            if (isLargeEntry && (!buildingLargeEntries))
            {
                buildingLargeEntries = true;
                firstLargeDirEntry = m_pFinalizedDir->Count();
                firstLargeRange = m_numFinalizedTotalRanges;
                firstLargeItem = m_numFinalizedTotalItems;
            }
        }

        // Track the number of candidates we'll be emitting
        if (!pItem->GetHasLink())
        {
            m_numFinalizedValues += pItem->GetNumCandidates();
            if (!m_hasLargeValues)
            {
                m_hasLargeValues = pItem->GetHasLargeCandidates();
            }
        }
    }

    // emit the final range/item
    if (currentRangeStart >= 0)
    {
        BuilderDirEntry entry;

        entry.itemIndexInSchema = currentRangeStart;
        entry.itemInfoIndex = m_numFinalizedTotalItems;
        entry.length = (currentRangeEnd - currentRangeStart + 1);
        entry.rangeInfoIndex = ((entry.length > 1) ? m_numFinalizedTotalRanges++ : -1);
        entry.firstValueIndex = currentRangeFirstValue;

        m_numFinalizedTotalItems += entry.length;

        RETURN_IF_FAILED(m_pFinalizedDir->Add(entry));
    }

    if (firstLargeDirEntry >= 0)
    {
        m_numFinalizedStandardDirEntries = firstLargeDirEntry;
        m_numFinalizedStandardRanges = firstLargeRange;
        m_numFinalizedStandardItems = firstLargeItem;
    }
    else
    {
        m_numFinalizedStandardDirEntries = m_pFinalizedDir->Count();
        m_numFinalizedStandardRanges = m_numFinalizedTotalRanges;
        m_numFinalizedStandardItems = m_numFinalizedTotalItems;
    }

    m_numFinalizedLargeDirEntries = (m_pFinalizedDir->Count() - m_numFinalizedStandardDirEntries);
    m_numFinalizedLargeRanges = (m_numFinalizedTotalRanges - m_numFinalizedStandardRanges);
    m_numFinalizedLargeItems = (m_numFinalizedTotalItems - m_numFinalizedStandardItems);

    if (m_numFinalizedLargeDirEntries > 0 || m_numFinalizedLargeRanges > 0 || m_numFinalizedLargeItems > 0)
    {
        m_cbFinalizedLargeData =
            sizeof(MRMFILE_RESOURCE_MAP_HEADER_LARGE) + (m_numFinalizedLargeDirEntries * sizeof(MRMFILE_MAP_DIR_ENTRY_LARGE)) +
            (m_numFinalizedLargeRanges * sizeof(MRMFILE_MAP_RANGE_LARGE)) + (m_numFinalizedLargeItems * sizeof(MRMFILE_MAP_ITEM_LARGE));
    }
    else
    {
        m_cbFinalizedLargeData = 0;
    }

    if (m_pPriBuilder->GetBuildConfiguration()->UseSchemaReference())
    {

        if (m_schemaReferenceBuilder != nullptr)
        {

            delete m_schemaReferenceBuilder;
            m_schemaReferenceBuilder = nullptr;
        }

        RETURN_IF_FAILED(HierarchicalSchemaReferenceSectionBuilder::CreateInstance(m_pSchema, &m_schemaReferenceBuilder));

        m_cbFinalizedSchemaRef = m_schemaReferenceBuilder->GetMaxSizeInBytes();
    }

    m_finalized = true;

    return S_OK;
}

UINT32 ResourceMapSectionBuilder::GetMaxSizeInBytes() const
{
    if (!m_finalized)
    {
        return 0;
    }

    UINT32 cbTotal = sizeof(MRMFILE_RESOURCE_MAP_HEADER) + m_cbFinalizedEnvironmentRefs + m_cbFinalizedSchemaRef +
                     (m_pValueTypes->Count() * sizeof(DEF_ATOM)) + (m_numFinalizedStandardDirEntries * sizeof(MRMFILE_MAP_DIR_ENTRY)) +
                     (m_numFinalizedStandardRanges * sizeof(MRMFILE_MAP_RANGE)) + (m_numFinalizedStandardItems * sizeof(MRMFILE_MAP_ITEM)) +
                     (m_numFinalizedValues * (m_hasLargeValues ? sizeof(MRMFILE_MAP_VALUE_LARGE) : sizeof(MRMFILE_MAP_VALUE))) +
                     m_cbFinalizedLargeData + m_pDataBuilder->GetMaxSizeInBytesOfDataBlob();
    cbTotal = _DEFFILE_PAD_SECTION(cbTotal);
    return cbTotal;
}

DEFFILE_SECTION_TYPEID
ResourceMapSectionBuilder::GetSectionType() const
{
    return (m_pPriBuilder->GetBuildConfiguration()->UseFileGlobalEnvironment() ? gResourceMap2SectionType : gResourceMapSectionType);
}

HRESULT
ResourceMapSectionBuilder::Build(
    _Out_writes_bytes_(bufferSizeInBytes) VOID* buffer,
    _In_ UINT32 bufferSizeInBytes,
    _Out_opt_ UINT32* numBytesWritten) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, buffer);
    RETURN_HR_IF(E_DEF_NOT_READY, !m_finalized);

    if (numBytesWritten != nullptr)
    {
        *numBytesWritten = 0;
    }

    MRMFILE_RESOURCE_MAP_HEADER header;
    MRMFILE_RESOURCE_MAP_HEADER_LARGE largeHeader;

    header.cbEnvironmentRefs = static_cast<UINT16>(m_cbFinalizedEnvironmentRefs);
    header.numEnvironmentRefs = static_cast<UINT16>((m_cbFinalizedEnvironmentRefs > 0) ? m_pEnvironment->GetNumEnvironments() : 0);
    header.schemaSectionIndex = m_pSchema->GetSectionIndex();
    header.cbSchemaRef = static_cast<UINT16>(m_cbFinalizedSchemaRef);
    header.decisionInfoSectionIndex = m_pDecisionInfo->GetSectionIndex();
    header.numResourceValueTypes = static_cast<UINT16>(m_pValueTypes->Count());
    header.numDirEntries = static_cast<UINT16>(m_numFinalizedStandardDirEntries);
    header.numRanges = static_cast<UINT16>(m_numFinalizedStandardRanges);
    header.numItems = static_cast<UINT16>(m_numFinalizedStandardItems);
    header.flags = (m_hasLargeValues ? MRMFILE_RESOURCE_MAP_BUILD_LARGE_VALUE : 0);
    header.numValues = static_cast<UINT32>(m_numFinalizedValues);
    header.cbInternalValueData = m_pDataBuilder->GetMaxSizeInBytesOfDataBlob();
    header.cbLargeItemData = m_cbFinalizedLargeData;

    largeHeader.numDirEntries = m_numFinalizedLargeDirEntries;
    largeHeader.numRanges = m_numFinalizedLargeRanges;
    largeHeader.numItems = m_numFinalizedLargeItems;

    MapBuilderFileData data;
    RETURN_IF_FAILED(data.Init(buffer, bufferSizeInBytes, &header, &largeHeader));

    // Environment references
    if (m_cbFinalizedEnvironmentRefs > 0)
    {
        size_t envNumBytesWritten = 0;
        BYTE* environmentRefs = data.GetEnvironmentRefsBlob();

        for (int i = 0; i < m_pEnvironment->GetNumEnvironments(); i++)
        {
            const IEnvironment* environment;
            (void)m_pEnvironment->GetEnvironment(i, &environment);
            if (environment != nullptr)
            {
                AutoDeletePtr<EnvironmentReferenceBuilder> builder;
                RETURN_IF_FAILED(EnvironmentReferenceBuilder::CreateInstance(environment, &builder));

                size_t thisEnvNumBytesWritten = 0;
                RETURN_IF_FAILED(builder->Build(
                    &environmentRefs[envNumBytesWritten], m_cbFinalizedEnvironmentRefs - envNumBytesWritten, &thisEnvNumBytesWritten));

                envNumBytesWritten += thisEnvNumBytesWritten;
            }
        }
    }

    // Schema references
    if (m_cbFinalizedSchemaRef > 0)
    {
        UINT schemaRefNumBytesWritten;
        BYTE* schemaRef = data.GetSchemaRefBlob();
        RETURN_IF_FAILED(m_schemaReferenceBuilder->Build(schemaRef, m_cbFinalizedSchemaRef, &schemaRefNumBytesWritten));
    }

    // Resource value type names
    DEF_ATOM* resourceValueTypes = data.GetResourceValueTypes();
    for (int i = 0; i < m_pValueTypes->Count(); i++)
    {
        Atom name;
        if (!m_pValueTypes->TryGet(i, &name))
        {
            return E_ABORT;
        }
        resourceValueTypes[i] = name.GetAtom();
    }

    // Directory
    for (int iDir = 0; iDir < m_pFinalizedDir->Count(); iDir++)
    {
        BuilderDirEntry dir;
        if (!m_pFinalizedDir->TryGet(iDir, &dir))
        {
            return E_ABORT;
        }

        if (dir.length > 1)
        {
            // need to write a range
            data.WriteRange(dir.rangeInfoIndex, dir.itemInfoIndex, dir.length);
            data.WriteRangeDirEntry(iDir, dir.itemIndexInSchema, dir.rangeInfoIndex);
        }
        else
        {
            // write a single item.
            data.WriteItemDirEntry(iDir, dir.itemIndexInSchema, dir.itemInfoIndex);
        }

        // Now write the items and values
        int nextValueIndex = dir.firstValueIndex;
        for (int iItem = 0; iItem < dir.length; iItem++)
        {
            BuilderItemInfo* item = m_pItems->GetItem(dir.itemIndexInSchema + iItem);

            if ((item == nullptr) || (item->GetNumCandidates() < 1) || item->GetHasLink())
            {
                int index;
                m_pDecisionInfo->GetEmptyDecisionIndex(&index);

                // no candidates, just write an empty item
                data.WriteItem(dir.itemInfoIndex + iItem, index, 0);

                if (item != nullptr)
                {
                    item->SetBuiltItemInfo(dir.itemInfoIndex + iItem, 0);
                }
            }
            else
            {
                DEF_ASSERT(item->GetDecisionIndex() > 0);

                // write the item itself
                data.WriteItem(dir.itemInfoIndex + iItem, item->GetDecisionIndex(), nextValueIndex);

                // keep track of what we wrote
                item->SetBuiltItemInfo(dir.itemInfoIndex + iItem, nextValueIndex);

                // now write the values
                for (int iCandidate = 0; iCandidate < item->GetNumCandidates(); iCandidate++)
                {
                    BUILDER_CANDIDATE* candidate = item->GetCandidate(iCandidate);
                    DEF_ASSERT(candidate != nullptr);

                    if (candidate->pBuildInstanceReference != nullptr)
                    {
                        MRMFILE_INDEX_INSTANCE instanceValue;
                        RETURN_IF_FAILED(candidate->pBuildInstanceReference->GenerateInstance(&instanceValue));

                        // Not present.  Initialize a candidate for this value.
                        DEF_ASSERT(instanceValue.detail != -1);
                        candidate->value.detail = instanceValue.detail;
                        candidate->value.data1 = instanceValue.data1;
                        candidate->value.data2 = instanceValue.data2;
                        candidate->value.data3 = instanceValue.data3;

                        delete candidate->pBuildInstanceReference; // Delete here finally
                        candidate->pBuildInstanceReference = nullptr;
                    }

                    if (m_hasLargeValues)
                    {
                        data.WriteCandidateValueLarge(nextValueIndex + candidate->indexInDecision, &candidate->value);
                    }
                    else
                    {
                        data.WriteCandidateValue(
                            nextValueIndex + candidate->indexInDecision, reinterpret_cast<MRMFILE_MAP_VALUE*>(&candidate->value));
                    }
                }
                nextValueIndex += static_cast<UINT16>(item->GetNumCandidates());
            }
        }
    }

    if (m_links != nullptr)
    {
        // Now fix up any links
        for (int iDir = 0; iDir < m_pFinalizedDir->Count(); iDir++)
        {
            BuilderDirEntry dir;
            if (!m_pFinalizedDir->TryGet(iDir, &dir))
            {
                return E_ABORT;
            }

            for (int iItem = 0; iItem < dir.length; iItem++)
            {
                const BuilderItemInfo* item = m_pItems->GetItem(dir.itemIndexInSchema + iItem);

                if ((item != nullptr) && item->GetHasLink())
                {
                    int linksToSchemaIndex;
                    int linksToResourceIndex;

                    if (m_links->TryGetResourceLinkByResourceIndex(iItem, &linksToSchemaIndex, &linksToResourceIndex))
                    {
                        if (linksToSchemaIndex != 0)
                        {
                            return E_NOTIMPL;
                        }

                        const BuilderItemInfo* linksTo = m_pItems->GetItem(linksToResourceIndex);
                        if (linksTo != nullptr)
                        {
                            if (linksTo->GetHasLink())
                            {
                                return E_DEFFILE_BUILD_LINK_TO_LINKED_RESOURCE;
                            }

                            data.WriteItem(item->GetBuiltItemEntryIndex(), linksTo->GetDecisionIndex(), linksTo->GetBuiltFirstValueIndex());
                        }
                        // else the resource we link to has no candidates, so nothing to do.
                    }
                    else
                    {
                        return E_ABORT;
                    }
                }
            }
        }
    }

    UINT32 internalDataSizeInBytes = 0;
    BYTE* internalData = data.GetInternalDataBlob(&internalDataSizeInBytes);
    UINT32 internalDataBytesWritten = 0;

    RETURN_IF_FAILED(m_pDataBuilder->BuildDataBlob(internalData, internalDataSizeInBytes, &internalDataBytesWritten));

    DEF_ASSERT(_DEFFILE_PAD_SECTION(data.SizeInBytesExcludingInternalData() + internalDataBytesWritten) <= data.SizeInBytes());

    if (numBytesWritten != nullptr)
    {
        *numBytesWritten = static_cast<UINT32>(_DEFFILE_PAD_SECTION(data.SizeInBytesExcludingInternalData() + internalDataBytesWritten));
    }
    return S_OK;
}

} // namespace Microsoft::Resources::Build