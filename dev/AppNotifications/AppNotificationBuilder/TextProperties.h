#pragma once
#include "Microsoft.Windows.AppNotifications.Builder.TextProperties.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    struct TextProperties : TextPropertiesT<TextProperties>
    {
        TextProperties() = default;

        winrt::Microsoft::Windows::AppNotifications::Builder::TextProperties SetMaxLines(int const& maxLines);

        winrt::Microsoft::Windows::AppNotifications::Builder::TextProperties SetLanguage(winrt::hstring const& language);

        winrt::Microsoft::Windows::AppNotifications::Builder::TextProperties UsesCallScenarioAlign();
        bool GetCallScenarioAlign() { return m_useCallScenarioAlign; };

        winrt::hstring GetXml();

    private:
        int m_maxLines{ 0 };
        winrt::hstring m_language;
        bool m_useCallScenarioAlign{};
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::Builder::factory_implementation
{
    struct TextProperties : TextPropertiesT<TextProperties, implementation::TextProperties>
    {
    };
}
