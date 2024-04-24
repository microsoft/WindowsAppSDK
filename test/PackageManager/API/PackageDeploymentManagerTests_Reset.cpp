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
    class PackageDeploymentManagerTests_Reset : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_Reset)
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

        TEST_METHOD(ResetPackageAsync_PackageFullName_NoSuchPackage_Fail)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageAsync not supported on this platform. Skipping test");
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFullName{ L"Does.Not.Exist_0.0.0.0_neutral__1234567890abc" };

            auto deploymentResult{ packageDeploymentManager.ResetPackageAsync(packageFullName).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
        }

        TEST_METHOD(ResetPackageAsync_PackageFullName_NotInstalled_Fail)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageAsync not supported on this platform. Skipping test");
                return;
            }

            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            auto deploymentOperation{ packageDeploymentManager.ResetPackageAsync(packageFullName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(ResetPackageAsync_PackageFullName_NotInstalled_Success)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageAsync not supported on this platform. Skipping test");
                return;
            }

            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            auto deploymentOperation{ packageDeploymentManager.ResetPackageAsync(packageFullName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(ResetPackageAsync_PackageFullName_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageAsync not supported on this platform. Skipping test");
                return;
            }

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            auto deploymentOperation{ packageDeploymentManager.ResetPackageAsync(packageFullName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(ResetPackageAsync_PackageFullName_Registered_Success)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageAsync not supported on this platform. Skipping test");
                return;
            }

            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            auto deploymentOperation{ packageDeploymentManager.ResetPackageAsync(packageFullName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(ResetPackageAsync_PackageFamilyName_NoSuchPackage_Success)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageAsync not supported on this platform. Skipping test");
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFamilyName{ L"Does.Not.Exist_1234567890abc" };

            auto deploymentResult{ packageDeploymentManager.ResetPackageAsync(packageFamilyName).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(ResetPackageAsync_PackageFamilyName_NotInstalled_Success)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageAsync not supported on this platform. Skipping test");
                return;
            }

            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.ResetPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(ResetPackageAsync_PackageFamilyName_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageAsync not supported on this platform. Skipping test");
                return;
            }

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.ResetPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(ResetPackageAsync_PackageFamilyName_Registered_Success)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageAsync not supported on this platform. Skipping test");
                return;
            }

            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            auto deploymentOperation{ packageDeploymentManager.ResetPackageAsync(packageFamilyName) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(ResetPackageByUriAsync_NoSuchPackage_Fail)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageByUriAsync not supported on this platform. Skipping test");
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR c_packageUriAsString{ L"ms-uup://Product/does.not.exist" };
            winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };

            auto deploymentResult{ packageDeploymentManager.ResetPackageByUriAsync(packageUri).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
        }

        TEST_METHOD(ResetPackageByUriAsync_NotInstalled_Fail)
        {
            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(ResetPackageByUriAsync_NotInstalled_Success)
        {
            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(ResetPackageByUriAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(ResetPackageByUriAsync_Registered_Success)
        {
            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(ResetPackageSetAsync_1_NoSuchPackage_Fail)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageSetAsync not supported on this platform. Skipping test");
                return;
            }

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

            auto deploymentResult{ packageDeploymentManager.ResetPackageSetAsync(packageSet).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(ResetPackageSetAsync_1_NotInstalled_Fail)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageSetAsync not supported on this platform. Skipping test");
                return;
            }

            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            auto deploymentOperation{ packageDeploymentManager.ResetPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(ResetPackageSetAsync_1_NotInstalled_Success)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageSetAsync not supported on this platform. Skipping test");
                return;
            }

            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            auto deploymentOperation{ packageDeploymentManager.ResetPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(ResetPackageSetAsync_1_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageSetAsync not supported on this platform. Skipping test");
                return;
            }

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            auto deploymentOperation{ packageDeploymentManager.ResetPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(ResetPackageSetAsync_1_Registered_Success)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageSetAsync not supported on this platform. Skipping test");
                return;
            }

            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            auto deploymentOperation{ packageDeploymentManager.ResetPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(ResetPackageSetAsync_N_NotInstalled_Fail)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageSetAsync not supported on this platform. Skipping test");
                return;
            }

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

            auto deploymentOperation{ packageDeploymentManager.ResetPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(ResetPackageSetAsync_N_NotInstalled_Success)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageSetAsync not supported on this platform. Skipping test");
                return;
            }

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

            auto deploymentOperation{ packageDeploymentManager.ResetPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(ResetPackageSetAsync_N_Registered_Success)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageSetAsync not supported on this platform. Skipping test");
                return;
            }

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

            auto deploymentOperation{ packageDeploymentManager.ResetPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(ResetPackageSetAsync_N_RegisteredAndNotInstalled_Success)
        {
            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageSetAsync not supported on this platform. Skipping test");
                return;
            }

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

            auto deploymentOperation{ packageDeploymentManager.ResetPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(ResetPackageSetAsync_N_RegisteredAndNotInstalledAndStaged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
            if (!winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::IsPackageDeploymentFeatureSupported(feature))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ResetPackageSetAsync not supported on this platform. Skipping test");
                return;
            }

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

            auto deploymentOperation{ packageDeploymentManager.ResetPackageSetAsync(packageSet) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }
    };

    class PackageDeploymentManagerTests_Reset_Elevated : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_Reset_Elevated)
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

        TEST_METHOD(ResetPackageAsync_PackageFullName_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
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

            const auto feature{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentFeature::ResetPackage };
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
