// Copyright (c) Microsoft Corporation. All rights reserved.

#ifndef __WINDOWSAPPRUNTIME_LICENSING_H
#define __WINDOWSAPPRUNTIME_LICENSING_H

/// Install licenses (if any) for a Windows App Runtime release.
///
/// This finds the Windows App Runtime's framework package and installs the contained licenses (if any).
///
/// @note Appropriate licenses MUST be installed for MddBootstrapInitialize() to succeed.
///
/// @param majorMinorVersion the major and minor version to use, e..g 0x00010002 for Major.Minor=1.2
/// @param versionTag the version pre-release identifier, or NULL if none.
STDAPI WindowsAppRuntime_InstallLicenses(
    UINT32 majorMinorVersion,
    PCWSTR versionTag) noexcept;

/// Install licenses (if any) in a Windows App Runtime's framework package.
///
/// This installs the licenses (if any) in the specified Windows App Runtime framework package.
///
/// @note Appropriate licenses MUST be installed for MddBootstrapInitialize() to succeed.
///
/// @note This is primarily for testing purposes. Developers are encouraged to use WindowsAppRuntime_InstallLicenses().
///
/// @param frameworkPackageFullName path to Windows App Runtime's framework package.
STDAPI WindowsAppRuntime_InstallLicensesInPackage(
    PCWSTR frameworkPackageFullName) noexcept;

#endif // __WINDOWSAPPRUNTIME_LICENSING_H
