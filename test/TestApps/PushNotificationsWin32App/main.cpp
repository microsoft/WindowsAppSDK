#include "pch.h"
#include <testdef.h>
#include <iostream>
#include <sstream>
#include <regex>
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
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace Windows::Web::Http;

using namespace winrt::Windows::ApplicationModel::Background; // BackgroundTask APIs

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
    switchMapping["channelRequest"] = ChannelRequest;
    switchMapping["foregroundTest"] = ForegroundTest;
    switchMapping["backgroundTest"] = BackgroundTest;
}

void startChannelRequestTest()
{
    std::cout << "Channel Request Test Start!" << std::endl;
}

void startForegroundActivationTest()
{
    std::cout << "Foreground Activation Test Start!" << std::endl;

    PushNotificationActivationInfo info(
        PushNotificationRegistrationKind::PushTrigger | PushNotificationRegistrationKind::ComActivator,
        winrt::guid("c54044c4-eac7-4c4b-9996-c570a94b9306")); // same clsid as app manifest

    // Registers a Push Trigger and sets up an inproc COM Server for Activations
    auto token = PushNotificationManager::RegisterActivator(info);

    auto activation = AppLifecycle::GetActivatedEventArgs2(); // mock name for now
    auto kind = activation.Kind();

    if (kind == ExtendedActivationKind::Push)
    {
        auto args = activation.Data().as<PushNotificationReceivedEventArgs>(); // Data is the real name though

        // Call GetDeferral to ensure that code runs in low power
        auto deferral = args.GetDeferral();

        auto payload = args.Payload();

        // Do stuff to process the raw payload
        std::string payloadString(payload.begin(), payload.end());

        std::cout << "Payload (background case): " + payloadString << std::endl;

        // Call Complete on the deferral as good practise: Needed mainly for low power usage
        deferral.Complete();
    }
}

void startBackgroundActivationTest()
{
    std::cout << "Background Activation Test Start!" << std::endl;
}

void runUnitTest(std::string unitTest)
{

    switch (switchMapping[unitTest])
    {
        case ChannelRequest:
            startChannelRequestTest();
            break;
        case ForegroundTest:
            startForegroundActivationTest();
            break;
        case BackgroundTest:
            startBackgroundActivationTest();
            break;
    }
}

int main()
{
    initUnitTestMapping();
    bool succeeded = true;
    auto args = AppLifecycle::GetActivatedEventArgs(); // mock name for now
    auto kind = args.Kind();

    auto activation = AppLifecycle::GetActivatedEventArgs2(); // mock name for now
    auto kind2 = activation.Kind();
    if (kind == ActivationKind::Protocol)
    {
        auto protocolArgs = args.as<IProtocolActivatedEventArgs>();
        Uri actualUri = protocolArgs.Uri();
        std::string unitTest = winrt::to_string(actualUri.Host());

        // Switch on this variable to run specific components (uri://ComponentToTest)
        runUnitTest(unitTest);

        // Signal TAEF that protocol was activated and valid.
        signalPhase(c_testProtocolScheme_Packaged);
        succeeded = true;
    }

    if (!succeeded)
    {
        // Signal TAEF that the test failed
        signalPhase(c_testFailureEventName);
    }
    std::getchar();
    return 0;
};
