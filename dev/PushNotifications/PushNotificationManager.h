#pragma once
#include "PushNotificationManager.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    static DWORD s_cookie = 0;

    struct PushNotificationManager
    {
        PushNotificationManager() = default;

        static Microsoft::ProjectReunion::PushNotificationRegistrationToken RegisterActivator(Microsoft::ProjectReunion::PushNotificationActivationInfo const& details);
        static void UnregisterActivator(Microsoft::ProjectReunion::PushNotificationRegistrationToken const& token, Microsoft::ProjectReunion::PushNotificationRegistrationKind const& kind);

        static Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::PushNotificationCreateChannelResult, Microsoft::ProjectReunion::PushNotificationCreateChannelStatus> CreateChannelAsync(winrt::guid remoteId);

    private:
        static bool isChannelRequestRetryable(const winrt::hresult& hrException);

    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushNotificationManager : PushNotificationManagerT<PushNotificationManager, implementation::PushNotificationManager>
    {
    };
}
