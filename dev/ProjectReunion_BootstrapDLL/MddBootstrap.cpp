// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "MddBootstrap.h"

#include "IDynamicDependencyLifetimeManager.h"

STDAPI AddFrameworkToPath(PCWSTR  path);

IDynamicDependencyLifetimeManager* g_lifetimeManager = nullptr;
DLL_DIRECTORY_COOKIE g_dllDirectoryCookie = 0;
wil::unique_cotaskmem_string g_frameworkPath;

STDAPI MddBootstrapInitialize(
    const CLSID& appDynamicDependencyLifetimeManager)
{
    wil::com_ptr_nothrow<IDynamicDependencyLifetimeManager> lifetimeManager;
    RETURN_IF_FAILED(CoCreateInstance(appDynamicDependencyLifetimeManager, nullptr, CLSCTX_LOCAL_SERVER, __uuidof(IDynamicDependencyLifetimeManager), reinterpret_cast<void**>(lifetimeManager.addressof())));

    wil::unique_cotaskmem_string path;
    RETURN_IF_FAILED(lifetimeManager->GetFrameworkPath(path.addressof()));

    RETURN_IF_FAILED(AddFrameworkToPath(path.get()));

    g_lifetimeManager = lifetimeManager.detach();
    return S_OK;
}

STDAPI MddBootstrapShutdown()
{
    if (!g_lifetimeManager)
    {
        RETURN_IF_FAILED(g_lifetimeManager->Shutdown());
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

    return S_OK;
}

STDAPI AddFrameworkToPath(PCWSTR frameworkPath)
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
