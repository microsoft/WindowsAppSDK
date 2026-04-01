// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "PackageDeploymentManagerTests.h"

#include <IsWindowsVersion.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TPF = ::Test::Packages::Framework;
namespace TPM = ::Test::Packages::Main;
namespace TPMT = ::Test::PackageManager::Tests;

namespace Test::PackageManager::Tests
{
    class PackageDeploymentManagerTests_IsPackageRegistrationPending : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_IsPackageRegistrationPending)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Class")    /****SEEME****/
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!::WindowsVersion::IsWindows10_20H1OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageDeploymentManager requires >= 20H1 (Vibranium). Skipping tests");
                return true;
            }

            TD::DumpExecutionContext();

            RemovePackage_Blacker();
            RemovePackage_Black();
            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            RemovePackage_Blacker();
            RemovePackage_Black();
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(IsPackageRegistrationPending_NoSuchPackage)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFullName{ L"Does.Not.Exist_0.0.0.0_neutral__1234567890abc" };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageRegistrationPending(packageFullName));
        }

        TEST_METHOD(IsPackageRegistrationPending_NotInstalled)
        {
            RemovePackage_Blacker();
            RemovePackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packageFullName{ ::TPM::Black::GetPackageFullName() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageRegistrationPending(packageFullName));
        }

        TEST_METHOD(IsPackageRegistrationPending_Registered)
        {
            RemovePackage_Blacker();
            AddPackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPM::Black::GetPackageFullName() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageRegistrationPending(packageFullName));
        }

        TEST_METHOD(IsPackageRegistrationPending_Pending)
        {
            RemovePackage_Blacker();
            AddPackage_Black();

            PCWSTR eventName{ L"PackageManagerTests.IsPackageRegistrationPending_Pending.EndOfTheLine" };
            wil::unique_event_nothrow endOfTheLine{ ::CreateEventW(nullptr, TRUE, FALSE, eventName) };
            if (!endOfTheLine)
            {
                const auto rc{ GetLastError() };
                VERIFY_FAIL(WEX::Common::String().Format(L"CreateEventW() LastError:%u (0x%08X)", rc, rc));
            }
            wil::com_ptr<IApplicationActivationManager> AAM{ wil::CoCreateInstance<IApplicationActivationManager>(CLSID_ApplicationActivationManager, CLSCTX_LOCAL_SERVER) };
            PCWSTR appUserModelId{ ::TPM::Black::c_appUserModelId };
            DWORD processId{};
            VERIFY_SUCCEEDED(AAM->ActivateApplication(appUserModelId, eventName, AO_NONE, &processId));
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"AppUserModleId:%s Arguments:%s ProcessId:%u", appUserModelId, eventName, processId));

            AddPackageDefer_Blacker();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPM::Black::GetPackageFullName() };
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageRegistrationPending(packageFullName));

            VERIFY_IS_TRUE(LOG_IF_WIN32_BOOL_FALSE(::SetEvent(endOfTheLine.get())));
        }

        TEST_METHOD(IsPackageRegistrationPendingForUser_NoSuchPackage)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFullName{ L"Does.Not.Exist_0.0.0.0_neutral__1234567890abc" };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageRegistrationPendingForUser(winrt::hstring{}, packageFullName));
        }

        TEST_METHOD(IsPackageRegistrationPendingForUser_NotInstalled)
        {
            RemovePackage_Blacker();
            RemovePackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPM::Black::GetPackageFullName() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageRegistrationPendingForUser(winrt::hstring{}, packageFullName));
        }

        TEST_METHOD(IsPackageRegistrationPendingForUser_Registered)
        {
            RemovePackage_Blacker();
            AddPackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPM::Black::GetPackageFullName() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageRegistrationPendingForUser(winrt::hstring{}, packageFullName));
        }

        TEST_METHOD(IsPackageRegistrationPendingForUser_Pending)
        {
            RemovePackage_Blacker();
            AddPackage_Black();

            PCWSTR eventName{ L"PackageManagerTests.IsPackageRegistrationPendingForUser_Pending.EndOfTheLine" };
            wil::unique_event_nothrow endOfTheLine{ ::CreateEventW(nullptr, TRUE, FALSE, eventName) };
            if (!endOfTheLine)
            {
                const auto rc{ GetLastError() };
                VERIFY_FAIL(WEX::Common::String().Format(L"CreateEventW() LastError:%u (0x%08X)", rc, rc));
            }
            wil::com_ptr<IApplicationActivationManager> AAM{ wil::CoCreateInstance<IApplicationActivationManager>(CLSID_ApplicationActivationManager, CLSCTX_LOCAL_SERVER) };
            PCWSTR appUserModelId{ ::TPM::Black::c_appUserModelId };
            DWORD processId{};
            VERIFY_SUCCEEDED(AAM->ActivateApplication(appUserModelId, eventName, AO_NONE, &processId));
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"AppUserModleId:%s Arguments:%s ProcessId:%u", appUserModelId, eventName, processId));

            AddPackageDefer_Blacker();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPM::Black::GetPackageFullName() };
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageRegistrationPendingForUser(winrt::hstring{}, packageFullName));

            VERIFY_IS_TRUE(LOG_IF_WIN32_BOOL_FALSE(::SetEvent(endOfTheLine.get())));
        }
    };
}
