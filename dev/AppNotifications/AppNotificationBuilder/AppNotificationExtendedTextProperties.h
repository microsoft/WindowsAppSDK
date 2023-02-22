// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationExtendedTextProperties.g.h"
#include "AppNotificationTextProperties.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationExtendedTextProperties : AppNotificationExtendedTextPropertiesT<AppNotificationExtendedTextProperties, winrt::Windows::Foundation::IStringable>
    {
        AppNotificationExtendedTextProperties();

        // AppNotificationExtendedTextProperties Properties
        void Style(AppNotificationTextStyle const& value) { m_style = value; };
        AppNotificationTextStyle Style() { return m_style; };

        void MinLines(int const& value) { m_minLines = value; };
        int MinLines() { return m_minLines; };

        void Align(AppNotificationTextAlign const& value) { m_align = value; };
        AppNotificationTextAlign Align() { return m_align; };

        // AppNotificationTextProperties Properties
        void Language(winrt::hstring const& value) { m_basicTextProperties->Language(value); };
        winrt::hstring Language() { return m_basicTextProperties->Language(); };

        void MaxLines(int const& value) { m_basicTextProperties->MaxLines(value); };
        int MaxLines() { return m_basicTextProperties->MaxLines(); };

        void IncomingCallAlignment(bool const& value) { m_basicTextProperties->IncomingCallAlignment(value); };
        bool IncomingCallAlignment() { return m_basicTextProperties->IncomingCallAlignment(); };

        // Fluent AppNotificationExtendedTextProperties Setters
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties SetStyle(AppNotificationTextStyle const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties SetMinLines(int const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties SetAlign(AppNotificationTextAlign const& value);

        // Fluent AppNotificationTextProperties Setters
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties SetLanguage(winrt::hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties SetIncomingCallAlignment();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties SetMaxLines(int const& value);

        // IStringable
        winrt::hstring ToString();

    private:
        winrt::com_ptr<AppNotificationTextProperties> m_basicTextProperties;
        virtual winrt::hstring ToStringInternal();

        std::wstring StyleToString();
        std::wstring AlignToString();

        AppNotificationTextStyle m_style{ AppNotificationTextStyle::Default };
        int m_minLines;
        AppNotificationTextAlign m_align;
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationExtendedTextProperties : AppNotificationExtendedTextPropertiesT<AppNotificationExtendedTextProperties, implementation::AppNotificationExtendedTextProperties>
    {
    };
}
