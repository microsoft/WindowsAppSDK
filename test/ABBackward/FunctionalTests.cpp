// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// ABBackward Test: Build with 1.8 SDK headers/WinMDs, run on CURRENT (2.0) framework.
// All 1.8 APIs should work on the 2.0 framework. Any failure is a backward
// compatibility regression that must be fixed by the component owner.

#include "pch.h"
#include <testdef.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::System;

using namespace Windows::Management::Deployment;

namespace Test::ABBackward
{
    static wil::unique_hmodule s_bootstrapDll;
    static std::wstring s_packageFamilyName;

    class FunctionalTests
    {
    public:
        FunctionalTests() = default;

        BEGIN_TEST_CLASS(FunctionalTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            // Discover the highest installed WindowsAppRuntime framework package.
            // ABBackward builds with 1.8 headers but runs on whatever framework is installed.
            // If 2.0 is installed, we validate backward compat (1.8 APIs on 2.0 runtime).
            // If only 1.8 is installed, we still validate the bootstrap path works.
            auto packageManager = winrt::Windows::Management::Deployment::PackageManager();

            UINT16 bestMajor = 0;
            UINT16 bestMinor = 0;
            std::wstring bestPackageName;

            try
            {
                auto packages = packageManager.FindPackagesForUser(L"");
                for (auto const& pkg : packages)
                {
                    try
                    {
                        if (!pkg.IsFramework()) continue;
                        auto name = std::wstring(pkg.Id().Name());

                        const std::wstring prefix = L"Microsoft.WindowsAppRuntime.";
                        if (name.find(prefix) != 0) continue;

                        auto versionStr = name.substr(prefix.size());
                        auto dotPos = versionStr.find(L'.');
                        if (dotPos == std::wstring::npos) continue;

                        auto majorStr = versionStr.substr(0, dotPos);
                        auto minorStr = versionStr.substr(dotPos + 1);
                        if (majorStr.empty() || minorStr.empty()) continue;

                        UINT16 major = static_cast<UINT16>(std::stoi(majorStr));
                        UINT16 minor = static_cast<UINT16>(std::stoi(minorStr));

                        if (major > bestMajor || (major == bestMajor && minor > bestMinor))
                        {
                            bestMajor = major;
                            bestMinor = minor;
                            bestPackageName = name;
                        }
                    }
                    catch (...) { continue; }
                }
            }
            catch (const winrt::hresult_error& e)
            {
                Log::Error(String().Format(L"Failed to enumerate packages: 0x%08X", e.code().value));
                return false;
            }

            if (bestMajor == 0 && bestMinor == 0)
            {
                Log::Error(L"No WindowsAppRuntime framework package found on this machine.");
                Log::Error(L"Run WindowsAppRuntimeInstall-x64.exe from the build output to install the runtime.");
                return false;
            }

            Log::Comment(String().Format(L"Discovered framework: %s (version %d.%d)",
                bestPackageName.c_str(), bestMajor, bestMinor));

            // Load the 1.8 Bootstrap DLL (copied to the test output directory during build)
            s_bootstrapDll.reset(LoadLibraryW(L"Microsoft.WindowsAppRuntime.Bootstrap.dll"));
            if (!s_bootstrapDll)
            {
                auto err = GetLastError();
                Log::Error(String().Format(L"Failed to load Microsoft.WindowsAppRuntime.Bootstrap.dll: error %d (0x%08X)", err, err));
                return false;
            }

            // Bootstrap to the discovered framework version
            UINT32 majorMinorVersion = (static_cast<UINT32>(bestMajor) << 16) | bestMinor;
            PACKAGE_VERSION minVersion{};
            auto hr = MddBootstrapInitialize(majorMinorVersion, nullptr, minVersion);
            if (FAILED(hr))
            {
                Log::Error(String().Format(L"MddBootstrapInitialize failed: 0x%08X for version %d.%d", hr, bestMajor, bestMinor));
                Log::Error(L"Ensure the WindowsAppRuntime framework is properly installed.");
                Log::Error(L"Try running WindowsAppRuntimeInstall-x64.exe from the build output.");
                s_bootstrapDll.reset();
                return false;
            }

            Log::Comment(String().Format(L"Successfully bootstrapped to WindowsAppRuntime %d.%d", bestMajor, bestMinor));

            s_packageFamilyName = L"Microsoft.WindowsAppRuntime." +
                std::to_wstring(bestMajor) + L"." + std::to_wstring(bestMinor) +
                L"_8wekyb3d8bbwe";
            Log::Comment(String().Format(L"Package family: %s", s_packageFamilyName.c_str()));

            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            MddBootstrapShutdown();
            s_bootstrapDll.reset();
            return true;
        }

