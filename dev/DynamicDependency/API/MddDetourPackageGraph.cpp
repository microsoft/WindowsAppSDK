// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

#include "MddDetourPackageGraph.h"

#include "PackageGraphManager.h"

#include "MddWin11.h"

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
    UINT32* count) = ::GetCurrentPackageInfo;

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
    UINT32* count) = nullptr;

LONG WINAPI DynamicGetCurrentPackageInfo2(
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count);

typedef HRESULT (WINAPI* GetCurrentPackageInfo2Function)(
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
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

static LONG (WINAPI* TrueGetPackageInfo2)(
    PACKAGE_INFO_REFERENCE packageInfoReference,
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count) = nullptr;

// NOTE: We don't dynamically load GetPackageInfo2 (if available)
//       but we DON'T Detour it so we don't need DynamicGetPackageInfo2()

typedef HRESULT (WINAPI* GetPackageInfo2Function)(
    PACKAGE_INFO_REFERENCE packageInfoReference,
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count);

static UINT32 (WINAPI* TrueGetPackageGraphRevisionId)() = nullptr;

HRESULT WINAPI DynamicGetPackageGraphRevisionId();

typedef UINT32 (WINAPI* GetPackageGraphRevisionIdFunction)();

HRESULT WINAPI MddDetourPackageGraphInitialize() noexcept
{
    // Use the Win11 APIs if available (instead of Detour'ing to our own implementation)
    if (MddCore::Win11::IsSupported())
    {
        RETURN_IF_FAILED(MddWin11Initialize());
        return S_OK;
    }

    // Detour package graph APIs to our implementation
    FAIL_FAST_IF_WIN32_ERROR(DetourUpdateThread(GetCurrentThread()));
    FAIL_FAST_IF_WIN32_ERROR(DetourAttach(&(PVOID&)TrueGetCurrentPackageInfo, DynamicGetCurrentPackageInfo));
    //
    // NOTE: GetCurrentPackageInfo2 requires >=19H1
    // NOTE: GetCurrentPackageInfo3 requires >=20H1
    // NOTE: GetPackageGraphRevisionId requires >=22H2
    // Support down to RS5
    if (WindowsVersion::IsWindows10_19H1OrGreater())
    {
        HMODULE dllApisetAppmodelRuntime_1_3{ LoadLibraryExW(L"api-ms-win-appmodel-runtime-l1-1-3.dll", nullptr, 0) };
        FAIL_FAST_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllApisetAppmodelRuntime_1_3);

        auto dllGetCurrentPackageInfo2{ reinterpret_cast<GetCurrentPackageInfo2Function>(GetProcAddress(dllApisetAppmodelRuntime_1_3, "GetCurrentPackageInfo2")) };
        FAIL_FAST_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllGetCurrentPackageInfo2);
        TrueGetCurrentPackageInfo2 = dllGetCurrentPackageInfo2;
        FAIL_FAST_IF_WIN32_ERROR(DetourAttach(&(PVOID&)TrueGetCurrentPackageInfo2, DynamicGetCurrentPackageInfo2));

        // Also grab GetPackageInfo2 if available (see MddGetPackageInfo1Or2() for details)
        auto dllGetPackageInfo2{ reinterpret_cast<GetPackageInfo2Function>(GetProcAddress(dllApisetAppmodelRuntime_1_3, "GetPackageInfo2")) };
        FAIL_FAST_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllGetPackageInfo2);
        TrueGetPackageInfo2 = dllGetPackageInfo2;

        if (WindowsVersion::IsWindows10_20H1OrGreater())
        {
            HMODULE dllApisetAppmodelRuntimeInternal_1_6{ LoadLibraryExW(L"api-ms-win-appmodel-runtime-internal-l1-1-6.dll", nullptr, 0) };
            FAIL_FAST_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllApisetAppmodelRuntimeInternal_1_6);

            auto dllGetCurrentPackageInfo3{ reinterpret_cast<GetCurrentPackageInfo3Function>(GetProcAddress(dllApisetAppmodelRuntimeInternal_1_6, "GetCurrentPackageInfo3")) };
            FAIL_FAST_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllGetCurrentPackageInfo3);
            TrueGetCurrentPackageInfo3 = dllGetCurrentPackageInfo3;
            FAIL_FAST_IF_WIN32_ERROR(DetourAttach(&(PVOID&)TrueGetCurrentPackageInfo3, DynamicGetCurrentPackageInfo3));

            if (WindowsVersion::IsWindows11_22H2OrGreater())
            {
                HMODULE dllApisetAppmodelRuntime_1_6{ LoadLibraryExW(L"api-ms-win-appmodel-runtime-l1-1-6.dll", nullptr, 0) };
                FAIL_FAST_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllApisetAppmodelRuntime_1_6);

                auto dllGetPackageGraphRevisionId{ reinterpret_cast<GetPackageGraphRevisionIdFunction>(GetProcAddress(dllApisetAppmodelRuntime_1_6, "GetPackageGraphRevisionId")) };
                FAIL_FAST_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllGetPackageGraphRevisionId);
                TrueGetPackageGraphRevisionId = dllGetPackageGraphRevisionId;
                FAIL_FAST_IF_WIN32_ERROR(DetourAttach(&(PVOID&)TrueGetPackageGraphRevisionId, DynamicGetPackageGraphRevisionId));
            }
        }
    }
    return S_OK;
}

