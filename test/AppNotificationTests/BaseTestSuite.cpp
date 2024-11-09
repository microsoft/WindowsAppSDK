// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "AppNotification-Test-Constants.h"
#include "AppNotifications.Test.h"
#include "BaseTestSuite.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::System;
using namespace winrt::Microsoft::Windows::AppNotifications;
using namespace AppNotifications::Test;

void BaseTestSuite::ClassSetup()
{
    ::Test::Bootstrap::Setup();
}

void BaseTestSuite::ClassCleanup()
{
    ::Test::Bootstrap::Cleanup();
}

void BaseTestSuite::MethodSetup()
{
    bool isSelfContained{};
    VERIFY_SUCCEEDED(TestData::TryGetValue(L"SelfContained", isSelfContained));

    if (!isSelfContained)
    {
        ::WindowsAppRuntime::VersionInfo::TestInitialize(::Test::Bootstrap::TP::WindowsAppRuntimeFramework::c_PackageFamilyName,
                                                        ::Test::Bootstrap::TP::WindowsAppRuntimeMain::c_PackageFamilyName);
        VERIFY_IS_FALSE(::WindowsAppRuntime::SelfContained::IsSelfContained());
    }
    else
    {
        ::WindowsAppRuntime::VersionInfo::TestInitialize(L"I_don't_exist_package!", L"I_don't_exist_package!");
        VERIFY_IS_TRUE(::WindowsAppRuntime::SelfContained::IsSelfContained());
    }
}

void BaseTestSuite::MethodCleanup()
{
    if (Test::AppModel::IsPackagedProcess() || (!Test::AppModel::IsPackagedProcess() && !m_unregisteredFully))
    {
        VERIFY_IS_TRUE(EnsureNoActiveToasts());
    }

    if (!m_unregisteredFully)
    {
        UnregisterAllWithAppNotificationManager();
    }

    ::WindowsAppRuntime::VersionInfo::TestShutdown();
}

void BaseTestSuite::RegisterWithAppNotificationManager()
{
    AppNotificationManager::Default().Register();
    m_unregisteredFully = false;
}

void BaseTestSuite::UnregisterAllWithAppNotificationManager()
{
    AppNotificationManager::Default().UnregisterAll();
    m_unregisteredFully = true;
}

void BaseTestSuite::VerifyRegisterActivatorandUnregisterActivator()
{
    RegisterWithAppNotificationManager();
    AppNotificationManager::Default().Unregister();
}

void BaseTestSuite::VerifyFailedMultipleRegister()
{
    RegisterWithAppNotificationManager();
    VERIFY_THROWS_HR(AppNotificationManager::Default().Register(), E_INVALIDARG);
}

void BaseTestSuite::VerifyUnregisterAll()
{
    RegisterWithAppNotificationManager();
    UnregisterAllWithAppNotificationManager();
}

void BaseTestSuite::VerifyUnregisterTwice()
{
    RegisterWithAppNotificationManager();
    AppNotificationManager::Default().Unregister();
    VERIFY_THROWS_HR(AppNotificationManager::Default().Unregister(), E_NOT_SET);
}
void BaseTestSuite::VerifyToastSettingEnabled()
{
    VERIFY_ARE_EQUAL(AppNotificationManager::Default().Setting(), AppNotificationSetting::Enabled);
}

void BaseTestSuite::VerifyToastPayload()
{
    winrt::hstring xmlPayload{ L"<toast>intrepidToast</toast>" };
    AppNotification toast{ xmlPayload };
    VERIFY_ARE_EQUAL(toast.Payload(), xmlPayload);
}

void BaseTestSuite::VerifyToastTag()
{
    AppNotification toast{ CreateToastNotification() };
    VERIFY_IS_TRUE(toast.Tag().empty());

    toast.Tag(L"Tag");
    VERIFY_ARE_EQUAL(toast.Tag(), L"Tag");
}

void BaseTestSuite::VerifyToastGroup()
{
    AppNotification toast{ CreateToastNotification() };
    VERIFY_IS_TRUE(toast.Group().empty());

    toast.Group(L"Group");
    VERIFY_ARE_EQUAL(toast.Group(), L"Group");
}

