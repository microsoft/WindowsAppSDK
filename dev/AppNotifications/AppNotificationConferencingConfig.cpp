// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "AppNotificationConferencingConfig.h"
#include "Microsoft.Windows.AppNotifications.AppNotificationConferencingConfig.g.cpp"
#include <IsWindowsVersion.h>

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

    ///Checks if the calling preview feature is supported on the current OS version
    ///TO DO - This method needs implementation on framework UDK, for now it always returns false
    bool AppNotificationConferencingConfig::IsCallingPreviewSupported()
    {
        return false;
    }
}
