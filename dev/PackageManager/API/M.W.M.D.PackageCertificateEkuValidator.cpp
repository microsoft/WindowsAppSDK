#include "pch.h"
#include "M.W.M.D.PackageCertificateEkuValidator.h"
#include "Microsoft.Windows.Management.Deployment.PackageCertificateEkuValidator.g.cpp"
#include <TerminalVelocityFeatures-PackageManager.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageCertificateEkuValidator::PackageCertificateEkuValidator(hstring const& expectedCertificateEku)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Management::Deployment::Feature_PackageValidator::IsEnabled());

        UNREFERENCED_PARAMETER(expectedCertificateEku);

        throw hresult_not_implemented();
    }
    bool PackageCertificateEkuValidator::IsPackageValid(winrt::Windows::Foundation::IInspectable const& appxPackagingObject)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Management::Deployment::Feature_PackageValidator::IsEnabled());

        UNREFERENCED_PARAMETER(appxPackagingObject);

        throw hresult_not_implemented();
    }
}
