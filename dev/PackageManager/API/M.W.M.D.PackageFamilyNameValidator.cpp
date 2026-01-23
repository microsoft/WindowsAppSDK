// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageFamilyNameValidator.h"
#include "Microsoft.Windows.Management.Deployment.PackageFamilyNameValidator.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageFamilyNameValidator::PackageFamilyNameValidator(hstring const& expectedPackageFamilyName)
    {
        m_packageFamilyName = expectedPackageFamilyName;
    }

    bool PackageFamilyNameValidator::IsPackageValid(winrt::Windows::Foundation::IInspectable const& appxPackagingObject)
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

    bool PackageFamilyNameValidator::CheckIdentity(IAppxManifestPackageId* packageId)
    {
        wil::unique_cotaskmem_string familyName;
        THROW_IF_FAILED(packageId->GetPackageFamilyName(&familyName));

        if (CSTR_EQUAL == CompareStringOrdinal(familyName.get(), -1, m_packageFamilyName.c_str(), -1, TRUE))
        {
            return true;
        }
        else
        {
            std::ignore = LOG_HR_MSG(HRESULT_FROM_WIN32(ERROR_BAD_FORMAT), "FamilyName=%ws", familyName.get());
            return false;
        }
    }
}
