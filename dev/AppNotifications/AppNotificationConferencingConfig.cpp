// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "AppNotificationConferencingConfig.h"
#include "Microsoft.Windows.AppNotifications.AppNotificationConferencingConfig.g.cpp"
#include <IsWindowsVersion.h>
#include "TerminalVelocityFeatures-CallingPreviewSupport.h"

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
    bool AppNotificationConferencingConfig::IsCallingPreviewSupported()
    {
        return WindowsVersion::IsWindows11_22H2OrGreater();
    }
}

// This function (not in the "implementation" namespace) is not defined when the feature is disabled,
// resulting in a linker error. Define the function for that scenario.
#if WINDOWSAPPRUNTIME_MICROSOFT_WINDOWS_CALLINGPREVIEWSUPPORT_FEATURE_CALLINGPREVIEWSUPPORT_ENABLED != 1
namespace winrt::Microsoft::Windows::AppNotifications
{
    bool AppNotificationConferencingConfig::IsCallingPreviewSupported()
    {
        return WindowsVersion::IsWindows11_22H2OrGreater();
    }
}
#endif
