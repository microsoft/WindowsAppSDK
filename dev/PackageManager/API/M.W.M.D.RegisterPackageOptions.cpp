// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

#include "M.W.M.D.RegisterPackageOptions.h"
#include "Microsoft.Windows.Management.Deployment.RegisterPackageOptions.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageVolume RegisterPackageOptions::AppDataVolume()
    {
        return m_appDataVolume;
    }
    void RegisterPackageOptions::AppDataVolume(winrt::Microsoft::Windows::Management::Deployment::PackageVolume const& value)
    {
        m_appDataVolume = value;
    }
    winrt::Windows::Foundation::Collections::IVector<hstring> RegisterPackageOptions::DependencyPackageFamilyNames()
    {
        if (!m_dependencyPackageFamilyNames)
        {
            m_dependencyPackageFamilyNames = winrt::single_threaded_vector<hstring>();
        }
        return m_dependencyPackageFamilyNames;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> RegisterPackageOptions::DependencyPackageUris()
    {
        if (!m_dependencyPackageUris)
        {
            m_dependencyPackageUris = winrt::single_threaded_vector<winrt::Windows::Foundation::Uri>();
        }
        return m_dependencyPackageUris;
    }
    winrt::Windows::Foundation::Collections::IVector<hstring> RegisterPackageOptions::OptionalPackageFamilyNames()
    {
        if (!m_optionalPackageFamilyNames)
        {
            m_optionalPackageFamilyNames = winrt::single_threaded_vector<hstring>();
        }
        return m_optionalPackageFamilyNames;
    }
    winrt::Windows::Foundation::Uri RegisterPackageOptions::ExternalLocationUri()
    {
        return m_externalLocationUri;
    }
    void RegisterPackageOptions::ExternalLocationUri(winrt::Windows::Foundation::Uri const& value)
    {
        m_externalLocationUri = value;
    }
    bool RegisterPackageOptions::AllowUnsigned()
    {
        return m_allowUnsigned;
    }
    void RegisterPackageOptions::AllowUnsigned(bool value)
    {
        m_allowUnsigned = value;
    }
    bool RegisterPackageOptions::DeveloperMode()
    {
        return m_developerMode;
    }
    void RegisterPackageOptions::DeveloperMode(bool value)
    {
        m_developerMode = value;
    }
    bool RegisterPackageOptions::ForceAppShutdown()
    {
        return m_forceAppShutdown;
    }
    void RegisterPackageOptions::ForceAppShutdown(bool value)
    {
        m_forceAppShutdown = value;
    }
    bool RegisterPackageOptions::ForceTargetAppShutdown()
    {
        return m_forceTargetAppShutdown;
    }
    void RegisterPackageOptions::ForceTargetAppShutdown(bool value)
    {
        m_forceTargetAppShutdown = value;
    }
    bool RegisterPackageOptions::ForceUpdateFromAnyVersion()
    {
        return m_forceUpdateFromAnyVersion;
    }
    void RegisterPackageOptions::ForceUpdateFromAnyVersion(bool value)
    {
        m_forceUpdateFromAnyVersion = value;
    }
    bool RegisterPackageOptions::InstallAllResources()
    {
        return m_installAllResources;
    }
    void RegisterPackageOptions::InstallAllResources(bool value)
    {
        m_installAllResources = value;
    }
    bool RegisterPackageOptions::StageInPlace()
    {
        return m_stageInPlace;
    }
    void RegisterPackageOptions::StageInPlace(bool value)
    {
        m_stageInPlace = value;
    }
    bool RegisterPackageOptions::DeferRegistrationWhenPackagesAreInUse()
    {
        return m_deferRegistrationWhenPackagesAreInUse;
    }
    void RegisterPackageOptions::DeferRegistrationWhenPackagesAreInUse(bool value)
    {
        m_deferRegistrationWhenPackagesAreInUse = value;
    }
    bool RegisterPackageOptions::IsExpectedDigestsSupported()
    {
        // Requires Windows >= 10.0.22621.0 (aka Win11 22H2)
        return WindowsVersion::IsWindows11_22H2OrGreater();
    }
    winrt::Windows::Foundation::Collections::IMap<winrt::Windows::Foundation::Uri, hstring> RegisterPackageOptions::ExpectedDigests()
    {
        return m_expectedDigests;
    }
}
