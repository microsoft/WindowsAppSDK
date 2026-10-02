// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources::Build
{

HRESULT DataItemOrchestrator::CreateInstance(
    _In_ FileBuilder* fileBuilder,
    _In_ CoreProfile* profile,
    _In_ DecisionInfoSectionBuilder* decisionInfo,
    _Outptr_ DataItemOrchestrator** result)
{
    *result = nullptr;

    AutoDeletePtr<DataItemOrchestrator> rtrn = new DataItemOrchestrator(fileBuilder, profile, decisionInfo);
    RETURN_IF_NULL_ALLOC(rtrn);
    RETURN_IF_FAILED(rtrn->Init());

    *result = rtrn.Detach();
    return S_OK;
}

DataItemOrchestrator::DataItemOrchestrator(
    _In_ FileBuilder* fileBuilder,
    _In_ CoreProfile* profile,
    _In_ DecisionInfoSectionBuilder* decisionInfo) :
    m_finalized(false),
    m_profile(profile),
    m_fileBuilder(fileBuilder),
    m_decisionInfo(decisionInfo),
    m_allBuilders(nullptr),
    m_buildersByQualifierSet(nullptr),
    m_buildConfiguration(profile->GetBuildConfiguration()),
    m_OrchestratorHashMap(nullptr)
{}

HRESULT DataItemOrchestrator::Init()
{
    RETURN_IF_FAILED(DynamicArray<DataItemsSectionBuilder*>::CreateInstance(10, &m_allBuilders));
    RETURN_IF_FAILED(DynamicArray<DataItemsSectionBuilder*>::CreateInstance(10, &m_buildersByQualifierSet));
    RETURN_IF_FAILED(OrchestratorHashMap::CreateInstance(1019, 0.75, &m_OrchestratorHashMap));

    return S_OK;
}

DataItemOrchestrator::~DataItemOrchestrator()
{
    if (m_allBuilders != nullptr)
    {
        for (int i = 0; i < m_allBuilders->Count(); i++)
        {
            DataItemsSectionBuilder* builder;
            if (SUCCEEDED(m_allBuilders->Get(i, &builder)))
            {
                delete builder;
            }
        }
        delete m_allBuilders;
    }

    delete m_buildersByQualifierSet;
    delete m_OrchestratorHashMap;
}

HRESULT DataItemOrchestrator::Finalize()
{
    RETURN_HR_IF(E_DEF_ALREADY_INITIALIZED, m_finalized);

    for (int i = 0; i < m_allBuilders->Count(); i++)
    {
        DataItemsSectionBuilder* builder;
        if (SUCCEEDED(m_allBuilders->Get(i, &builder)))
        {
            RETURN_IF_FAILED(builder->Finalize());
        }
    }

    m_finalized = true;

    return S_OK;
}

int DataItemOrchestrator::GetNumFinalizedDataItemSections() const { return (m_finalized ? m_allBuilders->Count() : 0); }

HRESULT DataItemOrchestrator::GetFinalizedDataItemSection(_In_ int index, _Out_ DataItemsSectionBuilder** result) const
{
    *result = nullptr;
    RETURN_HR_IF(E_DEF_NOT_READY, !m_finalized);

    return m_allBuilders->Get(index, result);
}

HRESULT DataItemOrchestrator::GetOrAddDataItemSectionBuilder(_In_ int qualifierSetIndex, _Out_ DataItemsSectionBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_DEF_ALREADY_INITIALIZED, m_finalized);

    // Return data section builder. Respective qualifier set has its own data section that will improve
    // data localility during Runtime search.

    DataItemsSectionBuilder* builder = nullptr;
    (void)m_buildersByQualifierSet->Get(qualifierSetIndex, &builder);
    if (builder == nullptr)
    {
        AutoDeletePtr<DataItemsSectionBuilder> autoBuilder;
        RETURN_IF_FAILED(DataItemsSectionBuilder::CreateInstance(&autoBuilder));
        RETURN_IF_FAILED(m_fileBuilder->AddSection(autoBuilder));
        RETURN_IF_FAILED(m_allBuilders->Add(autoBuilder));

        builder = autoBuilder.Detach();
        if (m_buildersByQualifierSet->Count() <= qualifierSetIndex)
        {
            RETURN_IF_FAILED(m_buildersByQualifierSet->SetExtent(qualifierSetIndex + 1));
        }

        RETURN_IF_FAILED(m_buildersByQualifierSet->Set(qualifierSetIndex, builder));
    }

    *result = builder;
    return S_OK;
}

