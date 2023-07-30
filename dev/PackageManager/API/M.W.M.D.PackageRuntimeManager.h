// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.PackageRuntimeManager.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageRuntimeManager : PackageRuntimeManagerT<PackageRuntimeManager>
    {
        PackageRuntimeManager() = default;

        static winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager GetDefault();
        void AddPackageSetByIdToPackageGraph(hstring const& packageSetId);
        void AddPackageSetToPackageGraph(winrt::Microsoft::Windows::Management::Deployment::PackageSet const& packageSet);
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageRuntimeManager : PackageRuntimeManagerT<PackageRuntimeManager, implementation::PackageRuntimeManager>
    {
    };
}
