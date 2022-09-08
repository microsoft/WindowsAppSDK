// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <iostream>
#include <wil/win32_helpers.h>
#include "WindowsAppRuntime.Test.AppModel.h"
#include <chrono>
#include <ShObjIdl_core.h>
#include <shlobj_core.h>
#include <propkey.h> //PKEY properties
#include <propsys.h>
#include <filesystem>

namespace std
{
    using namespace std::filesystem;
}

namespace winrt
{
    using namespace winrt::Microsoft::Windows::AppLifecycle;
    using namespace winrt::Windows::ApplicationModel::Activation;
    using namespace winrt::Windows::Foundation;
    using namespace winrt::Microsoft::Windows::AppNotifications;
    using namespace winrt::Windows::Foundation;
}

const std::wstring c_localWindowsAppSDKFolder{ LR"(\Microsoft\WindowsAppSDK\)" };
const std::wstring c_pngExtension{ LR"(.png)" };
const std::wstring c_appUserModelId{ LR"(TaefTestAppId)" };
const std::wstring c_iconFilepath{ std::filesystem::current_path() / "icon1.ico" };

bool BackgroundActivationTest() // Activating application for background test.
{
    return true;
}

bool UnregisterBackgroundActivationTest()
{
    winrt::AppNotificationManager::Default().Unregister();
    return true;
}

winrt::AppNotification CreateToastNotification(winrt::hstring message)
{
    winrt::hstring xmlPayload{ L"<toast>" + message + L"</toast>" };
    return winrt::AppNotification(xmlPayload);
}

winrt::AppNotification CreateToastNotification()
{
    return CreateToastNotification(L"intrepidToast");
}

void EnsureNoActiveToasts()
{
    auto removeAllAsync = winrt::AppNotificationManager::Default().RemoveAllAsync();
    if (removeAllAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        removeAllAsync.Cancel();
        THROW_HR_MSG(E_FAIL, "Failed to remove all active toasts");
    }
}

bool VerifyToastIsActive(UINT32 expectedToastId)
{
    auto retrieveNotificationsAsync{ winrt::AppNotificationManager::Default().GetAllAsync() };
    if (retrieveNotificationsAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        retrieveNotificationsAsync.Cancel();
        return false;
    }

    auto notifications = retrieveNotificationsAsync.get();

    bool found{ false };
    for (auto notification : notifications)
    {
        if (notification.Id() == expectedToastId)
        {
            found = true;
            break;
        }
    }

    return found;
}

bool VerifyProgressData(const winrt::AppNotificationProgressData& expected, const winrt::AppNotificationProgressData& actual)
{
    if (!expected && !actual)
    {
        return true;
    }

    if (!expected || !actual)
    {
        return false;
    }

    if (expected.Status() != actual.Status())
    {
        return false;
    }

    if (expected.Title() != actual.Title())
    {
        return false;
    }

    if (expected.Value() != actual.Value()) // Need an epsilon...
    {
        return false;
    }

    if (expected.ValueStringOverride() != actual.ValueStringOverride())
    {
        return false;
    }

    return true;
}

enum class ExpectedTransientProperties {
    EQUAL,    // Actual values are expected to be same as expected and will be checked.
    DEFAULT,  // Actual values are expected to have been defaulted and will be checked.
    UNKNOWN   // Actual values can't be determined and won't be checked.
};
bool VerifyToastNotificationIsValid(const winrt::AppNotification& expected, const winrt::AppNotification& actual, ExpectedTransientProperties expectedTransientProperties = ExpectedTransientProperties::EQUAL)
{
    if (expected.Tag() != actual.Tag())
    {
        return false;
    }

    if (expected.Group() != actual.Group())
    {
        return false;
    }

    if (expected.Id() != actual.Id())
    {
        return false;
    }

    auto expectedPayload = expected.Payload();
    auto actualPayload = actual.Payload();
    if (expectedPayload != actualPayload)
    {
        return false;
    }

    if (!VerifyProgressData(expected.Progress(), actual.Progress()))
    {
        return false;
    }

    if (expected.Expiration() > actual.Expiration())
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
        if (winrt::Microsoft::Windows::AppNotifications::AppNotificationPriority::Default != actual.Priority())
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

winrt::AppNotificationProgressData GetToastProgressData(
    std::wstring const& status,
    std::wstring const& title,
    double const& progressValue,
    std::wstring const& progressValueString,
    uint32_t sequenceNumber)
{
    winrt::AppNotificationProgressData progressData{sequenceNumber};
    progressData.Status(status);
    progressData.Title(title);
    progressData.Value(progressValue);
    progressData.ValueStringOverride(progressValueString);
    return progressData;
}

bool ProgressResultOperationHelper(winrt::IAsyncOperation<winrt::AppNotificationProgressResult> progressResultOperation, winrt::AppNotificationProgressResult progressResult)
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
    winrt::AppNotification toast{ CreateToastNotification() };

    toast.Tag(tag.c_str());
    toast.Group(group.c_str());

    winrt::AppNotificationManager::Default().Show(toast);

    if (toast.Id() == 0)
    {
        return false;
    }

    return true;
}

