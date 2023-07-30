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
        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageSetItem> PackageSetItems();
        void PackageSetItems(winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageSetItem> const& value);
    };
}
