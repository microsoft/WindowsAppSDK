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
    if (dll)
    {
        auto function{ GetProcAddress(dll.get(), functionName) };
        if (function)
        {
            return true;
        }
        else
        {
            DWORD getProcAddressError = GetLastError();
            if (getProcAddressError != ERROR_PROC_NOT_FOUND)
            {
                THROW_HR(HRESULT_FROM_WIN32(getProcAddressError));
            }
            return false;
        }
    }
    THROW_LAST_ERROR();
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
