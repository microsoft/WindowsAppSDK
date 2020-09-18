// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "MddBootstrap.h"

#include "IDynamicDependencyLifetimeManager.h"

HRESULT GetFrameworkPackageInfoForPackage(PCWSTR packageFullName, const PACKAGE_INFO*& frameworkPackageInfo, wil::unique_cotaskmem_ptr<BYTE[]>& packageInfoBuffer);
HRESULT AddFrameworkToPath(PCWSTR  path);

IDynamicDependencyLifetimeManager* g_lifetimeManager = nullptr;
DLL_DIRECTORY_COOKIE g_dllDirectoryCookie = 0;
wil::unique_cotaskmem_string g_frameworkPath;

STDAPI MddBootstrapInitialize(
    const CLSID& appDynamicDependencyLifetimeManager) noexcept try
{
    FAIL_FAST_HR_IF(HRESULT_FROM_WIN32(ERROR_ALREADY_INITIALIZED), g_lifetimeManager != nullptr);
    FAIL_FAST_HR_IF(HRESULT_FROM_WIN32(ERROR_ALREADY_INITIALIZED), g_dllDirectoryCookie != 0);
    FAIL_FAST_HR_IF(HRESULT_FROM_WIN32(ERROR_ALREADY_INITIALIZED), g_frameworkPath);

    wil::com_ptr_nothrow<IDynamicDependencyLifetimeManager> lifetimeManager(wil::CoCreateInstance<IDynamicDependencyLifetimeManager>(appDynamicDependencyLifetimeManager, CLSCTX_LOCAL_SERVER));

    THROW_IF_FAILED(lifetimeManager->Initialize());

    wil::unique_cotaskmem_string packageFullName;
    THROW_IF_FAILED(lifetimeManager->GetPackageFullName(&packageFullName));

    wil::unique_cotaskmem_ptr<BYTE[]> packageInfoBuffer;
    const PACKAGE_INFO* frameworkPackageInfo = nullptr;
    THROW_IF_FAILED(GetFrameworkPackageInfoForPackage(packageFullName.get(), frameworkPackageInfo, packageInfoBuffer));

    THROW_IF_FAILED(AddFrameworkToPath(frameworkPackageInfo->path));

    g_lifetimeManager = lifetimeManager.detach();
    return S_OK;
}
CATCH_RETURN();

STDAPI_(void) MddBootstrapShutdown() noexcept
{
    if (g_lifetimeManager)
    {
        (void)LOG_IF_FAILED(g_lifetimeManager->Shutdown());
        g_lifetimeManager->Release();
        g_lifetimeManager = nullptr;
    }

    if (g_dllDirectoryCookie != 0)
    {
        RemoveDllDirectory(g_dllDirectoryCookie);
        g_dllDirectoryCookie = 0;
    }

    if (g_frameworkPath)
    {
        //TODO: Revisit once MddAddPackageDependency is lit up
        wil::unique_cotaskmem_string path;
        const auto hr = wil::TryGetEnvironmentVariableW(L"PATH", path);
        if (SUCCEEDED(hr) && path)
        {
            const auto frameworkPathLength = wcslen(g_frameworkPath.get());
            PCWSTR pathWithoutFrameworkPath = g_frameworkPath.get() + frameworkPathLength;
            if (*pathWithoutFrameworkPath == L';')
            {
                ++pathWithoutFrameworkPath;
            }
            (void)LOG_IF_WIN32_BOOL_FALSE(SetEnvironmentVariableW(L"PATH", pathWithoutFrameworkPath));
        }

        g_frameworkPath.reset();
    }
}

