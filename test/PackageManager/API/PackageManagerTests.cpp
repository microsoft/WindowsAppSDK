// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TPF = ::Test::Packages::Framework;

namespace Test::PackageManager::Tests
{
    class PackageManagerTests
    {
    public:
        BEGIN_TEST_CLASS(PackageManagerTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            RemovePackage_Blue();
            RemovePackage_Green();
            RemovePackage_Red();
            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            RemovePackage_Blue();
            RemovePackage_Green();
            RemovePackage_Red();
            ::TB::Cleanup();
            return true;
        }

        static void AddPackage_Red()
        {
            ::TP::AddPackageIfNecessary(Test::Packages::Framework::Red::c_packageDirName, ::TPF::Red::GetPackageFullName());
        }
        static void RemovePackage_Red()
        {
            // Best-effort removal. PackageManager.RemovePackage errors if the package
            // is not registered, but if it's not registered we're good. "'Tis the destination
            // that matters, not the journey" so regardless how much or little work
            // we need do, we're happy as long as the package isn't registered when we're done
            //
            // Thus, do a *IfNecessary removal
            ::TP::RemovePackageIfNecessary(::TPF::Red::GetPackageFullName());
        }

        static void AddPackage_Green()
        {
            ::TP::AddPackageIfNecessary(Test::Packages::Framework::Green::c_packageDirName, ::TPF::Green::GetPackageFullName());
        }
        static void RemovePackage_Green()
        {
            // Best-effort removal. PackageManager.RemovePackage errors if the package
            // is not registered, but if it's not registered we're good. "'Tis the destination
            // that matters, not the journey" so regardless how much or little work
            // we need do, we're happy as long as the package isn't registered when we're done
            //
            // Thus, do a *IfNecessary removal
            ::TP::RemovePackageIfNecessary(::TPF::Green::GetPackageFullName());
        }

        static void AddPackage_Blue()
        {
            ::TP::AddPackageIfNecessary(Test::Packages::Framework::Blue::c_packageDirName, ::TPF::Blue::GetPackageFullName());
        }
        static void RemovePackage_Blue()
        {
            // Best-effort removal. PackageManager.RemovePackage errors if the package
            // is not registered, but if it's not registered we're good. "'Tis the destination
            // that matters, not the journey" so regardless how much or little work
            // we need do, we're happy as long as the package isn't registered when we're done
            //
            // Thus, do a *IfNecessary removal
            ::TP::RemovePackageIfNecessary(::TPF::Blue::GetPackageFullName());
        }

        void SetPackageStatus(PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            const auto packageTypes{ winrt::Windows::Management::Deployment::PackageTypes::Framework };
            auto packages{ m_packageManager.FindPackagesForUserWithPackageTypes(winrt::hstring(), packageFamilyName, packageTypes) };
            for (const winrt::Windows::ApplicationModel::Package& package : packages)
            {
                m_packageManager.SetPackageStatus(package.Id().FullName(), status);
            }
        }

        void ClearPackageStatus(PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            const auto packageTypes{ winrt::Windows::Management::Deployment::PackageTypes::Framework };
            auto packages{ m_packageManager.FindPackagesForUserWithPackageTypes(winrt::hstring(), packageFamilyName, packageTypes) };
            for (const winrt::Windows::ApplicationModel::Package& package : packages)
            {
                m_packageManager.ClearPackageStatus(package.Id().FullName(), status);
            }
        }

        TEST_METHOD(IsReady_InvalidParameter)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                packageDeploymentManager.IsReady(packageSet);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);

                packageDeploymentManager.IsReady(packageSet);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                packageSet.PackageSetItems().Append(packageSetItem);

                packageDeploymentManager.IsReady(packageSet);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageFamilyName{ L"Not a valid Package Family Name" };
                packageSetItem.PackageFamilyName(c_packageFamilyName);
                packageSet.PackageSetItems().Append(packageSetItem);

                packageDeploymentManager.IsReady(packageSet);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
                packageSetItem.PackageFamilyName(c_packageFamilyName);
                packageSet.PackageSetItems().Append(packageSetItem);

                packageDeploymentManager.IsReady(packageSet);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageUriAsString{ L"https://doesnotexist.com/assemble.msix" };
                winrt::Windows::Foundation::Uri c_packageUri{ c_packageUriAsString };
                packageSetItem.PackageUri(c_packageUri);
                packageSet.PackageSetItems().Append(packageSetItem);

