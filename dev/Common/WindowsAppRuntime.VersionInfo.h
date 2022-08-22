// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#ifndef __MICROSFT_WINDOWSAPPRUNTIME_VERSIONINFO_H
#define __MICROSFT_WINDOWSAPPRUNTIME_VERSIONINFO_H

/// Determine if Windows App SDK in use by the current process is deployed Self-Contained (vs deployed as MSIX packages)
///
/// @param packageFamilyName framework's package family name.
STDAPI WindowsAppRuntime_VersionInfo_MSIX_Framework_PackageFamilyName_Get(
    PCWSTR* packageFamilyName) noexcept;

/// Determine if Windows App SDK in use by the current process is deployed Self-Contained (vs deployed as MSIX packages)
///
/// @param packageFamilyName main's package family name.
STDAPI WindowsAppRuntime_VersionInfo_MSIX_Main_PackageFamilyName_Get(
    PCWSTR* packageFamilyName) noexcept;

/// Initialize SelfContained's test support. This will constrain package enumeration
/// and matching for test purposes.
///
/// @param frameworkPackageFamilyName only match framework packages with this family name.
///                                   If nullptr test support is disabled.
/// @param mainPackageFamilyName only match main packages with this family name.
///                              If nullptr test support is disabled.
///
/// @note Not for product use. This is for test purposes only to verify the implementation.
STDAPI WindowsAppRuntime_VersionInfo_TestInitialize(
    PCWSTR frameworkPackageFamilyName,
    PCWSTR mainPackageFamilyName) noexcept;

#if defined(__cplusplus)
namespace WindowsAppRuntime::VersionInfo
{
namespace Framework
{
/// Return the Windows App SDK framework's package family name.
inline std::wstring GetPackageFamilyName()
{
    PCWSTR packageFamilyName{};
    THROW_IF_FAILED(WindowsAppRuntime_VersionInfo_MSIX_Framework_PackageFamilyName_Get(&packageFamilyName));
    return std::wstring{ packageFamilyName };
}
}

namespace Main
{
/// Return the Windows App SDK main's package family name.
inline std::wstring GetPackageFamilyName()
{
    PCWSTR packageFamilyName{};
    THROW_IF_FAILED(WindowsAppRuntime_VersionInfo_MSIX_Main_PackageFamilyName_Get(&packageFamilyName));
    return std::wstring{ packageFamilyName };
}
}

/// Initialize VersionInfo's test support. This will constrain package enumeration
/// and matching for test purposes.
///
/// @param frameworkPackageFamilyName only match framework packages with this family name
/// @param mainPackageFamilyName only match main packages with this family name
///
/// @note Not for product use. This is for test purposes only to verify the implementation.
inline void TestInitialize(
    _In_ PCWSTR frameworkPackageFamilyName,
    _In_ PCWSTR mainPackageFamilyName)
{
    THROW_IF_FAILED(WindowsAppRuntime_VersionInfo_TestInitialize(frameworkPackageFamilyName, mainPackageFamilyName));
}

/// Shutdown VersionInfo's test support.
///
/// @note Not for product use. This is for test purposes only to verify the implementation.
inline void TestShutdown()
{
    WindowsAppRuntime_VersionInfo_TestInitialize(nullptr, nullptr);
}
}
#endif // defined(__cplusplus)

#endif // __MICROSFT_WINDOWSAPPRUNTIME_VERSIONINFO_H
