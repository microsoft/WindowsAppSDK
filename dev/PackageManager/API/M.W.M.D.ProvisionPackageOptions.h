// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.ProvisionPackageOptions.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct ProvisionPackageOptions : ProvisionPackageOptionsT<ProvisionPackageOptions>
    {
        ProvisionPackageOptions() = default;

        bool IsOptionalPackageFamilyNamesSupported();
        winrt::Windows::Foundation::Collections::IVector<hstring> OptionalPackageFamilyNames();
        bool IsProjectionOrderPackageFamilyNamesSupported();
        winrt::Windows::Foundation::Collections::IVector<hstring> ProjectionOrderPackageFamilyNames();

    private:
        winrt::Windows::Foundation::Collections::IVector<hstring> m_optionalPackageFamilyNames;
        winrt::Windows::Foundation::Collections::IVector<hstring> m_projectionOrderPackageFamilyNames;
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct ProvisionPackageOptions : ProvisionPackageOptionsT<ProvisionPackageOptions, implementation::ProvisionPackageOptions>
    {
    };
}
