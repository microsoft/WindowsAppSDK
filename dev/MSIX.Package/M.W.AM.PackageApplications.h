// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.PackageApplications.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct PackageApplications : PackageApplicationsT<PackageApplications>
    {
        PackageApplications() = default;

        PackageApplications(winrt::Microsoft::Windows::ApplicationModel::Package const& package);
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::ApplicationModel::Core::AppListEntry> GetAppListEntries();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::ApplicationModel::Core::AppListEntry>> GetAppListEntriesAsync();

    private:
        winrt::Microsoft::Windows::ApplicationModel::Package m_package;
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct PackageApplications : PackageApplicationsT<PackageApplications, implementation::PackageApplications>
    {
    };
}
