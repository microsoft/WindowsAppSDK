#include "pch.h"
#include "M.W.M.D.PackageFamilyNameValidator.h"
#include "Microsoft.Windows.Management.Deployment.PackageFamilyNameValidator.g.cpp"
#include <TerminalVelocityFeatures-PackageManager.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageFamilyNameValidator::PackageFamilyNameValidator(hstring const& expectedPackageFamilyName)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Management::Deployment::Feature_PackageValidator::IsEnabled());

        UNREFERENCED_PARAMETER(expectedPackageFamilyName);

        throw hresult_not_implemented();
    }
    bool PackageFamilyNameValidator::IsPackageValid(winrt::Windows::Foundation::IInspectable const& appxPackagingObject)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Management::Deployment::Feature_PackageValidator::IsEnabled());

        UNREFERENCED_PARAMETER(appxPackagingObject);

        throw hresult_not_implemented();
    }
}
