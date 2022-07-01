// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

// Do nothing. Just exist so consumers can import a reference to ensure the DLL is loaded
STDAPI WindowsAppRuntime_EnsureIsLoaded()
{
    return S_OK;
}
