// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

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
            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::TB::Cleanup();
            return true;
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
                PCWSTR c_packageSetId{ L"Avengers" };
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
                PCWSTR c_packageSetId{ L"Avengers" };
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
                PCWSTR c_packageSetId{ L"Avengers" };
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
                PCWSTR c_packageSetId{ L"Avengers" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageFamilyName{ L"Avengers.ValidButDoesNotExist_1234567890abc" };
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
                PCWSTR c_packageSetId{ L"Avengers" };
                packageSet.Id(c_packageSetId);
                winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
                PCWSTR c_packageUriAsString{ L"https://avengers.com/assemble.msix" };
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

        TEST_METHOD(IsReady_No)
        {
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"Avengers" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
            PCWSTR c_packageFamilyName{ L"Avengers.ValidButDoesNotExist_1234567890abc" };
            packageSetItem.PackageFamilyName(c_packageFamilyName);
            PCWSTR c_packageUriAsString{ L"https://avengers.com/does/not/exist.msix" };
            winrt::Windows::Foundation::Uri c_packageUri{ c_packageUriAsString };
            packageSetItem.PackageUri(c_packageUri);
            packageSet.PackageSetItems().Append(packageSetItem);

            VERIFY_IS_FALSE(packageDeploymentManager.IsReady(packageSet));
        }

        TEST_METHOD(IsReady_Yes)
        {
        }
    };
}
