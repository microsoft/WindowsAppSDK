#include "pch.h"
#include <testdef.h>
#include <iostream>
#include <wil/win32_helpers.h>
#include "WindowsAppRuntime.Test.AppModel.h"
#include <chrono>

namespace winrt
{
    using namespace winrt::Microsoft::Windows::AppLifecycle;
    using namespace winrt::Windows::ApplicationModel::Activation;
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Microsoft::Windows::ToastNotifications;
    using namespace winrt::Windows::Data::Xml::Dom;
}

bool BackgroundActivationTest() // Activating application for background test.
{
    return true;
}

bool UnregisterBackgroundActivationTest()
{
    winrt::ToastNotificationManager::Default().UnregisterActivator();
    return true;
}

winrt::ToastNotification GetToastNotification()
{
    winrt::hstring xmlPayload{ L"<toast>intrepidToast</toast>" };

    winrt::XmlDocument xmlDocument{};
    xmlDocument.LoadXml(xmlPayload);

    return winrt::ToastNotification(xmlDocument);
}

bool VerifyFailedRegisterActivatorUsingNullClsid()
{
    try
    {
        auto activationInfo = winrt::ToastActivationInfo::CreateFromActivationGuid(winrt::guid(GUID_NULL));

        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo);
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyFailedRegisterActivatorUsingNullClsid_Unpackaged()
{
    try
    {
        auto activationInfo = winrt::ToastActivationInfo::CreateFromActivationGuid(winrt::guid(GUID_NULL));

        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo);
    }
    catch (...)
    {
        return winrt::to_hresult() == E_ILLEGAL_METHOD_CALL;
    }

    return false;
}

bool VerifyFailedRegisterActivatorUsingNullAssets()
{
    try
    {
        auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(nullptr);

        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo);
    }
    catch (...)
    {
        return winrt::to_hresult() == E_ILLEGAL_METHOD_CALL;
    }

    return false;
}

bool VerifyFailedRegisterActivatorUsingNullAssets_Unpackaged()
{
    try
    {
        auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(nullptr);

        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo);
    }
    catch (...)
    {
        return winrt::to_hresult() == E_POINTER;
    }

    return false;
}

bool VerifyRegisterActivatorandUnRegisterActivatorUsingClsid()
{
    winrt::ToastNotificationManager::Default().UnregisterActivator();
    try
    {
        auto activationInfo = winrt::ToastActivationInfo::CreateFromActivationGuid(c_toastComServerId);

        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo);

        winrt::ToastNotificationManager::Default().UnregisterActivator();
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool VerifyRegisterActivatorandUnRegisterActivatorUsingAssets_Unpackaged()
{
    winrt::ToastAssets assets(L"ToastNotificationApp", winrt::Uri{ LR"(C:\Windows\System32\WindowsSecurityIcon.png)" });

    auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets);

    winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo);

    winrt::ToastNotificationManager::Default().UnregisterActivator();

    return true;
}

bool VerifyFailedMultipleRegisterActivatorUsingSameClsid()
{
    try
    {
        auto activationInfo = winrt::ToastActivationInfo::CreateFromActivationGuid(c_toastComServerId);

        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo);

        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo);
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }
    
    return false;
}

bool VerifyFailedMultipleRegisterActivatorUsingSameAssets_Unpackaged()
{
    try
    {
        winrt::ToastAssets assets(L"ToastNotificationApp", winrt::Uri{ LR"(C:\Windows\System32\WindowsSecurityIcon.png)" });

        auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets);

        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo);

        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo);
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyFailedToastAssetsWithEmptyDisplayName_Unpackaged()
{
    try
    {
        winrt::ToastAssets assets(L"", winrt::Uri{LR"(C:\Windows\System32\WindowsSecurityIcon.png)"});

        auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets);
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyFailedToastAssetsWithEmptyIconPath_Unpackaged()
{
    try
    {
        winrt::ToastAssets assets(L"ToastNotificationApp", winrt::Uri{ L""});

        auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets);
    }
    catch (...)
    {
        return winrt::to_hresult() == E_POINTER;
    }

    return false;
}

bool VerifyFailedToastAssetsWithNullIconPath_Unpackaged()
{
    try
    {
        winrt::ToastAssets assets(L"ToastNotificationApp", nullptr);

        auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets);
    }
    catch (...)
    {
        return winrt::to_hresult() == E_POINTER;
    }

    return false;
}

bool VerifyToastSettingEnabled()
{
    return winrt::ToastNotificationManager::Default().Setting() == winrt::ToastNotificationSetting::Enabled;
}

bool VerifyToastPayload()
{
    winrt::hstring xmlPayload{ L"<toast>intrepidToast</toast>" };

    winrt::XmlDocument xmlDocument{};
    xmlDocument.LoadXml(xmlPayload);

    winrt::ToastNotification toast{ xmlDocument };;

    if (toast.Payload() != xmlDocument)
    {
        return false;
    }

    return true;
}

bool VerifyToastTag()
{
    winrt::ToastNotification toast = GetToastNotification();

    if (toast.Tag() != winrt::hstring{ L"" })
    {
        return false;
    }

    winrt::hstring tag{ L"tag" };
    toast.Tag(tag);

    if (toast.Tag() != tag)
    {
        return false;
    }

    return true;
}

bool VerifyToastGroup()
{
    winrt::ToastNotification toast = GetToastNotification();

    if (toast.Group() != winrt::hstring{ L"" })
    {
        return false;
    }

    winrt::hstring group{ L"group" };
    toast.Group(group);

    if (toast.Group() != group)
    {
        return false;
    }

    return true;
}

