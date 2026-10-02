// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"
#include "mrm/readers/References.h"

using namespace Microsoft::Resources::Build;

namespace Microsoft::Resources
{

HRESULT ResourceReference::Set(_In_ size_t cbBlob, _In_reads_bytes_(cbBlob) const void* pBlob)
{
    m_cbBlob = cbBlob;
    m_pHeader = nullptr;
    m_pOrigin = nullptr;
    m_pPayload = nullptr;

    const MRM_REFERENCE_BLOB* pHeader = reinterpret_cast<const MRM_REFERENCE_BLOB*>(pBlob);

    if (cbBlob >= sizeof(MRM_REFERENCE_BLOB) && (pHeader->cbTotal <= cbBlob))
    {
        // Adjust our total size to what the blob header says
        cbBlob = pHeader->cbTotal;

        SectionParser data;
        // Don't need to report details about why the blob is invalid, just that it is.
        RETURN_HR_IF(E_INVALIDARG, FAILED(data.Set(pBlob, static_cast<UINT32>(cbBlob))));

        HRESULT hr = S_OK;
        m_pHeader = _SECTION_PARSER_NEXT(data, MRM_REFERENCE_BLOB, &hr);
        RETURN_HR_IF(E_INVALIDARG, FAILED(hr));

        if (m_pHeader->cchOriginName > 0)
        {
            m_pOrigin = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->cchOriginName, WCHAR, &hr);
            data.GetPadBytes(4, &hr, nullptr);
        }

        if (m_pHeader->cbPayload > 0)
        {
            m_pPayload = _SECTION_PARSER_NEXT_ARRAY(data, m_pHeader->cbPayload, BYTE, &hr);
            data.GetPadBytes(4, &hr, nullptr);
        }
        RETURN_HR_IF(E_INVALIDARG, FAILED(hr));
    }
    else
    {
        return E_INVALIDARG;
    }

    RETURN_HR_IF(E_INVALIDARG, FAILED(ValidateReferenceBlob()));

    return S_OK;
}

HRESULT ResourceReference::ValidateReferenceBlob()
{
    bool ok = true;
    // Can't be too big.
    ok = ok && (m_pHeader->cbTotal <= kMaxBlobSizeInBytes);

    // If an origin is defined, pOrigin must also be defined
    // If no origin is defined, pOrigin must be nullptr
    ok = ok && (HasOrigin() == (m_pOrigin != nullptr));

    // Must have a payload
    ok = ((m_pHeader->flags & fMrmRefPayload_ValidPayloadFlags) != 0) && (m_pPayload != nullptr);

    // Can't have any undefined flags set
    ok = ok && ((m_pHeader->flags & ~(fMrmRefPayload_ValidPayloadFlags | fMrmRefType_ValidOriginFlags)) == 0);

    // Index payload must be an non-negative integer
    if (PayloadIsResourceIndex())
    {
        ok = ok && (m_pHeader->cbPayload == sizeof(INT32));
        ok = ok && ((*reinterpret_cast<const INT32*>(m_pPayload)) >= 0);
    }

    // If anything is wrong, report INVALID_ARG.  It's up to the caller to translate that into
    // something more meaningful.
    if (!ok)
    {
        return E_INVALIDARG;
    }

    return S_OK;
}

