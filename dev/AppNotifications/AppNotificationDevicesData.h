#pragma once
#include "Microsoft.Windows.AppNotifications.AppNotificationDevicesData.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    struct AppNotificationDevicesData : AppNotificationDevicesDataT<AppNotificationDevicesData>
    {
        AppNotificationDevicesData() = default;

        // Getters
        hstring CameraDeviceId();
        hstring MicrophoneDeviceId();
        hstring SpeakerDeviceId();

        // Setters
        void CameraDeviceId(hstring const& value);
        void MicrophoneDeviceId(hstring const& value);
        void SpeakerDeviceId(hstring const& value);

        static bool IsVideoOrAudioCallingSupported();

    private:

        hstring m_cameraDeviceId{};
        hstring m_microphoneDeviceId{};
        hstring m_speakerDeviceId{};
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::factory_implementation
{
    struct AppNotificationDevicesData : AppNotificationDevicesDataT<AppNotificationDevicesData, implementation::AppNotificationDevicesData>
    {
    };
}
