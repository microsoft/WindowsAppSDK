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
            int hresult = 0;
            if (!global::Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.TryInitialize(majorMinorVersion, versionTag, minVersion, options, out hresult))
            {
                global::System.Environment.Exit(hr);
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
