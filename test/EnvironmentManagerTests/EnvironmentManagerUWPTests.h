// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "TestSetupAndTeardownHelper.h"

namespace ProjectReunionEnvironmentManagerTests
{
    class EnvironmentManagerUWPTests {
        BEGIN_TEST_CLASS(EnvironmentManagerUWPTests)
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:AppXManifest", L"AppxManifest.pkg.xml")
            TEST_CLASS_PROPERTY(L"RunFixtureAs", L"ElevatedUser")
            END_TEST_CLASS()

        TEST_CLASS_SETUP(UWPWriteEVs)
        {
            WriteUserEV();
            WriteMachineEV();
            return true;
        }

        TEST_CLASS_CLEANUP(IWPRemoveEVs)
        {
            RemoveUserEV();
            RemoveMachineEV();
            return true;
        }

        TEST_METHOD(UWPTestGetForProcess);
        TEST_METHOD(UWPTestGetForUser);
        TEST_METHOD(UWPTestGetForMachine);

        TEST_METHOD(UWPTestGetEnvironmentVariablesForProcess);
        TEST_METHOD(UWPTestGetEnvironmentVariablesForUser);
        TEST_METHOD(UWPTestGetEnvironmentVariablesForMachine);

        TEST_METHOD(UWPTestGetEnvironmentVariableForProcess);
        TEST_METHOD(UWPTestGetEnvironmentVariableForUser);
        TEST_METHOD(UWPTestGetEnvironmentVariableForMachine);

        TEST_METHOD(UWPTestSetEnvironmentVariableForProcess);
        TEST_METHOD(UWPTestSetEnvironmentVariableForUser);
        TEST_METHOD(UWPTestSetEnvironmentVariableForMachine);

        TEST_METHOD(UWPTestAppendToPathForProcess);
        TEST_METHOD(UWPTestAppendToPathForUser);
        TEST_METHOD(UWPTestAppendToPathForMachine);

        TEST_METHOD(UWPTestRemoveFromPathForProcess);
        TEST_METHOD(UWPTestRemoveFromPathForUser);
        TEST_METHOD(UWPTestRemoveFromPathForMachine);
    };
}
