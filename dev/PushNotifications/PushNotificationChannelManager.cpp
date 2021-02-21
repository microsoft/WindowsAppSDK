#include "pch.h"
#include "PushNotificationChannelManager.h"
#include "PushNotificationChannelManager.g.cpp"
#include <winrt/Windows.Networking.Pushnotifications.h>
#include <PushChannelResult.h>
#include <winrt/Windows.Foundation.h>
#include <wrl.h>

using namespace Microsoft::WRL::Wrappers;
namespace PR = ::winrt::Microsoft::ProjectReunion;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::PushChannelResult, Microsoft::ProjectReunion::PushChannelResult > PushNotificationChannelManager::CreatePushNotificationChannelAsync(hstring remoteId)
    {
        auto progress{ co_await winrt::get_progress_token() };

        Windows::Networking::PushNotifications::PushNotificationChannelManager channelManager{};
        winrt::Microsoft::ProjectReunion::PushChannelResult channelResult{ nullptr };

        try
        {
            //channelResult = nullptr;

            auto pushChannel = co_await channelManager.CreatePushNotificationChannelForApplicationAsync();

            if (pushChannel == nullptr)
            {
                channelResult = winrt::make<winrt::Microsoft::ProjectReunion::implementation::PushChannelResult>(nullptr, S_FALSE, ChannelStatus::CompletedFailure);
                progress(winrt::make<winrt::Microsoft::ProjectReunion::implementation::PushChannelResult>(nullptr, S_FALSE, Microsoft::ProjectReunion::ChannelStatus::CompletedFailure));
            }
            else
            {
                channelResult = winrt::make<winrt::Microsoft::ProjectReunion::implementation::PushChannelResult>(pushChannel, S_OK, ChannelStatus::CompletedSuccess);
                progress(winrt::make<winrt::Microsoft::ProjectReunion::implementation::PushChannelResult>(pushChannel, S_OK, Microsoft::ProjectReunion::ChannelStatus::CompletedSuccess));
                
            }
        }
        catch (const hresult& hrException)
        {
            channelResult = winrt::make<winrt::Microsoft::ProjectReunion::implementation::PushChannelResult>(nullptr, hrException , ChannelStatus::CompletedFailure);
            progress(winrt::make<winrt::Microsoft::ProjectReunion::implementation::PushChannelResult>(nullptr, hrException, Microsoft::ProjectReunion::ChannelStatus::CompletedFailure));
        }

        co_return channelResult;
    }
}
