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
        return winrt::make<implementation::RuntimeInfo>(*versionInfo);
    }
    winrt::Windows::ApplicationModel::PackageVersion RuntimeInfo::Version()
    {
        throw hresult_not_implemented();
    }
    uint64_t RuntimeInfo::VersionUInt64()
    {
        throw hresult_not_implemented();
    }
    hstring RuntimeInfo::ToString()
    {
        throw hresult_not_implemented();
    }
}
