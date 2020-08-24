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

#define TOAST_ACTIVATED_LAUNCH_ARG L"-ToastActivated"

class NotificationActivator WrlSealed :
    public RuntimeClass<RuntimeClassFlags<ClassicCom>, INotificationActivationCallback>
{
    HRESULT STDMETHODCALLTYPE Activate(
        _In_ LPCWSTR appUserModelId,
        _In_ LPCWSTR invokedArgs,
        _In_reads_(dataCount) const NOTIFICATION_USER_INPUT_DATA * data,
        ULONG dataCount) override
    {
        printf("Toast Activator!\n");
        winrt::hstring appId;
        appId = appUserModelId;
        winrt::hstring args;
        args = invokedArgs;
        winrt::Microsoft::ToastNotificationsWinRt::ToastActivatedEventArgs activatedEventArgs(appId, args);
        return S_OK;
    }
};

class NotificationActivatorFactory : public IClassFactory
{
public:
    NotificationActivatorFactory()
        : m_Ref(1)
    {
        ::InterlockedIncrement(&g_Count);
    }

    //
    // IUnknown Implementation
    //
    IFACEMETHODIMP_(ULONG) NotificationActivatorFactory::AddRef()
    {
        return InterlockedIncrement(&m_Ref);
    }

    IFACEMETHODIMP_(ULONG) NotificationActivatorFactory::Release()
    {
        ULONG Ref = InterlockedDecrement(&m_Ref);
        if (Ref <= 0)
        {
            delete this;
        }
        return Ref;
    }

    IFACEMETHODIMP NotificationActivatorFactory::QueryInterface(_In_ REFIID riid, _COM_Outptr_ PVOID* ppv)
    {
        HRESULT hr = S_OK;
        if (ppv == NULL)
        {
            hr = E_INVALIDARG;
            goto Exit;
        }
        if (IsEqualIID(riid, __uuidof(IClassFactory)) || IsEqualIID(riid, IID_IUnknown))
        {
            *ppv = static_cast<IClassFactory*> (this);
        }
        #define IUNKNOWN_QI(IClassFactory)
        else if (IsEqualIID(riid, __uuidof(IClassFactory)))
        {
            *ppv = static_cast<IClassFactory*> (this);
        }
        #define IUNKNOWN_QI_END()
        else
        {
           *ppv = NULL;
           hr = E_NOINTERFACE;
           goto Exit;
        }
        AddRef();

    Exit:
        return hr;
    }

    IFACEMETHODIMP NotificationActivatorFactory::CreateInstance(
        _In_ IUnknown* punkOuter,
        _In_ REFIID iid,
        _Outptr_ PVOID* ppv)
    {
        *ppv = nullptr;
        RETURN_HR_IF_NULL(CLASS_E_NOAGGREGATION, punkOuter);
        ComPtr<INotificationActivationCallback> activator;
        RETURN_IF_FAILED(MakeAndInitialize<NotificationActivator>(&activator));
        *ppv = (PVOID)activator.Detach();
        return S_OK;
    }

    IFACEMETHODIMP NotificationActivatorFactory::LockServer(_In_ BOOL Lock)
    {
        if (Lock)
        {
            ::InterlockedIncrement(&g_Count);
        }
        else
        {
            ::InterlockedDecrement(&g_Count);
        }

        return S_OK;
    }

private:
    ~NotificationActivatorFactory()
    {

    }

    LONG m_Ref;
};

namespace winrt::Microsoft::ToastNotificationsWinRt::implementation
{
    ToastActivatedEventArgs::ToastActivatedEventArgs(hstring const& appId, hstring const& arguments)
    {
        m_appId = appId;
        m_arguments = arguments;
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

        RETURN_IF_FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED));
        DWORD cookie;
        RETURN_IF_FAILED(CoRegisterClassObject(clsid, new NotificationActivatorFactory(), CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &cookie));
        return S_OK;
    }

    void DesktopToastNotificationManagerCompat::RegisterApplication(hstring const& clsid, hstring const& appId, hstring const& displayName, hstring const& iconPath)
    {
        if (!s_registeredAumidAndComServer)
        {
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

    bool DesktopToastNotificationManagerCompat::WasProcessToastActivated()
    {
        wstring commandLineArgs = GetCommandLine();
        auto found = commandLineArgs.find(TOAST_ACTIVATED_LAUNCH_ARG, 0);
        return found != std::wstring::npos;
    }

    winrt::event_token DesktopToastNotificationManagerCompat::ToastActivated(Windows::Foundation::EventHandler<Microsoft::ToastNotificationsWinRt::ToastActivatedEventArgs> const& handler)
    {
        winrt::event_token token;
        return token;
    }
    void DesktopToastNotificationManagerCompat::ToastActivated(winrt::event_token const& token) noexcept
    {
    }
}
