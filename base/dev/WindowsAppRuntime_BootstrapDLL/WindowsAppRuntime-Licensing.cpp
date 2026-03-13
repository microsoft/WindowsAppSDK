// Copyright (c) Microsoft Corporation and Contributors.

#include "pch.h"

#include "WindowsAppRuntime-Licensing.h"

#include <msixlicensing.h>

using PFN_MsixInstallLicenses = HRESULT(STDAPICALLTYPE*)();

STDAPI WindowsAppRuntime_InstallLicenses() noexcept try
{
    // Dynamically load the Foundation DLL to call MsixInstallLicenses
    auto windowsAppRuntimeDll = wil::unique_hmodule(LoadLibraryExW(L"Microsoft.WindowsAppRuntime.dll", nullptr, 0));
    RETURN_LAST_ERROR_IF_NULL_MSG(windowsAppRuntimeDll, "Failed to load Microsoft.WindowsAppRuntime.dll for licensing");

    auto pfnInstall = reinterpret_cast<PFN_MsixInstallLicenses>(
        GetProcAddress(windowsAppRuntimeDll.get(), "MsixInstallLicenses"));
    RETURN_LAST_ERROR_IF_NULL_MSG(pfnInstall, "Failed to resolve MsixInstallLicenses");

    RETURN_IF_FAILED(pfnInstall());
    return S_OK;
}
CATCH_RETURN();
