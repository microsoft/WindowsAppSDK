// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __ISWINDOWSVERSION_H
#define __ISWINDOWSVERSION_H

#include <VersionHelpers.h>

namespace WindowsVersion
{
VERSIONHELPERAPI IsWindowsVersionOrGreaterEx(
    const WORD majorVersion,
    const WORD minorVersion,
    const WORD servicePackMajor,
    const WORD buildNumber)
{
    OSVERSIONINFOEXW osvi{ sizeof(osvi) };
    osvi.dwMajorVersion = majorVersion;
    osvi.dwMinorVersion = minorVersion;
    osvi.wServicePackMajor = servicePackMajor;
    osvi.dwBuildNumber = buildNumber;

    const DWORDLONG c_conditionMask{
        VerSetConditionMask(
            VerSetConditionMask(
                VerSetConditionMask(
                    VerSetConditionMask(
                        0, VER_MAJORVERSION, VER_GREATER_EQUAL),
                    VER_MINORVERSION, VER_GREATER_EQUAL),
                VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL),
            VER_BUILDNUMBER, VER_GREATER_EQUAL)
    };

    return VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR | VER_BUILDNUMBER, c_conditionMask) != FALSE;
}

VERSIONHELPERAPI IsWindows10_19H1OrGreater()
{
    const WORD c_win10_19h1_build{ 18362 };
    return IsWindowsVersionOrGreaterEx(HIBYTE(_WIN32_WINNT_WIN10), LOBYTE(_WIN32_WINNT_WIN10), 0, c_win10_19h1_build);
}

VERSIONHELPERAPI IsWindows10_20H1OrGreater()
{
    const WORD c_win10_20h1_build{ 19041 };
    return IsWindowsVersionOrGreaterEx(HIBYTE(_WIN32_WINNT_WIN10), LOBYTE(_WIN32_WINNT_WIN10), 0, c_win10_20h1_build);
}
}

#endif // __ISWINDOWSVERSION_H
