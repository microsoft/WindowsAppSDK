// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <ToastNotificationsWinRT.h>
#include <Microsoft.ToastNotificationsWinRt.DesktopToastNotificationManagerCompat.g.cpp>
#include <Microsoft.ToastNotificationsWinRt.ToastActivatedEventArgs.g.cpp>
#include "NotificationActivationCallback.h"
#include <wrl.h>
#include <wrl\wrappers\corewrappers.h>

using namespace std;
using namespace Microsoft::WRL;

wstring s_appId;
bool s_registeredAumidAndComServer = false;
LONG g_Count = 0;
Microsoft::WRL::EventSource<winrt::Microsoft::ToastNotificationsWinRt::implementation::ToastActivatedEventArgs> s_event;
wil::unique_handle s_toastActivatedHandle;
static winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Microsoft::ToastNotificationsWinRt::ToastActivatedEventArgs>> s_activatedEvent;

#define TOAST_ACTIVATED_LAUNCH_ARG L"-ToastActivated"

struct callback : winrt::implements<callback, INotificationActivationCallback>
{
    HRESULT __stdcall Activate(
        LPCWSTR app,
        LPCWSTR args,
        [[maybe_unused]] NOTIFICATION_USER_INPUT_DATA const* data,
        [[maybe_unused]] ULONG count) noexcept final
    {
        printf("This app has been called back from a notification.");

        auto userInput{ winrt::single_threaded_map<winrt::hstring, winrt::hstring>() };
        for (ULONG i = 0; i < count; ++i)
        {
            winrt::hstring key = data[i].Key;
            winrt::hstring value = data[i].Value;
            userInput.Insert(key, value);
        }
        winrt::Microsoft::ToastNotificationsWinRt::implementation::DesktopToastNotificationManagerCompat::ActivatorCompleted(app, args, userInput);

        // Signal the api that we are done process the toast activator
        SetEvent(s_toastActivatedHandle.get());
        return S_OK;
    }
};

struct callback_factory : winrt::implements<callback_factory, IClassFactory>
{
    HRESULT __stdcall CreateInstance(
        IUnknown* outer,
        GUID const& iid,
        void** result) noexcept final
    {
        *result = nullptr;

        if (outer)
        {
            return CLASS_E_NOAGGREGATION;
        }

        return winrt::make<callback>()->QueryInterface(iid, result);
    }

    HRESULT __stdcall LockServer(BOOL) noexcept final
    {
        return S_OK;
    }
};

namespace winrt::Microsoft::ToastNotificationsWinRt::implementation
{
    ToastActivatedEventArgs::ToastActivatedEventArgs(hstring const& appId, hstring const& arguments, Windows::Foundation::Collections::IMap<hstring, hstring> const& userInput)
    {
        m_appId = appId;
        m_arguments = arguments;
        m_userInput = userInput;
    }

    hstring ToastActivatedEventArgs::Arguments()
    {
        return m_arguments;
    }

    hstring ToastActivatedEventArgs::AppId()
    {
        return m_appId;
    }

    Windows::Foundation::Collections::IMap<hstring, hstring> ToastActivatedEventArgs::UserInput()
    {
        return m_userInput;
    }

    HRESULT RegisterComServer(GUID clsid, PCWSTR exePath)
    {
        wil::unique_cotaskmem_string guidStr;
        RETURN_IF_FAILED(StringFromCLSID(clsid, &guidStr));

        wstring clsidStr = guidStr.get();
        wstring subKey = LR"(SOFTWARE\Classes\CLSID\)" + clsidStr + LR"(\LocalServer32)";

        // Include -ToastActivated launch args on the exe
        std::wstring exePathStr(exePath);
        exePathStr = L"\"" + exePathStr + L"\" " + TOAST_ACTIVATED_LAUNCH_ARG;

        // We don't need to worry about overflow here as ::GetModuleFileName won't
       // return anything bigger than the max file system path (much fewer than max of DWORD).
        DWORD dataSize = static_cast<DWORD>((exePathStr.length() + 1) * sizeof(WCHAR));

        RETURN_IF_FAILED(HRESULT_FROM_WIN32(::RegSetKeyValue(
            HKEY_CURRENT_USER,
            subKey.c_str(),
            nullptr,
            REG_SZ,
            reinterpret_cast<const BYTE*>(exePathStr.c_str()),
            dataSize)));
        return S_OK;
    }


