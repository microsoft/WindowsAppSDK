// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(PACKAGE_RUNTIME_H)
#define PACKAGE_RUNTIME_H

/// Return the absolute path to the file in the package.
/// @param packageFullName the package, or NULL or "" to use the current process' package identity.
/// @param filename file to locate.
/// @param packageFile absolute path to the packaged file, or NULL if not found. Allocated via HeapAlloc; use HeapFree to deallocate
/// @note The package path search order is External(User or Machine) -> Mutable -> Install.
/// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
STDAPI FindPackageFile(
    _In_ PCWSTR packageFullName,
    _In_ PCWSTR filename,
    _Outptr_result_maybenull_ PWSTR* packageFile) noexcept;

/// Return the absolute path to the file in the package graph.
/// @param packageFullName the package, or NULL or "" to use the current process' package identity.
/// @param filename file to locate.
/// @param packageFile absolute path to the packaged file, or NULL if not found. Allocated via HeapAlloc; use HeapFree to deallocate
/// @note The package paths search order is External(User or Machine) -> Mutable -> Install.
/// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
STDAPI FindPackageFileInPackageGraph(
    _In_ PCWSTR packageFullName,
    _In_ PCWSTR filename,
    _Outptr_result_maybenull_ PWSTR* packageFile) noexcept;

#endif // PACKAGE_RUNTIME_H