bool VerifyRegisterActivatorandUnregisterActivator()
{
    winrt::AppNotificationManager::Default().Unregister();

    try
    {
        winrt::AppNotificationManager::Default().Register();

        winrt::AppNotificationManager::Default().Unregister();
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool VerifyExplicitAppId_Unpackaged()
{
    winrt::AppNotificationManager::Default().Unregister();
    try
    {
        winrt::AppNotificationManager::Default().Register();
        winrt::AppNotificationManager::Default().Unregister();
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool VerifyUnregisterTwice_Unpackaged()
{
    winrt::AppNotificationManager::Default().Unregister();
    try
    {
        winrt::AppNotificationManager::Default().Register();
        winrt::AppNotificationManager::Default().Unregister();
        winrt::AppNotificationManager::Default().Unregister();
    }
    catch (...)
    {
        return winrt::to_hresult() == E_NOT_SET;
    }
    return false;
}

bool VerifyUnregisterTwice()
{
    try
    {
        // Register is already called in main for packaged apps
        winrt::AppNotificationManager::Default().Unregister();
        winrt::AppNotificationManager::Default().Unregister();
    }
    catch (...)
    {
        return winrt::to_hresult() == E_NOT_SET;
    }
    return false;
}

bool VerifyUnregisterAll_Unpackaged()
{
    winrt::AppNotificationManager::Default().UnregisterAll();
    try
    {
        winrt::AppNotificationManager::Default().Register();
        winrt::AppNotificationManager::Default().UnregisterAll();
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool VerifyUnregisterAll()
{
    try
    {
        // Register is already called in main for packaged apps
        winrt::AppNotificationManager::Default().UnregisterAll();
    }
    catch (...)
    {
        return false;
    }
    return true;
}

bool VerifyFailedMultipleRegisterActivator()
{
    try
    {
        // Register is already called in main for apps
        winrt::AppNotificationManager::Default().Register();
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyToastSettingEnabled()
{
    return winrt::AppNotificationManager::Default().Setting() == winrt::AppNotificationSetting::Enabled;
}

bool VerifyToastPayload()
{
    winrt::hstring xmlPayload{ L"<toast>intrepidToast</toast>" };

    winrt::AppNotification toast{ xmlPayload };;

    if (toast.Payload() != xmlPayload)
    {
        return false;
    }

    return true;
}

bool VerifyToastTag()
{
    winrt::AppNotification toast{ CreateToastNotification() };

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
    winrt::AppNotification toast{ CreateToastNotification() };

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
    winrt::AppNotification toast{ CreateToastNotification() };

    winrt::AppNotificationProgressData progressData{ 1 };
    progressData.Status(L"SomeStatus");
    progressData.Title(L"SomeTitle");
    progressData.Value(0.14);
    progressData.ValueStringOverride(L"14%");

    toast.Progress(progressData);

    auto progressDataFromToast = toast.Progress();
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

    if (progressDataFromToast.SequenceNumber() != 1)
    {
        return false;
    }

    return true;
}

bool VerifyToastExpirationTime()
{
    winrt::AppNotification toast{ CreateToastNotification() };

    if (toast.Expiration() != winrt::DateTime{})
    {
        return false;
    }

    winrt::DateTime expirationTime{ winrt::clock::now() };
    expirationTime += winrt::TimeSpan{ std::chrono::seconds(10) };

    toast.Expiration(expirationTime);
    if (toast.Expiration() != expirationTime)
    {
        return false;
    }

    return true;
}

bool VerifyToastPriority()
{
    winrt::AppNotification toast{ CreateToastNotification() };

    if (toast.Priority() != winrt::AppNotificationPriority::Default)
    {
        return false;
    }

    toast.Priority(winrt::AppNotificationPriority::High);
    if (toast.Priority() != winrt::AppNotificationPriority::High)
    {
        return false;
    }

    return true;
}

bool VerifyToastSuppressDisplay()
{
    winrt::AppNotification toast{ CreateToastNotification() };

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
    winrt::AppNotification toast{ CreateToastNotification() };

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
    winrt::AppNotification toast{ CreateToastNotification() };

    auto toastNotificationManager = winrt::AppNotificationManager::Default();
    toastNotificationManager.Show(toast);

    if (toast.Id() == 0)
    {
        return false;
    }

    return VerifyToastIsActive(toast.Id());
}

bool VerifyShowToast_Unpackaged()
{
	// Registration happens in main()
    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterAll();
        });

    EnsureNoActiveToasts();

    winrt::AppNotification toast{ CreateToastNotification() };

    toastNotificationManager.Show(toast);

    if (toast.Id() == 0)
    {
        return false;
    }

    return VerifyToastIsActive(toast.Id());
}

bool VerifyUpdateToastProgressDataUsingValidTagAndValidGroup()
{
    // Registration happens in main()
    auto toastNotificationManager{ winrt::AppNotificationManager::Default() };

    PostToastHelper(L"PTag", L"PGroup");

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterAll();
        });

    winrt::AppNotificationProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%", 1);

    auto progressResultOperation = winrt::AppNotificationManager::Default().UpdateAsync(progressData, L"PTag", L"PGroup");
    return ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::Succeeded);
}

bool VerifyUpdateToastProgressDataUsingValidTagAndValidGroup_Unpackaged()
{
    // Registration happens in main()
    auto toastNotificationManager{ winrt::AppNotificationManager::Default() };

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterAll();
        });

    PostToastHelper(L"Tag", L"Group");

    winrt::AppNotificationProgressData progressData = GetToastProgressData(L"SomeStatus", L"SomeTitle", 0.14, L"14%", 1);

    auto progressResultOperation = toastNotificationManager.UpdateAsync(progressData, L"Tag", L"Group");
    return ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::Succeeded);
}

