// Copyright (c) Microsoft Corporation. All rights reserved.

#ifndef __MSIXLICENSING_H
#define __MSIXLICENSING_H

STDAPI MsixInstallLicenses(
    UINT32 majorMinorVersion,
    PCWSTR versionTag) noexcept;

STDAPI MsixInstallLicensesInPackage(
    PCWSTR frameworkPackageFullName) noexcept;

#endif // __MSIXLICENSING_H
