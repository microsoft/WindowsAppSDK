// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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

namespace TP = ::Test::Packages;

#define WASDK_PACKAGE_NAME L"Microsoft.WindowsAppRuntime"
#define WASDK_PUBLISHER L"8wekyb3d8bbwe"

namespace Test::ABForward
{
    class FunctionalTests
    {
    private:
        winrt::hstring packageFamilyName{};

        // TODO(ABForward-diag): Temporary diagnostics to capture the real failure on
        // Win11 24H2/25H2 (see un-bypass in test/BypassTests.json). Revert once root-caused.
        static void WaitAndLogDeployment(PCWSTR stage, PCWSTR uri,
            winrt::Windows::Foundation::IAsyncOperationWithProgress<
                winrt::Windows::Management::Deployment::DeploymentResult,
                winrt::Windows::Management::Deployment::DeploymentProgress> const& op)
        {
            HRESULT getHr{ S_OK };
            try
            {
                op.get();
            }
            catch (winrt::hresult_error const& e)
            {
                getHr = e.code();
            }
            catch (...)
            {
                getHr = E_FAIL;
            }

            HRESULT extendedError{ S_OK };
            winrt::hstring errorText{};
            try
            {
                if (auto result{ op.GetResults() })
                {
                    extendedError = static_cast<HRESULT>(result.ExtendedErrorCode());
                    errorText = result.ErrorText();
                }
            }
            catch (...)
            {
            }

            const auto status{ op.Status() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(
                L"[ABForward] %s: uri=%s asyncStatus=%d getHr=0x%08X extendedError=0x%08X errorText='%s'",
                stage, uri, static_cast<int>(status), getHr, extendedError, errorText.c_str()));
            VERIFY_ARE_EQUAL(winrt::Windows::Foundation::AsyncStatus::Completed, status,
                WEX::Common::String().Format(L"[ABForward] %s deployment failed (getHr=0x%08X extendedError=0x%08X errorText='%s')",
                    stage, getHr, extendedError, errorText.c_str()));
        }

        void AddPackages()
        {
            auto packageManager{ Windows::Management::Deployment::PackageManager() };

            WEX::Logging::Log::Comment(WEX::Common::String().Format(
                L"[ABForward] AddPackages: packageFamilyName='%s'", packageFamilyName.c_str()));

            auto frameworkPackages{ packageManager.FindPackages(packageFamilyName) };

            if (!frameworkPackages.First().HasCurrent())
            {
                const auto frameworkPath{ Test::Packages::GetMsixPackagePath(L"Microsoft.WindowsAppRuntime") };
                auto frameworkUri{ Windows::Foundation::Uri(frameworkPath.c_str()) };
                auto frameworkOp{ packageManager.AddPackageAsync(frameworkUri, nullptr, DeploymentOptions::None) };
                WaitAndLogDeployment(L"Framework", frameworkPath.c_str(), frameworkOp);
            }
            else
            {
                WEX::Logging::Log::Comment(L"[ABForward] Framework already present; skipping install");
            }

            const auto ddlmPath{ Test::Packages::GetMsixPackagePath(L"Microsoft.WindowsAppRuntime.DDLM") };
            auto ddlmUri{ Windows::Foundation::Uri(ddlmPath.c_str()) };
            auto ddlmOp{ packageManager.AddPackageAsync(ddlmUri, nullptr, DeploymentOptions::None) };
            WaitAndLogDeployment(L"DDLM", ddlmPath.c_str(), ddlmOp);
        }

    public:
        FunctionalTests() = default;

        BEGIN_TEST_CLASS(FunctionalTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            packageFamilyName = winrt::hstring(WASDK_PACKAGE_NAME) +
                winrt::hstring(L".") +
                winrt::hstring(std::to_wstring(ABFORWARD_RUNTIME_VERSION_MAJOR)) +
                winrt::hstring(L".") +
                winrt::hstring(std::to_wstring(ABFORWARD_RUNTIME_VERSION_MINOR)) +
                winrt::hstring(L"_") +
                winrt::hstring(WASDK_PUBLISHER);

            AddPackages();

            const UINT32 c_Version_MajorMinor{ ABFORWARD_RUNTIME_VERSION_MAJOR << 16 | ABFORWARD_RUNTIME_VERSION_MINOR };
            const PACKAGE_VERSION minVersion{};
            WEX::Logging::Log::Comment(WEX::Common::String().Format(
                L"[ABForward] Bootstrapping version %d.%d (MajorMinor=0x%08X)",
                ABFORWARD_RUNTIME_VERSION_MAJOR, ABFORWARD_RUNTIME_VERSION_MINOR, c_Version_MajorMinor));
            ::Test::Bootstrap::SetupBootstrapWithVersion(c_Version_MajorMinor, minVersion, false);
            WEX::Logging::Log::Comment(L"[ABForward] Bootstrap succeeded");

            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            ::Test::Bootstrap::Cleanup();
            return true;
        }

        TEST_METHOD(ApplicationData)
        {
            winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(L"Microsoft.WindowsAppRuntime.1.6_8wekyb3d8bbwe");
        }

        TEST_METHOD(AppNotificationsManager)
        {
            winrt::Microsoft::Windows::AppNotifications::AppNotificationManager::Default().Register();
        }

        TEST_METHOD(AppNotificationsBuilder)
        {
            winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationBuilder();
        }

        TEST_METHOD(BackgroundTaskBuilder)
        {
            // BackgroundTaskBuilder is not available in 1.6
            VERIFY_THROWS(winrt::Microsoft::Windows::ApplicationModel::Background::BackgroundTaskBuilder(), winrt::hresult_class_not_registered);
        }

        TEST_METHOD(BadgeNotifications)
        {
            // Badge Notifications is not available in 1.6
            VERIFY_THROWS(winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationManager::Current(), winrt::hresult_class_not_registered);
        }

        TEST_METHOD(BatteryStatus)
        {
            [[maybe_unused]] const auto batteryStatus{ winrt::Microsoft::Windows::System::Power::PowerManager::BatteryStatus() };
        }

        TEST_METHOD(DeploymentManager)
        {
            // DeploymentManager fails when there is no Identity
            VERIFY_THROWS(winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentManager::DeploymentManager::Initialize(), winrt::hresult_error);
        }

        TEST_METHOD(EnvironmentManager)
        {
            auto environmentManager{ winrt::Microsoft::Windows::System::EnvironmentManager::GetForProcess() };
        }

        TEST_METHOD(PackageManager)
        {
            auto packageManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
        }

        TEST_METHOD(RuntimeVersion)
        {
            // RuntimeVersion is not available in 1.6
            VERIFY_THROWS(auto runtimeVersion = winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeInfo::Version(), winrt::hresult_class_not_available);
        }

        TEST_METHOD(RuntimeCompatibilityOptions)
        {
            // RuntimeCompatibilityOptions is not available in 1.6
            VERIFY_THROWS(auto runtimeCompatibilityOptions = winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityOptions::RuntimeCompatibilityOptions(), winrt::hresult_class_not_registered);
        }

        TEST_METHOD(SecurityAccessControl)
        {
            auto arr{ winrt::com_array<winrt::Microsoft::Windows::Security::AccessControl::AppContainerNameAndAccess>(1)};
            arr.at(0).appContainerName = packageFamilyName;
            auto widgetManager{ winrt::Microsoft::Windows::Security::AccessControl::SecurityDescriptorHelpers::GetSddlForAppContainerNames(arr, winrt::hstring(), 0)};
        }
    };
}