bool VerifyToastProgressDataFromToast()
{
    /*
    * TODO: Uncomment once ToastProgressData has been implemented

    winrt::ToastNotification toast = GetToastNotification();

    winrt::ToastProgressData progressData{};
    progressData.Status(L"SomeStatus");
    progressData.Title(L"SomeTitle");
    progressData.Value(0.14);
    progressData.ValueStringOverride(L"14%");

    toast.ProgressData(progressData);

    auto progressDataFromToast = toast.ProgressData();
    if (progressDataFromToast != progressData)
    {
        return false;
    }
    */

    return true;
}

bool VerifyToastExpirationTime()
{
    winrt::ToastNotification toast = GetToastNotification();

    if (toast.ExpirationTime() != winrt::DateTime{})
    {
        return false;
    }

    winrt::DateTime expirationTime = winrt::clock::now();
    expirationTime += winrt::TimeSpan(std::chrono::seconds(10));

    toast.ExpirationTime(expirationTime);
    if (toast.ExpirationTime() != expirationTime)
    {
        return false;
    }

    return true;
}

bool VerifyToastPriority()
{
    winrt::ToastNotification toast = GetToastNotification();

    if (toast.Priority() != winrt::ToastPriority::Default)
    {
        return false;
    }

    toast.Priority(winrt::ToastPriority::High);
    if (toast.Priority() != winrt::ToastPriority::High)
    {
        return false;
    }

    return true;
}

bool VerifyToastSuppressDisplay()
{
    winrt::ToastNotification toast = GetToastNotification();

    if (toast.SuppressDisplay())
    {
        return false;
    }

    toast.SuppressDisplay(true);
    if (!toast.SuppressDisplay())
    {
        return false;
    }

    return true;
}

bool VerifyToastExpiresOnReboot()
{
    winrt::ToastNotification toast = GetToastNotification();

    if (toast.ExpiresOnReboot())
    {
        return false;
    }

    toast.ExpiresOnReboot(true);
    if (!toast.ExpiresOnReboot())
    {
        return false;
    }

    return true;
}

std::string unitTestNameFromLaunchArguments(const winrt::ILaunchActivatedEventArgs& launchArgs)
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
        { "BackgroundActivationTest", &BackgroundActivationTest},
        { "UnregisterBackgroundActivationTest", &UnregisterBackgroundActivationTest},
        { "VerifyFailedRegisterActivatorUsingNullClsid", &VerifyFailedRegisterActivatorUsingNullClsid },
        { "VerifyFailedRegisterActivatorUsingNullClsid_Unpackaged", &VerifyFailedRegisterActivatorUsingNullClsid_Unpackaged},
        { "VerifyFailedRegisterActivatorUsingNullAssets", &VerifyFailedRegisterActivatorUsingNullAssets },
        { "VerifyFailedRegisterActivatorUsingNullAssets_Unpackaged", &VerifyFailedRegisterActivatorUsingNullAssets_Unpackaged},
        { "VerifyRegisterActivatorandUnRegisterActivatorUsingClsid", &VerifyRegisterActivatorandUnRegisterActivatorUsingClsid },
        { "VerifyRegisterActivatorandUnRegisterActivatorUsingAssets_Unpackaged", &VerifyRegisterActivatorandUnRegisterActivatorUsingAssets_Unpackaged },
        { "VerifyFailedMultipleRegisterActivatorUsingSameClsid", &VerifyFailedMultipleRegisterActivatorUsingSameClsid },
        { "VerifyFailedMultipleRegisterActivatorUsingSameAssets_Unpackaged", &VerifyFailedMultipleRegisterActivatorUsingSameAssets_Unpackaged },
        { "VerifyFailedToastAssetsWithEmptyDisplayName_Unpackaged", &VerifyFailedToastAssetsWithEmptyDisplayName_Unpackaged },
        { "VerifyFailedToastAssetsWithEmptyIconPath_Unpackaged", &VerifyFailedToastAssetsWithEmptyIconPath_Unpackaged },
        { "VerifyFailedToastAssetsWithNullIconPath_Unpackaged", &VerifyFailedToastAssetsWithNullIconPath_Unpackaged },
        { "VerifyToastSettingEnabled", &VerifyToastSettingEnabled },
        { "VerifyToastPayload", &VerifyToastPayload },
        { "VerifyToastTag", &VerifyToastTag },
        { "VerifyToastGroup", &VerifyToastGroup },
        { "VerifyToastProgressDataFromToast", &VerifyToastProgressDataFromToast },
        { "VerifyToastExpirationTime", &VerifyToastExpirationTime },
        { "VerifyToastPriority", &VerifyToastPriority },
        { "VerifyToastSuppressDisplay", &VerifyToastSuppressDisplay },
        { "VerifyToastExpiresOnReboot", &VerifyToastExpiresOnReboot },
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


int main() try
{
    bool testResult = false;
    auto scope_exit = wil::scope_exit([&] {
        ::Test::Bootstrap::CleanupBootstrap();
        });

    ::Test::Bootstrap::SetupBootstrap();

    if (Test::AppModel::IsPackagedProcess())
    {
        auto activationInfo = winrt::ToastActivationInfo::CreateFromActivationGuid(c_toastComServerId);
        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo);
    }

    auto args = winrt::AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();

    if (kind == winrt::ExtendedActivationKind::Launch)
    {
        auto unitTest = unitTestNameFromLaunchArguments(args.Data().as<winrt::ILaunchActivatedEventArgs>());
        std::cout << unitTest << std::endl;

        testResult = runUnitTest(unitTest);
    }

    return testResult ? 0 : 1; // We want 0 to be success and 1 failure
}
catch (...)
{
    std::cout << winrt::to_string(winrt::to_message()) << std::endl;

    return 1; // in the event of unhandled test crash
}
