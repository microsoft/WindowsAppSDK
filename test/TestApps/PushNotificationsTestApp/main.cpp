#include "pch.h"
#include <testdef.h>
#include <iostream>
#include <sstream>
#include <wil/win32_helpers.h>
#include <winrt/Windows.ApplicationModel.Background.h> // we need this for BackgroundTask APIs
#include "WindowsAppRuntime.Test.AppModel.h"

using namespace winrt;
using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace winrt::Microsoft::Windows::PushNotifications;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Background; // BackgroundTask APIs
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;

winrt::guid remoteId1(L"a2e4a323-b518-4799-9e80-0b37aeb0d225"); // Generated from ms.portal.azure.com
winrt::guid remoteId2(L"CA1A4AB2-AC1D-4EFC-A132-E5A191CA285A"); // Dummy guid from visual studio guid tool generator

constexpr auto timeout{ std::chrono::seconds(300) };

bool ChannelRequestUsingNullRemoteId()
{
    try
    {
        auto channelOperation = PushNotificationManager::Default().CreateChannelAsync(winrt::guid()).get();
    }
    catch (...)
    {
        return to_hresult() == E_INVALIDARG;
    }
    return false;
}

HRESULT ChannelRequestHelper(IAsyncOperationWithProgress<PushNotificationCreateChannelResult, PushNotificationCreateChannelStatus> const& channelOperation)
{
    if (channelOperation.wait_for(timeout) != AsyncStatus::Completed)
    {
        channelOperation.Cancel();
        return HRESULT_FROM_WIN32(ERROR_TIMEOUT); // timed out or failed
    }

    auto result = channelOperation.GetResults();
    auto status = result.Status();
    if (status != PushNotificationChannelStatus::CompletedSuccess)
    {
        return result.ExtendedError(); // did not produce a channel
    }

    result.Channel().Close();
    return S_OK;
}

bool ChannelRequestUsingRemoteId()
{
    auto channelOperation = PushNotificationManager::Default().CreateChannelAsync(remoteId1);
    auto channelOperationResult = ChannelRequestHelper(channelOperation);

    return channelOperationResult == S_OK;
}

// Verify calling channel close will fail when called twice.
bool MultipleChannelClose()
{
    auto channelOperation = PushNotificationManager::Default().CreateChannelAsync(remoteId1);
    if (channelOperation.wait_for(timeout) != AsyncStatus::Completed)
    {
        channelOperation.Cancel();
        return false; // timed out or failed
    }

    auto result = channelOperation.GetResults();
    auto status = result.Status();
    if (status != PushNotificationChannelStatus::CompletedSuccess)
    {
        return false; // did not produce a channel
    }

    result.Channel().Close();
    try
    {
        result.Channel().Close();
    }
    catch (...)
    {
        return to_hresult() == WPN_E_CHANNEL_CLOSED;
    }
    return false;
}

bool MultipleChannelRequestUsingSameRemoteId()
{

    auto channelOperation1 = PushNotificationManager::Default().CreateChannelAsync(remoteId1);
    auto channelOperation2 = PushNotificationManager::Default().CreateChannelAsync(remoteId1);
    auto channelOperationResult2 = ChannelRequestHelper(channelOperation2);
    auto channelOperationResult1 = ChannelRequestHelper(channelOperation1);

    return channelOperationResult2 == S_OK;
}

bool MultipleChannelRequestUsingMultipleRemoteId()
{
    auto channelOperation1 = PushNotificationManager::Default().CreateChannelAsync(remoteId1);
    auto channelOperation2 = PushNotificationManager::Default().CreateChannelAsync(remoteId2);
    auto channelOperationResult2 = ChannelRequestHelper(channelOperation2);
    auto channelOperationResult1 = ChannelRequestHelper(channelOperation1);

    return channelOperationResult2 == S_OK;
}

