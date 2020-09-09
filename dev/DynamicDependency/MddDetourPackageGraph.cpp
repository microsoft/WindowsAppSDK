// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>

#include <MddDetourPackageGraph.h>

#include <PackageGraph.h>

#include <../Detours/detours.h>

static LONG (WINAPI * TrueGetCurrentPackageInfo)(
    const UINT32 flags,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count) = GetCurrentPackageInfo;

LONG DynamicGetCurrentPackageInfo(
    const UINT32 flags,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count);

static LONG (WINAPI * TrueGetCurrentPackageInfo2)(
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count) = GetCurrentPackageInfo2;

LONG DynamicGetCurrentPackageInfo2(
    const UINT32 flags,
    PackagePathType packagePathType,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count);

HRESULT MddDetourPackageGraphInitialize() noexcept
{
    // Do we need to detour package graph APIs?
    if (DetourIsHelperProcess())
    {
        return S_OK;
    }

    // Detour package graph APIs to our implementation
    RETURN_IF_WIN32_BOOL_FALSE(DetourRestoreAfterWith());
    RETURN_IF_WIN32_ERROR(DetourTransactionBegin());
    RETURN_IF_WIN32_ERROR(DetourUpdateThread(GetCurrentThread()));
    RETURN_IF_WIN32_ERROR(DetourAttach(&(PVOID&)TrueGetCurrentPackageInfo, DynamicGetCurrentPackageInfo));
    RETURN_IF_WIN32_ERROR(DetourTransactionCommit());
    return S_OK;
}

HRESULT _MddDetourPackageGraphShutdown() noexcept
{
    // Did we detour package graph APIs?
    if (DetourIsHelperProcess())
    {
        return S_OK;
    }

    // Stop Detour'ing package graph APIs to our implementation
    RETURN_IF_WIN32_ERROR(DetourTransactionBegin());
    RETURN_IF_WIN32_ERROR(DetourUpdateThread(GetCurrentThread()));
    RETURN_IF_WIN32_ERROR(DetourDetach(&(PVOID&)TrueGetCurrentPackageInfo, DynamicGetCurrentPackageInfo));
    RETURN_IF_WIN32_ERROR(DetourTransactionCommit());
    return S_OK;
}

void MddDetourPackageGraphShutdown() noexcept
{
    _MddDetourPackageGraphShutdown();
}

LONG DynamicGetCurrentPackageInfo(
    const UINT32 flags,
    UINT32* bufferLength,
    BYTE* buffer,
    UINT32* count)
{
    return DynamicGetCurrentPackageInfo2(flags, PackagePathType_Install, bufferLength, buffer, count);
}

LONG DynamicGetCurrentPackageInfo2(
    const UINT32 /*flags*/,
    PackagePathType /*packagePathType*/,
    UINT32* /*bufferLength*/,
    BYTE* /*buffer*/,
    UINT32* count)
{
    *count = 0;

    auto lock(MddCore::AcquirePackageGraphLock());

#if defined(TODO_Detour_GetCurrentPackageInfo2)
    for (auto node : g_packageGraph)
    {
        auto packageInfoReference = node.get();
        if (node)
        {
            packageInfo += GetPackageInfo(packageInfoReference...);
        }
        else
        {
            packageInfo += TrueGetCurrentPackageInfo(...);
        }
        ++count
    }
    return ERROR_SUCCESS;
#endif
    return ERROR_NOT_SUPPORTED;
}