void BaseTestSuite::VerifyToastProgressDataFromToast()
{
    AppNotification toast{ CreateToastNotification() };

    AppNotificationProgressData progressData{ 1 };
    progressData.Status(L"Status");
    progressData.Title(L"Title");
    progressData.Value(0.14);
    progressData.ValueStringOverride(L"14%");
    toast.Progress(progressData);

    auto progressDataFromToast{ toast.Progress() };
    VERIFY_ARE_EQUAL(progressDataFromToast.Status(), L"Status");
    VERIFY_ARE_EQUAL(progressDataFromToast.Title(), L"Title");
    VERIFY_ARE_EQUAL(progressDataFromToast.Value(), 0.14);
    VERIFY_ARE_EQUAL(progressDataFromToast.ValueStringOverride(), L"14%");
    VERIFY_ARE_EQUAL(progressDataFromToast.SequenceNumber(), 1u);
}

void BaseTestSuite::VerifyToastExpirationTime()
{
    AppNotification toast{ CreateToastNotification() };
    VERIFY_ARE_EQUAL(toast.Expiration(), winrt::DateTime{});

    winrt::DateTime expirationTime{ winrt::clock::now() };
    expirationTime += winrt::TimeSpan{ std::chrono::seconds(10) };

    toast.Expiration(expirationTime);
    VERIFY_ARE_EQUAL(toast.Expiration(), expirationTime);
}

void BaseTestSuite::VerifyToastPriority()
{
    AppNotification toast{ CreateToastNotification() };
    VERIFY_ARE_EQUAL(toast.Priority(), AppNotificationPriority::Default);

    toast.Priority(AppNotificationPriority::High);
    VERIFY_ARE_EQUAL(toast.Priority(), AppNotificationPriority::High);
}

void BaseTestSuite::VerifyToastSuppressDisplay()
{
    AppNotification toast{ CreateToastNotification() };
    VERIFY_IS_FALSE(toast.SuppressDisplay());

    toast.SuppressDisplay(true);
    VERIFY_IS_TRUE(toast.SuppressDisplay());
}

void BaseTestSuite::VerifyToastExpiresOnReboot()
{
    AppNotification toast{ CreateToastNotification() };
    VERIFY_IS_FALSE(toast.ExpiresOnReboot());

    toast.ExpiresOnReboot(true);
    VERIFY_IS_TRUE(toast.ExpiresOnReboot());
}

void BaseTestSuite::VerifyToastProgressDataSequence0Fail()
{
    VERIFY_THROWS_HR(GetToastProgressData(L"PStatus", L"PTitle", 0.10, L"10%", 0), E_INVALIDARG);
}

void BaseTestSuite::VerifyShowToast()
{
    RegisterWithAppNotificationManager();

    AppNotification toast{ CreateToastNotification() };
    AppNotificationManager::Default().Show(toast);

    std::vector<AppNotification> toastVector{ toast };
    VERIFY_IS_TRUE(VerifyToastsPosted(toastVector));
}

void BaseTestSuite::VerifyUpdateToastProgressDataUsingValidTagAndValidGroup()
{
    RegisterWithAppNotificationManager();
    PostToastHelper(L"Tag", L"Group");
    AppNotificationProgressData progressData{ GetToastProgressData(L"Status", L"Title", 0.10, L"10%", 1) };

    auto progressResultOperation{ AppNotificationManager::Default().UpdateAsync(progressData, L"Tag", L"Group") };
    ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::Succeeded);
}

void BaseTestSuite::VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup()
{
    RegisterWithAppNotificationManager();
    PostToastHelper(L"Tag", L"");
    AppNotificationProgressData progressData{ GetToastProgressData(L"Status", L"Title", 0.14, L"14%", 1) };

    auto progressResultOperation{ AppNotificationManager::Default().UpdateAsync(progressData, L"Tag") };
    ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::Succeeded);
}

void BaseTestSuite::VerifyUpdateToastProgressDataUsingEmptyTagAndValidGroup()
{
    AppNotificationProgressData progressData{ GetToastProgressData(L"Status", L"Title", 0.14, L"14%", 1) };

    VERIFY_THROWS_HR(AppNotificationManager::Default().UpdateAsync(progressData, L"", L"Group").get(), E_INVALIDARG);
}

void BaseTestSuite::VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup()
{
    AppNotificationProgressData progressData{ GetToastProgressData(L"Status", L"Title", 0.14, L"14%", 1) };

    VERIFY_THROWS_HR(AppNotificationManager::Default().UpdateAsync(progressData, L"", L"").get(), E_INVALIDARG);
}

