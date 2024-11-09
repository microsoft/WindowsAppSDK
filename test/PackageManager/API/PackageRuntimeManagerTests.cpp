// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <MddWin11.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TPF = ::Test::Packages::Framework;
namespace TPM = ::Test::Packages::Main;
namespace TPMT = ::Test::PackageManager::Tests;

namespace Test::PackageManager::Tests
{
    class PackageRuntimeManagerTests
    {
    public:
        BEGIN_TEST_CLASS(PackageRuntimeManagerTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Class")    /****SEEME****/
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!MddCore::Win11::IsSupported())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageRuntimeManager requires Dynamic Dependencies delegating to OS Dynamic Dependencies. Skipping tests");
                return true;
            }

            TD::DumpExecutionContext();

            RemovePackage_Blue();
            RemovePackage_Green();
            RemovePackage_Redder();
            RemovePackage_Red();
            ::TB::Setup();
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();
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

        void SetPackageStatusByPackageFamilyName(PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            TPMT::SetPackageStatusByPackageFamilyName(m_packageManager, packageFamilyName, status);
        }

        void ClearPackageStatusByPackageFamilyName(PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
        {
            TPMT::ClearPackageStatusByPackageFamilyName(m_packageManager, packageFamilyName, status);
        }

        TEST_METHOD(AddPackageSet_InvalidParameter)
        {
            auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };

            try
            {
                winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
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

                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
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

                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
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

                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
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

                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
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
                winrt::Windows::Foundation::Uri c_packageUri{ c_packageUriAsString };
                packageSetItem.PackageUri(c_packageUri);
                packageSet.Items().Append(packageSetItem);

                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(AddPackageSet_1_NoSuchPackage_Fail)
        {
            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"Does.Not.Exist" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem packageSetItem;
            PCWSTR c_packageFamilyName{ L"Does.Not.Exist_1234567890abc" };
            packageSetItem.PackageFamilyName(c_packageFamilyName);
            PCWSTR c_packageUriAsString{ L"file://c:/does/not/exist.msix" };
            winrt::Windows::Foundation::Uri c_packageUri{ c_packageUriAsString };
            packageSetItem.PackageUri(c_packageUri);
            packageSet.Items().Append(packageSetItem);
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));

            try
            {
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(AddPackageSet_1_NotInstalled_Fail)
        {
            RemovePackage_Red();

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);

            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));

            try
            {
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(AddPackageSet_1_Staged_Fail)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            RemovePackage_Red();
            StagePackage_Red();

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));

            try
            {
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(AddPackageSet_1_Registered_Success)
        {
            AddPackage_Red();

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
            auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
            const auto packageSetRuntimeDisposition{ packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions) };

            packageRuntimeManager.RemovePackageSet(packageSetRuntimeDisposition);
        }

        TEST_METHOD(AddPackageSet_1_OlderRegistered_Fail)
        {
            RemovePackage_Redder();
            AddPackage_Red();

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem(::TPF::Redder::GetPackageFullName(), ::TPF::Redder::c_packageDirName) };
            packageSet.Items().Append(redder);
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));

            try
            {
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(AddPackageSet_1_NewerRegistered_Success)
        {
            AddPackage_Redder();

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
            auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
            const auto packageSetRuntimeDisposition{ packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions) };

            packageRuntimeManager.RemovePackageSet(packageSetRuntimeDisposition);

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageSet_1_RegisteredPackageStatusBad_Fail)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            AddPackage_Red();
            SetPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));

            try
            {
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            ClearPackageStatusByPackageFamilyName(::TPF::Red::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
        }

        TEST_METHOD(AddPackageSet_N_NotInstalled_Fail)
        {
            RemovePackage_Red();
            RemovePackage_Green();
            RemovePackage_Blue();

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));

            try
            {
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(AddPackageSet_N_Registered_Success)
        {
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
            auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
            const auto packageSetRuntimeDisposition{ packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions) };

            packageRuntimeManager.RemovePackageSet(packageSetRuntimeDisposition);
        }

        TEST_METHOD(AddPackageSet_N_NewerRegistered_Success)
        {
            AddPackage_Redder();
            AddPackage_Green();
            AddPackage_Blue();

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_TRUE(packageDeploymentManager.IsPackageSetReady(packageSet));

            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
            winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
            auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
            const auto packageSetRuntimeDisposition{ packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions) };

            packageRuntimeManager.RemovePackageSet(packageSetRuntimeDisposition);

            RemovePackage_Redder();
        }

        TEST_METHOD(AddPackageSet_N_OlderRegistered_Fail)
        {
            AddPackage_Red();
            AddPackage_Green();
            AddPackage_Blue();

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem redder{ Make_PackageSetItem(::TPF::Redder::GetPackageFullName(), ::TPF::Redder::c_packageDirName) };
            packageSet.Items().Append(redder);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Blue::GetPackageFullName(), ::TPF::Blue::c_packageDirName) };
            packageSet.Items().Append(blue);
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));

            try
            {
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(AddPackageSet_N_RegisteredAndNotInstalled_Fail)
        {
            AddPackage_Red();
            RemovePackage_Green();

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));

            try
            {
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(AddPackageSet_N_RegisteredAndNotInstalledAndStaged_Fail)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            AddPackage_Red();
            RemovePackage_Green();
            StagePackage_Blue();

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem blue{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(blue);
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));

            try
            {
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(AddPackageSet_N_RegisteredPackageStatusOkAndBad_Fail)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            END_TEST_METHOD_PROPERTIES()

            AddPackage_Red();
            AddPackage_Green();
            SetPackageStatusByPackageFamilyName(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);

            winrt::Microsoft::Windows::Management::Deployment::PackageSet packageSet;
            PCWSTR c_packageSetId{ L"RGB" };
            packageSet.Id(c_packageSetId);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem red{ Make_PackageSetItem(::TPF::Red::GetPackageFullName(), ::TPF::Red::c_packageDirName) };
            packageSet.Items().Append(red);
            winrt::Microsoft::Windows::Management::Deployment::PackageSetItem green{ Make_PackageSetItem(::TPF::Green::GetPackageFullName(), ::TPF::Green::c_packageDirName) };
            packageSet.Items().Append(green);
            auto packageDeploymentManager{ winrt::Microsoft::Windows::Management::Deployment::PackageDeploymentManager::GetDefault() };
            VERIFY_IS_FALSE(packageDeploymentManager.IsPackageSetReady(packageSet));

            try
            {
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::CreatePackageDependencyOptions createOptions;
                winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions;
                auto packageRuntimeManager{ winrt::Microsoft::Windows::Management::Deployment::PackageRuntimeManager::GetDefault() };
                packageRuntimeManager.AddPackageSet(packageSet, createOptions, addOptions);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            ClearPackageStatusByPackageFamilyName(::TPF::Green::c_packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus::Modified);
        }

    private:
        winrt::Windows::Management::Deployment::PackageManager m_packageManager;
    };
}
