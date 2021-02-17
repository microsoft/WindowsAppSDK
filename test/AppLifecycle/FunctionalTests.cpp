// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <testdef.h>
#include "Shared.h"

namespace Test::FileSystem
{
    constexpr PCWSTR ThisTestDllFilename{ L"CppTest.dll" };
}
#include <ProjectReunion.Test.Bootstrap.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Microsoft::ApplicationModel::Activation;
using namespace winrt;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::System;

namespace TP = ::Test::Packages;

// TODO: Write Register/Unregister tests that utilize the Assoc APIs to validate results.

PCWSTR IntegrityLevelToString(DWORD integrityLevel)
{
    switch (integrityLevel)
    {
        case SECURITY_MANDATORY_UNTRUSTED_RID:          return L"Untrusted";
        case SECURITY_MANDATORY_LOW_RID:                return L"Low";
        case SECURITY_MANDATORY_MEDIUM_RID:             return L"Medium";
        case SECURITY_MANDATORY_MEDIUM_PLUS_RID:        return L"MediumPlus";
        case SECURITY_MANDATORY_HIGH_RID:               return L"High";
        case SECURITY_MANDATORY_SYSTEM_RID:             return L"System";
        case SECURITY_MANDATORY_PROTECTED_PROCESS_RID:  return L"ProtectedProcess";
        default:                                        return L"???";
    }
}

void DumpUser(PCWSTR context, _In_ HANDLE token, PSID userSid)
{
    if (userSid)
    {
        wil::unique_hlocal_string userSidAsString;
        VERIFY_WIN32_BOOL_SUCCEEDED(ConvertSidToStringSidW(userSid, &userSidAsString));
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"UserSid:%s %s", context, userSidAsString.get()));

        wistd::unique_ptr<TOKEN_MANDATORY_LABEL> tokenMandatoryLabel;
        VERIFY_SUCCEEDED(wil::get_token_information_nothrow(tokenMandatoryLabel, token));
        const DWORD integrityLevel{ *GetSidSubAuthority((*tokenMandatoryLabel).Label.Sid, static_cast<DWORD>(static_cast<UCHAR>(*GetSidSubAuthorityCount((*tokenMandatoryLabel).Label.Sid) - 1))) };
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"IntegrityLevel: 0x%08X (%s)", integrityLevel, IntegrityLevelToString(integrityLevel)));
    }
    else
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"UserSid:%s null", context));
    }
}

void DumpExecutionContext()
{
    {
        auto tokenUser{ wil::get_token_information<TOKEN_USER>(GetCurrentThreadEffectiveToken()) };
        DumpUser(L"Effective", GetCurrentThreadEffectiveToken(), tokenUser->User.Sid);
    }

    {
        auto tokenUser{ wil::get_token_information<TOKEN_USER>(GetCurrentProcessToken()) };
        DumpUser(L"Process", GetCurrentProcessToken(), tokenUser->User.Sid);
    }

    const auto isAppContainer{ wil::get_token_is_app_container() };
    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"IsAppContainer:%s", isAppContainer ? L"True" : L"False"));

    WCHAR packageFullName[PACKAGE_FULL_NAME_MAX_LENGTH + 1]{};
    UINT32 packageFullNameLength{ static_cast<UINT32>(ARRAYSIZE(packageFullName)) };
    const auto rc = ::GetCurrentPackageFullName(&packageFullNameLength, packageFullName);
    if (rc == APPMODEL_ERROR_NO_PACKAGE)
    {
        WEX::Logging::Log::Comment(L"PackageFullName: <none>");
    }
    else if (rc == ERROR_SUCCESS)
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageFullName: %s", packageFullName));
    }
    else
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"GetCurrentPackageFullName(): %d (0x%X)", rc, rc));
    }

    std::filesystem::path currentPath{ std::filesystem::current_path() };
    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"CurrentDirectory: %s", currentPath.c_str()));
}