void BaseTestSuite::VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup()
{
    RegisterWithAppNotificationManager();
    PostToastHelper(L"Tag", L"Group");
    AppNotificationProgressData progressData{ GetToastProgressData(L"Status", L"Title", 0.14, L"14%", 1) };

    auto progressResultOperation{ AppNotificationManager::Default().UpdateAsync(progressData, L"NonExistentTag", L"NonExistentGroup") };
    ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::AppNotificationNotFound);
}

void BaseTestSuite::VerifyFailedUpdateNotificationDataWithoutPostToast()
{
    AppNotificationProgressData progressData{ GetToastProgressData(L"Status", L"Title", 0.14, L"14%", 1) };

    auto progressResultOperation{ AppNotificationManager::Default().UpdateAsync(progressData, L"NonExistentTag", L"NonExistentGroup") };
    ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::AppNotificationNotFound);
}

void BaseTestSuite::VerifyGetAllAsyncWithZeroActiveToast()
{
    auto retrieveNotificationsAsync{ AppNotificationManager::Default().GetAllAsync() };
    auto scope_exit = wil::scope_exit(
    [&] {
        retrieveNotificationsAsync.Cancel();
    });

    VERIFY_ARE_EQUAL(retrieveNotificationsAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Completed);
    scope_exit.release();

    VERIFY_ARE_EQUAL(retrieveNotificationsAsync.GetResults().Size(), 0u);
}

void BaseTestSuite::VerifyGetAllAsyncWithOneActiveToast()
{
    RegisterWithAppNotificationManager();
    AppNotification toast{ CreateToastNotification(L"MyOwnLittleToast") };
    toast.Tag(L"aDifferentTag");
    toast.Group(L"aDifferentGroup");
    winrt::DateTime expirationTime{ winrt::clock::now() };
    expirationTime += winrt::TimeSpan{ std::chrono::seconds(10) };
    toast.Expiration(expirationTime);
    toast.ExpiresOnReboot(true);
    toast.Priority(winrt::AppNotificationPriority::High);
    toast.SuppressDisplay(true);

    AppNotificationProgressData progressData = GetToastProgressData(L"Status", L"Title", 0.14, L"14%", 1);
    toast.Progress(progressData);

    AppNotificationManager::Default().Show(toast);
    std::vector<AppNotification> toastVector{ toast };
    VERIFY_IS_TRUE(VerifyToastsPosted(toastVector));

    auto retrieveNotificationsAsync{ AppNotificationManager::Default().GetAllAsync() };
    auto scope_exit = wil::scope_exit(
        [&] {
            retrieveNotificationsAsync.Cancel();
        });

    VERIFY_ARE_EQUAL(retrieveNotificationsAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Completed);
    scope_exit.release();

    auto notifications{ retrieveNotificationsAsync.GetResults() };
    VERIFY_ARE_EQUAL(notifications.Size(), 1u);

    auto actual = notifications.GetAt(0);
    return VerifyToastNotificationIsValid(toast, actual, ExpectedTransientProperties::DEFAULT);
}

void BaseTestSuite::VerifyGetAllAsyncWithMultipleActiveToasts()
{
    RegisterWithAppNotificationManager();
    AppNotification toast1{ CreateToastNotification(L"Toast1")};
    AppNotificationManager::Default().Show(toast1);

    AppNotification toast2{ CreateToastNotification(L"Toast2")};
    AppNotificationManager::Default().Show(toast2);

    AppNotification toast3{ CreateToastNotification(L"Toast3")};
    AppNotificationManager::Default().Show(toast3);

    std::vector<AppNotification> toastVector{ toast1, toast2, toast3 };
    VERIFY_IS_TRUE(VerifyToastsPosted(toastVector));
}

void BaseTestSuite::VerifyGetAllAsyncIgnoresUpdatesToProgressData()
{
    RegisterWithAppNotificationManager();
    AppNotification toast{ CreateToastNotification() };
    toast.Tag(L"Tag");
    toast.Group(L"Group");
    AppNotificationProgressData initialProgressData{ GetToastProgressData(L"Initial Status", L"Initial Title", 0.05, L"5%", 1) };
    toast.Progress(initialProgressData);

    AppNotificationManager::Default().Show(toast);

    winrt::AppNotificationProgressData updatedProgressData{ GetToastProgressData(L"Updated Status", L"Updated Title", 0.14, L"14%", 1) };
    auto progressResultOperation{ AppNotificationManager::Default().UpdateAsync(updatedProgressData, L"Tag", L"Group") };
    ProgressResultOperationHelper(progressResultOperation, winrt::AppNotificationProgressResult::Succeeded);

    auto retrieveNotificationsAsync{ AppNotificationManager::Default().GetAllAsync() };
    auto scope_exit = wil::scope_exit(
    [&] {
        retrieveNotificationsAsync.Cancel();
    });

    VERIFY_ARE_EQUAL(retrieveNotificationsAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Completed);
    scope_exit.release();

    auto notifications{ retrieveNotificationsAsync.GetResults() };
    VERIFY_ARE_EQUAL(notifications.Size(), 1u);
    VerifyToastNotificationIsValid(toast, notifications.GetAt(0), ExpectedTransientProperties::EQUAL);
}