HRESULT DataItemOrchestrator::AddDataAndCreateInstanceReference(
    _In_reads_bytes_(valueSizeInBytes) const void* value,
    _In_ UINT valueSizeInBytes,
    _In_ int qualifierSetIndex,
    _Outptr_ IBuildInstanceReference** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_DEF_ALREADY_INITIALIZED, m_finalized);

    IBuildInstanceReference* buildInstanceReference = nullptr;
    DataItemsSectionBuilder::PrebuildItemReference preBuildReference = {};

    if (m_buildConfiguration->UseDeduplication())
    {
        DEF_CHECKSUM defCheckSum = DefChecksum::ComputeChecksum(0, (const BYTE*)value, valueSizeInBytes);

        OrchestratorDataReference* dataRefereceFromMap = m_OrchestratorHashMap->TryGetFromMap(defCheckSum, value, valueSizeInBytes);

        if (dataRefereceFromMap == nullptr)
        {
            DataItemsSectionBuilder* dataItemSectionBuilder;
            RETURN_IF_FAILED(GetOrAddDataItemSectionBuilder(qualifierSetIndex, &dataItemSectionBuilder));

            RETURN_IF_FAILED(dataItemSectionBuilder->AddDataItem(value, valueSizeInBytes, &preBuildReference));

            AutoDeletePtr<OrchestratorDataReference> autoBuildInstanceReference;
            RETURN_IF_FAILED(OrchestratorDataReference::CreateInstance(
                defCheckSum, value, valueSizeInBytes, dataItemSectionBuilder, &preBuildReference, &autoBuildInstanceReference));

            RETURN_IF_FAILED(m_OrchestratorHashMap->AddtoMap(defCheckSum, autoBuildInstanceReference));

            buildInstanceReference = autoBuildInstanceReference.Detach();
        }
        else //duplication found
        {
            RETURN_IF_FAILED(
                OrchestratorDataReference::CloneDataReference(dataRefereceFromMap, (OrchestratorDataReference**)&buildInstanceReference));
        }
    }
    else
    {
        DataItemsSectionBuilder* dataItemSectionBuilder;
        RETURN_IF_FAILED(GetOrAddDataItemSectionBuilder(qualifierSetIndex, &dataItemSectionBuilder));

        RETURN_IF_FAILED(dataItemSectionBuilder->AddDataItem(value, valueSizeInBytes, &preBuildReference));

        RETURN_IF_FAILED(DataItemsBuildInstanceReference::CreateInstance(
            dataItemSectionBuilder, &preBuildReference, (DataItemsBuildInstanceReference**)&buildInstanceReference));
        RETURN_IF_NULL_ALLOC(buildInstanceReference);
    }
    *result = buildInstanceReference;
    return S_OK;
}

HRESULT DataItemOrchestrator::AddDataAndCreateInstanceReference(
    _In_reads_bytes_(valueSizeInBytes) const void* value,
    _In_ UINT valueSizeInBytes,
    _In_ const IQualifierSet* qualifiers,
    _Outptr_ IBuildInstanceReference** result,
    _Out_ int* qualifierIndex)
{
    *result = nullptr;
    int qualifierSetIndex;
    RETURN_IF_FAILED(m_decisionInfo->GetOrAddQualifierSet(qualifiers, &qualifierSetIndex));

    *qualifierIndex = qualifierSetIndex;

    return AddDataAndCreateInstanceReference(value, valueSizeInBytes, *qualifierIndex, result);
}

