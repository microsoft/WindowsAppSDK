// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationTextProperties.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationTextProperties : AppNotificationTextPropertiesT<AppNotificationTextProperties, winrt::Windows::Foundation::IStringable>
    {
        AppNotificationTextProperties() = default;

        // Properties
        void Language(winrt::hstring const& value) { m_language = value; };
        winrt::hstring Language() { return m_language; };

        void MaxLines(int const& value) { m_maxLines = value; };
        int MaxLines() { return m_maxLines; };

        void IncomingCallAlignment(bool const& value) { m_useCallScenarioAlign = value; };
        bool IncomingCallAlignment() { return m_useCallScenarioAlign; };

        void Style(AppNotificationTextStyle const& value) { m_style = value; };
        AppNotificationTextStyle Style() { return m_style; };

        void Wrap(bool const& value) { m_wrap = value; };
        bool Wrap() { return m_wrap; };

        void MinLines(int const& value) { m_minLines = value; };
        int MinLines() { return m_minLines; };

        void Align(AppNotificationTextAlign const& value) { m_align = value; };
        AppNotificationTextAlign Align() { return m_align; };

        // Fluent Setters
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties SetLanguage(winrt::hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties SetIncomingCallAlignment();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties SetMaxLines(int const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties SetStyle(AppNotificationTextStyle const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties SetWrap();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties SetMinLines(int const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties SetAlign(AppNotificationTextAlign const& value);

        // IStringable
        winrt::hstring ToString();

    private:
        std::wstring StyleToString();
        std::wstring AlignToString();

        int m_maxLines{ 0 };
        winrt::hstring m_language{};
        bool m_useCallScenarioAlign{};
        AppNotificationTextStyle m_style{ AppNotificationTextStyle::Default };
        bool m_wrap;
        int m_minLines;
        AppNotificationTextAlign m_align;
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationTextProperties : AppNotificationTextPropertiesT<AppNotificationTextProperties, implementation::AppNotificationTextProperties>
    {
    };
}
