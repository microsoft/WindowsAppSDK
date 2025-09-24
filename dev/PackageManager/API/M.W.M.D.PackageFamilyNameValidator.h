#pragma once
#include "Microsoft.Windows.Management.Deployment.PackageFamilyNameValidator.g.h"

#include <AppxPackaging.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageFamilyNameValidator : PackageFamilyNameValidatorT<PackageFamilyNameValidator>
    {
        PackageFamilyNameValidator(hstring const& expectedPackageFamilyName);
        bool IsPackageValid(winrt::Windows::Foundation::IInspectable const& appxPackagingObject);

    private:
        bool CheckIdentity(IAppxManifestPackageId* packageId);

        hstring m_packageFamilyName;
    };
}

namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageFamilyNameValidator : PackageFamilyNameValidatorT<PackageFamilyNameValidator, implementation::PackageFamilyNameValidator>
    {
    };
}
