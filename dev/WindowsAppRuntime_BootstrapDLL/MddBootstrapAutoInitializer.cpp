// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <Windows.h>
#include <stdint.h>
#include <MddBootstrap.h>
#include <WindowsAppSDK-VersionInfo.h>
#include <intrin.h>

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
            const PACKAGE_VERSION c_minVersion{WINDOWSAPPSDK_RUNTIME_VERSION_UINT64};
            const HRESULT hr{::MddBootstrapInitialize(WINDOWSAPPSDK_RELEASE_MAJORMINOR, WINDOWSAPPSDK_RELEASE_VERSION_TAG_W, c_minVersion)};
            if (FAILED(hr))
            {
                __fastfail(hr);
            }
        }
    };
    static AutoInitialize g_autoInitialize;
}