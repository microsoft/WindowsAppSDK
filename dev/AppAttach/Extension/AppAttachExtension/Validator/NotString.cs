using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace AppAttachExtension.Validator
{
    public class NotString : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            string strValue = value as string;
            if (string.IsNullOrWhiteSpace(strValue))
            {
                return new ValidationResult(false, "Value cannot be empty");
            }

            double result;
            bool isValid = double.TryParse(strValue, out result);

            return new ValidationResult(isValid, "Value must be a number");
        }
    }
}
