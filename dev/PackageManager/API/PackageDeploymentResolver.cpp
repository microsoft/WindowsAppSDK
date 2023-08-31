// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <winrt/Microsoft.Windows.ApplicationModel.DynamicDependency.h>

#include "PackageDeploymentResolver.h"

#include "MsixPackageManager.h"

namespace Microsoft::Windows::ApplicationModel::PackageDeploymentResolver
{
winrt::hstring Find(
    const winrt::Windows::Management::Deployment::PackageManager& packageManager,
    const winrt::hstring& packageFamilyName,
    const AppModel::Identity::PackageVersion& minVersion,
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures processorArchitectureFilter,
    bool stopOnFirstMatch);

static winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures ToPackageDependencyProcessorArchitectures(const winrt::Windows::System::ProcessorArchitecture architecture)
{
    switch (architecture)
    {
    case winrt::Windows::System::ProcessorArchitecture::X86: return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X86;
    case winrt::Windows::System::ProcessorArchitecture::X64: return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X64;
    case winrt::Windows::System::ProcessorArchitecture::Arm: return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Arm;
    case winrt::Windows::System::ProcessorArchitecture::Arm64: return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Arm64;
    case winrt::Windows::System::ProcessorArchitecture::X86OnArm64: return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X86OnArm64;
    case winrt::Windows::System::ProcessorArchitecture::Neutral: return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Neutral;
    case winrt::Windows::System::ProcessorArchitecture::Unknown: THROW_HR_MSG(E_UNEXPECTED, "Unsupported architecture 0x%X", architecture);
    default: THROW_HR_MSG(E_UNEXPECTED, "Unknown architecture 0x%X", architecture);
    }
}

static bool IsArchitectureInArchitectures(
    const winrt::Windows::System::ProcessorArchitecture architecture,
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures architectures)
{
    const auto architectureAsArchitectures{ ToPackageDependencyProcessorArchitectures(architecture) };
    return WI_IsAnyFlagSet(architectures, architectureAsArchitectures);
}

static USHORT GetSystemArchitecture()
{
    USHORT processMachine{ IMAGE_FILE_MACHINE_UNKNOWN };
    USHORT nativeMachine{ IMAGE_FILE_MACHINE_UNKNOWN };
    THROW_IF_WIN32_BOOL_FALSE(::IsWow64Process2(::GetCurrentProcess(), &processMachine, &nativeMachine));
    return nativeMachine;
}

static winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures GetSystemSupportedArchitectures(const std::uint16_t nativeMachine)
{
    switch (nativeMachine)
    {
    case IMAGE_FILE_MACHINE_I386:
        return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Neutral |
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X86;
    case IMAGE_FILE_MACHINE_AMD64:
        return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Neutral |
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X86 |
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X64;
    case IMAGE_FILE_MACHINE_ARM:
        return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Neutral |
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X86 |
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X64 |
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Arm;
    case IMAGE_FILE_MACHINE_ARM64:
        return winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Neutral |
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X86 |
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X64 |
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Arm |
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::Arm64 |
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::X86OnArm64;
    default:
        THROW_HR_MSG(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), "nativeMachine=%hu", nativeMachine);
    }
}

static winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures GetSystemSupportedArchitectures()
{
    const auto nativeMachine{ GetSystemArchitecture() };
    return GetSystemSupportedArchitectures(nativeMachine);
}

static PCWSTR GetSystemArchitectureAsString(const std::uint16_t nativeMachine)
{
    switch (nativeMachine)
    {
    case IMAGE_FILE_MACHINE_I386: return L"x86";
    case IMAGE_FILE_MACHINE_AMD64:return L"x64";
    case IMAGE_FILE_MACHINE_ARM:  return L"arm";
    case IMAGE_FILE_MACHINE_ARM64:return L"arm64";
    default: THROW_HR_MSG(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), "nativeMachine=%hu", nativeMachine);
    }
}

static PCWSTR GetSystemSupportedArchitecturesAsString(const std::uint16_t nativeMachine)
{
    switch (nativeMachine)
    {
    case IMAGE_FILE_MACHINE_I386: return L"neutral,x86";
    case IMAGE_FILE_MACHINE_AMD64:return L"neutral,x86,x64";
    case IMAGE_FILE_MACHINE_ARM:  return L"neutral,x86,arm";
    case IMAGE_FILE_MACHINE_ARM64:return L"neutral,x86,x64,arm,arm64,x86onArm64";
    default: THROW_HR_MSG(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), "nativeMachine=%hu", nativeMachine);
    }
}

static PCWSTR GetSystemSupportedArchitecturesAsString()
{
    const auto nativeMachine{ GetSystemArchitecture() };
    return GetSystemSupportedArchitecturesAsString(nativeMachine);
}

static bool IsArchitectureSupporedByHostMachine(
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures architecture)
{
    const auto supportedArchitectures{ GetSystemSupportedArchitectures() };
    return WI_IsAnyFlagSet(supportedArchitectures, architecture);
}

static bool IsArchitectureSupporedByHostMachine(
    const winrt::Windows::System::ProcessorArchitecture architecture)
{
    const auto architectureAsPackageDependencyProcessorArchitectures{ ToPackageDependencyProcessorArchitectures(architecture) };
    return IsArchitectureSupporedByHostMachine(architectureAsPackageDependencyProcessorArchitectures);
}
}

winrt::hstring Microsoft::Windows::ApplicationModel::PackageDeploymentResolver::FindBestFit(
    const winrt::Windows::Management::Deployment::PackageManager& packageManager,
    const winrt::hstring& packageFamilyName,
    const AppModel::Identity::PackageVersion& minVersion,
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures processorArchitectureFilter)
{
    return Find(packageManager, packageFamilyName, minVersion, processorArchitectureFilter, false);
}

