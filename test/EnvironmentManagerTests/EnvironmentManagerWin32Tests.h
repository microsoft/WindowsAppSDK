// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "TestSetupAndTeardownHelper.h"

namespace ProjectReunionEnvironmentManagerTests
{
    class EnvironmentManagerWin32Tests {
        BEGIN_TEST_CLASS(EnvironmentManagerWin32Tests)
            TEST_CLASS_PROPERTY(L"ActivationContext", L"EnvironmentReaderTests.dll.manifest")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs", L"ElevatedUser")
        END_TEST_CLASS()

            TEST_CLASS_SETUP(WriteEVs)
        {
            WriteMachineEV();
            return true;
        }

        TEST_CLASS_CLEANUP(RemoveEVs)
        {
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

        TEST_METHOD(TestSetEnvironmentVariableForProcess);
        TEST_METHOD(TestSetEnvironmentVariableForUser);
        TEST_METHOD(TestSetEnvironmentVariableForMachine);

        TEST_METHOD(TestAppendToPathForProcess);
        TEST_METHOD(TestAppendToPathForUser);
        TEST_METHOD(TestAppendToPathForMachine);

        TEST_METHOD(TestRemoveFromPathForProcess);
        TEST_METHOD(TestRemoveFromPathForUser);
        TEST_METHOD(TestRemoveFromPathForMachine);
    };
}
