// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace ProjectReunionEnvironmentManagerTests
{
    class EnvironmentManagerWin32Tests {
        BEGIN_TEST_CLASS(EnvironmentManagerWin32Tests)
            TEST_CLASS_PROPERTY(L"ActivationContext", L"EnvironmentManagerTests.dll.manifest")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs", L"{Restricted,Elevated,InteractiveUser}")
        END_TEST_CLASS()

        TEST_METHOD(TestGetForProcess);
        TEST_METHOD(TestGetForUser);
        TEST_METHOD(TestGetForMachine);
        TEST_METHOD(TestGetEnvironmentVariablesForProcess);
        TEST_METHOD(TestGetEnvironmentVariablesForUser);
        TEST_METHOD(TestGetEnvironmentVariablesForMachine);
    };
}
