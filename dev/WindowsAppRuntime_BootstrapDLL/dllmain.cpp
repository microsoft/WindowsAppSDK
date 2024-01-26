// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "MddWin11.h"

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD  reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hmodule);
        FAIL_FAST_IF_FAILED(MddWin11Initialize());
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
