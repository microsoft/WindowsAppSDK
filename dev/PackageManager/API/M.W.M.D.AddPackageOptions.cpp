// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

#include "M.W.M.D.AddPackageOptions.h"
#include "Microsoft.Windows.Management.Deployment.AddPackageOptions.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageVolume AddPackageOptions::TargetVolume()
    {
        return m_targetVolume;
    }
    void AddPackageOptions::TargetVolume(winrt::Microsoft::Windows::Management::Deployment::PackageVolume const& value)
    {
        m_targetVolume = value;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> AddPackageOptions::DependencyPackageUris()
    {
        if (!m_dependencyPackageUris)
        {
            m_dependencyPackageUris = winrt::single_threaded_vector<winrt::Windows::Foundation::Uri>();
        }
        return m_dependencyPackageUris;
    }
    winrt::Windows::Foundation::Collections::IVector<hstring> AddPackageOptions::OptionalPackageFamilyNames()
    {
        if (!m_optionalPackageFamilyNames)
        {
            m_optionalPackageFamilyNames = winrt::single_threaded_vector<hstring>();
        }
        return m_optionalPackageFamilyNames;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> AddPackageOptions::OptionalPackageUris()
    {
        if (!m_optionalPackageUris)
        {
            m_optionalPackageUris = winrt::single_threaded_vector<winrt::Windows::Foundation::Uri>();
        }
        return m_optionalPackageUris;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> AddPackageOptions::RelatedPackageUris()
    {
        if (!m_relatedPackageUris)
        {
            m_relatedPackageUris = winrt::single_threaded_vector<winrt::Windows::Foundation::Uri>();
        }
        return m_relatedPackageUris;
    }
    winrt::Windows::Foundation::Uri AddPackageOptions::ExternalLocationUri()
    {
        return m_externalLocationUri;
    }
    void AddPackageOptions::ExternalLocationUri(winrt::Windows::Foundation::Uri const& value)
    {
        m_externalLocationUri = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::StubPackageOption AddPackageOptions::StubPackageOption()
    {
        return m_stubPackageOption;
    }
    void AddPackageOptions::StubPackageOption(winrt::Microsoft::Windows::Management::Deployment::StubPackageOption const& value)
    {
        m_stubPackageOption = value;
    }
    bool AddPackageOptions::AllowUnsigned()
    {
        return m_allowUnsigned;
    }
    void AddPackageOptions::AllowUnsigned(bool value)
    {
        m_allowUnsigned = value;
    }
    bool AddPackageOptions::DeveloperMode()
    {
        return m_developerMode;
    }
    void AddPackageOptions::DeveloperMode(bool value)
    {
        m_developerMode = value;
    }
    bool AddPackageOptions::ForceAppShutdown()
    {
        return m_forceAppShutdown;
    }
    void AddPackageOptions::ForceAppShutdown(bool value)
    {
        m_forceAppShutdown = value;
    }
    bool AddPackageOptions::ForceTargetAppShutdown()
    {
        return m_forceTargetAppShutdown;
    }
    void AddPackageOptions::ForceTargetAppShutdown(bool value)
    {
        m_forceTargetAppShutdown = value;
    }
    bool AddPackageOptions::ForceUpdateFromAnyVersion()
    {
        return m_forceUpdateFromAnyVersion;
    }
    void AddPackageOptions::ForceUpdateFromAnyVersion(bool value)
    {
        m_forceUpdateFromAnyVersion = value;
    }
    bool AddPackageOptions::InstallAllResources()
    {
        return m_installAllResources;
    }
    void AddPackageOptions::InstallAllResources(bool value)
    {
        m_installAllResources = value;
    }
    bool AddPackageOptions::RequiredContentGroupOnly()
    {
        return m_requiredContentGroupOnly;
    }
    void AddPackageOptions::RequiredContentGroupOnly(bool value)
    {
        m_requiredContentGroupOnly = value;
    }
    bool AddPackageOptions::RetainFilesOnFailure()
    {
        return m_retainFilesOnFailure;
    }
    void AddPackageOptions::RetainFilesOnFailure(bool value)
    {
        m_retainFilesOnFailure = value;
    }
    bool AddPackageOptions::StageInPlace()
    {
        return m_stageInPlace;
    }
    void AddPackageOptions::StageInPlace(bool value)
    {
        m_stageInPlace = value;
    }
    bool AddPackageOptions::DeferRegistrationWhenPackagesAreInUse()
    {
        return m_deferRegistrationWhenPackagesAreInUse;
    }
    void AddPackageOptions::DeferRegistrationWhenPackagesAreInUse(bool value)
    {
        m_deferRegistrationWhenPackagesAreInUse = value;
    }
    bool AddPackageOptions::IsExpectedDigestsSupported()
    {
        // Requires Windows >= 10.0.22621.0 (aka Win11 22H2)
        return WindowsVersion::IsWindows11_22H2OrGreater();
    }
    winrt::Windows::Foundation::Collections::IMap<winrt::Windows::Foundation::Uri, hstring> AddPackageOptions::ExpectedDigests()
    {
        return m_expectedDigests;
    }
    bool AddPackageOptions::IsLimitToExistingPackagesSupported()
    {
        // Requires Windows >= 10.0.22621.0 (aka Win11 22H2)
        return WindowsVersion::IsWindows11_22H2OrGreater();
    }
    bool AddPackageOptions::LimitToExistingPackages()
    {
        return m_limitToExistingPackages;
    }
    void AddPackageOptions::LimitToExistingPackages(bool value)
    {
        m_limitToExistingPackages = value;
    }
}
