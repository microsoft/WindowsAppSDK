// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <Windows.h>
#include <stdint.h>
#include <stdlib.h>
#include <MddBootstrap.h>
#include <WindowsAppSDK-VersionInfo.h>

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

        static void Initialize()
        {
            const UINT32 c_majorMinorVersion{ WINDOWSAPPSDK_RELEASE_MAJORMINOR };
            PCWSTR c_versionTag{ WINDOWSAPPSDK_RELEASE_VERSION_TAG_W };
            const PACKAGE_VERSION c_minVersion{ WINDOWSAPPSDK_RUNTIME_VERSION_UINT64 };
            const auto c_options{ MddBootstrapInitializeOptions_OnNoMatch_ShowUI };
            const HRESULT hr{ ::MddBootstrapInitialize2(c_majorMinorVersion, c_versionTag, c_minVersion, c_options) };
            if (FAILED(hr))
            {
                exit(hr);
            }
        }
    };
    static AutoInitialize g_autoInitialize;
}
