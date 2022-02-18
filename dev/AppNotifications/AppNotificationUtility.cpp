
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "AppNotificationUtility.h"
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/base.h>
#include <externs.h>
#include <frameworkudk/pushnotifications.h>
#include "AppNotification.h"
#include "NotificationProgressData.h"

#include <wil/resource.h>
#include <wil/win32_helpers.h>
#include <propkey.h> // PKEY properties
#include <propsys.h> // IPropertyStore
#include <ShObjIdl_core.h>

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
    wil::unique_cotaskmem_string appId;

    if (SUCCEEDED(GetCurrentProcessExplicitAppUserModelID(&appId)))
    {
        return;
    }
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

void Microsoft::Windows::AppNotifications::Helpers::RegisterAssets(std::wstring const& appId, std::wstring const& clsid)
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

    // Retrieve DisplayName and IconUri
    // - DisplayName: Retrieve from Shell. If not specified, fall back to filename.
    // - Icon: Retrieve from Shell. If it's not the case or the file extension is unsupported, then throw.
    winrt::com_ptr<IPropertyStore> propertyStore;
    wil::unique_hwnd hWindow{ GetConsoleWindow() };
    THROW_IF_FAILED(SHGetPropertyStoreForWindow(hWindow.get(), IID_PPV_ARGS(propertyStore.put())));

    // Retrieve the display name
    std::wstring displayName{};

    wil::unique_prop_variant propVariantDisplayName;
    // Do not throw in case of failure. We can use the filepath approach below as fallback to set a DisplayName.
    LOG_IF_FAILED(propertyStore->GetValue(PKEY_AppUserModel_RelaunchDisplayNameResource, &propVariantDisplayName));

    displayName = propVariantDisplayName.vt != VT_EMPTY ? propVariantDisplayName.pwszVal : L"";

    if (displayName.length() == 0)
    {
        wil::unique_cotaskmem_string processName;
        THROW_IF_FAILED(GetCurrentProcessPath(processName));

        displayName = processName.get();

        size_t lastBackslashPosition{ displayName.rfind(L"\\") };
        THROW_HR_IF(E_UNEXPECTED, lastBackslashPosition == std::wstring::npos);
        displayName = displayName.substr(lastBackslashPosition + 1); // One after the delimiter

        displayName.erase(displayName.find_first_of(L".")); // Remove file extension
    }

    // Retrieve the icon
    std::wstring iconFilePath{};

    wil::unique_prop_variant propVariantIcon;
    // Throw in case of failure, since Icon is mandatory and we don't have a fallback!
    THROW_IF_FAILED(propertyStore->GetValue(PKEY_AppUserModel_RelaunchIconResource, &propVariantIcon));
    THROW_HR_IF_MSG(E_UNEXPECTED, propVariantIcon.vt == VT_EMPTY, "You must specify an app icon before calling Register().");

    iconFilePath = propVariantIcon.pwszVal;

    // Icon filepaths from Shell APIs have this format: <filepath>,-<index>,
    // since .ico files can have multiple icons in the same file.
    // NotificationController doesn't seem to support such format, so let it take the first icon by default.
    auto iteratorForCommaDelimiter = iconFilePath.find_first_of(L",");
    if (iteratorForCommaDelimiter != std::wstring::npos) // It may or may not have an index, which is fine.
    {
        iconFilePath.erase(iteratorForCommaDelimiter);
    }

    auto iteratorForFileExtension = iconFilePath.find_first_of(L".");
    THROW_HR_IF_MSG(E_UNEXPECTED, iteratorForFileExtension == std::wstring::npos, "You must provide a valid filepath as the app icon.");

    std::wstring iconFileExtension = iconFilePath.substr(iteratorForFileExtension);
    THROW_HR_IF_MSG(E_UNEXPECTED, iconFileExtension != L".ico" && iconFileExtension != L".png",
        "You must provide a supported file extension as the icon (.ico or .png).");

    RegisterValue(hKey, L"DisplayName", reinterpret_cast<const BYTE*>(displayName.c_str()), REG_EXPAND_SZ, displayName.size() * sizeof(wchar_t));
    RegisterValue(hKey, L"IconUri", reinterpret_cast<const BYTE*>(iconFilePath.c_str()), REG_EXPAND_SZ, iconFilePath.size() * sizeof(wchar_t));
    RegisterValue(hKey, L"CustomActivator", reinterpret_cast<const BYTE*>(clsid.c_str()), REG_SZ, clsid.size() * sizeof(wchar_t));
}

std::wstring Microsoft::Windows::AppNotifications::Helpers::RegisterComActivatorGuidAndAssets()
{
    std::wstring registeredGuid;
    HRESULT status = GetActivatorGuid(registeredGuid);

    THROW_HR_IF(status, FAILED(status) && status != HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));

    if (status == ERROR_FILE_NOT_FOUND)
    {
        // Get process name to identify the app 
        wil::unique_cotaskmem_string processName;
        THROW_IF_FAILED(GetCurrentProcessPath(processName));

        // Create a GUID for the COM Activator
        GUID comActivatorGuid = GUID_NULL;
        THROW_IF_FAILED(CoCreateGuid(&comActivatorGuid));

        // StringFromCLSID returns GUID String with braces
        wil::unique_cotaskmem_string comActivatorGuidString;
        THROW_IF_FAILED(StringFromCLSID(comActivatorGuid, &comActivatorGuidString));
        RegisterComServer(processName, comActivatorGuidString);

        registeredGuid = comActivatorGuidString.get();
    }

    std::wstring notificationAppId{ RetrieveNotificationAppId() };
    RegisterAssets(notificationAppId, registeredGuid);

    return registeredGuid;
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
        winrt::AppNotificationProgressData progressData{};

        // SequenceNumber is transient and thus,  left to its default.

        wil::unique_hstring status{};
        THROW_IF_FAILED(toastProgressData->get_Status(&status));
        progressData.Status(wil::str_raw_ptr(status));

        wil::unique_hstring title{};
        THROW_IF_FAILED(toastProgressData->get_Title(&title));
        progressData.Title(wil::str_raw_ptr(title));

        double progressValue{};
        toastProgressData->get_Value(&progressValue);
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
    auto expiryClock{ winrt::clock::from_file_time(expiryFileTime) };
    notification.Expiration(expiryClock);

    boolean expiresOnReboot{};
    THROW_IF_FAILED(properties->get_ExpiresOnReboot(&expiresOnReboot));
    notification.ExpiresOnReboot(expiresOnReboot);

    // Priority and SupressDisplay are transient values that do not exist in ToastProperties and thus, are left to their default.

    return notification;
}
