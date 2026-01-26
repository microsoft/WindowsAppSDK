// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.Management.Deployment.PackageCertificateEkuValidator.g.h"

#include <AppxPackaging.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageCertificateEkuValidator : PackageCertificateEkuValidatorT<PackageCertificateEkuValidator>
    {
        PackageCertificateEkuValidator(hstring const& expectedCertificateEku);
        bool IsPackageValid(winrt::Windows::Foundation::IInspectable const& appxPackagingObject);

    private:
        bool CheckSignature(IAppxFile* signatureFile);

        hstring m_expectedEku{};
    };
}

namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageCertificateEkuValidator : PackageCertificateEkuValidatorT<PackageCertificateEkuValidator, implementation::PackageCertificateEkuValidator>
    {
    };
}
