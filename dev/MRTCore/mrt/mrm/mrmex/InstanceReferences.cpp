// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"
#include "intsafe.h"

namespace Microsoft::Resources::Build
{

DataItemsBuildInstanceReference::DataItemsBuildInstanceReference(
    _In_ DataItemsSectionBuilder* pBuilder,
    _In_ DataItemsSectionBuilder::PrebuildItemReference* pPreBuildItemReference) :
    m_pDISBuilder(pBuilder)
{
    m_PreBuildReference.index = pPreBuildItemReference->index;
    m_PreBuildReference.isLarge = pPreBuildItemReference->isLarge;
}

HRESULT DataItemsBuildInstanceReference::CreateInstance(
    _In_ DataItemsSectionBuilder* pBuilder,
    _In_ DataItemsSectionBuilder::PrebuildItemReference* pPreBuildItemReference,
    _Outptr_ DataItemsBuildInstanceReference** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (pBuilder == nullptr) || (pPreBuildItemReference == nullptr));

    DataItemsBuildInstanceReference* pDataBuilder = new DataItemsBuildInstanceReference(pBuilder, pPreBuildItemReference);
    RETURN_IF_NULL_ALLOC(pDataBuilder);

    *result = pDataBuilder;
    return S_OK;
}

HRESULT DataItemsBuildInstanceReference::GenerateInstance(__out MRMFILE_INDEX_INSTANCE* pInstanceIndex) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pInstanceIndex);

    DataItemsSectionBuilder::BuiltItemReference builtItemRef;
    RETURN_IF_FAILED(m_pDISBuilder->GetBuiltItemInfo(&m_PreBuildReference, &builtItemRef));

    pInstanceIndex->instanceLocatorTypeOffset = MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM;
    pInstanceIndex->detail = builtItemRef.fileIndex; // This will be 0 for current file.
    pInstanceIndex->data1 = static_cast<UINT16>(builtItemRef.itemIndex & 0xffff);
    pInstanceIndex->data2 = builtItemRef.sectionIndex;
    pInstanceIndex->data3 = static_cast<UINT16>((builtItemRef.itemIndex >> 16) & 0xffff);

    return S_OK;
}

bool DataItemsBuildInstanceReference::IsReferenceEqual(_In_ const IBuildInstanceReference* pBuildInstanceReference) const
{
    if (MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM != pBuildInstanceReference->GetLocatorType())
    {
        return false;
    }

    BlobResult blob1;
    BlobResult blob2;

    if (FAILED(GetDataBlob(&blob1)) || FAILED(pBuildInstanceReference->GetDataBlob(&blob2)))
    {
        return false;
    }
    size_t blob1Size;
    size_t blob2Size;
    const void* pBlob1 = blob1.GetRef(&blob1Size);
    const void* pBlob2 = blob2.GetRef(&blob2Size);

    return ((blob1Size == blob2Size) && (memcmp(pBlob1, pBlob2, blob1Size) == 0));
}

HRESULT DataItemsBuildInstanceReference::GetDataBlob(_Inout_ BlobResult* pBlobResult) const
{
    MRMFILE_INDEX_INSTANCE indexInstance1;

    RETURN_IF_FAILED(GenerateInstance(&indexInstance1));

    int index = ((indexInstance1.data3 << 16) | indexInstance1.data1);

    return m_pDISBuilder->GetDataBlob(index, pBlobResult);
}

HRESULT
FileSectionBuildInstanceReference::CreateInstance(
    _In_ FileListBuilder* pBuilder,
    _In_ FileInfo* pFileInfo,
    _Outptr_ FileSectionBuildInstanceReference** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (pBuilder == nullptr) || (pFileInfo == nullptr));

    FileSectionBuildInstanceReference* pFileListBuilder = new FileSectionBuildInstanceReference(pBuilder, pFileInfo);
    RETURN_IF_NULL_ALLOC(pFileListBuilder);

    *result = pFileListBuilder;
    return S_OK;
}

HRESULT FileSectionBuildInstanceReference::GenerateInstance(__out MRMFILE_INDEX_INSTANCE* pInstanceIndex) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pInstanceIndex);

    int iFilePathIndex = m_pFileInfo->GetIndex();
    if (iFilePathIndex < 0)
    {
        return E_ABORT;
    }

    pInstanceIndex->detail = 0;
    pInstanceIndex->data1 = (UINT16)iFilePathIndex;
    pInstanceIndex->data2 = m_pFileListBuilder->GetSectionIndex();
    pInstanceIndex->data3 = 0;

    return S_OK;
}

bool FileSectionBuildInstanceReference::IsReferenceEqual(_In_ const IBuildInstanceReference* pBuildInstanceReference) const
{
    if (MRMFILE_MAP_VALUE_LOCATOR_FILE_ITEM != pBuildInstanceReference->GetLocatorType())
    {
        return false;
    }

    MRMFILE_INDEX_INSTANCE indexInstance1 = {};
    MRMFILE_INDEX_INSTANCE indexInstance2 = {};
    if (FAILED(GenerateInstance(&indexInstance1)) || FAILED(pBuildInstanceReference->GenerateInstance(&indexInstance2)))
    {
        return false;
    }

    return (indexInstance1.detail == indexInstance2.detail) && (indexInstance1.data1 == indexInstance2.data1) &&
           (indexInstance1.data2 == indexInstance2.data2) && (indexInstance1.data3 == indexInstance2.data3);
}

