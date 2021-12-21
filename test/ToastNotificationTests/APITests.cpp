#include "pch.h"
#include <TestDef.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::System;

namespace Test::ToastNotifications
{
    class APITests
    {
    private:
        wil::unique_event m_failed;
        wil::unique_process_handle m_processHandle;
        winrt::com_ptr<IApplicationActivationManager> m_testAppLauncher;

    public:
        BEGIN_TEST_CLASS(APITests)
            TEST_CLASS_PROPERTY(L"Description", L"Windows App SDK Toast Notifications test")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs:Class", L"RestrictedUser")
        END_TEST_CLASS()

        static const int testWaitTime()
        {
            return 3000;
        }

        static PCWSTR GetTestPackageFile()
        {
            return L"ToastNotificationsTestAppPackage";
        }

        static PCWSTR GetTestPackageFullName()
        {
            return L"ToastNotificationsTestAppPackage_1.0.0.0_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE L"__8wekyb3d8bbwe";
        }

        TEST_CLASS_SETUP(ClassInit)
        {
            try
            {
                TP::RemovePackage(GetTestPackageFullName());
                TP::RemovePackage_DynamicDependencyLifetimeManager();
                TP::RemovePackage_DynamicDependencyDataStore();
                TP::RemovePackage_WindowsAppRuntimeFramework();
                TP::AddPackage_WindowsAppRuntimeFramework();       // Installs WARfwk
                TP::AddPackage_DynamicDependencyDataStore();       // Installs WARmain
                TP::AddPackage_DynamicDependencyLifetimeManager(); // Installs WARddlm
                TP::WapProj::AddPackage(TAEF::GetDeploymentDir(), GetTestPackageFile(), L".msix"); // Installs ToastNotificationsTestApp.msix
            }
            catch (...)
            {
                return false;
            }

            m_testAppLauncher = winrt::create_instance<IApplicationActivationManager>(CLSID_ApplicationActivationManager, CLSCTX_ALL);

            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            try
            {
                // Remove in reverse order to avoid conflicts between inter-dependent packages.
                TP::RemovePackage(GetTestPackageFullName());
                TP::RemovePackage_DynamicDependencyLifetimeManager();
                TP::RemovePackage_DynamicDependencyDataStore();
                TP::RemovePackage_WindowsAppRuntimeFramework();
            }
            catch (...)
            {
                return false;
            }
            return true;
        }

        TEST_METHOD_SETUP(MethodInit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());

            m_processHandle.reset();
            return true;
        }

        void RunTest(const PCWSTR& testName, const int& waitTime)
        {
            DWORD processId{};
            VERIFY_SUCCEEDED(m_testAppLauncher->ActivateApplication(L"ToastNotificationsTestAppPackage_8wekyb3d8bbwe!App", testName, AO_NONE, &processId));

            m_processHandle.reset(OpenProcess(SYNCHRONIZE | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId));
            VERIFY_IS_TRUE(m_processHandle.is_valid());

            VERIFY_IS_TRUE(wil::handle_wait(m_processHandle.get(), waitTime));

            DWORD exitCode{};
            VERIFY_WIN32_BOOL_SUCCEEDED(GetExitCodeProcess(m_processHandle.get(), &exitCode));
            VERIFY_ARE_EQUAL(exitCode, 0);
        }

        TEST_METHOD(VerifyFailedRegisterActivatorUsingNullClsid)
        {
            RunTest(L"VerifyFailedRegisterActivatorUsingNullClsid", testWaitTime());
        }

        TEST_METHOD(VerifyFailedRegisterActivatorUsingNullClsid_Unpackaged)
        {
            // TODO
        }

        TEST_METHOD(VerifyFailedRegisterActivatorUsingNullAssets)
        {
            RunTest(L"VerifyFailedRegisterActivatorUsingNullAssets", testWaitTime());
        }

        TEST_METHOD(VerifyFailedRegisterActivatorUsingNullAssets_Unpackaged)
        {
            // TODO
        }

        TEST_METHOD(VerifyRegisterActivatorandUnRegisterActivatorUsingClsid)
        {
            RunTest(L"VerifyRegisterActivatorandUnRegisterActivatorUsingClsid", testWaitTime());
        }

        TEST_METHOD(VerifyFailedMultipleRegisterActivatorUsingSameClsid)
        {
            RunTest(L"VerifyFailedMultipleRegisterActivatorUsingSameClsid", testWaitTime());
        }
    };
}
