// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __SECURITY_INTEGRITYLEVEL_H
#define __SECURITY_INTEGRITYLEVEL_H

namespace Security::IntegrityLevel
{
inline DWORD GetIntegrityLevel(HANDLE token = nullptr)
{
    auto tokenMandatoryLabel{
            wil::get_token_information_failfast<TOKEN_MANDATORY_LABEL>(
                !token ? GetCurrentThreadEffectiveToken() : token) };
    return *GetSidSubAuthority((*tokenMandatoryLabel).Label.Sid,
        static_cast<DWORD>(static_cast<UCHAR>(*GetSidSubAuthorityCount((*tokenMandatoryLabel).Label.Sid) - 1)));
}

inline bool IsIntegrityLevelElevated(const DWORD integrityLevel)
{
    return integrityLevel >= SECURITY_MANDATORY_HIGH_RID;
}

inline bool IsElevated(HANDLE token = nullptr)
{
    const auto integrityLevel{ GetIntegrityLevel(token) };
    return IsIntegrityLevelElevated(integrityLevel);
}

inline PCWSTR ToString(const DWORD integrityLevel)
{
    switch (integrityLevel)
    {
        case SECURITY_MANDATORY_UNTRUSTED_RID:          return L"Untrusted";    // 0x00000000 Untrusted.
        case SECURITY_MANDATORY_LOW_RID:                return L"Low";          // 0x00001000 Low integrity.
        case SECURITY_MANDATORY_MEDIUM_RID:             return L"Medium";       // 0x00002000 Medium integrity.
        case SECURITY_MANDATORY_MEDIUM_PLUS_RID:        return L"MediumPlus";   // SECURITY_MANDATORY_MEDIUM_RID + 0x100 Medium high integrity.
        case SECURITY_MANDATORY_HIGH_RID:               return L"High";         // 0X00003000 High integrity.
        case SECURITY_MANDATORY_SYSTEM_RID:             return L"System";       // 0x00004000 System integrity.
        case SECURITY_MANDATORY_PROTECTED_PROCESS_RID:  return L"ProtectedProcess";
        default:                                        return L"???";
    }
}
}

#endif // __SECURITY_INTEGRITYLEVEL_H
