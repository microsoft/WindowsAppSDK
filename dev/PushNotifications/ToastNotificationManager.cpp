#include "pch.h"
#include "ToastNotificationManager.h"
#include "Microsoft.Windows.PushNotifications.ToastNotificationManager.g.cpp"
#include "ToastActivationCallback.h"
#include "externs.h"

static winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Windows::PushNotifications::ToastActivatedEventArgs>> g_toastHandlers;

static int g_toastHandlerCount = 0;

winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Microsoft::Windows::PushNotifications::ToastActivatedEventArgs>>& GetToastHandlers()
{
    return g_toastHandlers;
}

int& GetToastHandleCount()
{
    return g_toastHandlerCount;
}

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    static wil::unique_com_class_object_cookie s_toastcomActivatorRegistration;

    void ToastNotificationManager::RegisterActivator(winrt::guid const& taskClsid)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, s_toastcomActivatorRegistration, "ComActivator already registered.");

        GetWaitHandleForArgs().create();

        THROW_IF_FAILED(::CoRegisterClassObject(
            taskClsid,
            winrt::make<ToastActivationCallback_factory>().get(),
            CLSCTX_LOCAL_SERVER,
            REGCLS_MULTIPLEUSE,
            &s_toastcomActivatorRegistration));
    }

    void ToastNotificationManager::UnRegisterActivator()
    {
        THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !s_toastcomActivatorRegistration, "ComActivator not registered.");
        s_toastcomActivatorRegistration.reset();
    }

    winrt::event_token ToastNotificationManager::ToastActivated(winrt::Windows::Foundation::EventHandler<Microsoft::Windows::PushNotifications::ToastActivatedEventArgs> handler)
    {
        GetToastHandleCount()++;
        return GetToastHandlers().add(handler);
    }

    void ToastNotificationManager::ToastActivated(winrt::event_token const& token) noexcept
    {
        GetToastHandleCount()--;
        GetToastHandlers().remove(token);
    }
}
