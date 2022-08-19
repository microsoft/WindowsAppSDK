// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <testdef.h>
#include <TerminalVelocityFeatures-DeploymentAPI.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt;
using namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::System;

namespace Test::Deployment
{
    class APITests
    {
    private:

    public:
        BEGIN_TEST_CLASS(APITests)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            ClassUninit();
            TP::AddPackage_DeploymentWindowsAppRuntimeFramework();
            TP::AddPackage_WindowsAppRuntimeFramework();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            TP::RemovePackage_DeploymentWindowsAppRuntimeSingleton();
            TP::RemovePackage_DeploymentWindowsAppRuntimeMain();
            TP::RemovePackage_DeploymentWindowsAppRuntimeFramework();
            TP::RemovePackage_WindowsAppRuntimeFramework();
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DeploymentWindowsAppRuntimeFramework());
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            return true;
        }

        TEST_METHOD(GetStatus_NotOK)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                TEST_METHOD_PROPERTY(L"UAP:AppxManifest", L"Deployment-NoCapabilities-AppxManifest.xml")
            END_TEST_METHOD_PROPERTIES();

            auto result{ DeploymentManager::GetStatus() };
            Log::Comment(WEX::Common::String().Format(L"Status: 0x%0X", result.ExtendedError().value));
            VERIFY_IS_TRUE(result.Status() != DeploymentStatus::Ok);
            return;
        }

        TEST_METHOD(GetStatus_OK)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                TEST_METHOD_PROPERTY(L"UAP:AppxManifest", L"Deployment-Capabilities-AppxManifest.xml")
            END_TEST_METHOD_PROPERTIES();

            // Verify package status is by default not OK.
            auto result{ DeploymentManager::GetStatus() };
            Log::Comment(WEX::Common::String().Format(L"Status: 0x%0X", result.ExtendedError().value));
            VERIFY_IS_TRUE(result.Status() != DeploymentStatus::Ok);

            // Add the missing packages externally to the API (e.g. the installer).
            TP::AddPackage_DeploymentWindowsAppRuntimeSingleton();
            TP::AddPackage_DeploymentWindowsAppRuntimeMain();

            // Verify that package status is now OK.
            result = DeploymentManager::GetStatus();
            Log::Comment(WEX::Common::String().Format(L"Status: 0x%0X", result.ExtendedError().value));
            VERIFY_IS_TRUE(result.Status() == DeploymentStatus::Ok);
            return;
        }

        TEST_METHOD(Initialize_HasCapabilities)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                TEST_METHOD_PROPERTY(L"UAP:AppxManifest", L"Deployment-Capabilities-AppxManifest.xml")
            END_TEST_METHOD_PROPERTIES();

            // Verify package status is by default not OK.
            auto result{ DeploymentManager::GetStatus() };
            Log::Comment(WEX::Common::String().Format(L"Status: 0x%0X", result.ExtendedError().value));
            VERIFY_IS_TRUE(result.Status() != DeploymentStatus::Ok);

            // Call Initialize to correct and check status again.
            result = DeploymentManager::Initialize();
            Log::Comment(WEX::Common::String().Format(L"Initialize: 0x%0X", result.ExtendedError().value));
            VERIFY_IS_TRUE(result.Status() == DeploymentStatus::Ok);
            result = DeploymentManager::GetStatus();
            Log::Comment(WEX::Common::String().Format(L"Status: 0x%0X", result.ExtendedError().value));
            VERIFY_IS_TRUE(result.Status() == DeploymentStatus::Ok);
            return;
        }

        TEST_METHOD(Initialize_NoCapabilities)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                TEST_METHOD_PROPERTY(L"UAP:AppxManifest", L"Deployment-NoCapabilities-AppxManifest.xml")
            END_TEST_METHOD_PROPERTIES();

            // A package that does not have capabilities will be able to sucessfully detect that
            // status is not OK, but Initialize will fail to correct with error E_ACCESSDENIED.
            auto result{ DeploymentManager::GetStatus() };
            Log::Comment(WEX::Common::String().Format(L"Status: 0x%0X", result.ExtendedError().value));
            VERIFY_IS_TRUE(result.Status() != DeploymentStatus::Ok);
            result = DeploymentManager::Initialize();
            Log::Comment(WEX::Common::String().Format(L"Initialize: 0x%0X", result.ExtendedError().value));
            VERIFY_IS_TRUE(result.Status() == DeploymentStatus::PackageInstallFailed);
            VERIFY_IS_TRUE(result.ExtendedError().value == HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED));
            return;
        }

        TEST_METHOD(Combined_DDLMWindowsAppRuntimeFramework)
        {
            // This test uses the DDLM WindowsAppRuntime framework to exercise the same code.
            // GetStatus is expected to fail, as the matching main packages do not exist and
            // Initialize is also expected to fail because that framework does not have any
            // embedded packages.
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                TEST_METHOD_PROPERTY(L"UAP:AppxManifest", L"Deployment-RealNameFramework-AppxManifest.xml")
            END_TEST_METHOD_PROPERTIES();

            // Status is expected to fail because the matching main and singleton packages do not exist
            // with the correct naming scheme.
            auto result{ DeploymentManager::GetStatus() };
            Log::Comment(WEX::Common::String().Format(L"Status: 0x%0X", result.ExtendedError().value));
            VERIFY_IS_TRUE(result.Status() != DeploymentStatus::Ok);
            VERIFY_IS_TRUE(result.ExtendedError().value == HRESULT_FROM_WIN32(ERROR_NOT_FOUND));

            // Initialize is expected to fail because the packages are not contained in the framework, so they
            // will not be found when attempting to resolve the missing packages.
            result = DeploymentManager::Initialize();
            Log::Comment(WEX::Common::String().Format(L"Initialize: 0x%0X", result.ExtendedError().value));
            VERIFY_IS_TRUE(result.Status() == DeploymentStatus::PackageInstallFailed);
            VERIFY_IS_TRUE(result.ExtendedError().value == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND));
        }
    };
}
