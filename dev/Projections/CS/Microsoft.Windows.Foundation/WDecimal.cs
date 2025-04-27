// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using Microsoft.Windows.Foundation;

namespace Microsoft.Windows.Foundation
{
    public class WDecimal
    {
        public WDecimal()
        {
        }

        public WDecimal(WDecimal value)
        {
            m_value = value.m_value.ToDecimal();
        }

        public WDecimal(Microsoft.Windows.Foundation.Decimal value)
        {
            m_value = value;
        }

        public static WDecimal operator +(WDecimal left, WDecimal right)
        {
            return new WDecimal(left.m_value.Add(right.m_value));
        }

        private Microsoft.Windows.Foundation.Decimal m_value = new Microsoft.Windows.Foundation.Decimal();
    }

    public static class DecimalExtensions
    {
        //TODO public static Microsoft.Windows.Foundation.Decimal operator +(this Microsoft.Windows.Foundation.Decimal left, Microsoft.Windows.Foundation.Decimal right)
        //TODO {
        //TODO     return left.m_value.Add(right.m_value);
        //TODO }

        public static Microsoft.Windows.Foundation.Decimal Add(this Microsoft.Windows.Foundation.Decimal left, System.Decimal right)
        {
            return left.Add(right);
        }
    }
}
