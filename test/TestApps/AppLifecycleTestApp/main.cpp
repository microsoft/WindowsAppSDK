// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <testdef.h>
#include <wil/win32_helpers.h>
#include <iostream>
#include <sddl.h>


using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace winrt::Microsoft::ProjectReunion;
using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;

wil::unique_event CreateTestEvent(const std::wstring& eventName)
{
    bool alreadyExists = false;
    SECURITY_ATTRIBUTES attributes = {};
    wil::unique_hlocal_security_descriptor descriptor;

    // Grant access to world and appcontainer.
    THROW_IF_WIN32_BOOL_FALSE(ConvertStringSecurityDescriptorToSecurityDescriptor(
        L"D:(A;;GA;;;WD)(A;;GA;;;AC)", SDDL_REVISION_1, &descriptor, nullptr));
    attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    attributes.lpSecurityDescriptor = descriptor.get();

    wil::unique_event event;
    event.create(wil::EventOptions::None, eventName.c_str(), &attributes, &alreadyExists);
    return event;
}

bool WaitForEvent(const wil::unique_event& successEvent, const wil::unique_event& failedEvent)
{
    bool result = true;
    HANDLE waitEvents[2] = { successEvent.get(), failedEvent.get() };
    auto waitResult = WaitForMultipleObjects(_countof(waitEvents), waitEvents, FALSE,
        10000);

    // If waitResult == failureEventIndex, it means the remote test process signaled a
    // failure event while we were waiting for a different event.
    auto failureEventIndex = WAIT_OBJECT_0 + 1;
    if (waitResult == failureEventIndex)
    {
        result = false;
    }
    else if (waitResult == WAIT_TIMEOUT)
    {
        result = false;
    }
    else if (waitResult == WAIT_FAILED)
    {
        result = false;
    }

    successEvent.ResetEvent();
    failedEvent.ResetEvent();
    return result;
}

bool IsPackagedProcess()
{
    UINT32 n{};
    return ::GetCurrentPackageFullName(&n, nullptr) == ERROR_INSUFFICIENT_BUFFER;;
}

void SignalPhase(const std::wstring& phaseEventName)
{
    wil::unique_event phaseEvent;
    if (phaseEvent.try_open(phaseEventName.c_str(), EVENT_MODIFY_STATE, false))
    {
        phaseEvent.SetEvent();
    }
}

int main()
{
    std::wstring successEventName = L"ChannelRequest";
    std::wstring failedEventName = L"ChannelRequestFailed";
    wil::unique_event successEvent = CreateTestEvent(successEventName);
    wil::unique_event failedEvent = CreateTestEvent(failedEventName);

    PushNotificationActivationInfo info(
        PushNotificationRegistrationKind::PushTrigger | PushNotificationRegistrationKind::ComActivator,
        winrt::guid("c54044c4-eac7-4c4b-9996-c570a94b9306")); // same clsid as app manifest

    auto token = PushNotificationManager::RegisterActivator(info);

    
    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();
    if (kind == ExtendedActivationKind::Push)
    {
        PushNotificationReceivedEventArgs pushArgs = args.Data().as<PushNotificationReceivedEventArgs>();

        // Call GetDeferral to ensure that code runs in low power
        //auto deferral = pushArgs.GetDeferral();

        auto payload = pushArgs.Payload();

        // Do stuff to process the raw payload
        std::string payloadString(payload.begin(), payload.end());

        std::cout << "Payload (background case): " + payloadString << std::endl;

        // Call Complete on the deferral as good practise: Needed mainly for low power usage
        //deferral.Complete();
        SignalPhase(L"BackgroundActivation");
    }
    else if (kind == ExtendedActivationKind::Launch)
    {

        // SignalPhase(L"BackgroundActivationFailed");
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

                    std::cout << "channelUri: " << winrt::to_string(channelUri.ToString()) << std::endl;
                    std::getchar();
                    auto channelExpiry = result.Channel().ExpirationTime();

                    // Register Push Event for Foreground
                    pushToken = result.Channel().PushReceived([&](const auto&, PushNotificationReceivedEventArgs args)
                        {
                            auto payload = args.Payload();

                            // Do stuff to process the raw payload
                            std::string payloadString(payload.begin(), payload.end());

                            std::cout << "Payload (foreground case): " + payloadString << std::endl;

                            args.Handled(true);
                        });
                }
                else if (result.Status() == PushNotificationChannelStatus::CompletedFailure)
                {
                    LOG_HR_MSG(result.ExtendedError(), "We hit a critical non-retryable error with channel request!");
                }                
            });
    }


    // Unregisters the inproc COM Activator before exiting
    /*PushNotificationManager::UnregisterActivator(token, PushNotificationRegistrationKind::ComActivator);
    std::getchar();*/
    return 0;
}
