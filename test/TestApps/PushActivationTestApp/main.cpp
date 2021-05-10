#include "pch.h"
#include <testdef.h>
#include <iostream>
#include <sstream>
#include <wil/win32_helpers.h>
#include <winrt/Windows.ApplicationModel.Background.h> // we need this for BackgroundTask APIs

using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace winrt::Microsoft::Windows::PushNotifications;
using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Background; // BackgroundTask APIs


enum UnitTest {
    channelRequestUsingNullRemoteId, channelRequestUsingRemoteId, multipleChannelRequestUsingSameRemoteId,
    multipleChannelRequestUsingMultipleRemoteId, threeChannelRequestUsingSameRemoteId, foregroundActivation,
    backgroundActivation
};

static std::map<std::string, UnitTest> switchMapping;

void signalPhase(const std::wstring& phaseEventName)
{
    wil::unique_event phaseEvent;
    if (phaseEvent.try_open(phaseEventName.c_str(), EVENT_MODIFY_STATE, false))
    {
        phaseEvent.SetEvent();
    }
}

void initUnitTestMapping()
{
    switchMapping["ChannelRequestUsingNullRemoteId"] = UnitTest::channelRequestUsingNullRemoteId;
    switchMapping["ChannelRequestUsingRemoteId"] = UnitTest::channelRequestUsingRemoteId;
    switchMapping["MultipleChannelRequestUsingSameRemoteId"] = UnitTest::multipleChannelRequestUsingSameRemoteId;
    switchMapping["MultipleChannelRequestUsingMultipleRemoteId"] = UnitTest::multipleChannelRequestUsingMultipleRemoteId;
    switchMapping["ThreeChannelRequestUsingSameRemoteId"] = UnitTest::threeChannelRequestUsingSameRemoteId;
    switchMapping["ForegroundActivation"] = UnitTest::foregroundActivation;
    switchMapping["BackgroundActivation"] = UnitTest::backgroundActivation;
}

bool ChannelRequestUsingNullRemoteId()
{
    winrt::hresult hr = S_OK;

    try
    {
        auto channelOperation = PushNotificationManager::CreateChannelAsync(GUID_NULL).get();
    }
    catch (...)
    {
        auto channelRequestException = hresult_error(to_hresult());
        hr = channelRequestException.code();
    }

    if (hr == E_INVALIDARG)
        return true;
    else
        return false;
}

bool ChannelRequestUsingRemoteId()
{
    // winrt::guid remoteId { L"a2e4a323-b518-4799-9e80-0b37aeb0d225" };
    wil::unique_handle channelEvent = wil::unique_handle(CreateEvent(nullptr, FALSE, FALSE, nullptr));
    auto hr = S_OK;
    auto channelOperation = PushNotificationManager::CreateChannelAsync(winrt::guid(0xa2e4a323, 0xb518, 0x4799, { 0x9e, 0x80, 0x0b, 0x37, 0xae, 0xb0, 0xd2, 0x25 }));

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


                std::cout << "channelUri: " << winrt::to_string(channelUri.ToString()) << std::endl;

            }
            else if (result.Status() == PushNotificationChannelStatus::CompletedFailure)
            {
                std::cout << "Failed to complete the async complete handler, gracefully cancel the channelOperation" << std::endl;
            }


            SetEvent(channelEvent.get());
        });

    // The maximum amount of time it takes for channel request to be obtained - 16mins
    if (WAIT_OBJECT_0 != WaitForSingleObject(channelEvent.get(), 960000 /* milliseconds */))
    {
        std::cout << "Failed to call/handle the async complete handler, gracefully cancel the channelOperation" << std::endl;
        channelOperation.Cancel();
        hr = ERROR_TIMEOUT;
    }
    else
    {
        std::cout << "Channel complete handler has been completed, safely closing the async operation" << std::endl;
        channelOperation.Close(); // Do not call getresults after this
    }

    if (hr == S_OK)
        return true;
    else
        return false;
}

