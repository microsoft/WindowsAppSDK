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

#if !defined(TODO_Register_error_0x80073D2B_ERROR_UNSIGNED_PACKAGE_INVALID_CONTENT_on_20h_vb)
#define RETURN_TRUE_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST() \
    if (!::WindowsVersion::IsWindows11_21H2OrGreater()) \
    { \
        WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageDeploymentManager.Register*() tests require >= 21H2 (SV1). Skipping tests"); \
        return true; \
    }
#define RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST() \
    if (!::WindowsVersion::IsWindows11_21H2OrGreater()) \
    { \
        WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageDeploymentManager.Register*() tests require >= 21H2 (SV1). Skipping tests"); \
        return; \
    }
#endif

namespace Test::PackageManager::Tests
{
    class PackageDeploymentManagerTests_Register : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_Register)
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

            RETURN_TRUE_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();
            RemovePackage_Blue();
            RemovePackage_Green();
            RemovePackage_Redder();
            RemovePackage_Red();
            RemovePackage_White();
            RemovePackage_Blacker();
            RemovePackage_Black();
            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            RemovePackage_Blue();
            RemovePackage_Green();
            RemovePackage_Redder();
            RemovePackage_Red();
            RemovePackage_White();
            RemovePackage_Blacker();
            RemovePackage_Black();
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

        TEST_METHOD(RegisterPackageAsync_Framework_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPF::Red::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"package: %ls", package.c_str()));

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RegisterPackageAsync_Main_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            StagePackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPM::Black::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"package: %ls", package.c_str()));

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Black());
        }

        TEST_METHOD(RegisterPackageAsync_Framework_Registered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPF::Red::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"package: %ls", package.c_str()));

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RegisterPackageAsync_Main_Registered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            AddPackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPM::Black::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"package: %ls", package.c_str()));

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Black());
        }

        TEST_METHOD(RegisterPackageAsync_Framework_OlderRegistered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Redder();
            AddPackage_Red();
            StagePackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPF::Redder::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"package: %ls", package.c_str()));

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(IsPackageRegistered_Redder());

            RemovePackage_Redder();
        }

        TEST_METHOD(RegisterPackageAsync_Main_OlderRegistered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            AddPackage_Black();
            StagePackage_Blacker();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPM::Blacker::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"package: %ls", package.c_str()));

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageAsync(package, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Black());
            VERIFY_IS_TRUE(IsPackageRegistered_Blacker());

            RemovePackage_Blacker();
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

        TEST_METHOD(RegisterPackageByUriAsync_Framework_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPF::Red::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"package: %ls", package.c_str()));
            winrt::Windows::Foundation::Uri packageUri{ package };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"packageUri: %ls", packageUri.ToString().c_str()));

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RegisterPackageByUriAsync_Main_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            StagePackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPM::Black::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"package: %ls", package.c_str()));
            winrt::Windows::Foundation::Uri packageUri{ package };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"packageUri: %ls", packageUri.ToString().c_str()));

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Black());
        }

        TEST_METHOD(RegisterPackageByUriAsync_Framework_Registered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPF::Red::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"package: %ls", package.c_str()));
            winrt::Windows::Foundation::Uri packageUri{ package };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"packageUri: %ls", packageUri.ToString().c_str()));

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(RegisterPackageByUriAsync_Main_Registered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            AddPackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPM::Black::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"package: %ls", package.c_str()));
            winrt::Windows::Foundation::Uri packageUri{ package };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"packageUri: %ls", packageUri.ToString().c_str()));

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(IsPackageRegistered_Black());
        }

        TEST_METHOD(RegisterPackageByUriAsync_Framework_OlderRegistered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Redder();
            AddPackage_Red();
            StagePackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPF::Redder::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"package: %ls", package.c_str()));
            winrt::Windows::Foundation::Uri packageUri{ package };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"packageUri: %ls", packageUri.ToString().c_str()));

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(IsPackageRegistered_Redder());

            RemovePackage_Redder();
        }

        TEST_METHOD(RegisterPackageByUriAsync_Main_OlderRegistered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            AddPackage_Black();
            StagePackage_Blacker();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto appxManifestPath{ TP::GetAppxManifestPackagePath(::TPM::Blacker::GetPackageFullName()) };
            const winrt::hstring package{ appxManifestPath.c_str() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"package: %ls", package.c_str()));
            winrt::Windows::Foundation::Uri packageUri{ package };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"packageUri: %ls", packageUri.ToString().c_str()));

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageByUriAsync(packageUri, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_FALSE(IsPackageRegistered_Black());
            VERIFY_IS_TRUE(IsPackageRegistered_Blacker());

            RemovePackage_Blacker();
        }

        TEST_METHOD(RegisterPackageSetAsync_Framework_1_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

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

        TEST_METHOD(RegisterPackageSetAsync_Main_1_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            StagePackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem_ForRegister(::TPM::Black::GetPackageFullName()) };
            packageSet.Items().Append(black);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_Framework_1_Staged_PackageFamilyName_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem_NoPackageUri(::TPF::Red::GetPackageFullName()) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_Main_1_Staged_PackageFamilyName_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            StagePackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem_NoPackageUri(::TPM::Black::GetPackageFullName()) };
            packageSet.Items().Append(black);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_Framework_1_Registered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

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

        TEST_METHOD(RegisterPackageSetAsync_Main_1_Registered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            AddPackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"BW" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem_ForRegister(::TPM::Black::GetPackageFullName()) };
            packageSet.Items().Append(black);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_Framework_1_Registered_PackageFamilyName_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem_NoPackageUri(::TPF::Red::GetPackageFullName()) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_Main_1_Registered_PackageFamilyName_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            AddPackage_Black();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"BW" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem_NoPackageUri(::TPM::Black::GetPackageFullName()) };
            packageSet.Items().Append(black);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_Framework_1_OlderRegistered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Redder();
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

        TEST_METHOD(RegisterPackageSetAsync_Main_1_OlderRegistered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            AddPackage_Black();
            StagePackage_Blacker();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem_ForRegister(::TPM::Blacker::GetPackageFullName()) };
            packageSet.Items().Append(redder);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            VERIFY_IS_FALSE(IsPackageRegistered_Black());
            VERIFY_IS_TRUE(IsPackageRegistered_Blacker());

            RemovePackage_Blacker();
        }

        TEST_METHOD(RegisterPackageSetAsync_Framework_1_OlderRegistered_PackageFamilyName_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Redder();
            AddPackage_Red();
            StagePackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem_NoPackageUri(::TPF::Redder::GetPackageFullName()) };
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

        TEST_METHOD(RegisterPackageSetAsync_Main_1_OlderRegistered_PackageFamilyName_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            AddPackage_Black();
            StagePackage_Blacker();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem_NoPackageUri(::TPM::Blacker::GetPackageFullName()) };
            packageSet.Items().Append(redder);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            VERIFY_IS_FALSE(IsPackageRegistered_Black());
            VERIFY_IS_TRUE(IsPackageRegistered_Blacker());

            RemovePackage_Blacker();
        }

        TEST_METHOD(RegisterPackageSetAsync_Framework_N_Registered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

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

        TEST_METHOD(RegisterPackageSetAsync_Main_N_Registered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            AddPackage_Black();
            AddPackage_White();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"BW" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem_ForRegister(::TPM::Black::GetPackageFullName()) };
            packageSet.Items().Append(black);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem white{ Make_PackageSetItem_ForRegister(::TPM::White::GetPackageFullName()) };
            packageSet.Items().Append(white);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_Framework_N_Registered_PackageFamilyName_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem_NoPackageUri(::TPF::Red::GetPackageFullName()) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem_NoPackageUri(::TPF::Green::GetPackageFullName()) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem_NoPackageUri(::TPF::Blue::GetPackageFullName()) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_Main_N_Registered_PackageFamilyName_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            AddPackage_Black();
            AddPackage_White();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"BW" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem_NoPackageUri(::TPM::Black::GetPackageFullName()) };
            packageSet.Items().Append(black);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem white{ Make_PackageSetItem_NoPackageUri(::TPM::White::GetPackageFullName()) };
            packageSet.Items().Append(white);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_Framework_N_OlderRegistered_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Redder();
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

        TEST_METHOD(RegisterPackageSetAsync_Main_N_OlderRegistered_Success)
        {
            RemovePackage_Blacker();
            AddPackage_Black();
            StagePackage_Blacker();
            AddPackage_White();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blacker{ Make_PackageSetItem_ForRegister(::TPM::Blacker::GetPackageFullName()) };
            packageSet.Items().Append(blacker);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem white{ Make_PackageSetItem_ForRegister(::TPM::White::GetPackageFullName()) };
            packageSet.Items().Append(white);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            VERIFY_IS_FALSE(IsPackageRegistered_Black());
            VERIFY_IS_TRUE(IsPackageRegistered_Blacker());

            RemovePackage_Blacker();
        }

        TEST_METHOD(RegisterPackageSetAsync_Framework_N_OlderRegistered_PackageFamilyName_Success)
        {
            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Redder();
            AddPackage_Red();
            StagePackage_Redder();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem_NoPackageUri(::TPF::Redder::GetPackageFullName()) };
            packageSet.Items().Append(redder);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem_NoPackageUri(::TPF::Green::GetPackageFullName()) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem_NoPackageUri(::TPF::Blue::GetPackageFullName()) };
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

        TEST_METHOD(RegisterPackageSetAsync_Main_N_OlderRegistered_PackageFamilyName_Success)
        {
            RemovePackage_Blacker();
            AddPackage_Black();
            StagePackage_Blacker();
            AddPackage_White();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blacker{ Make_PackageSetItem_NoPackageUri(::TPM::Blacker::GetPackageFullName()) };
            packageSet.Items().Append(blacker);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem white{ Make_PackageSetItem_NoPackageUri(::TPM::White::GetPackageFullName()) };
            packageSet.Items().Append(white);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            VERIFY_IS_FALSE(IsPackageRegistered_Black());
            VERIFY_IS_TRUE(IsPackageRegistered_Blacker());

            RemovePackage_Blacker();
        }

        TEST_METHOD(RegisterPackageSetAsync_Framework_N_RegisteredAndStaged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

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

        TEST_METHOD(RegisterPackageSetAsync_Main_N_RegisteredAndStaged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            AddPackage_Black();
            StagePackage_White();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"BW" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem_ForRegister(::TPM::Black::GetPackageFullName()) };
            packageSet.Items().Append(black);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem white{ Make_PackageSetItem_ForRegister(::TPM::White::GetPackageFullName()) };
            packageSet.Items().Append(white);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_Framework_N_RegisteredAndStaged_PackageFamilyName_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            AddPackage_Red();
            StagePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem_NoPackageUri(::TPF::Red::GetPackageFullName()) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem_NoPackageUri(::TPF::Blue::GetPackageFullName()) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(RegisterPackageSetAsync_Main_N_RegisteredAndStaged_PackageFamilyName_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RETURN_IF_SKIP_ON_WIN10_DUE_TO_0x80073D2B_IN_TEST();

            RemovePackage_Blacker();
            AddPackage_Black();
            StagePackage_White();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"BW" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem_NoPackageUri(::TPM::Black::GetPackageFullName()) };
            packageSet.Items().Append(black);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem white{ Make_PackageSetItem_NoPackageUri(::TPM::White::GetPackageFullName()) };
            packageSet.Items().Append(white);

            winrt::Microsoft::Windows::Management::Deployment::RegisterPackageOptions options;
            auto deploymentOperation{ packageDeploymentManager.RegisterPackageSetAsync(packageSet, options) };
            auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
            TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }
    };
}
