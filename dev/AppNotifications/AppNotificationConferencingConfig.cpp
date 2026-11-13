// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "AppNotificationConferencingConfig.h"
#include "Microsoft.Windows.AppNotifications.AppNotificationConferencingConfig.g.cpp"
#include <IsWindowsVersion.h>
#include "TerminalVelocityFeatures-CallingPreviewSupport.h"
#include <frameworkudk/wnpnotifications.h>

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    hstring AppNotificationConferencingConfig::VideoDeviceId()
    {
        return m_videoDeviceId;
    }

    void AppNotificationConferencingConfig::VideoDeviceId(hstring const& value)
    {
        THROW_HR_IF(E_NOTIMPL, !IsCallingPreviewSupported());
        m_videoDeviceId = value;
    }

    hstring AppNotificationConferencingConfig::AudioInputDeviceId()
    {
        return m_audioInputDeviceId;
    }

    void AppNotificationConferencingConfig::AudioInputDeviceId(hstring const& value)
    {
        THROW_HR_IF(E_NOTIMPL, !IsCallingPreviewSupported());
        m_audioInputDeviceId = value;
    }

    hstring AppNotificationConferencingConfig::AudioOutputDeviceId()
    {
        return m_audioOutputDeviceId;
    }

    void AppNotificationConferencingConfig::AudioOutputDeviceId(hstring const& value)
    {
        THROW_HR_IF(E_NOTIMPL, !IsCallingPreviewSupported());
        m_audioOutputDeviceId = value;
    }

    //Checks if the calling preview feature is supported on the current OS version
    bool AppNotificationConferencingConfig::IsCallingPreviewSupported()
    {
        BOOL isSupported{};
        THROW_IF_FAILED(WnpNotifications_IsCallingPreviewSupported(&isSupported));
        return isSupported;
    }
}
