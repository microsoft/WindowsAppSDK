
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "AppNotificationUtility.h"
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Foundation.h>
#include <externs.h>
#include <frameworkudk/pushnotifications.h>

namespace winrt
{
    using namespace winrt::Windows::Foundation;
    using namespace Windows::ApplicationModel::Core;
}

std::wstring Microsoft::Windows::AppNotifications::Helpers::RetrieveUnpackagedNotificationAppId()
{
    wil::unique_cotaskmem_string processName;
    THROW_IF_FAILED(GetCurrentProcessPath(processName));

    std::wstring wideStringProcessName{ processName.get() };
    // subKey: L"Software\\Classes\\AppUserModelId\\{Path to ToastNotificationsTestApp.exe}"
    std::wstring subKey{ c_appIdentifierPath + ConvertPathToKey(wideStringProcessName) };

    wil::unique_hkey hKey;
    THROW_IF_FAILED(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        0,
        nullptr /* lpClass */,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        nullptr /* lpSecurityAttributes */,
        &hKey,
        nullptr /* lpdwDisposition */));

    WCHAR registeredGuidBuffer[GUID_LENGTH];
    DWORD bufferLength = sizeof(registeredGuidBuffer);
    HRESULT status = RegGetValueW(
        hKey.get(),
        nullptr /* lpValue */,
        L"NotificationGUID",
        RRF_RT_REG_SZ,
        nullptr /* pdwType */,
        &registeredGuidBuffer,
        &bufferLength);

    if (status == ERROR_FILE_NOT_FOUND)
    {
        GUID newNotificationGuid;
        THROW_IF_FAILED(CoCreateGuid(&newNotificationGuid));

        wil::unique_cotaskmem_string newNotificationGuidString;
        THROW_IF_FAILED(StringFromCLSID(newNotificationGuid, &newNotificationGuidString));

        std::wstring guidWideStr{ newNotificationGuidString.get() };
        RegisterValue(hKey, L"NotificationGUID", reinterpret_cast<const BYTE*>(guidWideStr.c_str()), REG_SZ, guidWideStr.size() * sizeof(wchar_t));
        return guidWideStr;
    }

    THROW_HR_IF(status, FAILED_WIN32(status));
    return registeredGuidBuffer;
}

std::wstring Microsoft::Windows::AppNotifications::Helpers::RetrieveNotificationAppId()
{
    if (AppModel::Identity::IsPackagedProcess())
    {
        wchar_t appUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
        UINT32 appUserModelIdSize{ APPLICATION_USER_MODEL_ID_MAX_LENGTH };

        THROW_IF_FAILED(GetCurrentApplicationUserModelId(&appUserModelIdSize, appUserModelId));
        return appUserModelId;
    }

    return RetrieveUnpackagedNotificationAppId();
}

void Microsoft::Windows::AppNotifications::Helpers::RegisterComServer(wil::unique_cotaskmem_string const& processName, wil::unique_cotaskmem_string const& clsid)
{
    wil::unique_hkey hKey;
    //subKey: Software\Classes\CLSID\{comActivatorGuidString}\LocalServer32
    std::wstring subKey{ c_clsIdPath + clsid.get() + LR"(\LocalServer32)" };

    THROW_IF_FAILED(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        0,
        nullptr /* lpClass */,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        nullptr /* lpSecurityAttributes */,
        &hKey,
        nullptr /* lpdwDisposition */));

    std::wstring comRegistrationExeString{ c_quote + processName.get() + c_quote + c_notificationActivatedArgument };

    RegisterValue(hKey, nullptr, reinterpret_cast<const BYTE*>(comRegistrationExeString.c_str()), REG_SZ, (comRegistrationExeString.size() * sizeof(wchar_t)));
}

void Microsoft::Windows::AppNotifications::Helpers::UnRegisterComServer(std::wstring const& clsid)
{
    wil::unique_hkey hKey;
    //subKey: Software\Classes\CLSID\{comActivatorGuidString}\LocalServer32
    std::wstring subKey{ c_clsIdPath + clsid + LR"(\LocalServer32)" };

    THROW_IF_FAILED(RegDeleteKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        KEY_WOW64_64KEY,
        0));
}

