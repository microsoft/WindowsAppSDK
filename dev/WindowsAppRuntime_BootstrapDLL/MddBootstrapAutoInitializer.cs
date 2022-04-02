// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

// If any options are defined use them, else use the default
#if !defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_DEFAULT) && \
    !defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_NONE) && \
    !defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONERROR_DEBUGBREAK) && \
    !defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONERROR_DEBUGBREAK_IFDEBUGGERATTACHED) && \
    !defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONERROR_FAILFAST) && \
    !defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONNOMATCH_SHOWUI) && \
    !defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONPACKAGEIDENTITY_NOOP)
// No options specified! Use the default
#define MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_DEFAULT
#endif

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
#if MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_DEFAULT
                // Use the default options
                return global::Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.InitializeOptions.OnNoMatch_ShowUI;
#elif MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_NONE
                // No options!
                return global::Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.InitializeOptions.None;
#else
               // Use the specified options
                var options = global::Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.InitializeOptions.None;
#if MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONERROR_DEBUGBREAK
                options |= global::Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.InitializeOptions.OnError_DebugBreak;
#endif
#if MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONERROR_DEBUGBREAK_IFDEBUGGERATTACHED
                options | global::Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.InitializeOptions.OnError_DebugBreak_IfDebuggerAttached;
#endif
#if MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONERROR_FAILFAST
                options | global::Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.InitializeOptions.OnError_FailFast;
#endif
#if MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONNOMATCH_SHOWUI
                options | global::Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.InitializeOptions.OnNoMatch_ShowUI;
#endif
#if MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONPACKAGEIDENTITY_NOOP
                options | global::Microsoft.Windows.ApplicationModel.DynamicDependency.Bootstrap.InitializeOptions.OnPackageIdentity_NOOP;
#endif
                return options;
#endif
            }
        }
    }
}
