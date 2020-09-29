// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "PackageDependencyManager.h"

static std::mutex g_lock;
std::vector<MddCore::PackageDependency> g_packageDependencies;

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
    packageDependency.GenerateId();

    auto lock = std::unique_lock<std::mutex>(g_lock);

    g_packageDependencies.push_back(packageDependency);

    auto id = wil::make_process_heap_string(packageDependency.Id().c_str());
    *packageDependencyId = id.release();
}

void MddCore::PackageDependencyManager::DeletePackageDependency(
    _In_ PCWSTR packageDependencyId)
{
    if (!packageDependencyId)
    {
        return;
    }

    auto lock = std::unique_lock<std::mutex>(g_lock);

    for (size_t index=0; index < g_packageDependencies.size(); ++index)
    {
        const auto& packageDependency = g_packageDependencies[index];
        if (CompareStringOrdinal(packageDependency.Id().c_str(), -1, packageDependencyId, -1, TRUE) == CSTR_EQUAL)
        {
            g_packageDependencies.erase(g_packageDependencies.begin() + index);
            break;
        }
    }
}

const MddCore::PackageDependency* MddCore::PackageDependencyManager::GetPackageDependency(
    _In_ PCWSTR packageDependencyId)
{
    for (const auto& packageDependency : g_packageDependencies)
    {
        if (CompareStringOrdinal(packageDependency.Id().c_str(), -1, packageDependencyId, -1, TRUE) == CSTR_EQUAL)
        {
            return &packageDependency;
        }
    }

    // Not found
    return nullptr;
}
