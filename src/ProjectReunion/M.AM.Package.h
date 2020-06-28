#pragma once
#include "Microsoft.ApplicationModel.Package.g.h"

namespace winrt::Microsoft::ApplicationModel::implementation
{
    struct Package : PackageT<Package>
    {
        Package() = default;

        Package(Windows::ApplicationModel::Package const& package);
        static Microsoft::ApplicationModel::Package GetCurrent();
        static Microsoft::ApplicationModel::Package FindPackage(hstring const& packageFullName);
        static Microsoft::ApplicationModel::Package FindPackage(Windows::System::User const& user, hstring const& packageFullName);
        static Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> FindPackages();
        static Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> FindPackages(hstring const& packagFamilyName);
        static Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> FindPackages(hstring const& packageName, hstring const& packagePublisher);
        static Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> FindPackagesForUser(Windows::System::User const& user);
        static Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> FindPackagesForUser(Windows::System::User const& user, hstring const& packagFamilyName);
        static Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> FindPackagesForUser(Windows::System::User const& user, hstring const& packageName, hstring const& packagePublisher);
        static Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> FindPackagesForUserWithPackageTypes(Windows::System::User const& user, Windows::Management::Deployment::PackageTypes const& types);
        static Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> FindPackagesForUserWithPackageTypes(Windows::System::User const& user, hstring const& packagFamilyName, Windows::Management::Deployment::PackageTypes const& types);
        static Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> FindPackagesForUserWithPackageTypes(Windows::System::User const& user, hstring const& packageName, hstring const& packagePublisher, Windows::Management::Deployment::PackageTypes const& types);
        static Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> FindProvisionedPackages();
        static Microsoft::ApplicationModel::Package FindPackageWithOptions(Microsoft::ApplicationModel::FindPackageOptions const& options);
        static Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> FindPackagesWithOptions(Microsoft::ApplicationModel::FindPackageOptions const& options);
        Microsoft::ApplicationModel::PackageDisplayInfo DisplayInfo();
        Microsoft::ApplicationModel::PackageLocation Location();
        Microsoft::ApplicationModel::PackageIdentity Identity();
        Microsoft::ApplicationModel::PackageGraph PackageGraph();
        Microsoft::ApplicationModel::PackageInstallInfo Install();
        Microsoft::ApplicationModel::PackageApplications Applications();
        Microsoft::ApplicationModel::PackageContentGroups ContentGroups();
        Windows::Management::Deployment::PackageTypes PackageType();
        bool IsMain();
        bool IsFramework();
        bool IsResource();
        bool IsOptional();
        bool IsOptionalInRelatedSet();
        bool IsBundle();
        bool IsDevelopmentMode();
        bool IsStub();
        Windows::ApplicationModel::PackageSignatureKind SignatureKind();
        Windows::ApplicationModel::PackageStatus Status();
        Windows::Foundation::IAsyncOperation<Windows::ApplicationModel::PackageUpdateAvailabilityResult> CheckUpdateAvailabilityAsync();
        Windows::Foundation::IAsyncOperation<bool> SetInUseAsync(bool inUse);
        Windows::Foundation::IAsyncOperation<bool> VerifyContentIntegrityAsync();

    private:
        Windows::ApplicationModel::Package m_package;
    };
}
namespace winrt::Microsoft::ApplicationModel::factory_implementation
{
    struct Package : PackageT<Package, implementation::Package>
    {
    };
}
