// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "AssemblyInfo.h"

#include <FrameworkUdk/Containment.h>
#include <winrt/Microsoft.Windows.ApplicationModel.WindowsAppRuntime.h>

// Signature of the test-only DLL export from Microsoft.WindowsAppRuntime.dll.
// Switches the WinAppSDK Containment catalog used by RuntimeCompatibilityOptions::Apply()
// between the production catalog (default) and a test-only catalog whose two groups
// straddle WinAppSDK_Latest: an "enabled" group at WinAppSDK_Latest - 1 holding
// {1, 2, 3} that Apply prunes out of disabledChanges, and a "disabled" group at
// WinAppSDK_Latest + 1 holding {0, 99999999} that Apply preserves in disabledChanges.
//
// The export is resolved via GetModuleHandleW/GetProcAddress (not a static import)
// because RuntimeCompatibilityOptions::Apply runs in the framework-package copy of
// Microsoft.WindowsAppRuntime.dll loaded by the bootstrap. The catalog globals live
// in that same module instance, so the test must call ContainmentTestInitialize on
// that DLL handle - a static import would resolve to a test-folder copy with its
// own (production) catalog and the catalog swap would have no observable effect.
using PFN_ContainmentTestInitialize = HRESULT(STDAPICALLTYPE*)(bool) noexcept;

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace WAR = winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime;

namespace Test::CompatibilityTests
{
    // Resolve ContainmentTestInitialize from the bootstrap-loaded framework copy
    // of Microsoft.WindowsAppRuntime.dll. Must be called AFTER SetupBootstrap so
    // the DLL is present in the process module list.
    static HRESULT ContainmentTestInitialize(bool enableTest) noexcept
    {
        HMODULE const hmod{ ::GetModuleHandleW(L"Microsoft.WindowsAppRuntime.dll") };
        if (hmod == nullptr)
        {
            return HRESULT_FROM_WIN32(::GetLastError());
        }
        auto const pfn{ reinterpret_cast<PFN_ContainmentTestInitialize>(
            ::GetProcAddress(hmod, "ContainmentTestInitialize")) };
        if (pfn == nullptr)
        {
            return HRESULT_FROM_WIN32(::GetLastError());
        }
        return pfn(enableTest);
    }

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

            // Swap in the test-only catalog so the catalog pre-prune tests
            // observe the synthetic groups that straddle WinAppSDK_Latest.
            // Must be done after SetupBootstrap so the framework copy of
            // Microsoft.WindowsAppRuntime.dll is loaded and reachable via
            // GetModuleHandleW; that copy is the one that hosts
            // RuntimeCompatibilityOptions::Apply and owns the catalog globals.
            VERIFY_ARE_EQUAL(S_OK, ContainmentTestInitialize(true));
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            // Restore the production catalog before tearing down the bootstrap.
            // IsolationLevel="Method" already guarantees a fresh process per test,
            // but resetting keeps the contract clean.
            VERIFY_ARE_EQUAL(S_OK, ContainmentTestInitialize(false));
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
            // TODO: Remove when MajorVersion and MinorVersion in AssemblyInfo.h are updated to match real release versions instead of dev defaults (0.0)
            // Skip when MajorVersion=0 (dev-loop default) — PatchLevel {0,8,3} matches major=0
            if (WINDOWSAPPSDK_RELEASE_MAJOR == 0)
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Skipped: WINDOWSAPPSDK_RELEASE_MAJOR is 0 (dev default); test patch levels conflict with major=0");
                return;
            }

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

        TEST_METHOD(VerifyCatalogPrePrunesByPatchLevel)
        {
            // The test catalog has two groups whose releaseVersion straddles
            // the runtime's effective patch level (WinAppSDK_Latest by
            // default):
            //   * s_enabled_changes_test  at WinAppSDK_Latest - 1: the
            //     pre-prune walk SKIPS this group, so {1, 2, 3} remain
            //     enabled.
            //   * s_disabled_changes_test at WinAppSDK_Latest + 1: the
            //     pre-prune walk COPIES this group into disabledChanges,
            //     so {0, 99999999} are disabled.
            // Together the two groups span the value range and exercise
            // both branches of the catalog walk, both ends of std::sort,
            // and both ends of the FrUdk worker's std::binary_search.
            winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityOptions options;
            options.Apply();

            // Use WinAppSDK_Security as the template-arg patch so the worker's
            // per-callsite patch comparison degenerates to (0 > effective) = false,
            // isolating the catalog pre-prune as the disabling mechanism.

            // s_enabled_changes_test: catalog group released BEFORE the
            // effective patch level. Apply prunes it out; IDs remain enabled.
            VERIFY_IS_TRUE((WinAppSdk::Containment::IsChangeEnabled<1, WinAppSDK_Security>()));
            VERIFY_IS_TRUE((WinAppSdk::Containment::IsChangeEnabled<2, WinAppSDK_Security>()));
            VERIFY_IS_TRUE((WinAppSdk::Containment::IsChangeEnabled<3, WinAppSDK_Security>()));

            // s_disabled_changes_test: catalog group released AFTER the
            // effective patch level. Apply preserves it; IDs are disabled.
            VERIFY_IS_FALSE((WinAppSdk::Containment::IsChangeEnabled<0, WinAppSDK_Security>()));        // smallest representable ID
            VERIFY_IS_FALSE((WinAppSdk::Containment::IsChangeEnabled<99999999, WinAppSDK_Security>())); // high-value sentinel

            // An ID not in the catalog and not explicitly disabled stays enabled.
            VERIFY_IS_TRUE((WinAppSdk::Containment::IsChangeEnabled<99999, WinAppSDK_Security>()));
        }

        TEST_METHOD(VerifyCatalogAndExplicitDisabledChangesCombine)
        {
            // Catalog pre-prune contributes {0, 99999999} via
            // s_disabled_changes_test (the catalog group released AFTER the
            // effective patch level), and the app's explicit DisabledChanges
            // also names 99999999 plus 55555. Duplicates between the two
            // sources are harmless: the FrUdk worker treats disabledChanges
            // as a sorted set and uses set-membership semantics, so the
            // result is the union, not a tally.
            winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::RuntimeCompatibilityOptions options;
            options.DisabledChanges().Append((WAR::RuntimeCompatibilityChange)99999999);
            options.DisabledChanges().Append((WAR::RuntimeCompatibilityChange)55555);
            options.Apply();

            VERIFY_IS_FALSE((WinAppSdk::Containment::IsChangeEnabled<0, WinAppSDK_Security>()));        // catalog only
            VERIFY_IS_FALSE((WinAppSdk::Containment::IsChangeEnabled<99999999, WinAppSDK_Security>())); // catalog + explicit
            VERIFY_IS_FALSE((WinAppSdk::Containment::IsChangeEnabled<55555, WinAppSDK_Security>()));    // explicit only
            VERIFY_IS_TRUE((WinAppSdk::Containment::IsChangeEnabled<99999, WinAppSDK_Security>()));     // neither
        }
    };
}
