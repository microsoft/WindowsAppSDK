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
            var options = Options;
            try
            {
                global::Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.Initialize(majorMinorVersion, versionTag, minVersion, options);
            }
            catch (global::System.Exception e)
            {
                global::System.Environment.FailFast(e.Message);
            }
        }

        internal static global::Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.InitializeOptions Options
        {
            get
            {
#ifdef MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTOINITIALIZER_OPTIONS_OVERRIDE
                return Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.AutoInitializer.InitializeOptions.Override.GetDefault();
#else
                return Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.InitializeOptions.OnNoMatch_ShowUI;
#endif
            }
        }
    }
}
