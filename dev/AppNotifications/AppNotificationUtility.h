// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "pch.h"
#include <winrt/Windows.Foundation.h>
#include <wrl/implements.h>
#include <wil/resource.h>
#include <AppNotificationActivatedEventArgs.h>
#include <FrameworkUdk/toastnotificationsrt.h>
#include <ShellLocalization.h>

namespace Microsoft::Windows::AppNotifications::Helpers
{
    const PCWSTR c_appIdentifierPath{ LR"(Software\Classes\AppUserModelId\)" };
    const PCWSTR c_clsIdPath{ LR"(Software\Classes\CLSID\)" };
    const PCWSTR c_quote{ LR"(")" };
    const PCWSTR c_notificationActivatedArgument{ L" ----AppNotificationActivated:" };

    inline const int GUID_LENGTH = 39; // GUID + '{' + '}' + '/0'

    inline std::wstring ConvertPathToKey(std::wstring path)
    {
        for (size_t i = 0; i < path.length(); i++)
        {
            if (path[i] == '\\')
            {
                path[i] = '.';
            }
        }
        return path;
    }

    inline void RegisterValue(wil::unique_hkey const& hKey, PCWSTR const& key, const BYTE* value, DWORD const& valueType, size_t const& size)
    {
        THROW_IF_WIN32_ERROR(RegSetValueExW(hKey.get(), key, 0, valueType, value, static_cast<DWORD>(size)));
    }

    inline wil::unique_hstring safe_make_unique_hstring(PCWSTR str)
    {
        // wil::make_unique_string can't allocate a zero byte memory buffer.
        return (str == nullptr || wcslen(str) == 0) ? wil::unique_hstring() : wil::make_unique_string<wil::unique_hstring>(str);
    }

    std::wstring RetrieveUnpackagedNotificationAppId();

    std::wstring RetrieveNotificationAppId();

    void RegisterComServer(wil::unique_cotaskmem_string const& clsid);

    void UnRegisterComServer(std::wstring const& clsid);

    void UnRegisterNotificationAppIdentifierFromRegistry();

    HRESULT GetActivatorGuid(std::wstring& activatorGuid) noexcept;

    std::wstring GetOrCreateComActivatorGuid();

    void RegisterAssets(std::wstring const& appId, std::wstring const& clsid, Microsoft::Windows::AppNotifications::ShellLocalization::AppNotificationAssets const& assets);

    wil::unique_cotaskmem_string ConvertUtf8StringToWideString(unsigned long length, const BYTE* utf8String);

    winrt::Microsoft::Windows::AppNotifications::AppNotification ToastNotificationFromToastProperties(ABI::Microsoft::Internal::ToastNotifications::INotificationProperties* properties);

    std::wstring GetDisplayNameBasedOnProcessName();

    Microsoft::Windows::AppNotifications::ShellLocalization::AppNotificationAssets GetAssets();

    Microsoft::Windows::AppNotifications::ShellLocalization::AppNotificationAssets ValidateAssets(winrt::hstring const& displayName, std::filesystem::path const& iconFilePath);
}
