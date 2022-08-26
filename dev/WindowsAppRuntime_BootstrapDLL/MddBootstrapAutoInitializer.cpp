// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <Windows.h>
#include <stdint.h>
#include <stdlib.h>
#include <MddBootstrap.h>
#include <WindowsAppSDK-VersionInfo.h>

// If any options are defined use them, else use the default
#if !defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_DEFAULT)
// Default isn't defined. Define it if no options are defined
#if defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_NONE)
#elif defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONERROR_DEBUGBREAK)
#elif defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONERROR_DEBUGBREAK_IFDEBUGGERATTACHED)
#elif defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONERROR_FAILFAST)
#elif defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONNOMATCH_SHOWUI)
#elif defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONPACKAGEIDENTITY_NOOP)
#else
// No options specified! Use the default
#define MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_DEFAULT
#endif
#endif

namespace Microsoft::Windows::ApplicationModel::DynamicDependency::Bootstrap
{
    struct AutoInitialize
    {
        AutoInitialize()
        {
            Initialize();
        }

        ~AutoInitialize()
        {
            ::MddBootstrapShutdown();
        }

        constexpr static MddBootstrapInitializeOptions Options()
        {
#if defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_DEFAULT)
            // Use the default options
            return MddBootstrapInitializeOptions_OnNoMatch_ShowUI;
#elif defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_NONE)
            // No options!
            return MddBootstrapInitializeOptions_None;
#else
            // Use the specified options
            return MddBootstrapInitializeOptions_None
#if defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONERROR_DEBUGBREAK)
                 | MddBootstrapInitializeOptions_OnError_DebugBreak
#endif
#if defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONERROR_DEBUGBREAK_IFDEBUGGERATTACHED)
                 | MddBootstrapInitializeOptions_OnError_DebugBreak_IfDebuggerAttached
#endif
#if defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONERROR_FAILFAST)
                 | MddBootstrapInitializeOptions_OnError_FailFast
#endif
#if defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONNOMATCH_SHOWUI)
                 | MddBootstrapInitializeOptions_OnNoMatch_ShowUI
#endif
#if defined(MICROSOFT_WINDOWSAPPSDK_BOOTSTRAP_AUTO_INITIALIZE_OPTIONS_ONPACKAGEIDENTITY_NOOP)
                 | MddBootstrapInitializeOptions_OnPackageIdentity_NOOP
#endif
            ;
#endif
        }

        static void Initialize()
        {
            const UINT32 c_majorMinorVersion{ WINDOWSAPPSDK_RELEASE_MAJORMINOR };
            PCWSTR c_versionTag{ WINDOWSAPPSDK_RELEASE_VERSION_TAG_W };
            const PACKAGE_VERSION c_minVersion{ WINDOWSAPPSDK_RUNTIME_VERSION_UINT64 };
            const auto c_options{ Options() };
            const HRESULT hr{ ::MddBootstrapInitialize2(c_majorMinorVersion, c_versionTag, c_minVersion, c_options) };
            if (FAILED(hr))
            {
                exit(hr);
            }
        }
    };
    static AutoInitialize g_autoInitialize;
}
