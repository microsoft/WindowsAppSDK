// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __MICROSFT_WINDOWSAPPRUNTIME_SELFCONTAINED_H
#define __MICROSFT_WINDOWSAPPRUNTIME_SELFCONTAINED_H

/// Determine if Windows App SDK in use by the current process is deployed Self-Contained (vs deployed as MSIX packages)
///
/// @param isSelfContained TRUE if WindowsAppSDK/Self-Contained.
STDAPI WindowsAppRuntime_IsSelfContained(
    BOOL* isSelfContained) noexcept;

#if defined(__cplusplus)
namespace WindowsAppRuntime::SelfContained
{
/// Return true if Windows App SDK in use by the current process is deployed Self-Contained.
inline bool IsSelfContained()
{
    BOOL isSelfContained{};
    THROW_IF_FAILED(WindowsAppRuntime_IsSelfContained(&isSelfContained));
    return !!isSelfContained;
}
}
#endif // defined(__cplusplus)

#endif // __MICROSFT_WINDOWSAPPRUNTIME_SELFCONTAINED_H
