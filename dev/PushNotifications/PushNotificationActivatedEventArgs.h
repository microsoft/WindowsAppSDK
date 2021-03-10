#pragma once
#include "PushNotificationActivatedEventArgs.g.h"
#include <mutex>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushNotificationActivatedEventArgs : PushNotificationActivatedEventArgsT<PushNotificationActivatedEventArgs>
    {
        PushNotificationActivatedEventArgs();

        ~PushNotificationActivatedEventArgs();

        PushNotificationActivatedEventArgs(Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask);
        com_array<uint8_t> Payload();
        void GetDeferral();
        void CompleteDeferral(); // heads up
        winrt::event_token Canceled(Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler);
        void Canceled(winrt::event_token const& token) noexcept;
        uint32_t SuspendedCount();
        Windows::ApplicationModel::Activation::ActivationKind Kind();
        Windows::ApplicationModel::Activation::ApplicationExecutionState PreviousExecutionState();
        Windows::ApplicationModel::Activation::SplashScreen SplashScreen();

        // Global accessor from AppLifecycle2
        static winrt::Microsoft::ProjectReunion::PushNotificationActivatedEventArgs GetPushNotificationActivatedEventArgs();

        DWORD s_cookie = 0;

        private:
            Windows::ApplicationModel::Background::IBackgroundTaskInstance m_backgroundTaskInstance;
            Windows::ApplicationModel::Background::BackgroundTaskDeferral m_backgroundTaskDeferral;
            winrt::com_array<uint8_t> m_payload;

            static std::mutex s_mutex;
            static std::unique_lock<std::mutex> s_lock;
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushNotificationActivatedEventArgs : PushNotificationActivatedEventArgsT<PushNotificationActivatedEventArgs, implementation::PushNotificationActivatedEventArgs>
    {
    };
}
