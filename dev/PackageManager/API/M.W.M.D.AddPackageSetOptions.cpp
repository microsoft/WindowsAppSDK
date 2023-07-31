// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

#include "M.W.M.D.AddPackageSetOptions.h"
#include "Microsoft.Windows.Management.Deployment.AddPackageSetOptions.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageVolume AddPackageSetOptions::TargetVolume()
    {
        return m_targetVolume;
    }
    void AddPackageSetOptions::TargetVolume(winrt::Microsoft::Windows::Management::Deployment::PackageVolume const& value)
    {
        m_targetVolume = value;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> AddPackageSetOptions::DependencyPackageUris()
    {
        return m_dependencyPackageUris;
    }
    winrt::Windows::Foundation::Collections::IVector<hstring> AddPackageSetOptions::OptionalPackageFamilyNames()
    {
        return m_optionalPackageFamilyNames;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> AddPackageSetOptions::OptionalPackageUris()
    {
        return m_optionalPackageUris;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> AddPackageSetOptions::RelatedPackageUris()
    {
        return m_relatedPackageUris;
    }
    winrt::Windows::Foundation::Uri AddPackageSetOptions::ExternalLocationUri()
    {
        return m_externalLocationUri;
    }
    void AddPackageSetOptions::ExternalLocationUri(winrt::Windows::Foundation::Uri const& value)
    {
        m_externalLocationUri = value;
    }
    winrt::Windows::Management::Deployment::StubPackageOption AddPackageSetOptions::StubPackageOption()
    {
        return m_stubPackageOption;
    }
    void AddPackageSetOptions::StubPackageOption(winrt::Windows::Management::Deployment::StubPackageOption const& value)
    {
        m_stubPackageOption = value;
    }
    bool AddPackageSetOptions::AllowUnsigned()
    {
        return m_allowUnsigned;
    }
    void AddPackageSetOptions::AllowUnsigned(bool value)
    {
        m_allowUnsigned = value;
    }
    bool AddPackageSetOptions::DeveloperMode()
    {
        return m_developerMode;
    }
    void AddPackageSetOptions::DeveloperMode(bool value)
    {
        m_developerMode = value;
    }
    bool AddPackageSetOptions::ForceAppShutdown()
    {
        return m_forceAppShutdown;
    }
    void AddPackageSetOptions::ForceAppShutdown(bool value)
    {
        m_forceAppShutdown = value;
    }
    bool AddPackageSetOptions::ForceTargetAppShutdown()
    {
        return m_forceTargetAppShutdown;
    }
    void AddPackageSetOptions::ForceTargetAppShutdown(bool value)
    {
        m_forceTargetAppShutdown = value;
    }
    bool AddPackageSetOptions::ForceUpdateFromAnyVersion()
    {
        return m_forceUpdateFromAnyVersion;
    }
    void AddPackageSetOptions::ForceUpdateFromAnyVersion(bool value)
    {
        m_forceUpdateFromAnyVersion = value;
    }
    bool AddPackageSetOptions::InstallAllResources()
    {
        return m_installAllResources;
    }
    void AddPackageSetOptions::InstallAllResources(bool value)
    {
        m_installAllResources = value;
    }
    bool AddPackageSetOptions::RequiredContentGroupOnly()
    {
        return m_requiredContentGroupOnly;
    }
    void AddPackageSetOptions::RequiredContentGroupOnly(bool value)
    {
        m_requiredContentGroupOnly = value;
    }
    bool AddPackageSetOptions::RetainFilesOnFailure()
    {
        return m_retainFilesOnFailure;
    }
    void AddPackageSetOptions::RetainFilesOnFailure(bool value)
    {
        m_retainFilesOnFailure = value;
    }
    bool AddPackageSetOptions::StageInPlace()
    {
        return m_stageInPlace;
    }
    void AddPackageSetOptions::StageInPlace(bool value)
    {
        m_stageInPlace = value;
    }
    bool AddPackageSetOptions::DeferRegistrationWhenPackagesAreInUse()
    {
        return m_deferRegistrationWhenPackagesAreInUse;
    }
    void AddPackageSetOptions::DeferRegistrationWhenPackagesAreInUse(bool value)
    {
        m_deferRegistrationWhenPackagesAreInUse = value;
    }
    bool AddPackageSetOptions::IsExpectedDigestsSupported()
    {
        // Requires Windows >= 10.0.22621.0 (aka Win11 22H2)
        return WindowsVersion::IsWindows11_22H2OrGreater();
    }
    winrt::Windows::Foundation::Collections::IMap<winrt::Windows::Foundation::Uri, hstring> AddPackageSetOptions::ExpectedDigests()
    {
        return m_expectedDigests;
    }
    bool AddPackageSetOptions::IsLimitToExistingPackagesSupported()
    {
        // Requires Windows >= 10.0.22621.0 (aka Win11 22H2)
        return WindowsVersion::IsWindows11_22H2OrGreater();
    }
    bool AddPackageSetOptions::LimitToExistingPackages()
    {
        return m_limitToExistingPackages;
    }
    void AddPackageSetOptions::LimitToExistingPackages(bool value)
    {
        m_limitToExistingPackages = value;
    }
}
