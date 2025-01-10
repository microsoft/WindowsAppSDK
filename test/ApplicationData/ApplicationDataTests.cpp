// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

static const winrt::hstring null_hstring;

namespace Test::ApplicationData::Tests
{
    const auto Main_PackageFamilyName{ ::TP::DynamicDependencyDataStore::c_PackageFamilyName };
    const auto Framework_PackageFamilyName{ ::TP::WindowsAppRuntimeFramework::c_PackageFamilyName };

    class ApplicationDataTests
    {
    public:
        BEGIN_TEST_CLASS(ApplicationDataTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Class")
            TEST_CLASS_PROPERTY(L"RunAs", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!::WindowsVersion::IsWindows11_21H2OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageDeploymentManager requires Win11 >= 21H2 (SV1). Skipping tests");
                return true;
            }

            ::TD::DumpExecutionContext();

            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::TB::Cleanup();
            return true;
        }

        TEST_METHOD(GetDefault_Main)
        {
            //TODO
        }

        TEST_METHOD(GetDefault_Framework)
        {
            //TODO
        }

        TEST_METHOD(GetForPackageFamily_Main)
        {
            winrt::hstring packageFamilyName{ Main_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            auto systemApplicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);
        }

        TEST_METHOD(GetForPackageFamily_Framework)
        {
            winrt::hstring packageFamilyName{ Framework_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            try
            {
                auto systemApplicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(GetForUser_Main)
        {
            //TODO
        }

        TEST_METHOD(GetForUser_Framework)
        {
            //TODO
        }

        TEST_METHOD(FolderAndPath_Main)
        {
            winrt::hstring packageFamilyName{ Main_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            auto systemApplicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(systemApplicationData);

            const auto localCacheFolder{ applicationData.LocalCacheFolder() };
            const auto localCachePath{ applicationData.LocalCachePath() };
            VERIFY_ARE_EQUAL(localCacheFolder.Path(), localCachePath);
            const auto expectedLocalCacheFolder{ systemApplicationData.LocalCacheFolder() };
            const auto expectedLocalCachePath{ expectedLocalCacheFolder.Path() };
            VERIFY_ARE_EQUAL(localCachePath, expectedLocalCachePath);

            const auto localFolder{ applicationData.LocalFolder() };
            const auto localPath{ applicationData.LocalPath() };
            VERIFY_ARE_EQUAL(localFolder.Path(), localPath);
            const auto expectedLocalFolder{ systemApplicationData.LocalFolder() };
            const auto expectedLocalPath{ expectedLocalFolder.Path() };
            VERIFY_ARE_EQUAL(localPath, expectedLocalPath);

            // SharedLocalFolder is only available if the appropriate group policy is enabled
            // If not enabled then SharedLocalFolder = SharedLocalPath = null
            const auto sharedLocalFolder{ applicationData.SharedLocalFolder() };
            const auto sharedLocalPath{ applicationData.SharedLocalPath() };
            if (sharedLocalFolder)
            {
                VERIFY_ARE_EQUAL(sharedLocalFolder.Path(), sharedLocalPath);
            }
            else
            {
                VERIFY_IS_NULL(sharedLocalFolder);
                VERIFY_ARE_EQUAL(sharedLocalPath, null_hstring);
            }
            const auto expectedSharedLocalFolder{ systemApplicationData.SharedLocalFolder() };
            winrt::hstring expectedSharedLocalPath;
            if (expectedSharedLocalFolder)
            {
                expectedSharedLocalPath = expectedSharedLocalFolder.Path();
            };
            VERIFY_ARE_EQUAL(sharedLocalPath, expectedSharedLocalPath);

            const auto temporaryFolder{ applicationData.TemporaryFolder() };
            const auto temporaryPath{ applicationData.TemporaryPath() };
            VERIFY_ARE_EQUAL(temporaryFolder.Path(), temporaryPath);
            const auto expectedTemporaryFolder{ systemApplicationData.TemporaryFolder() };
            const auto expectedTemporaryPath{ expectedTemporaryFolder.Path() };
            VERIFY_ARE_EQUAL(temporaryPath, expectedTemporaryPath);
        }

        TEST_METHOD(FolderAndPath_Framework)
        {
            winrt::hstring packageFamilyName{ Framework_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);
            const auto localCacheFolder{ applicationData.LocalCacheFolder() };
            VERIFY_IS_NULL(localCacheFolder);
            const auto localCachePath{ applicationData.LocalCachePath() };
            VERIFY_ARE_EQUAL(localCachePath, null_hstring);
            const auto localFolder{ applicationData.LocalFolder() };
            VERIFY_IS_NULL(localFolder);
            const auto localPath{ applicationData.LocalPath() };
            VERIFY_ARE_EQUAL(localPath, null_hstring);
            const auto sharedLocalFolder{ applicationData.SharedLocalFolder() };
            VERIFY_IS_NULL(sharedLocalFolder);
            const auto sharedLocalPath{ applicationData.SharedLocalPath() };
            VERIFY_ARE_EQUAL(sharedLocalPath, null_hstring);
            const auto temporaryFolder{ applicationData.TemporaryFolder() };
            VERIFY_IS_NULL(temporaryFolder);
            const auto temporaryPath{ applicationData.TemporaryPath() };
            VERIFY_ARE_EQUAL(temporaryPath, null_hstring);

            try
            {
                auto systemApplicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(PublisherCacheFolderAndPath_Main)
        {
            winrt::hstring packageFamilyName{ Main_PackageFamilyName };
            winrt::hstring folderName{ L"Does.Not.Exist" };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            auto systemApplicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(systemApplicationData);

            const auto publisherCacheFolder{ applicationData.GetPublisherCacheFolder(folderName) };
            const auto publisherCachePath{ applicationData.GetPublisherCachePath(folderName) };
            if (publisherCacheFolder)
            {
                VERIFY_ARE_EQUAL(publisherCacheFolder.Path(), publisherCachePath);
            }
            else
            {
                VERIFY_IS_NULL(publisherCacheFolder);
                VERIFY_ARE_EQUAL(publisherCachePath, null_hstring);
            }
            try
            {
                const auto expectedPublisherCacheFolder{ systemApplicationData.GetPublisherCacheFolder(folderName) };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
            const auto expectedPublisherCachePath{ null_hstring };
            VERIFY_ARE_EQUAL(publisherCachePath, expectedPublisherCachePath);
        }

        TEST_METHOD(PublisherCacheFolderAndPath_Framework)
        {
            winrt::hstring packageFamilyName{ Framework_PackageFamilyName };
            winrt::hstring folderName{ L"Does.Not.Exist" };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            try
            {
                auto systemApplicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            const auto publisherCacheFolder{ applicationData.GetPublisherCacheFolder(folderName) };
            VERIFY_IS_NULL(publisherCacheFolder);
            const auto publisherCachePath{ applicationData.GetPublisherCachePath(folderName) };
            VERIFY_ARE_EQUAL(publisherCachePath, null_hstring);
        }

        TEST_METHOD(MachineFolderAndPath_Main_NotSupported)
        {
            winrt::hstring packageFamilyName{ Main_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            VERIFY_IS_FALSE(applicationData.IsMachinePathSupported());

            const auto machineFolder{ applicationData.MachineFolder() };
            VERIFY_IS_NULL(machineFolder);
            const auto machinePath{ applicationData.MachinePath() };
            VERIFY_ARE_EQUAL(machinePath, null_hstring);
        }

        TEST_METHOD(MachineFolderAndPath_Framework_NotSupported)
        {
            winrt::hstring packageFamilyName{ Framework_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            VERIFY_IS_FALSE(applicationData.IsMachinePathSupported());

            const auto machineFolder{ applicationData.MachineFolder() };
            VERIFY_IS_NULL(machineFolder);
            const auto machinePath{ applicationData.MachinePath() };
            VERIFY_ARE_EQUAL(machinePath, null_hstring);
        }

        TEST_METHOD(LocalSettings_Main)
        {
            winrt::hstring packageFamilyName{ Main_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            auto systemApplicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(systemApplicationData);

            const auto localSettings{ applicationData.LocalSettings() };
            const auto systemLocalSettings{ systemApplicationData.LocalSettings() };
            VERIFY_ARE_EQUAL(static_cast<int32_t>(localSettings.Locality()), static_cast<int32_t>(systemLocalSettings.Locality()));

            auto containers{ localSettings.Containers() };
            VERIFY_ARE_EQUAL(0u, containers.Size());
            auto systemContainers{ systemLocalSettings.Containers() };
            VERIFY_ARE_EQUAL(0u, systemContainers.Size());
            VERIFY_ARE_EQUAL(containers.Size(), systemContainers.Size());

            const winrt::hstring foodAndStuff{ L"FoodAndStuff" };
            VERIFY_IS_FALSE(containers.HasKey(foodAndStuff));
            VERIFY_IS_FALSE(systemContainers.HasKey(foodAndStuff));

            auto container{ localSettings.CreateContainer(foodAndStuff, winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition::Always) };
            VERIFY_ARE_EQUAL(foodAndStuff, container.Name());
            //
            VERIFY_ARE_EQUAL(0u, containers.Size());
            VERIFY_IS_FALSE(containers.HasKey(foodAndStuff));
            containers = localSettings.Containers();
            VERIFY_ARE_EQUAL(1u, containers.Size());
            VERIFY_IS_TRUE(containers.HasKey(foodAndStuff));
            container = containers.Lookup(foodAndStuff);
            VERIFY_IS_NOT_NULL(container);
            VERIFY_ARE_EQUAL(foodAndStuff, container.Name());
            //
            VERIFY_ARE_EQUAL(0u, systemContainers.Size());
            VERIFY_IS_FALSE(systemContainers.HasKey(foodAndStuff));
            systemContainers = systemLocalSettings.Containers();
            VERIFY_ARE_EQUAL(1u, systemContainers.Size());
            VERIFY_IS_TRUE(systemContainers.HasKey(foodAndStuff));
            auto systemContainer{ systemContainers.Lookup(foodAndStuff) };
            VERIFY_IS_NOT_NULL(systemContainer);
            VERIFY_ARE_EQUAL(foodAndStuff, systemContainer.Name());

            const winrt::hstring keyMeat{ L"Meat" };
            const winrt::hstring rawValueSteak{ L"Steak" };
            auto valueSteak{ winrt::Windows::Foundation::PropertyValue::CreateString(rawValueSteak) };
            auto values{ container.Values() };
            VERIFY_ARE_EQUAL(0u, values.Size());
            values.Insert(keyMeat, valueSteak);
            VERIFY_ARE_EQUAL(1u, values.Size());
            auto steak{ values.Lookup(keyMeat) };
            VERIFY_IS_NOT_NULL(steak);
            auto steakLookupAsReferenceString{ steak.try_as<winrt::Windows::Foundation::IReference<winrt::hstring>>() };
            VERIFY_IS_NOT_NULL(steakLookupAsReferenceString);
            auto steakString{ steakLookupAsReferenceString.GetString() };
            VERIFY_ARE_EQUAL(rawValueSteak, steakString);
            //
            auto systemValues{ systemContainer.Values() };
            VERIFY_ARE_EQUAL(1u, systemValues.Size());
            auto systemSteak{ systemValues.Lookup(keyMeat) };
            VERIFY_IS_NOT_NULL(systemSteak);
            auto systemSteakLookupAsReferenceString{ systemSteak.try_as<winrt::Windows::Foundation::IReference<winrt::hstring>>() };
            VERIFY_IS_NOT_NULL(systemSteakLookupAsReferenceString);
            auto systemSteakString{ systemSteakLookupAsReferenceString.GetString() };
            VERIFY_ARE_EQUAL(rawValueSteak, systemSteakString);

            const winrt::hstring keyDrink{ L"Drink" };
            const winrt::hstring rawValueWhiskey{ L"Whiskey" };
            auto valueWhiskey{ winrt::Windows::Foundation::PropertyValue::CreateString(rawValueWhiskey) };
            VERIFY_ARE_EQUAL(1u, systemValues.Size());
            systemValues.Insert(keyDrink, valueWhiskey);
            VERIFY_ARE_EQUAL(2u, systemValues.Size());
            auto systemWhiskey{ systemValues.Lookup(keyDrink) };
            VERIFY_IS_NOT_NULL(systemWhiskey);
            auto systemWhiskeyLookupAsReferenceString{ systemWhiskey.try_as<winrt::Windows::Foundation::IReference<winrt::hstring>>() };
            VERIFY_IS_NOT_NULL(systemWhiskeyLookupAsReferenceString);
            auto systemWhiskeyString{ systemWhiskeyLookupAsReferenceString.GetString() };
            VERIFY_ARE_EQUAL(rawValueWhiskey, systemWhiskeyString);
            //
            VERIFY_ARE_EQUAL(2u, values.Size());
            auto whiskey{ values.Lookup(keyDrink) };
            VERIFY_IS_NOT_NULL(whiskey);
            auto whiskeyLookupAsReferenceString{ whiskey.try_as<winrt::Windows::Foundation::IReference<winrt::hstring>>() };
            VERIFY_IS_NOT_NULL(whiskeyLookupAsReferenceString);
            auto whiskeyString{ whiskeyLookupAsReferenceString.GetString() };
            VERIFY_ARE_EQUAL(rawValueWhiskey, whiskeyString);

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Local, container.Locality());
            container.Close();
            try
            {
                [[maybe_unused]] auto locality{ container.Locality() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
            VERIFY_ARE_EQUAL(winrt::Windows::Storage::ApplicationDataLocality::Local, systemContainer.Locality());
            systemContainer.Close();
            try
            {
                [[maybe_unused]] auto locality{ systemContainer.Locality() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            VERIFY_ARE_EQUAL(1u, localSettings.Containers().Size());
            VERIFY_ARE_EQUAL(1u, systemLocalSettings.Containers().Size());
            localSettings.DeleteContainer(foodAndStuff);
            VERIFY_ARE_EQUAL(0u, localSettings.Containers().Size());
            VERIFY_ARE_EQUAL(0u, systemLocalSettings.Containers().Size());

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Local, localSettings.Locality());
            localSettings.Close();
            try
            {
                [[maybe_unused]] auto locality{ localSettings.Locality() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
            VERIFY_ARE_EQUAL(winrt::Windows::Storage::ApplicationDataLocality::Local, systemLocalSettings.Locality());
            systemLocalSettings.Close();
            try
            {
                [[maybe_unused]] auto locality{ systemLocalSettings.Locality() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(LocalSettings_Framework)
        {
            winrt::hstring packageFamilyName{ Framework_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);
            const auto localSettings{ applicationData.LocalSettings() };
            VERIFY_IS_NULL(localSettings);

            try
            {
                auto systemApplicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(ClearAsync_Main)
        {
            //TODO
        }

        TEST_METHOD(ClearAsync_Framework)
        {
            //TODO
        }

        TEST_METHOD(ClearFolderAsync_Machine_Main)
        {
            //TODO
        }

        TEST_METHOD(ClearFolderAsync_Machine_Framework)
        {
            //TODO
        }

        TEST_METHOD(ClearPublisherCacheFolderAsync_Main)
        {
            //TODO
        }

        TEST_METHOD(ClearPublisherCacheFolderAsync_Framework)
        {
            //TODO
        }
    };
}
