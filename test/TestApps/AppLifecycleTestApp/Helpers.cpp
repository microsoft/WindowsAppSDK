// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include "Helpers.h"
#include <TestDef.h>

const wchar_t* g_bootStrapDllName = L"Microsoft.WindowsAppRuntime.Bootstrap.dll";

typedef HRESULT (*BootStrapTestInit)(PCWSTR ddlmPrefix, PCWSTR publisherId, PCWSTR frameworkPrefix, PCWSTR mainPrefix);
typedef HRESULT (*BootStrapInit)(const UINT32 majorMinorVersion, PCWSTR versionTag, const PACKAGE_VERSION minVersion);
typedef void (*BootStrapShutdown)();

void SignalPhase(const std::wstring& phaseEventName)
{
    wil::unique_event phaseEvent;
    if (phaseEvent.try_open(phaseEventName.c_str(), EVENT_MODIFY_STATE, false))
    {
        phaseEvent.SetEvent();
    }
}

bool NeedDynamicDependencies()
{
    return !Test::AppModel::IsPackagedProcess();
}

HRESULT BootstrapInitialize()
{
    if (!NeedDynamicDependencies())
    {
        return S_OK;
    }

    wil::unique_hmodule bootStrapDll(LoadLibraryEx(g_bootStrapDllName, NULL, 0));
    RETURN_LAST_ERROR_IF_NULL(bootStrapDll);

    BootStrapTestInit mddTestInitialize = reinterpret_cast<BootStrapTestInit>(GetProcAddress(bootStrapDll.get(), "MddBootstrapTestInitialize"));
    RETURN_LAST_ERROR_IF_NULL(mddTestInitialize);

    BootStrapInit mddInitialize = reinterpret_cast<BootStrapInit>(GetProcAddress(bootStrapDll.get(), "MddBootstrapInitialize"));
    RETURN_LAST_ERROR_IF_NULL(mddInitialize);

    constexpr PCWSTR c_PackageNamePrefix{ L"WindowsAppRuntime.Test.DDLM" };
    constexpr PCWSTR c_PackagePublisherId{ L"8wekyb3d8bbwe" };
    constexpr PCWSTR c_FrameworkPackageFamilyName = L"Microsoft.WindowsAppRuntime.Framework-4.1_8wekyb3d8bbwe";
    constexpr PCWSTR c_MainPackageFamilyName = L"WindowsAppRuntime.Test.DynDep.DataStore-4.1_8wekyb3d8bbwe";
    RETURN_IF_FAILED(mddTestInitialize(c_PackageNamePrefix, c_PackagePublisherId, c_FrameworkPackageFamilyName, c_MainPackageFamilyName));

    // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
    const UINT32 c_Version_MajorMinor{ 0x00040001 };
    const PACKAGE_VERSION minVersion{};
    RETURN_IF_FAILED(mddInitialize(c_Version_MajorMinor, nullptr, minVersion));

    return S_OK;
}

void BootstrapShutdown()
{
    if (!NeedDynamicDependencies())
    {
        return;
    }

    wil::unique_hmodule bootStrapDll(LoadLibraryEx(g_bootStrapDllName, NULL, 0));
    if (!bootStrapDll)
    {
        return;
    }

    BootStrapShutdown mddShutdown = reinterpret_cast<BootStrapShutdown>(GetProcAddress(bootStrapDll.get(), "MddBootstrapShutdown"));
    if (!mddShutdown)
    {
        return;
    }
    mddShutdown();
}
