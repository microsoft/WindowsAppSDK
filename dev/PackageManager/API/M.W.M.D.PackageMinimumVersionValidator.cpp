// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageMinimumVersionValidator.h"
#include "Microsoft.Windows.Management.Deployment.PackageMinimumVersionValidator.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageMinimumVersionValidator::PackageMinimumVersionValidator(winrt::Windows::ApplicationModel::PackageVersion const& minimumVersion)
    {
        m_minimumVersion = ::AppModel::Identity::PackageVersion{ minimumVersion }.Version;
    }

    bool PackageMinimumVersionValidator::IsPackageValid(winrt::Windows::Foundation::IInspectable const& appxPackagingObject)
    {
        winrt::com_ptr<IAppxPackageReader> packageReader;
        if (SUCCEEDED(appxPackagingObject.as(IID_PPV_ARGS(&packageReader))))
        {
            winrt::com_ptr<IAppxManifestReader> manifestReader;
            THROW_IF_FAILED(packageReader->GetManifest(manifestReader.put()));

            winrt::com_ptr<IAppxManifestPackageId> packageId;
            THROW_IF_FAILED(manifestReader->GetPackageId(packageId.put()));

            return CheckIdentity(packageId.get());
        }

        winrt::com_ptr<IAppxBundleReader> bundleReader;
        if (SUCCEEDED(appxPackagingObject.as(IID_PPV_ARGS(&bundleReader))))
        {
            winrt::com_ptr<IAppxBundleManifestReader> manifestReader;
            THROW_IF_FAILED(bundleReader->GetManifest(manifestReader.put()));

            winrt::com_ptr<IAppxManifestPackageId> packageId;
            THROW_IF_FAILED(manifestReader->GetPackageId(packageId.put()));

            return CheckIdentity(packageId.get());
        }

        THROW_HR(APPX_E_CORRUPT_CONTENT);
    }

    bool PackageMinimumVersionValidator::CheckIdentity(IAppxManifestPackageId* packageId)
    {
        UINT64 version{};
        THROW_IF_FAILED(packageId->GetVersion(&version));

        if (version >= m_minimumVersion)
        {
            return true;
        }
        else
        {
            std::ignore = LOG_HR_MSG(HRESULT_FROM_WIN32(ERROR_BAD_FORMAT), "Version=0x%016llX", version);
            return false;
        }
    }
}
