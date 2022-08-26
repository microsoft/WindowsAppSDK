// Copyright (c) Microsoft Corporation.
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
    // GetPackageInfo2() added to kernelbase.dll in NTDDI_WIN10_19H1 (aka 19H1)
    return IsExportPresent(L"kernelbase.dll", "GetPackageInfo2");
}

inline bool IsWindows10_20H1OrGreater()
{
    // GetPackageInfo3() added to kernelbase.dll in NTDDI_WIN10_VB (aka 20H1)
    return IsExportPresent(L"kernelbase.dll", "GetPackageInfo3");
}
inline bool IsWindows11_21H2OrGreater()
{
    // GetMachineTypeAttributes() added to kernelbase.dll in NTDDI_WIN10_CO (aka Windows 11 21H2)
    return IsExportPresent(L"kernelbase.dll", "GetMachineTypeAttributes");
}
}

#endif // __ISWINDOWSVERSION_H
