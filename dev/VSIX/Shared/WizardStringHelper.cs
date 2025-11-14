// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

namespace WindowsAppSDK.TemplateUtilities
{
    internal class WizardStringHelper
    {
        internal static string Format(string format, params object[] args)
        {
            return string.Format(format, args);
        }
    }
}