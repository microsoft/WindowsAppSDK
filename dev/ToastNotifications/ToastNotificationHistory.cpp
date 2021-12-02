#include "pch.h"
#include "ToastNotificationHistory.h"
#include "Microsoft.Windows.ToastNotifications.ToastNotificationHistory.g.cpp"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    winrt::Windows::Foundation::IAsyncAction ToastNotificationHistory::RemoveWithIdentiferAsync(uint32_t /* toastIdentifier */)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ToastNotificationHistory::RemoveWithTagAsync(hstring /* tag */)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ToastNotificationHistory::RemoveWithTagGroupAsync(hstring /* tag */, hstring /* group */)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ToastNotificationHistory::RemoveGroupAsync(hstring /* group */)
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncAction ToastNotificationHistory::RemoveAllAsync()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ToastNotifications::ToastNotification>> ToastNotificationHistory::GetAllAsync()
    {
        throw hresult_not_implemented();
    }
}
