// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "VersionInfo.RuntimeInfo.h"

#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeInfo.g.cpp>

#include <TerminalVelocityFeatures-VersionInfo.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    winrt::Windows::ApplicationModel::PackageVersion RuntimeInfo::Version()
    {
        const auto& version{ GetVersionInfo().Runtime.Version };
        return winrt::Windows::ApplicationModel::PackageVersion{ version.Major, version.Minor, version.Build, version.Revision };
    }
    hstring RuntimeInfo::AsString()
    {
        PCWSTR dotQuadString{ GetVersionInfo().Runtime.Version.DotQuadString };
        if (dotQuadString && (dotQuadString[0] != '\0'))
        {
            return winrt::hstring{ dotQuadString };
        }
        else
        {
            return winrt::hstring{};
        }
    }

    const ::Microsoft::WindowsAppSDK::VersionInfo& RuntimeInfo::GetVersionInfo()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::Feature_VersionInfoAPI::IsEnabled());

        const ::Microsoft::WindowsAppSDK::VersionInfo* versionInfo{ ::Microsoft::WindowsAppSDK::GetVersionInfo() };
        return *versionInfo;
    }
}
