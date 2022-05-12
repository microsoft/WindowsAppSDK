// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System.Reflection;
using System.Runtime.InteropServices;

namespace Microsoft.Windows.Foundation.UndockedRegFreeWinRTCS
{
    internal static class NativeMethods
    {
        [DllImport("Microsoft.WindowsAppRuntime.dll", CharSet = CharSet.Unicode, ExactSpelling = true)]
        internal static extern int UndockedRegFreeWinRT_EnsureIsLoaded();
    }

    class AutoInitialize
    {
        [global::System.Runtime.CompilerServices.ModuleInitializer]
        internal static void AccessWindowsAppSDK()
        {
            // No error handling needed as the target function does nothing (just {return S_OK}).
            // It's the act of calling the function causing the DllImport to load the DLL that
            // matters. This provides the moral equivalent of a native DLL's Import Address
            // Table (IAT) have an entry that's resolved when this module is loaded.
            NativeMethods.UndockedRegFreeWinRT_EnsureIsLoaded();
        }
    }
}
