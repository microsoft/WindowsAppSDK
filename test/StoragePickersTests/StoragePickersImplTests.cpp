// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <FrameworkUdk/Containment.h>
#include <winrt/Microsoft.Windows.Storage.Pickers.h>
#include <TerminalVelocityFeatures-StoragePickers.h>

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

#include "StoragePickersImpl.h"
using namespace StoragePickersImpl;

namespace Test::StoragePickersImplTests
{
    class StoragePickersImplTests
    {
    public:
        BEGIN_TEST_CLASS(StoragePickersImplTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA") // MTA is required for ::Test::Bootstrap::SetupPackages()
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"StoragePickers-AppxManifest.xml")
            END_TEST_CLASS()

            TEST_CLASS_SETUP(ClassSetup)
        {
            ::Test::Bootstrap::SetupPackages();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::Test::Bootstrap::CleanupPackages();
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());

            // The test method setup and execution is on a different thread than the class setup.
            // Initialize the framework for the test thread.
            ::Test::Bootstrap::SetupBootstrap();
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            ::Test::Bootstrap::CleanupBootstrap();
            return true;
        }

        // Test the test_add function from StoragePickersImpl
        TEST_METHOD(TestAdd)
        {
            // Call the test_add function from StoragePickersImpl
            int a = 5;
            int b = 7;
            int result = test_add(a, b);
            
            // Verify the result
            VERIFY_ARE_EQUAL(result, a + b);
            Log::Comment(WEX::Common::String().Format(L"test_add(%d, %d) = %d", a, b, result));
        }

        // Test negative numbers
        TEST_METHOD(TestAddWithNegativeNumbers)
        {
            int a = -3;
            int b = -8;
            int result = test_add(a, b);
            
            VERIFY_ARE_EQUAL(result, a + b);
            Log::Comment(WEX::Common::String().Format(L"test_add(%d, %d) = %d", a, b, result));
        }

        // Test with zero
        TEST_METHOD(TestAddWithZero)
        {
            int a = 0;
            int b = 42;
            int result = test_add(a, b);
            
            VERIFY_ARE_EQUAL(result, b);
            Log::Comment(WEX::Common::String().Format(L"test_add(%d, %d) = %d", a, b, result));
        }

        // Add more tests for other functions in StoragePickersImpl as needed
    };
}
