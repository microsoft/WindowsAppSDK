#pragma once
#include "PushNotificationManager.g.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushNotificationManager
    {
        PushNotificationManager() = default;

        static Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::PushNotificationCreateChannelResult, Microsoft::ProjectReunion::PushNotificationCreateChannelStatus> CreateChannelAsync(winrt::guid remoteId);

    private:
        static bool isChannelRequestRetryable(const winrt::hresult& hrException);
        static std::vector<winrt::guid> s_remoteIdList;
        static std::mutex s_mutex;
        static std::unique_lock<std::mutex> s_lock;
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushNotificationManager : PushNotificationManagerT<PushNotificationManager, implementation::PushNotificationManager>
    {
    };
}