void BaseTestSuite::VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier()
{
    auto removeNotificationAsync{ AppNotificationManager::Default().RemoveByIdAsync(0) };

    VERIFY_ARE_EQUAL(removeNotificationAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Error);
    VERIFY_THROWS_HR(removeNotificationAsync.GetResults(), E_INVALIDARG);
    removeNotificationAsync.Cancel();
}

void BaseTestSuite::VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow()
{
    RegisterWithAppNotificationManager();
    auto removeNotificationAsync{ AppNotificationManager::Default().RemoveByIdAsync(1) };
    auto scope_exit = wil::scope_exit(
    [&] {
        removeNotificationAsync.Cancel();
    });

    VERIFY_ARE_EQUAL(removeNotificationAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Completed);
    scope_exit.release();
}

void BaseTestSuite::VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier()
{
    RegisterWithAppNotificationManager();
    winrt::AppNotification toast1{ CreateToastNotification(L"Toast1") };
    AppNotificationManager::Default().Show(toast1);

    winrt::AppNotification toast2{ CreateToastNotification(L"Toast2") };
    AppNotificationManager::Default().Show(toast2);

    winrt::AppNotification toast3{ CreateToastNotification(L"Toast3") };
    AppNotificationManager::Default().Show(toast3);

    std::vector<AppNotification> toastVector{ toast1, toast3, toast2 };
    VERIFY_IS_TRUE(VerifyToastsPosted(toastVector));

    AppNotificationManager::Default().RemoveByIdAsync(toast2.Id()).get();

    // Remove last toast from actual vector
    toastVector.pop_back();
    VERIFY_IS_TRUE(VerifyToastsPosted(toastVector));
}

void BaseTestSuite::VerifyRemoveWithTagAsyncUsingEmptyTagThrows()
{
    VERIFY_THROWS_HR(AppNotificationManager::Default().RemoveByTagAsync(L"").get(), E_INVALIDARG);
}

void BaseTestSuite::VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow()
{
    RegisterWithAppNotificationManager();
    auto removeNotificationAsync{ AppNotificationManager::Default().RemoveByTagAsync(L"NonExistentTag") };
    auto scope_exit = wil::scope_exit(
        [&] {
            removeNotificationAsync.Cancel();
        });

    VERIFY_ARE_EQUAL(removeNotificationAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Completed);
    scope_exit.release();
}

void BaseTestSuite::VerifyRemoveWithTagAsync()
{
    RegisterWithAppNotificationManager();
    winrt::AppNotification toast{ CreateToastNotification() };
    toast.Tag(L"Unique tag");
    AppNotificationManager::Default().Show(toast);

    std::vector<AppNotification> toastVector{ toast };
    VERIFY_IS_TRUE(VerifyToastsPosted(toastVector));

    auto removeNotificationAsync{ AppNotificationManager::Default().RemoveByTagAsync(L"Unique tag") };
    auto scope_exit = wil::scope_exit(
    [&] {
        removeNotificationAsync.Cancel();
    });

    VERIFY_ARE_EQUAL(removeNotificationAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Completed);
    scope_exit.release();

    VERIFY_IS_TRUE(VerifyToastsCleared());
}

void BaseTestSuite::VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows()
{
    VERIFY_THROWS_HR(AppNotificationManager::Default().RemoveByTagAndGroupAsync(L"", L"NonexistentGroup").get(), E_INVALIDARG);
}

void BaseTestSuite::VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows()
{
    VERIFY_THROWS_HR(AppNotificationManager::Default().RemoveByTagAndGroupAsync(L"NonexistentTag", L"").get(), E_INVALIDARG);
}