bool MultipleChannelRequestUsingSameRemoteId()
{
    wil::unique_handle channelEvent = wil::unique_handle(CreateEvent(nullptr, FALSE, FALSE, nullptr));
    auto hr = S_OK;

    auto channelOperation1 = PushNotificationManager::CreateChannelAsync(winrt::guid(0xa2e4a323, 0xb518, 0x4799, { 0x9e, 0x80, 0x0b, 0x37, 0xae, 0xb0, 0xd2, 0x25 }));
    auto channelOperation2 = PushNotificationManager::CreateChannelAsync(winrt::guid(0xa2e4a323, 0xb518, 0x4799, { 0x9e, 0x80, 0x0b, 0x37, 0xae, 0xb0, 0xd2, 0x25 }));

    channelOperation2.Completed(
        [&channelEvent, &hr](
            IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& sender,
            AsyncStatus const /* asyncStatus */)
        {
            auto result = sender.GetResults();
            if (result.Status() == PushNotificationChannelStatus::CompletedSuccess)
            {
                auto channelUri = result.Channel().Uri();
                auto channelExpiry = result.Channel().ExpirationTime();

                std::cout << "channelUri: " << winrt::to_string(channelUri.ToString()) << std::endl;

            }
            else if (result.Status() == PushNotificationChannelStatus::CompletedFailure)
            {
                std::cout << "Failed to complete the async complete handler, gracefully cancel the channelOperation" << std::endl;
                hr = result.ExtendedError();
            }


            SetEvent(channelEvent.get());
        });

    // The maximum amount of time it takes for channel request to be obtained - 16mins
    if (WAIT_OBJECT_0 != WaitForSingleObject(channelEvent.get(), 960000 /* milliseconds */))
    {
        std::cout << "Failed to call/handle the async complete handler, gracefully cancel the channelOperation" << std::endl;
        channelOperation2.Cancel();
        hr = ERROR_TIMEOUT;
    }

    if (hr == WPN_E_OUTSTANDING_CHANNEL_REQUEST)
        return true;
    else
        return false;
}

bool MultipleChannelRequestUsingMultipleRemoteId()
{
    wil::unique_handle channelEvent = wil::unique_handle(CreateEvent(nullptr, FALSE, FALSE, nullptr));
    auto hr = S_OK;

    auto channelOperation1 = PushNotificationManager::CreateChannelAsync(winrt::guid(0xa2e4a323, 0xb518, 0x4799, { 0x9e, 0x80, 0x0b, 0x37, 0xae, 0xb0, 0xd2, 0x25 }));
    auto channelOperation2 = PushNotificationManager::CreateChannelAsync(winrt::guid(0xa2345667, 0xb518, 0x4799, { 0x9e, 0x80, 0x0b, 0x37, 0xae, 0xb0, 0xd2, 0x25 }));

    channelOperation2.Completed(
        [&channelEvent, &hr](
            IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& sender,
            AsyncStatus const /* asyncStatus */)
        {
            auto result = sender.GetResults();
            if (result.Status() == PushNotificationChannelStatus::CompletedSuccess)
            {
                auto channelUri = result.Channel().Uri();
                auto channelExpiry = result.Channel().ExpirationTime();

                std::cout << "channelUri: " << winrt::to_string(channelUri.ToString()) << std::endl;
            }
            else if (result.Status() == PushNotificationChannelStatus::CompletedFailure)
            {
                std::cout << "Failed to complete the async complete handler, gracefully cancel the channelOperation" << std::endl;
                hr = result.ExtendedError();
            }

            SetEvent(channelEvent.get());
        });

    // The maximum amount of time it takes for channel request to be obtained - 16mins
    if (WAIT_OBJECT_0 != WaitForSingleObject(channelEvent.get(), 960000 /* milliseconds */))
    {
        std::cout << "Failed to call/handle the async complete handler, gracefully cancel the channelOperation" << std::endl;
        channelOperation2.Cancel();
        hr = ERROR_TIMEOUT;
    }

    if (hr == WPN_E_OUTSTANDING_CHANNEL_REQUEST)
        return true;
    else
        return false;
}

