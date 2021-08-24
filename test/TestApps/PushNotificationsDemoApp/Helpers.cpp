// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include "Helpers.h"
#include <TestDef.h>

const wchar_t* g_bootStrapDllName = L"Microsoft.WindowsAppSDK.Bootstrap.dll";

typedef HRESULT (*BootStrapTestInit)(PCWSTR prefix, PCWSTR publisherId);
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

inline bool IsPackagedProcess()
{
    UINT32 n{};
    const auto rc{ ::GetCurrentPackageFullName(&n, nullptr) };
    THROW_HR_IF_MSG(HRESULT_FROM_WIN32(rc), (rc != APPMODEL_ERROR_NO_PACKAGE) && (rc != ERROR_INSUFFICIENT_BUFFER), "GetCurrentPackageFullName rc=%d", rc);
    return rc == ERROR_INSUFFICIENT_BUFFER;
}

bool NeedDynamicDependencies()
{
    return !IsPackagedProcess();
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

    constexpr PCWSTR c_PackageNamePrefix{ L"WindowsAppSDK.Test.DDLM" };
    constexpr PCWSTR c_PackagePublisherId{ L"8wekyb3d8bbwe" };
    RETURN_IF_FAILED(mddTestInitialize(c_PackageNamePrefix, c_PackagePublisherId));

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
