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
    using namespace winrt::Windows::Foundation;
}

winrt::ToastNotification CreateToastNotification(winrt::hstring message)
{
    winrt::hstring xmlPayload{ L"<toast>" + message + L"</toast>" };

    winrt::XmlDocument xmlDocument{};
    xmlDocument.LoadXml(xmlPayload);

    return winrt::ToastNotification(xmlDocument);
}

winrt::ToastNotification CreateToastNotification()
{
    return CreateToastNotification(L"intrepidToast");
}

void EnsureNoActiveToasts()
{
    auto removeAllAsync = winrt::ToastNotificationManager::Default().RemoveAllAsync();
    if (removeAllAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        removeAllAsync.Cancel();
        THROW_HR_MSG(E_FAIL, "Failed to remove all active toasts");
    }
}

bool VerifyToastIsActive(UINT32 expectedToastId)
{
    auto retrieveNotificationsAsync{ winrt::ToastNotificationManager::Default().GetAllAsync() };
    if (retrieveNotificationsAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        retrieveNotificationsAsync.Cancel();
        return false;
    }

    auto notifications = retrieveNotificationsAsync.get();

    bool found{ false };
    for (auto notification : notifications)
    {
        if (notification.ToastId() == expectedToastId)
        {
            found = true;
            break;
        }
    }

    return found;
}

bool VerifyProgressData(const winrt::ToastProgressData& expected, const winrt::ToastProgressData& actual)
{
    if (expected.Status() != actual.Status())
    {
        return false;
    }

    if (expected.Title() != actual.Title())
    {
        return false;
    }

    if (expected.Value() != actual.Value())
    {
        return false;
    }

    if (expected.ValueStringOverride() != actual.ValueStringOverride())
    {
        return false;
    }

    return true;
}

enum class ExpectedTransientProperties { EQUAL, DEFAULT, UNKNOWN };
bool VerifyToastNotificationIsValid(const winrt::ToastNotification& expected, const winrt::ToastNotification& actual, ExpectedTransientProperties expectedTransientProperties = ExpectedTransientProperties::EQUAL)
{
    if (expected.Tag() != actual.Tag())
    {
        return false;
    }

    if (expected.Group() != actual.Group())
    {
        return false;
    }

    if (expected.ToastId() != actual.ToastId())
    {
        return false;
    }

    auto expectedPayload = expected.Payload().GetElementsByTagName(L"toast").GetAt(0).GetXml();
    auto actualPayload = actual.Payload().GetElementsByTagName(L"toast").GetAt(0).GetXml();
    if (expectedPayload != actualPayload)
    {
        return false;
    }

    if (!VerifyProgressData(expected.ProgressData(), actual.ProgressData()))
    {
        return false;
    }

    if (expected.ExpirationTime() > actual.ExpirationTime())
    {
        // External factors, like setting ProgressData can bump the expiration time.
        // We're happy as long as the actual expiration time is equal or larger than the expected
        return false;
    }

    if (expected.ExpiresOnReboot() != actual.ExpiresOnReboot())
    {
        return false;
    }

    switch (expectedTransientProperties)
    {
    case ExpectedTransientProperties::EQUAL:
        if (expected.Priority() != actual.Priority())
        {
            return false;
        }

        if (expected.SuppressDisplay() != actual.SuppressDisplay())
        {
            return false;
        }
        break;

    case ExpectedTransientProperties::DEFAULT:
        if (winrt::Microsoft::Windows::ToastNotifications::ToastPriority::Default != actual.Priority())
        {
            return false;
        }

        if (false != actual.SuppressDisplay())
        {
            return false;
        }
        break;

    case ExpectedTransientProperties::UNKNOWN:
        // Nothing to validate here.
        break;

    default:
        // Unexpected selection
        return false;
    }

    return true;
}

winrt::ToastProgressData GetToastProgressData(std::wstring const& status, std::wstring const& title, double const& progressValue, std::wstring const& progressValueString)
{
    winrt::ToastProgressData progressData{};
    progressData.Status(status);
    progressData.Title(title);
    progressData.Value(progressValue);
    progressData.ValueStringOverride(progressValueString);

    return progressData;
}

