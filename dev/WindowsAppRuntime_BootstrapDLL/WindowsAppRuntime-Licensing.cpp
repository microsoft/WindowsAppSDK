// Copyright (c) Microsoft Corporation. All rights reserved.

#include "pch.h"

#include "WindowsAppRuntime-Licensing.h"

#include <msixlicensing.h>

static std::filesystem::path GetPathForPackage(
    PCWSTR packageFullName)
{
    // Get the package's path
    //
    // NOTE: Use GetStagedPackagePathByFullName as don't care if the package is registered.
    //
    // NOTE: Don't use GetStagedPackagePathByFullName2 as we want the *install* location
    //       (not e.g. modifiable location). Plus Get...2() is new in 20H1 (too new for us)
    //       where Get...() exists down to Win81. In this case simplest is bestest.
    wil::unique_cotaskmem_string packagePathBufferDynamic;
    uint32_t packagePathLength{};
    const auto rc{ GetStagedPackagePathByFullName(packageFullName, &packagePathLength, nullptr) };
    if (rc != ERROR_INSUFFICIENT_BUFFER)
    {
        THROW_HR_MSG(HRESULT_FROM_WIN32(rc), "PackageFullName:%ls", packageFullName);
    }
    auto packagePath{ wil::make_cotaskmem_string(nullptr, packagePathLength) };
    THROW_IF_WIN32_ERROR(GetStagedPackagePathByFullName(packageFullName, &packagePathLength, packagePath.get()));
    std::filesystem::path path{ packagePath.get() };
    return path;
}

static HMODULE LoadMsixLicensingApisAtPath(
    const std::filesystem::path& path)
{
    auto windowsAppRuntimeDllFilename{ path };
    windowsAppRuntimeDllFilename /= L"Microsoft.WindowsAppRuntime.dll";
    auto windowsAppRuntimeDll(LoadLibraryEx(windowsAppRuntimeDllFilename.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH ));
    if (!windowsAppRuntimeDll)
    {
        const auto lastError{ GetLastError() };
        THROW_WIN32_MSG(lastError, "Error in LoadLibrary: %d (0x%X) loading %ls", lastError, lastError, windowsAppRuntimeDllFilename.c_str());
    }
    return windowsAppRuntimeDll;
}

static HMODULE LoadMsixLicensingApisInPackage(
    PCWSTR packageFullName)
{
    auto path{ GetPathForPackage(packageFullName) };
    return LoadMsixLicensingApisAtPath(path);
}

static HMODULE LoadMsixLicensingApisInRelease(
    UINT32 majorMinorVersion,
    PCWSTR versionTag)
{
    // Licenses are only needed for Stable releases (versionTag=null or "")
    if (versionTag && (versionTag[0] != L'\0'))
    {
        // Nothing to do!
        return nullptr;
    }

    // Find a package in the family
    const UINT16 majorVersion{ HIWORD(majorMinorVersion) };
    const UINT16 minorVersion{ LOWORD(majorMinorVersion) };
    WCHAR packageFamilyName[PACKAGE_FAMILY_NAME_MAX_LENGTH + 1]{};
    wsprintf(packageFamilyName, L"Microsoft.WindowsAppRuntime.%hu.%hu_8wekyb3d8bbwe", majorVersion, minorVersion);

    // Find a framework package in the family (any will do)
    winrt::Windows::Management::Deployment::PackageManager packageManager;
    winrt::hstring currentUser;
    const auto c_packageTypes{ winrt::Windows::Management::Deployment::PackageTypes::Framework };
    for (auto package : packageManager.FindPackagesForUserWithPackageTypes(currentUser, packageFamilyName, c_packageTypes))
    {
        // Load the Licensing APIs' implementation
        const auto packageId{ package.Id() };
        const auto packageFullName{ packageId.FullName() };
        return LoadMsixLicensingApisInPackage(packageFullName.c_str());
    }

    // No framework package found in the family
    THROW_HR_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), "PackageFamilyName:%ls", packageFamilyName);
}

STDAPI WindowsAppRuntime_InstallLicenses(
    UINT32 majorMinorVersion,
    PCWSTR versionTag) noexcept try
{
    // Explicitly load the DLL before using it
    // NOTE: It doesn't need to be Register'd for the caller
    //       but it must be at least Stage'd for this to work.
    //
    // NOTE: Yes, this is a rather unusual usage. It's a very specific way
    //       that's safe for this specific case. Be very careful if/when
    //       changing this logic. And DON'T consider this license <heh>
    //       to use packages without being registered (and the usual
    //       unpackaged-processes-need-DynamicDependencies rules).
    //       This is the exception that proves the rule.
    wil::unique_hmodule windowsAppRuntimeDll{ LoadMsixLicensingApisInRelease(majorMinorVersion, versionTag) };
    if (windowsAppRuntimeDll)
    {
        RETURN_IF_FAILED(MsixInstallLicenses(majorMinorVersion, versionTag));
    }
    return S_OK;
}
CATCH_RETURN();

STDAPI WindowsAppRuntime_InstallLicensesInPackage(
    PCWSTR frameworkPackageFullName) noexcept try
{
    // Explicitly load the DLL before using it
    // NOTE: It doesn't need to be Register'd for the caller
    //       but it must be at least Stage'd for this to work.
    //
    // NOTE: Yes, this is a rather unusual usage. It's a very specific way
    //       that's safe for this specific case. Be very careful if/when
    //       changing this logic. And DON'T consider this license <heh>
    //       to use packages without being registered (and the usual
    //       unpackaged-processes-need-DynamicDependencies rules).
    //       This is the exception that proves the rule.
    wil::unique_hmodule windowsAppRuntimeDll{ LoadMsixLicensingApisInPackage(frameworkPackageFullName) };
    if (windowsAppRuntimeDll)
    {
        RETURN_IF_FAILED(MsixInstallLicensesInPackage(frameworkPackageFullName));
    }
    return S_OK;
}
CATCH_RETURN();

