// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <appmodel.h>

#define PACKAGE_PROPERTY_STATIC             0x00080000
#define PACKAGE_FILTER_STATIC               PACKAGE_PROPERTY_STATIC
#define PACKAGE_PROPERTY_DYNAMIC            0x00100000
#define PACKAGE_FILTER_DYNAMIC              PACKAGE_PROPERTY_DYNAMIC

typedef enum PackageInfoType
{
    PackageInfoType_PackageInfoInstallPath = 0,
    PackageInfoType_PackageInfoMutablePath = 1,
    PackageInfoType_PackageInfoEffectivePath = 2,
    PackageInfoType_PackageInfoMachineExternalPath = 3,
    PackageInfoType_PackageInfoUserExternalPath = 4,
    PackageInfoType_PackageInfoEffectiveExternalPath = 5,
    // Reserve 6-15
    PackageInfoType_PackageInfoGeneration = 16,
} PackageInfoType;

inline PackagePathType ToPackagePathType(const PackageInfoType packageInfoType)
{
    return static_cast<PackagePathType>(packageInfoType);
}

extern "C" HRESULT WINAPI GetCurrentPackageInfo3(
    _In_ UINT32 flags,
    _In_ PackageInfoType packageInfoType,
    _Inout_ UINT32* bufferLength,
    _Out_writes_bytes_opt_(*bufferLength) void* buffer,
    _Out_opt_ UINT32* count);

// Modern variants of appmodel.h
namespace appmodel
{
inline std::wstring GetPackagePath(PCWSTR packageFullName)
{
    // Paths can be long but typically short(ish). We can use a quick fixed buffer
    // as an optimization and fallback to dynamic allocation if need be
    WCHAR path[MAX_PATH];
    UINT32 pathLength{ ARRAYSIZE(path) };
    const auto rc{ ::GetPackagePathByFullName(packageFullName, &pathLength, path) };
    if (rc == ERROR_SUCCESS)
    {
        return std::wstring(path);
    }
    else if (rc != ERROR_INSUFFICIENT_BUFFER)
    {
        THROW_WIN32(rc);
    }

    // It's bigger than a breadbox. Allocate memory
    std::unique_ptr<WCHAR[]> pathBuffer{ std::make_unique<WCHAR[]>(pathLength) };
    THROW_IF_NULL_ALLOC(pathBuffer);
    THROW_IF_WIN32_ERROR(::GetPackagePathByFullName(packageFullName, &pathLength, pathBuffer.get()));
    return std::wstring(pathBuffer.get());
}
}
