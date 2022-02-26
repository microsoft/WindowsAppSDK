// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __MICROSFT_WINDOWSAPPRUNTIME_SELFCONTAINED_H
#define __MICROSFT_WINDOWSAPPRUNTIME_SELFCONTAINED_H

/// Determine if Windows App SDK in use by the current process is deployed Self-Contained (vs deployed as MSIX packages)
///
/// @param isSelfContained TRUE if WindowsAppSDK/Self-Contained.
STDAPI WindowsAppRuntime_IsSelfContained(
    BOOL* isSelfContained) noexcept;

/// Initialize SelfContained's test support. This will constrain package enumeration
/// and matching for test purposes.
///
/// @param frameworkPackageFamilyName only match framework packages with this family name
///
/// @note Not for product use. This is for test purposes only to verify the implementation.
STDAPI WindowsAppRuntime_SelfContainedTestInitialize(
    _In_ PCWSTR frameworkPackageFamilyName) noexcept;

#if defined(__cplusplus)
/// Return true if Windows App SDK in use by the current process is deployed Self-Contained.
namespace WindowsAppRuntime::SelfContained
{
inline bool IsSelfContained()
{
    BOOL isSelfContained{};
    THROW_IF_FAILED(WindowsAppRuntime_IsSelfContained(&isSelfContained));
    return !!isSelfContained;
}

/// Initialize SelfContained's test support. This will constrain package enumeration
/// and matching for test purposes.
///
/// @param frameworkPackageFamilyName only match framework packages with this family name
///
/// @note Not for product use. This is for test purposes only to verify the implementation.
inline void TestInitialize(
    _In_ PCWSTR frameworkPackageFamilyName)
{
    THROW_IF_FAILED(WindowsAppRuntime_SelfContainedTestInitialize(frameworkPackageFamilyName));
}
}
#endif // defined(__cplusplus)

#endif // __MICROSFT_WINDOWSAPPRUNTIME_SELFCONTAINED_H
