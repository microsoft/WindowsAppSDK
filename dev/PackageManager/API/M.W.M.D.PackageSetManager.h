// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageSetManager.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageSetManager : PackageSetManagerT<PackageSetManager>
    {
        PackageSetManager() = default;

        static winrt::Microsoft::Windows::Management::Deployment::PackageSetManager GetDefault();
        void Add(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet);
        void Update(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet);
        void Remove(hstring const& packageSetId);
        winrt::Microsoft::Windows::Management::Deployment::PackageSet Get(hstring const& packageSetId);
        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Management::Deployment::PackageSet> Find(winrt::Microsoft::Windows::Management::Deployment::FindPackageSetOptions const& options);
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageSetManager : PackageSetManagerT<PackageSetManager, implementation::PackageSetManager>
    {
    };
}