bool ActivatorTest()
{
    PushNotificationManager::Default().UnregisterAllActivators();
    try
    {
        if(PushNotificationManager::Default().IsActivatorSupported(PushNotificationRegistrationActivators::PushTrigger | PushNotificationRegistrationActivators::ComActivator))
        {
            PushNotificationActivationInfo info(
                PushNotificationRegistrationActivators::PushTrigger | PushNotificationRegistrationActivators::ComActivator,
                c_fakeComServerId);

            PushNotificationManager::Default().RegisterActivator(info);
            PushNotificationManager::Default().UnregisterActivator(PushNotificationRegistrationActivators::PushTrigger | PushNotificationRegistrationActivators::ComActivator);
        }
        else
        {
            PushNotificationActivationInfo info(PushNotificationRegistrationActivators::ProtocolActivator);

            PushNotificationManager::Default().RegisterActivator(info);
            PushNotificationManager::Default().UnregisterActivator(PushNotificationRegistrationActivators::ProtocolActivator);
        }

    }
    catch (...)
    {
        return false;
    }
    return true;
}

// Verify calling register activator with null PushNotificationActivationInfo is not allowed.
bool RegisterActivatorNullDetails()
{
    PushNotificationManager::Default().UnregisterAllActivators();
    try
    {
        PushNotificationManager::Default().RegisterActivator(nullptr);
    }
    catch (...)
    {
        return to_hresult() == E_INVALIDARG;
    }
    return false;
}

// Verify calling register activator with null clsid is not allowed.
bool RegisterActivatorNullClsid()
{
    PushNotificationManager::Default().UnregisterAllActivators();
    if(PushNotificationManager::Default().IsActivatorSupported(PushNotificationRegistrationActivators::PushTrigger | PushNotificationRegistrationActivators::ComActivator))
    {
        try
        {
            PushNotificationActivationInfo info(
                PushNotificationRegistrationActivators::PushTrigger | PushNotificationRegistrationActivators::ComActivator,
                winrt::guid());

            PushNotificationManager::Default().RegisterActivator(info);
        }
        catch(...)
        {
            return to_hresult() == E_INVALIDARG;
        }
        return false;
    }
    else
    {
        try
        {
            PushNotificationActivationInfo info(
                PushNotificationRegistrationActivators::ProtocolActivator,
                winrt::guid());

            PushNotificationManager::Default().RegisterActivator(info);
        }
        catch(...)
        {
            return false;
        }
        return true;
    }
}

// Verify registering multiple activators is not allowed.
bool MultipleRegisterActivatorTest()
{
    try
    {
        if(PushNotificationManager::Default().IsActivatorSupported(PushNotificationRegistrationActivators::PushTrigger | PushNotificationRegistrationActivators::ComActivator))
        {
            PushNotificationActivationInfo info(
                PushNotificationRegistrationActivators::PushTrigger | PushNotificationRegistrationActivators::ComActivator,
                c_fakeComServerId); // Fake clsid to test multiple activators

            PushNotificationManager::Default().RegisterActivator(info);
        }
        else
        {
            PushNotificationActivationInfo info(PushNotificationRegistrationActivators::ProtocolActivator);
            PushNotificationManager::Default().RegisterActivator(info);
        }
    }
    catch (...)
    {
        return to_hresult() == E_INVALIDARG;
    }
    return false;
}

bool BackgroundActivationTest() // Activating application for background test.
{
    return true;
}

bool VerifyComActivatorSupported()
{
    return PushNotificationManager::Default().IsActivatorSupported(PushNotificationRegistrationActivators::ComActivator);
}

bool VerifyComActivatorNotSupported()
{
    return !PushNotificationManager::Default().IsActivatorSupported(PushNotificationRegistrationActivators::ComActivator);
}

bool VerifyProtocolActivatorSupported()
{
    return PushNotificationManager::Default().IsActivatorSupported(PushNotificationRegistrationActivators::ProtocolActivator);
}

bool VerifyProtocolActivatorNotSupported()
{
    return !PushNotificationManager::Default().IsActivatorSupported(PushNotificationRegistrationActivators::ProtocolActivator);
}

bool VerifyComAndProtocolActivatorNotSupported()
{
    try
    {
        PushNotificationManager::Default().IsActivatorSupported(PushNotificationRegistrationActivators::ComActivator | PushNotificationRegistrationActivators::ProtocolActivator);
    }
    catch (...)
    {
        return to_hresult() == E_INVALIDARG;
    }
    return false;
}

bool VerifyNullActivatorNotSupported()
{
    try
    {
        PushNotificationManager::Default().IsActivatorSupported(PushNotificationRegistrationActivators::Undefined);
    }
    catch (...)
    {
        return to_hresult() == E_INVALIDARG;
    }
    return false;
}

