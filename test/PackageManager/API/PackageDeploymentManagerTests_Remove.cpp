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
    class PackageDeploymentManagerTests_Remove : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_Remove)
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

        TEST_METHOD(RemovePackageAsync_PackageFullName_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFullName{ L"Does.Not.Exist_0.0.0.0_neutral__1234567890abc" };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentResult{ packageDeploymentManager.RemovePackageAsync(packageFullName, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
        }

        TEST_METHOD(RemovePackageAsync_PackageFullName_NotInstalled_Fail)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFullName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageAsync_PackageFullName_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFullName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageAsync_PackageFullName_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFullName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageAsync_PackageFullName_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFullName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageAsync_PackageFamilyName_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFamilyName{ L"Does.Not.Exist_1234567890abc" };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentResult{ packageDeploymentManager.RemovePackageAsync(packageFamilyName, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageAsync_PackageFamilyName_NoSuchPackage_Success)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFamilyName{ L"Does.Not.Exist_1234567890abc" };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentResult{ packageDeploymentManager.RemovePackageAsync(packageFamilyName, options).get() };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageAsync_PackageFamilyName_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFamilyName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageAsync_PackageFamilyName_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFamilyName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageAsync_PackageFamilyName_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFamilyName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageByFullNameAsync_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFullName{ L"Does.Not.Exist_0.0.0.0_neutral__1234567890abc" };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentResult{ packageDeploymentManager.RemovePackageByFullNameAsync(packageFullName, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
        }

        TEST_METHOD(RemovePackageByFullNameAsync_NotInstalled_Fail)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageByFullNameAsync(packageFullName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageByFullNameAsync_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentOperation{ packageDeploymentManager.RemovePackageByFullNameAsync(packageFullName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageByFullNameAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageByFullNameAsync(packageFullName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageByFullNameAsync_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageByFullNameAsync(packageFullName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageByFamilyNameAsync_NoSuchPackage_Success)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFamilyName{ L"Does.Not.Exist_1234567890abc" };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentResult{ packageDeploymentManager.RemovePackageByFamilyNameAsync(packageFamilyName, options).get() };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);
        }

        TEST_METHOD(RemovePackageByFamilyNameAsync_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentOperation{ packageDeploymentManager.RemovePackageByFamilyNameAsync(packageFamilyName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageByFamilyNameAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageByFamilyNameAsync(packageFamilyName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageByFamilyNameAsync_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageByFamilyNameAsync(packageFamilyName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageByUriAsync_NoSuchPackage_Fail)
        {
            if (TPMT::SkipIfFeatureNotSupported_RemovePackageByUri() || TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR c_packageUriAsString{ L"ms-uup://Product/does.not.exist" };
            winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentResult{ packageDeploymentManager.RemovePackageByUriAsync(packageUri, options).get() };
//TODO WTH
WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Status: %d", deploymentResult.Status()));
WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Error: 0x%08X", deploymentResult.Error()));
WEX::Logging::Log::Comment(WEX::Common::String().Format(L"ExtendedError: 0x%08X", deploymentResult.ExtendedError()));
WEX::Logging::Log::Comment(WEX::Common::String().Format(L"ErrorText: %s", deploymentResult.ErrorText().c_str()));
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
        }

        TEST_METHOD(RemovePackageByUriAsync_NotInstalled_Fail)
        {
            if (TPMT::SkipIfFeatureNotSupported_RemovePackageByUri() || TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(RemovePackageByUriAsync_NotInstalled_Success)
        {
            if (TPMT::SkipIfFeatureNotSupported_RemovePackageByUri() || TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(RemovePackageByUriAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            if (TPMT::SkipIfFeatureNotSupported_RemovePackageByUri() || TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(RemovePackageByUriAsync_Registered_Success)
        {
            if (TPMT::SkipIfFeatureNotSupported_RemovePackageByUri() || TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(RemovePackageSetAsync_Uri_1_NoSuchPackage_Fail)
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

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentResult{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
#if defined(TODO_use_Platform_SDK_defining_RemovePackageOptions)
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
#else
            VERIFY_ARE_EQUAL(E_NOTIMPL, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
#endif

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RemovePackageSetAsync_Uri_1_NotInstalled_Fail)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
#if defined(TODO_use_Platform_SDK_defining_RemovePackageOptions)
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
#else
            VERIFY_ARE_EQUAL(E_NOTIMPL, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
#endif

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageSetAsync_Uri_1_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
#if defined(TODO_use_Platform_SDK_defining_RemovePackageOptions)
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);
#else
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(E_NOTIMPL, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
#endif

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RemovePackageSetAsync_Uri_1_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
#if defined(TODO_use_Platform_SDK_defining_RemovePackageOptions)
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);
#else
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(E_NOTIMPL, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
#endif

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RemovePackageSetAsync_Uri_1_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
#if defined(TODO_use_Platform_SDK_defining_RemovePackageOptions)
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
#else
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(E_NOTIMPL, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
#endif
        }

        TEST_METHOD(RemovePackageSetAsync_Uri_N_NotInstalled_Fail)
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

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
#if defined(TODO_use_Platform_SDK_defining_RemovePackageOptions)
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
#else
            VERIFY_ARE_EQUAL(E_NOTIMPL, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
#endif

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageSetAsync_Uri_N_NotInstalled_Success)
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

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
#if defined(TODO_use_Platform_SDK_defining_RemovePackageOptions)
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
#else
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(E_NOTIMPL, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
#endif
        }

        TEST_METHOD(RemovePackageSetAsync_Uri_N_Registered_Success)
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

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
#if defined(TODO_use_Platform_SDK_defining_RemovePackageOptions)
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
#else
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(E_NOTIMPL, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
#endif
        }

        TEST_METHOD(RemovePackageSetAsync_Uri_N_RegisteredAndNotInstalled_Success)
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

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
#if defined(TODO_use_Platform_SDK_defining_RemovePackageOptions)
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);
#else
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(E_NOTIMPL, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
#endif

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RemovePackageSetAsync_Uri_N_RegisteredAndNotInstalledAndStaged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
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

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
#if defined(TODO_use_Platform_SDK_defining_RemovePackageOptions)
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);
#else
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(E_NOTIMPL, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
#endif

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RemovePackageSetAsync_NoUri_1_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"Does.Not.Exist" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
            PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
            packageSetItem.PackageFamilyName(c_packageFamilyName);
            winrt::Windows::Foundation::Uri packageUri{ nullptr };
            packageSetItem.PackageUri(packageUri);
            packageSet.Items().Append(packageSetItem);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentResult{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RemovePackageSetAsync_NoUri_1_NotInstalled_Fail)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            red.PackageUri(nullptr);
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageSetAsync_NoUri_1_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            red.PackageUri(nullptr);
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RemovePackageSetAsync_NoUri_1_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            red.PackageUri(nullptr);
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RemovePackageSetAsync_NoUri_1_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            red.PackageUri(nullptr);
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RemovePackageSetAsync_NoUri_N_NotInstalled_Fail)
        {
            RemovePackage_Red();
            RemovePackage_Green();
            RemovePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            red.PackageUri(nullptr);
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            green.PackageUri(nullptr);
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            blue.PackageUri(nullptr);
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_PACKAGE_NOT_FOUND), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_FALSE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RemovePackageSetAsync_NoUri_N_NotInstalled_Success)
        {
            RemovePackage_Red();
            RemovePackage_Green();
            RemovePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            red.PackageUri(nullptr);
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            green.PackageUri(nullptr);
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            blue.PackageUri(nullptr);
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RemovePackageSetAsync_NoUri_N_Registered_Success)
        {
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            red.PackageUri(nullptr);
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            green.PackageUri(nullptr);
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            blue.PackageUri(nullptr);
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RemovePackageSetAsync_NoUri_N_RegisteredAndNotInstalled_Success)
        {
            AddPackage_Red();
            RemovePackage_Green();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            red.PackageUri(nullptr);
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            green.PackageUri(nullptr);
            packageSet.Items().Append(green);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RemovePackageSetAsync_NoUri_N_RegisteredAndNotInstalledAndStaged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            AddPackage_Red();
            RemovePackage_Green();
            StagePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            red.PackageUri(nullptr);
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            green.PackageUri(nullptr);
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            blue.PackageUri(nullptr);
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            VERIFY_IS_FALSE(options.FailIfNotFound());
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }
    };

    class PackageDeploymentManagerTests_Remove_Elevated : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_Remove_Elevated)
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

        TEST_METHOD(RemovePackageAsync_PackageFullName_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFullName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(RemovePackageAsync_PackageFamilyName_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFamilyName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(RemovePackageByFullNameAsync_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            const winrt::hstring packageFullName{ ::TPF::Red::GetPackageFullName() };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFullName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(RemovePackageByFamilyNameAsync_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            const winrt::hstring packageFamilyName{ ::TPF::Red::c_packageFamilyName };

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageAsync(packageFamilyName, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(RemovePackageByUriAsync_RegisteredPackageStatusBad_Success)
        {
            if (TPMT::SkipIfFeatureNotSupported_RemovePackageByUri() || TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(RemovePackageSetAsync_Uri_1_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
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
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
#if defined(TODO_use_Platform_SDK_defining_RemovePackageOptions)
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);
#else
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(E_NOTIMPL, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
#endif

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(RemovePackageSetAsync_Uri_N_RegisteredPackageStatusOkAndBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
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
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
#if defined(TODO_use_Platform_SDK_defining_RemovePackageOptions)
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);
#else
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(E_NOTIMPL, deploymentResult.Error(), WEX::Common::String().Format(L"0x%X", deploymentResult.Error()));
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
            VERIFY_IS_TRUE(deploymentResult.ErrorText().empty(), WEX::Common::String().Format(L"%s", deploymentResult.ErrorText().c_str()));
#endif
        }

        TEST_METHOD(RemovePackageSetAsync_NoUri_1_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            winrt::Windows::Foundation::Uri packageUri{ nullptr };
            red.PackageUri(packageUri);
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(RemovePackageSetAsync_NoUri_N_RegisteredPackageStatusOkAndBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
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
            winrt::Windows::Foundation::Uri packageUri{ nullptr };
            red.PackageUri(packageUri);
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            green.PackageUri(packageUri);
            packageSet.Items().Append(green);

            winrt::Microsoft::Windows::Management::Deployment::RemovePackageOptions options;
            options.FailIfNotFound(true);
            auto deploymentOperation{ packageDeploymentManager.RemovePackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));
        }
    };
}
