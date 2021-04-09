// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "TestSetupAndTeardownHelper.h"

namespace ProjectReunionEnvironmentReaderTests
{
    class EnvironmentReaderWin32Tests {
        BEGIN_TEST_CLASS(EnvironmentReaderWin32Tests)
            TEST_CLASS_PROPERTY(L"ActivationContext", L"EnvironmentReaderTests.dll.manifest")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs", L"{RestrictedUser,ElevatedUser,InteractiveUser}")
            TEST_CLASS_PROPERTY(L"RunFixtureAs", L"ElevatedUser")
        END_TEST_CLASS()

            TEST_CLASS_SETUP(WriteEVs)
        {
            WriteProcessEV();
            WriteUserEV();
            WriteMachineEV();

            return true;
        }

        TEST_CLASS_CLEANUP(RemoveEvs)
        {
            RemoveUserEV();
            RemoveMachineEV();

            return true;
        }

        TEST_METHOD(TestGetForProcess);
        TEST_METHOD(TestGetForUser);
        TEST_METHOD(TestGetForMachine);
        TEST_METHOD(TestGetEnvironmentVariablesForProcess);
        TEST_METHOD(TestGetEnvironmentVariablesForUser);
        TEST_METHOD(TestGetEnvironmentVariablesForMachine);
        TEST_METHOD(TestGetEnvironmentVariableForProcess);
        TEST_METHOD(TestGetEnvironmentVariableForUser);
        TEST_METHOD(TestGetEnvironmentVariableForMachine);
    };
}
