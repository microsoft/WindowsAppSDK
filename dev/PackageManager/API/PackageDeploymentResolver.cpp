// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <winrt/Microsoft.Windows.ApplicationModel.DynamicDependency.h>

#include "PackageDeploymentResolver.h"

#include "MsixPackageManager.h"
#include "PackageManagerTelemetry.h"

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

static bool IsArchitectureSupportedByHostMachine(
    const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures architecture)
{
    const auto supportedArchitectures{ GetSystemSupportedArchitectures() };
    return WI_IsAnyFlagSet(supportedArchitectures, architecture);
}

static bool IsArchitectureSupportedByHostMachine(
    const winrt::Windows::System::ProcessorArchitecture architecture)
{
    const auto architectureAsPackageDependencyProcessorArchitectures{ ToPackageDependencyProcessorArchitectures(architecture) };
    return IsArchitectureSupportedByHostMachine(architectureAsPackageDependencyProcessorArchitectures);
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
    const winrt::hstring& packageFullName)
{
    // Find the/any match
    auto package{ packageManager.FindPackageForUser(winrt::hstring(), packageFullName) };
    if (!package)
    {
        return false;
    }

    // Package status must be OK to use a package
    auto status{ package.Status() };
    return status.VerifyIsOK();
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
    TraceLoggingWrite(
        PackageManagementTelemetryProvider::Provider(),
        "PackageDeployment.Resolver.Scan",
        TraceLoggingWideString(packageFamilyName.c_str(), "Criteria.PackageFamilyName"),
        TraceLoggingHexUInt64(minVersion.Version, "Criteria.MinVersion"),
        TraceLoggingHexInt32(static_cast<std::int32_t>(processorArchitectureFilter), "Criteria.ArchitectureFilter"),
        TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
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
                TraceLoggingWrite(
                    PackageManagementTelemetryProvider::Provider(),
                    "PackageDeployment.Resolver.Scan.NoMatch.Version",
                    TraceLoggingWideString(candidateFullName.c_str(), "PackageFullName"),
                    TraceLoggingWideString(packageFamilyName.c_str(), "Criteria.PackageFamilyName"),
                    TraceLoggingHexUInt64(minVersion.Version, "Criteria.MinVersion"),
                    TraceLoggingHexInt32(static_cast<std::int32_t>(processorArchitectureFilter), "Criteria.ArchitectureFilter"),
                    TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
                    TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
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
                    TraceLoggingWrite(
                        PackageManagementTelemetryProvider::Provider(),
                        "PackageDeployment.Resolver.Scan.NoMatch.Architecture",
                        TraceLoggingWideString(candidateFullName.c_str(), "PackageFullName"),
                        TraceLoggingWideString(packageFamilyName.c_str(), "Criteria.PackageFamilyName"),
                        TraceLoggingHexUInt64(minVersion.Version, "Criteria.MinVersion"),
                        TraceLoggingHexInt32(static_cast<std::int32_t>(processorArchitectureFilter), "Criteria.ArchitectureFilter"),
                        TraceLoggingInt32(static_cast<std::int32_t>(candidateArchitecture), "Architecture"),
                        TraceLoggingHexInt32(static_cast<std::int32_t>(supportedArchitectures), "SupportedArchitectures"),
                        TraceLoggingUInt16(static_cast<std::uint32_t>(nativeMachine), "NativeMachineArchitecture"),
                        TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
                        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
                    continue;
                }
            }
            else
            {
                if (!IsArchitectureInArchitectures(candidateArchitecture, processorArchitectureFilter))
                {
                    TraceLoggingWrite(
                        PackageManagementTelemetryProvider::Provider(),
                        "PackageDeployment.Resolver.Scan.NoMatch.Architecture",
                        TraceLoggingWideString(candidateFullName.c_str(), "PackageFullName"),
                        TraceLoggingWideString(packageFamilyName.c_str(), "Criteria.PackageFamilyName"),
                        TraceLoggingHexUInt64(minVersion.Version, "Criteria.MinVersion"),
                        TraceLoggingHexInt32(static_cast<std::int32_t>(processorArchitectureFilter), "Criteria.ArchitectureFilter"),
                        TraceLoggingInt32(static_cast<std::int32_t>(candidateArchitecture), "Architecture"),
                        TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
                        TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
                    continue;
                }
            }

            // Package status must be OK to use a package
            winrt::hstring currentUser;
            auto status{ candidate.Status() };
            if (!status.VerifyIsOK())
            {
                TraceLoggingWrite(
                    PackageManagementTelemetryProvider::Provider(),
                    "PackageDeployment.Resolver.Scan.NoMatch.Status",
                    TraceLoggingWideString(candidateFullName.c_str(), "PackageFullName"),
                    TraceLoggingWideString(packageFamilyName.c_str(), "Criteria.PackageFamilyName"),
                    TraceLoggingHexUInt64(minVersion.Version, "Criteria.MinVersion"),
                    TraceLoggingHexInt32(static_cast<std::int32_t>(processorArchitectureFilter), "Criteria.ArchitectureFilter"),
                    TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
                    TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
                continue;
            }

            // Are we looking for any match?
            if (stopOnFirstMatch)
            {
                TraceLoggingWrite(
                    PackageManagementTelemetryProvider::Provider(),
                    "PackageDeployment.Resolver.Found.StopOnFirst",
                    TraceLoggingWideString(candidateFullName.c_str(), "PackageFullName"),
                    TraceLoggingWideString(packageFamilyName.c_str(), "Criteria.PackageFamilyName"),
                    TraceLoggingHexUInt64(minVersion.Version, "Criteria.MinVersion"),
                    TraceLoggingHexInt32(static_cast<std::int32_t>(processorArchitectureFilter), "Criteria.ArchitectureFilter"),
                    TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
                    TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
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
        TraceLoggingWrite(
            PackageManagementTelemetryProvider::Provider(),
            "PackageDeployment.Resolver.NotFound",
            TraceLoggingWideString(packageFamilyName.c_str(), "Criteria.PackageFamilyName"),
            TraceLoggingHexUInt64(minVersion.Version, "Criteria.MinVersion"),
            TraceLoggingHexInt32(static_cast<std::int32_t>(processorArchitectureFilter), "Criteria.ArchitectureFilter"),
            TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
    }
    else
    {
        TraceLoggingWrite(
            PackageManagementTelemetryProvider::Provider(),
            "PackageDeployment.Resolver.Found",
            TraceLoggingWideString(bestFitPackageFullName.c_str(), "PackageFullName"),
            TraceLoggingWideString(packageFamilyName.c_str(), "Criteria.PackageFamilyName"),
            TraceLoggingHexUInt64(minVersion.Version, "Criteria.MinVersion"),
            TraceLoggingHexInt32(static_cast<std::int32_t>(processorArchitectureFilter), "Criteria.ArchitectureFilter"),
            TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
            TelemetryPrivacyDataTag(PDT_ProductAndServicePerformance));
    }
    return bestFitPackageFullName;
}

bool Microsoft::Windows::ApplicationModel::PackageDeploymentResolver::IsRegistered(
    const winrt::Windows::Management::Deployment::PackageManager& packageManager,
    const winrt::hstring& packageFullName)
{
    // Find the match
    auto package{ packageManager.FindPackageForUser(winrt::hstring(), packageFullName) };
    return !!package;
}
