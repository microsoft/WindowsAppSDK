// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(PACKAGERUNTIME_H)
#define PACKAGERUNTIME_H

#include <appmodel.h>

#include <stdint.h>

#if defined(__cplusplus)

/// Return the absolute path to the packaged file.
/// @param packageFullName the package, or NULL or "" to use the current process' package identity.
/// @param filename file to locate.
/// @param packageFile absolute path to the packaged file, or NULL if not found. Allocated via HeapAlloc; use HeapFree to deallocate
/// @note The package path search order is External(User or Machine) -> Mutable -> Install.
/// @note If a package has a UserExternal location then MachineExternal location is not checked (even if the package has one).
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
STDAPI FindPackageFile(
    PCWSTR packageFullName,
    PCWSTR filename,
    _Outptr_result_maybenull_ PWSTR* packageFile) noexcept;

#endif // defined(__cplusplus)

#endif // PACKAGERUNTIME_H

