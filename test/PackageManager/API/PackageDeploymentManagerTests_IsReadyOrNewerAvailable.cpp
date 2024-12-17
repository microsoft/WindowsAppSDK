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
    class PackageDeploymentManagerTests_IsReadyOrNewerAvailable : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_IsReadyOrNewerAvailable)
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

        TEST_METHOD(IsPackageReadyOrNewerAvailable_PackageFullName_InvalidParameter)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            try
            {
                PCWSTR packageFullName{ L"Not a valid Package Full Name" };
                packageDeploymentManager.IsPackageReadyOrNewerAvailable(packageFullName);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(IsPackageReadyOrNewerAvailable_PackageFullName_NoSuchPackage_NotReady)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR c_packageFullName{ L"Does.Not.Exist_1.2.3.4_neutral__1234567890abc" };

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NotReady, packageDeploymentManager.IsPackageReadyOrNewerAvailable(c_packageFullName));
        }

        TEST_METHOD(IsPackageReadyOrNewerAvailable_PackageFullName_NotInstalled_NotReady)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFullName{ ::TPF::Red::GetPackageFullName() };

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NotReady, packageDeploymentManager.IsPackageReadyOrNewerAvailable(packageFullName));
        }

        TEST_METHOD(IsPackageReadyOrNewerAvailable_PackageFullName_Registered_Ready)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFullName{ ::TPF::Red::GetPackageFullName() };

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::Ready, packageDeploymentManager.IsPackageReadyOrNewerAvailable(packageFullName));
        }

        TEST_METHOD(IsPackageReadyOrNewerAvailable_PackageFullName_OlderRegistered_NotReady)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFullName{ ::TPF::Redder::GetPackageFullName() };

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NotReady, packageDeploymentManager.IsPackageReadyOrNewerAvailable(packageFullName));
        }

        TEST_METHOD(IsPackageReadyOrNewerAvailable_PackageFullName_NewerRegistered_Ready)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            AddPackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFullName{ ::TPF::Red::GetPackageFullName() };

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::Ready, packageDeploymentManager.IsPackageReadyOrNewerAvailable(packageFullName));

            RemovePackage_Redder();
        }

        TEST_METHOD(IsPackageReadyOrNewerAvailable_PackageFullName_NewerAvailable)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            RemovePackage_Blacker();
            AddPackage_Black();
            StagePackage_Blacker();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            PCWSTR packageFullName{ ::TPM::Black::GetPackageFullName() };

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NewerAvailable, packageDeploymentManager.IsPackageReadyOrNewerAvailable(packageFullName));

            RemovePackage_Blacker();
        }

        TEST_METHOD(IsPackageReadyOrNewerAvailable_PackageFamilyName_InvalidParameter)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            try
            {
                PCWSTR packageFamilyName{ L"Not a valid Package Family Name" };
                packageDeploymentManager.IsPackageReadyOrNewerAvailable(packageFamilyName);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(IsPackageReadyOrNewerAvailableByUri_InvalidParameter)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable() || TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(IsPackageReadyOrNewerAvailableByUri_NoSuchPackage_NotReady)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable() || TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(IsPackageReadyOrNewerAvailableByUri_NotInstalled_NotReady)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable() || TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(IsPackageReadyOrNewerAvailableByUri_Registered_Ready)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable() || TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(IsPackageReadyOrNewerAvailableByUri_OlderRegistered_NotReady)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable() || TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(IsPackageReadyOrNewerAvailableByUri_NewerRegistered_Ready)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable() || TPMT::SkipIfFeatureNotSupported_PackageUriScheme_ms_uup())
            {
                return;
            }

            WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"Cannot test ms-uup: URIs here. Skipping test");
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_InvalidParameter)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet);
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

                packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet);
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

                packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet);
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

                packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet);
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

                packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_1_NoSuchPackage_NotReady)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
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

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NotReady, packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet));
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_1_NotInstalled_NotReady)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            RemovePackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NotReady, packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet));
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_1_Registered_Ready)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::Ready, packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet));
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_1_OlderRegistered_NotReady)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            AddPackage_Red();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem(::TPF::Redder::GetPackageFullName(), ::TPF::Redder::c_packageDirName) };
            packageSet.Items().Append(redder);

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NotReady, packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet));
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_1_NewerRegistered_Ready)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            AddPackage_Redder();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::Ready, packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_1_NewerAvailable)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            RemovePackage_Blacker();
            AddPackage_Black();
            StagePackage_Blacker();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"B" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem(::TPM::Black::GetPackageFullName(), ::TPM::Black::c_packageDirName) };
            packageSet.Items().Append(black);

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NewerAvailable, packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet));

            RemovePackage_Blacker();
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_N_NotInstalled_NotReady)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
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

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NotReady, packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet));
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_N_Registered_Ready)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
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

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::Ready, packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet));
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_N_OlderRegistered_NotReady)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

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

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NotReady, packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet));
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_N_NewerRegistered_Ready)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

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

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::Ready, packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet));

            RemovePackage_Redder();
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_N_RegisteredAndNotInstalled_NotReady)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
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

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NotReady, packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet));
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_N_RegisteredAndNewerAvailable_NotReady)
        {
            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            AddPackage_Black();
            RemovePackage_Whiter();
            AddPackage_White();
            StagePackage_Whiter();

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"BW" };
            packageSet.Id(c_packageSetId);
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem black{ Make_PackageSetItem(::TPM::Black::GetPackageFullName(), ::TPM::Black::c_packageDirName) };
            packageSet.Items().Append(black);
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem white{ Make_PackageSetItem(::TPM::White::GetPackageFullName(), ::TPM::White::c_packageDirName) };
            packageSet.Items().Append(white);

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NewerAvailable, packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet));
        }

        TEST_METHOD(IsPackageSetReadyOrNewerAvailable_N_No_NotAllPackageStatusOK)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            if (TPMT::SkipIfFeatureNotSupported_IsPackageReadyOrNewerAvailable())
            {
                return;
            }

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };

            AddPackage_Red();
            AddPackage_Green();
            SetPackageStatusByPackageFamilyName(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NotReady, packageDeploymentManager.IsPackageReadyOrNewerAvailable(::TPF::Green::GetPackageFullName()));

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NotReady, packageDeploymentManager.IsPackageSetReadyOrNewerAvailable(packageSet));
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Management::Deployment::PackageReadyOrNewerAvailableStatus::NotReady, packageDeploymentManager.IsPackageReadyOrNewerAvailable(::TPF::Green::GetPackageFullName()));

            ClearPackageStatusByPackageFamilyName(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
        }
    };

    class PackageDeploymentManagerTests_IsReadyOrNewerAvailable_Elevated : PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentManagerTests_IsReadyOrNewerAvailable_Elevated)
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
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
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
    };
}
