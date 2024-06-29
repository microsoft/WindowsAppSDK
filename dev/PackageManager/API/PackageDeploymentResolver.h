// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(PACKAGERESOLVER_H)
#define PACKAGERESOLVER_H

namespace Microsoft::Windows::ApplicationModel::PackageDeploymentResolver
{
    // Return the best fit package's full name (or .empty if no match found)
    winrt::hstring FindBestFit(
        const winrt::Windows::Management::Deployment::PackageManager& packageManager,
        const winrt::hstring& packageFamilyName,
        const AppModel::Identity::PackageVersion& minVersion,
        const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures processorArchitectureFilter);

    // Return true if any package meets the criteria
    bool FindAny(
        const winrt::Windows::Management::Deployment::PackageManager& packageManager,
        const winrt::hstring& packageFamilyName,
        const AppModel::Identity::PackageVersion& minVersion,
        const winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyProcessorArchitectures processorArchitectureFilter);

    // Return true if any package meets the criteria
    bool FindAny(
        const winrt::Windows::Management::Deployment::PackageManager& packageManager,
        const winrt::hstring& packageFullName);

    bool IsRegistered(
        const winrt::Windows::Management::Deployment::PackageManager& packageManager,
        const winrt::hstring& packageFullName);
}

#endif // PACKAGERESOLVER_H
