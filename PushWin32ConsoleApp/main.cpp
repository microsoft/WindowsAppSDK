#include "pch.h"
#include <iostream>
#include <sstream>
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Web.Http.Headers.h>

using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::ProjectReunion;
using namespace Windows::Web::Http;



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

int main()
{
    // Register activator, always the first thing here
  /*  std::wstring activatorGuid = L"{C54044C4-EAC7-4C4B-9996-C570A94B9305}"; // same as in app manifest
    InProcActivatorDetails details(activatorGuid);
    PushManager::RegisterPushNotificationActivator(details);

    // Check to see if the WinMain activation is due to a Push Activator
    auto args = AppLifecycle2::GetActivatedEventArgs();
    auto kind = args.Kind2();

    if (kind == ActivationKindExtension::Push)
    {
        auto activatedEventArgs = args.ActivatedArgs();
        auto pushArgs = args.as<IPushNotificationActivatedEventArgs>();
        // Call TakeDeferral to ensure that code runs in low power
        pushArgs.GetDeferral();

        auto payload = pushArgs.Payload();

        // Do stuff to process the raw payload
        std::vector<uint8_t> byteVector(payload.begin(), payload.end());
        std::string payloadString(reinterpret_cast<char>(byteVector.data()), byteVector.size());

        std::cout << "Payload (background case): " + payloadString << std::endl;

        // Call CompleteDeferral as good practise: Needed mainly for low power usage
        pushArgs.CompleteDeferral();
    }
    else if (kind == ActivationKindExtension::Launch) // This indicates that the app is launching in the foreground
    {
        // Register an event to Intercept Push payloads
        auto eventToken = details.PushActivated([](const auto&, PushNotificationActivatedEventArgs args)
        {
            // Call TakeDeferral to ensure that code runs in low power
            args.GetDeferral();
            auto payload = args.Payload();

            // Do stuff to process the raw payload
            std::vector<uint8_t> byteVector(payload.begin(), payload.end());
            std::string payloadString(reinterpret_cast<char>(byteVector.data()), byteVector.size());

            std::cout << "Payload (foreground case): " + payloadString << std::endl;

            // Call CompleteDeferral as good practise: Needed mainly for low power usage
            args.CompleteDeferral();
        });
    }
    */
    // Create channel
    guid remoteId{ L"a2e4a323-b518-4799-9e80-0b37aeb0d225" };
    wil::unique_handle channelEvent = wil::unique_handle(CreateEvent(nullptr, FALSE, FALSE, nullptr));

    std::cout << "Channel Request started" << std::endl;

    auto channelOperation = PushNotificationManager::CreateChannelAsync(remoteId);

    channelOperation.Progress(
        [](
            IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& /* sender */,
            PushNotificationCreateChannelStatus const& args)
        {
            if (args.status == PushNotificationChannelStatus::InProgress)
            {
                // This is basically a noop since it isn't really an error state
                std::cout << "The channel request is in progress " << args.extendedError << std::endl;
            }
            else if (args.status == PushNotificationChannelStatus::InProgressRetry)
            {
                std::cout << "The channel request is in back-off retry mode because of a retryable error code: " << args.extendedError << " Expect delays in acquiring it" << std::endl;
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
                auto channelUri = result.Channel().Uri();
                auto channelExpiry = result.Channel().ExpirationTime();

                //sendRequestToServer(channelUri);
                std::cout << "channelUri: " << winrt::to_string(channelUri.ToString()) << std::endl;
                // Persist the channelUri and Expiry in the App Service
            }
            else if (result.Status() == PushNotificationChannelStatus::CompletedFailure)
            {
                std::cout << "Failed to complete the async complete handler, gracefully cancel the channelOperation" << std::endl;
            }

            // Send the channel request to server
            SetEvent(channelEvent.get());
        });

    // The maximum amount of time it takes for channel request to be obtained - 16mins
    if (WAIT_OBJECT_0 != WaitForSingleObject(channelEvent.get(), 960000 /* milliseconds */))
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
