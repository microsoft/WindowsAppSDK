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

#if PRTEST_MODE_UWP
        // UWP currently is not supported by these tests.
        TEST_METHOD(GetActivatedEventArgsIsNull)
        {
            VERIFY_IS_NULL(AppLifecycle::GetActivatedEventArgs());
        }
#else
        TEST_METHOD(GetActivatedEventArgsIsNotNull)
        {
            VERIFY_IS_NOT_NULL(AppLifecycle::GetActivatedEventArgs());
        }

        TEST_METHOD(GetActivatedEventArgsForLaunch)
        {
            auto args = AppLifecycle::GetActivatedEventArgs();
            VERIFY_IS_NOT_NULL(args);
            VERIFY_ARE_EQUAL(args.Kind(), ActivationKind::Launch);

            auto launchArgs = args.as<LaunchActivatedEventArgs>();
            VERIFY_IS_NOT_NULL(launchArgs);
        }
#endif
    };
}