bool VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup()
{
    // Registration happens in main()
    auto toastNotificationManager{ winrt::AppNotificationManager::Default() };

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterAll();
        });

    PostToastHelper(L"PTag", L"");

    winrt::AppNotificationProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%", 1);

    auto progressResultOperation = winrt::AppNotificationManager::Default().UpdateAsync(progressData, L"PTag");
    return ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::Succeeded);
}

bool VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup_Unpackaged()
{
    // Registration happens in main()
    auto toastNotificationManager{ winrt::AppNotificationManager::Default() };

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterAll();
        });

    PostToastHelper(L"Tag", L"");

    winrt::AppNotificationProgressData progressData = GetToastProgressData(L"SomeStatus", L"SomeTitle", 0.14, L"14%", 1);

    auto progressResultOperation = toastNotificationManager.UpdateAsync(progressData, L"Tag");
    return ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::Succeeded);
}

bool VerifyToastUpdateZeroSequenceFail_Unpackaged()
{
    // Registration happens in main()
    auto toastNotificationManager{ winrt::AppNotificationManager::Default() };

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterAll();
        });

    winrt::AppNotificationProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%", 1);
    try
    {
        progressData.SequenceNumber(0);
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }
    return false;
}

bool VerifyUpdateToastProgressDataUsingEmptyTagAndValidGroup()
{
    try
    {
        // Registration happens in main()
        auto toastNotificationManager{ winrt::AppNotificationManager::Default() };

        auto scope_exit = wil::scope_exit(
            [&] {
                toastNotificationManager.UnregisterAll();
            });

        winrt::AppNotificationProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%", 1);

        auto progressResultOperation = winrt::AppNotificationManager::Default().UpdateAsync(progressData, L"", L"Group").get();
        (void)progressResultOperation;  // Unused local, exists for debugging, optimized away in Release builds
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
        // Registration happens in main()
        auto toastNotificationManager{ winrt::AppNotificationManager::Default() };

        auto scope_exit = wil::scope_exit(
            [&] {
                toastNotificationManager.UnregisterAll();
            });

        winrt::AppNotificationProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%", 1);

        auto progressResultOperation = winrt::AppNotificationManager::Default().UpdateAsync(progressData, L"", L"").get();
        (void)progressResultOperation;  // Unused local, exists for debugging, optimized away in Release builds
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }
    return false;
}

