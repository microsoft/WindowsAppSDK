// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.Management.Deployment.PackageMinimumVersionValidator.g.h"

#include <AppxPackaging.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageMinimumVersionValidator : PackageMinimumVersionValidatorT<PackageMinimumVersionValidator>
    {
        PackageMinimumVersionValidator(winrt::Windows::ApplicationModel::PackageVersion const& minimumVersion);
        bool IsPackageValid(winrt::Windows::Foundation::IInspectable const& appxPackagingObject);

    private:
        bool CheckIdentity(IAppxManifestPackageId* packageId);

        UINT64 m_minimumVersion{};
    };
}

namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageMinimumVersionValidator : PackageMinimumVersionValidatorT<PackageMinimumVersionValidator, implementation::PackageMinimumVersionValidator>
    {
    };
}
