// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;
using System.Runtime.CompilerServices;

using Microsoft.Windows.Foundation;

namespace Microsoft.Windows.Foundation
{
    public static class DecimalExtensions
    {
        /// Return a WinRT DecimalValue structure.
        public static Microsoft.Windows.Foundation.DecimalValue ToDecimalValue(this decimal d)
        {
            // decimal.GetBits() returns a binary representation of a Decimal. The return value is an
            // integer array with four elements. Elements 0, 1, and 2 contain the low,
            // middle, and high 32 bits of the 96-bit integer part of the Decimal.
            // Element 3 contains the scale factor and sign of the Decimal: bits 0-15
            // (the lower word) are unused; bits 16-23 contain a value between 0 and
            // 28, indicating the power of 10 to divide the 96-bit integer part by to
            // produce the Decimal value; bits 24-30 are unused; and finally bit 31
            // indicates the sign of the Decimal value, 0 meaning positive and 1
            // meaning negative.
            //   [0] = (int)d.Low;
            //   [1] = (int)d.Mid;
            //   [2] = (int)d.High;
            //   [3] = d._flags;
            // where d._flags is 2 bytes reserved, 1 byte sign, 1 byte scale
            //
            // @see https://github.com/dotnet/runtime/blob/1d1bf92fcf43aa6981804dc53c5174445069c9e4/src/libraries/System.Private.CoreLib/src/System/Decimal.cs#L581C13-L581C80

            Span<int> bits = stackalloc int[4];
            decimal.GetBits(d, bits);

            var decimalValue = new Microsoft.Windows.Foundation.DecimalValue();
            decimalValue.Sign = (byte)((bits[3] & 0x80000000) >> 24);
            decimalValue.Scale = (byte)((bits[3] & 0x00FF0000) >> 16);
            decimalValue.Hi32 = (uint)bits[2];
            ulong low32 = (ulong)bits[0];
            ulong mid32 = (ulong)bits[1];
            decimalValue.Lo64 = ((low32 << 32) | mid32);
            return decimalValue;
        }

        /// Return a C# Decimal object.
        public static decimal FromDecimalValue(this decimal d, Microsoft.Windows.Foundation.DecimalValue value)
        {
            int low32 = (int)(value.Lo64 & 0x00000000FFFFFFFF);
            int mid32 = (int)((value.Lo64 >> 32) & 0x00000000FFFFFFFF);
            return new decimal(low32, mid32, (int)value.Hi32, value.Sign != 0, value.Scale);
        }
    }
}
