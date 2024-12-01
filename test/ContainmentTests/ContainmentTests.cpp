// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace Test::ContainmentTests
{
    class ContainmentTests
    {
    public:
        BEGIN_TEST_CLASS(ContainmentTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            //TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
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

        TEST_METHOD(CanSetCompatibilityOptions)
        {
            WEX::Logging::Log::Comment(WEX::Common::String(L"Starting CanSetCompatibilityOptions..."));
            winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::CompatibilityOptions options;
            WEX::Logging::Log::Comment(WEX::Common::String(L"   created CompatibilityOptions..."));
            options.PatchMode1({ 1, 7, 3 });
            options.Apply();
            //VERIFY_FAIL(L"Success is not expected without Microsoft.WindowsAppRuntime.Insights.Resource.dll");
            try
            {
                winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::CompatibilityOptions options2;
                options2.PatchMode1({ 1, 7, 6 });
                options2.Apply();
                VERIFY_FAIL(L"Success is not expected when setting a different configuration");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_MOD_NOT_FOUND), e.code());
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

        // TODO: Test setting DisabledChanges.
        // TODO: Can IsChangeEnabled be directly called to test patch mode check and DisabledChanges?
    };
}