namespace ProjectReunionCppTest
{
    // Run tests with a variety of user contexts:
    //   * Default          - runs as the calling user (tests declare no explicit user context)
    //   * RestrictedUser   - runs as a user using an unelevated (medium-IL) token
    //   * InteractiveUser  - runs in a logged-on user account (not DefaultAccount or SYSTEM)
    //   * UAP              - runs in an app context
    //
    // Test logic is implemented in a base class (AppLifecycleTests) to facilitate executing
    // the same tests in a variety of user contexts.
    //
    // Tests also use IsolationLevel=Method:
    //   * None (default) - TAEF will not isolate any tests.
    //   * Module         - TAEF will use a separate process host for each test DLL. This is the default value.
    //   * Class          - TAEF will use a separate process host for each test class.
    //   * Method         - TAEF will use a separate process host for each test. If the test is within an execution group, the same process host will be used for the whole execution group.
    // Tests always run as IsolationLevel=Method to ensure correct execution context
    // (i.e. prevent any accidental cross-pollution)

    class AppLifecycleTests
    {
    protected:
        wil::unique_event m_failed;

        const std::wstring c_testDataFileName = L"testfile" + c_testFileExtension;
        const std::wstring c_testDataFileName_Packaged = L"testfile" + c_testFileExtension_Packaged;
        const std::wstring c_testPackageFile = g_deploymentDir + L"AppLifecycleTestPackage.msixbundle";
        const std::wstring c_testPackageCertFile = g_deploymentDir + L"AppLifecycleTestPackage.cer";
        const std::wstring c_testPackageFullName = L"AppLifecycleTestPackage_1.0.0.0_x64__ph1m9x8skttmg";

    public:
        virtual ~AppLifecycleTests() = default;

        virtual bool ClassInit()
        {
            WEX::Logging::Log::Comment(L"CLASS_SETUP---Begin---");
            DumpExecutionContext();

            ::Test::Bootstrap::SetupPackages();

            // Write out some test content.
            WriteContentFile(c_testDataFileName);
            WriteContentFile(c_testDataFileName_Packaged);

            WEX::Logging::Log::Comment(L"CLASS_SETUP ---End---");
            return true;
        }

        virtual bool ClassUninit()
        {
            WEX::Logging::Log::Comment(L"CLASS_CLEANUP ---Begin---");
            DumpExecutionContext();

            // Swallow errors in cleanup.
            try
            {
                DeleteContentFile(c_testDataFileName_Packaged);
                DeleteContentFile(c_testDataFileName);
            }
            catch (const std::exception&)
            {
            }
            catch (const winrt::hresult_error&)
            {
            }

            ::Test::Bootstrap::CleanupPackages();
            WEX::Logging::Log::Comment(L"CLASS_CLEANUP ---End---");
            return true;
        }

        virtual bool MethodInit()
        {
            WEX::Logging::Log::Comment(L"METHOD_SETUP ---Begin---");
            DumpExecutionContext();

            VERIFY_IS_TRUE(TP::IsPackageRegistered_ProjectReunionFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());

            ::Test::Bootstrap::Setup();
            m_failed = CreateTestEvent(c_testFailureEventName);

            WEX::Logging::Log::Comment(L"METHOD_SETUP ---End---");
            return true;
        }

        virtual bool MethodUninit()
        {
            WEX::Logging::Log::Comment(L"METHOD_CLEANUP ---Begin---");
            DumpExecutionContext();

            VERIFY_IS_TRUE(TP::IsPackageRegistered_ProjectReunionFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());

            ::Test::Bootstrap::Cleanup();

            WEX::Logging::Log::Comment(L"METHOD_CLEANUP ---End---");
            return true;
        }

        virtual void GetActivatedEventArgsIsNotNull()
        {
            VERIFY_IS_NOT_NULL(AppLifecycle::GetActivatedEventArgs());
        }

        virtual void GetActivatedEventArgsForLaunch()
        {
            auto args = AppLifecycle::GetActivatedEventArgs();
            VERIFY_IS_NOT_NULL(args);
            VERIFY_ARE_EQUAL(args.Kind(), ActivationKind::Launch);

            auto launchArgs = args.as<LaunchActivatedEventArgs>();
            VERIFY_IS_NOT_NULL(launchArgs);
        }