HRESULT DataItemOrchestrator::AddStringAndCreateInstanceReference(
    _In_ PCWSTR value,
    _In_ int qualifierSetIndex,
    _Outptr_ IBuildInstanceReference** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_DEF_ALREADY_INITIALIZED, m_finalized);

    IBuildInstanceReference* buildInstanceReference = nullptr;
    DataItemsSectionBuilder::PrebuildItemReference preBuildReference = {};

    size_t valueLength;
    RETURN_IF_FAILED(GetValueSize(value, &valueLength)); // Use safe calculations to get the value length.

    if (m_buildConfiguration->UseDeduplication())
    {
        DEF_CHECKSUM defCheckSum;
        RETURN_IF_FAILED(DefChecksum::ComputeStringChecksum(0, true, value, &defCheckSum));
        OrchestratorDataReference* dataRefereceFromMap = m_OrchestratorHashMap->TryGetFromMap(defCheckSum, value, valueLength);

        if (dataRefereceFromMap == nullptr)
        {
            DataItemsSectionBuilder* dataItemSectionBuilder;
            RETURN_IF_FAILED(GetOrAddDataItemSectionBuilder(qualifierSetIndex, &dataItemSectionBuilder));

            RETURN_IF_FAILED(dataItemSectionBuilder->AddDataString(value, &preBuildReference));

            AutoDeletePtr<OrchestratorDataReference> autoBuildInstanceReference;
            RETURN_IF_FAILED(OrchestratorDataReference::CreateInstance(
                defCheckSum, value, valueLength, dataItemSectionBuilder, &preBuildReference, &autoBuildInstanceReference));

            RETURN_IF_FAILED(m_OrchestratorHashMap->AddtoMap(defCheckSum, autoBuildInstanceReference));

            buildInstanceReference = autoBuildInstanceReference.Detach();
        }
        else //duplication found
        {
            RETURN_IF_FAILED(
                OrchestratorDataReference::CloneDataReference(dataRefereceFromMap, (OrchestratorDataReference**)&buildInstanceReference));
        }
    }
    else
    {
        DataItemsSectionBuilder* dataItemSectionBuilder;
        RETURN_IF_FAILED(GetOrAddDataItemSectionBuilder(qualifierSetIndex, &dataItemSectionBuilder));

        RETURN_IF_FAILED(dataItemSectionBuilder->AddDataString(value, &preBuildReference));

        RETURN_IF_FAILED(DataItemsBuildInstanceReference::CreateInstance(
            dataItemSectionBuilder, &preBuildReference, (DataItemsBuildInstanceReference**)&buildInstanceReference));
    }

    *result = buildInstanceReference;
    return S_OK;
}

HRESULT DataItemOrchestrator::AddStringAndCreateInstanceReference(
    _In_ PCWSTR value,
    _In_ const IQualifierSet* qualifiers,
    _Outptr_ IBuildInstanceReference** result,
    _Out_ int* qualifierIndex)
{
    *result = nullptr;

    int qualifierSetIndex;
    RETURN_IF_FAILED(m_decisionInfo->GetOrAddQualifierSet(qualifiers, &qualifierSetIndex));

    *qualifierIndex = qualifierSetIndex;

    return AddStringAndCreateInstanceReference(value, *qualifierIndex, result);
}

HRESULT DataItemOrchestrator::OptimizeString(
    _Out_writes_bytes_to_(convertedStringSize, *writtenBytesIncludingNull) char* convertedString,
    _In_ PCWSTR value,
    _Inout_ size_t* writtenBytesIncludingNull,
    _In_ size_t convertedStringSize,
    _In_ MrmEnvironment::ResourceValueType* optimalType)
{
    _Analysis_assume_(*writtenBytesIncludingNull < convertedStringSize);
    DEF_ASSERT(*writtenBytesIncludingNull < convertedStringSize);

    if (MrmEnvironment::IsAsciiResourceValueType(*optimalType))
    {
        // WideCharToMultiByte supports only ANSI, not pure ASCII. So hand-roll an implementation here.
        for (size_t i = 0; i < *writtenBytesIncludingNull; i++)
        {
            DEF_ASSERT(value[i] <= 127); // Established by the encoding chooser.
            convertedString[i] = static_cast<char>(value[i]);
        }

        convertedString[*writtenBytesIncludingNull] = '\0';
        *writtenBytesIncludingNull =
            *writtenBytesIncludingNull + 1; // Count the null terminator here since WideCharToMultiByte returns the size with it included.
    }
    else
    {
        int convertedSize = WideCharToMultiByte(
            CP_UTF8,
            0,
            value,
            static_cast<int>(*writtenBytesIncludingNull + 1),
            convertedString,
            static_cast<int>(convertedStringSize),
            nullptr,
            nullptr);
        RETURN_LAST_ERROR_IF(convertedSize == 0);

        *writtenBytesIncludingNull = static_cast<size_t>(convertedSize);
    }
    return S_OK;
}

