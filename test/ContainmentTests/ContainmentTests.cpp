// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "AssemblyInfo.h"

#include <FrameworkUdk/Containment.h>
#include <winrt/Microsoft.Windows.ApplicationModel.WindowsAppRuntime.h>

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace WAR = winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime;

namespace Test::ContainmentTests
{
    class ContainmentTests
    {
    public:
        BEGIN_TEST_CLASS(ContainmentTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"UAP")
            TEST_CLASS_PROPERTY(L"UAP:AppxManifest", L"Containment-AppxManifest.xml")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method") // each test sets its own containment
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            //::Test::Bootstrap::SetupPackages(Test::Bootstrap::Packages::Framework);
            //::Test::Bootstrap::SetupBootstrap();
            ::Test::Bootstrap::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::Test::Bootstrap::Cleanup();
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            return true;
        }

        TEST_METHOD(CanSetCompatibilityOptions)
        {
            WEX::Logging::Log::Comment(WEX::Common::String(L"Starting CanSetCompatibilityOptions..."));
            winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::CompatibilityOptions options;
            WEX::Logging::Log::Comment(WEX::Common::String(L"   Created CompatibilityOptions..."));
            options.PatchMode1({ WINDOWSAPPSDK_RELEASE_MAJOR, WINDOWSAPPSDK_RELEASE_MINOR, 3 });
            options.Apply();
            WEX::Logging::Log::Comment(WEX::Common::String(L"   Applied CompatibilityOptions..."));

            try
            {
                WEX::Logging::Log::Comment(WEX::Common::String(L"   Applying CompatibilityOptions with different patch mode..."));
                winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::CompatibilityOptions options2;
                options2.PatchMode1({ WINDOWSAPPSDK_RELEASE_MAJOR, WINDOWSAPPSDK_RELEASE_MINOR, 6 });
                options2.Apply();
                VERIFY_FAIL(L"Success is not expected when setting a different configuration");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_ILLEGAL_STATE_CHANGE, e.code());
            }

            try
            {
                WEX::Logging::Log::Comment(WEX::Common::String(L"   Applying CompatibilityOptions with no patch mode..."));
                winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::CompatibilityOptions options3;
                options3.Apply();
                VERIFY_FAIL(L"Success is not expected when setting a different configuration");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_ILLEGAL_STATE_CHANGE, e.code());
            }
        }

        TEST_METHOD(VerifyNoMatchingPatchModeBehavior)
        {
            WEX::Logging::Log::Comment(WEX::Common::String(L"Setting CompatibilityOptions with no matching patch mode"));
            winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::CompatibilityOptions options;
            options.PatchMode1({ 0, 8, 3 });
            options.PatchMode1({ 1, 1, 4 });
            options.Apply();

            // Set a CompatibilityOptions with no patch mode, which should be allowed since neither
            // set a patch mode matching the runtime version.
            winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::CompatibilityOptions options2;
            options2.Apply();
        }

        TEST_METHOD(VerifyDisabledChanges)
        {
            winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::CompatibilityOptions options;
            options.PatchMode1({ WINDOWSAPPSDK_RELEASE_MAJOR, WINDOWSAPPSDK_RELEASE_MINOR, 3 });
            options.DisabledChanges().Append((WAR::CompatibilityChange)12345);
            options.DisabledChanges().Append((WAR::CompatibilityChange)23456);
            options.DisabledChanges().Append((WAR::CompatibilityChange)34567);
            options.DisabledChanges().Append(WAR::CompatibilityChange::None); // just to confirm compilation using a real enum value
            options.Apply();

            WEX::Logging::Log::Comment(WEX::Common::String(L"CompatibilityOptions with DisabledChanges applied."));

            // Verify that the specified DisabledChanges are disabled.
            VERIFY_IS_FALSE((WinAppSdk::Containment::IsChangeEnabled<12345, WinAppSDK_Security>()));
            VERIFY_IS_FALSE((WinAppSdk::Containment::IsChangeEnabled<23456, WinAppSDK_Security>()));
            VERIFY_IS_FALSE((WinAppSdk::Containment::IsChangeEnabled<34567, WinAppSDK_Security>()));

            // A different value not in DisabledChanges should remain enabled.
            VERIFY_IS_TRUE((WinAppSdk::Containment::IsChangeEnabled<99999, WinAppSDK_Security>()));
        }
    };
}
