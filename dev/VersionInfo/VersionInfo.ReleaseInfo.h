// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfo.ReleaseInfo.g.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::VersionInfo::implementation
{
    struct ReleaseInfo : ReleaseInfoT<ReleaseInfo>
    {
        ReleaseInfo() = default;

        ReleaseInfo(const ::Microsoft::WindowsAppSDK::VersionInfo& versionInfo) :
            m_versionInfo(versionInfo)
        {
        }

        static winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::VersionInfo::ReleaseInfo Current();
        uint16_t Major();
        uint16_t Minor();
        uint16_t Patch();
        uint32_t MajorMinor();
        hstring Channel();
        hstring VersionTag();
        hstring VersionShortTag();
        hstring FormattedVersionTag();
        hstring FormattedVersionShortTag();
        hstring ToString();

    private:
        const ::Microsoft::WindowsAppSDK::VersionInfo& m_versionInfo{};
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::VersionInfo::factory_implementation
{
    struct ReleaseInfo : ReleaseInfoT<ReleaseInfo, implementation::ReleaseInfo>
    {
    };
}
