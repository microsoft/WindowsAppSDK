#include "pch.h"
#include "Text.h"
#include "Microsoft.Windows.AppNotifications.Builder.Text.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    Text::Text(winrt::hstring const& content) : m_content(content) { };

    winrt::Microsoft::Windows::AppNotifications::Builder::Text Text::SetLanguage(winrt::hstring const& language)
    {
        m_language = language;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::Text Text::UseCallScenarioAlign()
    {
        m_useCallScenarioAlign = true;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::Text Text::UseAttributionText()
    {
        m_useAttributionText = true;
        return *this;
    }

    winrt::hstring Text::GetXml()
    {
        winrt::hstring xml{ L"<text" };
        if (!m_language.empty())
        {
            xml = xml + L" lang=" + m_language;
        }

        if (m_useCallScenarioAlign)
        {
            xml = xml + L" hint-callScenarioCenterAlign=true";
        }

        if (m_useAttributionText)
        {
            xml = xml + LR"( placement="attribution")";
        }

        xml = L">" + m_content + LR"(</text>)";
        return xml;
    }
}