HRESULT FileSectionBuildInstanceReference::GetDataBlob(_Inout_ BlobResult* /*pBlobResult*/) const
{
    // This is temporary, and it should be supported when FileSectionBuildInstanceReference (FileList Item) is used.
    return E_NOTIMPL;
}

FileSectionBuildInstanceReference::FileSectionBuildInstanceReference(_In_ FileListBuilder* pBuilder, _In_ FileInfo* pFileInfo) :
    m_pFileListBuilder(pBuilder), m_pFileInfo(pFileInfo)
{}

HRESULT ExternalFileStaticDataInstanceReference::CreateInstance(
    _In_ ResourceCandidateResult* pResourceCandidateResult,
    _In_ const FileInfo* pFileInfo,
    _Outptr_ ExternalFileStaticDataInstanceReference** result)
{
    *result = nullptr;
    RETURN_HR_IF(E_INVALIDARG, (pResourceCandidateResult == nullptr) || (pFileInfo == nullptr));

    AutoDeletePtr<ExternalFileStaticDataInstanceReference> pStaticBuilder =
        new ExternalFileStaticDataInstanceReference(pResourceCandidateResult, pFileInfo);
    RETURN_IF_NULL_ALLOC(pStaticBuilder);
    RETURN_IF_FAILED(pStaticBuilder->Init());

    *result = pStaticBuilder.Detach();
    return S_OK;
}

ExternalFileStaticDataInstanceReference::ExternalFileStaticDataInstanceReference(
    _In_ ResourceCandidateResult* pResourceCandidateResult,
    _In_ const FileInfo* pFileInfo) :
    m_pFileInfo(pFileInfo)
{
    m_resourceCandidateResult = *pResourceCandidateResult;
}

HRESULT ExternalFileStaticDataInstanceReference::Init()
{
    MRMFILE_MAP_VALUE_LOCATOR locatorType;
    UINT32 data; // sectioniIndex + itemIndex
    UINT16 extraData; // higher bits of itemIndex
    UINT16 detail;

    RETURN_IF_FAILED(m_resourceCandidateResult.GetValueLocation(&locatorType, &data, &extraData, &detail));

    // fileIndex, which is 0 all the time at this point since ExternalFileStaticDataInstanceReference is called
    // from resource pack merge that handle only resource pack where every fileindex  in the resource map
    // is 0
    DEF_ASSERT(detail == 0);

    if (locatorType != MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM)
    {
        return E_DEF_INCOMPATIBLE_LOCATOR_TYPE;
    }

    m_mrmIndexInstance.instanceLocatorTypeOffset = locatorType;
    m_mrmIndexInstance.data1 = static_cast<UINT16>(data); // lower bits of item index
    m_mrmIndexInstance.data2 = static_cast<UINT16>(data >> 16); // section index
    m_mrmIndexInstance.data3 = extraData; // higher bits of item index

    return S_OK;
}

HRESULT ExternalFileStaticDataInstanceReference::GenerateInstance(_Out_ MRMFILE_INDEX_INSTANCE* pInstanceIndex) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pInstanceIndex);

    *pInstanceIndex = m_mrmIndexInstance;
    // GenerateInstance is called from (1) candidate addition time, (2) Resource Map Build time
    // fileIndex (detail) will be -1 in the (1) case, but real valid value in the (2) case.
    pInstanceIndex->detail = static_cast<UINT16>(m_pFileInfo->GetIndex());

    return S_OK;
}

bool ExternalFileStaticDataInstanceReference::IsReferenceEqual(_In_ const IBuildInstanceReference* pBuildInstanceReference) const
{
    if (MRMFILE_MAP_VALUE_LOCATOR_DATA_ITEM != pBuildInstanceReference->GetLocatorType())
    {
        return false;
    }

    BlobResult blob1;
    BlobResult blob2;

    if (FAILED(GetDataBlob(&blob1)) || FAILED(pBuildInstanceReference->GetDataBlob(&blob2)))
    {
        return false;
    }

    bool bRet = (blob1.Compare(&blob2) == Def_Equal);
    return bRet;
}

HRESULT ExternalFileStaticDataInstanceReference::GetDataBlob(_Inout_ BlobResult* pBlobResult) const
{
    StringResult strResult;
    MrmEnvironment::ResourceValueType valueType;

    RETURN_IF_FAILED(m_resourceCandidateResult.GetResourceValueType(&valueType));

    if (MrmEnvironment::IsBinaryResourceValueType(valueType))
    {
        if (!m_resourceCandidateResult.TryGetBlobValue(pBlobResult))
        {
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }
        return S_OK;
    }
    else if (MrmEnvironment::IsPathResourceValueType(valueType))
    {
        if (!m_resourceCandidateResult.TryGetStringValue(&strResult))
        {
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }
        RETURN_IF_FAILED(GetBlobResultFromStringResult(&strResult, pBlobResult));
        return S_OK;
    }
    else if (MrmEnvironment::IsStringResourceValueType(valueType))
    {
        if (!m_resourceCandidateResult.TryGetStringValue(&strResult))
        {
            return HRESULT_FROM_WIN32(ERROR_NOT_FOUND);
        }
        RETURN_IF_FAILED(GetBlobResultFromStringResult(&strResult, pBlobResult));
        return S_OK;
    }

    DEF_ASSERT(FALSE);
    return E_INVALIDARG;
}

} // namespace Microsoft::Resources::Build