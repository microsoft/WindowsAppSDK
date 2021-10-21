// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System.Runtime.CompilerServices;
using Microsoft.WindowsAppSDK;
using Microsoft.WindowsAppSDK.Runtime;

namespace Microsoft.Windows.ApplicationModel.DynamicDependency.BootstrapCS
{
    class AutoInitialize
    {
        [ModuleInitializer]
        internal static void AccessWindowsAppSDK()
        {
            if (Assembly.GetEntryAssembly() != Assembly.GetExecutingAssembly())
            {
                return;
            }   

            var minVersion = new PackageVersion(Version.UInt64);
            try
            {
                Bootstrap.Initialize(Release.MajorMinor, Release.VersionTag, minVersion);
            }
            catch (global::System.Exception e)
            {
                global::System.Environment.FailFast(e.Message);
            }
        }
    }
}