HRESULT DataItemOrchestrator::AddOptimizedStringAndCreateInstanceReference(
    _In_ MrmEnvironment::ResourceValueType originalType,
    _In_ PCWSTR value,
    _In_ int qualifierSetIndex,
    _Outptr_ IBuildInstanceReference** result,
    _Out_ MrmEnvironment::ResourceValueType* optimalType)
{
    *result = nullptr;
    RETURN_HR_IF(E_DEF_ALREADY_INITIALIZED, m_finalized);
    RETURN_HR_IF(E_DEF_INCOMPATIBLE_VALUE_TYPE, !MrmEnvironment::IsUtf16ResourceValueType(originalType));

    DataItemsSectionBuilder::PrebuildItemReference preBuildReference = {};

    if (m_buildConfiguration->UseDeduplication())
    {
        DEF_CHECKSUM defCheckSum = 0;
        OrchestratorDataReference* buildInstanceReference = nullptr;

        // Override the provided resource value type with the optimal one.
        *optimalType = MrmEnvironment::ConvertToBestValueType(originalType, DefString_ChooseBestEncoding(value));

        if (!MrmEnvironment::IsUtf16ResourceValueType(*optimalType))
        {
            // The input can be optimized.
            // The actual value stored in OrchestratorDataReference needs to be consistent with the converted value added to dataItemSectionBuilder.
            // Therefore we convert the stirng at first so we can check its check sum and serach for a duplicaiton,
            // then create OrchestratorDataReference instance to store the converted string.

            // We know that the new string is less than the size of the existing one, else we wouldn't bother converting it.
            size_t writtenBytesIncludingNull = wcslen(value);
            size_t convertedStringSize = (writtenBytesIncludingNull + 1) * sizeof(wchar_t);
            BlobResult convertedStringResult;
            char* convertedString;
            RETURN_IF_FAILED(convertedStringResult.SetEmptyContents(convertedStringSize, (void**)&convertedString));

            RETURN_IF_FAILED(OptimizeString(convertedString, value, &writtenBytesIncludingNull, convertedStringSize, optimalType));

            // Converting finished. Check duplication.
            defCheckSum = DefChecksum::ComputeChecksum(
                0, reinterpret_cast<const BYTE*>(convertedString), static_cast<UINT32>(writtenBytesIncludingNull));
            buildInstanceReference =
                m_OrchestratorHashMap->TryGetFromMap(defCheckSum, convertedString, static_cast<UINT32>(writtenBytesIncludingNull));

            if (buildInstanceReference == nullptr) // The input value is an unique one.
            {
                DataItemsSectionBuilder* dataItemSectionBuilder;
                RETURN_IF_FAILED(GetOrAddDataItemSectionBuilder(qualifierSetIndex, &dataItemSectionBuilder));

                RETURN_IF_FAILED(dataItemSectionBuilder->AddDataItem(
                    convertedString, static_cast<UINT32>(writtenBytesIncludingNull), &preBuildReference));

                AutoDeletePtr<OrchestratorDataReference> autoBuildInstanceReference;
                RETURN_IF_FAILED(OrchestratorDataReference::CreateInstance(
                    defCheckSum,
                    convertedString,
                    static_cast<size_t>(writtenBytesIncludingNull),
                    dataItemSectionBuilder,
                    &preBuildReference,
                    &autoBuildInstanceReference));

                RETURN_IF_FAILED(m_OrchestratorHashMap->AddtoMap(defCheckSum, autoBuildInstanceReference));

                *result = autoBuildInstanceReference.Detach();
                return S_OK;
            } // End of if (buildInstanceReference == nullptr)
            else // A duplication found.
            {
                return OrchestratorDataReference::CloneDataReference(buildInstanceReference, (OrchestratorDataReference**)result);
            }
        } // End of if(!MrmEnvironment::IsUtf16ResourceValueType(*optimalType))
        else // The input value do not need to be optimized.
        {
            RETURN_IF_FAILED(DefChecksum::DefChecksum::ComputeStringChecksum(0, true, value, &defCheckSum));

            size_t valueLength;
            RETURN_IF_FAILED(GetValueSize(value, &valueLength)); // Use safe calculations to get the value length.

            buildInstanceReference = m_OrchestratorHashMap->TryGetFromMap(defCheckSum, value, valueLength);
            if (buildInstanceReference == nullptr) // The input value is an unique one.
            {
                DataItemsSectionBuilder* dataItemSectionBuilder;
                RETURN_IF_FAILED(GetOrAddDataItemSectionBuilder(qualifierSetIndex, &dataItemSectionBuilder));

                RETURN_IF_FAILED(dataItemSectionBuilder->AddDataString(value, &preBuildReference));

                AutoDeletePtr<OrchestratorDataReference> autoBuildInstanceReference;
                RETURN_IF_FAILED(OrchestratorDataReference::CreateInstance(
                    defCheckSum, value, valueLength, dataItemSectionBuilder, &preBuildReference, &autoBuildInstanceReference));

                RETURN_IF_FAILED(m_OrchestratorHashMap->AddtoMap(defCheckSum, autoBuildInstanceReference));

                *result = autoBuildInstanceReference.Detach();
                return S_OK;
            }
            else // Duplication found
            {
                return OrchestratorDataReference::CloneDataReference(buildInstanceReference, (OrchestratorDataReference**)result);
            }
        } // End of else. End of non-optimized string deduplication process.
    } // End of deduplication process
    else // Deduplication disabled.
    {
        DataItemsSectionBuilder* dataItemSectionBuilder;
        RETURN_IF_FAILED(GetOrAddDataItemSectionBuilder(qualifierSetIndex, &dataItemSectionBuilder));

        // Override the provided resource value type with the optimal one.
        *optimalType = MrmEnvironment::ConvertToBestValueType(originalType, DefString_ChooseBestEncoding(value));

        if (!MrmEnvironment::IsUtf16ResourceValueType(*optimalType))
        {
            // We know that the new string is less than the size of the existing one, else we wouldn't bother converting it.
            size_t writtenBytesIncludingNull = wcslen(value);
            size_t convertedStringSize = (writtenBytesIncludingNull + 1) * sizeof(wchar_t);
            BlobResult convertedStringResult;
            char* convertedString;
            RETURN_IF_FAILED(convertedStringResult.SetEmptyContents(convertedStringSize, (void**)&convertedString));

            RETURN_IF_FAILED(OptimizeString(convertedString, value, &writtenBytesIncludingNull, convertedStringSize, optimalType));

            RETURN_IF_FAILED(
                dataItemSectionBuilder->AddDataItem(convertedString, static_cast<UINT32>(writtenBytesIncludingNull), &preBuildReference));
        }
        else
        {
            RETURN_IF_FAILED(dataItemSectionBuilder->AddDataString(value, &preBuildReference));
        }

        IBuildInstanceReference* buildInstanceReference;
        RETURN_IF_FAILED(DataItemsBuildInstanceReference::CreateInstance(
            dataItemSectionBuilder, &preBuildReference, (DataItemsBuildInstanceReference**)&buildInstanceReference));

        *result = buildInstanceReference;
    } // End of non-deduplication process
    return S_OK;
}

