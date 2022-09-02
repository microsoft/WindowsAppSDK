// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

namespace Microsoft::Resources
{

class FileDataSection : public FileSectionBase
{
protected:
    _Field_size_bytes_(m_cbData) const BYTE* m_pData;
    UINT32 m_cbData;

    FileDataSection& operator=(const FileDataSection&) {}

    FileDataSection() : m_pData(nullptr), m_cbData(0) {}

    HRESULT Init(_In_opt_ const IFileSection* pSection, _In_reads_bytes_(cbData) const void* pData, _In_ int cbData);

public:
    static HRESULT CreateInstance(_In_reads_bytes_(cbData) const void* pData, _In_ int cbData, _Outptr_ FileDataSection** result);

    static HRESULT CreateInstance(_In_ IFileSection* pSection, _Outptr_ FileDataSection** result);

    virtual ~FileDataSection() {}

    HRESULT GetDataRef(_In_ UINT32 offset, _Out_ const BYTE** result, _Out_opt_ size_t* pcbBytesLeftOut = nullptr) const;
    HRESULT GetDataRef(_In_ UINT32 offset, _In_ size_t cbData, _Out_ const BYTE** result) const;
    HRESULT GetDataRef(_In_ UINT32 offset, _In_ UINT32 cbData, _Inout_ BlobResult* pData) const;
    static const DEFFILE_SECTION_TYPEID GetSectionTypeId() { return gDataSectionType; }
};

class FileDataItemsSection : public FileSectionBase
{
protected:
    const DEFFILE_DATAITEMS_HEADER* m_pHeader;

    _Field_size_(m_pHeader->numSmallItems) const DEFFILE_DATA_ITEM_SMALL* m_pSmallItems;
    _Field_size_(m_pHeader->numLargeItems) const DEFFILE_DATA_ITEM_LARGE* m_pLargeItems;
    _Field_size_bytes_(m_pHeader->cbData) const BYTE* m_pData;

    FileDataItemsSection& operator=(const FileDataSection&) {}

    FileDataItemsSection() : m_pHeader(nullptr), m_pSmallItems(nullptr), m_pLargeItems(nullptr), m_pData(nullptr) {}

    HRESULT Init(_In_opt_ const IFileSection* pSection, _In_reads_bytes_(cbData) const void* pData, _In_ int cbData);

    HRESULT ValidateHeader(_In_reads_bytes_(cbData) const void* pData, _In_ UINT32 cbData);

public:
    static HRESULT CreateInstance(_In_reads_bytes_(cbData) const void* pData, _In_ int cbData, _Outptr_ FileDataItemsSection** result);
    static HRESULT CreateInstance(_In_ IFileSection* pSection, _Outptr_ FileDataItemsSection** result);

    virtual ~FileDataItemsSection() {}

    int GetNumItems() const { return (m_pHeader->numSmallItems + GetNumberOfLargeItems(m_pHeader)); }

    HRESULT
    GetItemDataRef(_In_ UINT32 index, _Outptr_result_bytebuffer_(*pcbDataOut) const BYTE** result, _Out_opt_ UINT32* pcbDataOut) const;
    HRESULT GetItemDataRef(_In_ UINT32 index, _Inout_ BlobResult* pData) const;

    static const DEFFILE_SECTION_TYPEID GetSectionTypeId() { return gDataItemsSectionType; }
};

} // namespace Microsoft::Resources