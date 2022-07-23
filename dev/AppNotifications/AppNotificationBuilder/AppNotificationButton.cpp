#include "pch.h"
#include "AppNotificationButton.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationButton.g.cpp"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    AppNotificationButton::AppNotificationButton(winrt::hstring const& content) : m_content(content) { };

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::AddArgument(winrt::hstring const& key, winrt::hstring const& value)
    {
        THROW_HR_IF(E_INVALIDARG, key.empty());
        THROW_HR_IF(E_INVALIDARG, m_protocolUri);

        m_arguments.Insert(key, value);
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetIconUri(winrt::Windows::Foundation::Uri const& iconUri)
    {
        m_iconUri = iconUri;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetInvokeUri(winrt::Windows::Foundation::Uri const& protocolUri)
    {
        THROW_HR_IF(E_INVALIDARG, m_arguments.Size() > 0u);

        m_protocolUri = protocolUri;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetInvokeUri(winrt::Windows::Foundation::Uri const& protocolUri, winrt::hstring const& targetApplicationPfn)
    {
        THROW_HR_IF(E_INVALIDARG, m_arguments.Size() > 0u);

        m_protocolUri = protocolUri;
        m_targetApplicationPfn = targetApplicationPfn;
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

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetContextMenuPlacement()
    {
        m_useContextMenuPlacement = true;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetButtonStyle(AppNotificationButtonStyle const& buttonStyle)
    {
        m_buttonStyle = buttonStyle;
        return *this;
    }

    winrt::hstring AppNotificationButton::GetXml()
    {
        winrt::hstring xml{ L"<action content=\"" + m_content + L"\" arguments=\""};


        if (m_protocolUri)
        {
            xml = xml + m_protocolUri.ToString() + LR"(" activationType="protocol")";
            if (!m_targetApplicationPfn.empty())
            {
                xml = xml + L" protocolActivationTargetApplicationPfn=\"" + m_targetApplicationPfn + L"\"";
            }
        }
        else
        {
            std::wstring arguments{};
            for (auto pair : m_arguments)
            {
                arguments = arguments + pair.Key();
                if (!pair.Value().empty())
                {
                    arguments = arguments + L"=" + pair.Value();
                }
                arguments = arguments + L";";
            }

            xml = xml + arguments.substr(0, arguments.size() - 1) + L"\"";
        }
        

        if (m_useContextMenuPlacement)
        {
            xml = xml + LR"( placement="contextMenu")";
        }

        if (m_iconUri)
        {
            xml = xml + L" imageUri=\"" + m_iconUri.ToString() + L"\"";
        }

        if (!m_inputId.empty())
        {
            xml = xml + L" hint-inputId=\"" + m_inputId + L"\"";
        }

        if (m_buttonStyle == AppNotificationButtonStyle::Success)
        {
            xml = xml + LR"( hint-buttonStyle="Success")";
        }
        else if (m_buttonStyle == AppNotificationButtonStyle::Success)
        {
            xml = xml + LR"( hint-buttonStyle="Critical")";
        }

        if (!m_toolTip.empty())
        {
            xml = xml + L" hint-toolTip=\"" + m_toolTip + L"\"";
        }

        xml = xml + L"/>";
        return xml;
    }
}
