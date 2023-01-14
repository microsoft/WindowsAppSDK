// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>

#include "M.W.AM.Package.h"

#include "Microsoft.Windows.ApplicationModel.Package.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::implementation
{
    Package::Package(winrt::Windows::ApplicationModel::Package const& package) :
        m_package(package)
    {
    }
    winrt::Microsoft::Windows::ApplicationModel::Package Package::GetCurrent()
    {
        return winrt::Microsoft::Windows::ApplicationModel::Package(winrt::Windows::ApplicationModel::Package::Current());
    }
    winrt::Microsoft::Windows::ApplicationModel::Package Package::FindPackage(hstring const& packageFullName)
    {
        auto packageManager{ winrt::Windows::Management::Deployment::PackageManager() };
        auto package{ packageManager.FindPackage(packageFullName) };
        return winrt::Microsoft::Windows::ApplicationModel::Package(package);
    }
    winrt::Microsoft::Windows::ApplicationModel::Package Package::FindPackage(winrt::Windows::System::User const& /*user*/, hstring const& packageFullName)
    {
        auto packageManager{ winrt::Windows::Management::Deployment::PackageManager() };
        //TODO convert user to string
        auto package{ packageManager.FindPackageForUser(/*user*/ winrt::hstring(), packageFullName) };
        return winrt::Microsoft::Windows::ApplicationModel::Package(package);
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> Package::FindPackages()
    {
        auto packageManager{ winrt::Windows::Management::Deployment::PackageManager() };
        auto packages{ packageManager.FindPackages() };
        return ToVector(packages);
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> Package::FindPackages(hstring const& packageFamilyName)
    {
        auto packageManager{ winrt::Windows::Management::Deployment::PackageManager() };
        auto packages{ packageManager.FindPackages(packageFamilyName) };
        return ToVector(packages);
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> Package::FindPackages(hstring const& packageName, hstring const& packagePublisher)
    {
        auto packageManager{ winrt::Windows::Management::Deployment::PackageManager() };
        auto packages{ packageManager.FindPackages(packageName, packagePublisher) };
        return ToVector(packages);
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> Package::FindPackagesForUser(winrt::Windows::System::User const& /*user*/)
    {
        auto packageManager{ winrt::Windows::Management::Deployment::PackageManager() };
        //TODO convert user to string
        auto packages{ packageManager.FindPackagesForUser(/*user*/ winrt::hstring()) };
        return ToVector(packages);
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> Package::FindPackagesForUser(winrt::Windows::System::User const& /*user*/, hstring const& packageFamilyName)
    {
        auto packageManager{ winrt::Windows::Management::Deployment::PackageManager() };
        //TODO convert user to string
        auto packages{ packageManager.FindPackagesForUser(/*user*/ winrt::hstring(), packageFamilyName) };
        return ToVector(packages);
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> Package::FindPackagesForUser(winrt::Windows::System::User const& /*user*/, hstring const& packageName, hstring const& packagePublisher)
    {
        auto packageManager{ winrt::Windows::Management::Deployment::PackageManager() };
        //TODO convert user to string
        auto packages{ packageManager.FindPackagesForUser(/*user*/ winrt::hstring(), packageName, packagePublisher) };
        return ToVector(packages);
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> Package::FindPackagesForUserWithPackageTypes(winrt::Windows::System::User const& /*user*/, winrt::Windows::Management::Deployment::PackageTypes const& types)
    {
        auto packageManager{ winrt::Windows::Management::Deployment::PackageManager() };
        //TODO convert user to string
        auto packages{ packageManager.FindPackagesForUserWithPackageTypes(/*user*/ winrt::hstring(), types) };
        return ToVector(packages);
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> Package::FindPackagesForUserWithPackageTypes(winrt::Windows::System::User const& /*user*/, hstring const& packageFamilyName, winrt::Windows::Management::Deployment::PackageTypes const& types)
    {
        auto packageManager{ winrt::Windows::Management::Deployment::PackageManager() };
        //TODO convert user to string
        auto packages{ packageManager.FindPackagesForUserWithPackageTypes(/*user*/ winrt::hstring(), packageFamilyName, types) };
        return ToVector(packages);
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> Package::FindPackagesForUserWithPackageTypes(winrt::Windows::System::User const& /*user*/, hstring const& packageName, hstring const& packagePublisher, winrt::Windows::Management::Deployment::PackageTypes const& types)
    {
        auto packageManager{ winrt::Windows::Management::Deployment::PackageManager() };
        //TODO convert user to string
        auto packages{ packageManager.FindPackagesForUserWithPackageTypes(/*user*/ winrt::hstring(), packageName, packagePublisher, types) };
        return ToVector(packages);
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> Package::FindProvisionedPackages()
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::ApplicationModel::Package Package::FindPackageWithOptions(winrt::Microsoft::Windows::ApplicationModel::FindPackageOptions const& /*options*/)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> Package::FindPackagesWithOptions(winrt::Microsoft::Windows::ApplicationModel::FindPackageOptions const& /*options*/)
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::ApplicationModel::PackageDisplayInfo Package::DisplayInfo()
    {
        return winrt::Microsoft::Windows::ApplicationModel::PackageDisplayInfo(*this);
    }
    winrt::Microsoft::Windows::ApplicationModel::PackageLocation Package::Location()
    {
        return winrt::Microsoft::Windows::ApplicationModel::PackageLocation(*this);
    }
    winrt::Microsoft::Windows::ApplicationModel::PackageIdentity Package::Identity()
    {
        return winrt::Microsoft::Windows::ApplicationModel::PackageIdentity(*this);
    }
    winrt::Microsoft::Windows::ApplicationModel::PackageGraph Package::PackageGraph()
    {
        return winrt::Microsoft::Windows::ApplicationModel::PackageGraph(*this);
    }
    winrt::Microsoft::Windows::ApplicationModel::PackageInstallInfo Package::Install()
    {
        return winrt::Microsoft::Windows::ApplicationModel::PackageInstallInfo(*this);
    }
    winrt::Microsoft::Windows::ApplicationModel::PackageApplications Package::Applications()
    {
        return winrt::Microsoft::Windows::ApplicationModel::PackageApplications(*this);
    }
    winrt::Microsoft::Windows::ApplicationModel::PackageContentGroups Package::ContentGroups()
    {
        return winrt::Microsoft::Windows::ApplicationModel::PackageContentGroups(*this);
    }
    winrt::Windows::Management::Deployment::PackageTypes Package::PackageType()
    {
        if (IsFramework())
        {
            return winrt::Windows::Management::Deployment::PackageTypes::Framework;
        }
        else if (IsResource())
        {
            return winrt::Windows::Management::Deployment::PackageTypes::Resource;
        }
        else if (IsOptional())
        {
            return winrt::Windows::Management::Deployment::PackageTypes::Optional;
        }
        else if (IsBundle())
        {
            return winrt::Windows::Management::Deployment::PackageTypes::Bundle;
        }
        else
        {
            return winrt::Windows::Management::Deployment::PackageTypes::Main;
        }
    }
    bool Package::IsMain()
    {
        return PackageType() == winrt::Windows::Management::Deployment::PackageTypes::Main;
    }
    bool Package::IsFramework()
    {
        return m_package.IsFramework();
    }
    bool Package::IsResource()
    {
        return m_package.IsResourcePackage();
    }
    bool Package::IsOptional()
    {
        return m_package.IsOptional();
    }
    bool Package::IsOptionalInRelatedSet()
    {
        throw hresult_not_implemented();
    }
    bool Package::IsBundle()
    {
        return m_package.IsBundle();
    }
    bool Package::IsDevelopmentMode()
    {
        return m_package.IsDevelopmentMode();
    }
    bool Package::IsStub()
    {
        //? winrt::com_ptr<abi::winrt::Windows::ApplicationModel::IPackage9> ptr{ m_package.as<abi::winrt::Windows::ApplicationModel::IPackage9>() };
        throw hresult_not_implemented();
    }
    bool Package::IsSigned()
    {
        return SignatureKind() != winrt::Microsoft::Windows::ApplicationModel::PackageSignatureKind::None;
    }
    winrt::Microsoft::Windows::ApplicationModel::PackageSignatureKind Package::SignatureKind()
    {
        return static_cast<winrt::Microsoft::Windows::ApplicationModel::PackageSignatureKind>(m_package.SignatureKind());
    }
    winrt::Microsoft::Windows::ApplicationModel::PackageStatus Package::Status()
    {
        return winrt::Microsoft::Windows::ApplicationModel::PackageStatus{ m_package.Status() };
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::ApplicationModel::PackageUpdateAvailabilityResult> Package::CheckUpdateAvailabilityAsync()
    {
        return m_package.CheckUpdateAvailabilityAsync();
    }
    winrt::Windows::Foundation::IAsyncOperation<bool> Package::SetInUseAsync(bool inUse)
    {
        return m_package.SetInUseAsync(inUse);
    }
    winrt::Windows::Foundation::IAsyncOperation<bool> Package::VerifyContentIntegrityAsync()
    {
        return m_package.VerifyContentIntegrityAsync();
    }
    winrt::Windows::ApplicationModel::Package Package::W_AM_Package()
    {
        return m_package;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> Package::ToVector(
        winrt::Windows::Foundation::Collections::IIterable<winrt::Windows::ApplicationModel::Package>& packages)
    {
        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> vector;
        packages.as(vector);
        return vector;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> Package::ToVector(
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::ApplicationModel::Package>& packages)
    {
        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ApplicationModel::Package> vector{ winrt::single_threaded_vector<winrt::Microsoft::Windows::ApplicationModel::Package>() };
        for (auto package : packages)
        {
            vector.Append(winrt::Microsoft::Windows::ApplicationModel::Package(package));
        }
        return vector;
    }
}