//TODO:Change error handle to exceptions
/// Determine the path for the Project Reunion Framework package
HRESULT GetFrameworkPackageInfoForPackage(PCWSTR packageFullName, const PACKAGE_INFO*& frameworkPackageInfo, wil::unique_cotaskmem_ptr<BYTE[]>& packageInfoBuffer)
{
    frameworkPackageInfo = nullptr;
    packageInfoBuffer.reset();

    // We need to determine the exact Project Reunion Framework package
    // in the sidecar package's dependencies, as resolved by Windows.
    // A user can have multiple framework packages in a family registered
    // at a time, for multiple reasons:
    //
    //   * Multiple Architectures -- x86/x64 on an x64 machine, x86/arm/arm64/x86ona64 on an arm64 machine, etc
    //   * Multiple Versions -- v1.0.0.0 in use by processes running as pkg1 and v1.0.0.1 in use by runnings running as pkg2
    //                          or v1.0.0.0 in use by running processes and v1.0.0.1 in package graphs for packages w/no running process
    //
    // Thus FindPackagesByPackageFamily(pkgfamilyname,...) and PackageManager.FindPackages(user="", pkgfamilyname) could be ambiguous.
    // We need the actual dependency graph known to Windows for the sidecar package where we got our LifetimeManager.
    // That leaves us few options:
    //
    //   * PackageManager.FindPackage(user="", lifetimeManager->GetPackageFullName()).Dependencies
    //   * GetPackageInfo(OpenPackageInfoByFullName(lifetimeManager->GetPackageFullName())
    //
    // We'll go with the latter as the simpler (no COM/WinRT) and more performant solution.

    // Fetch the package graph for the package (per packageFullName)
    wil::unique_package_info_reference packageInfoReference;
    RETURN_IF_WIN32_ERROR(OpenPackageInfoByFullName(packageFullName, 0, &packageInfoReference));
    UINT32 bufferLength = 0;
    UINT32 packageInfoCount = 0;
    const auto hr = HRESULT_FROM_WIN32(GetPackageInfo(packageInfoReference.get(), PACKAGE_FILTER_DIRECT, &bufferLength, nullptr, &packageInfoCount));
    RETURN_HR_IF(hr, hr != HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER));
    RETURN_HR_IF(E_UNEXPECTED, packageInfoCount == 0);
    auto buffer = wil::make_unique_cotaskmem_nothrow<BYTE[]>(bufferLength);
    RETURN_IF_NULL_ALLOC(buffer);
    RETURN_IF_WIN32_ERROR(GetPackageInfo(packageInfoReference.get(), PACKAGE_FILTER_DIRECT, &bufferLength, buffer.get(), &packageInfoCount));

    // Find the Project Reunion Framework package in the package graph to determine its path
    const PACKAGE_INFO* packageInfo = reinterpret_cast<const PACKAGE_INFO*>(buffer.get());
    for (size_t index = 0; index < packageInfoCount; ++index, ++packageInfo)
    {
        PCWSTR frameworkPackageFamilyName = L"Microsoft.ProjectReunion.Framework_8wekyb3d8bbwe";
        if (CompareStringOrdinal(packageInfo->packageFamilyName, -1, frameworkPackageFamilyName, -1, TRUE) == CSTR_EQUAL)
        {
            packageInfoBuffer = std::move(buffer);
            frameworkPackageInfo = packageInfo;
            return S_OK;
        }
    }

    // We didn't find the framework package as a dependency of the package
    // providing the LifetimeManager.
    //
    // Verify the package providing the LifetimeManager declares
    // <PackageDependency> on the Project Reunion Framework package.
    RETURN_WIN32(APPMODEL_ERROR_PACKAGE_NOT_AVAILABLE);
}

//TODO:Change error handle to exceptions
HRESULT AddFrameworkToPath(PCWSTR frameworkPath)
{
    // Add the framework to the Loader's DllDirectory list
    wil::unique_dll_directory_cookie dllDirectoryCookie{ AddDllDirectory(frameworkPath) };
    RETURN_LAST_ERROR_IF_NULL(dllDirectoryCookie);

    // Make a copy of the framework path to save for later
    wil::unique_cotaskmem_string frameworkPathCopy(wil::make_cotaskmem_string_nothrow(frameworkPath));
    RETURN_IF_NULL_ALLOC(frameworkPathCopy);

    // Add the framework the the PATH environment variable
    wil::unique_cotaskmem_string path;
    RETURN_IF_FAILED(wil::GetEnvironmentVariableW(L"PATH", path));
    if (path)
    {
        // PATH = frameworkPath + ";" + path
        wil::unique_cotaskmem_string newPath;
        RETURN_IF_FAILED(wil::str_concat_nothrow(newPath, frameworkPathCopy, L";", path));
        RETURN_IF_WIN32_BOOL_FALSE(SetEnvironmentVariableW(L"PATH", newPath.get()));
    }
    else
    {
        const auto lastError = GetLastError();
        RETURN_HR_IF(HRESULT_FROM_WIN32(lastError), lastError != ERROR_ENVVAR_NOT_FOUND);
        RETURN_IF_WIN32_BOOL_FALSE(SetEnvironmentVariableW(L"PATH", frameworkPath));
    }

    g_frameworkPath = std::move(frameworkPathCopy);
    g_dllDirectoryCookie = dllDirectoryCookie.release();
    dllDirectoryCookie = 0;
    return S_OK;
}
