// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System.Globalization;
using System.Linq;
using System.Windows.Data;

namespace AppAttachExtension.Validator
{
    public class NextEnable : IMultiValueConverter
    {
        public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {

            return values.Where(x => (x is string && string.IsNullOrEmpty(x.ToString())) || (x is bool && !(bool)x))?.Count() == 0;
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
