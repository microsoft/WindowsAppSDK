#pragma once
#include "Microsoft.Windows.ToastNotifications.ToastNotificationHistory.g.h"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    struct ToastNotificationHistory : ToastNotificationHistoryT<ToastNotificationHistory>
    {
        ToastNotificationHistory() = default;

        winrt::Windows::Foundation::IAsyncAction RemoveWithIdentiferAsync(uint32_t toastIdentifier);
        winrt::Windows::Foundation::IAsyncAction RemoveWithTagAsync(hstring tag);
        winrt::Windows::Foundation::IAsyncAction RemoveWithTagGroupAsync(hstring tag, hstring group);
        winrt::Windows::Foundation::IAsyncAction RemoveGroupAsync(hstring group);
        winrt::Windows::Foundation::IAsyncAction RemoveAllAsync();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ToastNotifications::ToastNotification>> GetAllAsync();
    };
}
