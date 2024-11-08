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
    class PackageDeploymentManagerTests_Deprovision_Framework : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_Deprovision_Framework)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Class")    /****SEEME****/
            TEST_CLASS_PROPERTY(L"RunFixtureAs", L"ElevatedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!::WindowsVersion::IsWindows10_20H1OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageDeploymentManager requires >= 20H1 (Vibranium). Skipping tests");
                return true;
            }

            if (TPMT::PreBootstrap_SkipIfFeatureNotSupported_ProvisionPackage_Framework())
            {
                return true;
            }

            TD::DumpExecutionContext();

            RemovePackage_Red();
            AddPackage_Red();
            ProvisionPackage_Red();
            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            DeprovisionPackage_Red();
            RemovePackage_Red();
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(DeprovisionPackageAsync_Registered_AccessDenied)
        {
            AddPackage_Red();

            VERIFY_IS_TRUE(IsPackageRegistered_Red());

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(E_ACCESSDENIED, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
        }

    };

    class PackageDeploymentManagerTests_Deprovision_Framework_Elevated : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_Deprovision_Framework_Elevated)
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
                return true;
            }

            if (TPMT::PreBootstrap_SkipIfFeatureNotSupported_ProvisionPackage_Framework())
            {
                return true;
            }

            TD::DumpExecutionContext();

            DeprovisionPackage_Blue();
            DeprovisionPackage_Green();
            DeprovisionPackage_Red();
            RemovePackage_Blue();
            RemovePackage_Green();
            RemovePackage_Redder();
            RemovePackage_Red();
            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            TD::DumpExecutionContext();

            DeprovisionPackage_Blue();
            DeprovisionPackage_Green();
            DeprovisionPackage_Red();
            RemovePackage_Blue();
            RemovePackage_Green();
            RemovePackage_Redder();
            RemovePackage_Red();
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(DeprovisionPackageAsync_NoSuchPackage_Fail)
        {
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
            DeprovisionPackage_Red();
            StagePackage_Red();

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(IsPackageProvisioned_Red());

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(IsPackageProvisioned_Red());
        }

        TEST_METHOD(DeprovisionPackageAsync_Registered_Success)
        {
            DeprovisionPackage_Red();
            AddPackage_Red();

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(IsPackageProvisioned_Red());

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(IsPackageProvisioned_Red());
        }

        TEST_METHOD(DeprovisionPackageAsync_StagedProvisioned_Success)
        {
            DeprovisionPackage_Red();
            StagePackage_Red();
            ProvisionPackage_Red();

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(IsPackageProvisioned_Red());

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(IsPackageProvisioned_Red());
        }

        TEST_METHOD(DeprovisionPackageAsync_RegisteredProvisioned_Success)
        {
            AddPackage_Red();
            ProvisionPackage_Red();

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(IsPackageProvisioned_Red());

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(IsPackageProvisioned_Red());
        }

        TEST_METHOD(DeprovisionPackageAsync_RegisteredPackageStatusBad_Success)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            DeprovisionPackage_Red();
            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
            VERIFY_IS_FALSE(IsPackageProvisioned_Red());

            const auto packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
            VERIFY_IS_TRUE(IsPackageProvisioned_Red());
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
            DeprovisionPackage_Red();
            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            winrt::Windows::Foundation::Uri packageUri{ nullptr };
            red.PackageUri(packageUri);
            packageSet.Items().Append(red);

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
            DeprovisionPackage_Red();
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            winrt::Windows::Foundation::Uri packageUri{ nullptr };
            red.PackageUri(packageUri);
            packageSet.Items().Append(red);

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
            DeprovisionPackage_Red();
            StagePackage_Red();
            ProvisionPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            winrt::Windows::Foundation::Uri packageUri{ nullptr };
            red.PackageUri(packageUri);
            packageSet.Items().Append(red);

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
            DeprovisionPackage_Red();
            AddPackage_Red();
            ProvisionPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            winrt::Windows::Foundation::Uri packageUri{ nullptr };
            red.PackageUri(packageUri);
            packageSet.Items().Append(red);

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
            DeprovisionPackage_Red();
            DeprovisionPackage_Green();
            DeprovisionPackage_Blue();
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
            DeprovisionPackage_Red();
            DeprovisionPackage_Green();
            DeprovisionPackage_Blue();
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
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_N_StagedProvisioned_Success)
        {
            DeprovisionPackage_Red();
            DeprovisionPackage_Green();
            DeprovisionPackage_Blue();
            StagePackage_Red();
            StagePackage_Green();
            StagePackage_Blue();
            ProvisionPackage_Red();
            ProvisionPackage_Green();
            ProvisionPackage_Blue();

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
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_N_RegisteredProvisioned_Success)
        {
            DeprovisionPackage_Red();
            DeprovisionPackage_Green();
            DeprovisionPackage_Blue();
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();
            ProvisionPackage_Red();
            ProvisionPackage_Green();
            ProvisionPackage_Blue();

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
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_N_RegisteredAndNoSuchPackage_Fail)
        {
            DeprovisionPackage_Green();
            DeprovisionPackage_Red();
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

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(IsPackageRegistered_Green());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(IsPackageRegistered_Green());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }

        TEST_METHOD(DeprovisionPackageSetAsync_N_RegisteredAndNoSuchPackageAndStaged_Fail)
        {
            DeprovisionPackage_Blue();
            DeprovisionPackage_Green();
            DeprovisionPackage_Red();
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

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(IsPackageRegistered_Green());
            VERIFY_IS_FALSE(IsPackageRegistered_Blue());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));

            auto deploymentOperation{ packageDeploymentManager.DeprovisionPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(IsPackageRegistered_Green());
            VERIFY_IS_FALSE(IsPackageRegistered_Blue());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetProvisioned(packageSet));
        }
    };
}
