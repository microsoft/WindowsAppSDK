#pragma once
#include "Microsoft.Windows.AppNotifications.AppNotificationManager.g.h"
#include "NotificationActivationCallback.h"
#include "AppNotificationUtility.h"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    typedef winrt::Windows::Foundation::TypedEventHandler<
        winrt::Microsoft::Windows::AppNotifications::AppNotificationManager,
        winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs> NotificationActivationEventHandler;

    struct AppNotificationManager : AppNotificationManagerT<AppNotificationManager, INotificationActivationCallback>
    {
        AppNotificationManager() = default;

        static winrt::Microsoft::Windows::AppNotifications::AppNotificationManager Default();
        void Register(winrt::Microsoft::Windows::AppNotifications::AppNotificationActivationInfo const& details);
        void Unregister();
        winrt::event_token AppNotificationActivated(NotificationActivationEventHandler const& handler);
        void AppNotificationActivated(winrt::event_token const& token) noexcept;
        void Show(winrt::Microsoft::Windows::AppNotifications::AppNotification const& notification);
        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> UpdateProgressDataAsync(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const data, hstring const tag, hstring const group);
        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressResult> UpdateProgressDataAsync(winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData const data, hstring const tag);
        winrt::Microsoft::Windows::AppNotifications::AppNotificationSetting Enablement();
        winrt::Windows::Foundation::IAsyncAction RemoveByIdAsync(uint32_t notificationId);
        winrt::Windows::Foundation::IAsyncAction RemoveWithTagAsync(hstring tag);
        winrt::Windows::Foundation::IAsyncAction RemoveWithTagGroupAsync(hstring tag, hstring group);
        winrt::Windows::Foundation::IAsyncAction RemoveGroupAsync(hstring group);
        winrt::Windows::Foundation::IAsyncAction RemoveAllAsync();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::AppNotifications::AppNotification>> GetAllAsync();

        HRESULT __stdcall Activate(
            LPCWSTR appUserModelId,
            LPCWSTR invokedArgs,
            [[maybe_unused]] NOTIFICATION_USER_INPUT_DATA const* data,
            [[maybe_unused]] ULONG dataCount) noexcept;

    private:
        winrt::event<NotificationActivationEventHandler> m_notificationHandlers;
    };

    struct AppNotificationManagerFactory : winrt::implements<AppNotificationManagerFactory, IClassFactory>
    {
        STDMETHODIMP CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final try
        {
            RETURN_HR_IF(CLASS_E_NOAGGREGATION, aggregateInterface != nullptr);
            return AppNotificationManager::Default().as(interfaceId, object);
        }
        CATCH_RETURN()

        STDMETHODIMP LockServer(BOOL fLock) noexcept final
        {
            if (fLock)
            {
                ++winrt::get_module_lock();
            }
            else
            {
                --winrt::get_module_lock();
            }
            return S_OK;
        }
    };

}
namespace winrt::Microsoft::Windows::AppNotifications::factory_implementation
{
    struct AppNotificationManager : AppNotificationManagerT<AppNotificationManager, implementation::AppNotificationManager>
    {
    };
}
