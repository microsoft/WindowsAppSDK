// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "stdafx.h"

namespace Microsoft
{
namespace Resources
{

HRESULT StaticHierarchicalSchemaDescription::Init(
    _In_ StaticSchemaDescriptionFlags flags,
    _In_ PCWSTR pSimpleName,
    _In_ PCWSTR pUniqueName,
    _In_ UINT16 majorVersion,
    _In_ UINT16 minorVersion,
    _In_range_(<=, INT_MAX) size_t numScopeNames,
    _In_reads_(numScopeNames) PWSTR* ppScopeNames,
    _In_range_(<=, INT_MAX) size_t numItemNames,
    _In_reads_(numItemNames) PWSTR* ppItemNames)
{
    m_majorVersion = majorVersion;
    m_minorVersion = minorVersion;

    RETURN_IF_FAILED(_DefSizeTToInt(numScopeNames, &m_numScopeNames));
    RETURN_IF_FAILED(_DefSizeTToInt(numItemNames, &m_numItemNames));

    if ((flags & CreateByReference) != 0)
    {
        RETURN_IF_FAILED(m_simpleName.SetRef(pSimpleName));
        RETURN_IF_FAILED(m_uniqueName.SetRef(pUniqueName));
        RETURN_IF_FAILED(
            StaticAtomPool::CreateInstance(ppScopeNames, m_numScopeNames, L"", StaticAtomPool::AllowNullForAtom0, &m_pScopeNames));
        RETURN_IF_FAILED(StaticAtomPool::CreateInstance(ppItemNames, m_numItemNames, L"", StaticAtomPool::DefaultFlags, &m_pItemNames));

        m_ppMyScopeNames = m_ppMyItemNames = nullptr;
    }
    else
    {
        RETURN_IF_FAILED(m_simpleName.SetCopy(pSimpleName));
        RETURN_IF_FAILED(m_uniqueName.SetCopy(pUniqueName));

        m_ppMyScopeNames = _DefArray_AllocZeroed(PWSTR, numScopeNames);
        RETURN_IF_NULL_ALLOC(m_ppMyScopeNames);
        m_ppMyItemNames = _DefArray_AllocZeroed(PWSTR, numItemNames);
        RETURN_IF_NULL_ALLOC(m_ppMyItemNames);

        for (int i = 0; i < m_numScopeNames; i++)
        {
            RETURN_IF_FAILED(DefString_Dup(ppScopeNames[i], &m_ppMyScopeNames[i]));
        }

        for (int i = 0; i < m_numItemNames; i++)
        {
            RETURN_IF_FAILED(DefString_Dup(ppItemNames[i], &m_ppMyItemNames[i]));
        }

        RETURN_IF_FAILED(
            StaticAtomPool::CreateInstance(m_ppMyScopeNames, m_numScopeNames, L"", StaticAtomPool::AllowNullForAtom0, &m_pScopeNames));
        RETURN_IF_FAILED(StaticAtomPool::CreateInstance(m_ppMyItemNames, m_numItemNames, L"", StaticAtomPool::DefaultFlags, &m_pItemNames));
    }

    return S_OK;
}

HRESULT
StaticHierarchicalSchemaDescription::CreateInstance(
    _In_ StaticSchemaDescriptionFlags flags,
    _In_ PCWSTR pSimpleName,
    _In_ PCWSTR pUniqueName,
    _In_ UINT16 majorVersion,
    _In_ UINT16 minorVersion,
    _In_ size_t numScopes,
    _In_reads_(numScopes) PWSTR* ppScopeNames,
    _In_ size_t numItems,
    _In_reads_(numItems) PWSTR* ppItemNames,
    _Outptr_ StaticHierarchicalSchemaDescription** result)
{
    *result = nullptr;

    AutoDeletePtr<StaticHierarchicalSchemaDescription> pRtrn = new StaticHierarchicalSchemaDescription();
    RETURN_IF_NULL_ALLOC(pRtrn);

    RETURN_IF_FAILED(
        pRtrn->Init(flags, pSimpleName, pUniqueName, majorVersion, minorVersion, numScopes, ppScopeNames, numItems, ppItemNames));

    *result = pRtrn.Detach();

    return S_OK;
}

StaticHierarchicalSchemaDescription::~StaticHierarchicalSchemaDescription()
{
    if (m_ppMyScopeNames)
    {
        for (int i = 0; i < m_numScopeNames; i++)
        {
            Def_Free(m_ppMyScopeNames[i]);
            m_ppMyScopeNames[i] = nullptr;
        }
        Def_Free(m_ppMyScopeNames);
        m_ppMyScopeNames = nullptr;
    }

    if (m_ppMyItemNames)
    {
        for (int i = 0; i < m_numItemNames; i++)
        {
            Def_Free(m_ppMyItemNames[i]);
            m_ppMyItemNames[i] = nullptr;
        }
        Def_Free(m_ppMyItemNames);
        m_ppMyItemNames = nullptr;
    }
}

HRESULT
HierarchicalSchemaVersionInfo::CreateInstance(
    _In_reads_bytes_(cbData) const void* pData,
    _In_ size_t cbData,
    _Outptr_ HierarchicalSchemaVersionInfo** result)
{
    *result = nullptr;
    AutoDeletePtr<HierarchicalSchemaVersionInfo> pRtrn = new HierarchicalSchemaVersionInfo();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pData, cbData));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT
HierarchicalSchemaVersionInfo::CreateInstance(
    _In_ const MRMFILE_HSCHEMA_VERSION_INFO* pHeader,
    _Outptr_ HierarchicalSchemaVersionInfo** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pHeader);

