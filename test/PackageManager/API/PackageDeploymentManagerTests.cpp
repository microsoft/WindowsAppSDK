// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TPF = ::Test::Packages::Framework;
namespace TPMT = ::Test::PackageManager::Tests;

namespace Test::PackageManager::Tests
{
    class PackageDeploymentManagerTests_Base
    {
    protected:
        winrt::Windows::ApplicationModel::PackageStatus GetPackageStatus(PCWSTR packageFullName)
        {
            return TPMT::GetPackageStatus(m_packageManager, packageFullName);
        }

        void SetPackageStatus(PCWSTR packageFullName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            TPMT::SetPackageStatus(m_packageManager, packageFullName, status);
        }

        void SetPackageStatusByPackageFamilyName(PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            TPMT::SetPackageStatusByPackageFamilyName(m_packageManager, packageFamilyName, status);
        }

        void ClearPackageStatus(PCWSTR packageFullName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            TPMT::ClearPackageStatus(m_packageManager, packageFullName, status);
        }

        void ClearPackageStatusByPackageFamilyName(PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            TPMT::ClearPackageStatusByPackageFamilyName(m_packageManager, packageFamilyName, status);
        }

        winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult WaitForDeploymentOperation(
            winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentResult, winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentProgress>& deploymentOperation)
        {
            using namespace winrt::Windows::Foundation;
            using namespace winrt::Microsoft::Windows::Management::Deployment;
            AsyncOperationProgressHandler<PackageDeploymentResult, PackageDeploymentProgress> progressCallback(
                [&](const IAsyncOperationWithProgress<PackageDeploymentResult, PackageDeploymentProgress>&, PackageDeploymentProgress progress)
            {
                    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"...State:%d Percentage:%lf", static_cast<int>(progress.Status), progress.Progress));
                }
            );
            deploymentOperation.Progress(progressCallback);
            auto deploymentResult{ deploymentOperation.get() };
            return deploymentResult;
        }

    protected:
        winrt::Windows::Management::Deployment::PackageManager m_packageManager;
    };

    class PackageDeploymentManagerTests : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!::WindowsVersion::IsWindows10_20H1OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageDeploymentManager requires >= 20H1 (Vibranium). Skipping tests");
                return true;
            }
            RemovePackage_Blue();
            RemovePackage_Green();
            RemovePackage_Redder();
            RemovePackage_Red();
            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            RemovePackage_Blue();
            RemovePackage_Green();
            RemovePackage_Redder();
            RemovePackage_Red();
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(IsPackageSetReady_InvalidParameter)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                packageDeploymentManager.IsPackageSetReady(packageSet);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);

                packageDeploymentManager.IsPackageSetReady(packageSet);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                packageSet.Items().Append(packageSetItem);

                packageDeploymentManager.IsPackageSetReady(packageSet);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageFamilyName{ L"Not a valid Package Family Name" };
                packageSetItem.PackageFamilyName(c_packageFamilyName);
                packageSet.Items().Append(packageSetItem);

                packageDeploymentManager.IsPackageSetReady(packageSet);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
                packageSetItem.PackageFamilyName(c_packageFamilyName);
                packageSet.Items().Append(packageSetItem);

                packageDeploymentManager.IsPackageSetReady(packageSet);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageUriAsString{ L"https://doesnotexist.com/assemble.msix" };
                winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };
                packageSetItem.PackageUri(packageUri);
                packageSet.Items().Append(packageSetItem);

                packageDeploymentManager.IsPackageSetReady(packageSet);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(IsPackageSetReady_1_NoSuchPackage_No)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"Does.Not.Exist" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
            PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
            packageSetItem.PackageFamilyName(c_packageFamilyName);
            PCWSTR c_packageUriAsString{ L"file://c:/does/not/exist.msix" };
            winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };
            packageSetItem.PackageUri(packageUri);
            packageSet.Items().Append(packageSetItem);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(IsPackageSetReady_1_NotInstalled_No)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(IsPackageSetReady_1_Registered_Yes)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(IsPackageSetReady_1_OlderRegistered_No)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem(::TPF::Redder::GetPackageFullName(), ::TPF::Redder::c_packageDirName) };
            packageSet.Items().Append(redder);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(IsPackageSetReady_1_NewerRegistered_Yes)
        {
            AddPackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(IsPackageSetReady_N_NotInstalled_No)
        {
            RemovePackage_Red();
            RemovePackage_Green();
            RemovePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(IsPackageSetReady_N_Registered_Yes)
        {
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(IsPackageSetReady_N_OlderRegistered_No)
        {
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem(::TPF::Redder::GetPackageFullName(), ::TPF::Redder::c_packageDirName) };
            packageSet.Items().Append(redder);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(IsPackageSetReady_N_NewerRegistered_Yes)
        {
            AddPackage_Redder();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(IsPackageSetReady_N_RegisteredAndNotInstalled_No)
        {
            AddPackage_Red();
            RemovePackage_Green();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(IsPackageSetReady_N_No_NotAllPackageStatusOK)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            AddPackage_Green();
            SetPackageStatusByPackageFamilyName(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));

            ClearPackageStatusByPackageFamilyName(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_InvalidParameter)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
                auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);

                winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
                auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                packageSet.Items().Append(packageSetItem);

                winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
                auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageFamilyName{ L"Not a valid Package Family Name" };
                packageSetItem.PackageFamilyName(c_packageFamilyName);
                packageSet.Items().Append(packageSetItem);

                winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
                auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
                packageSetItem.PackageFamilyName(c_packageFamilyName);
                packageSet.Items().Append(packageSetItem);

                winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
                auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageUriAsString{ L"file://c:/assemble.msix" };
                winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };
                packageSetItem.PackageUri(packageUri);
                packageSet.Items().Append(packageSetItem);

                winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
                auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_1_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"Does.Not.Exist" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
            PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
            packageSetItem.PackageFamilyName(c_packageFamilyName);
            PCWSTR c_packageUriAsString{ L"file://c:/does/not/exist.msix" };
            winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };
            packageSetItem.PackageUri(packageUri);
            packageSet.Items().Append(packageSetItem);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_1_NotInstalled_Success)
        {
            RemovePackageFamily_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_1_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_1_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_1_OlderRegistered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem(::TPF::Redder::GetPackageFullName(), ::TPF::Redder::c_packageDirName) };
            packageSet.Items().Append(redder);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_1_NewerRegistered_Success)
        {
            AddPackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_N_NotInstalled_Success)
        {
            RemovePackageFamily_Red();
            RemovePackage_Green();
            RemovePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_N_Registered_Success)
        {
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_N_NewerRegistered_Success)
        {
            AddPackage_Redder();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_N_OlderRegistered_Success)
        {
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem(::TPF::Redder::GetPackageFullName(), ::TPF::Redder::c_packageDirName) };
            packageSet.Items().Append(redder);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_N_RegisteredAndNotInstalled_Success)
        {
            AddPackage_Red();
            RemovePackage_Green();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_N_RegisteredAndNotInstalledAndStaged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            AddPackage_Red();
            RemovePackage_Green();
            StagePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(AddPackageAsync_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR package{ L"c:\\does\\not\\exist.msix" };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
        }

        TEST_METHOD(AddPackageAsync_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(AddPackageAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(AddPackageAsync_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(AddPackageAsync_OlderRegistered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageAsync_NewerRegistered_Success)
        {
            AddPackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Redder());

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageByUriAsync_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR c_packageUriAsString{ L"file://c:/does/not/exist.msix" };
            winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
        }

        TEST_METHOD(AddPackageByUriAsync_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(AddPackageByUriAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(AddPackageByUriAsync_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(AddPackageByUriAsync_OlderRegistered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageByUriAsync_NewerRegistered_Success)
        {
            AddPackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Redder());

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageSetAsync_1_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"Does.Not.Exist" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
            PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
            packageSetItem.PackageFamilyName(c_packageFamilyName);
            PCWSTR c_packageUriAsString{ L"file://c:/does/not/exist.msix" };
            winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };
            packageSetItem.PackageUri(packageUri);
            packageSet.Items().Append(packageSetItem);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(AddPackageSetAsync_1_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(AddPackageSetAsync_1_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(AddPackageSetAsync_1_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(AddPackageSetAsync_1_OlderRegistered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem(::TPF::Redder::GetPackageFullName(), ::TPF::Redder::c_packageDirName) };
            packageSet.Items().Append(redder);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageSetAsync_1_NewerRegistered_Success)
        {
            AddPackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageSetAsync_N_NotInstalled_Success)
        {
            RemovePackage_Red();
            RemovePackage_Green();
            RemovePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(AddPackageSetAsync_N_Registered_Success)
        {
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(AddPackageSetAsync_N_NewerRegistered_Success)
        {
            AddPackage_Redder();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageSetAsync_N_OlderRegistered_Success)
        {
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem(::TPF::Redder::GetPackageFullName(), ::TPF::Redder::c_packageDirName) };
            packageSet.Items().Append(redder);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageSetAsync_N_RegisteredAndNotInstalled_Success)
        {
            AddPackage_Red();
            RemovePackage_Green();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(AddPackageSetAsync_N_RegisteredAndNotInstalledAndStaged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            AddPackage_Red();
            RemovePackage_Green();
            StagePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageAsync_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR package{ L"c:\\does\\not\\exist.msix" };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            //
            // NOTE: ExtendedError() should be HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND) but on some platforms may be S_OK (and also ErrorText() may be empty)
            VERIFY_IS_TRUE((deploymentResult.ExtendedError() == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND)) || (deploymentResult.ExtendedError() == S_OK), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            if (FAILED(deploymentResult.ExtendedError()))
            {
                VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
            }
        }

        TEST_METHOD(StagePackageAsync_NotInstalled_Success)
        {
            RemovePackageFamily_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RemovePackageFamily_Red();
            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageAsync_Registered_Success)
        {
            RemovePackageFamily_Red();
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageAsync_OlderStaged_Success)
        {
            RemovePackageFamily_Red();
            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(IsPackageStaged_Redder());

            RemovePackage_Redder();
        }

        TEST_METHOD(StagePackageAsync_NewerStaged_Success)
        {
            RemovePackageFamily_Redder();
            StagePackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Redder());

            RemovePackageFamily_Redder();
        }

        TEST_METHOD(StagePackageByUriAsync_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR c_packageUriAsString{ L"file://c:/does/not/exist.msix" };
            winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            //
            // NOTE: ExtendedError() should be HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND) but on some platforms may be S_OK (and also ErrorText() may be empty)
            VERIFY_IS_TRUE((deploymentResult.ExtendedError() == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND)) || (deploymentResult.ExtendedError() == S_OK), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            if (FAILED(deploymentResult.ExtendedError()))
            {
                VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
            }
        }

        TEST_METHOD(StagePackageByUriAsync_NotInstalled_Success)
        {
            RemovePackageFamily_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageByUriAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RemovePackageFamily_Red();
            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageByUriAsync_Registered_Success)
        {
            RemovePackageFamily_Red();
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageByUriAsync_OlderStaged_Success)
        {
            RemovePackageFamily_Red();
            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(IsPackageStaged_Redder());

            RemovePackageFamily_Redder();
        }

        TEST_METHOD(StagePackageByUriAsync_NewerStaged_Success)
        {
            RemovePackageFamily_Redder();
            StagePackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Redder());

            RemovePackageFamily_Redder();
        }

        TEST_METHOD(StagePackageSetAsync_1_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"Does.Not.Exist" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
            PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
            packageSetItem.PackageFamilyName(c_packageFamilyName);
            PCWSTR c_packageUriAsString{ L"file://c:/does/not/exist.msix" };
            winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };
            packageSetItem.PackageUri(packageUri);
            packageSet.Items().Append(packageSetItem);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            //
            // NOTE: ExtendedError() should be HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND) but on some platforms may be S_OK (and also ErrorText() may be empty)
            VERIFY_IS_TRUE((deploymentResult.ExtendedError() == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND)) || (deploymentResult.ExtendedError() == S_OK), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            if (FAILED(deploymentResult.ExtendedError()))
            {
                VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
            }

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_1_NotInstalled_Success)
        {
            RemovePackageFamily_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_1_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RemovePackageFamily_Red();
            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_1_Registered_Success)
        {
            RemovePackageFamily_Red();
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_1_OlderStaged_Success)
        {
            RemovePackageFamily_Red();
            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem(::TPF::Redder::GetPackageFullName(), ::TPF::Redder::c_packageDirName) };
            packageSet.Items().Append(redder);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageStaged_Redder());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackageFamily_Red();
        }

        TEST_METHOD(StagePackageSetAsync_1_NewerStaged_Success)
        {
            RemovePackageFamily_Red();
            StagePackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageStaged_Redder());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_NoSuchPackage_Fail)
        {
            RemovePackageFamily_Red();
            RemovePackage_Blue();
            StagePackage_Red();
            StagePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"Does.Not.Exist" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
            PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
            packageSetItem.PackageFamilyName(c_packageFamilyName);
            PCWSTR c_packageUriAsString{ L"file://c:/does/not/exist.msix" };
            winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };
            packageSetItem.PackageUri(packageUri);
            packageSet.Items().Append(packageSetItem);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            //
            // NOTE: ExtendedError() should be HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND) but on some platforms may be S_OK (and also ErrorText() may be empty)
            VERIFY_IS_TRUE((deploymentResult.ExtendedError() == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND)) || (deploymentResult.ExtendedError() == S_OK), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            if (FAILED(deploymentResult.ExtendedError()))
            {
                VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
            }

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageStaged_Blue());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_NotInstalled_Success)
        {
            RemovePackageFamily_Red();
            RemovePackage_Green();
            RemovePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageStaged_Green());
            VERIFY_IS_TRUE(IsPackageStaged_Blue());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_Staged_Success)
        {
            RemovePackageFamily_Red();
            RemovePackage_Green();
            RemovePackage_Blue();
            StagePackage_Red();
            StagePackage_Green();
            StagePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageStaged_Green());
            VERIFY_IS_TRUE(IsPackageStaged_Blue());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_Registered_Success)
        {
            RemovePackageFamily_Red();
            RemovePackage_Green();
            RemovePackage_Blue();
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageStaged_Green());
            VERIFY_IS_TRUE(IsPackageStaged_Blue());
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_OlderStaged_Success)
        {
            RemovePackageFamily_Red();
            RemovePackage_Green();
            RemovePackage_Blue();
            StagePackage_Red();
            StagePackage_Green();
            StagePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem(::TPF::Redder::GetPackageFullName(), ::TPF::Redder::c_packageDirName) };
            packageSet.Items().Append(redder);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Redder());
            VERIFY_IS_TRUE(IsPackageStaged_Green());
            VERIFY_IS_TRUE(IsPackageStaged_Blue());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_NewerStaged_Success)
        {
            RemovePackageFamily_Redder();
            RemovePackage_Green();
            RemovePackage_Blue();
            StagePackage_Redder();
            StagePackage_Green();
            StagePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Redder());
            VERIFY_IS_TRUE(IsPackageStaged_Green());
            VERIFY_IS_TRUE(IsPackageStaged_Blue());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_StagedAndNotInstalled_Success)
        {
            RemovePackageFamily_Red();
            RemovePackage_Green();
            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageStaged_Green());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_StagedAndNotInstalledAndStaged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RemovePackageFamily_Red();
            RemovePackage_Green();
            RemovePackage_Blue();
            StagePackage_Red();
            StagePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageStaged_Green());
            VERIFY_IS_TRUE(IsPackageStaged_Blue());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageAsync_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR package{ L"c:\\does\\not\\exist\\appxmanifest.xml" };

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
        }

        TEST_METHOD(RegisterPackageAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPF::Red::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RegisterPackageAsync_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPF::Red::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RegisterPackageAsync_OlderRegistered_Success)
        {
            AddPackage_Red();
            StagePackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPF::Redder::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(IsPackageRegistered_Redder());

            RemovePackage_Redder();
        }

        TEST_METHOD(RegisterPackageByUriAsync_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR c_packageUriAsString{ L"file://c:/does/not/exist/appxmanifest.xml" };
            winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
        }

        TEST_METHOD(RegisterPackageByUriAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPF::Red::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            winrt::Windows::Foundation::Uri packageUri{ package };

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RegisterPackageByUriAsync_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPF::Red::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            winrt::Windows::Foundation::Uri packageUri{ package };

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RegisterPackageByUriAsync_OlderRegistered_Success)
        {
            AddPackage_Red();
            StagePackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPF::Redder::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            winrt::Windows::Foundation::Uri packageUri{ package };

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(IsPackageRegistered_Redder());

            RemovePackage_Redder();
        }

        TEST_METHOD(RegisterPackageSetAsync_1_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem_ForRegister(::TPF::Red::GetPackageFullName()) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_1_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem_ForRegister(::TPF::Red::GetPackageFullName()) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_1_OlderRegistered_Success)
        {
            AddPackage_Red();
            StagePackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem_ForRegister(::TPF::Redder::GetPackageFullName()) };
            packageSet.Items().Append(redder);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(IsPackageRegistered_Redder());

            RemovePackage_Redder();
        }

        TEST_METHOD(RegisterPackageSetAsync_N_Registered_Success)
        {
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem_ForRegister(::TPF::Red::GetPackageFullName()) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem_ForRegister(::TPF::Green::GetPackageFullName()) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem_ForRegister(::TPF::Blue::GetPackageFullName()) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_N_OlderRegistered_Success)
        {
            AddPackage_Red();
            StagePackage_Redder();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem_ForRegister(::TPF::Redder::GetPackageFullName()) };
            packageSet.Items().Append(redder);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem_ForRegister(::TPF::Green::GetPackageFullName()) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem_ForRegister(::TPF::Blue::GetPackageFullName()) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(IsPackageRegistered_Redder());
            RemovePackage_Redder();
        }

        TEST_METHOD(RegisterPackageSetAsync_N_RegisteredAndStaged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            AddPackage_Red();
            StagePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem_ForRegister(::TPF::Red::GetPackageFullName()) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem_ForRegister(::TPF::Blue::GetPackageFullName()) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        //TODO Remove
        //TODO Reset
        //TODO Repair
        //TODO Provision
        //TODO Deprovision
    };

    class PackageDeploymentManagerTests_Elevated : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_Elevated)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!::WindowsVersion::IsWindows10_20H1OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageDeploymentManager requires >= 20H1 (Vibranium). Skipping tests");
                return true;
            }

            TD::DumpExecutionContext();

            RemovePackage_Blue();
            RemovePackage_Green();
            RemovePackage_Redder();
            RemovePackage_Red();
            AddPackage_Red();
            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            TD::DumpExecutionContext();

            RemovePackage_Blue();
            RemovePackage_Green();
            RemovePackage_Redder();
            RemovePackage_Red();
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(IsPackageSetReady_1_RegisteredPackageStatusBad_No)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_TRUE(IsPackageRegistered_Red());

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));

            ClearPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_1_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_TRUE(IsPackageRegistered_Red());

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_N_RegisteredPackageStatusOkAndBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            AddPackage_Green();
            SetPackageStatusByPackageFamilyName(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentOperation{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(AddPackageAsync_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(AddPackageByUriAsync_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(AddPackageSetAsync_1_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(AddPackageSetAsync_N_RegisteredPackageStatusOkAndBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            AddPackage_Green();
            SetPackageStatusByPackageFamilyName(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.AddPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));
        }

        TEST_METHOD(StagePackageAsync_StagedPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            RemovePackageFamily_Red();
            StagePackage_Red();
            SetPackageStatus(::TPF::Red::GetPackageFullName(), winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(IsPackageRegistered_Red());

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(StagePackageByUriAsync_StagedPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            RemovePackageFamily_Red();
            StagePackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::GetPackageFullName(), winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(StagePackageSetAsync_1_StagedPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            RemovePackageFamily_Red();
            StagePackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::GetPackageFullName(), winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_StagedPackageStatusOkAndBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            RemovePackageFamily_Red();
            RemovePackage_Green();
            StagePackage_Red();
            StagePackage_Green();
            SetPackageStatusByPackageFamilyName(::TPF::Green::GetPackageFullName(), winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageStaged_Green());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));
        }
    };
}
