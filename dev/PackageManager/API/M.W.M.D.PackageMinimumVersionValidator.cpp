#include "pch.h"
#include "M.W.M.D.PackageMinimumVersionValidator.h"
#include "Microsoft.Windows.Management.Deployment.PackageMinimumVersionValidator.g.cpp"
#include <TerminalVelocityFeatures-PackageManager.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageMinimumVersionValidator::PackageMinimumVersionValidator(winrt::Windows::ApplicationModel::PackageVersion const& minimumVersion)
    {
        m_minimumVersion = ::AppModel::Identity::PackageVersion{ minimumVersion }.Version;
    }

    bool PackageMinimumVersionValidator::IsPackageValid(winrt::Windows::Foundation::IInspectable const& appxPackagingObject)
    {
        winrt::com_ptr<IAppxPackageReader> packageReader;
        winrt::com_ptr<IAppxBundleReader> bundleReader;

        if (SUCCEEDED(appxPackagingObject.as(IID_PPV_ARGS(&packageReader))))
        {
            winrt::com_ptr<IAppxManifestReader> manifestReader;
            THROW_IF_FAILED(packageReader->GetManifest(manifestReader.put()));

            winrt::com_ptr<IAppxManifestPackageId> packageId;
            THROW_IF_FAILED(manifestReader->GetPackageId(packageId.put()));

            return CheckIdentity(packageId.get());
        }
        else if (SUCCEEDED(appxPackagingObject.as(IID_PPV_ARGS(&bundleReader))))
        {
            winrt::com_ptr<IAppxBundleManifestReader> manifestReader;
            THROW_IF_FAILED(bundleReader->GetManifest(manifestReader.put()));

            winrt::com_ptr<IAppxManifestPackageId> packageId;
            THROW_IF_FAILED(manifestReader->GetPackageId(packageId.put()));

            return CheckIdentity(packageId.get());
        }
        else
        {
            THROW_WIN32(ERROR_NOT_SUPPORTED);
        }
    }

    bool PackageMinimumVersionValidator::CheckIdentity(IAppxManifestPackageId* packageId)
    {
        UINT64 version;
        THROW_IF_FAILED(packageId->GetVersion(&version));

        return (version >= m_minimumVersion);
    }
}
