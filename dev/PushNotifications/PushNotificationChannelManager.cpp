#include "pch.h"
#include "PushNotificationChannelManager.h"
#include "PushNotificationChannelManager.g.cpp"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::PushChannelResult, Microsoft::ProjectReunion::PushChannelResult> PushNotificationChannelManager::CreateChannelAsync(hstring remoteId)
    {
        throw hresult_not_implemented();
    }
}
