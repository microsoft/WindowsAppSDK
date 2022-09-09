// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.ReleaseInfo.g.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    struct ReleaseInfo
    {
        ReleaseInfo() = default;

        static uint16_t Major();
        static uint16_t Minor();
        static uint16_t Patch();
        static hstring VersionTag();
        static hstring AsString();

    private:
        static const ::Microsoft::WindowsAppSDK::VersionInfo& GetVersionInfo();
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::factory_implementation
{
    struct ReleaseInfo : ReleaseInfoT<ReleaseInfo, implementation::ReleaseInfo>
    {
    };
}