    HierarchicalSchemaVersionInfo* pRtrn = new HierarchicalSchemaVersionInfo(pHeader);
    RETURN_IF_NULL_ALLOC(pRtrn);

    *result = pRtrn;
    return S_OK;
}

HRESULT HierarchicalSchemaVersionInfo::Init(_In_reads_bytes_(cbData) const void* pData, _In_ size_t cbData)
{
    SectionParser data;
    RETURN_IF_FAILED(data.Set(pData, static_cast<UINT32>(cbData)));

    HRESULT hr = S_OK;
    m_pHeader = _SECTION_PARSER_NEXT(data, MRMFILE_HSCHEMA_VERSION_INFO, &hr);
    return hr;
}

HierarchicalSchemaVersionInfo::HierarchicalSchemaVersionInfo(_In_ const MRMFILE_HSCHEMA_VERSION_INFO* pHeader) { m_pHeader = pHeader; }

HRESULT
HierarchicalSchemaReference::CreateInstance(
    _In_reads_bytes_(cbData) const void* pData,
    _In_ size_t cbData,
    _Outptr_ HierarchicalSchemaReference** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pData);

    AutoDeletePtr<HierarchicalSchemaReference> pRtrn = new HierarchicalSchemaReference();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pData, cbData));

    *result = pRtrn.Detach();
    return S_OK;
}

bool HierarchicalSchemaReference::CheckIsIdentical(_In_ const IHierarchicalSchema* pSchema) const
{
    if (pSchema == nullptr)
    {
        return false;
    }
    const IHierarchicalSchemaVersionInfo* pVersion = pSchema->GetVersionInfo();
    if ((DefString_CchCompareWithOptions(m_pUniqueId, pSchema->GetUniqueId(), m_pHdr->cchUniqueId, DefCompare_CaseInsensitive) !=
         Def_Equal) ||
        (!CheckHierarchicalSchemaVersionIsIdentical(m_pVersion, pVersion)))
    {
        return false;
    }
    return true;
}

bool HierarchicalSchemaReference::CheckIsCompatible(_In_ const IHierarchicalSchema* pSchema) const
{
    if (pSchema == nullptr)
    {
        return false;
    }
    if (CheckIsIdentical(pSchema))
    {
        return true;
    }
    DefChecksum::Checksum cs = 0;
    return (SUCCEEDED(ComputeHierarchicalSchemaVersionChecksum(pSchema, m_pVersion, &cs)) && (cs == m_pVersion->GetVersionChecksum()));
}

