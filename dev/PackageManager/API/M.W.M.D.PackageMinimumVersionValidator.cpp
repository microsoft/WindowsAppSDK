#include "pch.h"
#include "M.W.M.D.PackageMinimumVersionValidator.h"
#include "Microsoft.Windows.Management.Deployment.PackageMinimumVersionValidator.g.cpp"
#include <TerminalVelocityFeatures-PackageManager.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageMinimumVersionValidator::PackageMinimumVersionValidator(winrt::Windows::ApplicationModel::PackageVersion const& minimumVersion)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Management::Deployment::Feature_PackageValidator::IsEnabled());

        UNREFERENCED_PARAMETER(minimumVersion);

        throw hresult_not_implemented();
    }
    bool PackageMinimumVersionValidator::IsPackageValid(winrt::Microsoft::Windows::Management::Deployment::AppxPackagingObject const& packagingObject)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Management::Deployment::Feature_PackageValidator::IsEnabled());

        UNREFERENCED_PARAMETER(packagingObject);

        throw hresult_not_implemented();
    }
}
