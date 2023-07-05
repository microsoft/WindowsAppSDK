// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(MDDWIN11DYNAMICDEPENDENCY_H)
#define MDDWIN11DYNAMICDEPENDENCY_H

namespace MddCore::Win11
{
bool IsSupported();

HRESULT Initialize();

void Shutdown();

HRESULT TryCreatePackageDependency(
    PSID user,
    _In_ PCWSTR packageFamilyName,
    PACKAGE_VERSION minVersion,
    MddPackageDependencyProcessorArchitectures packageDependencyProcessorArchitectures,
    MddPackageDependencyLifetimeKind lifetimeKind,
    PCWSTR lifetimeArtifact,
    MddCreatePackageDependencyOptions options,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId);

void DeletePackageDependency(
    _In_ PCWSTR packageDependencyId);

HRESULT AddPackageDependency(
    _In_ PCWSTR packageDependencyId,
    INT32 rank,
    MddAddPackageDependencyOptions options,
    _Out_ MDD_PACKAGEDEPENDENCY_CONTEXT* packageDependencyContext,
    _Outptr_opt_result_maybenull_ PWSTR* packageFullName);

void RemovePackageDependency(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext);

HRESULT GetResolvedPackageFullNameForPackageDependency(
    _In_ PCWSTR packageDependencyId,
    _Outptr_result_maybenull_ PWSTR* packageFullName);

HRESULT GetIdForPackageDependencyContext(
    _In_ MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext,
    _Outptr_result_maybenull_ PWSTR* packageDependencyId);

UINT32 GetPackageGraphRevisionId();
}

#endif // MDDWIN11DYNAMICDEPENDENCY_H
