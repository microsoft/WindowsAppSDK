// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <MddWin11.h>
#include <MddDetourPackageGraph.h>
#include <urfw.h>

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

#include <../Detours/detours.h>

static HRESULT DetoursInitialize()
{
    // Only detour APIs for not-packaged processes
    if (AppModel::Identity::IsPackagedProcess())
    {
        return S_OK;
    }

    // Do we need to detour APIs?
    if (!MddNeedsDetours() && !UrfwNeedsDetours())
    {
        return S_OK;
    }

    // No detours needed in a 'detours helper process'
    if (DetourIsHelperProcess())
    {
        return S_OK;
    }

    // Detour APIs to our implementation
    DetourRestoreAfterWith();
    FAIL_FAST_IF_WIN32_ERROR(DetourTransactionBegin());
    FAIL_FAST_IF_FAILED(MddDetourPackageGraphInitialize());
    FAIL_FAST_IF_FAILED(UrfwInitialize());
    FAIL_FAST_IF_WIN32_ERROR(DetourTransactionCommit());
    return S_OK;
}

static HRESULT DetoursShutdown()
{
    // Only detour APIs for not-packaged processes
    if (AppModel::Identity::IsPackagedProcess())
    {
        return S_OK;
    }

    // Did we detour APIs?
    if (DetourIsHelperProcess())
    {
        return S_OK;
    }

    // Stop Detour'ing APIs to our implementation
    FAIL_FAST_IF_WIN32_ERROR(DetourTransactionBegin());
    FAIL_FAST_IF_WIN32_ERROR(DetourUpdateThread(GetCurrentThread()));
    UrfwShutdown();
    MddDetourPackageGraphShutdown();
    FAIL_FAST_IF_WIN32_ERROR(DetourTransactionCommit());
    return S_OK;
}

// ====== TEMPORARY DIAGNOSTIC LOGGING (remove before final merge) ======
static void DiagLogFrameworkDllMain(PCWSTR phase, HMODULE selfHmodule) noexcept
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
    WCHAR selfPath[MAX_PATH * 2]{};
    ::GetModuleFileNameW(selfHmodule, selfPath, ARRAYSIZE(selfPath));
    WCHAR line[2048]{};
    swprintf_s(line, L"[%02u:%02u:%02u.%03u tid=%lu] FrameworkDLL.DllMain %ls: hmod=0x%p path='%ls'\r\n",
        st.wHour, st.wMinute, st.wSecond, st.wMilliseconds,
        ::GetCurrentThreadId(), phase, selfHmodule, selfPath);
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
        DiagLogFrameworkDllMain(L"DLL_PROCESS_ATTACH begin", hmodule);
        DisableThreadLibraryCalls(hmodule);
        FAIL_FAST_IF_FAILED(MddWin11Initialize());
        FAIL_FAST_IF_FAILED(DetoursInitialize());
        DiagLogFrameworkDllMain(L"DLL_PROCESS_ATTACH end (after DetoursInitialize)", hmodule);
        break;
    }
    case DLL_PROCESS_DETACH:
    {
        DetoursShutdown();
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
