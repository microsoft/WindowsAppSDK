// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "PackageDependency.h"

namespace MddCore
{
/// @note All public static methods are thread safe and acquire the global lock if necessary.
/// @note All private static methods assume the global lock managed by their caller and held for their duration.
class PackageDependencyManager
{
public:
    PackageDependencyManager() = delete;
    ~PackageDependencyManager() = delete;

public:
    static void CreatePackageDependency(
        PSID user,
        _In_ PCWSTR packageFamilyName,
        PACKAGE_VERSION minVersion,
        MddPackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
        MddPackageDependencyLifetimeKind lifetimeKind,
        PCWSTR lifetimeArtifact,
        MddCreatePackageDependencyOptions options,
        _Outptr_result_maybenull_ PWSTR* packageDependencyId);

    static void CreatePackageDependency(
        const MddCore::PackageDependency& packageDependency,
        _Outptr_result_maybenull_ PWSTR* packageDependencyId);

    static void DeletePackageDependency(
        _In_ PCWSTR packageDependencyId);

    static const PackageDependency* GetPackageDependency(
        _In_ PCWSTR packageDependencyId);

private:
    static const PackageDependency* GetPackageDependencyInMemory(
        _In_ PCWSTR packageDependencyId);

    static const PackageDependency* GetPackageDependencyInDataStore(
        _In_ PCWSTR packageDependencyId);

    static void Verify(
        const MddCore::PackageDependency& packageDependency);
};
}
