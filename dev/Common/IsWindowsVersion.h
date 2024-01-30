// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __ISWINDOWSVERSION_H
#define __ISWINDOWSVERSION_H

#include <VersionHelpers.h>

namespace WindowsVersion
{
inline bool IsExportPresent(
    PCWSTR filename,
    PCSTR functionName)
{
    wil::unique_hmodule dll{ LoadLibraryExW(filename, nullptr, 0) };
    if (!dll)
    {
        const DWORD rcLoadLibraryError = GetLastError();
        THROW_HR_IF(HRESULT_FROM_WIN32(rcLoadLibraryError), rcLoadLibraryError != ERROR_MOD_NOT_FOUND);
        return false;
    }

    auto function{ GetProcAddress(dll.get(), functionName) };
    if (!function)
    {
        const DWORD rcGetProcAddressError = GetLastError();
        THROW_HR_IF(HRESULT_FROM_WIN32(rcGetProcAddressError), rcGetProcAddressError != ERROR_PROC_NOT_FOUND);
        return false;
    }

    return true;
}

inline bool IsMinVersion(
    uint64_t minVersion)
{
    PCWSTR subkey{ L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion" };
    auto regkey{ wil::reg::open_unique_key(HKEY_LOCAL_MACHINE, subkey) };
    const uint64_t major{ wil::reg::get_value_dword(regkey.get(), L"CurrentMajorVersionNumber") };
    const uint64_t minor{ wil::reg::get_value_dword(regkey.get(), L"CurrentMinorVersionNumber") };
    const std::wstring buildAsString{ wil::reg::get_value_string(regkey.get(), L"CurrentBuildNumber") };
    const uint64_t build{ std::stoul(buildAsString.c_str(), nullptr, 10) };
    const uint64_t revision{ wil::reg::get_value_dword(regkey.get(), L"BaseBuildRevisionNumber") };
    const uint64_t version{ (major << 48) | (minor << 32) | (build << 16) | revision };
    return version >= minVersion;
}

constexpr uint64_t ToVersion64(uint32_t major, uint32_t minor=0, uint32_t build=0, uint32_t revision=0)
{
    return (static_cast<uint64_t>(major) << 48) |
           (static_cast<uint64_t>(minor) << 32) |
           (static_cast<uint64_t>(build) << 16) |
           static_cast<uint64_t>(revision);
}

inline bool IsWindows10_19H1OrGreater()
{
    // GetPackageInfo2() added to kernelbase.dll in NTDDI_WIN10_19H1 (aka Windows 10 19H1 aka 10.0.18363.0)
    return IsExportPresent(L"kernelbase.dll", "GetPackageInfo2");
}

inline bool IsWindows10_20H1OrGreater()
{
    // GetPackageInfo3() added to kernelbase.dll in NTDDI_WIN10_VB (aka Windows 10 20H1 aka 10.0.19041.0)
    return IsExportPresent(L"kernelbase.dll", "GetPackageInfo3");
}
inline bool IsWindows11_21H2OrGreater()
{
    // GetMachineTypeAttributes() added to kernelbase.dll in NTDDI_WIN10_CO (aka Windows 11 21H2 aka 10.0.22021.0)
    return IsExportPresent(L"kernelbase.dll", "GetMachineTypeAttributes");
}
inline bool IsWindows11_22H2OrGreater()
{
    // GetPackageGraphRevisionId() added to kernelbase.dll in NTDDI_WIN10_NI (aka Windows 11 22H2 aka 10.0.22621.0)
    return IsExportPresent(L"kernelbase.dll", "GetPackageGraphRevisionId");
}
inline bool IsWindows11_23H2OrGreater()
{
    // No good symbol to probe so version check (Windows 11 23H2 aka 10.0.22631.0)
    return IsMinVersion(ToVersion64(10, 0, 22631, 0));
}
inline bool IsWindows11_24H2OrGreater()
{
    // TryCreatePackageDependency2() added to  in NTDDI_WIN10_GE (aka Windows 11 24H2 aka TBD)
    return IsExportPresent(L"api-ms-win-appmodel-runtime-l1-1-7.dll", "TryCreatePackageDependency2");
}
}

#endif // __ISWINDOWSVERSION_H
