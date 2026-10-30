// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;
using Windows.Foundation;

namespace MrtCoreCsWinRTTests
{
    // CsWinRT 2.x and 3.0 expose TryGetDataUnsafe from different types and with different pointer types.
    internal static class BufferMarshal
    {
        public static unsafe bool TryGetDataUnsafe(IMemoryBufferReference reference, out IntPtr data, out uint capacity)
        {
#if NET10_0_OR_GREATER
            bool result = WindowsRuntime.InteropServices.WindowsRuntimeBufferMarshal.TryGetDataUnsafe(reference, out byte* dataPointer, out capacity);
            data = (IntPtr)dataPointer;
            return result;
#else
            return System.Runtime.InteropServices.WindowsRuntime.WindowsRuntimeMarshal.TryGetDataUnsafe(reference, out data, out capacity);
#endif
        }
    }
}