        virtual void GetActivatedEventArgsForFile_Win32()
        {
            // Create a named event for communicating with test app.
            auto event = CreateTestEvent(c_testFilePhaseEventName);

            // Launch the test app to register for protocol launches.
            Execute(L"AppLifecycleTestApp.exe", L"/RegisterFile", g_deploymentDir);

            // Wait for the register event.
            WaitForEvent(event, m_failed);

            // Launch the file and wait for the event to fire.
            auto file = OpenDocFile(c_testDataFileName);
            auto launchResult = Launcher::LaunchFileAsync(file).get();
            VERIFY_IS_TRUE(launchResult);

            // Wait for the protocol activation.
            WaitForEvent(event, m_failed);
        }

        virtual void GetActivatedEventArgsForProtocol_Win32()
        {
            // Create a named event for communicating with test app.
            auto event{ CreateTestEvent(c_testProtocolPhaseEventName) };

            // Cleanup any leftover data from previous runs i.e. ensure we running with a clean slate
            Execute(L"AppLifecycleTestApp.exe", L"/UnregisterProtocol", g_deploymentDir);
            WaitForEvent(event, m_failed);

            // Register the protocol
            Execute(L"AppLifecycleTestApp.exe", L"/RegisterProtocol", g_deploymentDir);
            WaitForEvent(event, m_failed);

            // Launch a URI with the protocol schema and wait for the app to fire the event
            Uri launchUri{ c_testProtocolScheme + L"://this_is_a_test" };
            auto launchResult{ Launcher::LaunchUriAsync(launchUri).get() };
            VERIFY_IS_TRUE(launchResult);
            WaitForEvent(event, m_failed);

            // Deregister the protocol
            Execute(L"AppLifecycleTestApp.exe", L"/UnregisterProtocol", g_deploymentDir);
            WaitForEvent(event, m_failed);
        }
    };

    class AppLifecycleFunctionalTests_DefaultUser : public AppLifecycleTests
    {
    public:
        typedef AppLifecycleTests super;

        BEGIN_TEST_CLASS(AppLifecycleFunctionalTests_DefaultUser)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            return super::ClassInit();
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            return super::ClassUninit();
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            return super::MethodInit();
        }

        TEST_METHOD_CLEANUP(MethodShutdown)
        {
            return super::MethodUninit();
        }

        TEST_METHOD(GetActivatedEventArgsIsNotNull)
        {
            super::GetActivatedEventArgsIsNotNull();
        }

        TEST_METHOD(GetActivatedEventArgsForLaunch)
        {
            super::GetActivatedEventArgsForLaunch();
        }

        TEST_METHOD(GetActivatedEventArgsForFile_Win32)
        {
            super::GetActivatedEventArgsForFile_Win32();
        }

