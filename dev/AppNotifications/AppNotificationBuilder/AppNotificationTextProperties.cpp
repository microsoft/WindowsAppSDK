#include "pch.h"
#include "AppNotificationTextProperties.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationTextProperties.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties AppNotificationTextProperties::SetMaxLines(int const& maxLines)
    {
        m_maxLines = maxLines;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties AppNotificationTextProperties::SetLanguage(winrt::hstring const& language)
    {
        m_language = language;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties AppNotificationTextProperties::UsesCallScenarioAlign()
    {
        m_useCallScenarioAlign = true;
        return *this;
    }

    winrt::hstring AppNotificationTextProperties::GetXml()
    {
        winrt::hstring xmlResult{ L"<text"};
        if (!m_language.empty())
        {
            xmlResult = xmlResult + L" lang=\"" + m_language + L"\"";
        }

        if (m_maxLines)
        {
            xmlResult = xmlResult + L" hint-maxLines=\"" + winrt::to_hstring(m_maxLines) + L"\"";
        }

        if (m_useCallScenarioAlign)
        {
            xmlResult = xmlResult + L" hint-callScenarioCenterAlign=\"true\"";
        }
        return xmlResult + L">";
    }
}