bool HierarchicalSchemaReference::CheckIsIdentical(_In_ const HierarchicalSchemaReference* schema) const
{
    if (schema == nullptr)
    {
        return false;
    }

    const IHierarchicalSchemaVersionInfo* wantVersion = schema->GetVersionInfo();

    if ((DefString_CchCompareWithOptions(m_pUniqueId, schema->GetUniqueId(), m_pHdr->cchUniqueId, DefCompare_CaseInsensitive) ==
         Def_Equal) &&
        (CheckHierarchicalSchemaVersionIsIdentical(m_pVersion, wantVersion)))
    {
        return true;
    }

    return false;
}

HRESULT HierarchicalSchemaReference::Init(_In_reads_bytes_(cbData) const void* pData, _In_ size_t cbData)
{
    SectionParser data;
    RETURN_IF_FAILED(data.Set(pData, static_cast<UINT32>(cbData)));

    HRESULT hr = S_OK;
    m_pHdr = _SECTION_PARSER_NEXT(data, MRMFILE_HSCHEMA_REF, &hr);
    RETURN_IF_FAILED(hr);

    m_pUniqueId = _SECTION_PARSER_NEXT_ARRAY(data, m_pHdr->cchUniqueId, WCHAR, &hr);
    RETURN_IF_FAILED(hr);

    RETURN_IF_FAILED(HierarchicalSchemaVersionInfo::CreateInstance(
        &m_pHdr->version, sizeof(m_pHdr->version), (HierarchicalSchemaVersionInfo**)&m_pVersion));
    return S_OK;
}

HierarchicalSchemaReference::~HierarchicalSchemaReference()
{
    if (m_pVersion != nullptr)
    {
        delete m_pVersion;
        m_pVersion = nullptr;
    }
}

HRESULT
ComputeHierarchicalSchemaVersionChecksum(
    _In_ const IHierarchicalSchema* pSchema,
    _In_ const IHierarchicalSchemaVersionInfo* pVersion,
    _Out_ DefChecksum::Checksum* pChecksumOut)
{
    RETURN_HR_IF(E_INVALIDARG, (pSchema == nullptr) || (pVersion == nullptr) || (pChecksumOut == nullptr));

    *pChecksumOut = 0;
    RETURN_HR_IF(E_DEF_SIZE_MISMATCH, pVersion->GetNumScopes() > pSchema->GetNumScopes());
    RETURN_HR_IF(E_DEF_SIZE_MISMATCH, pVersion->GetNumItems() > pSchema->GetNumItems());

    union
    {
        UINT32 ui32;
        UINT16 ui16[2];
    } v;
    v.ui16[0] = static_cast<UINT16>(pVersion->GetMajorVersion());
    v.ui16[1] = static_cast<UINT16>(pVersion->GetMinorVersion());
    DEF_CHECKSUM crc;
    RETURN_IF_FAILED(DefChecksum::ComputeStringChecksum(0, true, pSchema->GetUniqueId(), &crc));
    RETURN_IF_FAILED(DefChecksum::ComputeStringChecksum(crc, true, pSchema->GetSimpleId(), &crc));
    crc = DefChecksum::ComputeUInt32Checksum(crc, v.ui32);
    RETURN_IF_FAILED(DefChecksum::ComputeAtomPoolChecksum(crc, pSchema->GetScopeNames(), pVersion->GetNumScopes(), &crc));
    RETURN_IF_FAILED(DefChecksum::ComputeAtomPoolChecksum(crc, pSchema->GetItemNames(), pVersion->GetNumItems(), &crc));

    *pChecksumOut = crc;
    return S_OK;
}

bool CheckHierarchicalSchemaVersionIsIdentical(
    _In_opt_ const IHierarchicalSchemaVersionInfo* pVersion1,
    _In_opt_ const IHierarchicalSchemaVersionInfo* pVersion2)
{
    if ((pVersion1 == nullptr) || (pVersion2 == nullptr))
    {
        return false;
    }

    if ((pVersion1->GetMajorVersion() != pVersion2->GetMajorVersion()) || (pVersion1->GetMinorVersion() != pVersion2->GetMinorVersion()) ||
        (pVersion1->GetVersionChecksum() != pVersion2->GetVersionChecksum()) || (pVersion1->GetNumScopes() != pVersion2->GetNumScopes()) ||
        (pVersion1->GetNumItems() != pVersion2->GetNumItems()))
    {
        return false;
    }

    return true;
}

