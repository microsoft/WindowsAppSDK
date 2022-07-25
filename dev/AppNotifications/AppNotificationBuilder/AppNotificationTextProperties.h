#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationTextProperties.g.h"
#include "ITextProperties.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct AppNotificationTextProperties : AppNotificationTextPropertiesT<AppNotificationTextProperties, ITextProperties>
    {
        AppNotificationTextProperties() = default;

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties SetLanguage(winrt::hstring const& value);

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties SetIncomingCallAlignment();

        winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties SetMaxLines(int const& value);

        winrt::hstring GetXml();

        // ITextProperties
        int GetMaxLines() { return m_maxLines; };
        winrt::hstring GetLanguage() { return m_language; };
        bool GetCallScenarioAlign() { return m_useCallScenarioAlign; };

    private:
        int m_maxLines{ 0 };
        winrt::hstring m_language;
        bool m_useCallScenarioAlign{};
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct AppNotificationTextProperties : AppNotificationTextPropertiesT<AppNotificationTextProperties, implementation::AppNotificationTextProperties>
    {
    };
}
