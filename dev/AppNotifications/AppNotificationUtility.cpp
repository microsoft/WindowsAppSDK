
// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <cwctype>

#include "AppNotificationUtility.h"
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/base.h>
#include <externs.h>
#include <frameworkudk/pushnotifications.h>
#include "AppNotification.h"
#include "NotificationProgressData.h"

#include <Microsoft.Foundation.String.h>
#include <ShObjIdl_core.h>
#include <shlobj_core.h>
#include <filesystem>

#include <ShellLocalization.h>

namespace std
{
    using namespace std::filesystem;
}

namespace winrt
{
    using namespace winrt::Windows::Foundation;
    using namespace Windows::ApplicationModel::Core;
    using namespace winrt::Microsoft::Windows::AppNotifications;
}

namespace ToastABI
{
    using namespace ::ABI::Microsoft::Internal::ToastNotifications;
}

using namespace Microsoft::Windows::AppNotifications::ShellLocalization;

std::wstring Microsoft::Windows::AppNotifications::Helpers::RetrieveUnpackagedNotificationAppId()
{
    wil::unique_cotaskmem_string appId;

    // If the developer has called into SetCurrentProcessExplicitAppUserModelID, we should honor that AppId rather than dynamically generate our own
    if (SUCCEEDED(GetCurrentProcessExplicitAppUserModelID(&appId)))
    {
        return appId.get();
    }
    else
    {
        // subKey: L"Software\\Classes\\AppUserModelId\\{Path to ToastNotificationsTestApp.exe}"
        std::wstring subKey{ c_appIdentifierPath + ConvertPathToKey(GetCurrentProcessPath()) };

        wil::unique_hkey hKey;
        THROW_IF_WIN32_ERROR(RegCreateKeyEx(
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
        auto status = RegGetValueW(
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
            RegisterValue(hKey, L"NotificationGUID", reinterpret_cast<const BYTE*>(newNotificationGuidString.get()), REG_SZ, wcslen(newNotificationGuidString.get()) * sizeof(wchar_t));
            return newNotificationGuidString.get();
        }
        else
        {
            THROW_IF_WIN32_ERROR(status);
            return registeredGuidBuffer;
        }
    }
}

std::wstring Microsoft::Windows::AppNotifications::Helpers::RetrieveNotificationAppId()
{
    if (AppModel::Identity::IsPackagedProcess())
    {
        wchar_t appUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH] = {};
        UINT32 appUserModelIdSize{ APPLICATION_USER_MODEL_ID_MAX_LENGTH };

        THROW_IF_FAILED(::GetCurrentApplicationUserModelId(&appUserModelIdSize, appUserModelId));
        return appUserModelId;
    }
    else
    {
        return RetrieveUnpackagedNotificationAppId();
    }
}

void Microsoft::Windows::AppNotifications::Helpers::RegisterComServer(wil::unique_cotaskmem_string const& clsid)
{
    wil::unique_hkey hKey;
    //subKey: Software\Classes\CLSID\{comActivatorGuidString}\LocalServer32
    std::wstring subKey{ c_clsIdPath };
    subKey.append(clsid.get());
    subKey.append(LR"(\LocalServer32)");

    THROW_IF_WIN32_ERROR(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        0,
        nullptr /* lpClass */,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        nullptr /* lpSecurityAttributes */,
        &hKey,
        nullptr /* lpdwDisposition */));

    std::wstring comRegistrationExeString{ c_quote + GetCurrentProcessPath() + c_quote + c_notificationActivatedArgument };

    RegisterValue(hKey, nullptr, reinterpret_cast<const BYTE*>(comRegistrationExeString.c_str()), REG_SZ, (comRegistrationExeString.size() * sizeof(wchar_t)));
}

void Microsoft::Windows::AppNotifications::Helpers::UnRegisterComServer(std::wstring const& clsid)
{
    wil::unique_hkey hKey;
    //clsidPath: Software\Classes\CLSID\{comActivatorGuidString}
    std::wstring clsidPath{ c_clsIdPath + clsid };

    //subKey: Software\Classes\CLSID\{comActivatorGuidString}\LocalServer32
    std::wstring subKey{ clsidPath + LR"(\LocalServer32)" };

    THROW_IF_WIN32_ERROR(RegDeleteKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        KEY_ALL_ACCESS,
        0));

    THROW_IF_WIN32_ERROR(RegDeleteKeyEx(
        HKEY_CURRENT_USER,
        clsidPath.c_str(),
        KEY_ALL_ACCESS,
        0));
}

void Microsoft::Windows::AppNotifications::Helpers::UnRegisterNotificationAppIdentifierFromRegistry()
{
    wil::unique_cotaskmem_string appId;

    std::wstring notificationAppId{ RetrieveNotificationAppId() };

    wil::unique_hkey hKey;
    //subKey: \Software\Classes\AppUserModelId\{AppGUID}
    std::wstring subKey{ c_appIdentifierPath + notificationAppId };

    THROW_IF_WIN32_ERROR(RegDeleteKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        KEY_ALL_ACCESS,
        0));
}

