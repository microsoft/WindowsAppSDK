// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "MddWin11.h"

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

// ====== TEMPORARY DIAGNOSTIC LOGGING (remove before final merge) ======
static void DiagWriteFromDllMain(PCWSTR phase, PCWSTR detail) noexcept
{
    WCHAR temp[MAX_PATH]{};
    const DWORD chars{ ::GetEnvironmentVariableW(L"TEMP", temp, ARRAYSIZE(temp)) };
    if (chars == 0 || chars >= ARRAYSIZE(temp)) return;
    std::wstring path{ temp };
    path += L"\\preload-debug.log";
    HANDLE h{ ::CreateFileW(path.c_str(), FILE_APPEND_DATA,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
        OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr) };
    if (h == INVALID_HANDLE_VALUE) return;
    SYSTEMTIME st{};
    ::GetSystemTime(&st);
    HMODULE wprt{ ::GetModuleHandleW(L"Microsoft.WindowsAppRuntime.dll") };
    WCHAR wprtPath[MAX_PATH * 2]{};
    if (wprt) { ::GetModuleFileNameW(wprt, wprtPath, ARRAYSIZE(wprtPath)); }
    WCHAR line[2048]{};
    swprintf_s(line, L"[%02u:%02u:%02u.%03u tid=%lu] %ls: %ls (Microsoft.WindowsAppRuntime.dll handle=0x%p path='%ls')\r\n",
        st.wHour, st.wMinute, st.wSecond, st.wMilliseconds,
        ::GetCurrentThreadId(), phase, detail ? detail : L"", wprt, wprt ? wprtPath : L"");
    char narrow[4096]{};
    int n = ::WideCharToMultiByte(CP_UTF8, 0, line, -1, narrow, sizeof(narrow), nullptr, nullptr);
    if (n > 0)
    {
        ::SetFilePointer(h, 0, nullptr, FILE_END);
        DWORD written{};
        ::WriteFile(h, narrow, static_cast<DWORD>(n - 1), &written, nullptr);
    }
    ::CloseHandle(h);
}
// ====== END DIAGNOSTIC ======

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD  reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DiagWriteFromDllMain(L"Bootstrap.dll.DllMain", L"DLL_PROCESS_ATTACH begin");
        DisableThreadLibraryCalls(hmodule);
        FAIL_FAST_IF_FAILED(MddWin11Initialize());
        DiagWriteFromDllMain(L"Bootstrap.dll.DllMain", L"DLL_PROCESS_ATTACH end (after MddWin11Initialize)");
        break;
    }
    case DLL_PROCESS_DETACH:
    {
        MddWin11Shutdown();
        break;
    }
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    }

    // Give WIL a crack at DLLMain processing
    // See DLLMain() in wil/result_macros.h for why
    wil::DLLMain(hmodule, reason, reserved);

    return TRUE;
}
