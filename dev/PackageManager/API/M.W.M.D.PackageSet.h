// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageSet.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageSet : PackageSetT<PackageSet>
    {
        PackageSet() = default;

        hstring Id();
        void Id(hstring const& value);
        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageSetItem> Items();
        winrt::Windows::Foundation::Uri PackageUri();
        void PackageUri(winrt::Windows::Foundation::Uri const& value);

    private:
        hstring m_id;
        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageSetItem> m_items;
        winrt::Windows::Foundation::Uri m_packageUri{ nullptr };
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageSet : PackageSetT<PackageSet, implementation::PackageSet>
    {
    };
}
