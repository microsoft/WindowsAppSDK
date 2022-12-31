// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.PackageIdentity.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct PackageIdentity : PackageIdentityT<PackageIdentity>
    {
        PackageIdentity() = default;

        PackageIdentity(winrt::Microsoft::Windows::ApplicationModel::Package const& package);
        static hstring FormatPackageFullName(hstring const& packagename, winrt::Windows::ApplicationModel::PackageVersion const& version, winrt::Windows::System::ProcessorArchitecture const& architecture, hstring const& resourceId, hstring const& publisher);
        static hstring FormatPackageFullNameGivenPublisherId(hstring const& packagename, winrt::Windows::ApplicationModel::PackageVersion const& version, winrt::Windows::System::ProcessorArchitecture const& architecture, hstring const& resourceId, hstring const& publisherId);
        static winrt::Microsoft::Windows::ApplicationModel::PackageIdentity ParsePackageFullName(hstring const& packageFullName);
        static hstring FormatPackageFamilyName(hstring const& packageFullName);
        static hstring FormatPackageFamilyName(hstring const& packagename, hstring const& publisher);
        static hstring FormatPackageFamilyNameGivenPublisherId(hstring const& packagename, hstring const& publisherId);
        static winrt::Microsoft::Windows::ApplicationModel::PackageFamilyIdentity ParsePackageFamilyName(hstring const& packageFamilyName);
        static bool VerifyPackageId(hstring const& packagename, winrt::Windows::ApplicationModel::PackageVersion const& version, winrt::Windows::System::ProcessorArchitecture const& architecture, hstring const& resourceId, hstring const& publisher);
        static bool VerifyPackageIdGivenPublisherId(hstring const& packagename, winrt::Windows::ApplicationModel::PackageVersion const& version, winrt::Windows::System::ProcessorArchitecture const& architecture, hstring const& resourceId, hstring const& publisherId);
        static bool VerifyPackageFullName(hstring const& packageFullName);
        static bool VerifyPackageFamilyName(hstring const& packageFullName);
        hstring Name();
        winrt::Windows::ApplicationModel::PackageVersion Version();
        winrt::Windows::System::ProcessorArchitecture Architecture();
        hstring ResouceId();
        hstring Publisher();
        hstring PublisherId();
        hstring PackageFullName();
        hstring PackageFamilyName();

    private:
        winrt::Microsoft::Windows::ApplicationModel::Package m_package;
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct PackageIdentity : PackageIdentityT<PackageIdentity, implementation::PackageIdentity>
    {
    };
}
