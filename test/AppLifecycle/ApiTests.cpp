// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Microsoft::ApplicationModel::Activation;

namespace ProjectReunionCppTest
{
    class AppLifecycleApiTests
    {
        TEST_CLASS(AppLifecycleApiTests)

        // UWP currently is not supported by these tests.
        TEST_METHOD(GetActivatedEventArgsIsNull)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
            END_TEST_METHOD_PROPERTIES();

            VERIFY_IS_NULL(AppLifecycle::GetActivatedEventArgs());
        }

        TEST_METHOD(GetActivatedEventArgsIsNotNull)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                // Run this test for both PackagedWin32 and Win32.
                TEST_METHOD_PROPERTY(L"RunAs", L"{UAP,InteractiveUser}")
                TEST_METHOD_PROPERTY(L"UAP:Host", L"PackagedCwa")
                TEST_METHOD_PROPERTY(L"UAP:AppXManifest", L"PackagedCwaFullTrust")
            END_TEST_METHOD_PROPERTIES();

            VERIFY_IS_NOT_NULL(AppLifecycle::GetActivatedEventArgs());
        }

        TEST_METHOD(GetActivatedEventArgsForLaunch)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                // Run this test for both PackagedWin32 and Win32.
                TEST_METHOD_PROPERTY(L"RunAs", L"{UAP,InteractiveUser}")
                TEST_METHOD_PROPERTY(L"UAP:Host", L"PackagedCwa")
                TEST_METHOD_PROPERTY(L"UAP:AppXManifest", L"PackagedCwaFullTrust")
            END_TEST_METHOD_PROPERTIES();

            auto args = AppLifecycle::GetActivatedEventArgs();
            VERIFY_IS_NOT_NULL(args);
            VERIFY_ARE_EQUAL(args.Kind(), ActivationKind::Launch);

            auto launchArgs = args.as<LaunchActivatedEventArgs>();
            VERIFY_IS_NOT_NULL(launchArgs);
        }

        TEST_METHOD(GetActivatedEventArgsForProtocol)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"{UAP,InteractiveUser}")
                TEST_METHOD_PROPERTY(L"UAP:Host", L"PackagedCwa")
                TEST_METHOD_PROPERTY(L"UAP:AppXManifest", L"PackagedWin32Manifest.xml")
            END_TEST_METHOD_PROPERTIES();

            auto args = AppLifecycle::GetActivatedEventArgs();
            VERIFY_IS_NOT_NULL(args);
            VERIFY_ARE_EQUAL(args.Kind(), ActivationKind::Launch);

            auto launchArgs = args.as<LaunchActivatedEventArgs>();
            VERIFY_IS_NOT_NULL(launchArgs);
        }
    };
}
