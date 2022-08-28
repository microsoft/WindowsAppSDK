// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <Windows.h>
#include <wil/resource.h>
#include <wil/result.h>
#include <processthreadsapi.h>


namespace Security::Descriptors
{
    wil::unique_any_psid GetCurrentProcessSid()
    {
        wil::unique_any_psid result;
        wil::unique_process_heap_ptr<TOKEN_GROUPS> tg;
        DWORD length = 0;
        if (!::GetTokenInformation(
            ::GetCurrentProcessToken(),
            TokenLogonSid,
            nullptr,
            0,
            &length))
        {
            auto err = ::GetLastError();
            if (err != ERROR_INSUFFICIENT_BUFFER)
            {
                THROW_WIN32(err);
            }
            tg.reset(static_cast<TOKEN_GROUPS*>(::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, length)));
        }
        THROW_IF_WIN32_BOOL_FALSE(::GetTokenInformation(
            ::GetCurrentProcessToken(),
            TokenLogonSid,
            tg.get(),
            length,
            &length));

        auto sidLength = ::GetLengthSid(tg->Groups[0].Sid);
        result.reset(::HeapAlloc(::GetProcessHeap(), 0, sidLength));
        THROW_IF_WIN32_BOOL_FALSE(::CopySid(
            sidLength, result.get(), tg->Groups[0].Sid));
        return result;
    }
}