bool CheckHierarchicalSchemaVersionIsCompatible(
    _In_opt_ const IHierarchicalSchema* pHaveSchema,
    _In_opt_ const IHierarchicalSchemaVersionInfo* pWantVersion)
{
    if ((pHaveSchema == nullptr) || (pWantVersion == nullptr))
    {
        return false;
    }

    const IHierarchicalSchemaVersionInfo* pHaveVersion = pHaveSchema->GetVersionInfo();
    if (CheckHierarchicalSchemaVersionIsIdentical(pWantVersion, pHaveVersion))
    {
        return true;
    }
    if ((pWantVersion->GetMajorVersion() != pHaveVersion->GetMajorVersion()) ||
        (pWantVersion->GetMinorVersion() >= pHaveVersion->GetMinorVersion()))
    {
        return false;
    }

    DefChecksum::Checksum cs = 0;
    return (
        SUCCEEDED(ComputeHierarchicalSchemaVersionChecksum(pHaveSchema, pWantVersion, &cs)) && (cs == pWantVersion->GetVersionChecksum()));
}

HierarchicalSchema::HierarchicalSchema() :
    m_pUniqueId(nullptr), m_pSimpleId(nullptr), m_pVersions(nullptr), m_pNames(nullptr), m_pMyBuffer(nullptr)
{
    m_header.numVersions = 0; // This is needed during class destruction so ensure it always has a predictable state.
}

HRESULT
HierarchicalSchema::Init(
    _In_ const DEFFILE_SECTION_TYPEID& type,
    _In_opt_ const IFileSection* pSection,
    _In_reads_bytes_(cbData) const void* pData,
    _In_ int cbData)
{
    RETURN_IF_FAILED(FileSectionBase::Init(pSection, pData, cbData));

    SectionParser data;
    RETURN_IF_FAILED(data.Set(pData, cbData));

    HRESULT hr = S_OK;
    if (BaseFile::SectionTypesEqual(type, gHierarchicalSchemaSectionType))
    {

        const MRMFILE_HSCHEMA_HEADER* pHeader = _SECTION_PARSER_NEXT(data, MRMFILE_HSCHEMA_HEADER, &hr);
        RETURN_IF_FAILED(hr);

        m_header.cchSimpleId = pHeader->cchSimpleId;
        m_header.cchUniqueId = pHeader->cchUniqueId;
        m_header.numVersions = pHeader->numVersions;
        m_header.pad = pHeader->pad;
        m_header.hnamesTypeId = gHierarchicalNamesSectionType;
    }
    else if (BaseFile::SectionTypesEqual(type, gHierarchicalSchemaExSectionType))
    {
        const MRMFILE_HSCHEMA_HEADER_EX* pHeader = _SECTION_PARSER_NEXT(data, MRMFILE_HSCHEMA_HEADER_EX, &hr);
        RETURN_IF_FAILED(hr);

        m_header = *pHeader;
    }
    else
    {
        return E_NOTIMPL;
    }

    if ((m_header.numVersions < 1) || (m_header.cchUniqueId < 2) || (m_header.cchSimpleId < 2))
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE);
    }

    m_pFileVersions = _SECTION_PARSER_NEXT_ARRAY(data, m_header.numVersions, MRMFILE_HSCHEMA_VERSION_INFO, &hr);
    m_pUniqueId = _SECTION_PARSER_NEXT_ARRAY(data, m_header.cchUniqueId, WCHAR, &hr);
    m_pSimpleId = _SECTION_PARSER_NEXT_ARRAY(data, m_header.cchSimpleId, WCHAR, &hr);
    data.GetPadBytes(BaseFile::Align32Bit, &hr, nullptr);
    RETURN_IF_FAILED(hr);

    m_pVersions = nullptr; // lazy init
    RETURN_IF_FAILED(HierarchicalNames::CreateInstance(
        m_header.hnamesTypeId,
        data.RemainingBuffer(),
        static_cast<int>(data.RemainingBufferSizeInBytes()),
        (HierarchicalNames**)&m_pNames));
    m_pSectionData = pData;
    m_cbSection = cbData;

    return S_OK;
}

