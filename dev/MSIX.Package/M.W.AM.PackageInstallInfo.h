// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.PackageInstallInfo.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct PackageInstallInfo : PackageInstallInfoT<PackageInstallInfo>
    {
        PackageInstallInfo() = default;

        PackageInstallInfo(winrt::Microsoft::Windows::ApplicationModel::Package const& package);
        winrt::Windows::Foundation::DateTime WhenFirstRegisteredForUser();
        winrt::Windows::Foundation::DateTime WhenLastRegisteredForUser();
        winrt::Windows::ApplicationModel::AppInstallerInfo GetAppInstallerInfo();
        hstring SourceUriSchemeName();

    private:
        winrt::Microsoft::Windows::ApplicationModel::Package m_package;
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct PackageInstallInfo : PackageInstallInfoT<PackageInstallInfo, implementation::PackageInstallInfo>
    {
    };
}
