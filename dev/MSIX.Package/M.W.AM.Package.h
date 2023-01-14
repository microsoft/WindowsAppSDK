// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.ApplicationModel.Package.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    struct Package : PackageT<Package>
    {
        Package() = default;

        Package(winrt::Windows::ApplicationModel::Package const& package);
        static winrt::Microsoft::Windows::ApplicationModel::Package GetCurrent();
        static winrt::Microsoft::Windows::ApplicationModel::Package FindPackage(hstring const& packageFullName);
        static winrt::Microsoft::Windows::ApplicationModel::Package FindPackage(winrt::Windows::System::User const& user, hstring const& packageFullName);
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> FindPackages();
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> FindPackages(hstring const& packageFamilyName);
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> FindPackages(hstring const& packageName, hstring const& packagePublisher);
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> FindPackagesForUser(winrt::Windows::System::User const& user);
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> FindPackagesForUser(winrt::Windows::System::User const& user, hstring const& packageFamilyName);
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> FindPackagesForUser(winrt::Windows::System::User const& user, hstring const& packageName, hstring const& packagePublisher);
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> FindPackagesForUserWithPackageTypes(winrt::Windows::System::User const& user, winrt::Windows::Management::Deployment::PackageTypes const& types);
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> FindPackagesForUserWithPackageTypes(winrt::Windows::System::User const& user, hstring const& packageFamilyName, winrt::Windows::Management::Deployment::PackageTypes const& types);
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> FindPackagesForUserWithPackageTypes(winrt::Windows::System::User const& user, hstring const& packageName, hstring const& packagePublisher, winrt::Windows::Management::Deployment::PackageTypes const& types);
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> FindProvisionedPackages();
        static winrt::Microsoft::Windows::ApplicationModel::Package FindPackageWithOptions(winrt::Microsoft::Windows::ApplicationModel::FindPackageOptions const& options);
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> FindPackagesWithOptions(winrt::Microsoft::Windows::ApplicationModel::FindPackageOptions const& options);
        winrt::Microsoft::Windows::ApplicationModel::PackageDisplayInfo DisplayInfo();
        winrt::Microsoft::Windows::ApplicationModel::PackageLocation Location();
        winrt::Microsoft::Windows::ApplicationModel::PackageIdentity Identity();
        winrt::Microsoft::Windows::ApplicationModel::PackageGraph PackageGraph();
        winrt::Microsoft::Windows::ApplicationModel::PackageInstallInfo Install();
        winrt::Microsoft::Windows::ApplicationModel::PackageApplications Applications();
        winrt::Microsoft::Windows::ApplicationModel::PackageContentGroups ContentGroups();
        winrt::Windows::Management::Deployment::PackageTypes PackageType();
        bool IsMain();
        bool IsFramework();
        bool IsResource();
        bool IsOptional();
        bool IsOptionalInRelatedSet();
        bool IsBundle();
        bool IsDevelopmentMode();
        bool IsStub();
        bool IsSigned();
        winrt::Microsoft::Windows::ApplicationModel::PackageSignatureKind SignatureKind();
        winrt::Microsoft::Windows::ApplicationModel::PackageStatus Status();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::ApplicationModel::PackageUpdateAvailabilityResult> CheckUpdateAvailabilityAsync();
        winrt::Windows::Foundation::IAsyncOperation<bool> SetInUseAsync(bool inUse);
        winrt::Windows::Foundation::IAsyncOperation<bool> VerifyContentIntegrityAsync();
        winrt::Windows::ApplicationModel::Package W_AM_Package();

    private:
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> ToVector(
            winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::ApplicationModel::Package>& packages);
        static winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> ToVector(
            winrt::Windows::Foundation::Collections::IVector<winrt::Windows::ApplicationModel::Package>& packages);

    private:
        winrt::Windows::ApplicationModel::Package m_package;
    };
}
namespace winrt::Microsoft::Windows::ApplicationModel::factory_implementation
{
    struct Package : PackageT<Package, implementation::Package>
    {
    };
}