std::map<std::string, bool(*)()> const& GetSwitchMapping()
{
    static std::map<std::string, bool(*)()> switchMapping = {
        { "ChannelRequestUsingNullRemoteId",  &ChannelRequestUsingNullRemoteId },
        { "ChannelRequestUsingRemoteId", &ChannelRequestUsingRemoteId },
        { "MultipleChannelClose", &MultipleChannelClose},
        { "MultipleChannelRequestUsingSameRemoteId", &MultipleChannelRequestUsingSameRemoteId},
        { "MultipleChannelRequestUsingMultipleRemoteId", &MultipleChannelRequestUsingMultipleRemoteId},
        { "RegisterActivatorNullDetails", &RegisterActivatorNullDetails},
        { "RegisterActivatorNullClsid", &RegisterActivatorNullClsid},
        { "ActivatorTest", &ActivatorTest},
        { "MultipleRegisterActivatorTest", &MultipleRegisterActivatorTest},
        { "BackgroundActivationTest", &BackgroundActivationTest},
        { "VerifyComActivatorSupported", &VerifyComActivatorSupported},
        { "VerifyComActivatorNotSupported", &VerifyComActivatorNotSupported },
        { "VerifyProtocolActivatorSupported", &VerifyProtocolActivatorSupported},
        { "VerifyProtocolActivatorNotSupported", &VerifyProtocolActivatorNotSupported },
        { "VerifyComAndProtocolActivatorNotSupported", &VerifyComAndProtocolActivatorNotSupported },
        { "VerifyNullActivatorNotSupported", &VerifyNullActivatorNotSupported }
    };
    return switchMapping;
}

bool runUnitTest(std::string unitTest)
{
    auto const& switchMapping = GetSwitchMapping();
    auto it = switchMapping.find(unitTest);
    if (it == switchMapping.end())
    {
        return false;
    }

    return it->second();
}

std::string unitTestNameFromLaunchArguments(const ILaunchActivatedEventArgs& launchArgs)
{
    std::string unitTestName = to_string(launchArgs.Arguments());
    auto argStart = unitTestName.rfind(" ");
    if (argStart != std::wstring::npos)
    {
        unitTestName = unitTestName.substr(argStart + 1);
    }

    return unitTestName;
}

int main() try
{
    bool testResult = false;
    auto scope_exit = wil::scope_exit([&] {
        PushNotificationManager::Default().UnregisterAllActivators();
        ::Test::Bootstrap::CleanupBootstrap();
    });

    ::Test::Bootstrap::SetupBootstrap();

    // TODO: Register ProtocolActivator for unpackaged applications or Packaged Applications when COM activation is unsupported
    if (PushNotificationManager::Default().IsActivatorSupported(PushNotificationRegistrationActivators::ComActivator))
    {
        PushNotificationActivationInfo info(
            PushNotificationRegistrationActivators::PushTrigger | PushNotificationRegistrationActivators::ComActivator,
            winrt::guid(c_comServerId)); // same clsid as app manifest

        PushNotificationManager::Default().RegisterActivator(info);
    }
    else
    {
        PushNotificationActivationInfo info(PushNotificationRegistrationActivators::ProtocolActivator);
        PushNotificationManager::Default().RegisterActivator(info);
    }
    
    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();

    if (kind == ExtendedActivationKind::Launch)
    {
        auto unitTest = unitTestNameFromLaunchArguments(args.Data().as<ILaunchActivatedEventArgs>());
        std::cout << unitTest << std::endl;

        testResult = runUnitTest(unitTest);
    }
    else if (kind == ExtendedActivationKind::Push)
    {
        PushNotificationReceivedEventArgs pushArgs = args.Data().as<PushNotificationReceivedEventArgs>();
        auto payload = pushArgs.Payload();
        std::wstring payloadString(payload.begin(), payload.end());

        testResult = payloadString == c_rawNotificationPayload;
    }

    return testResult ? 0 : 1; // We want 0 to be success and 1 failure
}
catch (...)
{
    std::cout << winrt::to_string(winrt::to_message()) << std::endl;
    return 1; // in the event of unhandled test crash
}
