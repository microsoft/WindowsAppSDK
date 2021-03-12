// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD  reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hmodule);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    // Give WIL a crack at DLLMain processing
    // See DLLMain() in wil/result_macros.h for why
    wil::DLLMain(hmodule, reason, reserved);

    return TRUE;
}
