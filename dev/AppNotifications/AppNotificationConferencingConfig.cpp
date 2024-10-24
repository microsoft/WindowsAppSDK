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
        m_videoDeviceId = value;
    }

    hstring AppNotificationConferencingConfig::AudioInputDeviceId()
    {
        return m_audioInputDeviceId;
    }

    void AppNotificationConferencingConfig::AudioInputDeviceId(hstring const& value)
    {
        m_audioInputDeviceId = value;
    }

    hstring AppNotificationConferencingConfig::AudioOutputDeviceId()
    {
        return m_audioOutputDeviceId;
    }

    void AppNotificationConferencingConfig::AudioOutputDeviceId(hstring const& value)
    {
        m_audioOutputDeviceId = value;
    }

    /// <summary>
    /// verifies if video calling is supported <TO DO>
    /// </summary>
    /// <returns>bool</returns>
    bool AppNotificationConferencingConfig::IsVideoOrAudioCallingSupported()
    {
        return WindowsVersion::IsWindows11_23H1OrGreater(); // Windows 11 23H1 or greater
    }
}
