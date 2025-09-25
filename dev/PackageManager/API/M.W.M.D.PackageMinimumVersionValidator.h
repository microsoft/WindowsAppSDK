#pragma once
#include "Microsoft.Windows.Management.Deployment.PackageMinimumVersionValidator.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageMinimumVersionValidator : PackageMinimumVersionValidatorT<PackageMinimumVersionValidator>
    {
        PackageMinimumVersionValidator() = default;

        PackageMinimumVersionValidator(winrt::Windows::ApplicationModel::PackageVersion const& minimumVersion);
        bool IsPackageValid(winrt::Windows::Foundation::IInspectable const& appxPackagingObject);
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageMinimumVersionValidator : PackageMinimumVersionValidatorT<PackageMinimumVersionValidator, implementation::PackageMinimumVersionValidator>
    {
    };
}
