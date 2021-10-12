#include "pch.h"
#include "ToastNotificationManager.h"
#include "Microsoft.Windows.PushNotifications.ToastNotificationManager.g.cpp"
#include "ToastBackgroundTask.h"

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    static wil::unique_com_class_object_cookie s_toastcomActivatorRegistration;

    void ToastNotificationManager::RegisterActivator(winrt::guid const& taskClsid)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, s_toastcomActivatorRegistration, "ComActivator already registered.");

        THROW_IF_FAILED(::CoRegisterClassObject(
            taskClsid,
            winrt::make<ToastBackgroundTask_factory>().get(),
            CLSCTX_LOCAL_SERVER,
            REGCLS_MULTIPLEUSE,
            &s_toastcomActivatorRegistration));
    }

    void ToastNotificationManager::UnRegisterActivator()
    {
        THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), !s_toastcomActivatorRegistration, "ComActivator not registered.");
        s_toastcomActivatorRegistration.reset();
    }
}
