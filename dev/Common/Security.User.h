// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __SECURITY_USER_H
#define __SECURITY_USER_H

#include <sddl.h>

namespace Security::User
{
inline bool IsLocalSystem(HANDLE token = nullptr)
{
    BYTE localSystemSidBuffer[SECURITY_MAX_SID_SIZE]{};
    PSID localSystemSid{ reinterpret_cast<PSID>(localSystemSidBuffer) };
    DWORD localSystemSidBufferSize{ ARRAYSIZE(localSystemSidBuffer) };
    THROW_IF_WIN32_BOOL_FALSE(CreateWellKnownSid(WinLocalSystemSid, nullptr, localSystemSid, &localSystemSidBufferSize));

    const auto user{ wil::get_token_information<TOKEN_USER>(!token ? GetCurrentThreadEffectiveToken() : token) };
    PSID userSid{ user->User.Sid };

    return !!EqualSid(userSid, localSystemSid);
}

/// @return sid. Allocated via LocalAlloc; use LocalFree to deallocate
inline PSID StringToSid(PCWSTR sidString)
{
    if (!sidString || (sidString[0] == L'\0'))
    {
        return nullptr;
    }

    PSID sid{};
    THROW_IF_WIN32_BOOL_FALSE(::ConvertStringSidToSidW(sidString, &sid));
    return sid;
}

/// @return sid as a string. Allocated via LocalAlloc; use LocalFree to deallocate
inline PWSTR SidToString(PSID sid)
{
    if (!sid)
    {
        return nullptr;
    }

    PWSTR sidString{};
    THROW_IF_WIN32_BOOL_FALSE(::ConvertSidToStringSidW(sid, &sidString));
    return sidString;
}

/// @return a new sid. Allocated via LocalAlloc; use LocalFree to deallocate
inline wil::unique_any_psid CopySid(PSID source)
{
    if (!source)
    {
        return null;
    }

    const auto size{ ::GetLengthSid(source) };
    wil::unique_any_psid copy{ static_cast<PSID>(::LocalAlloc(LMEM_FIXED, size))};
    THROW_IF_NULL_ALLOC(copy);
    THROW_IF_WIN32_BOOL_FALSE(::CopySid(size, copy.get(), source));
    return copy;
}
}

#endif // __SECURITY_USER_H
