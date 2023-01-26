// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

using namespace winrt::Windows::Foundation;

int wmain(int /*argc*/, wchar_t* /*argv[]*/) try
{
    return S_OK;
}
CATCH_RETURN()