HRESULT Microsoft::Windows::AppNotifications::Helpers::GetActivatorGuid(std::wstring& activatorGuid) noexcept try
{
    std::wstring notificationAppId{ RetrieveNotificationAppId() };
    // subKey: \Software\Classes\AppUserModelId\{AppGUID}
    std::wstring subKey{ c_appIdentifierPath + notificationAppId };

    wil::unique_hkey hKey;
    THROW_IF_WIN32_ERROR(RegCreateKeyEx(
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
    THROW_IF_WIN32_ERROR(RegGetValueW(
        hKey.get(),
        nullptr /* lpValue */,
        L"CustomActivator",
        RRF_RT_REG_SZ,
        nullptr /* pdwType */,
        &activatorGuidBuffer,
        &bufferLength));

    activatorGuid = activatorGuidBuffer;

    // We want to verify the integrity of this COM registration in path: Software\Classes\CLSID\{comActivatorGuidString}\LocalServer32
    // This would indicate data corruption in which case we create a new activator entry later on.
    subKey = c_clsIdPath + activatorGuid + LR"(\LocalServer32)";
    auto status = RegOpenKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        0,
        KEY_READ,
        &hKey);

    // If there is an activator GUID mismatch in the 2 paths, we should return ERROR_FILE_NOT_FOUND so that we can recreate the ActivatorGuid in the upper layers
    if (FAILED_WIN32(status))
    {
        return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    }
    else
    {
        return S_OK;
    }
}
CATCH_RETURN()

std::wstring Microsoft::Windows::AppNotifications::Helpers::GetDisplayNameBasedOnProcessName()
{
    std::wstring displayName{};
    THROW_IF_FAILED(wil::GetModuleFileNameExW(GetCurrentProcess(), nullptr, displayName));

    size_t lastBackslashPosition{ displayName.rfind(L"\\") };
    THROW_HR_IF(E_UNEXPECTED, lastBackslashPosition == std::wstring::npos);
    displayName = displayName.substr(lastBackslashPosition + 1); // One after the delimiter

    displayName.erase(displayName.find_first_of(L".")); // Remove file extension

    displayName[0] = std::towupper(displayName[0]);

    return displayName;
}

std::wstring Microsoft::Windows::AppNotifications::Helpers::GetOrCreateComActivatorGuid()
{
    std::wstring registeredGuid;
    auto hr = GetActivatorGuid(registeredGuid);

    if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
    {
        // Create a GUID for the COM Activator
        GUID comActivatorGuid = GUID_NULL;
        THROW_IF_FAILED(CoCreateGuid(&comActivatorGuid));

        // StringFromCLSID returns GUID String with braces
        wil::unique_cotaskmem_string comActivatorGuidString;
        THROW_IF_FAILED(StringFromCLSID(comActivatorGuid, &comActivatorGuidString));
        RegisterComServer(comActivatorGuidString);

        registeredGuid = comActivatorGuidString.get();
    }
    else
    {
        THROW_IF_FAILED(hr);
    }

    return registeredGuid;
}

// Try the following techniques to retrieve display name and icon:
// 1. Based on the best app shortcut, using the FrameworkUdk.
// 2. From the current process.
// 3. Set a default DisplayName, but leave empty the icon file path so Shell can set a default icon.
AppNotificationAssets Microsoft::Windows::AppNotifications::Helpers::GetAssets()
{
    AppNotificationAssets assets{};

    if (FAILED(RetrieveAssetsFromShortcut(assets)) &&
        FAILED(RetrieveAssetsFromProcess(assets)))
    {
        assets.displayName = GetDisplayNameBasedOnProcessName();
    }

    return assets;
}

AppNotificationAssets Microsoft::Windows::AppNotifications::Helpers::ValidateAssets(winrt::hstring const& displayName, std::filesystem::path const& iconFilePath)
{
    winrt::check_bool(std::filesystem::exists(iconFilePath));

    THROW_HR_IF_MSG(E_INVALIDARG, !IsIconFileExtensionSupported(iconFilePath), "Icon format not supported");

    return AppNotificationAssets{ displayName.c_str(), iconFilePath.wstring() };
}

void Microsoft::Windows::AppNotifications::Helpers::RegisterAssets(std::wstring const& appId, std::wstring const& clsid, AppNotificationAssets const& assets)
{
    wil::unique_hkey hKey;
    // subKey: \Software\Classes\AppUserModelId\{AppGUID}
    std::wstring subKey{ c_appIdentifierPath + appId };

    THROW_IF_WIN32_ERROR(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        subKey.c_str(),
        0,
        nullptr /* lpClass */,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        nullptr /* lpSecurityAttributes */,
        &hKey,
        nullptr /* lpdwDisposition */));

    RegisterValue(hKey, L"DisplayName", reinterpret_cast<const BYTE*>(assets.displayName.c_str()), REG_EXPAND_SZ, assets.displayName.size() * sizeof(wchar_t));

    // If no icon is specified in the Registry, the OS will render a default icon for App Notifications.
    if (!assets.iconFilePath.empty())
    {
        RegisterValue(hKey, L"IconUri", reinterpret_cast<const BYTE*>(assets.iconFilePath.c_str()), REG_EXPAND_SZ, assets.iconFilePath.size() * sizeof(wchar_t));
    }
    else // clean any Icon URI from previous registrations
    {
        LOG_IF_WIN32_ERROR(RegDeleteValue(hKey.get(), L"IconUri")); // Do not throw, since this is a best effort action.
    }

    RegisterValue(hKey, L"CustomActivator", reinterpret_cast<const BYTE*>(clsid.c_str()), REG_SZ, wil::guid_string_length * sizeof(wchar_t));
}