        TEST_METHOD(GetActivatedEventArgsForProtocol_Win32)
        {
            super::GetActivatedEventArgsForProtocol_Win32();
        }
    };

    class AppLifecycleFunctionalTests_InteractiveUser : public AppLifecycleTests
    {
    public:
        typedef AppLifecycleTests super;

        BEGIN_TEST_CLASS(AppLifecycleFunctionalTests_InteractiveUser)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"InteractiveUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"InteractiveUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            return super::ClassInit();
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            return super::ClassUninit();
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            return super::MethodInit();
        }

        TEST_METHOD_CLEANUP(MethodShutdown)
        {
            return super::MethodUninit();
        }

        TEST_METHOD(GetActivatedEventArgsIsNotNull)
        {
            super::GetActivatedEventArgsIsNotNull();
        }

        TEST_METHOD(GetActivatedEventArgsForLaunch)
        {
            super::GetActivatedEventArgsForLaunch();
        }

        TEST_METHOD(GetActivatedEventArgsForFile_Win32)
        {
            super::GetActivatedEventArgsForFile_Win32();
        }

        TEST_METHOD(GetActivatedEventArgsForProtocol_Win32)
        {
            super::GetActivatedEventArgsForProtocol_Win32();
        }
    };

    class AppLifecycleFunctionalTests_RestrictedUser : public AppLifecycleTests
    {
    public:
        typedef AppLifecycleTests super;

        BEGIN_TEST_CLASS(AppLifecycleFunctionalTests_RestrictedUser)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunAs", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            return super::ClassInit();
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            return super::ClassUninit();
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            return super::MethodInit();
        }

        TEST_METHOD_CLEANUP(MethodShutdown)
        {
            return super::MethodUninit();
        }

        TEST_METHOD(GetActivatedEventArgsIsNotNull)
        {
            super::GetActivatedEventArgsIsNotNull();
        }

        TEST_METHOD(GetActivatedEventArgsForLaunch)
        {
            super::GetActivatedEventArgsForLaunch();
        }

        TEST_METHOD(GetActivatedEventArgsForFile_Win32)
        {
            super::GetActivatedEventArgsForFile_Win32();
        }

        TEST_METHOD(GetActivatedEventArgsForProtocol_Win32)
        {
            super::GetActivatedEventArgsForProtocol_Win32();
        }
    };

    //-----------------------------------------------------------------

    class AppLifecycleTestsUAP
    {
    protected:
        wil::unique_event m_failed;

        const std::wstring c_testDataFileName = L"testfile" + c_testFileExtension;
        const std::wstring c_testDataFileName_Packaged = L"testfile" + c_testFileExtension_Packaged;
        const std::wstring c_testPackageFile = g_deploymentDir + L"AppLifecycleTestPackage.msixbundle";
        const std::wstring c_testPackageCertFile = g_deploymentDir + L"AppLifecycleTestPackage.cer";
        const std::wstring c_testPackageFullName = L"AppLifecycleTestPackage_1.0.0.0_x64__ph1m9x8skttmg";

    public:
        virtual ~AppLifecycleTestsUAP() = default;

        BEGIN_TEST_CLASS(AppLifecycleTestsUAP)
            //TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunFixtureAs:Class", L"InteractiveUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            WEX::Logging::Log::Comment(L"CLASS_SETUP---Begin---");
            DumpExecutionContext();

            ::Test::Bootstrap::SetupPackages();

            // Write out some test content.
            WriteContentFile(c_testDataFileName);
            WriteContentFile(c_testDataFileName_Packaged);

            WEX::Logging::Log::Comment(L"CLASS_SETUP ---End---");
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            WEX::Logging::Log::Comment(L"CLASS_CLEANUP ---Begin---");
            DumpExecutionContext();

            // Swallow errors in cleanup.
            try
            {
                DeleteContentFile(c_testDataFileName_Packaged);
                DeleteContentFile(c_testDataFileName);
            }
            catch (const std::exception&)
            {
            }
            catch (const winrt::hresult_error&)
            {
            }

            ::Test::Bootstrap::CleanupPackages();
            WEX::Logging::Log::Comment(L"CLASS_CLEANUP ---End---");
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            WEX::Logging::Log::Comment(L"METHOD_SETUP ---Begin---");
            DumpExecutionContext();

            VERIFY_IS_TRUE(TP::IsPackageRegistered_ProjectReunionFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());

            m_failed = CreateTestEvent(c_testFailureEventName);

            WEX::Logging::Log::Comment(L"METHOD_SETUP ---End---");
            return true;
        }

        TEST_METHOD_CLEANUP(MethodShutdown)
        {
            WEX::Logging::Log::Comment(L"METHOD_CLEANUP ---Begin---");
            DumpExecutionContext();

            VERIFY_IS_TRUE(TP::IsPackageRegistered_ProjectReunionFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());

            WEX::Logging::Log::Comment(L"METHOD_CLEANUP ---End---");
            return true;
        }

        TEST_METHOD(GetActivatedEventArgsIsNull_UAP)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"UAP")
                TEST_METHOD_PROPERTY(L"UAP:AppxManifest", L"AppLifecycle-AppxManifest.xml")
            END_TEST_METHOD_PROPERTIES();

            DumpExecutionContext();

            VERIFY_IS_NULL(AppLifecycle::GetActivatedEventArgs());
        }
    };
}
