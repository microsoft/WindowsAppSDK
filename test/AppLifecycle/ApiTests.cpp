// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Microsoft::ApplicationModel::Activation;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectReunionCppTest
{
    TEST_CLASS(AppLifecycleApiTests)
    {
#if PRTEST_MODE_UWP
        // UWP currently is not supported by these tests.
        TEST_METHOD(GetActivatedEventArgsIsNull)
        {
            Assert::IsTrue(AppLifecycle::GetActivatedEventArgs() == nullptr);
        }
#else
        TEST_METHOD(GetActivatedEventArgsIsNotNull)
        {
            Assert::IsTrue(AppLifecycle::GetActivatedEventArgs() != nullptr);
        }

        TEST_METHOD(GetActivatedEventArgsForLaunch)
        {
            auto args = AppLifecycle::GetActivatedEventArgs();
            Assert::IsTrue(args != nullptr);
            Assert::IsTrue(args.Kind() == ActivationKind::Launch);

            auto launchArgs = args.as<LaunchActivatedEventArgs>();
            Assert::IsTrue(launchArgs != nullptr);
        }
#endif
    };
}
