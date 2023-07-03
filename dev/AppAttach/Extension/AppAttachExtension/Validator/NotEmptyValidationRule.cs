// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System.Globalization;
using System.Windows.Controls;

namespace AppAttachExtension.Validator
{
    public class NotEmptyValidationRule : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            if (string.IsNullOrEmpty((string)value))
            {
                return new ValidationResult(false, "This field is required.");
            }
            return ValidationResult.ValidResult;
        }
    }
}
