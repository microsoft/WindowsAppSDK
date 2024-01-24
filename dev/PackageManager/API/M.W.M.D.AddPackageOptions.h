// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.AddPackageOptions.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct AddPackageOptions : AddPackageOptionsT<AddPackageOptions>
    {
        AddPackageOptions() = default;

        winrt::Microsoft::Windows::Management::Deployment::PackageVolume TargetVolume();
        void TargetVolume(winrt::Microsoft::Windows::Management::Deployment::PackageVolume const& value);
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> DependencyPackageUris();
        winrt::Windows::Foundation::Collections::IVector<hstring> OptionalPackageFamilyNames();
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> OptionalPackageUris();
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> RelatedPackageUris();
        winrt::Windows::Foundation::Uri ExternalLocationUri();
        void ExternalLocationUri(winrt::Windows::Foundation::Uri const& value);
        winrt::Microsoft::Windows::Management::Deployment::StubPackageOption StubPackageOption();
        void StubPackageOption(winrt::Microsoft::Windows::Management::Deployment::StubPackageOption const& value);
        bool AllowUnsigned();
        void AllowUnsigned(bool value);
        bool DeveloperMode();
        void DeveloperMode(bool value);
        bool ForceAppShutdown();
        void ForceAppShutdown(bool value);
        bool ForceTargetAppShutdown();
        void ForceTargetAppShutdown(bool value);
        bool ForceUpdateFromAnyVersion();
        void ForceUpdateFromAnyVersion(bool value);
        bool InstallAllResources();
        void InstallAllResources(bool value);
        bool RequiredContentGroupOnly();
        void RequiredContentGroupOnly(bool value);
        bool RetainFilesOnFailure();
        void RetainFilesOnFailure(bool value);
        bool StageInPlace();
        void StageInPlace(bool value);
        bool DeferRegistrationWhenPackagesAreInUse();
        void DeferRegistrationWhenPackagesAreInUse(bool value);
        bool IsExpectedDigestsSupported();
        winrt::Windows::Foundation::Collections::IMap<winrt::Windows::Foundation::Uri, hstring> ExpectedDigests();
        bool IsLimitToExistingPackagesSupported();
        bool LimitToExistingPackages();
        void LimitToExistingPackages(bool value);

    private:
        winrt::Microsoft::Windows::Management::Deployment::PackageVolume m_targetVolume{ nullptr };
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> m_dependencyPackageUris;
        winrt::Windows::Foundation::Collections::IVector<hstring> m_optionalPackageFamilyNames;
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> m_optionalPackageUris;
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> m_relatedPackageUris;
        winrt::Windows::Foundation::Uri m_externalLocationUri{ nullptr };
        winrt::Microsoft::Windows::Management::Deployment::StubPackageOption m_stubPackageOption{};
        bool m_allowUnsigned{};
        bool m_developerMode{};
        bool m_forceAppShutdown{};
        bool m_forceTargetAppShutdown{};
        bool m_forceUpdateFromAnyVersion{};
        bool m_installAllResources{};
        bool m_requiredContentGroupOnly{};
        bool m_retainFilesOnFailure{};
        bool m_stageInPlace{};
        bool m_deferRegistrationWhenPackagesAreInUse{};
        winrt::Windows::Foundation::Collections::IMap<winrt::Windows::Foundation::Uri, hstring> m_expectedDigests;
        bool m_limitToExistingPackages{};
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct AddPackageOptions : AddPackageOptionsT<AddPackageOptions, implementation::AddPackageOptions>
    {
    };
}
