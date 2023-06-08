// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "stdafx.h"

namespace Microsoft::Resources::Build
{

HRESULT
EnvironmentReferenceBuilder::CreateInstance(_In_ const MRMFILE_ENVIRONMENT_REF* pFileRef, _Outptr_ EnvironmentReferenceBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pFileRef);

    EnvironmentReferenceBuilder* pRtrn = new EnvironmentReferenceBuilder();
    RETURN_IF_NULL_ALLOC(pRtrn);
    pRtrn->m_ref = *pFileRef;

    *result = pRtrn;
    return S_OK;
}

HRESULT EnvironmentReferenceBuilder::CreateInstance(_In_ const IEnvironment* pEnvironment, _Outptr_ EnvironmentReferenceBuilder** result)
{
    *result = nullptr;
    RETURN_HR_IF_NULL(E_INVALIDARG, pEnvironment);

    AutoDeletePtr<EnvironmentReferenceBuilder> pRtrn = new EnvironmentReferenceBuilder();
    RETURN_IF_NULL_ALLOC(pRtrn);
    RETURN_IF_FAILED(pRtrn->Init(pEnvironment));

    *result = pRtrn.Detach();
    return S_OK;
}

_Use_decl_annotations_ HRESULT EnvironmentReferenceBuilder::Build(void* pBuffer, size_t cbBuffer, size_t* pcbWrittenOut) const
{
    RETURN_HR_IF_NULL(E_INVALIDARG, pBuffer);
    RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_MRM_INVALID_PRI_FILE), cbBuffer < sizeof(MRMFILE_ENVIRONMENT_REF));

    if (pcbWrittenOut != nullptr)
    {
        *pcbWrittenOut = sizeof(MRMFILE_ENVIRONMENT_REF);
    }

    MRMFILE_ENVIRONMENT_REF* pFileRef = static_cast<MRMFILE_ENVIRONMENT_REF*>(pBuffer);
    *pFileRef = m_ref;
    return S_OK;
}

} // namespace Microsoft::Resources::Build