HRESULT
HierarchicalSchema::CreateFromSection(_In_opt_ const IFileSection* pSection, _Outptr_ HierarchicalSchema** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pSection);

    AutoDeletePtr<HierarchicalSchema> pRtrn = new HierarchicalSchema();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pSection->GetSectionType(), pSection, pSection->GetData(), pSection->GetDataSize()));

    *result = pRtrn.Detach();
    return S_OK;
}

HRESULT
HierarchicalSchema::CreateInstance(
    _In_ const DEFFILE_SECTION_TYPEID& type,
    _In_reads_bytes_(cbData) const void* pData,
    _In_ int cbData,
    _Outptr_ HierarchicalSchema** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pData);

    AutoDeletePtr<HierarchicalSchema> pRtrn = new HierarchicalSchema();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(type, nullptr, pData, cbData));

    *result = pRtrn.Detach();
    return S_OK;
}

HierarchicalSchema::~HierarchicalSchema()
{
    delete m_pNames;

    if (m_pVersions != nullptr)
    {
        for (int i = 0; i < m_header.numVersions; i++)
        {
            delete m_pVersions[i];
        }
        Def_Free(m_pVersions);
        m_pVersions = nullptr;
    }

    if (m_pMyBuffer != nullptr)
    {
        Def_Free(m_pMyBuffer);
        m_pMyBuffer = nullptr;
    }
}

const IHierarchicalSchemaVersionInfo* HierarchicalSchema::GetVersionInfo(_In_ int index) const
{
    if ((index < 0) || (index >= m_header.numVersions))
    {
        return nullptr;
    }

    if (m_pVersions == nullptr)
    {
        m_pVersions = _DefArray_AllocZeroed(HierarchicalSchemaVersionInfo*, m_header.numVersions);
        if (m_pVersions == nullptr)
        {
            return nullptr;
        }
    }

    if (m_pVersions[index] == nullptr)
    {
        if (FAILED(HierarchicalSchemaVersionInfo::CreateInstance(&m_pFileVersions[index], &m_pVersions[index])))
        {
            return nullptr;
        }
    }

    return m_pVersions[index];
}

HRESULT
HierarchicalSchema::Clone(_Outptr_ IHierarchicalSchema** result) const
{
    *result = nullptr;

    UINT32 cbData = 0;
    const BYTE* pMyBuffer = GetData(&cbData);
    if (!pMyBuffer)
    {
        return S_OK;
    }

    unique_deffree_ptr<BYTE> pCloneBuffer(_DefArray_AllocZeroed(BYTE, cbData));
    RETURN_IF_NULL_ALLOC(pCloneBuffer);

    CopyMemory(pCloneBuffer.get(), pMyBuffer, cbData);

    HierarchicalSchema* pClone;
    RETURN_IF_FAILED(HierarchicalSchema::CreateInstance(GetSectionType(), pCloneBuffer.get(), cbData, &pClone));

    pClone->m_pMyBuffer = pCloneBuffer.release();
    *result = pClone;

    return S_OK;
}

const DEFFILE_SECTION_TYPEID HierarchicalSchema::GetSectionTypeId() { return gHierarchicalSchemaSectionType; }

const DEFFILE_SECTION_TYPEID HierarchicalSchema::GetExSectionTypeId() { return gHierarchicalSchemaExSectionType; }

HRESULT
HierarchicalSchema::GetSchemaBlobFromFileSection(
    _Inout_opt_ DEFFILE_SECTION_TYPEID* pSectionTypeResult,
    _Inout_opt_ BlobResult* pBlobResult) const
{
    // The fuction will be called for ResourcePack merge only when all added schema version are same
    DEF_ASSERT(m_cbSection != 0);

    if (pSectionTypeResult != nullptr)
    {
        // make sure we get the section type from the file section base rather than
        // the one calculated from flags.
        *pSectionTypeResult = GetSectionType();
    }

    if (pBlobResult != nullptr)
    {
        RETURN_IF_FAILED(pBlobResult->SetRef(m_pSectionData, m_cbSection));
    }

    return S_OK;
}

} // namespace Resources
} // namespace Microsoft
