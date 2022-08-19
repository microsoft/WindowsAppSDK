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
    }
    return false;
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
}

#endif // __ISWINDOWSVERSION_H
