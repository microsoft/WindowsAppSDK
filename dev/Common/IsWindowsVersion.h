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

inline bool IsWindows10_19H1OrGreater()
{
    // GetPackageInfo2() added to kernelbase.dll in 19H1 (aka NTDDI_WIN10_19H1)
    return IsExportPresent(L"kernelbase.dll", "GetPackageInfo2");
}

inline bool IsWindows10_20H1OrGreater()
{
    // GetPackageInfo3() added to kernelbase.dll in 20H1 (aka NTDDI_WIN10_VB)
    return IsExportPresent(L"kernelbase.dll", "GetPackageInfo3");
}
inline bool IsWindows11_21H2OrGreater()
{
    // GetMachineTypeAttributes() added to kernelbase.dll in Windows 11 21H2 (aka NTDDI_WIN10_CO)
    return IsExportPresent(L"kernelbase.dll", "GetMachineTypeAttributes");
}
inline bool IsWindows11_22H2OrGreater()
{
    // GetPackageGraphRevisionId() added to kernelbase.dll in Windows 11 22H2 (aka NTDDI_WIN10_NI)
    return IsExportPresent(L"kernelbase.dll", "GetPackageGraphRevisionId");
}
inline bool IsWindows11_24H1OrGreater()
{
    // TryCreatePackageDependency2() added to  in Windows 11 24H1 (aka NTDDI_WIN11_GE)
    return IsExportPresent(L"kernelbase.dll", "TryCreatePackageDependency2");
}
inline bool IsWindows11_24H2OrGreater()
{
    // MsixIsPackageFeatureSupported() added to  in Windows 11 24H2 (aka NTDDI_WIN11_GE)
    return IsExportPresent(L"appxdeploymentclient.dll", "MsixIsPackageFeatureSupported");
}
}

#endif // __ISWINDOWSVERSION_H
