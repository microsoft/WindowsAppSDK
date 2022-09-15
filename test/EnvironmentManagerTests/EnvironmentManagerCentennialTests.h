// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "TestSetupAndTeardownHelper.h"
#include "LogContext.h"
#include <TerminalVelocityFeatures-EnvironmentManager.h>
#include <WindowsAppRuntime.VersionInfo.h>

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

            ::Test::Bootstrap::Setup();

            ::WindowsAppRuntime::VersionInfo::TestInitialize(::TP::WindowsAppRuntimeFramework::c_PackageFamilyName, ::TP::WindowsAppRuntimeMain::c_PackageFamilyName);

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

        // Ignore because the test framework package and production framework package have different family names.
        // Can be run when the code can switch between the test family name and the production family name.
        BEGIN_TEST_METHOD(CentennialTestAreChangesTracked)
            TEST_METHOD_PROPERTY(L"Ignore", L"true")
        END_TEST_METHOD()

        // Ignore until a way is found to install a framework package for another user.
        BEGIN_TEST_METHOD(CentennialTestAreChangesTrackedAsAdmin)
            TEST_METHOD_PROPERTY(L"Ignore", L"true")
            TEST_METHOD_PROPERTY(L"Description", L"Tests if a framework package, installed by a different user, can be found")
        END_TEST_METHOD()

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
