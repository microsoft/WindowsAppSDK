// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfo.ReleaseInfo.g.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::VersionInfo::implementation
{
    struct ReleaseInfo : ReleaseInfoT<ReleaseInfo>
    {
        ReleaseInfo() = default;

        ReleaseInfo(const ::Microsoft::WindowsAppSDK::VersionInfo* versionInfo) :
            m_versionInfo(versionInfo)
        {
        }

        static winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::VersionInfo::ReleaseInfo Current();
        uint16_t Major();
        void Major(uint16_t value);
        uint16_t Minor();
        void Minor(uint16_t value);
        uint16_t Patch();
        void Patch(uint16_t value);
        uint32_t MajorMinor();
        void MajorMinor(uint32_t value);
        hstring Channel();
        void Channel(hstring const& value);
        hstring VersionTag();
        void VersionTag(hstring const& value);
        hstring VersionShortTag();
        void VersionShortTag(hstring const& value);
        hstring FormattedVersionTag();
        void FormattedVersionTag(hstring const& value);
        hstring FormattedVersionShortTag();
        void FormattedVersionShortTag(hstring const& value);
        hstring ToString();

    private:
        const ::Microsoft::WindowsAppSDK::VersionInfo* m_versionInfo{};
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::VersionInfo::factory_implementation
{
    struct ReleaseInfo : ReleaseInfoT<ReleaseInfo, implementation::ReleaseInfo>
    {
    };
}
