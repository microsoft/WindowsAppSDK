// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ProjectReunionCppTest
{
    TEST_CLASS(AppLifecycleApiTests)
    {
#if PRTEST_MODE_UWP
        TEST_METHOD(GetActivatedEventArgsNotNull)
        {
            Assert::IsTrue(!!winrt::Microsoft::ProjectReunion::AppLifecycle::GetActivatedEventArgs());
        }
#else
        TEST_METHOD(GetActivatedEventArgsNotNull)
        {
            Assert::IsTrue(!!winrt::Microsoft::ProjectReunion::AppLifecycle::GetActivatedEventArgs());
        }
#endif
    };
}
