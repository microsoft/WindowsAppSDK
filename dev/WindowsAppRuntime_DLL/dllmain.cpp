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

static bool g_isDetoursInitialized{};

static HRESULT DetoursInitialize()
{
    // We only use Detours for downlevel support for RegFree WinRT,
    // Dynamic Dependencies and (some) Package Graph functionality.
    //
    // URFW is required where OS RegFree WinRT doesn't exist (RS5).
    //
    // Detours is required by Dynamic Dependency's polyfill implementation.
    // Unecessary when delegating to the OS Dynamic Dependency API
    // (discoverable via MddCore::Win11::IsSupported() in dev\DynamicDependency\API\MddWin11.h).
    //
    // PackageGraph detours are required by Dynamic Dependency's polyfill implementation.
    //
    // QED IsDetoursNeeded == (OS <= RS5) or (not MddCore::Win11::IsSupported())
    //
    // BUT as we've always run with URFW enabled we'll be paranoid for now and always use Detours
    // and URFW when Dynamic Dependency doesn't delegate to the OS API (i.e. when WinAppSDK Dynamic Dependency
    // implementation does polyfill, which will never be on systems lacking OS RegFree WinRT).
    //
    if (MddCore::Win11::IsSupported())
    {
        // No need for Detours
        return S_OK;
    }

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
    g_isDetoursInitialized = true;
    return S_OK;
}

static HRESULT DetoursShutdown()
{
    // Did we detour APIs?
    if (!g_isDetoursInitialized)
    {
        return S_OK;
    }

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
    g_isDetoursInitialized = false;
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
