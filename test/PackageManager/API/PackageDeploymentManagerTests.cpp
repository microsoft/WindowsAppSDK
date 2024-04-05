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

        TEST_METHOD(IsPackageDeploymentFeatureSupported_InvalidParameter)
        {
            const auto feature{ static_cast<winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature>(0) };
            VERIFY_IS_FALSE(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature));
        }
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

        TEST_METHOD(RemovePackageAsync_PackageFullName_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFullName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(RemovePackageAsync_PackageFamilyName_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFamilyName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(RemovePackageByFullNameAsync_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFullName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(RemovePackageByFamilyNameAsync_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFamilyName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(RemovePackageByUriAsync_RegisteredPackageStatusBad_Success)
        {
            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(RemovePackageSetAsync_1_RegisteredPackageStatusBad_Success)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::RemovePackageSetAsync };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"RemovePackageSetAsync not supported on this platform. Skipping test");
                return;
            }

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

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(RemovePackageSetAsync_N_RegisteredPackageStatusOkAndBad_Success)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::RemovePackageSetAsync };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"RemovePackageSetAsync not supported on this platform. Skipping test");
                return;
            }

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

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));
        }

        TEST_METHOD(ResetPackageAsync_PackageFullName_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackageSetAsync };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageAsync not supported on this platform. Skipping test");
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            auto deploymentOperation{ packageDeploymentManager.ResetPackageAsync(packageFullName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(ResetPackageAsync_PackageFamilyName_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackageSetAsync };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageAsync not supported on this platform. Skipping test");
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.ResetPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(ResetPackageByUriAsync_RegisteredPackageStatusBad_Success)
        {
            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(ResetPackageSetAsync_1_RegisteredPackageStatusBad_Success)
        {
            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(ResetPackageSetAsync_N_RegisteredPackageStatusOkAndBad_Success)
        {
            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }
    };
}
