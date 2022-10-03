// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "TestSetupAndTeardownHelper.h"
#include "LogContext.h"
#include <TerminalVelocityFeatures-EnvironmentManager.h>

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
            if (!::Microsoft::Windows::System::Feature_EnvironmentManager::IsEnabled())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Environment Manager is experimental.");
                return false;
            }

            ::Test::Bootstrap::SetupPackages();

            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            ::Test::Bootstrap::CleanupPackages();
            return true;
        }

        TEST_METHOD_SETUP(CentennialWriteEVs)
        {
            ::Test::Bootstrap::SetupBootstrap();

            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());

            UserSetup();
            MachineSetup();
            return true;
        }

        TEST_METHOD_CLEANUP(CentennialRemoveEVs)
        {
            ::Test::Bootstrap::CleanupBootstrap();
            UserCleanup();
            MachineCleanup();
            return true;
        }

        TEST_METHOD(CentennialTestGetForProcess);
        TEST_METHOD(CentennialTestGetForUser);
        TEST_METHOD(CentennialTestGetForMachine);

        TEST_METHOD(CentennialTestAreChangesTracked);

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
