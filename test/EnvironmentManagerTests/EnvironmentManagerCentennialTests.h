// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "TestSetupAndTeardownHelper.h"

namespace ProjectReunionEnvironmentManagerTests
{
    class EnvironmentManagerCentennialTests {
        BEGIN_TEST_CLASS(EnvironmentManagerCentennialTests)
            TEST_CLASS_PROPERTY(L"RunAs", L"{UAP,Restricted,Elevated,InteractiveUser}")
            TEST_CLASS_PROPERTY(L"UAP:Host", L"PackagedCwa")
            TEST_CLASS_PROPERTY(L"UAP:AppXManifest", L"CentennialAppxManifest.pkg.xml")
            TEST_CLASS_PROPERTY(L"RunFixtureAs", L"Elevated")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(CentennialWriteEVs)
        {
            WriteProcessEV();
            WriteUserEV();
            WriteMachineEV();

            return true;
        }

        TEST_CLASS_CLEANUP(CentennialRemoveEvs)
        {
            RemoveProcessEV();
            RemoveUserEV();
            RemoveMachineEV();

            return true;
        }

        TEST_METHOD(CentennialTestGetForProcess);
        TEST_METHOD(CentennialTestGetForUser);
        TEST_METHOD(CentennialTestGetForMachine);
        TEST_METHOD(CentennialTestGetEnvironmentVariablesForProcess);
        TEST_METHOD(CentennialTestGetEnvironmentVariablesForUser);
        TEST_METHOD(CentennialTestGetEnvironmentVariablesForMachine);
        TEST_METHOD(CentennialTestGetEnvironmentVariableForProcess);
        TEST_METHOD(CentennialTestGetEnvironmentVariableForUser);
        TEST_METHOD(CentennialTestGetEnvironmentVariableForMachine);
        TEST_METHOD(CentennialTestSetEnvironmentVariableForProcess);
        TEST_METHOD(CentennialTestSetEnvironmentVariableForUser);
        TEST_METHOD(CentennialTestSetEnvironmentVariableForMachine);
    };

}
