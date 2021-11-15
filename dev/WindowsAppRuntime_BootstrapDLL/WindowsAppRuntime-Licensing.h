// Copyright (c) Microsoft Corporation. All rights reserved.

#ifndef __WINDOWSAPPRUNTIME_LICENSING_H
#define __WINDOWSAPPRUNTIME_LICENSING_H

STDAPI WindowsAppRuntime_InstallLicenses(
    UINT32 majorMinorVersion,
    PCWSTR versionTag) noexcept;

STDAPI WindowsAppRuntime_InstallLicensesInPackage(
    PCWSTR frameworkPackageFullName) noexcept;

#endif // __WINDOWSAPPRUNTIME_LICENSING_H