bool ThreeChannelRequestUsingSameRemoteId()
{
    wil::unique_handle channelEvent2 = wil::unique_handle(CreateEvent(nullptr, FALSE, FALSE, nullptr));
    auto channelOperationResult2 = S_OK;

    wil::unique_handle channelEvent3 = wil::unique_handle(CreateEvent(nullptr, FALSE, FALSE, nullptr));
    auto channelOperationResult3 = S_OK;

    auto channelOperation1 = PushNotificationManager::CreateChannelAsync(winrt::guid(0xa2e4a323, 0xb518, 0x4799, { 0x9e, 0x80, 0x0b, 0x37, 0xae, 0xb0, 0xd2, 0x25 }));
    auto channelOperation2 = PushNotificationManager::CreateChannelAsync(winrt::guid(0xa234a323, 0xb518, 0x4799, { 0x9e, 0x80, 0x0b, 0x37, 0xae, 0xb0, 0xd2, 0x25 }));

    channelOperation2.Completed(
        [&channelEvent2, &channelOperationResult2](
            IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& sender,
            AsyncStatus const /* asyncStatus */)
        {
            auto result = sender.GetResults();
            if (result.Status() == PushNotificationChannelStatus::CompletedSuccess)
            {
                auto channelUri = result.Channel().Uri();
                auto channelExpiry = result.Channel().ExpirationTime();

                std::cout << "channelUri: " << winrt::to_string(channelUri.ToString()) << std::endl;

            }
            else if (result.Status() == PushNotificationChannelStatus::CompletedFailure)
            {
                std::cout << "Failed to complete the async complete handler, gracefully cancel the channelOperation" << std::endl;
                channelOperationResult2 = result.ExtendedError();
            }


            SetEvent(channelEvent2.get());
        });


    auto channelOperation3 = PushNotificationManager::CreateChannelAsync(winrt::guid(0xa234a323, 0xb518, 0x4799, { 0x9e, 0x80, 0x0b, 0x37, 0xae, 0xb0, 0xd2, 0x25 }));

    channelOperation3.Completed(
        [&channelEvent3, &channelOperationResult3](
            IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& sender,
            AsyncStatus const /* asyncStatus */)
        {
            auto result = sender.GetResults();
            if (result.Status() == PushNotificationChannelStatus::CompletedSuccess)
            {
                auto channelUri = result.Channel().Uri();
                auto channelExpiry = result.Channel().ExpirationTime();

                std::cout << "channelUri: " << winrt::to_string(channelUri.ToString()) << std::endl;

            }
            else if (result.Status() == PushNotificationChannelStatus::CompletedFailure)
            {
                std::cout << "Failed to complete the async complete handler, gracefully cancel the channelOperation" << std::endl;
                channelOperationResult3 = result.ExtendedError();
            }

            SetEvent(channelEvent3.get());
        });

    // The maximum amount of time it takes for channel request to be obtained - 16mins
    if (WAIT_OBJECT_0 != WaitForSingleObject(channelEvent2.get(), 960000 /* milliseconds */))
    {
        std::cout << "Failed to call/handle the async complete handler, gracefully cancel the channelOperation" << std::endl;
        channelOperation2.Cancel();
        channelOperationResult2 = ERROR_TIMEOUT;
    }

    // The maximum amount of time it takes for channel request to be obtained - 16mins
    if (WAIT_OBJECT_0 != WaitForSingleObject(channelEvent3.get(), 960000 /* milliseconds */))
    {
        std::cout << "Failed to call/handle the async complete handler, gracefully cancel the channelOperation" << std::endl;
        channelOperation2.Cancel();
        channelOperationResult2 = ERROR_TIMEOUT;
    }

    if ((channelOperationResult2 == WPN_E_OUTSTANDING_CHANNEL_REQUEST) && (channelOperationResult3 == WPN_E_OUTSTANDING_CHANNEL_REQUEST))
        return true;
    else
        return false;
}



bool ForegroundActivation()
{
    return true;
}

bool BackgroundActivation()
{

    return true;
}


bool runUnitTest(std::string unitTest)
{
    switch (switchMapping[unitTest])
    {
    case UnitTest::channelRequestUsingNullRemoteId:
        return ChannelRequestUsingNullRemoteId();

    case UnitTest::channelRequestUsingRemoteId:
        return ChannelRequestUsingRemoteId();

    case UnitTest::multipleChannelRequestUsingSameRemoteId:
        return MultipleChannelRequestUsingSameRemoteId();

    case UnitTest::multipleChannelRequestUsingMultipleRemoteId:
        return MultipleChannelRequestUsingMultipleRemoteId();

    case UnitTest::threeChannelRequestUsingSameRemoteId:
        return ThreeChannelRequestUsingSameRemoteId();

    case UnitTest::foregroundActivation:
        return ForegroundActivation();

    case UnitTest::backgroundActivation:
        return BackgroundActivation();

    default:
        return false;
    }
}

int main()
{
    initUnitTestMapping();
    bool succeeded = true;

    PushNotificationActivationInfo info(
        PushNotificationRegistrationKind::PushTrigger | PushNotificationRegistrationKind::ComActivator,
        winrt::guid("ccd2ae3f-764f-4ae3-be45-9804761b28b2")); // same clsid as app manifest

    auto token = PushNotificationManager::RegisterActivator(info);

    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();

    if (kind == ExtendedActivationKind::Protocol)
    {
        auto protocolArgs = args.Data().as<IProtocolActivatedEventArgs>();
        Uri actualUri = protocolArgs.Uri();
        std::string unitTest = winrt::to_string(actualUri.Host());

        std::cout << unitTest << std::endl;

        // Switch on this variable to run specific components (uri://ComponentToTest)
        auto output = runUnitTest(unitTest);

        if (output)
        {
            // Signal TAEF that protocol was activated and valid.
            signalPhase(c_testProtocolScheme_Packaged);
        }
        else
        {
            // Signal TAEF that the test failed
            signalPhase(c_testFailureEventName);
        }
    }
    else if (kind == ExtendedActivationKind::Push)
    {
        PushNotificationReceivedEventArgs pushArgs = args.Data().as<PushNotificationReceivedEventArgs>();
        auto payload = pushArgs.Payload();
        std::wstring payloadString(payload.begin(), payload.end());
        if (!payloadString.compare(c_rawNotificationPayload))
        {
            signalPhase(c_testProtocolScheme_Packaged);
        }
        else
        {
            // Signal TAEF that the test failed
            signalPhase(c_testFailureEventName);
        }
    }
    return 0;
};
