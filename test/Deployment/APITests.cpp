// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <testdef.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt;
using namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK;
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
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            TP::RemovePackage_DeploymentWindowsAppRuntimeSingleton();
            TP::RemovePackage_DeploymentWindowsAppRuntimeMain();
            TP::RemovePackage_DeploymentWindowsAppRuntimeFramework();
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

            std::wstring WASFrameworkName { TP::DeploymentWindowsAppRuntimeFramework::c_PackageFullName };
            auto status{ DeploymentManager::GetStatus(WASFrameworkName) };
            VERIFY_IS_TRUE(!status.IsOK());
            return;
        }

        TEST_METHOD(GetStatus_OK)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                TEST_METHOD_PROPERTY(L"UAP:AppxManifest", L"Deployment-Capabilities-AppxManifest.xml")
            END_TEST_METHOD_PROPERTIES();

            // Verify package status is by default not OK.
            std::wstring WASFrameworkName{ TP::DeploymentWindowsAppRuntimeFramework::c_PackageFullName };
            auto status{ DeploymentManager::GetStatus(WASFrameworkName) };
            VERIFY_IS_TRUE(!status.IsOK());

            // Add the missing packages externally to the API (e.g. the installer).
            TP::AddPackage_DeploymentWindowsAppRuntimeSingleton();
            TP::AddPackage_DeploymentWindowsAppRuntimeMain();

            // Verify that package status is now OK.
            status = DeploymentManager::GetStatus(WASFrameworkName);
            VERIFY_IS_TRUE(status.IsOK());
            return;
        }


        TEST_METHOD(Initialize_HasCapabilities)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                TEST_METHOD_PROPERTY(L"UAP:AppxManifest", L"Deployment-Capabilities-AppxManifest.xml")
            END_TEST_METHOD_PROPERTIES();

            // Verify package status is by defualt not OK.
            std::wstring WASFrameworkName{ TP::DeploymentWindowsAppRuntimeFramework::c_PackageFullName };
            auto status{ DeploymentManager::GetStatus(WASFrameworkName) };
            VERIFY_IS_TRUE(!status.IsOK());

            // Call Initialize to correct and check status again.
            status = DeploymentManager::Initialize(WASFrameworkName);
            VERIFY_IS_TRUE(status.IsOK());
            status = DeploymentManager::GetStatus(WASFrameworkName);
            VERIFY_IS_TRUE(status.IsOK());
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
            std::wstring WASFrameworkName{ TP::DeploymentWindowsAppRuntimeFramework::c_PackageFullName };
            auto status{ DeploymentManager::GetStatus(WASFrameworkName) };
            VERIFY_IS_TRUE(!status.IsOK());
            status = DeploymentManager::Initialize(WASFrameworkName);
            VERIFY_IS_TRUE(!status.IsOK());
            VERIFY_IS_TRUE(status.ExtendedError() == E_ACCESSDENIED);
            return;
        }

    };
}
