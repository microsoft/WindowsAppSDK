// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "PackageDependencyManager.h"

#include "DataStore.h"
#include "PackageGraph.h"

static std::mutex g_lock;
std::vector<MddCore::PackageDependency> g_packageDependencies;

bool MddCore::PackageDependencyManager::ExistsPackageDependency(
    PSID user,
    _In_ PCWSTR packageDependencyId)
{
    auto lock{ std::unique_lock<std::mutex>(g_lock) };

    // Find it (if we can)
    auto packageDependency{ GetPackageDependency(packageDependencyId) };
    if (packageDependency)
    {
        auto packageDependencyUser{ packageDependency->User() };
        if (user)
        {
            // We're expecting a definition for the specifiedd user
            return packageDependencyUser && !!EqualSid(user, packageDependencyUser);
        }
        else
        {
            // We're not expecting a user (i.e. it's for System)
            return !packageDependencyUser;
        }
    }
    return false;
}

void MddCore::PackageDependencyManager::CreatePackageDependency(
    PSID user,
    _In_ PCWSTR packageFamilyName,
    PACKAGE_VERSION minVersion,
    MddPackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
    MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact,
    MddCreatePackageDependencyOptions options,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId)
{
    *packageDependencyId = nullptr;

    MddCore::PackageDependency packageDependency(user, packageFamilyName, minVersion, packageDependencyProcessorArchitectures, lifetimeKind, lifetimeArtifact, options);
    Verify(packageDependency);
    packageDependency.GenerateId();

    MddCore::DataStore::Save(packageDependency, options);

    auto lock{ std::unique_lock<std::mutex>(g_lock) };

    g_packageDependencies.push_back(packageDependency);

    auto id{ wil::make_process_heap_string(packageDependency.Id().c_str()) };
    *packageDependencyId = id.release();
}

void MddCore::PackageDependencyManager::CreatePackageDependency(
    const MddCore::PackageDependency& packageDependency,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId)
{
    // Make a new PackageDependency object with the definition parts of the provided one
    CreatePackageDependency(packageDependency.User(), packageDependency.PackageFamilyName().c_str(),
        packageDependency.MinVersion(), packageDependency.Architectures(),
        packageDependency.LifetimeKind(), packageDependency.LifetimeArtifact().c_str(), packageDependency.Options(),
        packageDependencyId);
}

void MddCore::PackageDependencyManager::DeletePackageDependency(
    _In_ PCWSTR packageDependencyId)
{
    if (!packageDependencyId)
    {
        return;
    }

    auto lock{ std::unique_lock<std::mutex>(g_lock) };

    for (size_t index=0; index < g_packageDependencies.size(); ++index)
    {
        const auto& packageDependency{ g_packageDependencies[index] };
        if (CompareStringOrdinal(packageDependency.Id().c_str(), -1, packageDependencyId, -1, TRUE) == CSTR_EQUAL)
        {
            g_packageDependencies.erase(g_packageDependencies.begin() + index);
            break;
        }
    }

    MddCore::DataStore::Delete(packageDependencyId);
}

const MddCore::PackageDependency* MddCore::PackageDependencyManager::GetPackageDependency(
    _In_ PCWSTR packageDependencyId)
{
    // Find it (if we can)
    auto packageDependency{ GetPackageDependencyInMemory(packageDependencyId) };
    if (!packageDependency)
    {
        packageDependency = GetPackageDependencyInDataStore(packageDependencyId);
    }
    return packageDependency;
}

const MddCore::PackageDependency* MddCore::PackageDependencyManager::GetPackageDependencyInMemory(
    _In_ PCWSTR packageDependencyId)
{
    // Check the in-memory list
    for (size_t index=0; index < g_packageDependencies.size(); ++index)
    {
        const auto& packageDependency{ g_packageDependencies[index] };
        if (CompareStringOrdinal(packageDependency.Id().c_str(), -1, packageDependencyId, -1, TRUE) == CSTR_EQUAL)
        {
            // Gotcha!
            return &packageDependency;
        }
    }

    // Not found
    return nullptr;
}

/// @warning This method assumes \c packageDependencyId is not in the in-memory list
const MddCore::PackageDependency* MddCore::PackageDependencyManager::GetPackageDependencyInDataStore(
    _In_ PCWSTR packageDependencyId)
{
    auto packageDependency{ MddCore::DataStore::Load(packageDependencyId) };
    if (!packageDependency)
    {
        return nullptr;
    }

    // We're guaranteed it's not in the in-memory list at this point

    // Has it expired?
    if (packageDependency.IsExpired())
    {
        // GC the expired package dependency
        MddCore::DataStore::Delete(packageDependencyId);

        // Not found
        return nullptr;
    }

    // Add it to the in-memory list
    g_packageDependencies.push_back(packageDependency);

    // Gotcha!
    return &g_packageDependencies.back();
}

void MddCore::PackageDependencyManager::Verify(
    const MddCore::PackageDependency& packageDependency)
{
    // Verify the package dependency's lifetime artifact
    THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_CONTEXT_EXPIRED), packageDependency.IsExpired());

    // Verify the package dependency's dependency resolution (if necessary)
    if (WI_IsFlagClear(packageDependency.Options(), MddCreatePackageDependencyOptions::DoNotVerifyDependencyResolution))
    {
        MddAddPackageDependencyOptions options{};
        wil::unique_process_heap_string packageFullName;
        THROW_IF_FAILED(MddCore::PackageGraph::ResolvePackageDependency(packageDependency, options, packageFullName));
    }
}
