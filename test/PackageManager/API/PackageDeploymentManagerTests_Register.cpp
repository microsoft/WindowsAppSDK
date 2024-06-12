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
    class PackageDeploymentManagerTests_Register : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_Register)
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

        TEST_METHOD(RegisterPackageAsync_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR package{ L"c:\\does\\not\\exist\\appxmanifest.xml" };

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }
    };
}