HRESULT DataItemOrchestrator::GetValueSize(_In_ PCWSTR value, _Out_ size_t* size)
{
    *size = 0;

    size_t valueLengthAfterAdd = 0;
    RETURN_IF_FAILED(SizeTAdd(wcslen(value), 1, &valueLengthAfterAdd));
    RETURN_IF_FAILED(SizeTMult(valueLengthAfterAdd, sizeof(WCHAR), size));

    return S_OK;
}

HRESULT DataItemOrchestrator::AddOptimizedStringAndCreateInstanceReference(
    _In_ MrmEnvironment::ResourceValueType originalType,
    _In_ PCWSTR value,
    _In_ const IQualifierSet* qualifiers,
    _Outptr_ IBuildInstanceReference** result,
    _Out_ int* qualifierIndex,
    _Out_ MrmEnvironment::ResourceValueType* optimalType)
{
    *result = nullptr;

    int qualifierSetIndex;
    RETURN_IF_FAILED(m_decisionInfo->GetOrAddQualifierSet(qualifiers, &qualifierSetIndex));

    *qualifierIndex = qualifierSetIndex;

    RETURN_IF_FAILED(AddOptimizedStringAndCreateInstanceReference(originalType, value, *qualifierIndex, result, optimalType));

    return S_OK;
}

void DataItemOrchestrator::DisableDeduplication()
{
    UINT32 newFlags = m_buildConfiguration->GetFlags() & (~MrmBuildConfiguration::UseDeduplicationFlag);
    m_buildConfiguration->SetFlags(newFlags);
}