HRESULT ResourceReference::ResolveAsString(
    _In_opt_ IUnifiedResourceView* pManager,
    _In_opt_ IResolver* pContext,
    _Inout_ StringResult* pStringOut) const
{
    // Fail if we have no header, or if we're called without a resource manager for non-literal blob
    if (m_pHeader == nullptr)
    {
        return E_DEF_NOT_READY;
    }

    // If our payload is literal, just return it.
    if (PayloadIsLiteral())
    {
        BlobResult blob;
        RETURN_IF_FAILED(blob.SetRef(m_pPayload, m_pHeader->cbPayload));
        RETURN_IF_FAILED(GetStringResultFromBlobResult(&blob, DEFSTRING_ENCODING_UTF16, pStringOut));

        return S_OK;
    }

    // From this point on we need a resource manager and context
    // to figure things out.   Report an error if either is missing.
    if ((pManager == nullptr) || (pContext == nullptr))
    {
        return E_MRM_MANAGER_REQUIRED;
    }

    const IResourceMapBase* pMap = nullptr;

    // if our reference specifies an origin, make sure it's legit for our manager
    if (m_pOrigin != nullptr)
    {
        if (OriginIsPackage())
        {
            RETURN_IF_FAILED(pManager->GetResourceMapById(m_pOrigin, &pMap));
        }
        else if ((m_pHeader->flags & fMrmRefType_FileOrigin) != 0)
        {
            // File-based references not supported for now.
            return E_NOTIMPL;
        }
    }
    else
    {
        RETURN_IF_FAILED(pManager->GetPrimaryResourceMap(&pMap));
    }

    if (pMap == nullptr)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_MAP_NOT_FOUND);
    }

    // Okay, we have our resource map (i.e. origin).   Now let's find the resource
    BlobResult payload;
    RETURN_IF_FAILED(payload.SetRef(m_pPayload, m_pHeader->cbPayload));

    NamedResourceResult resource;

    if (PayloadIsResourceName())
    {
        StringResult resourceName;

        RETURN_IF_FAILED(GetStringResultFromBlobResult(&payload, DEFSTRING_ENCODING_UTF16, &resourceName));
        RETURN_IF_FAILED(pMap->GetResource(resourceName.GetRef(), &resource));
    }
    else if (PayloadIsResourceIndex())
    {
        INT32 index;

        if (payload.GetSize() < sizeof(index))
        {
            return HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
        }

        index = *reinterpret_cast<const INT32*>(payload.GetRef(nullptr));

        RETURN_IF_FAILED(pMap->GetResourceByIndex(index, &resource));
    }
    else
    {
        return HRESULT_FROM_WIN32(ERROR_BAD_ENVIRONMENT);
    }

    // If we get here successfully, we should have a resource.  Now resolve it.
    DecisionResult decision;
    QualifierSetResult qualifierSet;
    ResourceCandidateResult candidate;
    int resultIndex;

    RETURN_IF_FAILED(resource.GetDecision(&decision));
    RETURN_IF_FAILED(pContext->EvaluateDecision(&decision, &resultIndex, &qualifierSet));
    RETURN_IF_FAILED(resource.GetCandidate(resultIndex, &candidate));

    bool isMatch = false;
    bool isDefault = false;
    bool isMatchAsDefault = false;
    RETURN_IF_FAILED(pContext->EvaluateQualifierSet(&qualifierSet, &isMatch, &isDefault, &isMatchAsDefault, nullptr));

    if (!isMatch && !isDefault)
    {
        return HRESULT_FROM_WIN32(ERROR_MRM_NO_MATCH_OR_DEFAULT_CANDIDATE);
    }

    if (!candidate.TryGetStringValue(pStringOut))
    {
        return E_MRM_BAD_ITEM_TYPE;
    }

    return S_OK;
}

bool ReferenceBuilder::TryGetOnlyValue(_In_ const NamedResourceResult* pResource, _Inout_ StringResult* pResultOut)
{
    int numCandidates = pResource->GetNumCandidates();

    if (numCandidates == 1)
    {
        ResourceCandidateResult candidate;
        QualifierSetResult qualifiers;

        // If we have exactly one candidate which is either default or neutral,
        // then that must be our result.  Just save it as a literal.
        if (SUCCEEDED(pResource->GetCandidate(0, &candidate)) && SUCCEEDED(candidate.GetQualifiers(&qualifiers)) &&
            qualifiers.GetIsNeutralOrDefault() && candidate.TryGetStringValue(pResultOut))
        {
            return true;
        }
    }

    // We don't have a single default or neutral value (or an error occured)
    return false;
}

