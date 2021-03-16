#include "pch.h"
#include <iostream>
#include <sstream>
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt/Windows.Foundation.h>
/*
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Web.Http.Headers.h> */

using namespace winrt;
/*using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams; */
using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::ProjectReunion;
//using namespace Windows::Web::Http;


/*
std::wstring BuildNotificationPayload(std::wstring channel)
{
    std::wstring channelUri = L"\"ChannelUri\":\"" + channel + L"\"";
    std::wstring x_wns_type = L"\"X_WNS_Type\": \"wns/raw\"";
    std::wstring contentType = L"\"Content_Type\": \"application/octet-stream\"";
    std::wstring payload = L"\"Payload\": \"<toast></toast>\"";
    std::wstring delay = L"\"Delay\": \"false\"";
    return { L"{" + channelUri + L"," + x_wns_type + L"," + contentType + L"," + payload + L"," + delay + L"}" };
}

void sendRequestToServer(winrt::hstring channel)
{
    HttpResponseMessage httpResponseMessage;
    std::wstring httpResponseBody;
    try {
        // Construct the HttpClient and Uri. This endpoint is for test purposes only.
        HttpClient httpClient;
        Uri requestUri{ L"http://localhost:7071/api/PostPushNotification" };

        // Construct the JSON to post.
        HttpStringContent jsonContent(
            BuildNotificationPayload(channel.c_str()),
            UnicodeEncoding::Utf8,
            L"application/json");

        // Post the JSON, and wait for a response.
        httpResponseMessage = httpClient.PostAsync(
            requestUri,
            jsonContent).get();

        // Make sure the post succeeded, and write out the response.
        httpResponseMessage.EnsureSuccessStatusCode();
        httpResponseBody = httpResponseMessage.Content().ReadAsStringAsync().get();
        std::wcout << httpResponseBody.c_str() << std::endl;
    }
    catch (winrt::hresult_error const& ex)
    {
        std::wcout << ex.message().c_str() << std::endl;
    }
}
*/

int main()
{
    // Create channel
    guid remoteId{ L"a2e4a323-b518-4799-9e80-0b37aeb0d225" };
    wil::unique_handle channelEvent = wil::unique_handle(CreateEvent(nullptr, FALSE, FALSE, nullptr));

    std::cout << "Channel Request started" << std::endl;

    try {
        auto channelOperation = PushNotificationManager::CreateChannelAsync(remoteId);

        channelOperation.Progress(
            [](
                IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& /* sender */,
                PushNotificationCreateChannelStatus const& args)
            {
                if (args.status == PushNotificationChannelStatus::InProgress)
                {
                    // This is basically a noop since it isn't really an error state
                    std::cout << "The first channel request is in progress! \n" << std::endl;
                }
                else if (args.status == PushNotificationChannelStatus::InProgressRetry)
                {
                    std::cout <<
                        args.extendedError <<
                        " The channel request is in back-off retry mode because of a retryable error! Expect delays in acquiring it. RetryCount = " <<
                        args.retryCount;
                }
            });

        // Setup the completed event handler
        channelOperation.Completed(
            [&channelEvent](
                IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& sender,
                AsyncStatus const /* asyncStatus */)
            {
                auto result = sender.GetResults();
                if (result.Status() == PushNotificationChannelStatus::CompletedSuccess)
                {
                    //  auto channelUri = result.Channel().Uri();
                    //  auto channelExpiry = result.Channel().ExpirationTime();

                      // Persist the channelUri and Expiry in the App Service for subsequent Push operations
                    std::cout << "ChannelUri obtained" << std::endl;
                }
                else if (result.Status() == PushNotificationChannelStatus::CompletedFailure)
                {
                    std::cout << result.ExtendedError() << "We hit a critical non-retryable error with channel request!" << std::endl;
                }

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

    }
    catch (...)
    {
        auto ex = hresult_error(to_hresult(), take_ownership_from_abi);

        std::cout << "Hello! Thanks. " << ex.code() << std::endl;
    }

    std::cout << "Press a key to close the window" << std::endl;

    std::getchar();

    return 0;
};
