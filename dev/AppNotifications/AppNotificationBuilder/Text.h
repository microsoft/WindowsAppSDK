#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.Text.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct Text : TextT<Text>
    {
        Text(winrt::hstring const& content);

        Text(winrt::hstring const& content, int const& maxLines);
        winrt::Microsoft::Windows::AppNotifications::Builder::Text SetLanguage(winrt::hstring const& language);

        winrt::Microsoft::Windows::AppNotifications::Builder::Text UseCallScenarioAlign();

        winrt::Microsoft::Windows::AppNotifications::Builder::Text UseAttributionText();

        winrt::hstring GetXml();

    private:
        winrt::hstring m_content;
        int m_maxLines{ 0 };
        winrt::hstring m_language;
        bool m_useCallScenarioAlign{};
        bool m_useAttributionText{};
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct Text : TextT<Text, implementation::Text>
    {
    };
}
