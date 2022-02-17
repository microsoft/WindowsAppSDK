#include "pch.h"
#include "NotificationActivationCallback.h"
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
                // Cleanup previous installations. Need this to remove any manual installations outside of running this tests.
                TP::RemovePackage(GetTestPackageFullName());
                TP::RemovePackage_PushNotificationsLongRunningTask();
                TP::RemovePackage_DynamicDependencyLifetimeManager();
                TP::RemovePackage_DynamicDependencyDataStore();
                TP::RemovePackage_WindowsAppRuntimeFramework();

                TP::AddPackage_WindowsAppRuntimeFramework();       // Installs WARfwk
                TP::AddPackage_DynamicDependencyDataStore();       // Installs WARmain
                TP::AddPackage_DynamicDependencyLifetimeManager(); // Installs WARddlm
                TP::AddPackage_PushNotificationsLongRunningTask(); // Installs the PushNotifications long running task.
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
                TP::RemovePackage_PushNotificationsLongRunningTask();
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
            VERIFY_IS_TRUE(TP::IsPackageRegistered_PushNotificationsLongRunningTask());
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyDataStore());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_DynamicDependencyLifetimeManager());
            VERIFY_IS_TRUE(TP::IsPackageRegistered_PushNotificationsLongRunningTask());

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

        wil::unique_handle RunUnpackaged(const std::wstring& command, const std::wstring& args, const std::wstring& directory)
        {
            SHELLEXECUTEINFO ei{};
            ei.cbSize = sizeof(SHELLEXECUTEINFO);
            ei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_DOENVSUBST;
            ei.lpFile = command.c_str();
            ei.lpParameters = args.c_str();
            ei.lpDirectory = directory.c_str();
            ei.nShow = SW_NORMAL;

            if (!ShellExecuteEx(&ei))
            {
                auto lastError = GetLastError();
                VERIFY_WIN32_SUCCEEDED(lastError);
            }

            wil::unique_handle process{ ei.hProcess };
            return process;
        }

        const std::wstring GetDeploymentDir()
        {
            WEX::Common::String deploymentDir;
            WEX::TestExecution::RuntimeParameters::TryGetValue(L"TestDeploymentDir", deploymentDir);
            return reinterpret_cast<PCWSTR>(deploymentDir.GetBuffer());
        }

        void RunTestUnpackaged(const PCWSTR& testName, const int& waitTime)
        {
            auto processHandle = RunUnpackaged(L"ToastNotificationsTestApp.exe", testName, GetDeploymentDir());
            VERIFY_IS_TRUE(processHandle.is_valid());

            VERIFY_IS_TRUE(wil::handle_wait(processHandle.get(), waitTime));

            DWORD exitCode{};
            VERIFY_WIN32_BOOL_SUCCEEDED(GetExitCodeProcess(processHandle.get(), &exitCode));
            VERIFY_ARE_EQUAL(exitCode, 0);
        }

        TEST_METHOD(VerifyBackgroundActivation)
        {
            RunTest(L"BackgroundActivationTest", testWaitTime()); // Need to launch one time to enable background activation.

            auto toastActivationCallback = winrt::create_instance<INotificationActivationCallback>(c_toastComServerId, CLSCTX_ALL);
            VERIFY_SUCCEEDED(toastActivationCallback->Activate(L"AUMID", L"args", nullptr, 0));

            RunTest(L"UnregisterBackgroundActivationTest", testWaitTime()); // Need to launch again to unregister activation
        }

        TEST_METHOD(VerifyFailedRegisterActivatorUsingNullClsid)
        {
            RunTest(L"VerifyFailedRegisterActivatorUsingNullClsid", testWaitTime());
        }

        TEST_METHOD(VerifyFailedRegisterActivatorUsingNullClsid_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyFailedRegisterActivatorUsingNullClsid_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyFailedRegisterActivatorUsingNullActivationInfo)
        {
            RunTest(L"VerifyFailedRegisterActivatorUsingNullActivationInfo", testWaitTime());
        }

        TEST_METHOD(VerifyFailedRegisterActivatorUsingNullActivationInfo_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyFailedRegisterActivatorUsingNullActivationInfo_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyRegisterActivatorandUnRegisterActivatorUsingClsid)
        {
            RunTest(L"VerifyRegisterActivatorandUnRegisterActivatorUsingClsid", testWaitTime());
        }

        TEST_METHOD(VerifyFailedMultipleRegisterActivatorUsingSameClsid)
        {
            RunTest(L"VerifyFailedMultipleRegisterActivatorUsingSameClsid", testWaitTime());
        }

        TEST_METHOD(VerifyRegisterActivatorandUnRegisterActivatorUsingAssets_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRegisterActivatorandUnRegisterActivatorUsingAssets_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyFailedMultipleRegisterActivatorUsingSameAssets_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyFailedMultipleRegisterActivatorUsingSameAssets_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyFailedToastAssetsWithEmptyDisplayName_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyFailedToastAssetsWithEmptyDisplayName_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyFailedToastAssetsWithEmptyIconPath_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyFailedToastAssetsWithEmptyIconPath_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyFailedToastAssetsWithNullIconPath_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyFailedToastAssetsWithEmptyIconPath_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyToastSettingEnabled_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyToastSettingEnabled", testWaitTime());
        }

        TEST_METHOD(VerifyToastSettingEnabled)
        {
            RunTest(L"VerifyToastSettingEnabled", testWaitTime());
        }

        TEST_METHOD(VerifyToastPayload)
        {
            RunTest(L"VerifyToastPayload", testWaitTime());
        }

        TEST_METHOD(VerifyToastPayload_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyToastPayload", testWaitTime());
        }

        TEST_METHOD(VerifyToastTag)
        {
            RunTest(L"VerifyToastTag", testWaitTime());
        }

        TEST_METHOD(VerifyToastTag_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyToastTag", testWaitTime());
        }

        TEST_METHOD(VerifyToastGroup)
        {
            RunTest(L"VerifyToastGroup", testWaitTime());
        }

        TEST_METHOD(VerifyToastGroup_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyToastGroup", testWaitTime());
        }

        TEST_METHOD(VerifyToastProgressDataFromToast)
        {
            RunTest(L"VerifyToastProgressDataFromToast", testWaitTime());
        }

        TEST_METHOD(VerifyToastProgressDataFromToast_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyToastProgressDataFromToast", testWaitTime());
        }

        TEST_METHOD(VerifyToastExpirationTime)
        {
            RunTest(L"VerifyToastExpirationTime", testWaitTime());
        }

        TEST_METHOD(VerifyToastExpirationTime_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyToastExpirationTime", testWaitTime());
        }

        TEST_METHOD(VerifyToastPriority)
        {
            RunTest(L"VerifyToastPriority", testWaitTime());
        }

        TEST_METHOD(VerifyToastPriority_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyToastPriority", testWaitTime());
        }

        TEST_METHOD(VerifyToastSuppressDisplay)
        {
            RunTest(L"VerifyToastSuppressDisplay", testWaitTime());
        }

        TEST_METHOD(VerifyToastSuppressDisplay_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyToastSuppressDisplay", testWaitTime());
        }

        TEST_METHOD(VerifyToastExpiresOnReboot)
        {
            RunTest(L"VerifyToastExpiresOnReboot", testWaitTime());
        }

        TEST_METHOD(VerifyToastExpiresOnReboot_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyToastExpiresOnReboot", testWaitTime());
        }

        TEST_METHOD(VerifyShowToast)
        {
            RunTest(L"VerifyShowToast", testWaitTime());
        }

        TEST_METHOD(VerifyShowToast_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyShowToast_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyUpdateToastProgressDataUsingValidTagAndValidGroup)
        {
            RunTest(L"VerifyUpdateToastProgressDataUsingValidTagAndValidGroup", testWaitTime());
        }

        TEST_METHOD(VerifyUpdateToastProgressDataUsingValidTagAndValidGroup_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyUpdateToastProgressDataUsingValidTagAndValidGroup_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup)
        {
            RunTest(L"VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup", testWaitTime());
        }

        TEST_METHOD(VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyUpdateToastProgressDataUsingValidTagAndEmptyGroup", testWaitTime());
        }

        TEST_METHOD(VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup)
        {
            RunTest(L"VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup", testWaitTime());
        }

        TEST_METHOD(VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyFailedUpdateNotificationDataWithNonExistentTagAndGroup_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyFailedUpdateNotificationDataWithoutPostToast)
        {
            RunTest(L"VerifyFailedUpdateNotificationDataWithoutPostToast", testWaitTime());
        }

        TEST_METHOD(VerifyFailedUpdateNotificationDataWithoutPostToast_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyFailedUpdateNotificationDataWithoutPostToast_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyUpdateToastProgressDataUsingEmptyTagAndValidGroup)
        {
            RunTest(L"VerifyUpdateToastProgressDataUsingEmptyTagAndValidGroup", testWaitTime());
        }

        TEST_METHOD(VerifyUpdateToastProgressDataUsingEmptyTagAndValidGroup_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyUpdateToastProgressDataUsingEmptyTagAndValidGroup", testWaitTime());
        }

        TEST_METHOD(VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup)
        {
            RunTest(L"VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup", testWaitTime());
        }

        TEST_METHOD(VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyUpdateToastProgressDataUsingEmptyTagAndEmptyGroup", testWaitTime());
        }

        TEST_METHOD(VerifyGetAllAsyncWithZeroActiveToast)
        {
            RunTest(L"VerifyGetAllAsyncWithZeroActiveToast", testWaitTime());
        }

        TEST_METHOD(VerifyGetAllAsyncWithZeroActiveToast_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyGetAllAsyncWithZeroActiveToast", testWaitTime());
        }

        TEST_METHOD(VerifyGetAllAsyncWithOneActiveToast)
        {
            RunTest(L"VerifyGetAllAsyncWithOneActiveToast", testWaitTime());
        }

        TEST_METHOD(VerifyGetAllAsyncWithOneActiveToast_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyGetAllAsyncWithOneActiveToast", testWaitTime());
        }

        TEST_METHOD(VerifyGetAllAsyncWithMultipleActiveToasts)
        {
            RunTest(L"VerifyGetAllAsyncWithMultipleActiveToasts", testWaitTime());
        }

        TEST_METHOD(VerifyGetAllAsyncWithMultipleActiveToasts_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyGetAllAsyncWithMultipleActiveToasts", testWaitTime());
        }

        TEST_METHOD(VerifyGetAllAsyncIgnoresUpdatesToProgressData)
        {
            RunTest(L"VerifyGetAllAsyncIgnoresUpdatesToProgressData", testWaitTime());
        }

        TEST_METHOD(VerifyGetAllAsyncIgnoresUpdatesToProgressData_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyGetAllAsyncIgnoresUpdatesToProgressData", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier)
        {
            RunTest(L"VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveWithIdentifierAsyncUsingZeroedToastIdentifier", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow)
        {
            RunTest(L"VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveWithIdentifierAsyncUsingNonActiveToastIdentifierDoesNotThrow", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier)
        {
            RunTest(L"VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveWithIdentifierAsyncUsingActiveToastIdentifier", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagAsyncUsingEmptyTagThrows)
        {
            RunTest(L"VerifyRemoveWithTagAsyncUsingEmptyTagThrows", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagAsyncUsingEmptyTagThrows_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveWithTagAsyncUsingEmptyTagThrows", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow)
        {
            RunTest(L"VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveWithTagAsyncUsingNonExistentTagDoesNotThrow", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagAsync)
        {
            RunTest(L"VerifyRemoveWithTagAsync", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagAsync_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveWithTagAsync", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows)
        {
            RunTest(L"VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveWithTagGroupAsyncUsingEmptyTagThrows", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows)
        {
            RunTest(L"VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveWithTagGroupAsyncUsingEmptyGroupThrows", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagGroupAsyncUsingNonExistentTagGroupDoesNotThrow)
        {
            RunTest(L"VerifyRemoveWithTagGroupAsyncUsingNonExistentTagGroupDoesNotThrow", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagGroupAsyncUsingNonExistentTagGroupDoesNotThrow_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveWithTagGroupAsyncUsingNonExistentTagGroupDoesNotThrow", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagGroupAsync)
        {
            RunTest(L"VerifyRemoveWithTagGroupAsync", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveWithTagGroupAsync_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveWithTagGroupAsync", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveGroupAsyncUsingEmptyGroupThrows)
        {
            RunTest(L"VerifyRemoveGroupAsyncUsingEmptyGroupThrows", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveGroupAsyncUsingEmptyGroupThrows_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveGroupAsyncUsingEmptyGroupThrows", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow)
        {
            RunTest(L"VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveGroupAsyncUsingNonExistentGroupDoesNotThrow", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveGroupAsync)
        {
            RunTest(L"VerifyRemoveGroupAsync", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveGroupAsync_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveGroupAsync", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow)
        {
            RunTest(L"VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveAllAsyncWithNoActiveToastDoesNotThrow", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveAllAsync)
        {
            RunTest(L"VerifyRemoveAllAsync", testWaitTime());
        }

        TEST_METHOD(VerifyRemoveAllAsync_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyRemoveAllAsync", testWaitTime());
        }

        TEST_METHOD(VerifyExplicitAppId_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyExplicitAppId_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyUnregisterAll_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyUnregisterAll_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyUnregisterAll)
        {
            RunTest(L"VerifyUnregisterAll", testWaitTime());
        }

        TEST_METHOD(VerifyUnregisterTwice_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyUnregisterTwice_Unpackaged", testWaitTime());
        }

        TEST_METHOD(VerifyUnregisterTwice)
        {
            RunTest(L"VerifyUnregisterTwice", testWaitTime());
        }

        TEST_METHOD(VerifyToastProgressDataSequence0Fail)
        {
            RunTest(L"VerifyToastProgressDataSequence0Fail", testWaitTime());
        }

        TEST_METHOD(VerifyToastUpdateZeroSequenceFail_Unpackaged)
        {
            RunTestUnpackaged(L"VerifyToastUpdateZeroSequenceFail_Unpackaged", testWaitTime());
        }
    };
}
