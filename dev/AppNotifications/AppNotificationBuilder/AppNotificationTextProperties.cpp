#include "pch.h"
#include "AppNotificationTextProperties.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationTextProperties.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties AppNotificationTextProperties::SetLanguage(winrt::hstring const& value)
    {
        m_language = value;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties AppNotificationTextProperties::SetIncomingCallAlignment()
    {
        m_useCallScenarioAlign = true;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties AppNotificationTextProperties::SetMaxLines(int const& value)
    {
        m_maxLines = value;
        return *this;
    }

    winrt::hstring AppNotificationTextProperties::ToString()
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