HRESULT _MddDetourPackageGraphShutdown() noexcept
{
    // Use the Win11 APIs if available (instead of Detour'ing to our own implementation)
    if (MddCore::Win11::IsSupported())
    {
        MddWin11Shutdown();
        return S_OK;
    }

    // Stop Detour'ing package graph APIs to our implementation (undo in reverse order we started Detour'ing APIs)
    if (TrueGetPackageGraphRevisionId)
    {
        FAIL_FAST_IF_WIN32_ERROR(DetourDetach(&(PVOID&)TrueGetPackageGraphRevisionId, DynamicGetPackageGraphRevisionId));
        TrueGetPackageGraphRevisionId = nullptr;
    }
    if (TrueGetCurrentPackageInfo3)
    {
        FAIL_FAST_IF_WIN32_ERROR(DetourDetach(&(PVOID&)TrueGetCurrentPackageInfo3, DynamicGetCurrentPackageInfo3));
        TrueGetCurrentPackageInfo3 = nullptr;
    }
    if (TrueGetCurrentPackageInfo2)
    {
        FAIL_FAST_IF_WIN32_ERROR(DetourDetach(&(PVOID&)TrueGetCurrentPackageInfo2, DynamicGetCurrentPackageInfo2));
        TrueGetCurrentPackageInfo2 = nullptr;
    }
    FAIL_FAST_IF_WIN32_ERROR(DetourDetach(&(PVOID&)TrueGetCurrentPackageInfo, DynamicGetCurrentPackageInfo));
    TrueGetCurrentPackageInfo = ::GetCurrentPackageInfo;
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

LONG MddGetPackageInfo1Or2(
    PACKAGE_INFO_REFERENCE packageInfoReference,
    UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count)
{
    // GetPackageInfo2 is only available on Windows >= 19H1
    // Call it if available, else fall back to GetPackageInfo (v1)
    if (TrueGetPackageInfo2)
    {
        return TrueGetPackageInfo2(packageInfoReference, flags, packagePathType, bufferLength, buffer, count);
    }
    else
    {
        return ::GetPackageInfo(packageInfoReference, flags, bufferLength, buffer, count);
    }
}

HRESULT MddTrueGetCurrentPackageInfo3(
    UINT32 flags,
    PackageInfoType packageInfoType,
    UINT32* bufferLength,
    void* buffer,
    UINT32* count)
{
    // Passthru to the original (not-Detoured) Windows API
    RETURN_IF_FAILED(TrueGetCurrentPackageInfo3(flags, packageInfoType, bufferLength, buffer, count));
    return S_OK;
}

LONG WINAPI DynamicGetPackageGraphRevisionId()
{
    return MddCore::PackageGraphManager::GetPackageGraphRevisionId();
}
