// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "TestSetupAndTeardownHelper.h"

namespace ProjectReunionEnvironmentManagerTests
{
    class EnvironmentManagerCentennialTests {
        BEGIN_TEST_CLASS(EnvironmentManagerCentennialTests)
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"RunFixtureAs", L"ElevatedUser")
            TEST_CLASS_PROPERTY(L"UAP:AppXManifest", L"{PackagedCwaFullTrust, PackagedCwaPartialTrust}")
            END_TEST_CLASS()

        TEST_METHOD_SETUP(CentennialWriteEVs)
        {
            UserSetup();
            MachineSetup();
            return true;
        }

        TEST_METHOD_CLEANUP(CentennialRemoveEVs)
        {
            UserCleanup();
            MachineCleanup();
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

        TEST_METHOD(CentennialTestAppendToPathForProcess);
        TEST_METHOD(CentennialTestAppendToPathForUser);
        TEST_METHOD(CentennialTestAppendToPathForMachine);

        TEST_METHOD(CentennialTestRemoveFromPathForProcess);
        TEST_METHOD(CentennialTestRemoveFromPathForUser);
        TEST_METHOD(CentennialTestRemoveFromPathForMachine);

        TEST_METHOD(CentennialTestAppendToPathExtForProcess);
        TEST_METHOD(CentennialTestAppendToPathExtForUser);
        TEST_METHOD(CentennialTestAppendToPathExtForMachine);

        TEST_METHOD(CentennialTestRemoveFromPathExtForProcess);
        TEST_METHOD(CentennialTestRemoveFromPathExtForUser);
        TEST_METHOD(CentennialTestRemoveFromPathExtForMachine);

    };

}