bool VerifyToastProgressDataSequence0Fail()
{
    try
    {
        // Registration happens in main()
        auto toastNotificationManager{ winrt::AppNotificationManager::Default() };

        auto scope_exit = wil::scope_exit(
            [&] {
                toastNotificationManager.UnregisterAll();
            });

        winrt::AppNotificationProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%", 0);
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }
    return false;
}

bool VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup()
{
    // Registration happens in main()

    auto toastNotificationManager{ winrt::AppNotificationManager::Default() };

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterAll();
        });

    PostToastHelper(L"PTag", L"PGroup");

    winrt::AppNotificationProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%", 1);

    auto progressResultOperation = winrt::AppNotificationManager::Default().UpdateAsync(progressData, L"NonExistentTag", L"NonExistentGroup");
    return ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::AppNotificationNotFound);
}

bool VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup_Unpackaged()
{
    auto toastNotificationManager{ winrt::AppNotificationManager::Default() };

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterAll();
        });

    PostToastHelper(L"Tag", L"Group");

    winrt::AppNotificationProgressData progressData = GetToastProgressData(L"SomeStatus", L"SomeTitle", 0.14, L"14%", 1);

    auto progressResultOperation = toastNotificationManager.UpdateAsync(progressData, L"NonExistentTag", L"NonExistentGroup");
    return ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::AppNotificationNotFound);
}

bool VerifyFailedUpdateNotificationDataWithoutPostToast()
{
    // Registration happens in main()
    auto toastNotificationManager{ winrt::AppNotificationManager::Default() };

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterAll();
        });

    winrt::AppNotificationProgressData progressData = GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%", 1);

    auto progressResultOperation = winrt::AppNotificationManager::Default().UpdateAsync(progressData, L"Tag", L"Group");
    return ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::AppNotificationNotFound);
}

bool VerifyFailedUpdateNotificationDataWithoutPostToast_Unpackaged()
{
    auto toastNotificationManager{ winrt::AppNotificationManager::Default() };

    auto scope_exit = wil::scope_exit(
        [&] {
            toastNotificationManager.UnregisterAll();
        });

    winrt::AppNotificationProgressData progressData = GetToastProgressData(L"SomeStatus", L"SomeTitle", 0.14, L"14%", 1);
    auto progressResultOperation = toastNotificationManager.UpdateAsync(progressData, L"SomeRandomTag", L"SomeRandomGroup");
    return ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::AppNotificationNotFound);
}

bool VerifyGetAllAsyncWithZeroActiveToast()
{
    EnsureNoActiveToasts();

    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    auto retrieveNotificationsAsync = toastNotificationManager.GetAllAsync();
    if (retrieveNotificationsAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        retrieveNotificationsAsync.Cancel();
        return false;
    }

    auto notifications = retrieveNotificationsAsync.GetResults();

    auto size = notifications.Size();
    if (size != 0)
    {
        return false;
    }

    return true;
}

bool VerifyGetAllAsyncWithOneActiveToast()
{
    EnsureNoActiveToasts();

    winrt::AppNotification toast{ CreateToastNotification(L"MyOwnLittleToast") };
    toast.Tag(L"aDifferentTag");
    toast.Group(L"aDifferentGroup");
    winrt::DateTime expirationTime{ winrt::clock::now() };
    expirationTime += winrt::TimeSpan{ std::chrono::seconds(10) };
    toast.Expiration(expirationTime);
    toast.ExpiresOnReboot(true);
    toast.Priority(winrt::AppNotificationPriority::High);
    toast.SuppressDisplay(true);

    winrt::AppNotificationProgressData progressData = GetToastProgressData(L"SomeStatus", L"SomeTitle", 0.14, L"14%", 1);
    toast.Progress(progressData);

    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    toastNotificationManager.Show(toast);

    auto retrieveNotificationsAsync = toastNotificationManager.GetAllAsync();
    if (retrieveNotificationsAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        retrieveNotificationsAsync.Cancel();
        return false;
    }

    auto notifications = retrieveNotificationsAsync.GetResults();

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

    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    winrt::AppNotification toast1{ CreateToastNotification() };
    toastNotificationManager.Show(toast1);

    winrt::AppNotification toast2{ CreateToastNotification() };
    toastNotificationManager.Show(toast2);

    winrt::AppNotification toast3{ CreateToastNotification() };
    toastNotificationManager.Show(toast3);

    auto getNotificationsAsync = toastNotificationManager.GetAllAsync();
    if (getNotificationsAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        getNotificationsAsync.Cancel();
        return false;
    }

    auto notifications = getNotificationsAsync.GetResults();

    if (notifications.Size() != 3)
    {
        return false;
    }

    auto actual = notifications.GetAt(0);
    auto payload = actual.Payload();

    if (wcscmp(L"<toast>intrepidToast</toast>", payload.c_str()) != 0)
    {
        return false;
    }

    return true;
}