HRESULT ReferenceBuilder::BuildReferenceBlob(
    _In_ UINT16 flags,
    _In_opt_ PCWSTR pszOriginIn,
    _In_ size_t cbPayloadIn,
    _In_reads_bytes_opt_(cbPayload) const VOID* pPayloadIn,
    _Inout_ BlobResult* pBlobOut)
{
    size_t cbBlob = sizeof(MRM_REFERENCE_BLOB);

    // If context is non-null, flags must specify a reference.
    // If conttext is null, flags must not specify a reference
    // If cbPayload is > 0, pPayload must be non-null
    // If cbPayload is 0, pPayload must be null
    if (((pszOriginIn != nullptr) != ResourceReference::HasOrigin(flags)) || ((pPayloadIn != nullptr) != (cbPayloadIn > 0)))
    {
        return E_INVALIDARG;
    }

    size_t cchOrigin = 0;
    size_t cbOrigin = 0;
    if (ResourceReference::HasOrigin(flags))
    {
        cchOrigin = wcslen(pszOriginIn) + 1;
        cbOrigin = _DEFFILE_PAD((cchOrigin * sizeof(WCHAR)), BaseFile::Align32Bit);
        cbBlob += cbOrigin;
    }

    size_t cbPayloadPadded = _DEFFILE_PAD(cbPayloadIn, BaseFile::Align32Bit);
    cbBlob += cbPayloadPadded;

    // check all three so we don't get fooled by an integer overflow
    if ((cbBlob > ResourceReference::kMaxBlobSizeInBytes) || (cbOrigin > ResourceReference::kMaxBlobSizeInBytes) ||
        (cbPayloadPadded > ResourceReference::kMaxBlobSizeInBytes))
    {
        return HRESULT_FROM_WIN32(ERROR_RANGE_NOT_FOUND);
    }

    // We've verified parameters & computed sizes.  Let's get our blob.
    RETURN_IF_FAILED(pBlobOut->SetEmptyContents(cbBlob));

    void* pBuf = pBlobOut->GetWritableRef(nullptr);

    // Now set up pointers to the header, context & payload
    SectionBuilderParser data;

    // range checked above so cast is safe
    RETURN_IF_FAILED(data.Set(pBuf, static_cast<UINT32>(cbBlob)));

    // Header
    HRESULT hr = S_OK;
    MRM_REFERENCE_BLOB* pHeader = _SECTION_BUILDER_NEXT(data, MRM_REFERENCE_BLOB, &hr);

    // followed by padded origin, if present.
    WCHAR* pszOrigin = ((cchOrigin > 0) ? _SECTION_BUILDER_NEXT_ARRAY(data, static_cast<UINT32>(cchOrigin), WCHAR, &hr) : nullptr);
    _SECTION_BUILDER_PAD(&data, BaseFile::Align32Bit, &hr);

    // followed by padded payload, if present.
    BYTE* pPayload = ((cbPayloadPadded > 0) ? _SECTION_BUILDER_NEXT_ARRAY(data, static_cast<UINT32>(cbPayloadPadded), BYTE, &hr) : nullptr);
    _SECTION_BUILDER_PAD(&data, BaseFile::Align32Bit, &hr);

    // Make sure the blob initialized correctly
    RETURN_IF_FAILED(hr);

    _Analysis_assume_(pHeader != nullptr);

    pHeader->flags = flags;
    pHeader->cbTotal = static_cast<UINT16>(cbBlob);
    pHeader->cchOriginName = static_cast<UINT16>(cchOrigin);
    pHeader->cbPayload = static_cast<UINT16>(cbPayloadIn);

    if (pszOrigin != nullptr)
    {
        RETURN_IF_FAILED(DefString_CchCopy(pszOrigin, cchOrigin, pszOriginIn));
    }

    if (pPayload != nullptr)
    {
        CopyMemory(pPayload, pPayloadIn, cbPayloadIn);
    }
    return S_OK;
}

HRESULT ReferenceBuilder::GetExternalReferenceBlob(
    _In_ UINT16 originFlags,
    _In_ PCWSTR pOrigin,
    _In_ const NamedResourceResult* pResource,
    _Inout_ BlobResult* pBlobOut)
{
    RETURN_IF_FAILED(pBlobOut->SetRef(nullptr, 0));

    // Don't check for only value - external reference means that the referenced file
    // might change without our blob being updated.

    StringResult name;
    RETURN_IF_FAILED(pResource->GetResourceName(&name));

    size_t cbName = (wcslen(name.GetRef()) + 1) * sizeof(WCHAR);
    return BuildReferenceBlob(originFlags | ResourceReference::fMrmRefPayload_ResourceName, pOrigin, cbName, name.GetRef(), pBlobOut);
}

HRESULT ReferenceBuilder::GetInternalReferenceBlob(_In_ const NamedResourceResult* pResource, _Inout_ BlobResult* pBlobOut)
{
    RETURN_IF_FAILED(pBlobOut->SetRef(nullptr, 0));

    // Safe to turn the result into a literal when possible
    // as internal reference means that our blob is expired
    // if the refrenced map ever changes.
    StringResult str;
    if (TryGetOnlyValue(pResource, &str))
    {
        return GetLiteralBlob(str.GetRef(), pBlobOut);
    }

    UINT32 index = pResource->GetResourceIndexInSchema();

    return BuildReferenceBlob(
        ResourceReference::fMrmRefType_UnspecifiedOrigin | ResourceReference::fMrmRefPayload_ResourceIndex,
        nullptr,
        sizeof(index),
        &index,
        pBlobOut);
}

} // namespace Microsoft::Resources