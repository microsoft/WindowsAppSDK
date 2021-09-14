// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <VersionHelpers.h>

#include "MddDetourPackageGraph.h"

#include "PackageGraphManager.h"

#include <../Detours/detours.h>

// Windows provides HRESULT_FROM_WIN32() but not the reverse. We need that for compat reasons.
// Define WIN32_FROM_HRESULT() to covert an HRESULT to a Win32 Error Code if the HRESULT's facility
// is FACILITY_WIN32. See https://devblogs.microsoft.com/oldnewthing/20061103-07/?p=29133 for more details
#if !defined(WIN32_FROM_HRESULT)
inline DWORD Win32FromHResult(const HRESULT hr)
{
    if (HRESULT_FACILITY(hr) == FACILITY_WIN32)
    {
        return static_cast<DWORD>(HRESULT_CODE(hr));
    }
    else
    {
        return static_cast<DWORD>(hr);
    }
}
#define WIN32_FROM_HRESULT(hr) Win32FromHResult(hr)
#endif

static LONG (WINAPI* TrueGetCurrentPackageInfo)(
    const UINT32 flags,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count) = GetCurrentPackageInfo;

LONG WINAPI DynamicGetCurrentPackageInfo(
    const UINT32 flags,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count);

static LONG (WINAPI* TrueGetCurrentPackageInfo2)(
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count) = GetCurrentPackageInfo2;

LONG WINAPI DynamicGetCurrentPackageInfo2(
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count);

HRESULT WINAPI StubGetCurrentPackageInfo3(
    UINT32 flags,
    PackageInfoType packageInfoType,
    UINT32* bufferLength,
    void* buffer,
    UINT32* count);

static HRESULT (WINAPI* TrueGetCurrentPackageInfo3)(
    UINT32 flags,
    PackageInfoType packageInfoType,
    UINT32* bufferLength,
    void* buffer,
    UINT32* count) = nullptr;

HRESULT WINAPI DynamicGetCurrentPackageInfo3(
    UINT32 flags,
    PackageInfoType packageInfoType,
    UINT32* bufferLength,
    void* buffer,
    UINT32* count);

typedef HRESULT (WINAPI* GetCurrentPackageInfo3Function)(
    UINT32 flags,
    PackageInfoType packageInfoType,
    UINT32* bufferLength,
    void* buffer,
    UINT32* count);

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

VERSIONHELPERAPI IsWindows10_20H1OrGreater()
{
    const WORD c_win10_20h1_build{ 19041 };
    return IsWindowsVersionOrGreaterEx(HIBYTE(_WIN32_WINNT_WIN10), LOBYTE(_WIN32_WINNT_WIN10), 0, c_win10_20h1_build);
}

HRESULT WINAPI MddDetourPackageGraphInitialize() noexcept
{
    // Detour package graph APIs to our implementation
    FAIL_FAST_IF_WIN32_ERROR(DetourUpdateThread(GetCurrentThread()));
    FAIL_FAST_IF_WIN32_ERROR(DetourAttach(&(PVOID&)TrueGetCurrentPackageInfo, DynamicGetCurrentPackageInfo));
    FAIL_FAST_IF_WIN32_ERROR(DetourAttach(&(PVOID&)TrueGetCurrentPackageInfo2, DynamicGetCurrentPackageInfo2));
    if (IsWindows10_20H1OrGreater())
    {
        HMODULE dllKernelbase{ LoadLibraryExW(L"kernelbase.dll", nullptr, 0) };
        FAIL_FAST_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllKernelbase);

        auto dllGetCurrentPackageInfo3{ reinterpret_cast<GetCurrentPackageInfo3Function>(GetProcAddress(dllKernelbase, "GetCurrentPackageInfo3")) };
        FAIL_FAST_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllGetCurrentPackageInfo3);

        TrueGetCurrentPackageInfo3 = dllGetCurrentPackageInfo3;

        FAIL_FAST_IF_WIN32_ERROR(DetourAttach(&(PVOID&)TrueGetCurrentPackageInfo3, DynamicGetCurrentPackageInfo3));
    }
    return S_OK;
}

HRESULT _MddDetourPackageGraphShutdown() noexcept
{
    // Stop Detour'ing package graph APIs to our implementation
    FAIL_FAST_IF_WIN32_ERROR(DetourDetach(&(PVOID&)TrueGetCurrentPackageInfo, DynamicGetCurrentPackageInfo));
    FAIL_FAST_IF_WIN32_ERROR(DetourDetach(&(PVOID&)TrueGetCurrentPackageInfo2, DynamicGetCurrentPackageInfo2));
    if (TrueGetCurrentPackageInfo3)
    {
        FAIL_FAST_IF_WIN32_ERROR(DetourDetach(&(PVOID&)TrueGetCurrentPackageInfo3, DynamicGetCurrentPackageInfo3));
    }
    return S_OK;
}

void WINAPI MddDetourPackageGraphShutdown() noexcept
{
    _MddDetourPackageGraphShutdown();
}

LONG WINAPI DynamicGetCurrentPackageInfo(
    const UINT32 flags,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count)
{
    return DynamicGetCurrentPackageInfo2(flags, PackagePathType_Install, bufferLength, buffer, count);
}

LONG WINAPI DynamicGetCurrentPackageInfo2(
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count)
{
    // Legacy callers may not be aware of dynamic packages and a common mistake is to assume PACKAGE_FILTER_HEAD will return the
    // main package as the first entry which is not going to be true when packages have been added dynamically to the head of the graph.
    // Maintain pre-dynamic behavior by requiring the caller to opt into receiving dynamic packages.
    auto localFlags{ flags };
    if (WI_IsFlagClear(localFlags, PACKAGE_FILTER_DYNAMIC))
    {
        WI_SetFlag(localFlags, PACKAGE_FILTER_STATIC);
    }
    return WIN32_FROM_HRESULT(DynamicGetCurrentPackageInfo3(localFlags, static_cast<PackageInfoType>(packagePathType), bufferLength, buffer, count));
}

LONG WINAPI DynamicGetCurrentPackageInfo3(
    UINT32 flags,
    PackageInfoType packageInfoType,
    UINT32* bufferLength,
    void* buffer,
    UINT32* count)
{
    return MddCore::PackageGraphManager::GetCurrentPackageInfo3(flags, packageInfoType, bufferLength, buffer, count);
}

LONG WINAPI GetCurrentStaticPackageInfo(
    const UINT32 flags,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count) noexcept
{
    return TrueGetCurrentPackageInfo(flags, bufferLength, buffer, count);
}
