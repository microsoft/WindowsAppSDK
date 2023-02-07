// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

using namespace winrt::Windows::Foundation;

int APIENTRY wWinMain(
    HINSTANCE /*hInstance*/,
    HINSTANCE /*hPrevInstance*/,
    PWSTR /*pCmdLine*/,
    int /*nCmdShow*/) try
{
    int argc{};
    const wil::unique_hlocal_ptr<PWSTR[]> argv{ CommandLineToArgvW(GetCommandLineW(), &argc) };
    wprintf(L"argc: %d\nargv[0]: %ls\n", argc, argv[0]);

    return S_OK;
}
CATCH_RETURN()
