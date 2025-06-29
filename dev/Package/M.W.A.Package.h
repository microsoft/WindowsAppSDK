// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.Package.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct Package
    {
        Package() = default;

        static hstring FindPackageFile(hstring const& packageFullName, hstring const& filename);
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct Package : PackageT<Package, implementation::Package>
    {
    };
}
