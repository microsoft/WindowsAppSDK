// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include <pch.h>

#include "VersionInfo.RuntimeInfo.h"

#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.VersionInfo.RuntimeInfo.g.cpp>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::VersionInfo::implementation
{
    winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::VersionInfo::RuntimeInfo RuntimeInfo::Current()
    {
        const ::Microsoft::WindowsAppSDK::VersionInfo* versionInfo{ ::Microsoft::WindowsAppSDK::GetVersionInfo() };
        return winrt::make<implementation::RuntimeInfo>(versionInfo);
    }
    winrt::Windows::ApplicationModel::PackageVersion RuntimeInfo::Version()
    {
        const auto& version{ m_versionInfo->Runtime.Version };
        return winrt::Windows::ApplicationModel::PackageVersion{ version.Major, version.Minor, version.Build, version.Revision };
    }
    uint64_t RuntimeInfo::VersionUInt64()
    {
        return m_versionInfo->Runtime.Version.UInt64;
    }
    hstring RuntimeInfo::ToString()
    {
        PCWSTR dotQuadString{ m_versionInfo->Runtime.Version.DotQuadString };
        if (dotQuadString && (dotQuadString[0] != '\0'))
        {
            return winrt::hstring{ dotQuadString };
        }
        else
        {
            return winrt::hstring{};
        }
    }
}
