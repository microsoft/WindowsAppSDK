// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.PackageContentGroups.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct PackageContentGroups : PackageContentGroupsT<PackageContentGroups>
    {
        PackageContentGroups() = default;

        PackageContentGroups(winrt::Microsoft::Windows::ApplicationModel::Package const& package);
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::ApplicationModel::PackageContentGroup> GetContentGroupAsync(hstring name);
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::ApplicationModel::PackageContentGroup>> GetContentGroupsAsync();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::ApplicationModel::PackageContentGroup>> StageContentGroups();

    private:
        winrt::Microsoft::Windows::ApplicationModel::Package m_package;
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct PackageContentGroups : PackageContentGroupsT<PackageContentGroups, implementation::PackageContentGroups>
    {
    };
}
