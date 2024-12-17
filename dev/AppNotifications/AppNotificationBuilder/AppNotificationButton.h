// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationButton.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{

    struct AppNotificationButton : AppNotificationButtonT<AppNotificationButton, winrt::Windows::Foundation::IStringable>
    {
        AppNotificationButton() = default;
        AppNotificationButton(winrt::hstring const& content);

        // Properties
        void Content(winrt::hstring const& value) { m_content = value; };
        winrt::hstring Content() { return m_content; };

        void Arguments(winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> const& value) { m_arguments = value; };
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> Arguments() { return m_arguments; };

        void Icon(winrt::Windows::Foundation::Uri const& value) { m_iconUri = value; };
        winrt::Windows::Foundation::Uri Icon() { return m_iconUri; };

        void ToolTip(winrt::hstring const& value) { m_toolTip = value; };
        winrt::hstring ToolTip() { return m_toolTip; };

        void ContextMenuPlacement(bool const& value) { m_useContextMenuPlacement = value; };
        bool ContextMenuPlacement() { return m_useContextMenuPlacement; };

        void ButtonStyle(AppNotificationButtonStyle const& value) { m_buttonStyle = value; };
        AppNotificationButtonStyle ButtonStyle() { return m_buttonStyle; };

        void InputId(winrt::hstring const& value) { m_inputId = value; };
        winrt::hstring InputId() { return m_inputId; };

        void InvokeUri(winrt::Windows::Foundation::Uri const& value) { m_protocolUri = value; };
        winrt::Windows::Foundation::Uri InvokeUri() { return m_protocolUri; };

        void TargetAppId(winrt::hstring const& value) { m_targetApplicationPfn = value; };
        winrt::hstring TargetAppId() { return m_targetApplicationPfn; };

        // Fluent setters
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AddArgument(winrt::hstring const& key, winrt::hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetIcon(winrt::Windows::Foundation::Uri const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetToolTip(winrt::hstring const& value);
        static bool IsToolTipSupported();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetContextMenuPlacement();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetButtonStyle(AppNotificationButtonStyle const& value);
        static bool IsButtonStyleSupported();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetInputId(winrt::hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetInvokeUri(winrt::Windows::Foundation::Uri const& protocolUri);
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetInvokeUri(winrt::Windows::Foundation::Uri const& protocolUri, winrt::hstring const& targetAppId);

        winrt::hstring ToString();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton SetSettingStyle(AppNotificationButtonSettingStyle const& value);

    private:
        std::wstring GetActivationArguments();
        std::wstring GetButtonStyle();
        std::wstring GetSettingStyle();

        winrt::hstring m_content{};
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::hstring> m_arguments { winrt::single_threaded_map<winrt::hstring, winrt::hstring>() };
        winrt::Windows::Foundation::Uri m_iconUri{ nullptr };
        winrt::Windows::Foundation::Uri m_protocolUri{ nullptr };
        winrt::hstring m_targetApplicationPfn{};
        winrt::hstring m_toolTip{};
        winrt::hstring m_inputId{};
        bool m_useContextMenuPlacement{};
        AppNotificationButtonStyle m_buttonStyle { AppNotificationButtonStyle::Default };
        AppNotificationButtonSettingStyle m_settingType{ AppNotificationButtonSettingStyle::None };
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationButton : AppNotificationButtonT<AppNotificationButton, implementation::AppNotificationButton>
    {
    };
}