void BaseTestSuite::VerifyRemoveWithTagGroupAsync()
{
    RegisterWithAppNotificationManager();
    AppNotification toast1{ CreateToastNotification(L"Toast1")};
    toast1.Tag(L"tag1");
    toast1.Group(L"Shared group");
    AppNotificationManager::Default().Show(toast1);

    winrt::AppNotification toast2{ CreateToastNotification(L"Toast2")};
    toast2.Tag(L"tag2");
    toast2.Group(L"Shared group");
    AppNotificationManager::Default().Show(toast2);

    winrt::AppNotification toast3{ CreateToastNotification(L"Toast3")};
    toast3.Tag(L"tag3");
    toast3.Group(L"Shared group");
    AppNotificationManager::Default().Show(toast3);

    std::vector<AppNotification> toastVector{ toast1, toast3, toast2 };
    VERIFY_IS_TRUE(VerifyToastsPosted(toastVector));

    auto removeNotificationAsync{ AppNotificationManager::Default().RemoveByTagAndGroupAsync(L"tag2", L"Shared group") };
    auto scope_exit = wil::scope_exit(
        [&] {
            removeNotificationAsync.Cancel();
        });

    VERIFY_ARE_EQUAL(removeNotificationAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Completed);
    scope_exit.release();

    // Remove last toast from actual vector
    toastVector.pop_back();
    VERIFY_IS_TRUE(VerifyToastsPosted(toastVector));
}

void BaseTestSuite::VerifyRemoveGroupAsyncUsingEmptyGroupThrows()
{
    VERIFY_THROWS_HR(AppNotificationManager::Default().RemoveByGroupAsync(L"").get(), E_INVALIDARG);
}

void BaseTestSuite::VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow()
{
    RegisterWithAppNotificationManager();
    auto removeNotificationAsync{ AppNotificationManager::Default().RemoveByGroupAsync(L"group") };
    auto scope_exit = wil::scope_exit(
        [&] {
            removeNotificationAsync.Cancel();
        });

    VERIFY_ARE_EQUAL(removeNotificationAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Completed);
    scope_exit.release();
}

void BaseTestSuite::VerifyRemoveGroupAsync()
{
    RegisterWithAppNotificationManager();
    winrt::AppNotification toast1{ CreateToastNotification() };
    toast1.Tag(L"tag1");
    toast1.Group(L"Shared group");
    AppNotificationManager::Default().Show(toast1);

    winrt::AppNotification toast2{ CreateToastNotification() };
    toast2.Tag(L"tag2");
    toast2.Group(L"Shared group");
    AppNotificationManager::Default().Show(toast2);

    winrt::AppNotification toast3{ CreateToastNotification() };
    toast3.Tag(L"tag3");
    toast3.Group(L"Shared group");
    AppNotificationManager::Default().Show(toast3);

    std::vector<AppNotification> toastVector{ toast1, toast2, toast3 };
    VERIFY_IS_TRUE(VerifyToastsPosted(toastVector));

    auto removeNotificationAsync{ AppNotificationManager::Default().RemoveByGroupAsync(L"Shared group") };
    auto scope_exit = wil::scope_exit(
        [&] {
            removeNotificationAsync.Cancel();
        });

    VERIFY_ARE_EQUAL(removeNotificationAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Completed);
    scope_exit.release();

    VERIFY_IS_TRUE(VerifyToastsCleared());
}

void BaseTestSuite::VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow()
{
    RegisterWithAppNotificationManager();
    auto removeNotificationAsync{ AppNotificationManager::Default().RemoveAllAsync() };
    auto scope_exit = wil::scope_exit(
        [&] {
            removeNotificationAsync.Cancel();
        });

    VERIFY_ARE_EQUAL(removeNotificationAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Completed);
    scope_exit.release();
}

void BaseTestSuite::VerifyRemoveAllAsync()
{
    RegisterWithAppNotificationManager();
    AppNotification toast1{ CreateToastNotification(L"Toast1")};
    AppNotificationManager::Default().Show(toast1);

    AppNotification toast2{ CreateToastNotification(L"Toast2") };
    AppNotificationManager::Default().Show(toast2);

    AppNotification toast3{ CreateToastNotification(L"Toast3") };
    AppNotificationManager::Default().Show(toast3);

    std::vector<AppNotification> toastVector{ toast1, toast2, toast3 };
    VERIFY_IS_TRUE(VerifyToastsPosted(toastVector));

    auto removeAllAsync{ AppNotificationManager::Default().RemoveAllAsync() };
    auto scopeExitRemoveAll = wil::scope_exit(
        [&] {
            removeAllAsync.Cancel();
        });

    VERIFY_ARE_EQUAL(removeAllAsync.wait_for(c_timeout), winrt::Windows::Foundation::AsyncStatus::Completed);
    scopeExitRemoveAll.release();

    VERIFY_IS_TRUE(VerifyToastsCleared());
}

