// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MddDetourPackageGraph.h>
#include <urfw.h>

#include <../Detours/detours.h>

static bool IsPackagedProcess()
{
    UINT32 n{};
    const auto rc = ::GetCurrentPackageFullName(&n, nullptr);
    (void) LOG_HR_IF_MSG(HRESULT_FROM_WIN32(rc), (rc != APPMODEL_ERROR_NO_PACKAGE) && (rc != ERROR_INSUFFICIENT_BUFFER), "GetCurrentPackageFullName rc=%d", rc);
    return rc == ERROR_INSUFFICIENT_BUFFER;
}

static HRESULT DetoursInitialize()
{
    // Only detour APIs for not-packaged processes
    if (IsPackagedProcess())
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
    if (IsPackagedProcess())
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
        FAIL_FAST_IF_FAILED(DetoursInitialize());
        break;
    }
    case DLL_PROCESS_DETACH:
    {
        DetoursShutdown();
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
