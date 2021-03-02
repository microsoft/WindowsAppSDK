#include "pch.h"
#include <iostream>
#include <winrt\Windows.Networking.PushNotifications.h>

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::ProjectReunion;

int main()
{
    guid remoteId{ L"938c922a-0361-4eab-addb-29c74671c2bf" };
    wil::unique_handle channelEvent = wil::unique_handle(CreateEvent(nullptr, FALSE, FALSE, nullptr));

    std::cout << "Channel Request started" << std::endl;

    auto channelOperation = PushManager::CreateChannelAsync(remoteId);

    channelOperation.Progress(
        [&channelEvent](
            IAsyncOperationWithProgress<ChannelResult, ChannelResult> const& /* sender */,
            ChannelResult const& args)
        {
            if (args.Status() == ChannelStatus::InProgress)
            {
                // This is basically a noop since it isn't really an error state
                printf("The first channel request is still in progress! \n");
            }
            else if (args.Status() == ChannelStatus::InProgressRetry)
            {
                LOG_HR_MSG(args.ExtendedError(), "The channel request is in back-off retry mode because of a retryable error! Expect delays in acquiring it.");
            }
    });

    // Setup the completed event handler
    channelOperation.Completed(
        [&channelEvent](
            IAsyncOperationWithProgress<ChannelResult, ChannelResult> const& sender,
            AsyncStatus const /* asyncStatus */)
        {
            auto result = sender.GetResults();
            if (result.Status() == ChannelStatus::CompletedSuccess)
            {
                auto channelUri = result.Channel().Uri();
                auto channelExpiry = result.Channel().ExpirationTime();

                std::cout << "channelUri: " << winrt::to_string(channelUri) << std::endl;
                // Persist the channelUri and Expiry in the App Service
            }
            else if (result.Status() == ChannelStatus::CompletedFailure)
            {
                std::cout << "Failed to complete the async complete handler, gracefully cancel the channelOperation" << std::endl;
            }

            // Send the channel request to server

            SetEvent(channelEvent.get());
        });

    // Handle channelOperation gracefully - if main goes out of context

    if (WAIT_OBJECT_0 != WaitForSingleObject(channelEvent.get(), 300000))
    {
        std::cout << "Failed to call/handle the async complete handler, gracefully cancel the channelOperation" << std::endl;
        channelOperation.Cancel();
    }
    else
    {
        std::cout << "Channel complete handler has been completed, safely closing the async operation" << std::endl;
        channelOperation.Close(); // Do not call getresults after this
    }

    std::cout << "Press a key to close the window" << std::endl;

    std::getchar();

    return 0;
};