wil::unique_cotaskmem_string Microsoft::Windows::AppNotifications::Helpers::ConvertUtf8StringToWideString(unsigned long length, const byte* utf8String)
{
    int size{ MultiByteToWideChar(
        CP_UTF8,
        0,
        reinterpret_cast<PCSTR>(utf8String),
        length,
        nullptr,
        0) };
    THROW_LAST_ERROR_IF(size == 0);

    wil::unique_cotaskmem_string wideString{ wil::make_unique_string<wil::unique_cotaskmem_string>(nullptr, size) };

    size = MultiByteToWideChar(
        CP_UTF8,
        0,
        reinterpret_cast<PCSTR>(utf8String),
        length,
        wideString.get(),
        size);
    THROW_LAST_ERROR_IF(size == 0);

    return wideString;
}

winrt::Microsoft::Windows::AppNotifications::AppNotification Microsoft::Windows::AppNotifications::Helpers::ToastNotificationFromToastProperties(ABI::Microsoft::Internal::ToastNotifications::INotificationProperties* properties)
{
    unsigned int payloadSize{};
    wil::unique_cotaskmem_array_ptr<byte> payload{};
    THROW_IF_FAILED(properties->get_Payload(&payloadSize, &payload));

    auto wide{ ConvertUtf8StringToWideString(payloadSize, payload.get()) };
    winrt::hstring xmlPayload{ wide.get() };

    winrt::Microsoft::Windows::AppNotifications::AppNotification notification(xmlPayload);

    wil::unique_hstring tag{};
    THROW_IF_FAILED(properties->get_Tag(&tag));
    notification.Tag(wil::str_raw_ptr(tag));

    wil::unique_hstring group{};
    THROW_IF_FAILED(properties->get_Group(&group));
    notification.Group(wil::str_raw_ptr(group));

    unsigned int notificationId{};
    THROW_IF_FAILED(properties->get_NotificationId(&notificationId));
    winrt::Microsoft::Windows::AppNotifications::implementation::AppNotification* notificationImpl{ winrt::get_self< winrt::Microsoft::Windows::AppNotifications::implementation::AppNotification>(notification) };
    notificationImpl->SetNotificationId(notificationId);

    winrt::com_ptr<ToastABI::IToastProgressData> toastProgressData;
    THROW_IF_FAILED(properties->get_ToastProgressData(toastProgressData.put()));
    if (toastProgressData)
    {
        // Sequence number is a transient property and we give it a default non-zero value of 1 in the ctor
        winrt::AppNotificationProgressData progressData{ 1 };

        wil::unique_hstring status{};
        THROW_IF_FAILED(toastProgressData->get_Status(&status));
        progressData.Status(wil::str_raw_ptr(status));

        wil::unique_hstring title{};
        THROW_IF_FAILED(toastProgressData->get_Title(&title));
        progressData.Title(wil::str_raw_ptr(title));

        double progressValue{};
        THROW_IF_FAILED(toastProgressData->get_Value(&progressValue));
        progressData.Value(progressValue);

        wil::unique_hstring progressValueString{};
        THROW_IF_FAILED(toastProgressData->get_ValueStringOverride(&progressValueString));
        progressData.ValueStringOverride(wil::str_raw_ptr(progressValueString));

        notification.Progress(progressData);
    }

    unsigned long long expiry{};
    THROW_IF_FAILED(properties->get_Expiry(&expiry));
    FILETIME expiryFileTime{};
    expiryFileTime.dwHighDateTime = expiry >> 32;
    expiryFileTime.dwLowDateTime = static_cast<DWORD>(expiry);
    notification.Expiration(winrt::clock::from_file_time(expiryFileTime));

    boolean expiresOnReboot{};
    THROW_IF_FAILED(properties->get_ExpiresOnReboot(&expiresOnReboot));
    notification.ExpiresOnReboot(expiresOnReboot);

    // Priority and SupressDisplay are transient values that do not exist in ToastProperties and thus, are left to their default.

    return notification;
}
