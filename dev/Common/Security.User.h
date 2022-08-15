// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __SECURITY_USER_H
#define __SECURITY_USER_H

namespace Security::User
{
inline bool IsLocalSystem(HANDLE token = nullptr)
{
    BYTE localSystemSidBuffer[ SECURITY_MAX_SID_SIZE ];
    PSID localSystemSid{ reinterpret_cast<PSID>(localSystemSidBuffer) };
    DWORD localSystemSidBufferSize{ ARRAYSIZE(localSystemSidBuffer) };
    THROW_IF_WIN32_BOOL_FALSE(CreateWellKnownSid(WinLocalSystemSid, nullptr, localSystemSid, &localSystemSidBufferSize));

    wistd::unique_ptr<TOKEN_USER> user{
        wil::get_token_information<TOKEN_USER>(
            !token ? GetCurrentThreadEffectiveToken() : token) };
    PSID userSid{ user->User.Sid };

    return !!EqualSid(userSid, localSystemSid);
}
}

#endif // __SECURITY_USER_H
