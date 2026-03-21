// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.Package.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct Package
    {
        Package() = default;

        static bool IsFeatureSupported(winrt::Microsoft::Windows::ApplicationModel::PackageFeature const& feature);
        static hstring GetFilePath(hstring const& filename);
        static hstring GetFilePath(hstring const& filename, hstring const& packageFullName);
        static hstring GetFilePath(hstring const& filename, hstring const& packageFullName, winrt::Microsoft::Windows::ApplicationModel::GetFilePathOptions const& options);
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct Package : PackageT<Package, implementation::Package>
    {
    };
}
