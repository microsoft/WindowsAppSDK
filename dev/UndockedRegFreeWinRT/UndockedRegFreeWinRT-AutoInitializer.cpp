// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <Windows.h>

// Do nothing. Just exist.
//
// This ensures the including PE file has an import reference
// to the WindowsAppSDK runtime DLL and thus gets loaded when
// the including PE file gets loaded.

STDAPI UndockedRegFreeWinRT_EnsureIsLoaded();

// NOTE: Disable optimizations to ensure this unreferenced symbol
//       doesn't get 'optimized away'. We need the end compiled binary
//       to import this symbol from the Windows App SDK runtime DLL.
#pragma optimize("", off)
namespace Microsoft::Windows::Foundation::UndockedRegFreeWinRT
{
static void EnsureIsLoaded()
{
    (void) UndockedRegFreeWinRT_EnsureIsLoaded();
}
}
#pragma optimize("", on)