HRESULT OrchestratorDataReference::CreateInstance(
    _In_ DEF_CHECKSUM valueHash,
    _In_reads_bytes_(valueSizeInBytes) const void* actualValue,
    _In_ size_t valueSizeInBytes,
    _In_ DataItemsSectionBuilder* builder,
    _In_ DataItemsSectionBuilder::PrebuildItemReference* preBuildItemReference,
    _Out_ OrchestratorDataReference** result)
{
    *result = nullptr;

    RETURN_HR_IF(E_INVALIDARG, (builder == nullptr) || (preBuildItemReference == nullptr));

    AutoDeletePtr<OrchestratorDataReference> orchestratorDataRef = new OrchestratorDataReference(valueHash, builder, preBuildItemReference);
    RETURN_IF_NULL_ALLOC(orchestratorDataRef);
    RETURN_IF_FAILED(orchestratorDataRef->Init(actualValue, valueSizeInBytes));

    *result = orchestratorDataRef.Detach();

    return S_OK;
}

OrchestratorDataReference::OrchestratorDataReference(
    _In_ DEF_CHECKSUM valueHash,
    _In_ DataItemsSectionBuilder* builder,
    _In_ DataItemsSectionBuilder::PrebuildItemReference* preBuildItemReference) :
    m_valueHash(valueHash), m_disBuilder(builder)
{
    m_innerReference.index = preBuildItemReference->index;
    m_innerReference.isLarge = preBuildItemReference->isLarge;
}

HRESULT OrchestratorDataReference::Init(_In_reads_bytes_(valueSizeInBytes) const void* actualValue, _In_ size_t valueSizeInBytes)
{
    RETURN_IF_FAILED(DynamicArray<UINT>::CreateInstance(10, &m_metadata));
    RETURN_IF_FAILED(m_actualDataBlob.SetCopy(actualValue, valueSizeInBytes));

    return S_OK;
}

HRESULT
OrchestratorDataReference::CloneDataReference(_In_ OrchestratorDataReference* sourceDataRef, _Outptr_ OrchestratorDataReference** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, sourceDataRef);

    const void* actualBlobData = sourceDataRef->GetActualValue();
    size_t actualBlobSize = sourceDataRef->GetActualValueSize();

    RETURN_IF_FAILED(OrchestratorDataReference::CreateInstance(
        sourceDataRef->m_valueHash, actualBlobData, actualBlobSize, sourceDataRef->m_disBuilder, &sourceDataRef->m_innerReference, result));

    return S_OK;
}

HRESULT OrchestratorDataReference::GenerateInstance(_Out_ MRMFILE_INDEX_INSTANCE* pInstanceIndex) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pInstanceIndex);

    DataItemsSectionBuilder::BuiltItemReference builtItemRef;
    RETURN_IF_FAILED(m_disBuilder->GetBuiltItemInfo(&m_innerReference, &builtItemRef));

    pInstanceIndex->instanceLocatorTypeOffset = MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM;
    pInstanceIndex->detail = builtItemRef.fileIndex; // This will be 0 for current file.
    pInstanceIndex->data1 = static_cast<UINT16>(builtItemRef.itemIndex & 0xffff);
    pInstanceIndex->data2 = builtItemRef.sectionIndex;
    pInstanceIndex->data3 = static_cast<UINT16>((builtItemRef.itemIndex >> 16) & 0xffff);

    return S_OK;
}

bool OrchestratorDataReference::IsReferenceEqual(_In_ const IBuildInstanceReference* pBuildInstanceReference) const
{
    if (MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM != pBuildInstanceReference->GetLocatorType())
    {
        return false;
    }

    BlobResult blob1;
    BlobResult blob2;

    Def_IfFailedReturnFalse(GetDataBlob(&blob1));
    Def_IfFailedReturnFalse(pBuildInstanceReference->GetDataBlob(&blob2));

    size_t blob1Size;
    size_t blob2Size;
    const void* pBlob1 = blob1.GetRef(&blob1Size);
    const void* pBlob2 = blob2.GetRef(&blob2Size);

    return ((blob1Size == blob2Size) && (memcmp(pBlob1, pBlob2, blob1Size) == 0));
}

HRESULT OrchestratorDataReference::GetDataBlob(_Inout_ BlobResult* pBlobResult) const
{
    MRMFILE_INDEX_INSTANCE indexInstance;
    RETURN_IF_FAILED(GenerateInstance(&indexInstance));

    int index = ((indexInstance.data3 << 16) | indexInstance.data1);

    RETURN_IF_FAILED(m_disBuilder->GetDataBlob(index, pBlobResult));

    return S_OK;
}