bool VerifyGetAllAsyncIgnoresUpdatesToProgressData()
{
    EnsureNoActiveToasts();

    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    winrt::AppNotification toast{ CreateToastNotification() };
    toast.Tag(L"Tag");
    toast.Group(L"Group");
    winrt::AppNotificationProgressData initialProgressData = GetToastProgressData(L"Initial Status", L"Initial Title", 0.05, L"5%", 1);
    toast.Progress(initialProgressData);

    toastNotificationManager.Show(toast);

    winrt::AppNotificationProgressData updatedProgressData = GetToastProgressData(L"Updated Status", L"Updated Title", 0.14, L"14%", 1);
    auto progressResultOperation = toastNotificationManager.UpdateAsync(updatedProgressData, L"Tag", L"Group");
    if (!ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::Succeeded))
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
    return VerifyToastNotificationIsValid(toast, actual, ExpectedTransientProperties::EQUAL);
}

bool VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier()
{
    try
    {
        auto removeToastAsync{ winrt::AppNotificationManager::Default().RemoveByIdAsync(0) };
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

bool VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow()
{
    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    winrt::AppNotification toast{ CreateToastNotification() };
    toastNotificationManager.Show(toast);
    auto id{ toast.Id() };
    toastNotificationManager.RemoveAllAsync().get();

    auto removeToastAsync{ toastNotificationManager.RemoveByIdAsync(id) };
    if (removeToastAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        removeToastAsync.Cancel();
        return false;
    }

    removeToastAsync.GetResults();
    return true;
}

bool VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier()
{
    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    winrt::AppNotification toast1{ CreateToastNotification(L"Toast1") };
    toastNotificationManager.Show(toast1);

    winrt::AppNotification toast2{ CreateToastNotification(L"Toast2") };
    toastNotificationManager.Show(toast2);

    winrt::AppNotification toast3{ CreateToastNotification(L"Toast3") };
    toastNotificationManager.Show(toast3);

    if (!VerifyToastIsActive(toast1.Id()) || !VerifyToastIsActive(toast2.Id()) || !VerifyToastIsActive(toast3.Id()))
    {
        return false;
    }

    toastNotificationManager.RemoveByIdAsync(toast2.Id()).get();

    if (!VerifyToastIsActive(toast1.Id()) || !VerifyToastIsActive(toast3.Id()))
    {
        return false;
    }

    return !VerifyToastIsActive(toast2.Id());
}

bool VerifyRemoveWithTagAsyncUsingEmptyTagThrows()
{
    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    try
    {
        toastNotificationManager.RemoveByTagAsync(L"").get();
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow()
{
    EnsureNoActiveToasts();

    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    auto removeToastAsync{ toastNotificationManager.RemoveByTagAsync(L"tag") };
    if (removeToastAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        return false;
    }

    return true;
}

bool VerifyRemoveWithTagAsync()
{
    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    winrt::AppNotification toast1{ CreateToastNotification() };
    toast1.Tag(L"Shared tag");
    //toast1.Group(L"group1");
    toastNotificationManager.Show(toast1);

    winrt::AppNotification toast2{ CreateToastNotification() };
    toast2.Tag(L"Unique tag");
    //toast2.Group(L"group2");
    toastNotificationManager.Show(toast2);

    winrt::AppNotification toast3{ CreateToastNotification() };
    toast3.Tag(L"Unique tag");
    toast3.Group(L"group3");
    toastNotificationManager.Show(toast3);

    winrt::AppNotification toast4{ CreateToastNotification() };
    toast4.Tag(L"Unique tag");
    //toast4.Group(L"group3");
    toastNotificationManager.Show(toast4);

    if (!VerifyToastIsActive(toast1.Id()) || VerifyToastIsActive(toast2.Id()) || !VerifyToastIsActive(toast3.Id()) || !VerifyToastIsActive(toast4.Id()))
    {
        return false;
    }

    auto removeToastAsync{ toastNotificationManager.RemoveByTagAsync(L"Unique tag") };
    if (removeToastAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        return false;
    }

    if (!VerifyToastIsActive(toast1.Id()) || VerifyToastIsActive(toast2.Id()) || !VerifyToastIsActive(toast3.Id()) || VerifyToastIsActive(toast4.Id()))
    {
        return false;
    }

    return true;
}

bool VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows()
{
    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    try
    {
        toastNotificationManager.RemoveByTagAndGroupAsync(L"", L"group").get();
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows()
{
    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    try
    {
        toastNotificationManager.RemoveByTagAndGroupAsync(L"tag", L"").get();
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyRemoveWithTagGroupAsyncUsingNonExistentTagGroupDoesNotThrow()
{
    EnsureNoActiveToasts();

    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    auto removeToastAsync{ toastNotificationManager.RemoveByTagAndGroupAsync(L"tag", L"group")};
    if (removeToastAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        return false;
    }

    return true;
}

bool VerifyRemoveWithTagGroupAsync()
{
    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    winrt::AppNotification toast1{ CreateToastNotification() };
    toast1.Tag(L"tag1");
    toast1.Group(L"Shared group");
    toastNotificationManager.Show(toast1);

    winrt::AppNotification toast2{ CreateToastNotification() };
    toast2.Tag(L"tag2");
    toast2.Group(L"Shared group");
    toastNotificationManager.Show(toast2);

    winrt::AppNotification toast3{ CreateToastNotification() };
    toast3.Tag(L"tag3");
    toast3.Group(L"Shared group");
    toastNotificationManager.Show(toast3);

    if (!VerifyToastIsActive(toast1.Id()) || !VerifyToastIsActive(toast2.Id()) || !VerifyToastIsActive(toast3.Id()))
    {
        return false;
    }

    auto removeToastAsync{ toastNotificationManager.RemoveByTagAndGroupAsync(L"tag2", L"Shared group") };
    if (removeToastAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        return false;
    }

    if (!VerifyToastIsActive(toast1.Id()) || VerifyToastIsActive(toast2.Id()) || !VerifyToastIsActive(toast3.Id()))
    {
        return false;
    }

    return true;
}

bool VerifyRemoveGroupAsyncUsingEmptyGroupThrows()
{
    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    try
    {
        toastNotificationManager.RemoveByGroupAsync(L"").get();
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow()
{
    EnsureNoActiveToasts();

    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    auto removeToastAsync{ toastNotificationManager.RemoveByGroupAsync(L"group") };
    if (removeToastAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        return false;
    }

    return true;
}

bool VerifyRemoveGroupAsync()
{
    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    winrt::AppNotification toast1{ CreateToastNotification() };
    toast1.Tag(L"tag1");
    toast1.Group(L"Shared group");
    toastNotificationManager.Show(toast1);

    winrt::AppNotification toast2{ CreateToastNotification() };
    toast2.Tag(L"tag2");
    toast2.Group(L"Shared group");
    toastNotificationManager.Show(toast2);

    winrt::AppNotification toast3{ CreateToastNotification() };
    toast3.Tag(L"tag3");
    toast3.Group(L"Shared group");
    toastNotificationManager.Show(toast3);

    if (!VerifyToastIsActive(toast1.Id()) || !VerifyToastIsActive(toast2.Id()) || !VerifyToastIsActive(toast3.Id()))
    {
        return false;
    }

    auto removeToastAsync{ toastNotificationManager.RemoveByGroupAsync(L"Shared group") };
    if (removeToastAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        return false;
    }

    if (VerifyToastIsActive(toast1.Id()) || VerifyToastIsActive(toast2.Id()) || VerifyToastIsActive(toast3.Id()))
    {
        return false;
    }

    return true;
}

bool VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow()
{
    EnsureNoActiveToasts();

    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    auto removeToastAsync{ toastNotificationManager.RemoveAllAsync() };
    if (removeToastAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        return false;
    }

    return true;
}

bool VerifyRemoveAllAsync()
{
    auto toastNotificationManager = winrt::AppNotificationManager::Default();

    winrt::AppNotification toast1{ CreateToastNotification() };
    toastNotificationManager.Show(toast1);

    winrt::AppNotification toast2{ CreateToastNotification() };
    toastNotificationManager.Show(toast2);

    winrt::AppNotification toast3{ CreateToastNotification() };
    toastNotificationManager.Show(toast3);

    auto getAllAsync = toastNotificationManager.GetAllAsync();
    if (getAllAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        getAllAsync.Cancel();
        return false;
    }

    // At this point, there are at least 3 active toasts, the ones we just posted but there could also be others that are still active.
    if (getAllAsync.GetResults().Size() < 3)
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
    if (getAllAsync.wait_for(std::chrono::seconds(300)) != winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        getAllAsync.Cancel();
        return false;
    }

    if (getAllAsync.GetResults().Size() != 0)
    {
        return false;
    }

    return true;
}

bool VerifyIconPathExists_Unpackaged()
{
    try
    {
        // Register is already called in main with an explicit appusermodelId
        wil::unique_cotaskmem_string localAppDataPath;
        THROW_IF_FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0 /* flags */, nullptr /* access token handle */, &localAppDataPath));

        // Evaluated path: C:\Users\<currentUser>\AppData\Local\Microsoft\WindowsAppSDK\<AUMID>.png
        std::path iconFilePath{ std::wstring(localAppDataPath.get()) + c_localWindowsAppSDKFolder + c_appUserModelId + c_pngExtension };
        winrt::check_bool(std::exists(iconFilePath));

        winrt::AppNotificationManager::Default().UnregisterAll();

        // After unregister this file should not exist
        winrt::check_bool(!std::exists(iconFilePath));
    }
    catch (...)
    {
        return false;
    }

    return true;
}

bool VerifyRegisterWithNullDisplayNameFail_Unpackaged()
{
    // Register is already called in main with an explicit appusermodelId
    winrt::AppNotificationManager::Default().UnregisterAll();
    try
    {
        winrt::AppNotificationManager::Default().Register(winrt::hstring{}, winrt::Uri{ c_iconFilepath });
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyRegisterWithNullIconFail_Unpackaged()
{
    // Register is already called in main with an explicit appusermodelId
    winrt::AppNotificationManager::Default().UnregisterAll();
    try
    {
        winrt::AppNotificationManager::Default().Register(L"AppNotificationApp", nullptr);
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyRegisterWithNullDisplayNameAndNullIconFail_Unpackaged()
{
    // Register is already called in main with an explicit appusermodelId
    winrt::AppNotificationManager::Default().UnregisterAll();
    try
    {
        winrt::AppNotificationManager::Default().Register(winrt::hstring{}, nullptr);
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return true;
}

bool VerifyShowToastWithCustomDisplayNameAndIcon_Unpackaged()
{
    // Register is already called in main with an explicit appusermodelId
    winrt::AppNotificationManager::Default().UnregisterAll();
    try
    {
          winrt::AppNotificationManager::Default().Register(L"AppNotificationApp", winrt::Uri{ c_iconFilepath });

          winrt::check_bool(VerifyShowToast_Unpackaged());
    }
    catch (...)
    {
        return false;
    }

    return true;
}

bool VerifyRegisterWithDisplayNameAndInvalidIconPathFail_Unpackaged()
{
    // Register is already called in main with an explicit appusermodelId
    winrt::AppNotificationManager::Default().UnregisterAll();
    try
    {
        winrt::AppNotificationManager::Default().Register(L"AppNotificationApp", winrt::Uri{ LR"(C:\InvalidPath\)" });
    }
    catch (...)
    {
        return winrt::to_hresult() == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    }

    return false;
}

bool VerifyRegisterWithEmptyDisplayNameFail_Unpackaged()
{
    // Register is already called in main with an explicit appusermodelId
    winrt::AppNotificationManager::Default().UnregisterAll();
    try
    {
        // hstring treats L"" as assigning nullptr
        winrt::AppNotificationManager::Default().Register(L"", winrt::Uri{ c_iconFilepath });
    }
    catch (...)
    {
        return winrt::to_hresult() == E_INVALIDARG;
    }

    return false;
}

bool VerifyRegisterWithAssetsFail()
{
    // Register is already called in main with an explicit appusermodelId
    winrt::AppNotificationManager::Default().UnregisterAll();
    try
    {
        // API fails for Packaged Scenario
        winrt::AppNotificationManager::Default().Register(L"AppNotificationApp", winrt::Uri{ LR"(C:\InvalidPath\)" });
    }
    catch (...)
    {
        return winrt::to_hresult() == E_ILLEGAL_METHOD_CALL;
    }

    return false;
}

std::map<std::string, bool(*)()> const& GetSwitchMapping()
{
    static std::map<std::string, bool(*)()> switchMapping = {
        { "BackgroundActivationTest", &BackgroundActivationTest},
        { "UnregisterBackgroundActivationTest", &UnregisterBackgroundActivationTest },
        { "VerifyRegisterActivatorandUnRegisterActivatorUsingClsid", &VerifyRegisterActivatorandUnregisterActivator },
        { "VerifyRegisterActivatorandUnRegisterActivatorUsingAssets_Unpackaged", &VerifyRegisterActivatorandUnregisterActivator },
        { "VerifyFailedMultipleRegisterActivatorUsingSameClsid", &VerifyFailedMultipleRegisterActivator },
        { "VerifyFailedMultipleRegisterActivatorUsingSameAssets_Unpackaged", &VerifyFailedMultipleRegisterActivator },

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
        { "VerifyGetAllAsyncIgnoresUpdatesToProgressData", &VerifyGetAllAsyncIgnoresUpdatesToProgressData },
        { "VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier", &VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier },
        { "VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow", &VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow },
        { "VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier", &VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier },
        { "VerifyRemoveWithTagAsyncUsingEmptyTagThrows", &VerifyRemoveWithTagAsyncUsingEmptyTagThrows },
        { "VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow", &VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow },
        { "VerifyRemoveWithTagAsync", &VerifyRemoveWithTagAsync },
        { "VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows", &VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows },
        { "VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows", &VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows },
        { "VerifyRemoveWithTagGroupAsyncUsingNonExistentTagGroupDoesNotThrow", &VerifyRemoveWithTagGroupAsyncUsingNonExistentTagGroupDoesNotThrow },
        { "VerifyRemoveWithTagGroupAsync", &VerifyRemoveWithTagGroupAsync },
        { "VerifyRemoveGroupAsyncUsingEmptyGroupThrows", &VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows },
        { "VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow", &VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow },
        { "VerifyRemoveGroupAsync", &VerifyRemoveGroupAsync },
        { "VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow", &VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow },
        { "VerifyRemoveAllAsync", &VerifyRemoveAllAsync },
        { "VerifyExplicitAppId_Unpackaged", &VerifyExplicitAppId_Unpackaged },
        { "VerifyUnregisterAll_Unpackaged", &VerifyUnregisterAll_Unpackaged },
        { "VerifyUnregisterAll", &VerifyUnregisterAll },
        { "VerifyUnregisterTwice", &VerifyUnregisterTwice },
        { "VerifyUnregisterTwice_Unpackaged", &VerifyUnregisterTwice_Unpackaged },
        { "VerifyToastProgressDataSequence0Fail", &VerifyToastProgressDataSequence0Fail },
        { "VerifyToastUpdateZeroSequenceFail_Unpackaged", &VerifyToastUpdateZeroSequenceFail_Unpackaged },
        { "VerifyIconPathExists_Unpackaged", &VerifyIconPathExists_Unpackaged},

        { "VerifyRegisterWithNullDisplayNameFail_Unpackaged", &VerifyRegisterWithNullDisplayNameFail_Unpackaged},
        { "VerifyRegisterWithNullIconFail_Unpackaged", &VerifyRegisterWithNullIconFail_Unpackaged},
        { "VerifyRegisterWithNullDisplayNameAndNullIconFail_Unpackaged", &VerifyRegisterWithNullDisplayNameAndNullIconFail_Unpackaged},
        { "VerifyShowToastWithCustomDisplayNameAndIcon_Unpackaged", &VerifyShowToastWithCustomDisplayNameAndIcon_Unpackaged},
        { "VerifyRegisterWithDisplayNameAndInvalidIconPathFail_Unpackaged", &VerifyRegisterWithDisplayNameAndInvalidIconPathFail_Unpackaged},
        { "VerifyRegisterWithEmptyDisplayNameFail_Unpackaged", &VerifyRegisterWithEmptyDisplayNameFail_Unpackaged},
        { "VerifyRegisterWithAssetsFail", &VerifyRegisterWithAssetsFail},
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

    if (!Test::AppModel::IsPackagedProcess())
    {
        // Not mandatory, but it's highly recommended to specify AppUserModelId
        THROW_IF_FAILED(SetCurrentProcessExplicitAppUserModelID(c_appUserModelId.c_str()));
    }

    winrt::AppNotificationManager::Default().Register();

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
