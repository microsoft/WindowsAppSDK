// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;
using System.Collections.Generic;

namespace WindowsAppSDK.Cpp.Extension
{
    public static class NuGetPackageList
    {
        public static readonly List<string> Packages = new List<string>
        {
            "Microsoft.WindowsAppSDK",
            "Microsoft.Windows.CppWinRT",
            "Microsoft.Windows.SDK.BuildTools",
            "Microsoft.Windows.ImplementationLibrary",
        };
    }
}
