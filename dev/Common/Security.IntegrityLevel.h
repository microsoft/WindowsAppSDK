// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __SECURITY_INTEGRITYLEVEL_H
#define __SECURITY_INTEGRITYLEVEL_H

namespace Security::IntegrityLevel
{
inline DWORD GetIntegrityLevel(HANDLE token = nullptr)
{
    wistd::unique_ptr<TOKEN_MANDATORY_LABEL> tokenMandatoryLabel{
            wil::get_token_information_failfast<TOKEN_MANDATORY_LABEL>(
                !token ? GetCurrentThreadEffectiveToken() : token) };
    return *GetSidSubAuthority((*tokenMandatoryLabel).Label.Sid,
        static_cast<DWORD>(static_cast<UCHAR>(*GetSidSubAuthorityCount((*tokenMandatoryLabel).Label.Sid) - 1)));
}

inline bool IsElevated(HANDLE token = nullptr)
{
    const auto integrityLevel{ GetIntegrityLevel(token) };
    return integrityLevel >= SECURITY_MANDATORY_HIGH_RID;
}
}

#endif // __SECURITY_INTEGRITYLEVEL_H