const void* OrchestratorDataReference::GetActualValue() const
{
    size_t blobSize = m_actualDataBlob.GetSize();
    if (blobSize == 0)
    {
        return nullptr;
    }
    return m_actualDataBlob.GetRef(&blobSize);
}

size_t OrchestratorDataReference::GetActualValueSize() const { return m_actualDataBlob.GetSize(); }

HRESULT OrchestratorHashNode::CreateInstance(
    _In_ DEF_CHECKSUM valueHash,
    _In_ OrchestratorDataReference* dataReference,
    _Outptr_ OrchestratorHashNode** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, dataReference);

    OrchestratorHashNode* hashNode = new OrchestratorHashNode(valueHash, dataReference);
    RETURN_IF_NULL_ALLOC(hashNode);

    *result = hashNode;
    return S_OK;
}

OrchestratorHashNode::OrchestratorHashNode(_In_ DEF_CHECKSUM valueHash, _In_ OrchestratorDataReference* dataReference) :
    m_valueHash(valueHash), m_dataReference(dataReference), m_nextOrchHashNode(nullptr)
{}

bool OrchestratorHashNode::SetNext(_In_ OrchestratorHashNode* inputNode)
{
    m_nextOrchHashNode = inputNode;
    return true;
}

OrchestratorHashMap::~OrchestratorHashMap()
{
    if (m_entries != nullptr)
    {
        for (int entryIndex = 0; entryIndex < m_currentSize; entryIndex++)
        {
            OrchestratorHashNode* node = nullptr;
            m_entries->TryGet(entryIndex, &node);
            while (node != nullptr)
            {
                OrchestratorHashNode* nodeToBeDeleted = node;
                node = node->GetNext();
                delete nodeToBeDeleted;
                nodeToBeDeleted = nullptr;
            }
        }

        delete m_entries;
    }
}

OrchestratorHashMap::OrchestratorHashMap(_In_ int initCapacity, _In_ float loadFactor) :
    m_currentSize(initCapacity), m_nodeCount(0), m_loadFactor(loadFactor)
{}

HRESULT OrchestratorHashMap::Init(int initCapacity)
{
    RETURN_IF_FAILED(DynamicArray<OrchestratorHashNode*>::CreateInstance(initCapacity, &m_entries));
    return S_OK;
}

HRESULT OrchestratorHashMap::CreateInstance(_In_ int initCapacity, _In_ float loadFactor, _Outptr_ OrchestratorHashMap** result)
{
    *result = nullptr;

    AutoDeletePtr<OrchestratorHashMap> orchsHashMap = new OrchestratorHashMap(initCapacity, loadFactor);
    RETURN_IF_NULL_ALLOC(orchsHashMap);
    RETURN_IF_FAILED(orchsHashMap->Init(initCapacity));

    *result = orchsHashMap.Detach();
    return S_OK;
}

int OrchestratorHashMap::HashCode(_In_ DEF_CHECKSUM key)
{
    int index = key % m_currentSize;
    return index;
}

int OrchestratorHashMap::HashCode(_In_ size_t newSize, _In_ DEF_CHECKSUM key)
{
    int index = key % newSize;
    return index;
}

HRESULT OrchestratorHashMap::AddtoMap(_In_ DEF_CHECKSUM key, _In_ OrchestratorDataReference* dataReference)
{
    RETURN_HR_IF_NULL(E_INVALIDARG, dataReference);

    int valueIndex = HashCode(key);
    OrchestratorHashNode* existingNode = nullptr;
    m_entries->TryGet(valueIndex, &existingNode);

    AutoDeletePtr<OrchestratorHashNode> newHashNode;
    RETURN_IF_FAILED(OrchestratorHashNode::CreateInstance(key, dataReference, &newHashNode));

    RETURN_IF_FAILED(m_entries->ExtendAndSet(valueIndex, newHashNode, &existingNode));
    OrchestratorHashNode* newLocalHasNode = newHashNode.Detach();

    if (existingNode != nullptr)
    {
        newLocalHasNode->SetNext(existingNode);
    }

    m_nodeCount++;

    if (m_nodeCount > m_currentSize * m_loadFactor)
    {
        RETURN_IF_FAILED(ResizeMap());
    }

    return S_OK;
}

