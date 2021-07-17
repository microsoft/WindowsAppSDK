// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(MDDBOOSTRAP_H)
#define MDDBOOSTRAP_H

#include <appmodel.h>

/// Iniitalize the calling process to use Windows App SDK's framework package.
///
/// Find a Windows App SDK framework package meeting the criteria and make it available
/// for use by the current process. If multiple packages meet the criteria the best
/// candidate is selected.
///
/// @param majorMinorVersion the major and minor version to use, e..g 0x00010002 for Major.Minor=1.2
/// @param versionTag the version pre-release identifier, or NULL if none.
/// @param minVersion the minimum version to use
STDAPI MddBootstrapInitialize(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion) noexcept;

/// Undo the changes made by MddBoostrapInitialize().
///
/// @warning Packages made available via MddBootstrapInitialize() and
///          the Dynamic Dependencies API should not be used after this call.
STDAPI_(void) MddBootstrapShutdown() noexcept;

#endif // MDDBOOSTRAP_H