void Microsoft::Windows::AppNotifications::Helpers::UnRegisterNotificationAppIdentifierFromRegistry()
{
    std::wstring notificationAppId{ RetrieveNotificationAppId() };

    wil::unique_hkey hKey;
    //subKey: \Software\Classes\AppUserModelId\{AppGUID}
    std::wstring subKey{ c_appIdentifierPath + notificationAppId };

    THROW_IF_FAILED(RegDeleteKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        KEY_WOW64_64KEY,
        0));
}

HRESULT Microsoft::Windows::AppNotifications::Helpers::GetActivatorGuid(std::wstring& activatorGuid) noexcept try
{
    std::wstring notificationAppId{ RetrieveNotificationAppId() };
    // subKey: \Software\Classes\AppUserModelId\{AppGUID}
    std::wstring subKey{ c_appIdentifierPath + notificationAppId };

    wil::unique_hkey hKey;
    THROW_IF_FAILED(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        0,
        nullptr /* lpClass */,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        nullptr /* lpSecurityAttributes */,
        &hKey,
        nullptr /* lpdwDisposition */));

    WCHAR activatorGuidBuffer[GUID_LENGTH];
    DWORD bufferLength = sizeof(activatorGuidBuffer);
    HRESULT status = RegGetValueW(
        hKey.get(),
        nullptr /* lpValue */,
        L"CustomActivator",
        RRF_RT_REG_SZ,
        nullptr /* pdwType */,
        &activatorGuidBuffer,
        &bufferLength);

    activatorGuid = activatorGuidBuffer;
    return status;
}
CATCH_RETURN()

void Microsoft::Windows::AppNotifications::Helpers::RegisterAssets(std::wstring const& appId, winrt::hstring const& displayName, winrt::Windows::Foundation::Uri const& iconUri, wil::unique_cotaskmem_string const& clsid)
{
    wil::unique_hkey hKey;
    // subKey: \Software\Classes\AppUserModelId\{AppGUID}
    std::wstring subKey{ c_appIdentifierPath + appId };

    THROW_IF_FAILED(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        0,
        nullptr /* lpClass */,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        nullptr /* lpSecurityAttributes */,
        &hKey,
        nullptr /* lpdwDisposition */));

    RegisterValue(hKey, L"DisplayName", reinterpret_cast<const BYTE*>(displayName.c_str()), REG_EXPAND_SZ, displayName.size() * sizeof(wchar_t));
    RegisterValue(hKey, L"IconUri", reinterpret_cast<const BYTE*>(iconUri.AbsoluteUri().c_str()), REG_EXPAND_SZ, iconUri.AbsoluteUri().size() * sizeof(wchar_t));

    std::wstring wideStringClsid{ clsid.get() };
    RegisterValue(hKey, L"CustomActivator", reinterpret_cast<const BYTE*>(wideStringClsid.c_str()), REG_SZ, wideStringClsid.size() * sizeof(wchar_t));
}

std::wstring Microsoft::Windows::AppNotifications::Helpers::RegisterComActivatorGuidAndAssets(winrt::Microsoft::Windows::AppNotifications::AppNotificationActivationInfo const& details)
{
    std::wstring registeredGuid;
    HRESULT status = GetActivatorGuid(registeredGuid);
    if (status == ERROR_FILE_NOT_FOUND)
    {
        wil::unique_cotaskmem_string processName;
        THROW_IF_FAILED(GetCurrentProcessPath(processName));

        GUID comActivatorGuid = GUID_NULL;
        THROW_IF_FAILED(CoCreateGuid(&comActivatorGuid));

        // StringFromCLSID returns GUID String with braces.
        wil::unique_cotaskmem_string comActivatorGuidString;
        THROW_IF_FAILED(StringFromCLSID(comActivatorGuid, &comActivatorGuidString));

        std::wstring notificationAppId{ RetrieveNotificationAppId() };
        RegisterAssets(notificationAppId, details.DisplayName(), details.IconUri(), comActivatorGuidString);
        RegisterComServer(processName, comActivatorGuidString);

        return comActivatorGuidString.get();
    }

    THROW_IF_WIN32_ERROR(status);
    return registeredGuid;
}
