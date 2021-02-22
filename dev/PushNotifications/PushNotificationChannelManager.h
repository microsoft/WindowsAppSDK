#pragma once
#include "PushNotificationChannelManager.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushNotificationChannelManager
    {
        PushNotificationChannelManager() = default;

        static Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::PushChannelResult, Microsoft::ProjectReunion::PushChannelResult> CreateChannelAsync(hstring remoteId);
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushNotificationChannelManager : PushNotificationChannelManagerT<PushNotificationChannelManager, implementation::PushNotificationChannelManager>
    {
    };
}