HRESULT OrchestratorHashMap::ResizeMap()
{
    int oldindex = 0;
    int newIndex = 0;
    DEF_CHECKSUM key = 0;
    OrchestratorHashNode* nodeToMove = nullptr;
    OrchestratorHashNode* nestNodeInOldMap = nullptr;
    OrchestratorHashNode* existingNodeInNewMap = nullptr;
    OrchestratorDataReference* dataReference = nullptr;
    DynamicArray<OrchestratorHashNode*>* oldMapEntry = m_entries;
    AutoDeletePtr<DynamicArray<OrchestratorHashNode*>> newMapEntry;

    RETURN_IF_FAILED(DynamicArray<OrchestratorHashNode*>::CreateInstance(m_currentSize * 2, &newMapEntry));

    for (oldindex = 0; oldindex < m_currentSize; oldindex++)
    {
        nestNodeInOldMap = nullptr;
        if (!oldMapEntry->TryGet(oldindex, &nestNodeInOldMap))
        {
            continue;
        }

        while (nestNodeInOldMap != nullptr)
        {
            //move the odeNode pointer
            nodeToMove = nestNodeInOldMap;
            nestNodeInOldMap = nestNodeInOldMap->GetNext();

            //set this node's nextpoint to null
            nodeToMove->SetNext(nullptr);

            //Calculate new index by the hash from its reference
            dataReference = nodeToMove->GetDataReference();
            key = dataReference->GetValueHash();
            size_t newsize = 0;
            RETURN_IF_FAILED(SizeTAdd(m_currentSize, m_currentSize, &newsize));

            newIndex = HashCode(newsize, key);

            //put the new node(actually not a totally new one)
            //check if the position is null
            existingNodeInNewMap = nullptr;
            newMapEntry->TryGet(newIndex, &existingNodeInNewMap);

            if (existingNodeInNewMap == nullptr) //the new position is empty, put the node in there
            {
                RETURN_IF_FAILED(newMapEntry->ExtendAndSet(newIndex, nodeToMove));
            }
            else //the new position is not empty, put the new node in front of the existing node.
            {
                nodeToMove->SetNext(existingNodeInNewMap);
                RETURN_IF_FAILED(newMapEntry->ExtendAndSet(newIndex, nodeToMove));
            }
            //Finish adding one node continue check.
        }
    }

    m_entries = newMapEntry.Detach();
    delete oldMapEntry;
    m_currentSize = m_currentSize * 2;
    return S_OK;
}

OrchestratorDataReference* OrchestratorHashMap::TryGetFromMap(
    _In_ DEF_CHECKSUM key,
    _In_opt_ const void* value,
    _In_opt_ size_t valueSizeInBytes)
{
    if ((value == nullptr) || (valueSizeInBytes > SIZE_T_MAX))
    {
        return nullptr;
    }

    int valueIndex = HashCode(key);
    int ifEqual = 1;

    // get the entry of the value
    OrchestratorHashNode* existingNodeInCurrentMap = nullptr;

    (void)m_entries->Get(valueIndex, &existingNodeInCurrentMap);

    // if it is nullptr, there is no exsiting node in that position.
    // Return nullptr means new node can be added to this position.
    if (existingNodeInCurrentMap == nullptr)
    {
        return nullptr;
    }

    // If the entry is not nullptr, need to check the link on this entry.
    while (existingNodeInCurrentMap != nullptr)
    {
        // Firstly, check if there is any same hash code in the link.
        if (existingNodeInCurrentMap->GetHash() == key)
        {
            // A node with the same hash code found
            // Secondly, check if they have the same hash value.
            // Only if so, they can be considered as duplicate values.
            OrchestratorDataReference* dataReference = existingNodeInCurrentMap->GetDataReference();

            // if the input value has the same size with the existing value, check the actual values.
            // if they have different size, consider as different value.
            if (valueSizeInBytes == dataReference->GetActualValueSize())
            {
                const void* existingValue = dataReference->GetActualValue();
                ifEqual = memcmp(value, existingValue, valueSizeInBytes);
            }

            if (ifEqual == 0)
            {
                // A true duplication found, return the existing dataReference.
                return dataReference;
            }
        }

        existingNodeInCurrentMap = existingNodeInCurrentMap->GetNext();
    }

    return nullptr;
}

} // namespace Microsoft::Resources::Build