    HRESULT RegisterActivator(GUID clsid)
    {
        wchar_t exePath[MAX_PATH];
        DWORD charWritten = ::GetModuleFileName(nullptr, exePath, ARRAYSIZE(exePath));
        RETURN_IF_FAILED(charWritten > 0 ? S_OK : HRESULT_FROM_WIN32(::GetLastError()));

        // Register the COM server
        RETURN_IF_FAILED(RegisterComServer(clsid, exePath));

        // Update the CustomActivator
        std::wstring regKey = LR"(SOFTWARE\Classes\AppUserModelId\)" + s_appId;

        wil::unique_cotaskmem_string guidStr;
        RETURN_IF_FAILED(StringFromCLSID(clsid, &guidStr));
        wstring clsidStr = guidStr.get();

        // Register the activator
        RETURN_IF_FAILED(HRESULT_FROM_WIN32(::RegSetKeyValue(
            HKEY_CURRENT_USER,
            regKey.c_str(),
            L"CustomActivator",
            REG_SZ,
            reinterpret_cast<const BYTE*>(clsidStr.c_str()),
            static_cast<DWORD>((clsidStr.size() + 1) * sizeof(WCHAR)))));

        DWORD cookie;
        winrt::check_hresult(::CoRegisterClassObject(
            clsid,
            make<callback_factory>().get(),
            CLSCTX_LOCAL_SERVER,
            REGCLS_SINGLEUSE,
            &cookie));
        return S_OK;
    }

    void DesktopToastNotificationManagerCompat::RegisterApplication(hstring const& clsid, hstring const& appId, hstring const& displayName, hstring const& iconPath)
    {
        if (!s_registeredAumidAndComServer)
        {
            s_toastActivatedHandle = wil::unique_handle(CreateEvent(nullptr, FALSE, FALSE, nullptr));
            THROW_LAST_ERROR_IF(!s_toastActivatedHandle);
            s_appId = appId.c_str();
            wstring regKey = LR"(SOFTWARE\Classes\AppUserModelId\)" + s_appId;

            // Set display name
            THROW_IF_FAILED(HRESULT_FROM_WIN32(::RegSetKeyValueW(
                HKEY_CURRENT_USER,
                regKey.c_str(),
                L"DisplayName",
                REG_SZ,
                reinterpret_cast<const BYTE*>(displayName.c_str()),
                static_cast<DWORD>((wcslen(displayName.c_str()) + 1) * sizeof(WCHAR)))));

            // Set icon if specified
            if (!iconPath.empty())
            {
                THROW_IF_FAILED(HRESULT_FROM_WIN32(::RegSetKeyValue(
                    HKEY_CURRENT_USER,
                    regKey.c_str(),
                    L"IconUri",
                    REG_SZ,
                    reinterpret_cast<const BYTE*>(iconPath.c_str()),
                    static_cast<DWORD>((wcslen(iconPath.c_str()) + 1) * sizeof(WCHAR)))));
            }

            // Set icon background color. Only appears in the settings page, always setting to light gray since app icon is known to work well on light gray anyways since that's how it appears in Action Center
            THROW_IF_FAILED(HRESULT_FROM_WIN32(::RegSetKeyValue(
                HKEY_CURRENT_USER,
                regKey.c_str(),
                L"IconBackgroundColor",
                REG_SZ,
                reinterpret_cast<const BYTE*>(L"FFDDDDDD"),
                static_cast<DWORD>((wcslen(L"FFDDDDDD") + 1) * sizeof(WCHAR)))));

            GUID clsidGuid;
            THROW_IF_FAILED(CLSIDFromString(clsid.c_str(), &clsidGuid));
            THROW_IF_FAILED(RegisterActivator(clsidGuid));
            s_registeredAumidAndComServer = true;
        }
    }

    void DesktopToastNotificationManagerCompat::ActivatorCompleted(_In_ PCWSTR appId, _In_ PCWSTR args, _In_ Windows::Foundation::Collections::IMap<hstring, hstring> const& userInput)
    {
        hstring appIdString = appId;
        hstring argsString = args;

        auto toastArgs = winrt::make_self<ToastActivatedEventArgs>(appId, args, userInput);
        s_activatedEvent(nullptr, *toastArgs);
    }

    bool DesktopToastNotificationManagerCompat::WasProcessToastActivated()
    {
        wstring commandLineArgs = GetCommandLine();
        auto found = commandLineArgs.find(TOAST_ACTIVATED_LAUNCH_ARG, 0);

        // If this is a toast activation, wait for the activation request to complete before exiting the process
        if (found)
        {
            WaitForSingleObject(s_toastActivatedHandle.get(), 2000);
        }

        return found != std::wstring::npos;
    }

    winrt::event_token DesktopToastNotificationManagerCompat::ToastActivated(Windows::Foundation::EventHandler<Microsoft::ToastNotificationsWinRt::ToastActivatedEventArgs> const& handler)
    {
        return s_activatedEvent.add(handler);
    }

    void DesktopToastNotificationManagerCompat::ToastActivated(winrt::event_token const& token) noexcept
    {
        s_activatedEvent.remove(token);
    }
}
