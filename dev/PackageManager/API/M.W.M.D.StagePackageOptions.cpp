// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>
#include <TerminalVelocityFeatures-PackageManager.h>

#include "M.W.M.D.StagePackageOptions.h"
#include "Microsoft.Windows.Management.Deployment.StagePackageOptions.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    winrt::Microsoft::Windows::Management::Deployment::PackageVolume StagePackageOptions::TargetVolume()
    {
        return m_targetVolume;
    }
    void StagePackageOptions::TargetVolume(winrt::Microsoft::Windows::Management::Deployment::PackageVolume const& value)
    {
        m_targetVolume = value;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> StagePackageOptions::DependencyPackageUris()
    {
        if (!m_dependencyPackageUris)
        {
            m_dependencyPackageUris = winrt::single_threaded_vector<winrt::Windows::Foundation::Uri>();
        }
        return m_dependencyPackageUris;
    }
    winrt::Windows::Foundation::Collections::IVector<hstring> StagePackageOptions::OptionalPackageFamilyNames()
    {
        if (!m_optionalPackageFamilyNames)
        {
            m_optionalPackageFamilyNames = winrt::single_threaded_vector<hstring>();
        }
        return m_optionalPackageFamilyNames;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> StagePackageOptions::OptionalPackageUris()
    {
        if (!m_optionalPackageUris)
        {
            m_optionalPackageUris = winrt::single_threaded_vector<winrt::Windows::Foundation::Uri>();
        }
        return m_optionalPackageUris;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> StagePackageOptions::RelatedPackageUris()
    {
        if (!m_relatedPackageUris)
        {
            m_relatedPackageUris = winrt::single_threaded_vector<winrt::Windows::Foundation::Uri>();
        }
        return m_relatedPackageUris;
    }
    winrt::Windows::Foundation::Uri StagePackageOptions::ExternalLocationUri()
    {
        return m_externalLocationUri;
    }
    void StagePackageOptions::ExternalLocationUri(winrt::Windows::Foundation::Uri const& value)
    {
        m_externalLocationUri = value;
    }
    winrt::Microsoft::Windows::Management::Deployment::StubPackageOption StagePackageOptions::StubPackageOption()
    {
        return m_stubPackageOption;
    }
    void StagePackageOptions::StubPackageOption(winrt::Microsoft::Windows::Management::Deployment::StubPackageOption const& value)
    {
        m_stubPackageOption = value;
    }
    bool StagePackageOptions::DeveloperMode()
    {
        return m_developerMode;
    }
    void StagePackageOptions::DeveloperMode(bool value)
    {
        m_developerMode = value;
    }
    bool StagePackageOptions::ForceUpdateFromAnyVersion()
    {
        return m_forceUpdateFromAnyVersion;
    }
    void StagePackageOptions::ForceUpdateFromAnyVersion(bool value)
    {
        m_forceUpdateFromAnyVersion = value;
    }
    bool StagePackageOptions::InstallAllResources()
    {
        return m_installAllResources;
    }
    void StagePackageOptions::InstallAllResources(bool value)
    {
        m_installAllResources = value;
    }
    bool StagePackageOptions::RequiredContentGroupOnly()
    {
        return m_requiredContentGroupOnly;
    }
    void StagePackageOptions::RequiredContentGroupOnly(bool value)
    {
        m_requiredContentGroupOnly = value;
    }
    bool StagePackageOptions::StageInPlace()
    {
        return m_stageInPlace;
    }
    void StagePackageOptions::StageInPlace(bool value)
    {
        m_stageInPlace = value;
    }
    bool StagePackageOptions::AllowUnsigned()
    {
        return m_allowUnsigned;
    }
    void StagePackageOptions::AllowUnsigned(bool value)
    {
        m_allowUnsigned = value;
    }
    bool StagePackageOptions::IsExpectedDigestsSupported()
    {
        // Requires Windows >= 10.0.22621.0 (aka Win11 22H2)
        return WindowsVersion::IsWindows11_22H2OrGreater();
    }
    winrt::Windows::Foundation::Collections::IMap<winrt::Windows::Foundation::Uri, hstring> StagePackageOptions::ExpectedDigests()
    {
        if (!m_expectedDigests)
        {
            m_expectedDigests = winrt::single_threaded_map<winrt::Windows::Foundation::Uri, hstring>();
        }
        return m_expectedDigests;
    }

    bool StagePackageOptions::IsPackageValidationSupported()
    {
        return WindowsVersion::SupportsIAppxFactory4();
    }

    winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventSource StagePackageOptions::GetValidationEventSourceForUri(winrt::Windows::Foundation::Uri const& uri)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Management::Deployment::Feature_PackageValidation::IsEnabled());

        if (!m_packageValidators)
        {
            m_packageValidators = winrt::single_threaded_map<winrt::Windows::Foundation::Uri, winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventSource>();
        }
        if (!m_packageValidators.HasKey(uri))
        {
            m_packageValidators.Insert(uri, winrt::make<winrt::Microsoft::Windows::Management::Deployment::implementation::PackageValidationEventSource>());
        }

        return m_packageValidators.Lookup(uri);
    }

    winrt::Windows::Foundation::Collections::IMapView<winrt::Windows::Foundation::Uri, winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventSource> StagePackageOptions::PackageValidators()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Management::Deployment::Feature_PackageValidation::IsEnabled());

        if (!m_packageValidators)
        {
            // return an empty view
            return winrt::single_threaded_map<winrt::Windows::Foundation::Uri, winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventSource>().GetView();
        }
        else
        {
            return m_packageValidators.GetView();
        }
    }
}