bool ProgressResultOperationHelper(winrt::IAsyncOperation<winrt::ToastProgressResult> progressResultOperation, winrt::ToastProgressResult progressResult)
{
    if (progressResultOperation.wait_for(std::chrono::seconds(2)) != winrt::AsyncStatus::Completed)
    {
        progressResultOperation.Cancel();
        return false; // timed out or failed
    }

    return progressResultOperation.GetResults() == progressResult;
}

bool PostToastHelper(std::wstring const& tag, std::wstring const& group)
{
    winrt::ToastNotification toast{ CreateToastNotification() };

    toast.Tag(tag.c_str());
    toast.Group(group.c_str());

    winrt::ToastNotificationManager::Default().ShowToast(toast);

    if (toast.ToastId() == 0)
    {
        return false;
    }

    return true;
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

bool VerifyFailedRegisterActivatorUsingNullClsid()
{
    try
    {
        auto activationInfo = winrt::ToastActivationInfo::CreateFromActivationGuid(winrt::guid(GUID_NULL)); // The exception gets thrown here

        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo); // This doesn't get called
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
        auto activationInfo = winrt::ToastActivationInfo::CreateFromActivationGuid(winrt::guid(GUID_NULL)); // The exception gets thrown here

        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo); // This doesn't get called
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
        auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(nullptr); // The exception gets thrown here

        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo); // This doesn't get called
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
        auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(nullptr); // The exception gets thrown here

        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo); // This doesn't get called
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
    auto activationInfo = winrt::ToastActivationInfo::CreateFromActivationGuid(c_toastComServerId);

    try
    {
        winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo); // This is the call that actually throws

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
    winrt::ToastAssets assets(L"ToastNotificationApp", winrt::Uri{ LR"(C:\Windows\System32\WindowsSecurityIcon.png)" });

    auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets);

    winrt::ToastNotificationManager::Default().RegisterActivator(activationInfo);

    try
    {
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
    winrt::ToastAssets assets(L"", winrt::Uri{ LR"(C:\Windows\System32\WindowsSecurityIcon.png)" });

    try
    {
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
        winrt::ToastAssets assets(L"ToastNotificationApp", winrt::Uri{ L"" }); // The exception gets thrown here

        auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets); // This doesn't get called
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
        winrt::ToastAssets assets(L"ToastNotificationApp", nullptr); // The exception gets thrown here

        auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets); // This doesn't get called
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
    winrt::ToastNotification toast{ CreateToastNotification() };

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
    winrt::ToastNotification toast{ CreateToastNotification() };

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
    winrt::ToastNotification toast{ CreateToastNotification() };

    winrt::ToastProgressData progressData{};
    progressData.Status(L"SomeStatus");
    progressData.Title(L"SomeTitle");
    progressData.Value(0.14);
    progressData.ValueStringOverride(L"14%");

    toast.ProgressData(progressData);

    auto progressDataFromToast = toast.ProgressData();
    if (progressDataFromToast.Status() != L"SomeStatus")
    {
        return false;
    }

    if (progressDataFromToast.Title() != L"SomeTitle")
    {
        return false;
    }

    if (progressDataFromToast.Value() != 0.14)
    {
        return false;
    }

    if (progressDataFromToast.ValueStringOverride() != L"14%")
    {
        return false;
    }

    return true;
}

bool VerifyToastExpirationTime()
{
    winrt::ToastNotification toast{ CreateToastNotification() };

    if (toast.ExpirationTime() != winrt::DateTime{})
    {
        return false;
    }

    winrt::DateTime expirationTime{ winrt::clock::now() };
    expirationTime += winrt::TimeSpan{ std::chrono::seconds(10) };

    toast.ExpirationTime(expirationTime);
    if (toast.ExpirationTime() != expirationTime)
    {
        return false;
    }

    return true;
}

