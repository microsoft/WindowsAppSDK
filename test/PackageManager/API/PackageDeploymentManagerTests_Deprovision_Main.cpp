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
    class PackageDeploymentManagerTests_Deprovision_Main : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_Deprovision_Main)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Class")    /****SEEME****/
            TEST_CLASS_PROPERTY(L"RunFixtureAs", L"ElevatedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!::WindowsVersion::IsWindows10_20H1OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageDeploymentManager requires >= 20H1 (Vibranium). Skipping tests");
                DoNotExecuteTestMethod(true);
                return true;
            }

            if (TPMT::PreBootstrap_SkipIfFeatureNotSupported_ProvisionPackage_Framework())
            {
                DoNotExecuteTestMethod(true);
                return true;
            }

            TD::DumpExecutionContext();

            RemovePackage_Black();
            AddPackage_Black();
            ProvisionPackage_Black();
            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            DeprovisionPackage_Black();
            RemovePackage_Black();
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(DeprovisionPackageAsync_Registered_AccessDenied)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            AddPackage_Black();

            VERIFY_IS_TRUE(IsPackageRegistered_Black());

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packageFamilyName{ ::TPM::Black::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(E_ACCESSDENIED, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
        }
    };

    class PackageDeploymentManagerTests_Deprovision_Main_Elevated : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_Deprovision_Main_Elevated)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            TEST_CLASS_PROPERTY(L"RunFixtureAs", L"ElevatedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!::WindowsVersion::IsWindows10_20H1OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageDeploymentManager requires >= 20H1 (Vibranium). Skipping tests");
                DoNotExecuteTestMethod(true);
                return true;
            }

            if (TPMT::PreBootstrap_SkipIfFeatureNotSupported_ProvisionPackage_Framework())
            {
                DoNotExecuteTestMethod(true);
                return true;
            }

            TD::DumpExecutionContext();

            DeprovisionPackage_White();
            DeprovisionPackage_Black();
            RemovePackage_White();
            RemovePackage_Blacker();
            RemovePackage_Black();
            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            TD::DumpExecutionContext();

            DeprovisionPackage_White();
            DeprovisionPackage_Black();
            RemovePackage_White();
            RemovePackage_Blacker();
            RemovePackage_Black();
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(DeprovisionPackageAsync_NoSuchPackage_Fail)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFamilyName{ L"Does.Not.Exist_1234567890abc" };

            auto deploymentResult{ packageDeploymentManager.DeprovisionPackageAsync(packageFamilyName).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
        }

        TEST_METHOD(DeprovisionPackageAsync_Staged_Success)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            DeprovisionPackage_Black();
            StagePackage_Black();

            VERIFY_IS_TRUE(IsPackageStaged_Black());
            VERIFY_IS_FALSE(IsPackageRegistered_Black());
            VERIFY_IS_FALSE(IsPackageProvisioned_Black());

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packageFamilyName{ ::TPM::Black::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageStaged_Black());
            VERIFY_IS_TRUE(IsPackageRegistered_Black());
            VERIFY_IS_TRUE(IsPackageProvisioned_Black());
        }

        TEST_METHOD(DeprovisionPackageAsync_Registered_Success)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            DeprovisionPackage_Black();
            AddPackage_Black();

            VERIFY_IS_TRUE(IsPackageRegistered_Black());
            VERIFY_IS_FALSE(IsPackageProvisioned_Black());

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packageFamilyName{ ::TPM::Black::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Black());
            VERIFY_IS_FALSE(IsPackageProvisioned_Black());
        }

        TEST_METHOD(DeprovisionPackageAsync_StagedProvisioned_Success)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            DeprovisionPackage_Black();
            StagePackage_Black();
            ProvisionPackage_Black();

            VERIFY_IS_TRUE(IsPackageStaged_Black());
            VERIFY_IS_FALSE(IsPackageRegistered_Black());
            VERIFY_IS_TRUE(IsPackageProvisioned_Black());

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packageFamilyName{ ::TPM::Black::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageStaged_Black());
            VERIFY_IS_TRUE(IsPackageRegistered_Black());
            VERIFY_IS_FALSE(IsPackageProvisioned_Black());
        }

        TEST_METHOD(DeprovisionPackageAsync_RegisteredProvisioned_Success)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            AddPackage_Black();
            ProvisionPackage_Black();

            VERIFY_IS_TRUE(IsPackageRegistered_Black());
            VERIFY_IS_TRUE(IsPackageProvisioned_Black());

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packageFamilyName{ ::TPM::Black::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Black());
            VERIFY_IS_FALSE(IsPackageProvisioned_Black());
        }

        TEST_METHOD(DeprovisionPackageAsync_RegisteredPackageStatusBad_Success)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            DeprovisionPackage_Black();
            AddPackage_Black();
            SetPackageStatusByPackageFamilyName(::TPM::Black::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPM::Black::GetPackageFullName()));
            VERIFY_IS_FALSE(IsPackageProvisioned_Black());

            const auto packageFamilyName{ ::TPM::Black::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Black());
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPM::Black::GetPackageFullName()));
            VERIFY_IS_TRUE(IsPackageProvisioned_Black());
        }

        TEST_METHOD(DeprovisionPackageByUriAsync_NoSuchPackage_Fail)
        {
            if (TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(DeprovisionPackageByUriAsync_Staged_Success)
        {
            if (TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(DeprovisionPackageByUriAsync_Registered_Success)
        {
            if (TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(DeprovisionPackageByUriAsync_StagedProvisioned_Success)
        {
            if (TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(DeprovisionPackageByUriAsync_RegisteredProvisioned_Success)
        {
            if (TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(DeprovisionPackageByUriAsync_RegisteredPackageStatusBad_Success)
        {
            if (TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(DeprovisionPackageSetAsync_1_NoSuchPackage_Fail)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"Does.Not.Exist" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
            PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
            packageSetItem.PackageFamilyName(c_packageFamilyName);
            packageSet.Items().Append(packageSetItem);

            auto deploymentResult{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_1_Staged_Success)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            DeprovisionPackage_Black();
            StagePackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem(::TPM::Black::GetPackageFullName(), ::TPM::Black::c_packageDirName) };
            winrt::Windows::Foundation::Uri packageUri{ nullptr };
            black.PackageUri(packageUri);
            packageSet.Items().Append(black);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_1_Registered_Success)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            DeprovisionPackage_Black();
            AddPackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem(::TPM::Black::GetPackageFullName(), ::TPM::Black::c_packageDirName) };
            winrt::Windows::Foundation::Uri packageUri{ nullptr };
            black.PackageUri(packageUri);
            packageSet.Items().Append(black);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_1_StagedProvisioned_Success)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            DeprovisionPackage_Black();
            StagePackage_Black();
            ProvisionPackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem(::TPM::Black::GetPackageFullName(), ::TPM::Black::c_packageDirName) };
            winrt::Windows::Foundation::Uri packageUri{ nullptr };
            black.PackageUri(packageUri);
            packageSet.Items().Append(black);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_1_RegisteredProvisioned_Success)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            DeprovisionPackage_Black();
            AddPackage_Black();
            ProvisionPackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem(::TPM::Black::GetPackageFullName(), ::TPM::Black::c_packageDirName) };
            winrt::Windows::Foundation::Uri packageUri{ nullptr };
            black.PackageUri(packageUri);
            packageSet.Items().Append(black);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_N_Staged_Success)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            DeprovisionPackage_Black();
            DeprovisionPackage_White();
            StagePackage_Black();
            StagePackage_White();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem(::TPM::Black::GetPackageFullName(), ::TPM::Black::c_packageDirName) };
            packageSet.Items().Append(black);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem white{ Make_PackageSetItem(::TPM::White::GetPackageFullName(), ::TPM::White::c_packageDirName) };
            packageSet.Items().Append(white);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_N_Registered_Success)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            DeprovisionPackage_Black();
            DeprovisionPackage_White();
            AddPackage_Black();
            AddPackage_White();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem(::TPM::Black::GetPackageFullName(), ::TPM::Black::c_packageDirName) };
            packageSet.Items().Append(black);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem white{ Make_PackageSetItem(::TPM::White::GetPackageFullName(), ::TPM::White::c_packageDirName) };
            packageSet.Items().Append(white);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_N_StagedProvisioned_Success)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            DeprovisionPackage_Black();
            DeprovisionPackage_White();
            StagePackage_Black();
            StagePackage_White();
            ProvisionPackage_Black();
            ProvisionPackage_White();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem(::TPM::Black::GetPackageFullName(), ::TPM::Black::c_packageDirName) };
            packageSet.Items().Append(black);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem white{ Make_PackageSetItem(::TPM::White::GetPackageFullName(), ::TPM::White::c_packageDirName) };
            packageSet.Items().Append(white);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_N_RegisteredProvisioned_Success)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            DeprovisionPackage_Black();
            DeprovisionPackage_White();
            AddPackage_Black();
            AddPackage_White();
            ProvisionPackage_Black();
            ProvisionPackage_White();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem(::TPM::Black::GetPackageFullName(), ::TPM::Black::c_packageDirName) };
            packageSet.Items().Append(black);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem white{ Make_PackageSetItem(::TPM::White::GetPackageFullName(), ::TPM::White::c_packageDirName) };
            packageSet.Items().Append(white);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_N_RegisteredAndNoSuchPackage_Fail)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            DeprovisionPackage_White();
            DeprovisionPackage_Black();
            AddPackage_Black();
            RemovePackage_White();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem(::TPM::Black::GetPackageFullName(), ::TPM::Black::c_packageDirName) };
            packageSet.Items().Append(black);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem white{ Make_PackageSetItem(::TPM::White::GetPackageFullName(), ::TPM::White::c_packageDirName) };
            packageSet.Items().Append(white);

            VERIFY_IS_TRUE(IsPackageRegistered_Black());
            VERIFY_IS_FALSE(IsPackageRegistered_White());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Black());
            VERIFY_IS_FALSE(IsPackageRegistered_White());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_N_RegisteredAndNoSuchPackageAndStaged_Fail)
        {
            if (DoNotExecuteTestMethod())
            {
                return;
            }

            DeprovisionPackage_White();
            DeprovisionPackage_Black();
            AddPackage_Black();
            RemovePackage_White();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem(::TPM::Black::GetPackageFullName(), ::TPM::Black::c_packageDirName) };
            packageSet.Items().Append(black);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem white{ Make_PackageSetItem(::TPM::White::GetPackageFullName(), ::TPM::White::c_packageDirName) };
            packageSet.Items().Append(white);

            VERIFY_IS_TRUE(IsPackageRegistered_Black());
            VERIFY_IS_FALSE(IsPackageRegistered_White());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Black());
            VERIFY_IS_FALSE(IsPackageRegistered_White());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }
    };
}
