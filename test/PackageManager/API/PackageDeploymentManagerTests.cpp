// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TPF = ::Test::Packages::Framework;
namespace TPMT = ::Test::PackageManager::Tests;

namespace Test::PackageManager::Tests
{
    class PackageDeploymentManagerTests
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

        winrt::Windows::ApplicationModel::PackageStatus GetPackageStatus(PCWSTR packageFamilyName)
        {
            return TPMT::GetPackageStatus(m_packageManager, packageFamilyName);
        }

        void SetPackageStatus(PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            TPMT::SetPackageStatus(m_packageManager, packageFamilyName, status);
        }

        void ClearPackageStatus(PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            TPMT::ClearPackageStatus(m_packageManager, packageFamilyName, status);
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

        TEST_METHOD(IsPackageSetReady_1_RegisteredPackageStatusBad_No)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatus(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));

            ClearPackageStatus(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
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
            SetPackageStatus(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
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

            ClearPackageStatus(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
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
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_1_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_1_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatus(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(EnsurePackageSetReadyAsync_N_NotInstalled_Success)
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

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            SetPackageStatus(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);

            winrt::Microsoft::Windows::Management::Deployment::EnsureReadyOptions options;
            auto deploymentResult{ packageDeploymentManager.EnsurePackageSetReadyAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(AddPackageAsync_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR package{ L"c:\\does\\not\\exist.msix" };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
        }

        TEST_METHOD(AddPackageAsync_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.AddPackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(AddPackageAsync_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(AddPackageAsync_OlderRegistered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.AddPackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageRegistered_Redder());

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageAsync_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatus(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(AddPackageByUriAsync_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR c_packageUriAsString{ L"file://c:/does/not/exist.msix" };
            winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
        }

        TEST_METHOD(AddPackageByUriAsync_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(AddPackageByUriAsync_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
        }

        TEST_METHOD(AddPackageByUriAsync_OlderRegistered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageByUriAsync_NewerRegistered_Success)
        {
            AddPackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageRegistered_Redder());

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageByUriAsync_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatus(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageRegistered_Red());
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
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
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageSetAsync_1_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatus(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
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
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

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
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(AddPackageSetAsync_N_RegisteredPackageStatusOkAndBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            AddPackage_Green();
            SetPackageStatus(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);

            winrt::Microsoft::Windows::Management::Deployment::AddPackageOptions options;
            auto deploymentResult{ packageDeploymentManager.AddPackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));
        }

        TEST_METHOD(StagePackageAsync_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR package{ L"c:\\does\\not\\exist.msix" };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
        }

        TEST_METHOD(StagePackageAsync_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageAsync_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageAsync_OlderStaged_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());

            RemovePackage_Redder();
        }

        TEST_METHOD(StagePackageAsync_NewerStaged_Success)
        {
            AddPackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageStaged_Redder());

            RemovePackage_Redder();
        }

        TEST_METHOD(StagePackageAsync_StagedPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatus(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            const auto packagePath{ TP::GetMsixPackagePath(::TPF::Red::c_packageDirName) };
            const winrt::hstring package{ packagePath.c_str() };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageAsync(package, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(StagePackageByUriAsync_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR c_packageUriAsString{ L"file://c:/does/not/exist.msix" };
            winrt::Windows::Foundation::Uri packageUri{ c_packageUriAsString };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));
        }

        TEST_METHOD(StagePackageByUriAsync_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageByUriAsync_Staged_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            StagePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageByUriAsync_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
        }

        TEST_METHOD(StagePackageByUriAsync_OlderStaged_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());

            RemovePackage_Redder();
        }

        TEST_METHOD(StagePackageByUriAsync_NewerStaged_Success)
        {
            AddPackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageStaged_Redder());

            RemovePackage_Redder();
        }

        TEST_METHOD(StagePackageByUriAsync_StagedPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatus(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            winrt::Windows::Foundation::Uri packageUri{ TP::GetMsixPackageUri(::TPF::Red::c_packageDirName) };

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageByUriAsync(packageUri, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageStaged_Red());
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
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
            VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED), deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_1_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(IsPackageSetStaged(packageSet));
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_1_Staged_Success)
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

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_1_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_1_OlderStaged_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem(::TPF::Redder::GetPackageFullName(), ::TPF::Redder::c_packageDirName) };
            packageSet.Items().Append(redder);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(StagePackageSetAsync_1_NewerStaged_Success)
        {
            AddPackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(StagePackageSetAsync_1_StagedPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            SetPackageStatus(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Red::GetPackageFullName()));
        }

        TEST_METHOD(StagePackageSetAsync_N_NotInstalled_Success)
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

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_Staged_Success)
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

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_NewerStaged_Success)
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

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(StagePackageSetAsync_N_OlderStaged_Success)
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

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(StagePackageSetAsync_N_StagedAndNotInstalled_Success)
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

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_StagedAndNotInstalledAndStaged_Success)
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
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(blue);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
        }

        TEST_METHOD(StagePackageSetAsync_N_StagedPackageStatusOkAndBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            AddPackage_Green();
            SetPackageStatus(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);

            winrt::Microsoft::Windows::Management::Deployment::StagePackageOptions options;
            auto deploymentResult{ packageDeploymentManager.StagePackageSetAsync(packageSet, options).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError(), WEX::Common::String().Format(L"0x%X", deploymentResult.ExtendedError()));

            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageReady(::TPF::Green::GetPackageFullName()));
        }

    private:
        winrt::Windows::Management::Deployment::PackageManager m_packageManager;
    };
}
