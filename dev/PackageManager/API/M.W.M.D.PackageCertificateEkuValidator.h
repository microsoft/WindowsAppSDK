#pragma once
#include "Microsoft.Windows.Management.Deployment.PackageCertificateEkuValidator.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageCertificateEkuValidator : PackageCertificateEkuValidatorT<PackageCertificateEkuValidator>
    {
        PackageCertificateEkuValidator() = default;

        PackageCertificateEkuValidator(hstring const& expectedCertificateEku);
        bool IsPackageValid(winrt::Microsoft::Windows::Management::Deployment::AppxPackagingObject const& packagingObject);
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageCertificateEkuValidator : PackageCertificateEkuValidatorT<PackageCertificateEkuValidator, implementation::PackageCertificateEkuValidator>
    {
    };
}
