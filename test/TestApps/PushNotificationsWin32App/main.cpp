#include "pch.h"
#include <iostream>
#include <sstream>
#include <winrt\Windows.Networking.PushNotifications.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Web.Http.Headers.h>

#include <winrt/Windows.ApplicationModel.Background.h> // we need this for BackgroundTask APIs

using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::ProjectReunion;
using namespace Windows::Web::Http;
using namespace winrt::Microsoft::ApplicationModel::Activation; // AppLifecycle Reunion APIs

using namespace winrt::Windows::ApplicationModel::Background; // BackgroundTask APIs

int main()
{
    std::cout << "Press a key to start the test app" << std::endl;
    std::getchar();

    // Register the COM Activator GUID
    PushNotificationActivationInfo info(
        PushNotificationRegistrationKind::PushTrigger | PushNotificationRegistrationKind::ComActivator,
        winrt::guid("BACCFA91-F1DE-4CA2-B80E-90BE66934EC6"));

    // Registers a Push Trigger and sets up an inproc COM Server for Activations
    auto token = PushNotificationManager::RegisterActivator(info);

    // Check to see if the WinMain activation is due to a Push Activator
    // Note: This API is currently not present in Reunion but will be included as part of the AppLifecycle Public API spec.

    //auto activation = AppLifecycle::Activation();
    auto activation = AppLifecycle::GetActivatedEventArgs2(); // mock name for now
    auto kind = activation.Kind();

    if (kind == ExtendedActivationKind::Push)
    {
        auto args = activation.Data().as<PushNotificationReceivedEventArgs>(); // Data is the real name though

        // Call GetDeferral to ensure that code runs in low power
        auto deferral = args.GetDeferral();

        auto payload = args.Payload();

        // Do stuff to process the raw payload
        std::vector<uint8_t> byteVector(payload.begin(), payload.end());
        std::string payloadString(reinterpret_cast<char>(byteVector.data()), byteVector.size());

        std::cout << "Payload (background case): " + payloadString << std::endl;

        // Call Complete on the deferral as good practise: Needed mainly for low power usage
        deferral.Complete();
    }
    else if (kind == ExtendedActivationKind::Launch) // This indicates that the app is launching in the foreground
    {
        // Register the AAD RemoteIdentifier for the App to receive Push
        auto channelOperation = PushNotificationManager::CreateChannelAsync(
            winrt::guid("F80E541E-3606-48FB-935E-118A3C5F41F4"));

        // Setup the inprogress event handler
        channelOperation.Progress(
            [](
                IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& sender,
                PushNotificationCreateChannelStatus const& args)
            {
                if (args.status == PushNotificationChannelStatus::InProgress)
                {
                    // This is basically a noop since it isn't really an error state
                    printf("The first channel request is still in progress! \n");
                }
                else if (args.status == PushNotificationChannelStatus::InProgressRetry)
                {
                    LOG_HR_MSG(
                        args.extendedError,
                        "The channel request is in back-off retry mode because of a retryable error! Expect delays in acquiring it. RetryCount = %d",
                        args.retryCount);
                }
            });

        winrt::event_token pushToken;

        // Setup the completed event handler
        channelOperation.Completed(
            [&](
                IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& sender,
                AsyncStatus const asyncStatus)
            {
                auto result = sender.GetResults();
                if (result.Status() == PushNotificationChannelStatus::CompletedSuccess)
                {
                    auto channelUri = result.Channel().Uri();
                    auto channelExpiry = result.Channel().ExpirationTime();

                    // Register Push Event for Foreground
                    pushToken = result.Channel().PushReceived([&](const auto&, PushNotificationReceivedEventArgs args)
                        {
                            auto payload = args.Payload();

                            // Do stuff to process the raw payload
                            std::vector<uint8_t> byteVector(payload.begin(), payload.end());
                            std::string payloadString(reinterpret_cast<char>(byteVector.data()), byteVector.size());

                            std::cout << "Payload (background case): " + payloadString << std::endl;

                            // Stop the subsequent background activation from launching process again with this payload
                            args.Handled(true);
                        });

                    // Persist the channelUri and Expiry in the App Service for subsequent Push operations
                }
                else if (result.Status() == PushNotificationChannelStatus::CompletedFailure)
                {
                    LOG_HR_MSG(result.ExtendedError(), "We hit a critical non-retryable error with channel request!");
                }
            });

        // Draw window and other foreground UI stuff here

        // Unregister the Push event for Foreground before exiting
        auto result = channelOperation.GetResults();
        if (result.Status() == PushNotificationChannelStatus::CompletedSuccess)
        {
            result.Channel().PushReceived(pushToken);
        }
    }

    // Unregisters the inproc COM Activator before exiting
    PushNotificationManager::UnregisterActivator(token, PushNotificationRegistrationKind::ComActivator);

    std::cout << "Press a key to close the window" << std::endl;
    std::getchar();

    return 0;
};
