#include "pch.h"
#include "AppNotificationDevicesData.h"
#include "Microsoft.Windows.AppNotifications.AppNotificationDevicesData.g.cpp"
#include <IsWindowsVersion.h>

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    hstring AppNotificationDevicesData::CameraDeviceId()
    {
        return m_cameraDeviceId;
    }

    void AppNotificationDevicesData::CameraDeviceId(hstring const& value)
    {
        m_cameraDeviceId = value;
    }

    hstring AppNotificationDevicesData::MicrophoneDeviceId()
    {
        return m_microphoneDeviceId;
    }

    void AppNotificationDevicesData::MicrophoneDeviceId(hstring const& value)
    {
        m_microphoneDeviceId = value;
    }

    hstring AppNotificationDevicesData::SpeakerDeviceId()
    {
        return m_speakerDeviceId;
    }

    void AppNotificationDevicesData::SpeakerDeviceId(hstring const& value)
    {
        m_speakerDeviceId = value;
    }

    /// <summary>
    /// verifies if video calling is supported
    /// </summary>
    /// <returns>bool</returns>
    bool AppNotificationDevicesData::IsVideoCallingSupported()
    {
        return WindowsVersion::IsWindows11_23H1OrGreater(); // Windows 11 23H1 or greater
    }
}
