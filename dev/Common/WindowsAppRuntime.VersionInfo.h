// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __MICROSFT_WINDOWSAPPRUNTIME_VERSIONINFO_H
#define __MICROSFT_WINDOWSAPPRUNTIME_VERSIONINFO_H

/// Determine if Windows App SDK in use by the current process is deployed Self-Contained (vs deployed as MSIX packages)
///
/// @param packageFamilyName framework's package family name.
STDAPI WindowsAppRuntime_VersionInfo_MSIX_Framework_PackageFamilyName_Get(
    PCWSTR* packageFamilyName) noexcept;

#if defined(__cplusplus)
/// Return true if Windows App SDK in use by the current process is deployed Self-Contained.
namespace WindowsAppRuntime::VersionInfo
{
inline std::wstring GetPackageFamilyName()
{
    PCWSTR packageFamilyName{};
    THROW_IF_FAILED(WindowsAppRuntime_VersionInfo_MSIX_Framework_PackageFamilyName_Get(&packageFamilyName));
    return std::wstring{ packageFamilyName };
}
}
#endif // defined(__cplusplus)

#endif // __MICROSFT_WINDOWSAPPRUNTIME_VERSIONINFO_H
