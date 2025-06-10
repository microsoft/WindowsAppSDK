// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "AssemblyInfo.h"

#include <FrameworkUdk/Containment.h>
#include <winrt/Microsoft.Windows.ApplicationModel.WindowsAppRuntime.h>

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace WAR = winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime;

namespace Test::CompatibilityTests
{
    class CompatibilityTests
    {
    public:
        BEGIN_TEST_CLASS(CompatibilityTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA") // MTA is required for ::Test::Bootstrap::SetupPackages()
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method") // each test sets its own RuntimeCompatibilityOptions
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

        TEST_METHOD(CanSetRuntimeCompatibilityOptions)
        {
            WEX::Logging::Log::Comment(WEX::Common::String(L"Starting CanSetRuntimeCompatibilityOptions..."));
            winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityOptions options;
            WEX::Logging::Log::Comment(WEX::Common::String(L"   Created RuntimeCompatibilityOptions..."));
            options.PatchLevel1({ WINDOWSAPPSDK_RELEASE_MAJOR, WINDOWSAPPSDK_RELEASE_MINOR, 3 });
            options.Apply();
            WEX::Logging::Log::Comment(WEX::Common::String(L"   Applied RuntimeCompatibilityOptions..."));

            try
            {
                WEX::Logging::Log::Comment(WEX::Common::String(L"   Applying RuntimeCompatibilityOptions with different patch level..."));
                winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityOptions options2;
                options2.PatchLevel1({ WINDOWSAPPSDK_RELEASE_MAJOR, WINDOWSAPPSDK_RELEASE_MINOR, 6 });
                options2.Apply();
                VERIFY_FAIL(L"Success is not expected when setting a different configuration");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_ILLEGAL_STATE_CHANGE, e.code());
            }

            try
            {
                WEX::Logging::Log::Comment(WEX::Common::String(L"   Applying RuntimeCompatibilityOptions with no patch level..."));
                winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityOptions options3;
                options3.Apply();
                VERIFY_FAIL(L"Success is not expected when setting a different configuration");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_ILLEGAL_STATE_CHANGE, e.code());
            }
        }

        TEST_METHOD(VerifyNoMatchingPatchLevelBehavior)
        {
            WEX::Logging::Log::Comment(WEX::Common::String(L"Setting RuntimeCompatibilityOptions with no matching patch level"));
            winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityOptions options;
            options.PatchLevel1({ 0, 8, 3 });
            options.PatchLevel2({ 1, 1, 4 });
            options.Apply();

            // Set a RuntimeCompatibilityOptions with no patch level, which should be allowed since neither
            // set a patch level matching the runtime version.
            winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityOptions options2;
            options2.Apply();
        }

        TEST_METHOD(VerifyConflictingPatchLevelBehavior)
        {
            WEX::Logging::Log::Comment(WEX::Common::String(L"Setting RuntimeCompatibilityOptions with conflicting patch levels"));
            winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityOptions options;
            options.PatchLevel1({ 1, 7, 3 });
            options.PatchLevel2({ 1, 7, 6 }); // Conflicting patch level for 1.7.x! Apply should fail.
            try
            {
                options.Apply();
                VERIFY_FAIL(L"Success is not expected when setting a conflicting configuration");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }
        }

        TEST_METHOD(VerifyDisabledChanges)
        {
            winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityOptions options;
            options.PatchLevel1({ WINDOWSAPPSDK_RELEASE_MAJOR, WINDOWSAPPSDK_RELEASE_MINOR, 3 });
            options.DisabledChanges().Append((WAR::RuntimeCompatibilityChange)12345);
            options.DisabledChanges().Append((WAR::RuntimeCompatibilityChange)23456);
            options.DisabledChanges().Append((WAR::RuntimeCompatibilityChange)34567);
            options.DisabledChanges().Append(WAR::RuntimeCompatibilityChange::None); // just to confirm compilation using a real enum value
            options.Apply();

            WEX::Logging::Log::Comment(WEX::Common::String(L"RuntimeCompatibilityOptions with DisabledChanges applied."));

            // Verify that the specified DisabledChanges are disabled.
            VERIFY_IS_FALSE((WinAppSdk::Containment::IsChangeEnabled<12345, WinAppSDK_Security>()));
            VERIFY_IS_FALSE((WinAppSdk::Containment::IsChangeEnabled<23456, WinAppSDK_Security>()));
            VERIFY_IS_FALSE((WinAppSdk::Containment::IsChangeEnabled<34567, WinAppSDK_Security>()));

            // A different value not in DisabledChanges should remain enabled.
            VERIFY_IS_TRUE((WinAppSdk::Containment::IsChangeEnabled<99999, WinAppSDK_Security>()));
        }
    };
}
