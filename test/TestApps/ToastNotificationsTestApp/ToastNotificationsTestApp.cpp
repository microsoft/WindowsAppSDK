#include "pch.h"
#include <testdef.h>
#include <iostream>
#include <wil/win32_helpers.h>
#include "WindowsAppRuntime.Test.AppModel.h"

using namespace winrt;
using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::Windows::ToastNotifications;

bool VerifyFailedRegisterActivatorUsingNullClsid()
{
    try
    {
        auto activationInfo = ToastActivationInfo::CreateFromActivationGuid(winrt::guid(GUID_NULL));

        ToastNotificationManager::Default().RegisterActivator(activationInfo);
    }
    catch (...)
    {
        return to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyFailedRegisterActivatorUsingNullAssets()
{
    try
    {
        auto activationInfo = ToastActivationInfo::CreateFromToastAssets(nullptr);

        ToastNotificationManager::Default().RegisterActivator(activationInfo);
    }
    catch (...)
    {
        return to_hresult() == E_ILLEGAL_METHOD_CALL;
    }

    return false;
}

bool VerifyRegisterActivatorandUnRegisterActivatorUsingClsid()
{

    auto activationInfo = ToastActivationInfo::CreateFromActivationGuid(winrt::guid("1940DBA9-0F64-4F0D-8A4B-5D207B812E61"));

    ToastNotificationManager::Default().RegisterActivator(activationInfo);

    ToastNotificationManager::Default().UnregisterActivator();

    return true;
}

bool VerifyFailedMultipleRegisterActivatorUsingSameClsid()
{
    try
    {
        auto activationInfo = ToastActivationInfo::CreateFromActivationGuid(winrt::guid("1940DBA9-0F64-4F0D-8A4B-5D207B812E61"));

        ToastNotificationManager::Default().RegisterActivator(activationInfo);

        ToastNotificationManager::Default().RegisterActivator(activationInfo);
    }
    catch (...)
    {
        return to_hresult() == E_INVALIDARG;
    }
    
    return false;
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

std::map<std::string, bool(*)()> const& GetSwitchMapping()
{
    static std::map<std::string, bool(*)()> switchMapping = {
        { "VerifyFailedRegisterActivatorUsingNullClsid", &VerifyFailedRegisterActivatorUsingNullClsid },
        { "VerifyFailedRegisterActivatorUsingNullAssets", &VerifyFailedRegisterActivatorUsingNullAssets },
        { "VerifyRegisterActivatorandUnRegisterActivatorUsingClsid", &VerifyRegisterActivatorandUnRegisterActivatorUsingClsid },
        { "VerifyFailedMultipleRegisterActivatorUsingSameClsid", &VerifyFailedMultipleRegisterActivatorUsingSameClsid }
    };
    return switchMapping;
}

bool runUnitTest(std::string unitTest)
{
    auto const& switchMapping = GetSwitchMapping();
    auto it = switchMapping.find(unitTest);
    if (it == switchMapping.end())
    {
        std::cout << "Hello3" << std::endl;
        return false;
    }

    return it->second();
}


int main() try
{
    bool testResult = false;
    auto scope_exit = wil::scope_exit([&] {
        ::Test::Bootstrap::CleanupBootstrap();
        });

    ::Test::Bootstrap::SetupBootstrap();

    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();

    if (kind == ExtendedActivationKind::Launch)
    {
        auto unitTest = unitTestNameFromLaunchArguments(args.Data().as<ILaunchActivatedEventArgs>());
        std::cout << unitTest << std::endl;

        testResult = runUnitTest(unitTest);
    }
 
   // VerifyRegisterActivatorUsingClsid();

    return testResult ? 0 : 1; // We want 0 to be success and 1 failure
}
catch (...)
{
    std::cout << winrt::to_string(winrt::to_message()) << std::endl;
   // getchar();
    return 1; // in the event of unhandled test crash
}
