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

/// Non-throwing variant using dynamic loading (safe before DLL is loaded).
inline HRESULT IsSelfContained_nothrow(bool& isSelfContained) noexcept
{
    isSelfContained = false;
    auto module = ::GetModuleHandleW(L"Microsoft.WindowsAppRuntime.dll");
    RETURN_LAST_ERROR_IF_NULL(module);
    using IsSelfContainedFn = HRESULT(__stdcall*)(BOOL*);
    auto fn = reinterpret_cast<IsSelfContainedFn>(
        ::GetProcAddress(module, "WindowsAppRuntime_IsSelfContained"));
    RETURN_LAST_ERROR_IF_NULL(fn);
    BOOL result{};
    const auto hr{ fn(&result) };
    RETURN_IF_FAILED(hr);
    isSelfContained = !!result;
    return S_OK;
}
}
#endif // defined(__cplusplus)

#endif // __MICROSFT_WINDOWSAPPRUNTIME_SELFCONTAINED_H
