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

            TP::AddPackage_WindowsAppSDKFramework();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            TP::RemovePackage_DynamicDependencyDataStore();
            TP::RemovePackage_DynamicDependencyLifetimeManager();
            TP::RemovePackage_WindowsAppSDKSingleton();
            TP::RemovePackage_WindowsAppSDKFramework();
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppSDKFramework());
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            return true;
        }

        TEST_METHOD(GetStatusBasicTest)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                TEST_METHOD_PROPERTY(L"UAP:AppxManifest", L"Deployment-AppxManifest.xml")
            END_TEST_METHOD_PROPERTIES();

            std::wstring WASFrameworkName { TP::WindowsAppSDKFramework::c_PackageFullName };




            auto status{ DeploymentManager::GetStatus(WASFrameworkName) };

            VERIFY_IS_TRUE(status.IsOK());

            return;
        }

        TEST_METHOD(InitializeBasicTest)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                TEST_METHOD_PROPERTY(L"UAP:AppxManifest", L"Deployment-AppxManifest.xml")
                END_TEST_METHOD_PROPERTIES();

            std::wstring WASFrameworkName{ TP::WindowsAppSDKFramework::c_PackageFullName };

            auto status{ DeploymentManager::Initialize(WASFrameworkName) };

            VERIFY_IS_TRUE(status.IsOK());

            return;
        }

    };
}