void BaseTestSuite::VerifyIconPathExists()
{
    RegisterWithAppNotificationManager();
    wil::unique_cotaskmem_string localAppDataPath;

    // TODO: Verify icon from shortcut. If there is no shortcut, verify the process
    // has the icon.
    VERIFY_SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0 /* flags */, nullptr /* access token handle */, &localAppDataPath));

    std::filesystem::path iconFilePath{ std::wstring(localAppDataPath.get()) + c_localWindowsAppSDKFolder + c_appUserModelId + c_pngExtension };
    VERIFY_IS_TRUE(std::filesystem::exists(iconFilePath));

    winrt::AppNotificationManager::Default().UnregisterAll();
    VERIFY_IS_FALSE(std::filesystem::exists(iconFilePath));
}

void BaseTestSuite::VerifyExplicitAppId()
{
    if (!Test::AppModel::IsPackagedProcess())
    {
        // Not mandatory, but it's highly recommended to specify AppUserModelId
        THROW_IF_FAILED(SetCurrentProcessExplicitAppUserModelID(c_appUserModelId.c_str()));
    }

    RegisterWithAppNotificationManager();
    AppNotificationManager::Default().Unregister();
}

void BaseTestSuite::VerifyToastConferencingConfigAllDevicesSet()
{
    if (!AppNotificationConferencingConfig::IsCallingPreviewSupported())
    {
        return;
    }

    AppNotification toast{ CreateToastNotification() };

    AppNotificationConferencingConfig conferencingConfig{};
    conferencingConfig.VideoDeviceId(L"CameraDeviceId");
    conferencingConfig.AudioInputDeviceId(L"MicrophoneDeviceId");
    conferencingConfig.AudioOutputDeviceId(L"SpeakerDeviceId");

    toast.ConferencingConfig(conferencingConfig);

    VERIFY_ARE_EQUAL(toast.ConferencingConfig().VideoDeviceId(), L"CameraDeviceId");
    VERIFY_ARE_EQUAL(toast.ConferencingConfig().AudioInputDeviceId(), L"MicrophoneDeviceId");
    VERIFY_ARE_EQUAL(toast.ConferencingConfig().AudioOutputDeviceId(), L"SpeakerDeviceId");
}

void BaseTestSuite::VerifyToastConferencingConfigNoDevicesSet()
{
    AppNotification toast{ CreateToastNotification() };

    VERIFY_ARE_EQUAL(toast.ConferencingConfig(), nullptr);
}

void BaseTestSuite::VerifyToastConferencingConfigNotAllDevicesSet()
{
    if (!AppNotificationConferencingConfig::IsCallingPreviewSupported())
    {
        return;
    }

    AppNotification toast{ CreateToastNotification() };

    AppNotificationConferencingConfig conferencingConfig{ };
    conferencingConfig.VideoDeviceId(L"CameraDeviceId");

    toast.ConferencingConfig(conferencingConfig);

    VERIFY_ARE_EQUAL(toast.ConferencingConfig().VideoDeviceId(), L"CameraDeviceId");
    VERIFY_ARE_EQUAL(toast.ConferencingConfig().AudioInputDeviceId(), L"");
    VERIFY_ARE_EQUAL(toast.ConferencingConfig().AudioOutputDeviceId(), L"");
}

void BaseTestSuite::VerifyToastConferencingConfigWithIsCallingPreviewSupportedFalse()
{
    AppNotification toast{ CreateToastNotification() };
    AppNotificationConferencingConfig conferencingConfig{ };

    if (!AppNotificationConferencingConfig::IsCallingPreviewSupported())
    {
        VERIFY_THROWS_HR(conferencingConfig.VideoDeviceId(L"CameraDeviceId"), E_NOTIMPL);
        VERIFY_THROWS_HR(conferencingConfig.AudioInputDeviceId(L"MicrophoneDeviceId"), E_NOTIMPL);
        VERIFY_THROWS_HR(conferencingConfig.AudioOutputDeviceId(L"SpeakerDeviceId"), E_NOTIMPL);

        VERIFY_THROWS_HR(toast.ConferencingConfig(conferencingConfig), E_NOTIMPL);
    }
}
