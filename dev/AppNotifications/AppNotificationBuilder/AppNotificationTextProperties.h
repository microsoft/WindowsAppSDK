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

        // Fluent Setters
        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties SetLanguage(winrt::hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties SetIncomingCallAlignment();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties SetMaxLines(int const& value);

        // IStringable
        winrt::hstring ToString();

    private:
        int m_maxLines{ 0 };
        winrt::hstring m_language{};
        bool m_useCallScenarioAlign{};
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationTextProperties : AppNotificationTextPropertiesT<AppNotificationTextProperties, implementation::AppNotificationTextProperties>
    {
    };
}
