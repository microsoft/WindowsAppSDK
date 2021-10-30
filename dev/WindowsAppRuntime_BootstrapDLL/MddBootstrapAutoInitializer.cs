// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

namespace Microsoft.Windows.ApplicationModel.DynamicDependency.BootstrapCS
{
    class AutoInitialize
    {
        [global::System.Runtime.CompilerServices.ModuleInitializer]
        internal static void AccessWindowsAppSDK()
        {
            uint majorMinorVersion = global::Microsoft.WindowsAppSDK.Release.MajorMinor;
            string versionTag = global::Microsoft.WindowsAppSDK.Release.VersionTag;
            var minVersion = new PackageVersion(global::Microsoft.WindowsAppSDK.Runtime.Version.UInt64);
            try
            {
                global::Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.Initialize(majorMinorVersion, versionTag, minVersion);
            }
            catch (global::System.Exception e)
            {
                global::System.Environment.FailFast(e.Message);
            }
        }
    }
}
