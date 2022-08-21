// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#pragma once

#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfo.RuntimeInfo.g.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::VersionInfo::implementation
{
    struct RuntimeInfo : RuntimeInfoT<RuntimeInfo>
    {
        RuntimeInfo() = default;

        RuntimeInfo(const ::Microsoft::WindowsAppSDK::VersionInfo& versionInfo) :
            m_versionInfo(versionInfo)
        {
        }

        static winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::VersionInfo::RuntimeInfo Current();
        winrt::Windows::ApplicationModel::PackageVersion Version();
        uint64_t VersionUInt64();
        hstring ToString();

    private:
        const ::Microsoft::WindowsAppSDK::VersionInfo& m_versionInfo{};
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::VersionInfo::factory_implementation
{
    struct RuntimeInfo : RuntimeInfoT<RuntimeInfo, implementation::RuntimeInfo>
    {
    };
}
