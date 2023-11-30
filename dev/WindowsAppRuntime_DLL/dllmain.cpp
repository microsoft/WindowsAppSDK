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

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD  reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hmodule);
        FAIL_FAST_IF_FAILED(MddWin11Initialize());
        FAIL_FAST_IF_FAILED(DetoursInitialize());
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
