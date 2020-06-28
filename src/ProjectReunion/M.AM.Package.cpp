#include "pch.h"
#include "M.AM.Package.h"

namespace winrt::Microsoft::ApplicationModel::implementation
{
    Package::Package(Windows::ApplicationModel::Package const& package) :
        m_package(package)
    {
    }
    Microsoft::ApplicationModel::Package Package::GetCurrent()
    {
        return Microsoft::ApplicationModel::Package(Windows::ApplicationModel::Package::Current());
    }
    Microsoft::ApplicationModel::Package Package::FindPackage(hstring const& packageFullName)
    {
        throw hresult_not_implemented();
    }
    Microsoft::ApplicationModel::Package Package::FindPackage(Windows::System::User const& user, hstring const& packageFullName)
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> Package::FindPackages()
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> Package::FindPackages(hstring const& packagFamilyName)
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> Package::FindPackages(hstring const& packageName, hstring const& packagePublisher)
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> Package::FindPackagesForUser(Windows::System::User const& user)
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> Package::FindPackagesForUser(Windows::System::User const& user, hstring const& packagFamilyName)
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> Package::FindPackagesForUser(Windows::System::User const& user, hstring const& packageName, hstring const& packagePublisher)
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> Package::FindPackagesForUserWithPackageTypes(Windows::System::User const& user, Windows::Management::Deployment::PackageTypes const& types)
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> Package::FindPackagesForUserWithPackageTypes(Windows::System::User const& user, hstring const& packagFamilyName, Windows::Management::Deployment::PackageTypes const& types)
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> Package::FindPackagesForUserWithPackageTypes(Windows::System::User const& user, hstring const& packageName, hstring const& packagePublisher, Windows::Management::Deployment::PackageTypes const& types)
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> Package::FindProvisionedPackages()
    {
        throw hresult_not_implemented();
    }
    Microsoft::ApplicationModel::Package Package::FindPackageWithOptions(Microsoft::ApplicationModel::FindPackageOptions const& options)
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::Collections::IVector<Microsoft::ApplicationModel::Package> Package::FindPackagesWithOptions(Microsoft::ApplicationModel::FindPackageOptions const& options)
    {
        throw hresult_not_implemented();
    }
    Microsoft::ApplicationModel::PackageDisplayInfo Package::DisplayInfo()
    {
        return Microsoft::ApplicationModel::PackageDisplayInfo(*this);
    }
    Microsoft::ApplicationModel::PackageLocation Package::Location()
    {
        return Microsoft::ApplicationModel::PackageLocation(*this);
    }
    Microsoft::ApplicationModel::PackageIdentity Package::Identity()
    {
        return Microsoft::ApplicationModel::PackageIdentity(*this);
    }
    Microsoft::ApplicationModel::PackageGraph Package::PackageGraph()
    {
        return Microsoft::ApplicationModel::PackageGraph(*this);
    }
    Microsoft::ApplicationModel::PackageInstallInfo Package::Install()
    {
        return Microsoft::ApplicationModel::PackageInstallInfo(*this);
    }
    Microsoft::ApplicationModel::PackageApplications Package::Applications()
    {
        return Microsoft::ApplicationModel::PackageApplications(*this);
    }
    Microsoft::ApplicationModel::PackageContentGroups Package::ContentGroups()
    {
        return Microsoft::ApplicationModel::PackageContentGroups(*this);
    }
    Windows::Management::Deployment::PackageTypes Package::PackageType()
    {
        if (IsFramework())
        {
            return Windows::Management::Deployment::PackageTypes::Framework;
        }
        else if (IsResource())
        {
            return Windows::Management::Deployment::PackageTypes::Resource;
        }
        else if (IsOptional())
        {
            return Windows::Management::Deployment::PackageTypes::Optional;
        }
        else if (IsBundle())
        {
            return Windows::Management::Deployment::PackageTypes::Bundle;
        }
        else
        {
            return Windows::Management::Deployment::PackageTypes::Main;
        }
    }
    bool Package::IsMain()
    {
        return PackageType() == Windows::Management::Deployment::PackageTypes::Main;
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
        throw hresult_not_implemented();
    }
    Windows::ApplicationModel::PackageSignatureKind Package::SignatureKind()
    {
        return m_package.SignatureKind();
    }
    Windows::ApplicationModel::PackageStatus Package::Status()
    {
        return m_package.Status();
    }
    Windows::Foundation::IAsyncOperation<Windows::ApplicationModel::PackageUpdateAvailabilityResult> Package::CheckUpdateAvailabilityAsync()
    {
        return m_package.CheckUpdateAvailabilityAsync();
    }
    Windows::Foundation::IAsyncOperation<bool> Package::SetInUseAsync(bool inUse)
    {
        return m_package.SetInUseAsync(inUse);
    }
    Windows::Foundation::IAsyncOperation<bool> Package::VerifyContentIntegrityAsync()
    {
        return m_package.VerifyContentIntegrityAsync();
    }
}
