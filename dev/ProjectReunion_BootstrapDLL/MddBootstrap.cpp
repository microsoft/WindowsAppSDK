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
    const CLSID& appDynamicDependencyLifetimeManager)
{
    wil::com_ptr_nothrow<IDynamicDependencyLifetimeManager> lifetimeManager;
    RETURN_IF_FAILED(CoCreateInstance(appDynamicDependencyLifetimeManager, nullptr, CLSCTX_LOCAL_SERVER, __uuidof(IDynamicDependencyLifetimeManager), reinterpret_cast<void**>(lifetimeManager.addressof())));

    RETURN_IF_FAILED(lifetimeManager->Initialize());

    wil::unique_cotaskmem_string packageFullName;
    RETURN_IF_FAILED(lifetimeManager->GetPackageFullName(&packageFullName));

    wil::unique_cotaskmem_ptr<BYTE[]> packageInfoBuffer;
    const PACKAGE_INFO* frameworkPackageInfo = nullptr;
    RETURN_IF_FAILED(GetFrameworkPackageInfoForPackage(packageFullName.get(), frameworkPackageInfo, packageInfoBuffer));

    RETURN_IF_FAILED(AddFrameworkToPath(frameworkPackageInfo->path));

    g_lifetimeManager = lifetimeManager.detach();
    return S_OK;
}

STDAPI_(void) MddBootstrapShutdown()
{
    if (!g_lifetimeManager)
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
    }
}

HRESULT GetFrameworkPackageInfoForPackage(PCWSTR packageFullName, const PACKAGE_INFO*& frameworkPackageInfo, wil::unique_cotaskmem_ptr<BYTE[]>& packageInfoBuffer)
{
    frameworkPackageInfo = nullptr;

    wil::unique_package_info_reference packageInfoReference;
    RETURN_IF_WIN32_ERROR(OpenPackageInfoByFullName(packageFullName, 0, &packageInfoReference));
    UINT32 bufferLength = 0;
    const auto hr = HRESULT_FROM_WIN32(GetPackageInfo(packageInfoReference.get(), PACKAGE_FILTER_DIRECT, &bufferLength, nullptr, nullptr));
    RETURN_HR_IF(hr, hr != HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER));
    packageInfoBuffer = wil::make_unique_cotaskmem_nothrow<BYTE[]>(bufferLength);
    RETURN_IF_NULL_ALLOC(packageInfoBuffer);
    UINT32 packageInfoCount = 0;
    RETURN_IF_WIN32_ERROR(GetPackageInfo(packageInfoReference.get(), PACKAGE_FILTER_DIRECT, &bufferLength, packageInfoBuffer.get(), &packageInfoCount));

    const PACKAGE_INFO* packageInfo = reinterpret_cast<const PACKAGE_INFO*>(packageInfoBuffer.get());
    for (size_t index = 0; index < packageInfoCount; ++index, ++packageInfo)
    {
        PCWSTR frameworkPackageFamilyName = L"Microsoft.ProjectReunionFramework_8wekyb3d8bbwe";
        if (CompareStringOrdinal(packageInfo->packageFamilyName, -1, frameworkPackageFamilyName, -1, TRUE) == CSTR_EQUAL)
        {
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

HRESULT AddFrameworkToPath(PCWSTR frameworkPath)
{
    // Add the framework to the Loader's DllDirectory list
    auto dllDirectoryCookie = AddDllDirectory(frameworkPath);
    RETURN_LAST_ERROR_IF(dllDirectoryCookie == 0);

    auto on_exit = wil::scope_exit([dllDirectoryCookie] {
        if (dllDirectoryCookie)
        {
            RemoveDllDirectory(dllDirectoryCookie);
        }
    });

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

    g_frameworkPath = wistd::move(frameworkPathCopy);
    g_dllDirectoryCookie = dllDirectoryCookie;
    dllDirectoryCookie = 0;
    return S_OK;
}
