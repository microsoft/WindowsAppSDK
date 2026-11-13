// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if CSWINRT3_0
namespace MrtCoreCsWinRTTests
{
    // CsWinRT 3.0 only generates WinRT.Interop.dll and the type map attributes for executables,
    // so the CsWinRT 3.0 test assembly is built as an Exe. TAEF loads it as a library; Main is never called.
    internal static class Program
    {
        private static void Main()
        {
        }
    }
}
#endif
