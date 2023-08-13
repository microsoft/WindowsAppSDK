// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "PackageResolver.h"

#include "MsixPackageManager.h"

namespace Microsoft::Windows::ApplicationModel::PackageResolver
{
winrt::hstring Find(
    const winrt::Windows::Management::Deployment::PackageManager& packageManager,
    const winrt::hstring& packageFamilyName,
    const AppModel::Identity::PackageVersion& minVersion,
    bool stopOnFirstMatch);
}

winrt::hstring Microsoft::Windows::ApplicationModel::PackageResolver::FindBestFit(
    const winrt::Windows::Management::Deployment::PackageManager& packageManager,
    const winrt::hstring& packageFamilyName,
    const AppModel::Identity::PackageVersion& minVersion)
{
    return Find(packageManager, packageFamilyName, minVersion, false);
}

bool Microsoft::Windows::ApplicationModel::PackageResolver::FindAny(
    const winrt::Windows::Management::Deployment::PackageManager& packageManager,
    const winrt::hstring& packageFamilyName,
    const AppModel::Identity::PackageVersion& minVersion)
{
    winrt::hstring packageFullName{ Find(packageManager, packageFamilyName, minVersion, true) };
    return !packageFullName.empty();
}

winrt::hstring Microsoft::Windows::ApplicationModel::PackageResolver::Find(
    const winrt::Windows::Management::Deployment::PackageManager& packageManager,
    const winrt::hstring& packageFamilyName,
    const AppModel::Identity::PackageVersion& minVersion,
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
    auto criteria{ wil::str_printf<wil::unique_cotaskmem_string>(L"PackageFamilyName=%ls MinVersion=%hu.%hu.%hu.%hu",
                                                                 packageFamilyName.c_str(),
                                                                 minVersion.Major, minVersion.Minor,
                                                                 minVersion.Build, minVersion.Revision) };
    (void) LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN,
                      "PackageResolver: Scanning packages (%ls)",
                      criteria.get());
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
            (void) LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_NOT_MATCH,
                              "PackageResolver: %ls not applicable. Version doesn't match MinVersion criteria (%ls)",
                              candidateFullName.c_str(), criteria.get());
            continue;
        }

        // Do we already have a higher version under consideration?
        if (!bestFitPackageFullName.empty() && (bestFitVersion > candidateVersion))
        {
            continue;
        }

#if 0 //TODO
        // Package architecture must meet the architecture filter
        if (packageDependency.Architectures() == MddPackageDependencyProcessorArchitectures::None)
        {
            if (!IsPackageABetterFitPerArchitecture(bestFit, candidate))
            {
                continue;
            }
        }
        else
        {
            if (!packageDependency.IsArchitectureInArchitectures(candidate.Architecture()))
            {
                continue;
            }
        }

        // Does the architecture match?
        const auto architecture{ packageId.Architecture() };
        const auto currentArchitecture{ AppModel::Identity::GetCurrentArchitecture() };
        if (architecture != currentArchitecture)
        {
            (void)LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_NOT_MATCH,
                             "PackageResolver: %ls not applicable. Architecture doesn't match current architecture %ls (%ls)",
                             packageFullName.c_str(), ::AppModel::Identity::GetCurrentArchitectureAsString(), criteria.get());
            continue;
        }
#endif

        // Package status must be OK to use a package
        winrt::hstring currentUser;
        auto status{ candidate.Status() };
        if (!status.VerifyIsOK())
        {
            (void) LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_NOT_MATCH,
                              "PackageResolver: %ls not applicable. Status not OK (%ls)",
                              candidateFullName.c_str(), criteria.get());
            continue;
        }

        // Are we looking for any match?
        if (stopOnFirstMatch)
        {
            (void) LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_FAILED,
                              "PackageResolver: Stopping on 1st match %ls (%ls)",
                              candidateFullName.c_str(), criteria.get());
            return candidateFullName;
        }

        // The new candidate is better than the current champion
        bestFitPackageFullName = std::move(candidateFullName);
        bestFitVersion = candidateVersion;
    }

    // Did we find what we're looking for?
    if (bestFitPackageFullName.empty())
    {
        (void) LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_FAILED,
                          "PackageResolver: No match (%ls)",
                          criteria.get());
    }
    else
    {
        (void) LOG_HR_MSG(MSIXPACKAGEMANAGER_E_PACKAGE_SCAN_MATCH,
                          "PackageResolver: %ls is applicable (%ls)",
                          bestFitPackageFullName.c_str(), criteria.get());
    }
    return bestFitPackageFullName;
}
