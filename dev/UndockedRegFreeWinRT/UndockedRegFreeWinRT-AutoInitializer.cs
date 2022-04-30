// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

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
            int hr = NativeMethods.UndockedRegFreeWinRT_EnsureIsLoaded();
            if (hr < 0)
            {
                global::System.Environment.Exit(hr);
            }
        }
    }
}
