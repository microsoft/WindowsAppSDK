// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "TestSetupAndTeardownHelper.h"

namespace WindowsAppSDKEnvironmentManagerTests
{
    class EnvironmentManagerCentennialTests {
        BEGIN_TEST_CLASS(EnvironmentManagerCentennialTests)
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Method", L"ElevatedUser")
            TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"CentennialAppxManifest.pkg.xml")
            TEST_CLASS_PROPERTY(L"UAP:Host",  L"PackagedCWA")
            END_TEST_CLASS()


        TEST_CLASS_SETUP(ClassInit)
        {
            ::Test::Bootstrap::Setup();

            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            ::Test::Bootstrap::Cleanup();
            return true;
        }

        TEST_METHOD_SETUP(CentennialWriteEVs)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());

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
