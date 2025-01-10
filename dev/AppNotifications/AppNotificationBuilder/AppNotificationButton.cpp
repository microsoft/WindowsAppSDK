// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "externs.h"
#include "AppNotificationButton.h"
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationButton.g.cpp"
#include <IsWindowsVersion.h>
#include "AppNotificationBuilderUtility.h"
#include "AppNotificationBuilderTelemetry.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    AppNotificationButton::AppNotificationButton(winrt::hstring const& content) : m_content(content) { };

    bool AppNotificationButton::IsToolTipSupported()
    {
        return WindowsVersion::IsWindows10_20H1OrGreater();
    }

    bool AppNotificationButton::IsButtonStyleSupported()
    {
        return WindowsVersion::IsWindows10_20H1OrGreater();
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::AddArgument(winrt::hstring const& key, winrt::hstring const& value)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, key.empty(), "You must provide a key when adding an argument");
        THROW_HR_IF_MSG(E_INVALIDARG, m_protocolUri, "You cannot add an argument after calling SetInvokeUri");

        m_arguments.Insert(EncodeArgument(key.c_str()), EncodeArgument(value.c_str()));
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetIcon(winrt::Windows::Foundation::Uri const& value)
    {
        m_iconUri = value;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetToolTip(winrt::hstring const& value)
    {
        m_toolTip = EncodeXml(value.c_str()).c_str();
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetContextMenuPlacement()
    {
        m_useContextMenuPlacement = true;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetButtonStyle(AppNotificationButtonStyle const& value)
    {
        m_buttonStyle = value;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetInputId(winrt::hstring const& value)
    {
        m_inputId = EncodeXml(value.c_str()).c_str();
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetInvokeUri(winrt::Windows::Foundation::Uri const& protocolUri)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, m_arguments.Size() > 0u, "You cannot add a protocol activation uri after calling AddArgument");

        m_protocolUri = protocolUri;
        return *this;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetInvokeUri(winrt::Windows::Foundation::Uri const& protocolUri, winrt::hstring const& targetAppId)
    {
        THROW_HR_IF_MSG(E_INVALIDARG, m_arguments.Size() > 0u, "You cannot add a protocol activation uri after calling AddArgument");

        m_protocolUri = protocolUri;
        m_targetApplicationPfn = targetAppId;
        return *this;
    }

    std::wstring AppNotificationButton::GetActivationArguments()
    {
        if (m_protocolUri)
        {
            std::wstring protocolTargetPfn{ !m_targetApplicationPfn.empty() ? wil::str_printf<std::wstring>(L" protocolActivationTargetApplicationPfn='%ls'", m_targetApplicationPfn.c_str()) : L"" };
            return wil::str_printf<std::wstring>(L" arguments='%ws' activationType='protocol'%ls", m_protocolUri.ToString().c_str(), protocolTargetPfn.c_str());
        }
        else
        {
            std::wstring arguments;
            for (auto pair : m_arguments)
            {
                if (!pair.Value().empty())
                {
                    arguments.append(wil::str_printf<std::wstring>(L"%ls=%ls;", pair.Key().c_str(), pair.Value().c_str()));
                }
                else
                {
                    arguments.append(wil::str_printf<std::wstring>(L"%ls;", pair.Key().c_str()));
                }
            }
            arguments.pop_back();

            return wil::str_printf<std::wstring>(L" arguments='%ls'", arguments.c_str());
        }
    }

    std::wstring AppNotificationButton::GetButtonStyle()
    {
        if (m_buttonStyle == AppNotificationButtonStyle::Default)
        {
            return L"";
        }

        std::wstring style{ m_buttonStyle == AppNotificationButtonStyle::Success ? L"Success" : L"Critical" };
        return wil::str_printf<std::wstring>(L" hint-buttonStyle='%ls'", style.c_str());
    }

    winrt::hstring AppNotificationButton::ToString()
    {
        auto logTelemetry{ AppNotificationBuilderTelemetry::ButtonToString::Start(g_telemetryHelper) };

        std::wstring xmlResult{ wil::str_printf<std::wstring>(L"<action content='%ls'%ls%ls%ls%ls%ls%ls%ls/>",
            m_content.c_str(),
            GetActivationArguments().c_str(),
            m_useContextMenuPlacement ? L" placement='contextMenu'" : L"",
            m_iconUri ? wil::str_printf<std::wstring>(L" imageUri='%ls'", m_iconUri.ToString().c_str()).c_str() : L"",
            !m_inputId.empty() ? wil::str_printf<std::wstring>(L" hint-inputId='%ls'", m_inputId.c_str()).c_str() : L"",
            GetButtonStyle().c_str(),
            !m_toolTip.empty() ? wil::str_printf<std::wstring>(L" hint-toolTip='%ls'", m_toolTip.c_str()).c_str() : L"",
            GetSettingStyle().c_str()) };

        logTelemetry.Stop();

        return xmlResult.c_str();
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationButton::SetSettingStyle(AppNotificationButtonSettingStyle const& value)
    {
        THROW_HR_IF(E_NOTIMPL, !AppNotificationConferencingConfig::IsCallingPreviewSupported());

        m_settingType = value;
        return *this;
    }

    std::wstring AppNotificationButton::GetSettingStyle()
    {
        switch (m_settingType)
        {
        case AppNotificationButtonSettingStyle::VideoCallConfig:
            return L" settingType='videoDevices'";
        case AppNotificationButtonSettingStyle::AudioCallConfig:
            return L" settingType='audioDevices'";
        default: // AppNotificationButtonSettingStyle::None
            return L"";
        }
    }
}
