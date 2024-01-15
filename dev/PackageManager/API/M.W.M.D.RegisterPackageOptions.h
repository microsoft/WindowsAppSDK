// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Management.Deployment.RegisterPackageOptions.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct RegisterPackageOptions : RegisterPackageOptionsT<RegisterPackageOptions>
    {
        RegisterPackageOptions() = default;

        winrt::Microsoft::Windows::Management::Deployment::PackageVolume AppDataVolume();
        void AppDataVolume(winrt::Microsoft::Windows::Management::Deployment::PackageVolume const& value);
        winrt::Windows::Foundation::Collections::IVector<hstring> DependencyPackageFamilyNames();
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> DependencyPackageUris();
        winrt::Windows::Foundation::Collections::IVector<hstring> OptionalPackageFamilyNames();
        winrt::Windows::Foundation::Uri ExternalLocationUri();
        void ExternalLocationUri(winrt::Windows::Foundation::Uri const& value);
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
        bool StageInPlace();
        void StageInPlace(bool value);
        bool DeferRegistrationWhenPackagesAreInUse();
        void DeferRegistrationWhenPackagesAreInUse(bool value);
        bool IsExpectedDigestsSupported();
        winrt::Windows::Foundation::Collections::IMap<winrt::Windows::Foundation::Uri, hstring> ExpectedDigests();

    private:
        winrt::Microsoft::Windows::Management::Deployment::PackageVolume m_appDataVolume{ nullptr };
        winrt::Windows::Foundation::Collections::IVector<hstring> m_dependencyPackageFamilyNames;
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::Uri> m_dependencyPackageUris;
        winrt::Windows::Foundation::Collections::IVector<hstring> m_optionalPackageFamilyNames;
        winrt::Windows::Foundation::Uri m_externalLocationUri{ nullptr };
        bool m_allowUnsigned{ true };
        bool m_developerMode{};
        bool m_forceAppShutdown{};
        bool m_forceTargetAppShutdown{};
        bool m_forceUpdateFromAnyVersion{};
        bool m_installAllResources{};
        bool m_stageInPlace{};
        bool m_deferRegistrationWhenPackagesAreInUse{};
        winrt::Windows::Foundation::Collections::IMap<winrt::Windows::Foundation::Uri, hstring> m_expectedDigests;
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct RegisterPackageOptions : RegisterPackageOptionsT<RegisterPackageOptions, implementation::RegisterPackageOptions>
    {
    };
}