bool VerifyToastPriority()
{
    winrt::ToastNotification toast{ CreateToastNotification() };

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
    winrt::ToastNotification toast{ CreateToastNotification() };

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
    winrt::ToastNotification toast{ CreateToastNotification() };

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

bool VerifyShowToast()
{
    EnsureNoActiveToasts();

    // Registration happens in main()
    winrt::ToastNotification toast{ CreateToastNotification() };

    auto toastNotificationManager = winrt::ToastNotificationManager::Default();
    toastNotificationManager.ShowToast(toast);

    if (toast.ToastId() == 0)
    {
        return false;
    }

    return VerifyToastIsActive(toast.ToastId());
}

bool VerifyShowToast_Unpackaged()
{
    winrt::ToastAssets assets(L"ToastNotificationApp", winrt::Uri{ LR"(C:\Windows\System32\WindowsSecurityIcon.png)" });
    auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets);

    auto toastNotificationManager = winrt::ToastNotificationManager::Default();
    toastNotificationManager.RegisterActivator(activationInfo);

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterActivator();
        });

    EnsureNoActiveToasts();

    winrt::ToastNotification toast{ CreateToastNotification() };

    toastNotificationManager.ShowToast(toast);

    if (toast.ToastId() == 0)
    {
        return false;
    }

    return VerifyToastIsActive(toast.ToastId());
}

bool VerifyGetAllAsyncReportsProgressData()
{
    EnsureNoActiveToasts();

    auto toastNotificationManager = winrt::ToastNotificationManager::Default();

    winrt::ToastNotification toast{ CreateToastNotification() };
    toast.Tag(L"Tag");
    toast.Group(L"Group");
    toastNotificationManager.ShowToast(toast);

    winrt::ToastProgressData progressData = GetToastProgressData(L"SomeStatus", L"SomeTitle", 0.14, L"14%");
    auto progressResultOperation = toastNotificationManager.UpdateToastProgressDataAsync(progressData, L"Tag", L"Group");
    if (!ProgressResultOperationHelper(progressResultOperation, winrt::ToastProgressResult::Succeeded))
    {
        return false;
    }

    auto getNotificationsAsync = toastNotificationManager.GetAllAsync();
    if (getNotificationsAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        getNotificationsAsync.Cancel();
        return false;
    }

    auto notifications = getNotificationsAsync.GetResults();

    if (notifications.Size() != 1)
    {
        return false;
    }

    auto actual = notifications.GetAt(0);

    return VerifyToastNotificationIsValid(toast, actual, ExpectedTransientProperties::DEFAULT);
}

bool VerifyUpdateToastProgressDataUsingValidTagAndValidGroup()
{
    // Registration happens in main()
    PostToastHelper(L"PTag", L"PGroup");

    winrt::ToastProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%");

    auto progressResultOperation = winrt::ToastNotificationManager::Default().UpdateToastProgressDataAsync(progressData, L"PTag", L"PGroup");
    return ProgressResultOperationHelper(progressResultOperation, winrt::ToastProgressResult::Succeeded);
}

bool VerifyUpdateToastProgressDataUsingValidTagAndValidGroup_Unpackaged()
{
    winrt::ToastAssets assets(L"ToastNotificationApp", winrt::Uri{ LR"(C:\Windows\System32\WindowsSecurityIcon.png)" });
    auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets);

    auto toastNotificationManager{ winrt::ToastNotificationManager::Default() };

    toastNotificationManager.RegisterActivator(activationInfo);

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterActivator();
        });

    PostToastHelper(L"Tag", L"Group");

    winrt::ToastProgressData progressData = GetToastProgressData(L"SomeStatus", L"SomeTitle", 0.14, L"14%");

    auto progressResultOperation = toastNotificationManager.UpdateToastProgressDataAsync(progressData, L"Tag", L"Group");
    return ProgressResultOperationHelper(progressResultOperation, winrt::ToastProgressResult::Succeeded);
}

bool VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup()
{
    // Registration happens in main()
    PostToastHelper(L"PTag", L"");

    winrt::ToastProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%");

    auto progressResultOperation = winrt::ToastNotificationManager::Default().UpdateToastProgressDataAsync(progressData, L"PTag");
    return ProgressResultOperationHelper(progressResultOperation, winrt::ToastProgressResult::Succeeded);
}

bool VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup_Unpackaged()
{
    winrt::ToastAssets assets(L"ToastNotificationApp", winrt::Uri{ LR"(C:\Windows\System32\WindowsSecurityIcon.png)" });
    auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets);

    auto toastNotificationManager{ winrt::ToastNotificationManager::Default() };

    toastNotificationManager.RegisterActivator(activationInfo);

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterActivator();
        });

    PostToastHelper(L"Tag", L"");

    winrt::ToastProgressData progressData = GetToastProgressData(L"SomeStatus", L"SomeTitle", 0.14, L"14%");

    auto progressResultOperation = toastNotificationManager.UpdateToastProgressDataAsync(progressData, L"Tag");
    return ProgressResultOperationHelper(progressResultOperation, winrt::ToastProgressResult::Succeeded);
}

