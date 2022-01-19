#include "pch.h"
#include "ToastNotificationHistory.h"
#include "Microsoft.Windows.ToastNotifications.ToastNotificationHistory.g.cpp"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    winrt::Windows::Foundation::IAsyncAction ToastNotificationHistory::RemoveWithIdentiferAsync(uint32_t toastIdentifier)
    {
        std::wstring appId{ RetrieveAppId() };
        auto hr{ ToastNotifications_RemoveToast(appId.c_str(), toastIdentifier) };

        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::IAsyncAction ToastNotificationHistory::RemoveWithTagAsync(hstring /* tag */)
    {
        std::wstring appId{ RetrieveAppId() };
        auto hr{ ToastNotifications_RemoveToastsWithTagAndGroup(appId.c_str(), tag.get(), nullptr) };

        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::IAsyncAction ToastNotificationHistory::RemoveWithTagGroupAsync(hstring tag, hstring group)
    {
        std::wstring appId{ RetrieveAppId() };
        auto hr{ ToastNotifications_RemoveToastsWithTagAndGroup(appId.c_str(), tag.get(), group.get()) };

        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::IAsyncAction ToastNotificationHistory::RemoveGroupAsync(hstring /* group */)
    {
        std::wstring appId{ RetrieveAppId() };
        auto hr{ ToastNotifications_RemoveToastsWithTagAndGroup(appId.c_str(), nullptr, group.get()) };

        throw hresult_not_implemented();
    }

    winrt::Windows::Foundation::IAsyncAction ToastNotificationHistory::RemoveAllAsync()
    {
        std::wstring appId{ RetrieveAppId() };
        auto hr{ ToastNotifications_RemoveAllToastsForApp(appId.c_str()) };

        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::ToastNotifications::ToastNotification>> ToastNotificationHistory::GetAllAsync()
    {
        throw hresult_not_implemented();
    }
}
