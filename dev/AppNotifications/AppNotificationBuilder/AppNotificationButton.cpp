#include "pch.h"
#include "AppNotificationButton.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationButton.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    AppNotificationButton::AppNotificationButton(winrt::hstring const& content) : m_content(content) { };

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::AddArgument(winrt::hstring const& key, winrt::hstring const& value)
    {
        m_arguments.Insert(key, value);
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetIconUri(winrt::Windows::Foundation::Uri const& iconUri)
    {
        m_iconUri = iconUri;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetProtocolActivation(winrt::Windows::Foundation::Uri const& protocolUri)
    {
        m_protocolUri = protocolUri;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetProtocolActivation(winrt::Windows::Foundation::Uri const& protocolUri, winrt::hstring const& targetApplicationPfn)
    {
        m_protocolUri = protocolUri;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetToolTip(winrt::hstring const& toolTip)
    {
        m_toolTip = toolTip;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetInputId(winrt::hstring const& inputId)
    {
        m_inputId = inputId;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::UseContextMenuPlacement()
    {
        m_useContextMenuPlacement = true;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetButtonStyle(ButtonStyle const& buttonStyle)
    {
        m_buttonStyle = buttonStyle;
        return *this;
    }

    winrt::hstring AppNotificationButton::GetXml()
    {
        winrt::hstring xml{ L"<action content=" + m_content + L" arguments="};

        if (m_protocolUri)
        {
            xml = xml + m_protocolUri.ToString() + LR"( activationType="protocol")";
            if (!m_targetApplicationPfn.empty())
            {
                xml = xml + L" protocolActivationTargetApplicationPfn=" + m_targetApplicationPfn;
            }
        }
        else
        {
            for (auto pair : m_arguments)
            {
                xml = xml + pair.Key();
                if (!pair.Value().empty())
                {
                    xml = xml + L"&" + pair.Value() + L";";
                }
            }
        }
        

        if (m_useContextMenuPlacement)
        {
            xml = xml + LR"( placement="contextMenu")";
        }

        if (m_iconUri)
        {
            xml = xml + L" imageUri=" + m_iconUri.ToString();
        }

        if (m_protocolUri)
        {
            xml = xml + LR"( activationType="protocol" protocolActivationTargetApplicationPfn=)" + m_protocolUri.ToString();
        }

        if (!m_inputId.empty())
        {
            xml = xml + L" hint-inputId=" + m_inputId;
        }

        if (m_buttonStyle == ButtonStyle::Success)
        {
            xml = xml + LR"( hint-buttonStyle="success")";
        }
        else if (m_buttonStyle == ButtonStyle::Success)
        {
            xml = xml + LR"( hint-buttonStyle="critical")";
        }

        if (!m_toolTip.empty())
        {
            xml = xml + L" hint-toolTip=" + m_toolTip;
        }

        xml = xml + L" />";
        return xml;
    }
}