                packageDeploymentManager.IsReady(packageSet);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }
        }

        TEST_METHOD(IsReady_1_NoSuchPackage_No)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"Does.Not.Exist" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
            PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
            packageSetItem.PackageFamilyName(c_packageFamilyName);
            PCWSTR c_packageUriAsString{ L"file://c:/does/not/exist.msix" };
            winrt::Windows::Foundation::Uri c_packageUri{ c_packageUriAsString };
            packageSetItem.PackageUri(c_packageUri);
            packageSet.PackageSetItems().Append(packageSetItem);

            try
            {
                VERIFY_IS_FALSE(packageDeploymentManager.IsReady(packageSet));
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }
        }

        TEST_METHOD(IsReady_1_NotInstalled_No)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);

            VERIFY_IS_FALSE(packageDeploymentManager.IsReady(packageSet));
        }

        TEST_METHOD(IsReady_1_Registered_Yes)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);

            VERIFY_IS_TRUE(packageDeploymentManager.IsReady(packageSet));
        }

        TEST_METHOD(IsReady_1_RegisteredPackageStatusBad_No)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            AddPackage_Red();
            SetPackageStatus(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);

            VERIFY_IS_FALSE(packageDeploymentManager.IsReady(packageSet));

            ClearPackageStatus(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
        }

        TEST_METHOD(IsReady_N_NotInstalled_No)
        {
            RemovePackage_Red();
            RemovePackage_Green();
            RemovePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green;
            green.PackageFamilyName(::TPF::Green::c_packageFamilyName);
            green.PackageUri(::TP::GetMsixPackageUri(::TPF::Green::c_packageDirName));
            packageSet.PackageSetItems().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue;
            blue.PackageFamilyName(::TPF::Blue::c_packageFamilyName);
            blue.PackageUri(::TP::GetMsixPackageUri(::TPF::Blue::c_packageDirName));
            packageSet.PackageSetItems().Append(blue);

            VERIFY_IS_FALSE(packageDeploymentManager.IsReady(packageSet));
        }

        TEST_METHOD(IsReady_N_Registered_Yes)
        {
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green;
            green.PackageFamilyName(::TPF::Green::c_packageFamilyName);
            green.PackageUri(::TP::GetMsixPackageUri(::TPF::Green::c_packageDirName));
            packageSet.PackageSetItems().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue;
            blue.PackageFamilyName(::TPF::Blue::c_packageFamilyName);
            blue.PackageUri(::TP::GetMsixPackageUri(::TPF::Blue::c_packageDirName));
            packageSet.PackageSetItems().Append(blue);

            VERIFY_IS_TRUE(packageDeploymentManager.IsReady(packageSet));
        }

        TEST_METHOD(IsReady_N_RegisteredAndNotInstalled_No)
        {
            AddPackage_Red();
            RemovePackage_Green();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green;
            green.PackageFamilyName(::TPF::Green::c_packageFamilyName);
            green.PackageUri(::TP::GetMsixPackageUri(::TPF::Green::c_packageDirName));
            packageSet.PackageSetItems().Append(green);

            VERIFY_IS_FALSE(packageDeploymentManager.IsReady(packageSet));
        }

        TEST_METHOD(IsReady_N_No_NotAllPackageStatusOK)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            AddPackage_Red();
            AddPackage_Green();
            SetPackageStatus(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green;
            green.PackageFamilyName(::TPF::Green::c_packageFamilyName);
            green.PackageUri(::TP::GetMsixPackageUri(::TPF::Green::c_packageDirName));
            packageSet.PackageSetItems().Append(green);

            VERIFY_IS_FALSE(packageDeploymentManager.IsReady(packageSet));

            ClearPackageStatus(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
        }

        TEST_METHOD(EnsureIsReadyAsync_InvalidParameter)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);

                auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                packageSet.PackageSetItems().Append(packageSetItem);

                auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageFamilyName{ L"Not a valid Package Family Name" };
                packageSetItem.PackageFamilyName(c_packageFamilyName);
                packageSet.PackageSetItems().Append(packageSetItem);

                auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
                packageSetItem.PackageFamilyName(c_packageFamilyName);
                packageSet.PackageSetItems().Append(packageSetItem);

                auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                PCWSTR c_packageSetId{ L"Does.Not.Exist" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageUriAsString{ L"file://c:/assemble.msix" };
                winrt::Windows::Foundation::Uri c_packageUri{ c_packageUriAsString };
                packageSetItem.PackageUri(c_packageUri);
                packageSet.PackageSetItems().Append(packageSetItem);

                auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code());
            }
        }

        TEST_METHOD(EnsureIsReadyAsync_1_NoSuchPackage_Fail)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"Does.Not.Exist" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
            PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
            packageSetItem.PackageFamilyName(c_packageFamilyName);
            PCWSTR c_packageUriAsString{ L"file://c:/does/not/exist.msix" };
            winrt::Windows::Foundation::Uri c_packageUri{ c_packageUriAsString };
            packageSetItem.PackageUri(c_packageUri);
            packageSet.PackageSetItems().Append(packageSetItem);

            auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedFailure, deploymentResult.Status());
            VERIFY_ARE_EQUAL(E_FAIL, deploymentResult.ExtendedError());
        }

        TEST_METHOD(EnsureIsReadyAsync_1_NotInstalled_Success)
        {
            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);

            auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError());
        }

        TEST_METHOD(EnsureIsReadyAsync_1_Registered_Success)
        {
            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);

            auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError());
        }

        TEST_METHOD(EnsureIsReadyAsync_1_RegisteredPackageStatusBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            AddPackage_Red();
            SetPackageStatus(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);

            auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError());

            ClearPackageStatus(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
        }

        TEST_METHOD(EnsureIsReadyAsync_N_NotInstalled_Success)
        {
            RemovePackage_Red();
            RemovePackage_Green();
            RemovePackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green;
            green.PackageFamilyName(::TPF::Green::c_packageFamilyName);
            green.PackageUri(::TP::GetMsixPackageUri(::TPF::Green::c_packageDirName));
            packageSet.PackageSetItems().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue;
            blue.PackageFamilyName(::TPF::Blue::c_packageFamilyName);
            blue.PackageUri(::TP::GetMsixPackageUri(::TPF::Blue::c_packageDirName));
            packageSet.PackageSetItems().Append(blue);

            auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError());
        }

        TEST_METHOD(EnsureIsReadyAsync_N_Registered_Success)
        {
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green;
            green.PackageFamilyName(::TPF::Green::c_packageFamilyName);
            green.PackageUri(::TP::GetMsixPackageUri(::TPF::Green::c_packageDirName));
            packageSet.PackageSetItems().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue;
            blue.PackageFamilyName(::TPF::Blue::c_packageFamilyName);
            blue.PackageUri(::TP::GetMsixPackageUri(::TPF::Blue::c_packageDirName));
            packageSet.PackageSetItems().Append(blue);

            auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError());
        }

        TEST_METHOD(EnsureIsReadyAsync_N_RegisteredAndNotInstalled_Success)
        {
            AddPackage_Red();
            RemovePackage_Green();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green;
            green.PackageFamilyName(::TPF::Green::c_packageFamilyName);
            green.PackageUri(::TP::GetMsixPackageUri(::TPF::Green::c_packageDirName));
            packageSet.PackageSetItems().Append(green);

            auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError());
        }

        TEST_METHOD(EnsureIsReadyAsync_N_RegisteredPackageStatusOkAndBad_Success)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            AddPackage_Red();
            AddPackage_Green();
            SetPackageStatus(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red;
            red.PackageFamilyName(::TPF::Red::c_packageFamilyName);
            red.PackageUri(::TP::GetMsixPackageUri(::TPF::Red::c_packageDirName));
            packageSet.PackageSetItems().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green;
            green.PackageFamilyName(::TPF::Green::c_packageFamilyName);
            green.PackageUri(::TP::GetMsixPackageUri(::TPF::Green::c_packageDirName));
            packageSet.PackageSetItems().Append(green);

            auto deploymentResult{ packageDeploymentManager.EnsureIsReadyAsync(packageSet).get() };
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentStatus::CompletedSuccess, deploymentResult.Status());
            VERIFY_ARE_EQUAL(S_OK, deploymentResult.ExtendedError());

            ClearPackageStatus(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
        }

    private:
        winrt::Windows::Management::Deployment::PackageManager m_packageManager;
    };
}
