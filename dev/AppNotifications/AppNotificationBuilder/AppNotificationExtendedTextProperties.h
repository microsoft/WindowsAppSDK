// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationExtendedTextProperties.g.h"
#include "AppNotificationTextProperties.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationExtendedTextProperties : AppNotificationExtendedTextPropertiesT<AppNotificationExtendedTextProperties, implementation::AppNotificationTextProperties>
    {
        AppNotificationExtendedTextProperties() = default;

        // Properties
        void Style(AppNotificationTextStyle const& value) { m_style = value; };
        AppNotificationTextStyle Style() { return m_style; };

        void MinLines(int const& value) { m_minLines = value; };
        int MinLines() { return m_minLines; };

        void Align(AppNotificationTextAlign const& value) { m_align = value; };
        AppNotificationTextAlign Align() { return m_align; };

        // Fluent Setters
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties SetStyle(AppNotificationTextStyle const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties SetMinLines(int const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationExtendedTextProperties SetAlign(AppNotificationTextAlign const& value);

    private:
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
