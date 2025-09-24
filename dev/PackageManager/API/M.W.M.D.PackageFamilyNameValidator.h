#pragma once
#include "Microsoft.Windows.Management.Deployment.PackageFamilyNameValidator.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageFamilyNameValidator : PackageFamilyNameValidatorT<PackageFamilyNameValidator>
    {
        PackageFamilyNameValidator() = default;

        PackageFamilyNameValidator(hstring const& expectedPackageFamilyName);
        bool IsPackageValid(winrt::Microsoft::Windows::Management::Deployment::AppxPackagingObject const& packagingObject);
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageFamilyNameValidator : PackageFamilyNameValidatorT<PackageFamilyNameValidator, implementation::PackageFamilyNameValidator>
    {
    };
}