bool Microsoft::Windows::ApplicationModel::PackageDeploymentResolver::FindAny(
    const winrt::Windows::Management::Deployment::PackageManager& packageManager,
    const winrt::hstring& packageFamilyName,
    const AppModel::Identity::PackageVersion& minVersion,
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures processorArchitectureFilter)
{
    winrt::hstring packageFullName{ Find(packageManager, packageFamilyName, minVersion, processorArchitectureFilter, true) };
    return !packageFullName.empty();
}

winrt::hstring Microsoft::Windows::ApplicationModel::PackageDeploymentResolver::Find(
    const winrt::Windows::Management::Deployment::PackageManager& packageManager,
    const winrt::hstring& packageFamilyName,
    const AppModel::Identity::PackageVersion& minVersion,
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures processorArchitectureFilter,
    bool stopOnFirstMatch)
{
    // Find the 'best fit' or 'first matching' package in the family (if any)
    winrt::hstring bestFitPackageFullName;
    AppModel::Identity::PackageVersion bestFitVersion;

    // Determine the packages in the family that could match
    const auto packageTypes{ winrt::Windows::Management::Deployment::PackageTypes::Framework |
                             winrt::Windows::Management::Deployment::PackageTypes::Main };
    auto packages{ packageManager.FindPackagesForUserWithPackageTypes(winrt::hstring(), packageFamilyName, packageTypes) };

    // Find the/any match
    auto criteria{ wil::str_printf<wil::unique_cotaskmem_string>(L"PackageFamilyName=%ls MinVersion=%hu.%hu.%hu.%hu ArchitectureFilter:0x%X",
                                                                 packageFamilyName.c_str(),
                                                                 minVersion.Major, minVersion.Minor,
                                                                 minVersion.Build, minVersion.Revision,
                                                                 static_cast<std::uint32_t>(processorArchitectureFilter)) };
    (void)LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN,
                     "PackageDeploymentResolver: Scanning packages (%ls)",
                     criteria.get());
    if (packages)
    {
        for (const winrt::Windows::ApplicationModel::Package& candidate : packages)
        {
            // Do we already have a higher version under consideration?
            auto packageId{ candidate.Id() };
            const AppModel::Identity::PackageVersion candidateVersion{ packageId.Version() };
            if (!bestFitPackageFullName.empty() && (bestFitVersion > candidateVersion))
            {
                continue;
            }

            // Package version must meet the minVersion filter
            auto candidateFullName{ packageId.FullName() };
            if (candidateVersion < minVersion)
            {
                (void)LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_NOT_MATCH,
                                 "PackageDeploymentResolver: %ls not applicable. Version doesn't match MinVersion criteria (%ls)",
                                 candidateFullName.c_str(), criteria.get());
                continue;
            }

            // Do we already have a higher version under consideration?
            if (!bestFitPackageFullName.empty() && (bestFitVersion > candidateVersion))
            {
                continue;
            }

            // Package architecture must meet the architecture filter
            // Filter=None ==> architecture must match system supported architectures
            // Filter!=None => architecture must match one of the specified architectures
            const auto candidateArchitecture{ packageId.Architecture() };
            if (processorArchitectureFilter == winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures::None)
            {
                const auto nativeMachine{ GetSystemArchitecture() };
                const auto supportedArchitectures{ GetSystemSupportedArchitectures(nativeMachine) };
                if (!IsArchitectureInArchitectures(candidateArchitecture, supportedArchitectures))
                {
                    (void)LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_NOT_MATCH,
                                     "PackageDeploymentResolver: %ls not applicable. Architecture (%ls) doesn't match system supported architectures (0x%X %ls)",
                                     candidateFullName.c_str(), ::AppModel::Identity::GetArchitectureAsString(candidateArchitecture),
                                     static_cast<std::uint32_t>(supportedArchitectures), GetSystemSupportedArchitecturesAsString(nativeMachine));
                    continue;
                }
            }
            else
            {
                if (!IsArchitectureInArchitectures(candidateArchitecture, processorArchitectureFilter))
                {
                    (void)LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_NOT_MATCH,
                                     "PackageDeploymentResolver: %ls not applicable. Architecture (%ls) doesn't match specified architectures (0x%X)",
                                     candidateFullName.c_str(), ::AppModel::Identity::GetArchitectureAsString(candidateArchitecture),
                                     static_cast<std::uint32_t>(processorArchitectureFilter));
                    continue;
                }
            }

            // Package status must be OK to use a package
            winrt::hstring currentUser;
            auto status{ candidate.Status() };
            if (!status.VerifyIsOK())
            {
                (void)LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_NOT_MATCH,
                                 "PackageDeploymentResolver: %ls not applicable. Status not OK (%ls)",
                                 candidateFullName.c_str(), criteria.get());
                continue;
            }

            // Are we looking for any match?
            if (stopOnFirstMatch)
            {
                (void)LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_FAILED,
                                 "PackageDeploymentResolver: Stopping on 1st match %ls (%ls)",
                                 candidateFullName.c_str(), criteria.get());
                return candidateFullName;
            }

            // The new candidate is better than the current champion
            bestFitPackageFullName = std::move(candidateFullName);
            bestFitVersion = candidateVersion;
        }
    }

    // Did we find what we're looking for?
    if (bestFitPackageFullName.empty())
    {
        (void)LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_FAILED,
                         "PackageDeploymentResolver: No match (%ls)",
                         criteria.get());
    }
    else
    {
        (void)LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_MATCH,
                         "PackageDeploymentResolver: %ls is applicable (%ls)",
                         bestFitPackageFullName.c_str(), criteria.get());
    }
    return bestFitPackageFullName;
}
