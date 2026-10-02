// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.AppNotifications.AppNotificationConferencingConfig.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    struct AppNotificationConferencingConfig : AppNotificationConferencingConfigT<AppNotificationConferencingConfig>
    {
        AppNotificationConferencingConfig() = default;

        // Getters
        hstring VideoDeviceId();
        hstring AudioInputDeviceId();
        hstring AudioOutputDeviceId();

        // Setters
        void VideoDeviceId(hstring const& value);
        void AudioInputDeviceId(hstring const& value);
        void AudioOutputDeviceId(hstring const& value);

        static bool IsCallingPreviewSupported();

    private:

        hstring m_videoDeviceId{};
        hstring m_audioInputDeviceId{};
        hstring m_audioOutputDeviceId{};
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::factory_implementation
{
    struct AppNotificationConferencingConfig : AppNotificationConferencingConfigT<AppNotificationConferencingConfig, implementation::AppNotificationConferencingConfig>
    {
    };
}