bool VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup()
{
    // Registration happens in main()
    PostToastHelper(L"PTag", L"PGroup");

    winrt::ToastProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%");

    auto progressResultOperation = winrt::ToastNotificationManager::Default().UpdateToastProgressDataAsync(progressData, L"NonExistentTag", L"NonExistentGroup");
    return ProgressResultOperationHelper(progressResultOperation, winrt::ToastProgressResult::NotificationNotFound);
}

bool VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup_Unpackaged()
{
    winrt::ToastAssets assets(L"ToastNotificationApp", winrt::Uri{ LR"(C:\Windows\System32\WindowsSecurityIcon.png)" });
    auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets);

    auto toastNotificationManager{ winrt::ToastNotificationManager::Default() };

    toastNotificationManager.RegisterActivator(activationInfo);

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterActivator();
        });

    PostToastHelper(L"Tag", L"Group");

    winrt::ToastProgressData progressData = GetToastProgressData(L"SomeStatus", L"SomeTitle", 0.14, L"14%");

    auto progressResultOperation = toastNotificationManager.UpdateToastProgressDataAsync(progressData, L"NonExistentTag", L"NonExistentGroup");
    return ProgressResultOperationHelper(progressResultOperation, winrt::ToastProgressResult::NotificationNotFound);
}

bool VerifyFailedUpdateNotificationDataWithoutPostToast()
{
    // Registration happens in main()
    winrt::ToastProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%");

    auto progressResultOperation = winrt::ToastNotificationManager::Default().UpdateToastProgressDataAsync(progressData, L"Tag", L"Group");
    return ProgressResultOperationHelper(progressResultOperation, winrt::ToastProgressResult::NotificationNotFound);
}

bool VerifyFailedUpdateNotificationDataWithoutPostToast_Unpackaged()
{
    winrt::ToastAssets assets(L"ToastNotificationApp", winrt::Uri{ LR"(C:\Windows\System32\WindowsSecurityIcon.png)" });
    auto activationInfo = winrt::ToastActivationInfo::CreateFromToastAssets(assets);

    auto toastNotificationManager{ winrt::ToastNotificationManager::Default() };

    toastNotificationManager.RegisterActivator(activationInfo);

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterActivator();
        });

    winrt::ToastProgressData progressData = GetToastProgressData(L"SomeStatus", L"SomeTitle", 0.14, L"14%");
    auto progressResultOperation = toastNotificationManager.UpdateToastProgressDataAsync(progressData, L"SomeRandomTag", L"SomeRandomGroup");
    return ProgressResultOperationHelper(progressResultOperation, winrt::ToastProgressResult::NotificationNotFound);
}

