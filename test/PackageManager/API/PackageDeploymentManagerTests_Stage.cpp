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
    class PackageDeploymentManagerTests_Stage : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_Stage)
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

        TEST_METHOD(StagePackageAsync_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR package{ L"c:\\does\\not\\exist.msix" };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RemovePackageFamily_Red();
            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageByUriAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RemovePackageFamily_Red();
            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_1_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_FAILED), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageStaged_Green());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_StagedAndNotInstalledAndStaged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageStaged_Green());
            VERIFY_IS_TRUE(IsPackageStaged_Blue());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }
    };

    class PackageDeploymentManagerTests_Stage_Elevated : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_Stage_Elevated)
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

        TEST_METHOD(StagePackageAsync_StagedPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(StagePackageByUriAsync_StagedPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(StagePackageSetAsync_1_StagedPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_StagedPackageStatusOkAndBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
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
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_TRUE(IsPackageStaged_Green());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));
        }
    };
}