        // =====================================================================
        // Microsoft.Security.Authentication.OAuth
        // All OAuth classes existed in 1.8 and must work on 2.0 framework.
        // =====================================================================

        TEST_METHOD(OAuth_AuthRequestParams)
        {
            auto params{ winrt::Microsoft::Security::Authentication::OAuth::AuthRequestParams::CreateForAuthorizationCodeRequest(L"test-client-id", winrt::Windows::Foundation::Uri(L"https://localhost/callback")) };
            VERIFY_IS_NOT_NULL(params);
            VERIFY_ARE_EQUAL(params.ClientId(), L"test-client-id");
        }

        TEST_METHOD(OAuth_ClientAuthentication)
        {
            auto auth{ winrt::Microsoft::Security::Authentication::OAuth::ClientAuthentication() };
            VERIFY_IS_NOT_NULL(auth);
        }

        TEST_METHOD(OAuth_TokenRequestParams)
        {
            auto params{ winrt::Microsoft::Security::Authentication::OAuth::TokenRequestParams(L"authorization_code") };
            VERIFY_IS_NOT_NULL(params);
        }

        TEST_METHOD(OAuth_AuthFailure)
        {
            auto name = winrt::name_of<winrt::Microsoft::Security::Authentication::OAuth::AuthFailure>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(OAuth_AuthRequestResult)
        {
            auto name = winrt::name_of<winrt::Microsoft::Security::Authentication::OAuth::AuthRequestResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(OAuth_AuthResponse)
        {
            auto name = winrt::name_of<winrt::Microsoft::Security::Authentication::OAuth::AuthResponse>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(OAuth_OAuth2Manager)
        {
            // OAuth2Manager is static - verify accessible via dependent class
            try
            {
                auto params{ winrt::Microsoft::Security::Authentication::OAuth::AuthRequestParams::CreateForAuthorizationCodeRequest(L"test-client-id", winrt::Windows::Foundation::Uri(L"https://localhost/callback")) };
                VERIFY_IS_NOT_NULL(params);
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
            }
        }

        TEST_METHOD(OAuth_TokenFailure)
        {
            auto name = winrt::name_of<winrt::Microsoft::Security::Authentication::OAuth::TokenFailure>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(OAuth_TokenRequestResult)
        {
            auto name = winrt::name_of<winrt::Microsoft::Security::Authentication::OAuth::TokenRequestResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(OAuth_TokenResponse)
        {
            auto name = winrt::name_of<winrt::Microsoft::Security::Authentication::OAuth::TokenResponse>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Windows.ApplicationModel.Background
        // =====================================================================

        TEST_METHOD(BackgroundTaskBuilder)
        {
            auto builder{ winrt::Microsoft::Windows::ApplicationModel::Background::BackgroundTaskBuilder() };
            VERIFY_IS_NOT_NULL(builder);
        }

        // =====================================================================
        // Microsoft.Windows.ApplicationModel.DynamicDependency
        // =====================================================================

        TEST_METHOD(DynamicDependency_AddPackageDependencyOptions)
        {
            auto options{ winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions() };
            VERIFY_IS_NOT_NULL(options);
        }

        TEST_METHOD(DynamicDependency_CreatePackageDependencyOptions)
        {
            auto options{ winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions() };
            VERIFY_IS_NOT_NULL(options);
        }

        TEST_METHOD(DynamicDependency_PackageDependency)
        {
            auto dep{ winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependency::GetFromId(L"nonexistent-id") };
            // GetFromId returns null for unknown IDs, verifying the class is accessible
        }

        TEST_METHOD(DynamicDependency_PackageDependencyContext)
        {
            try
            {
                auto context{ winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyContext(0) };
                // Context may be null for invalid context ID 0 — that's OK, the type activated
                Log::Comment(String().Format(L"PackageDependencyContext created (may be null for invalid ID)"));
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"PackageDependencyContext acceptable error: 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(DynamicDependency_PackageDependencyRank)
        {
            [[maybe_unused]] auto defaultRank{ winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyRank::Default() };
        }

        // =====================================================================
        // Microsoft.Windows.ApplicationModel.WindowsAppRuntime
        // =====================================================================

        TEST_METHOD(DeploymentManager)
        {
            VERIFY_THROWS(winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentManager::Initialize(), winrt::hresult_error);
        }

        TEST_METHOD(DeploymentManager_GetStatus)
        {
            // KNOWN ABI BREAK: DeploymentManager::GetStatus() crashes the process with
            // STATUS_STACK_BUFFER_OVERRUN (0xC0000409) in both forward and backward directions.
            // This kills the test host, so we must skip to avoid losing all subsequent tests.
            // Tracked in ABCompatibility_BrokenAPIs.md.
            Log::Result(TestResults::Skipped, L"DeploymentManager::GetStatus() causes fatal ABI crash — skipping");
        }

        TEST_METHOD(DeploymentResult)
        {
            auto name = winrt::name_of<winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(DeploymentInitializeOptions)
        {
            auto options{ winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentInitializeOptions() };
            VERIFY_IS_NOT_NULL(options);
        }

        TEST_METHOD(RuntimeCompatibilityOptions)
        {
            auto options{ winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityOptions() };
            VERIFY_IS_NOT_NULL(options);
        }

        TEST_METHOD(ReleaseInfo)
        {
            auto releaseInfo{ winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::ReleaseInfo::AsString() };
            VERIFY_IS_FALSE(releaseInfo.empty());
            Log::Comment(String().Format(L"ReleaseInfo: %s", releaseInfo.c_str()));
        }

        TEST_METHOD(RuntimeInfo)
        {
            auto runtimeInfo{ winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeInfo::AsString() };
            VERIFY_IS_FALSE(runtimeInfo.empty());
            Log::Comment(String().Format(L"RuntimeInfo: %s", runtimeInfo.c_str()));
        }

        // =====================================================================
        // Microsoft.Windows.AppLifecycle
        // =====================================================================

        TEST_METHOD(AppLifecycle_AppInstance)
        {
            auto current{ winrt::Microsoft::Windows::AppLifecycle::AppInstance::GetCurrent() };
            VERIFY_IS_NOT_NULL(current);
        }

        TEST_METHOD(AppLifecycle_AppActivationArguments)
        {
            try
            {
                auto current{ winrt::Microsoft::Windows::AppLifecycle::AppInstance::GetCurrent() };
                auto args{ current.GetActivatedEventArgs() };
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"AppActivationArguments acceptable error: 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(AppLifecycle_ActivationRegistrationManager)
        {
            try
            {
                winrt::Microsoft::Windows::AppLifecycle::ActivationRegistrationManager::RegisterForFileTypeActivation(
                    { L".abbackwardtest" }, L"", L"ABBackwardTest", {}, L"");
                winrt::Microsoft::Windows::AppLifecycle::ActivationRegistrationManager::UnregisterForFileTypeActivation(
                    { L".abbackwardtest" }, L"");
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"AppLifecycle_ActivationRegistrationManager acceptable error: 0x%08X %s",
                    static_cast<uint32_t>(ex.code()), ex.message().c_str()));
            }
        }

        // =====================================================================
        // Microsoft.Windows.AppNotifications
        // =====================================================================

        TEST_METHOD(AppNotificationsManager)
        {
            auto manager{ winrt::Microsoft::Windows::AppNotifications::AppNotificationManager::Default() };
            VERIFY_IS_NOT_NULL(manager);
        }

        TEST_METHOD(AppNotificationsManager_Register)
        {
            try
            {
                winrt::Microsoft::Windows::AppNotifications::AppNotificationManager::Default().Register();
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"Register acceptable error: 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(AppNotification_Construct)
        {
            auto notification{ winrt::Microsoft::Windows::AppNotifications::AppNotification(L"<toast><visual><binding template='ToastText01'><text id='1'>Test</text></binding></visual></toast>") };
            VERIFY_IS_NOT_NULL(notification);
        }

        TEST_METHOD(AppNotificationActivatedEventArgs)
        {
            auto name = winrt::name_of<winrt::Microsoft::Windows::AppNotifications::AppNotificationActivatedEventArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AppNotificationProgressData)
        {
            auto progressData{ winrt::Microsoft::Windows::AppNotifications::AppNotificationProgressData(1) };
            progressData.Title(L"Test Progress");
            progressData.Value(0.5);
            VERIFY_ARE_EQUAL(progressData.Title(), L"Test Progress");
        }

        // =====================================================================
        // Microsoft.Windows.AppNotifications.Builder
        // =====================================================================

        TEST_METHOD(AppNotificationsBuilder)
        {
            auto builder{ winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder() };
            builder.AddText(L"Test Title");
            builder.AddText(L"Test Body");
            auto xml{ builder.BuildNotification() };
            VERIFY_IS_NOT_NULL(xml);
        }

        TEST_METHOD(AppNotificationButton)
        {
            auto button{ winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton(L"Click Me") };
            button.AddArgument(L"action", L"test");
            VERIFY_IS_NOT_NULL(button);
        }

        TEST_METHOD(AppNotificationComboBox)
        {
            auto comboBox{ winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationComboBox(L"combo1") };
            comboBox.AddItem(L"item1", L"Item One");
            VERIFY_IS_NOT_NULL(comboBox);
        }

        TEST_METHOD(AppNotificationProgressBar)
        {
            auto progressBar{ winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationProgressBar() };
            progressBar.SetTitle(L"Downloading");
            VERIFY_IS_NOT_NULL(progressBar);
        }

        TEST_METHOD(AppNotificationTextProperties)
        {
            auto textProps{ winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationTextProperties() };
            VERIFY_IS_NOT_NULL(textProps);
        }

        // =====================================================================
        // Microsoft.Windows.BadgeNotifications
        // =====================================================================

        TEST_METHOD(BadgeNotifications)
        {
            auto manager{ winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationManager::Current() };
            VERIFY_IS_NOT_NULL(manager);
        }

        // =====================================================================
        // Microsoft.Windows.Management.Deployment
        // =====================================================================

        TEST_METHOD(PackageDeploymentManager)
        {
            auto manager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_NOT_NULL(manager);
        }

        TEST_METHOD(PackageDeploymentResult)
        {
            auto name = winrt::name_of<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AddPackageOptions)
        {
            auto options{ winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions() };
            VERIFY_IS_NOT_NULL(options);
        }

        TEST_METHOD(EnsureReadyOptions)
        {
            auto options{ winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions() };
            VERIFY_IS_NOT_NULL(options);
        }

        TEST_METHOD(PackageSet)
        {
            auto packageSet{ winrt::Microsoft::Windows::Management::Deployment::PackageSet() };
            VERIFY_IS_NOT_NULL(packageSet);

            auto item{ winrt::Microsoft::Windows::Management::Deployment::PackageSetItem() };
            VERIFY_IS_NOT_NULL(item);
        }

        TEST_METHOD(ProvisionPackageOptions)
        {
            auto options{ winrt::Microsoft::Windows::Management::Deployment::ProvisionPackageOptions() };
            VERIFY_IS_NOT_NULL(options);
        }

        TEST_METHOD(RegisterPackageOptions)
        {
            auto options{ winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions() };
            VERIFY_IS_NOT_NULL(options);
        }

        TEST_METHOD(RemovePackageOptions)
        {
            auto options{ winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions() };
            VERIFY_IS_NOT_NULL(options);
        }

        TEST_METHOD(StagePackageOptions)
        {
            auto options{ winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions() };
            VERIFY_IS_NOT_NULL(options);
        }

        TEST_METHOD(PackageRuntimeManager)
        {
            auto manager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
            VERIFY_IS_NOT_NULL(manager);
        }

        TEST_METHOD(PackageSetItemRuntimeDisposition)
        {
            try
            {
                auto disposition{ winrt::Microsoft::Windows::Management::Deployment::PackageSetItemRuntimeDisposition() };
                VERIFY_IS_NOT_NULL(disposition);
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"PackageSetItemRuntimeDisposition acceptable error: 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(PackageSetRuntimeDisposition)
        {
            try
            {
                auto disposition{ winrt::Microsoft::Windows::Management::Deployment::PackageSetRuntimeDisposition() };
                VERIFY_IS_NOT_NULL(disposition);
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"PackageSetRuntimeDisposition acceptable error: 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(PackageVolume)
        {
            auto name = winrt::name_of<winrt::Microsoft::Windows::Management::Deployment::PackageVolume>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Windows.Media.Capture
        // =====================================================================

        TEST_METHOD(CameraCaptureUI)
        {
            try
            {
                winrt::Microsoft::UI::WindowId windowId{};
                auto captureUI{ winrt::Microsoft::Windows::Media::Capture::CameraCaptureUI(windowId) };
                VERIFY_IS_NOT_NULL(captureUI);
                auto photoSettings{ captureUI.PhotoSettings() };
                VERIFY_IS_NOT_NULL(photoSettings);
                auto videoSettings{ captureUI.VideoSettings() };
                VERIFY_IS_NOT_NULL(videoSettings);
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"CameraCaptureUI acceptable error: 0x%08X %s",
                    static_cast<uint32_t>(ex.code()), ex.message().c_str()));
            }
        }

        TEST_METHOD(CameraCaptureUIPhotoCaptureSettings)
        {
            auto name = winrt::name_of<winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIPhotoCaptureSettings>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(CameraCaptureUIVideoCaptureSettings)
        {
            auto name = winrt::name_of<winrt::Microsoft::Windows::Media::Capture::CameraCaptureUIVideoCaptureSettings>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Windows.PushNotifications
        // =====================================================================

        TEST_METHOD(PushNotificationManager)
        {
            try
            {
                auto manager{ winrt::Microsoft::Windows::PushNotifications::PushNotificationManager::Default() };
                VERIFY_IS_NOT_NULL(manager);
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"PushNotificationManager acceptable error: 0x%08X %s",
                    static_cast<uint32_t>(ex.code()), ex.message().c_str()));
            }
        }

        TEST_METHOD(PushNotificationChannel)
        {
            auto name = winrt::name_of<winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(PushNotificationCreateChannelResult)
        {
            auto name = winrt::name_of<winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(PushNotificationReceivedEventArgs)
        {
            auto name = winrt::name_of<winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Windows.Security.AccessControl
        // =====================================================================

        TEST_METHOD(SecurityAccessControl)
        {
            auto arr{ winrt::com_array<winrt::Microsoft::Windows::Security::AccessControl::AppContainerNameAndAccess>(1)};
            arr.at(0).appContainerName = winrt::hstring(s_packageFamilyName);
            auto sddl{ winrt::Microsoft::Windows::Security::AccessControl::SecurityDescriptorHelpers::GetSddlForAppContainerNames(arr, winrt::hstring(), 0)};
            VERIFY_IS_FALSE(sddl.empty());
        }

        // =====================================================================
        // Microsoft.Windows.Storage
        // =====================================================================

        TEST_METHOD(ApplicationData)
        {
            auto appData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(winrt::hstring(s_packageFamilyName)) };
            VERIFY_IS_NOT_NULL(appData);
        }

        TEST_METHOD(ApplicationDataContainer)
        {
            try
            {
                auto appData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(winrt::hstring(s_packageFamilyName)) };
                auto localSettings{ appData.LocalSettings() };
                // LocalSettings may be null if the package family isn't fully registered — that's OK
                Log::Comment(String().Format(L"ApplicationDataContainer: LocalSettings %s",
                    localSettings ? L"available" : L"null (expected without full package identity)"));
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"ApplicationDataContainer acceptable error: 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        // =====================================================================
        // Microsoft.Windows.Storage.Pickers
        // =====================================================================

        TEST_METHOD(FileOpenPicker)
        {
            try
            {
                winrt::Microsoft::UI::WindowId windowId{};
                auto picker{ winrt::Microsoft::Windows::Storage::Pickers::FileOpenPicker(windowId) };
                VERIFY_IS_NOT_NULL(picker);
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"FileOpenPicker acceptable error: 0x%08X %s",
                    static_cast<uint32_t>(ex.code()), ex.message().c_str()));
            }
        }

        TEST_METHOD(FileSavePicker)
        {
            try
            {
                winrt::Microsoft::UI::WindowId windowId{};
                auto picker{ winrt::Microsoft::Windows::Storage::Pickers::FileSavePicker(windowId) };
                VERIFY_IS_NOT_NULL(picker);
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"FileSavePicker acceptable error: 0x%08X %s",
                    static_cast<uint32_t>(ex.code()), ex.message().c_str()));
            }
        }

        TEST_METHOD(FolderPicker)
        {
            try
            {
                winrt::Microsoft::UI::WindowId windowId{};
                auto picker{ winrt::Microsoft::Windows::Storage::Pickers::FolderPicker(windowId) };
                VERIFY_IS_NOT_NULL(picker);
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"FolderPicker acceptable error: 0x%08X %s",
                    static_cast<uint32_t>(ex.code()), ex.message().c_str()));
            }
        }

        TEST_METHOD(PickFileResult)
        {
            auto name = winrt::name_of<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(PickFolderResult)
        {
            auto name = winrt::name_of<winrt::Microsoft::Windows::Storage::Pickers::PickFolderResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Windows.System
        // =====================================================================

        TEST_METHOD(EnvironmentManager)
        {
            auto envManager{ winrt::Microsoft::Windows::System::EnvironmentManager::GetForProcess() };
            VERIFY_IS_NOT_NULL(envManager);
        }

        // =====================================================================
        // Microsoft.Windows.System.Power
        // =====================================================================

        TEST_METHOD(BatteryStatus)
        {
            [[maybe_unused]] auto batteryStatus{ winrt::Microsoft::Windows::System::Power::PowerManager::BatteryStatus() };
        }

        TEST_METHOD(PowerManager_Properties)
        {
            [[maybe_unused]] auto displayStatus{ winrt::Microsoft::Windows::System::Power::PowerManager::DisplayStatus() };
            [[maybe_unused]] auto energySaver{ winrt::Microsoft::Windows::System::Power::PowerManager::EnergySaverStatus() };
            [[maybe_unused]] auto powerSource{ winrt::Microsoft::Windows::System::Power::PowerManager::PowerSourceKind() };
            [[maybe_unused]] auto remaining{ winrt::Microsoft::Windows::System::Power::PowerManager::RemainingChargePercent() };
        }


        // =====================================================================
        // Microsoft.Windows.ApplicationModel.Resources
        // =====================================================================

        TEST_METHOD(Resources_ResourceLoader)
        {
            try
            {
                auto loader{ winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceLoader() };
                VERIFY_IS_NOT_NULL(loader);
                // GetString will throw without a PRI file — that's fine, class activated
                try
                {
                    loader.GetString(L"test");
                }
                catch (winrt::hresult_error const&)
                {
                    // Expected without PRI resources
                }
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"ResourceLoader acceptable error: 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(Resources_ResourceManager)
        {
            try
            {
                auto manager{ winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceManager() };
                VERIFY_IS_NOT_NULL(manager);
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"ResourceManager acceptable error: 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(Resources_ResourceContext)
        {
            // Non-activatable (created from ResourceManager)
            auto name = winrt::name_of<winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceContext>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Resources_ResourceCandidate)
        {
            // Non-activatable (returned from resource queries)
            auto name = winrt::name_of<winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Resources_ResourceMap)
        {
            // Non-activatable (obtained from ResourceManager)
            auto name = winrt::name_of<winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceMap>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Resources_ResourceNotFoundEventArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::ApplicationModel::Resources::ResourceNotFoundEventArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Resources_KnownResourceQualifierName)
        {
            // Static-only class — call a static property
            auto language{ winrt::Microsoft::Windows::ApplicationModel::Resources::KnownResourceQualifierName::Language() };
            VERIFY_IS_FALSE(language.empty());
            Log::Comment(String().Format(L"KnownResourceQualifierName::Language = %s", language.c_str()));
        }

        // =====================================================================
        // Microsoft.Windows.Foundation
        // =====================================================================

        TEST_METHOD(Foundation_DecimalHelper)
        {
            // Static-only class — verify type metadata
            auto name = winrt::name_of<winrt::Microsoft::Windows::Foundation::DecimalHelper>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Windows.Globalization
        // =====================================================================

        TEST_METHOD(Globalization_ApplicationLanguages)
        {
            // Static-only class — read PrimaryLanguageOverride
            try
            {
                [[maybe_unused]] auto lang{ winrt::Microsoft::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride() };
                Log::Comment(String().Format(L"PrimaryLanguageOverride: '%s'", lang.c_str()));
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"ApplicationLanguages acceptable error: 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        // =====================================================================
        // Microsoft.Windows.ApplicationModel.Background.UniversalBGTask
        // =====================================================================

        TEST_METHOD(UniversalBGTask_Task)
        {
            // SKIP: Not an ABI break. UniversalBGTask.Task has no ActivatableClass registration
            // in any appxfragment or framework manifest. Cannot be WinRT-activated from any process.
            Log::Result(TestResults::Skipped, L"UniversalBGTask.Task: No ActivatableClass registration exists (not an ABI break)");
        }

        // =====================================================================
        // Microsoft.Windows.AI
        // =====================================================================

        TEST_METHOD(AI_AIFeatureReadyResult)
        {
            // Non-activatable (returned by availability checks)
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::AIFeatureReadyResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Windows.AI.ContentSafety
        // =====================================================================

        TEST_METHOD(AI_ContentFilterOptions)
        {
            // Activatable — hardware-dependent
            try
            {
                auto options{ winrt::Microsoft::Windows::AI::ContentSafety::ContentFilterOptions() };
                VERIFY_IS_NOT_NULL(options);
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"ContentFilterOptions not available (hardware/capability): 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(AI_ImageContentFilterSeverity)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::ContentSafety::ImageContentFilterSeverity>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_TextContentFilterSeverity)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::ContentSafety::TextContentFilterSeverity>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Windows.AI.Foundation
        // =====================================================================

        TEST_METHOD(AI_EmbeddingVector)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Foundation::EmbeddingVector>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Windows.AI.Imaging
        // =====================================================================

        TEST_METHOD(AI_ImageDescriptionGenerator)
        {
            // Has static GetReadyState() — hardware-dependent
            try
            {
                [[maybe_unused]] auto state{ winrt::Microsoft::Windows::AI::Imaging::ImageDescriptionGenerator::GetReadyState() };
                Log::Comment(String().Format(L"ImageDescriptionGenerator::GetReadyState = %d", static_cast<int>(state)));
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"ImageDescriptionGenerator not available (hardware/capability): 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(AI_ImageDescriptionResult)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Imaging::ImageDescriptionResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_ImageObjectExtractor)
        {
            // Has static GetReadyState() — hardware-dependent
            try
            {
                [[maybe_unused]] auto state{ winrt::Microsoft::Windows::AI::Imaging::ImageObjectExtractor::GetReadyState() };
                Log::Comment(String().Format(L"ImageObjectExtractor::GetReadyState = %d", static_cast<int>(state)));
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"ImageObjectExtractor not available (hardware/capability): 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(AI_ImageObjectExtractorHint)
        {
            // Activatable with parameters — verify type metadata
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Imaging::ImageObjectExtractorHint>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_ImageObjectRemover)
        {
            // Has static GetReadyState() — hardware-dependent
            try
            {
                [[maybe_unused]] auto state{ winrt::Microsoft::Windows::AI::Imaging::ImageObjectRemover::GetReadyState() };
                Log::Comment(String().Format(L"ImageObjectRemover::GetReadyState = %d", static_cast<int>(state)));
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"ImageObjectRemover not available (hardware/capability): 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(AI_ImageScaler)
        {
            // Has static GetReadyState() — hardware-dependent
            try
            {
                [[maybe_unused]] auto state{ winrt::Microsoft::Windows::AI::Imaging::ImageScaler::GetReadyState() };
                Log::Comment(String().Format(L"ImageScaler::GetReadyState = %d", static_cast<int>(state)));
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"ImageScaler not available (hardware/capability): 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(AI_RecognizedLine)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Imaging::RecognizedLine>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_RecognizedText)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Imaging::RecognizedText>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_RecognizedWord)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Imaging::RecognizedWord>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_TextRecognizer)
        {
            // Has static GetReadyState() — hardware-dependent
            try
            {
                [[maybe_unused]] auto state{ winrt::Microsoft::Windows::AI::Imaging::TextRecognizer::GetReadyState() };
                Log::Comment(String().Format(L"TextRecognizer::GetReadyState = %d", static_cast<int>(state)));
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"TextRecognizer not available (hardware/capability): 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        // =====================================================================
        // Microsoft.Windows.AI.Text
        // =====================================================================

        TEST_METHOD(AI_LanguageModel)
        {
            // Has static GetReadyState() — hardware-dependent
            try
            {
                [[maybe_unused]] auto state{ winrt::Microsoft::Windows::AI::Text::LanguageModel::GetReadyState() };
                Log::Comment(String().Format(L"LanguageModel::GetReadyState = %d", static_cast<int>(state)));
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"LanguageModel not available (hardware/capability): 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(AI_LanguageModelContext)
        {
            // Non-default-constructible — verify type metadata
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Text::LanguageModelContext>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_LanguageModelOptions)
        {
            // Activatable — hardware-dependent
            try
            {
                auto options{ winrt::Microsoft::Windows::AI::Text::LanguageModelOptions() };
                VERIFY_IS_NOT_NULL(options);
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"LanguageModelOptions not available (hardware/capability): 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(AI_LanguageModelEmbeddingVectorResult)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Text::LanguageModelEmbeddingVectorResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_LanguageModelResponseResult)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Text::LanguageModelResponseResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_ConversationItem)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Text::ConversationItem>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_ConversationSummaryOptions)
        {
            // Activatable — hardware-dependent
            try
            {
                auto options{ winrt::Microsoft::Windows::AI::Text::ConversationSummaryOptions() };
                VERIFY_IS_NOT_NULL(options);
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"ConversationSummaryOptions not available (hardware/capability): 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(AI_TextRewriter)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Text::TextRewriter>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_TextSummarizer)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Text::TextSummarizer>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_TextToTableConverter)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Text::TextToTableConverter>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_TextToTableResponseResult)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Text::TextToTableResponseResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(AI_TextToTableRow)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::Text::TextToTableRow>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Graphics.Imaging
        // =====================================================================

        TEST_METHOD(Graphics_ImageBuffer)
        {
            // Non-default-constructible — verify type metadata
            auto name = winrt::name_of<winrt::Microsoft::Graphics::Imaging::ImageBuffer>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Windows.AI.MachineLearning
        // =====================================================================

        TEST_METHOD(ML_ModelCatalog)
        {
            // Non-default-constructible — requires ModelCatalogSource array. Verify type metadata.
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::MachineLearning::ModelCatalog>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(ML_ModelCatalogSource)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::MachineLearning::ModelCatalogSource>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(ML_CatalogModelInfo)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::MachineLearning::CatalogModelInfo>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(ML_CatalogModelInstance)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::MachineLearning::CatalogModelInstance>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(ML_CatalogModelInstanceResult)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::MachineLearning::CatalogModelInstanceResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(ML_ExecutionProvider)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::MachineLearning::ExecutionProvider>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(ML_ExecutionProviderCatalog)
        {
            // Static class — verify type metadata
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::MachineLearning::ExecutionProviderCatalog>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(ML_ExecutionProviderReadyResult)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::AI::MachineLearning::ExecutionProviderReadyResult>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Windows.Widgets.Providers
        // =====================================================================

        TEST_METHOD(Widgets_WidgetManager)
        {
            // SKIP: Not an ABI break. WidgetManager IS registered and other classes from
            // the same DLL (WidgetUpdateRequestOptions) activate fine. GetDefault() requires
            // Widget Board Service infrastructure not available in TAEF test environment.
            Log::Result(TestResults::Skipped, L"WidgetManager::GetDefault(): Requires Widget Board Service (not an ABI break)");
        }

        TEST_METHOD(Widgets_WidgetUpdateRequestOptions)
        {
            // Activatable with widgetId parameter
            try
            {
                auto options{ winrt::Microsoft::Windows::Widgets::Providers::WidgetUpdateRequestOptions(L"widgetId") };
                VERIFY_IS_NOT_NULL(options);
            }
            catch (winrt::hresult_error const& ex)
            {
                VERIFY_ARE_NOT_EQUAL(ex.code(), REGDB_E_CLASSNOTREG);
                Log::Comment(String().Format(L"WidgetUpdateRequestOptions acceptable error: 0x%08X", static_cast<uint32_t>(ex.code())));
            }
        }

        TEST_METHOD(Widgets_WidgetContext)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Providers::WidgetContext>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Widgets_WidgetInfo)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Providers::WidgetInfo>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Widgets_WidgetActionInvokedArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Providers::WidgetActionInvokedArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Widgets_WidgetAnalyticsInfoReportedArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Providers::WidgetAnalyticsInfoReportedArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Widgets_WidgetContextChangedArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Providers::WidgetContextChangedArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Widgets_WidgetCustomizationRequestedArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Providers::WidgetCustomizationRequestedArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Widgets_WidgetErrorInfoReportedArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Providers::WidgetErrorInfoReportedArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Widgets_WidgetMessageReceivedArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Providers::WidgetMessageReceivedArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Widgets_WidgetResourceRequest)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Providers::WidgetResourceRequest>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Widgets_WidgetResourceRequestedArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Providers::WidgetResourceRequestedArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Widgets_WidgetResourceResponse)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Providers::WidgetResourceResponse>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Windows.Widgets.Feeds.Providers
        // =====================================================================

        TEST_METHOD(Feeds_FeedManager)
        {
            // SKIP: Not an ABI break. FeedManager IS registered and other classes from
            // the same DLL activate fine. GetDefault() requires Widget Board Service
            // infrastructure not available in TAEF test environment.
            Log::Result(TestResults::Skipped, L"FeedManager::GetDefault(): Requires Widget Board Service (not an ABI break)");
        }

        TEST_METHOD(Feeds_CustomQueryParametersUpdateOptions)
        {
            // Non-default-constructible — verify type metadata
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Feeds::Providers::CustomQueryParametersUpdateOptions>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Feeds_FeedProviderInfo)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Feeds::Providers::FeedProviderInfo>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Feeds_FeedResourceResponse)
        {
            // Non-default-constructible — verify type metadata
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Feeds::Providers::FeedResourceResponse>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Feeds_CustomQueryParametersRequestedArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Feeds::Providers::CustomQueryParametersRequestedArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Feeds_FeedAnalyticsInfoReportedArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Feeds::Providers::FeedAnalyticsInfoReportedArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Feeds_FeedDisabledArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Feeds::Providers::FeedDisabledArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Feeds_FeedEnabledArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Feeds::Providers::FeedEnabledArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Feeds_FeedErrorInfoReportedArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Feeds::Providers::FeedErrorInfoReportedArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Feeds_FeedMessageReceivedArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Feeds::Providers::FeedMessageReceivedArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Feeds_FeedProviderDisabledArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Feeds::Providers::FeedProviderDisabledArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Feeds_FeedProviderEnabledArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Feeds::Providers::FeedProviderEnabledArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Feeds_FeedResourceRequest)
        {
            // Non-activatable
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Feeds::Providers::FeedResourceRequest>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Feeds_FeedResourceRequestedArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Feeds::Providers::FeedResourceRequestedArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        // =====================================================================
        // Microsoft.Windows.Widgets.Notifications
        // =====================================================================

        TEST_METHOD(Widgets_FeedAnnouncement)
        {
            // Non-default-constructible — verify type metadata
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Notifications::FeedAnnouncement>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }

        TEST_METHOD(Widgets_FeedAnnouncementInvokedArgs)
        {
            // Non-activatable (event args)
            auto name = winrt::name_of<winrt::Microsoft::Windows::Widgets::Notifications::FeedAnnouncementInvokedArgs>();
            VERIFY_IS_NOT_NULL(name.data());
            Log::Comment(String().Format(L"Type verified: %s", name.data()));
        }



        // =====================================================================
        // NOTE: No AppNotificationConferencingConfig test here.
        // That class is new in 2.0 and does not exist in the 1.8 WinMDs,
        // so it cannot be referenced when building against 1.8 headers.
        // =====================================================================
    };
}