bool VerifyUpdateToastProgressDataUsingEmptyTagAndValidGroup()
{
    try
    {
        winrt::ToastProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%");

        auto progressResultOperation = winrt::ToastNotificationManager::Default().UpdateToastProgressDataAsync(progressData, L"", L"Group").get();
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup()
{
    try
    {
        winrt::ToastProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%");

        auto progressResultOperation = winrt::ToastNotificationManager::Default().UpdateToastProgressDataAsync(progressData, L"", L"").get();
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyGetAllAsyncWithZeroActiveToast()
{
    EnsureNoActiveToasts();

    auto toastNotificationManager = winrt::ToastNotificationManager::Default();

    auto getAllAsync = toastNotificationManager.GetAllAsync();
    if (getAllAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Error)
    {
        getAllAsync.Cancel();
        return false;
    }

    return true;
}

bool VerifyGetAllAsyncWithOneActiveToast()
{
    EnsureNoActiveToasts();

    winrt::ToastNotification toast{ CreateToastNotification(L"MyOwnLittleToast") };
    toast.Tag(L"aDifferentTag");
    toast.Group(L"aDifferentGroup");
    winrt::DateTime expirationTime{ winrt::clock::now() };
    expirationTime += winrt::TimeSpan{ std::chrono::seconds(10) };
    toast.ExpirationTime(expirationTime);
    toast.ExpiresOnReboot(false); // ELx - Setting this to true fails, investigating
    toast.Priority(winrt::Microsoft::Windows::ToastNotifications::ToastPriority::High);
    toast.SuppressDisplay(true);

    auto toastNotificationManager = winrt::ToastNotificationManager::Default();

    toastNotificationManager.ShowToast(toast);

    auto retrieveNotificationsAsync = toastNotificationManager.GetAllAsync();
    if (retrieveNotificationsAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        retrieveNotificationsAsync.Cancel();
        return false;
    }

    auto notifications = retrieveNotificationsAsync.get();

    auto size = notifications.Size();
    if (size != 1)
    {
        return false;
    }

    auto actual = notifications.GetAt(0);
    return VerifyToastNotificationIsValid(toast, actual, ExpectedTransientProperties::DEFAULT);
}

bool VerifyGetAllAsyncWithMultipleActiveToasts()
{
    EnsureNoActiveToasts();

    auto toastNotificationManager = winrt::ToastNotificationManager::Default();

    winrt::ToastNotification toast1{ CreateToastNotification() };
    toastNotificationManager.ShowToast(toast1);

    winrt::ToastNotification toast2{ CreateToastNotification() };
    toastNotificationManager.ShowToast(toast2);

    winrt::ToastNotification toast3{ CreateToastNotification() };
    toastNotificationManager.ShowToast(toast3);

    auto getNotificationsAsync = toastNotificationManager.GetAllAsync();
    if (getNotificationsAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        getNotificationsAsync.Cancel();
        return false;
    }

    auto notifications = getNotificationsAsync.get();

    if (notifications.Size() != 3)
    {
        return false;
    }

    auto actual = notifications.GetAt(0);
    auto payload = actual.Payload().GetElementsByTagName(L"toast").GetAt(0).GetXml();

    if (wcscmp(L"<toast>intrepidToast</toast>", payload.c_str()) != 0)
    {
        return false;
    }

    return true;
}

bool VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier()
{
    try
    {
        auto removeToastAsync{ winrt::ToastNotificationManager::Default().RemoveWithIdentifierAsync(0) };
        if (removeToastAsync.wait_for(std::chrono::seconds(300)) == winrt::Windows::Foundation::AsyncStatus::Error)
        {
            removeToastAsync.GetResults();
        }

        removeToastAsync.Cancel();
        return false;
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }
}

bool VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifier()
{
    auto toastNotificationManager = winrt::ToastNotificationManager::Default();

    winrt::ToastNotification toast{ CreateToastNotification() };
    toastNotificationManager.ShowToast(toast);
    auto id{ toast.ToastId() };
    toastNotificationManager.RemoveAllAsync().get();

    try
    {
        auto removeToastAsync{ winrt::ToastNotificationManager::Default().RemoveWithIdentifierAsync(id) };
        if (removeToastAsync.wait_for(std::chrono::seconds(300)) == winrt::Windows::Foundation::AsyncStatus::Error)
        {
            removeToastAsync.GetResults();
        }

        removeToastAsync.Cancel();
        return false;
    }
    catch (...)
    {
        return winrt::to_hresult() == E_FAIL; // ELx - would expect the operation to report that it couldn't remove the toast but it doesn't. The operation simply fails silently. Is this a bug or the expected behavior?
    }
}

bool VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier()
{
    auto toastNotificationManager = winrt::ToastNotificationManager::Default();

    winrt::ToastNotification toast1{ CreateToastNotification(L"Toast1") };
    toastNotificationManager.ShowToast(toast1);

    winrt::ToastNotification toast2{ CreateToastNotification(L"Toast2") };
    toastNotificationManager.ShowToast(toast2);

    winrt::ToastNotification toast3{ CreateToastNotification(L"Toast3") };
    toastNotificationManager.ShowToast(toast3);

    if (!VerifyToastIsActive(toast1.ToastId()) || !VerifyToastIsActive(toast2.ToastId()) || !VerifyToastIsActive(toast3.ToastId()))
    {
        return false;
    }

    toastNotificationManager.RemoveWithIdentifierAsync(toast2.ToastId()).get();

    if (!VerifyToastIsActive(toast1.ToastId()) || !VerifyToastIsActive(toast3.ToastId()))
    {
        return false;
    }

    return !VerifyToastIsActive(toast2.ToastId());
}

bool VerifyRemoveWithTagAsync()
{
    auto toastNotificationManager = winrt::ToastNotificationManager::Default();

    winrt::ToastNotification toast1{ CreateToastNotification() };
    toast1.Tag(L"Shared tag");
    //toast1.Group(L"group1");
    toastNotificationManager.ShowToast(toast1);

    winrt::ToastNotification toast2{ CreateToastNotification() };
    toast2.Tag(L"Unique tag");
    //toast2.Group(L"group2");
    toastNotificationManager.ShowToast(toast2);

    winrt::ToastNotification toast3{ CreateToastNotification() };
    toast3.Tag(L"Unique tag");
    toast3.Group(L"group3");
    toastNotificationManager.ShowToast(toast3);

    winrt::ToastNotification toast4{ CreateToastNotification() };
    toast4.Tag(L"Unique tag");
    //toast4.Group(L"group3");
    toastNotificationManager.ShowToast(toast4);

    if (!VerifyToastIsActive(toast1.ToastId()) || VerifyToastIsActive(toast2.ToastId()) || !VerifyToastIsActive(toast3.ToastId()) || !VerifyToastIsActive(toast4.ToastId()))
    {
        return false;
    }

    auto removeToastAsync{ winrt::ToastNotificationManager::Default().RemoveWithTagAsync(L"Unique tag") };
    if (removeToastAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        return false;
    }

    if (!VerifyToastIsActive(toast1.ToastId()) || VerifyToastIsActive(toast2.ToastId()) || !VerifyToastIsActive(toast3.ToastId()) || VerifyToastIsActive(toast4.ToastId()))
    {
        return false;
    }

    return true;
}

bool VerifyRemoveWithTagGroupAsync()
{
    auto toastNotificationManager = winrt::ToastNotificationManager::Default();

    winrt::ToastNotification toast1{ CreateToastNotification() };
    toast1.Tag(L"tag1");
    toast1.Group(L"Shared group");
    toastNotificationManager.ShowToast(toast1);

    winrt::ToastNotification toast2{ CreateToastNotification() };
    toast2.Tag(L"tag2");
    toast2.Group(L"Shared group");
    toastNotificationManager.ShowToast(toast2);

    winrt::ToastNotification toast3{ CreateToastNotification() };
    toast3.Tag(L"tag3");
    toast3.Group(L"Shared group");
    toastNotificationManager.ShowToast(toast3);

    if (!VerifyToastIsActive(toast1.ToastId()) || !VerifyToastIsActive(toast2.ToastId()) || !VerifyToastIsActive(toast3.ToastId()))
    {
        return false;
    }

    auto removeToastAsync{ winrt::ToastNotificationManager::Default().RemoveWithTagGroupAsync(L"tag2", L"Shared group") };
    if (removeToastAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        return false;
    }

    if (!VerifyToastIsActive(toast1.ToastId()) || VerifyToastIsActive(toast2.ToastId()) || !VerifyToastIsActive(toast3.ToastId()))
    {
        return false;
    }

    return true;
}

bool VerifyRemoveWithGroupAsync()
{
    auto toastNotificationManager = winrt::ToastNotificationManager::Default();

    winrt::ToastNotification toast1{ CreateToastNotification() };
    toast1.Tag(L"tag1");
    toast1.Group(L"Shared group");
    toastNotificationManager.ShowToast(toast1);

    winrt::ToastNotification toast2{ CreateToastNotification() };
    toast2.Tag(L"tag2");
    toast2.Group(L"Shared group");
    toastNotificationManager.ShowToast(toast2);

    winrt::ToastNotification toast3{ CreateToastNotification() };
    toast3.Tag(L"tag3");
    toast3.Group(L"Shared group");
    toastNotificationManager.ShowToast(toast3);

    if (!VerifyToastIsActive(toast1.ToastId()) || !VerifyToastIsActive(toast2.ToastId()) || !VerifyToastIsActive(toast3.ToastId()))
    {
        return false;
    }

    auto removeToastAsync{ winrt::ToastNotificationManager::Default().RemoveGroupAsync(L"Shared group") };
    if (removeToastAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        return false;
    }

    if (VerifyToastIsActive(toast1.ToastId()) || VerifyToastIsActive(toast2.ToastId()) || VerifyToastIsActive(toast3.ToastId()))
    {
        return false;
    }

    return true;
}

bool VerifyRemoveAllAsync()
{
    auto toastNotificationManager = winrt::ToastNotificationManager::Default();

    winrt::ToastNotification toast1{ CreateToastNotification() };
    toastNotificationManager.ShowToast(toast1);

    winrt::ToastNotification toast2{ CreateToastNotification() };
    toastNotificationManager.ShowToast(toast2);

    winrt::ToastNotification toast3{ CreateToastNotification() };
    toastNotificationManager.ShowToast(toast3);

    auto getAllAsync = toastNotificationManager.GetAllAsync();
    if (getAllAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        getAllAsync.Cancel();
        return false;
    }

    // At this point, there are at least 3 active toasts, the ones we just posted but there could also be others that are still active.
    if (getAllAsync.get().Size() < 3)
    {
        return false;
    }

    auto removeAllAsync = toastNotificationManager.RemoveAllAsync();
    if (removeAllAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        removeAllAsync.Cancel();
        return false;
    }

    getAllAsync = toastNotificationManager.GetAllAsync();
    if (getAllAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Error)
    {
        getAllAsync.Cancel();
        return false;
    }

    return true;
}

std::map<std::string, bool(*)()> const& GetSwitchMapping()
{
    static std::map<std::string, bool(*)()> switchMapping = {
        { "BackgroundActivationTest", &BackgroundActivationTest},
        { "UnregisterBackgroundActivationTest", &UnregisterBackgroundActivationTest },
        { "VerifyFailedRegisterActivatorUsingNullClsid", &VerifyFailedRegisterActivatorUsingNullClsid },
        { "VerifyFailedRegisterActivatorUsingNullClsid_Unpackaged", &VerifyFailedRegisterActivatorUsingNullClsid_Unpackaged },
        { "VerifyFailedRegisterActivatorUsingNullAssets", &VerifyFailedRegisterActivatorUsingNullAssets },
        { "VerifyFailedRegisterActivatorUsingNullAssets_Unpackaged", &VerifyFailedRegisterActivatorUsingNullAssets_Unpackaged },
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
        { "VerifyShowToast", &VerifyShowToast },
        { "VerifyShowToast_Unpackaged", &VerifyShowToast_Unpackaged },

        { "VerifyUpdateToastProgressDataUsingValidTagAndValidGroup", &VerifyUpdateToastProgressDataUsingValidTagAndValidGroup },
        { "VerifyUpdateToastProgressDataUsingValidTagAndValidGroup_Unpackaged", &VerifyUpdateToastProgressDataUsingValidTagAndValidGroup_Unpackaged },
        { "VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup", &VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup },
        { "VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup_Unpackaged", &VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup_Unpackaged },
        { "VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup", &VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup },
        { "VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup_Unpackaged", &VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup_Unpackaged },
        { "VerifyFailedUpdateNotificationDataWithoutPostToast", &VerifyFailedUpdateNotificationDataWithoutPostToast },
        { "VerifyFailedUpdateNotificationDataWithoutPostToast_Unpackaged", &VerifyFailedUpdateNotificationDataWithoutPostToast_Unpackaged },
        { "VerifyUpdateToastProgressDataUsingEmptyTagAndValidGroup", &VerifyUpdateToastProgressDataUsingEmptyTagAndValidGroup },
        { "VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup", &VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup },

        { "VerifyGetAllAsyncWithZeroActiveToast", &VerifyGetAllAsyncWithZeroActiveToast },
        { "VerifyGetAllAsyncWithOneActiveToast", &VerifyGetAllAsyncWithOneActiveToast },
        { "VerifyGetAllAsyncWithMultipleActiveToasts", &VerifyGetAllAsyncWithMultipleActiveToasts },
        { "VerifyGetAllAsyncReportsProgressData", &VerifyGetAllAsyncReportsProgressData },

        { "VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier", &VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier },
        { "VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifier", &VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifier },
        { "VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier", &VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier },
        { "VerifyRemoveWithTagAsync", &VerifyRemoveWithTagAsync },
        { "VerifyRemoveWithTagGroupAsync", &VerifyRemoveWithTagGroupAsync },
        { "VerifyRemoveWithGroupAsync", &VerifyRemoveWithGroupAsync },
        { "VerifyRemoveAllAsync", &VerifyRemoveAllAsync },

      };

    return switchMapping;
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
