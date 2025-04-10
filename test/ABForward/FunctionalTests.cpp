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

namespace Test::ABForward
{
    class FunctionalTests
    {
    private:
        void AddPackages()
        {
            auto packageManager{ Windows::Management::Deployment::PackageManager() };

            auto frameworkPackages{ packageManager.FindPackages(L"Microsoft.WindowsAppRuntime.1.6_8wekyb3d8bbwe") };

            if (!frameworkPackages.First().HasCurrent())
            {
                auto frameworkUri{ Windows::Foundation::Uri(Test::Packages::GetMsixPackagePath(L"Microsoft.WindowsAppRuntime.1.6").c_str()) };
                auto frameworkOp{ packageManager.AddPackageAsync(frameworkUri, nullptr, DeploymentOptions::None) };
                auto frameworkResult{ frameworkOp.get() };
            }

            auto ddlmUri{ Windows::Foundation::Uri(Test::Packages::GetMsixPackagePath(L"Microsoft.WindowsAppRuntime.DDLM.1.6").c_str()) };
            auto ddlmOp{ packageManager.AddPackageAsync(ddlmUri, nullptr, DeploymentOptions::None) };
            auto ddlmResult{ ddlmOp.get() };
        }

    public:
        BEGIN_TEST_CLASS(FunctionalTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            AddPackages();

            const UINT32 c_Version_MajorMinor{ 0x00010006 };
            const PACKAGE_VERSION minVersion{};
            ::Test::Bootstrap::SetupBootstrapWithVersion(c_Version_MajorMinor, minVersion, false);

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

        TEST_METHOD(BatteryStatus)
        {
            auto batteryStatus{ winrt::Microsoft::Windows::System::Power::PowerManager::BatteryStatus() };
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

        TEST_METHOD(DeploymentManager)
        {
            // DeploymentManager fails when there is no Identity
            VERIFY_THROWS(winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::DeploymentManager::DeploymentManager::Initialize(), winrt::hresult_error);
        }
    };
}
