#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationButton.g.h"
#include "IAppNotificationButton.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{

    struct AppNotificationButton : AppNotificationButtonT<AppNotificationButton, IAppNotificationButton>
    {
        AppNotificationButton() = default;
        AppNotificationButton(winrt::hstring const& content);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AddArgument(winrt::hstring const& key, winrt::hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetIconUri(winrt::Windows::Foundation::Uri const& iconUri);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetToolTip(winrt::hstring const& toolTip);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetInputId(winrt::hstring const& inputId);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetInvokeUri(winrt::Windows::Foundation::Uri const& protocolUri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetInvokeUri(winrt::Windows::Foundation::Uri const& protocolUri, winrt::hstring const& targetApplicationPfn);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton UseContextMenuPlacement();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetButtonStyle(AppNotificationButtonStyle const& buttonStyle);

        winrt::hstring GetXml();

        // IAppNotificationButton
        AppNotificationButtonStyle GetButtonStyle() { return m_buttonStyle; };

    private:
        winrt::hstring m_content;
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> m_arguments { winrt::single_threaded_map<winrt::hstring, winrt::hstring>() };
        winrt::Windows::Foundation::Uri m_iconUri{ nullptr };
        winrt::Windows::Foundation::Uri m_protocolUri{ nullptr };
        winrt::hstring m_targetApplicationPfn;
        winrt::hstring m_toolTip;
        winrt::hstring m_inputId;
        bool m_useContextMenuPlacement{};
        AppNotificationButtonStyle m_buttonStyle { AppNotificationButtonStyle::Default };
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationButton : AppNotificationButtonT<AppNotificationButton, implementation::AppNotificationButton>
    {
    };
}
