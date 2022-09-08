// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeInfo.g.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    struct RuntimeInfo
    {
        RuntimeInfo() = default;

        static winrt::Windows::ApplicationModel::PackageVersion Version();
        static hstring AsString();

    private:
        static const ::Microsoft::WindowsAppSDK::VersionInfo& GetVersionInfo();
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::factory_implementation
{
    struct RuntimeInfo : RuntimeInfoT<RuntimeInfo, implementation::RuntimeInfo>
    {
    };
}
