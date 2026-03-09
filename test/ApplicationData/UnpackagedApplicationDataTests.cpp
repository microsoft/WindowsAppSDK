// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TD = ::Test::Diagnostics;

static const winrt::hstring null_hstring;

namespace Test::ApplicationData::Tests
{
    const winrt::hstring Publisher{ L"ApplicationDataTests" };
    const winrt::hstring Product{ L"UnpackagedApplicationDataTests" };

    class UnpackagedApplicationDataTests
    {
    public:
        BEGIN_TEST_CLASS(UnpackagedApplicationDataTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Class")
            TEST_CLASS_PROPERTY(L"RunAs", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            ::TD::DumpExecutionContext();
            if (!::WindowsVersion::IsWindows11_21H2OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"ApplicationData requires Win11 >= 21H2 (SV1). Skipping tests");
                return true;
            }

            ::TD::DumpExecutionContext();

            ::TB::Setup();
            CreateResources();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            DeleteResources();
            ::TB::Cleanup();
            return true;
        }

        void CreateResources()
        {
            CreateResources_FileSystem();
             // Registry resources are created by the code under test, so no need to create them here
             // But delete any pre-existing in case a previous test crashed or otherwise didn't complete and clean up properly
             DeleteResources_Registry();
        }

        void CreateResources_FileSystem()
        {
            const auto localPath{ UserLocalPath(Publisher, Product) };
            VERIFY_SUCCEEDED(wil::CreateDirectoryDeepNoThrow(localPath.c_str()),
                             WEX::Common::String().Format(L"MKDIR %s", localPath.c_str()));

            const auto temporaryPath{ UserTemporaryPath(Publisher, Product) };
            VERIFY_SUCCEEDED(wil::CreateDirectoryDeepNoThrow(temporaryPath.c_str()),
                             WEX::Common::String().Format(L"MKDIR %s", temporaryPath.c_str()));
        }

        void DeleteResources()
        {
            DeleteResources_FileSystem();
            DeleteResources_Registry();
        }

        void DeleteResources_FileSystem()
        {
            const std::filesystem::path temporaryPath{ UserTemporaryPath(Publisher).c_str() };
            if (PathExists(temporaryPath))
            {
                const auto removeOptions{ wil::RemoveDirectoryOptions::RemoveReadOnly };
                VERIFY_SUCCEEDED(wil::RemoveDirectoryRecursiveNoThrow(temporaryPath.c_str(), removeOptions),
                                 WEX::Common::String().Format(L"RMDIR %s", temporaryPath.c_str()));
            }

            const std::filesystem::path localPath{ UserLocalPath(Publisher).c_str() };
            if (PathExists(localPath))
            {
                const auto removeOptions{ wil::RemoveDirectoryOptions::RemoveReadOnly };
                VERIFY_SUCCEEDED(wil::RemoveDirectoryRecursiveNoThrow(localPath.c_str(), removeOptions),
                                 WEX::Common::String().Format(L"RMDIR %s", localPath.c_str()));
            }
        }

        void DeleteResources_Registry()
        {
            PCWSTR c_product{ L"Software\\TestApplicationData_Contoso" };
            const auto hr{ HRESULT_FROM_WIN32(::RegDeleteTreeW(HKEY_CURRENT_USER, c_product)) };
            if (!wil::reg::is_registry_not_found(hr))
            {
                VERIFY_SUCCEEDED(hr, WEX::Common::String().Format(L"RegDeleteTreeW HKEY_CURRENT_USER\\%s", c_product));
            }
        }

        TEST_METHOD(GetForUnpackaged_InvalidParameter)
        {
            const winrt::hstring publisher{ L"FabrikamTest" };
            const winrt::hstring product{ L"ApplicationDataTest" };
            const winrt::hstring emptyString;

            try
            {
                [[maybe_unused]] auto unpackagedApplicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(emptyString, Product) };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                [[maybe_unused]] auto unpackagedApplicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(Publisher, emptyString) };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_INVALIDARG, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(GetForUnpackaged)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(Publisher, Product) };
            VERIFY_IS_NOT_NULL(applicationData);
        }

        static bool PathExists(std::filesystem::path const& path)
        {
            const std::filesystem::directory_entry directoryEntry{ path };
            return directoryEntry.is_directory();
        }

        std::filesystem::path UserLocalPath(winrt::hstring const& publisher)
        {
            // Caller is LocalSystem    : %PROGRAMDATA%\...publisher...
            // Caller is <MediumIL (Low): %USERPROFILE%\AppData\LocalLow\...publisher...
            // Caller is >=MediumIL     : %USERPROFILE%\AppData\Local\...publisher...
            auto folderId{ FOLDERID_LocalAppData };
            if (::Security::User::IsLocalSystem())
            {
                folderId = FOLDERID_ProgramData;
            }
            else if (::Security::IntegrityLevel::GetIntegrityLevel() < SECURITY_MANDATORY_MEDIUM_RID)
            {
                folderId = FOLDERID_LocalAppDataLow;
            }
            wil::unique_cotaskmem_string rootPath;
            VERIFY_SUCCEEDED(SHGetKnownFolderPath(folderId, KF_FLAG_DEFAULT/*TODO KF_FLAG_CREATE | KF_FLAG_DONT_VERIFY*/, nullptr, wil::out_param(rootPath)));
            std::filesystem::path path{ rootPath.get() };
            path /= publisher.c_str();
            return path;
        }

        winrt::hstring UserLocalPath(winrt::hstring const& publisher, winrt::hstring const& product)
        {
            // Caller is LocalSystem    : %PROGRAMDATA%\...publisher...\...product...
            // Caller is <MediumIL (Low): %USERPROFILE%\AppData\LocalLow\...publisher...\...product...
            // Caller is >=MediumIL     : %USERPROFILE%\AppData\Local\...publisher...\...product...
            auto path{ UserLocalPath(publisher) };
            path /= product.c_str();
            return winrt::hstring{ path.c_str() };
        }

        winrt::Windows::Storage::StorageFolder UserLocalFolder(winrt::hstring const& publisher, winrt::hstring const& product)
        {
            const auto path{ UserLocalPath(publisher, product) };
            return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(path).get();
        }

        std::filesystem::path UserTemporaryPath(winrt::hstring const& publisher)
        {
            // GetTempPath[2]() + \...publisher...
            auto path{ ::Microsoft::FileSystem::Path::GetTempDirectory() };
            path /= publisher.c_str();
            return path;
        }

        winrt::hstring UserTemporaryPath(winrt::hstring const& publisher, winrt::hstring const& product)
        {
            // GetTempPath[2]() + \...publisher...\...product...
            auto path{ UserTemporaryPath(publisher) };
            path /= product.c_str();
            return winrt::hstring{ path.c_str() };
        }

        winrt::Windows::Storage::StorageFolder UserTemporaryFolder(winrt::hstring const& publisher, winrt::hstring const& product)
        {
            const auto path{ UserTemporaryPath(publisher, product) };
            return winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(path).get();
        }

        TEST_METHOD(LocalCacheFolderAndPath)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(Publisher, Product) };
            VERIFY_IS_NOT_NULL(applicationData);

            try
            {
                [[maybe_unused]] auto path{ applicationData.LocalCachePath() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_NOTIMPL, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                [[maybe_unused]] auto folder{ applicationData.LocalCacheFolder() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_NOTIMPL, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(LocalFolderAndPath)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(Publisher, Product) };
            VERIFY_IS_NOT_NULL(applicationData);

            const auto localFolder{ applicationData.LocalFolder() };
            const auto localPath{ applicationData.LocalPath() };
            VERIFY_ARE_EQUAL(localFolder.Path(), localPath);
            const auto expectedLocalFolder{ UserLocalFolder(Publisher, Product) };
            const auto expectedLocalPath{ UserLocalPath(Publisher, Product) };
            VERIFY_ARE_EQUAL(localPath, expectedLocalPath);
        }

        TEST_METHOD(SharedLocalFolderAndPath)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(Publisher, Product) };
            VERIFY_IS_NOT_NULL(applicationData);

            try
            {
                [[maybe_unused]] auto path{ applicationData.SharedLocalPath() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_NOTIMPL, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                [[maybe_unused]] auto folder{ applicationData.SharedLocalFolder() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_NOTIMPL, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(TemporaryFolderAndPath)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(Publisher, Product) };
            VERIFY_IS_NOT_NULL(applicationData);

            const auto temporaryFolder{ applicationData.TemporaryFolder() };
            const auto temporaryPath{ applicationData.TemporaryPath() };
            VERIFY_ARE_EQUAL(temporaryFolder.Path(), temporaryPath);
            const auto expectedTemporaryFolder{ UserTemporaryFolder(Publisher, Product) };
            const auto expectedTemporaryPath{ UserTemporaryPath(Publisher, Product) };
            VERIFY_ARE_EQUAL(temporaryPath, expectedTemporaryPath);
        }

        TEST_METHOD(PublisherCacheFolderAndPath)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(Publisher, Product) };
            VERIFY_IS_NOT_NULL(applicationData);

            winrt::hstring folderName{ L"Does.Not.Exist" };
            try
            {
                [[maybe_unused]] auto path{ applicationData.GetPublisherCachePath(folderName) };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_NOTIMPL, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                [[maybe_unused]] auto folder{ applicationData.GetPublisherCacheFolder(folderName) };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(E_NOTIMPL, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(MachineFolderAndPath_NotSupported)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(Publisher, Product) };
            VERIFY_IS_NOT_NULL(applicationData);

            VERIFY_IS_FALSE(applicationData.IsMachinePathSupported());

            const auto machinePath{ applicationData.MachinePath() };
            VERIFY_ARE_EQUAL(machinePath, null_hstring);
            const auto machineFolder{ applicationData.MachineFolder() };
            VERIFY_IS_NULL(machineFolder);
        }

        TEST_METHOD(LocalSettings)
        {
#ifdef TODO_LocalSettings
            winrt::hstring packageFamilyName{ Main_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(Publisher, Product) };
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
#endif
        }

        TEST_METHOD(ClearAsync)
        {
            //TODO
        }

        TEST_METHOD(ClearFolderAsync_Machine)
        {
            //TODO
        }

        TEST_METHOD(ClearPublisherCacheFolderAsync)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(Publisher, Product) };
            VERIFY_IS_NOT_NULL(applicationData);
            winrt::hstring folderName{ L"Does.Not.Exist" };
            [[maybe_unused]] auto asyncAction{ applicationData.ClearPublisherCacheFolderAsync(folderName) };
            VERIFY_ARE_EQUAL(winrt::Windows::Foundation::AsyncStatus::Error, asyncAction.Status());
            VERIFY_ARE_EQUAL(E_NOTIMPL, asyncAction.ErrorCode());
        }

        TEST_METHOD(ContainerOperations)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(L"TestApplicationData_Contoso", L"SupermarketPointOfSale") };
            VERIFY_IS_NOT_NULL(applicationData);

            auto localSettings{ applicationData.LocalSettings() };
            VERIFY_IS_NOT_NULL(localSettings);
            VERIFY_ARE_EQUAL(L"", localSettings.Name());
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Local, localSettings.Locality());

            // Start clean
            auto containers{ localSettings.Containers() };
            if (containers.HasKey(L"Inventory"))
            {
                localSettings.DeleteContainer(L"Inventory");
            }
            containers = localSettings.Containers();
            VERIFY_IS_FALSE(containers.HasKey(L"Inventory"));

            // CreateContainer with Always creates a new container
            auto inventory{ localSettings.CreateContainer(L"Inventory", winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition::Always) };
            VERIFY_IS_NOT_NULL(inventory);
            VERIFY_ARE_EQUAL(L"Inventory", inventory.Name());
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Local, inventory.Locality());

            containers = localSettings.Containers();
            VERIFY_ARE_EQUAL(1u, containers.Size());
            VERIFY_IS_TRUE(containers.HasKey(L"Inventory"));
            auto lookedUp{ containers.Lookup(L"Inventory") };
            VERIFY_IS_NOT_NULL(lookedUp);
            VERIFY_ARE_EQUAL(L"Inventory", lookedUp.Name());

            // CreateContainer with Always on existing container returns it
            auto inventoryAgain{ localSettings.CreateContainer(L"Inventory", winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition::Always) };
            VERIFY_IS_NOT_NULL(inventoryAgain);
            VERIFY_ARE_EQUAL(L"Inventory", inventoryAgain.Name());
            containers = localSettings.Containers();
            VERIFY_ARE_EQUAL(1u, containers.Size());

            // CreateContainer with Existing on existing container returns it
            auto inventoryExisting{ localSettings.CreateContainer(L"Inventory", winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition::Existing) };
            VERIFY_IS_NOT_NULL(inventoryExisting);
            VERIFY_ARE_EQUAL(L"Inventory", inventoryExisting.Name());

            // Multiple containers
            auto pricing{ localSettings.CreateContainer(L"Pricing", winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition::Always) };
            containers = localSettings.Containers();
            VERIFY_ARE_EQUAL(2u, containers.Size());
            VERIFY_IS_TRUE(containers.HasKey(L"Inventory"));
            VERIFY_IS_TRUE(containers.HasKey(L"Pricing"));

            // Values in a child container
            auto inventoryValues{ inventory.Values() };
            VERIFY_ARE_EQUAL(0u, inventoryValues.Size());
            inventoryValues.Insert(L"SKU", winrt::box_value(L"ABC-123"));
            VERIFY_ARE_EQUAL(1u, inventoryValues.Size());
            auto sku{ winrt::unbox_value<winrt::hstring>(inventoryValues.Lookup(L"SKU")) };
            VERIFY_ARE_EQUAL(L"ABC-123", sku);

            // DeleteContainer removes the container and its values
            localSettings.DeleteContainer(L"Inventory");
            containers = localSettings.Containers();
            VERIFY_ARE_EQUAL(1u, containers.Size());
            VERIFY_IS_FALSE(containers.HasKey(L"Inventory"));
            VERIFY_IS_TRUE(containers.HasKey(L"Pricing"));

            // Cleanup
            localSettings.DeleteContainer(L"Pricing");
            containers = localSettings.Containers();
            VERIFY_ARE_EQUAL(0u, containers.Size());
        }

        TEST_METHOD(Values_ScalarTypes)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(L"TestApplicationData_Contoso", L"SupermarketPointOfSale") };
            auto localSettings{ applicationData.LocalSettings() };
            auto values{ localSettings.Values() };
            values.Clear();

            // Empty (null)
            values.Insert(L"Empty", nullptr);
            VERIFY_IS_TRUE(values.HasKey(L"Empty"));
            auto emptyVal{ values.Lookup(L"Empty") };
            VERIFY_IS_NULL(emptyVal);

            // String
            values.Insert(L"String", winrt::box_value(L"Hello World"));
            VERIFY_ARE_EQUAL(L"Hello World", winrt::unbox_value<winrt::hstring>(values.Lookup(L"String")));

            // UInt8
            values.Insert(L"UInt8", winrt::box_value(static_cast<uint8_t>(42)));
            VERIFY_ARE_EQUAL(static_cast<uint8_t>(42), winrt::unbox_value<uint8_t>(values.Lookup(L"UInt8")));

            // Int16
            values.Insert(L"Int16", winrt::box_value(static_cast<int16_t>(-1234)));
            VERIFY_ARE_EQUAL(static_cast<int16_t>(-1234), winrt::unbox_value<int16_t>(values.Lookup(L"Int16")));

            // UInt16
            values.Insert(L"UInt16", winrt::box_value(static_cast<uint16_t>(65535)));
            VERIFY_ARE_EQUAL(static_cast<uint16_t>(65535), winrt::unbox_value<uint16_t>(values.Lookup(L"UInt16")));

            // Int32
            values.Insert(L"Int32", winrt::box_value(static_cast<int32_t>(-100000)));
            VERIFY_ARE_EQUAL(static_cast<int32_t>(-100000), winrt::unbox_value<int32_t>(values.Lookup(L"Int32")));

            // UInt32
            values.Insert(L"UInt32", winrt::box_value(static_cast<uint32_t>(3000000000u)));
            VERIFY_ARE_EQUAL(static_cast<uint32_t>(3000000000u), winrt::unbox_value<uint32_t>(values.Lookup(L"UInt32")));

            // Int64
            values.Insert(L"Int64", winrt::box_value(static_cast<int64_t>(-9876543210LL)));
            VERIFY_ARE_EQUAL(static_cast<int64_t>(-9876543210LL), winrt::unbox_value<int64_t>(values.Lookup(L"Int64")));

            // UInt64
            values.Insert(L"UInt64", winrt::box_value(static_cast<uint64_t>(18000000000000000000ULL)));
            VERIFY_ARE_EQUAL(static_cast<uint64_t>(18000000000000000000ULL), winrt::unbox_value<uint64_t>(values.Lookup(L"UInt64")));

            // Single
            values.Insert(L"Single", winrt::box_value(3.14f));
            VERIFY_ARE_EQUAL(3.14f, winrt::unbox_value<float>(values.Lookup(L"Single")));

            // Double
            values.Insert(L"Double", winrt::box_value(2.718281828));
            VERIFY_ARE_EQUAL(2.718281828, winrt::unbox_value<double>(values.Lookup(L"Double")));

            // Char16
            values.Insert(L"Char16", winrt::box_value(u'Z'));
            VERIFY_ARE_EQUAL(u'Z', winrt::unbox_value<char16_t>(values.Lookup(L"Char16")));

            // Boolean true
            values.Insert(L"BoolTrue", winrt::box_value(true));
            VERIFY_IS_TRUE(winrt::unbox_value<bool>(values.Lookup(L"BoolTrue")));

            // Boolean false
            values.Insert(L"BoolFalse", winrt::box_value(false));
            VERIFY_IS_FALSE(winrt::unbox_value<bool>(values.Lookup(L"BoolFalse")));

            // DateTime
            const winrt::Windows::Foundation::DateTime dateTime{ winrt::Windows::Foundation::TimeSpan{ 132800000000000000LL } };
            values.Insert(L"DateTime", winrt::box_value(dateTime));
            auto readDateTime{ winrt::unbox_value<winrt::Windows::Foundation::DateTime>(values.Lookup(L"DateTime")) };
            VERIFY_ARE_EQUAL(dateTime.time_since_epoch().count(), readDateTime.time_since_epoch().count());

            // TimeSpan
            const winrt::Windows::Foundation::TimeSpan timeSpan{ 36000000000LL }; // 1 hour in 100ns ticks
            values.Insert(L"TimeSpan", winrt::box_value(timeSpan));
            auto readTimeSpan{ winrt::unbox_value<winrt::Windows::Foundation::TimeSpan>(values.Lookup(L"TimeSpan")) };
            VERIFY_ARE_EQUAL(timeSpan.count(), readTimeSpan.count());

            // Guid
            const winrt::guid testGuid{ 0x01020304, 0x0506, 0x0708, { 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10 } };
            values.Insert(L"Guid", winrt::box_value(testGuid));
            VERIFY_ARE_EQUAL(testGuid, winrt::unbox_value<winrt::guid>(values.Lookup(L"Guid")));

            // Point
            const winrt::Windows::Foundation::Point point{ 1.5f, 2.5f };
            values.Insert(L"Point", winrt::box_value(point));
            auto readPoint{ winrt::unbox_value<winrt::Windows::Foundation::Point>(values.Lookup(L"Point")) };
            VERIFY_ARE_EQUAL(point.X, readPoint.X);
            VERIFY_ARE_EQUAL(point.Y, readPoint.Y);

            // Size
            const winrt::Windows::Foundation::Size size{ 100.0f, 200.0f };
            values.Insert(L"Size", winrt::box_value(size));
            auto readSize{ winrt::unbox_value<winrt::Windows::Foundation::Size>(values.Lookup(L"Size")) };
            VERIFY_ARE_EQUAL(size.Width, readSize.Width);
            VERIFY_ARE_EQUAL(size.Height, readSize.Height);

            // Rect
            const winrt::Windows::Foundation::Rect rect{ 10.0f, 20.0f, 300.0f, 400.0f };
            values.Insert(L"Rect", winrt::box_value(rect));
            auto readRect{ winrt::unbox_value<winrt::Windows::Foundation::Rect>(values.Lookup(L"Rect")) };
            VERIFY_ARE_EQUAL(rect.X, readRect.X);
            VERIFY_ARE_EQUAL(rect.Y, readRect.Y);
            VERIFY_ARE_EQUAL(rect.Width, readRect.Width);
            VERIFY_ARE_EQUAL(rect.Height, readRect.Height);

            // Overwrite a value
            values.Insert(L"String", winrt::box_value(L"Updated"));
            VERIFY_ARE_EQUAL(L"Updated", winrt::unbox_value<winrt::hstring>(values.Lookup(L"String")));

            // Verify count
            VERIFY_ARE_EQUAL(20u, values.Size());

            values.Clear();
        }

        TEST_METHOD(Values_ArrayTypes)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(L"TestApplicationData_Contoso", L"SupermarketPointOfSale") };
            auto localSettings{ applicationData.LocalSettings() };
            auto values{ localSettings.Values() };
            values.Clear();

            using PV = winrt::Windows::Foundation::PropertyValue;
            namespace WF = winrt::Windows::Foundation;

            // UInt8Array
            {
                // An initializer list like: { 1, 2, 3, 255 } is always an initializer_list<int> unless told otherwise.
                // winrt::com_array<T> has a templated constructor that accepts iterators / initializer lists, so the compiler happily
                // tries to copy int values into T, and then quite correctly warns you that: “I am truncating integers into smaller
                // integer types. I hope you meant that.” Better to make the initializer list elements match the array element type.
                std::array<uint8_t, 4> arrValues{ 1, 2, 3, 255 };
                winrt::com_array<uint8_t> arr(arrValues.begin(), arrValues.end());
                values.Insert(L"UInt8Array", PV::CreateUInt8Array(arr));
                auto pv{ values.Lookup(L"UInt8Array").as<WF::IPropertyValue>() };
                winrt::com_array<uint8_t> result;
                pv.GetUInt8Array(result);
                VERIFY_ARE_EQUAL(4u, result.size());
                VERIFY_ARE_EQUAL(static_cast<uint8_t>(1), result[0]);
                VERIFY_ARE_EQUAL(static_cast<uint8_t>(255), result[3]);
            }

            // Int16Array
            {
                // An initializer list like: { 1, 2, 3, 255 } is always an initializer_list<int> unless told otherwise.
                // winrt::com_array<T> has a templated constructor that accepts iterators / initializer lists, so the compiler happily
                // tries to copy int values into T, and then quite correctly warns you that: “I am truncating integers into smaller
                // integer types. I hope you meant that.” Better to make the initializer list elements match the array element type.
                std::array<int16_t, 4> arrValues{ -32768, 0, 32767 };
                winrt::com_array<int16_t> arr(arrValues.begin(), arrValues.end());
                values.Insert(L"Int16Array", PV::CreateInt16Array(arr));
                auto pv{ values.Lookup(L"Int16Array").as<WF::IPropertyValue>() };
                winrt::com_array<int16_t> result;
                pv.GetInt16Array(result);
                VERIFY_ARE_EQUAL(3u, result.size());
                VERIFY_ARE_EQUAL(static_cast<int16_t>(-32768), result[0]);
                VERIFY_ARE_EQUAL(static_cast<int16_t>(32767), result[2]);
            }

            // UInt16Array
            {
                // An initializer list like: { 1, 2, 3, 255 } is always an initializer_list<int> unless told otherwise.
                // winrt::com_array<T> has a templated constructor that accepts iterators / initializer lists, so the compiler happily
                // tries to copy int values into T, and then quite correctly warns you that: “I am truncating integers into smaller
                // integer types. I hope you meant that.” Better to make the initializer list elements match the array element type.
                std::array<uint16_t, 4> arrValues{ 0, 1000, 65535 };
                winrt::com_array<uint16_t> arr(arrValues.begin(), arrValues.end());
                values.Insert(L"UInt16Array", PV::CreateUInt16Array(arr));
                auto pv{ values.Lookup(L"UInt16Array").as<WF::IPropertyValue>() };
                winrt::com_array<uint16_t> result;
                pv.GetUInt16Array(result);
                VERIFY_ARE_EQUAL(3u, result.size());
                VERIFY_ARE_EQUAL(static_cast<uint16_t>(0), result[0]);
                VERIFY_ARE_EQUAL(static_cast<uint16_t>(65535), result[2]);
            }

            // Int32Array
            {
                winrt::com_array<int32_t> arr{ -2147483647 - 1, 0, 2147483647 };
                values.Insert(L"Int32Array", PV::CreateInt32Array(arr));
                auto pv{ values.Lookup(L"Int32Array").as<WF::IPropertyValue>() };
                winrt::com_array<int32_t> result;
                pv.GetInt32Array(result);
                VERIFY_ARE_EQUAL(3u, result.size());
                VERIFY_ARE_EQUAL(static_cast<int32_t>(-2147483647 - 1), result[0]);
                VERIFY_ARE_EQUAL(static_cast<int32_t>(2147483647), result[2]);
            }

            // UInt32Array
            {
                winrt::com_array<uint32_t> arr{ 0u, 1000000u, 4294967295u };
                values.Insert(L"UInt32Array", PV::CreateUInt32Array(arr));
                auto pv{ values.Lookup(L"UInt32Array").as<WF::IPropertyValue>() };
                winrt::com_array<uint32_t> result;
                pv.GetUInt32Array(result);
                VERIFY_ARE_EQUAL(3u, result.size());
                VERIFY_ARE_EQUAL(0u, result[0]);
                VERIFY_ARE_EQUAL(4294967295u, result[2]);
            }

            // Int64Array
            {
                winrt::com_array<int64_t> arr{ -9223372036854775807LL - 1, 0LL, 9223372036854775807LL };
                values.Insert(L"Int64Array", PV::CreateInt64Array(arr));
                auto pv{ values.Lookup(L"Int64Array").as<WF::IPropertyValue>() };
                winrt::com_array<int64_t> result;
                pv.GetInt64Array(result);
                VERIFY_ARE_EQUAL(3u, result.size());
                VERIFY_ARE_EQUAL(static_cast<int64_t>(-9223372036854775807LL - 1), result[0]);
                VERIFY_ARE_EQUAL(static_cast<int64_t>(9223372036854775807LL), result[2]);
            }

            // UInt64Array
            {
                winrt::com_array<uint64_t> arr{ 0ULL, 18446744073709551615ULL };
                values.Insert(L"UInt64Array", PV::CreateUInt64Array(arr));
                auto pv{ values.Lookup(L"UInt64Array").as<WF::IPropertyValue>() };
                winrt::com_array<uint64_t> result;
                pv.GetUInt64Array(result);
                VERIFY_ARE_EQUAL(2u, result.size());
                VERIFY_ARE_EQUAL(0ULL, result[0]);
                VERIFY_ARE_EQUAL(18446744073709551615ULL, result[1]);
            }

            // SingleArray
            {
                winrt::com_array<float> arr{ 1.1f, 2.2f, 3.3f };
                values.Insert(L"SingleArray", PV::CreateSingleArray(arr));
                auto pv{ values.Lookup(L"SingleArray").as<WF::IPropertyValue>() };
                winrt::com_array<float> result;
                pv.GetSingleArray(result);
                VERIFY_ARE_EQUAL(3u, result.size());
                VERIFY_ARE_EQUAL(1.1f, result[0]);
                VERIFY_ARE_EQUAL(3.3f, result[2]);
            }

            // DoubleArray
            {
                winrt::com_array<double> arr{ 1.11, 2.22 };
                values.Insert(L"DoubleArray", PV::CreateDoubleArray(arr));
                auto pv{ values.Lookup(L"DoubleArray").as<WF::IPropertyValue>() };
                winrt::com_array<double> result;
                pv.GetDoubleArray(result);
                VERIFY_ARE_EQUAL(2u, result.size());
                VERIFY_ARE_EQUAL(1.11, result[0]);
                VERIFY_ARE_EQUAL(2.22, result[1]);
            }

            // Char16Array
            {
                winrt::com_array<char16_t> arr{ L'A', L'B', L'\x4e16' };
                values.Insert(L"Char16Array", PV::CreateChar16Array(arr));
                auto pv{ values.Lookup(L"Char16Array").as<WF::IPropertyValue>() };
                winrt::com_array<char16_t> result;
                pv.GetChar16Array(result);
                VERIFY_ARE_EQUAL(3u, result.size());
                VERIFY_ARE_EQUAL(L'A', result[0]);
                VERIFY_ARE_EQUAL(L'\x4e16', result[2]);
            }

            // BooleanArray
            {
                winrt::com_array<bool> arr{ true, false, true, false };
                values.Insert(L"BooleanArray", PV::CreateBooleanArray(arr));
                auto pv{ values.Lookup(L"BooleanArray").as<WF::IPropertyValue>() };
                winrt::com_array<bool> result;
                pv.GetBooleanArray(result);
                VERIFY_ARE_EQUAL(4u, result.size());
                VERIFY_IS_TRUE(result[0]);
                VERIFY_IS_FALSE(result[1]);
                VERIFY_IS_TRUE(result[2]);
                VERIFY_IS_FALSE(result[3]);
            }

            // StringArray
            {
                winrt::com_array<winrt::hstring> arr{ winrt::hstring{L"Alpha"}, winrt::hstring{L"Beta"}, winrt::hstring{L"Gamma"} };
                values.Insert(L"StringArray", PV::CreateStringArray(arr));
                auto pv{ values.Lookup(L"StringArray").as<WF::IPropertyValue>() };
                winrt::com_array<winrt::hstring> result;
                pv.GetStringArray(result);
                VERIFY_ARE_EQUAL(3u, result.size());
                VERIFY_ARE_EQUAL(winrt::hstring{L"Alpha"}, result[0]);
                VERIFY_ARE_EQUAL(winrt::hstring{L"Beta"}, result[1]);
                VERIFY_ARE_EQUAL(winrt::hstring{L"Gamma"}, result[2]);
            }

            // DateTimeArray
            {
                WF::DateTime dt1{ WF::TimeSpan{ 100000000LL } };
                WF::DateTime dt2{ WF::TimeSpan{ 200000000LL } };
                winrt::com_array<WF::DateTime> arr{ dt1, dt2 };
                values.Insert(L"DateTimeArray", PV::CreateDateTimeArray(arr));
                auto pv{ values.Lookup(L"DateTimeArray").as<WF::IPropertyValue>() };
                winrt::com_array<WF::DateTime> result;
                pv.GetDateTimeArray(result);
                VERIFY_ARE_EQUAL(2u, result.size());
                VERIFY_ARE_EQUAL(dt1.time_since_epoch().count(), result[0].time_since_epoch().count());
                VERIFY_ARE_EQUAL(dt2.time_since_epoch().count(), result[1].time_since_epoch().count());
            }

            // TimeSpanArray
            {
                WF::TimeSpan ts1{ 10000000LL };  // 1 second
                WF::TimeSpan ts2{ 600000000LL }; // 1 minute
                winrt::com_array<WF::TimeSpan> arr{ ts1, ts2 };
                values.Insert(L"TimeSpanArray", PV::CreateTimeSpanArray(arr));
                auto pv{ values.Lookup(L"TimeSpanArray").as<WF::IPropertyValue>() };
                winrt::com_array<WF::TimeSpan> result;
                pv.GetTimeSpanArray(result);
                VERIFY_ARE_EQUAL(2u, result.size());
                VERIFY_ARE_EQUAL(ts1.count(), result[0].count());
                VERIFY_ARE_EQUAL(ts2.count(), result[1].count());
            }

            // GuidArray
            {
                winrt::guid g1{ 0x11111111, 0x2222, 0x3333, { 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB } };
                winrt::guid g2{ 0xAAAAAAAA, 0xBBBB, 0xCCCC, { 0xDD, 0xEE, 0xFF, 0x00, 0x11, 0x22, 0x33, 0x44 } };
                winrt::com_array<winrt::guid> arr{ g1, g2 };
                values.Insert(L"GuidArray", PV::CreateGuidArray(arr));
                auto pv{ values.Lookup(L"GuidArray").as<WF::IPropertyValue>() };
                winrt::com_array<winrt::guid> result;
                pv.GetGuidArray(result);
                VERIFY_ARE_EQUAL(2u, result.size());
                VERIFY_ARE_EQUAL(g1, result[0]);
                VERIFY_ARE_EQUAL(g2, result[1]);
            }

            // PointArray
            {
                WF::Point p1{ 1.0f, 2.0f };
                WF::Point p2{ 3.0f, 4.0f };
                winrt::com_array<WF::Point> arr{ p1, p2 };
                values.Insert(L"PointArray", PV::CreatePointArray(arr));
                auto pv{ values.Lookup(L"PointArray").as<WF::IPropertyValue>() };
                winrt::com_array<WF::Point> result;
                pv.GetPointArray(result);
                VERIFY_ARE_EQUAL(2u, result.size());
                VERIFY_ARE_EQUAL(p1.X, result[0].X);
                VERIFY_ARE_EQUAL(p1.Y, result[0].Y);
                VERIFY_ARE_EQUAL(p2.X, result[1].X);
                VERIFY_ARE_EQUAL(p2.Y, result[1].Y);
            }

            // SizeArray
            {
                WF::Size s1{ 10.0f, 20.0f };
                WF::Size s2{ 30.0f, 40.0f };
                winrt::com_array<WF::Size> arr{ s1, s2 };
                values.Insert(L"SizeArray", PV::CreateSizeArray(arr));
                auto pv{ values.Lookup(L"SizeArray").as<WF::IPropertyValue>() };
                winrt::com_array<WF::Size> result;
                pv.GetSizeArray(result);
                VERIFY_ARE_EQUAL(2u, result.size());
                VERIFY_ARE_EQUAL(s1.Width, result[0].Width);
                VERIFY_ARE_EQUAL(s1.Height, result[0].Height);
                VERIFY_ARE_EQUAL(s2.Width, result[1].Width);
                VERIFY_ARE_EQUAL(s2.Height, result[1].Height);
            }

            // RectArray
            {
                WF::Rect r1{ 1.0f, 2.0f, 3.0f, 4.0f };
                WF::Rect r2{ 5.0f, 6.0f, 7.0f, 8.0f };
                winrt::com_array<WF::Rect> arr{ r1, r2 };
                values.Insert(L"RectArray", PV::CreateRectArray(arr));
                auto pv{ values.Lookup(L"RectArray").as<WF::IPropertyValue>() };
                winrt::com_array<WF::Rect> result;
                pv.GetRectArray(result);
                VERIFY_ARE_EQUAL(2u, result.size());
                VERIFY_ARE_EQUAL(r1.X, result[0].X);
                VERIFY_ARE_EQUAL(r1.Y, result[0].Y);
                VERIFY_ARE_EQUAL(r1.Width, result[0].Width);
                VERIFY_ARE_EQUAL(r1.Height, result[0].Height);
                VERIFY_ARE_EQUAL(r2.X, result[1].X);
                VERIFY_ARE_EQUAL(r2.Y, result[1].Y);
                VERIFY_ARE_EQUAL(r2.Width, result[1].Width);
                VERIFY_ARE_EQUAL(r2.Height, result[1].Height);
            }

            values.Clear();
        }

        TEST_METHOD(Values_PropertySetOperations)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(L"TestApplicationData_Contoso", L"SupermarketPointOfSale") };
            auto localSettings{ applicationData.LocalSettings() };
            auto values{ localSettings.Values() };
            values.Clear();

            // Insert and Size
            VERIFY_ARE_EQUAL(0u, values.Size());
            auto inserted{ values.Insert(L"Key1", winrt::box_value(L"Value1")) };
            VERIFY_IS_FALSE(inserted); // Insert returns true if key existed (replaced)
            VERIFY_ARE_EQUAL(1u, values.Size());

            values.Insert(L"Key2", winrt::box_value(static_cast<uint32_t>(42)));
            VERIFY_ARE_EQUAL(2u, values.Size());

            // Replace existing key
            inserted = values.Insert(L"Key1", winrt::box_value(L"Updated"));
            VERIFY_IS_TRUE(inserted); // Key existed, so replaced
            VERIFY_ARE_EQUAL(2u, values.Size());
            VERIFY_ARE_EQUAL(L"Updated", winrt::unbox_value<winrt::hstring>(values.Lookup(L"Key1")));

            // HasKey
            VERIFY_IS_TRUE(values.HasKey(L"Key1"));
            VERIFY_IS_TRUE(values.HasKey(L"Key2"));
            VERIFY_IS_FALSE(values.HasKey(L"NonExistent"));

            // Lookup
            auto val1{ values.Lookup(L"Key1") };
            VERIFY_IS_NOT_NULL(val1);
            auto val2{ values.Lookup(L"Key2") };
            VERIFY_IS_NOT_NULL(val2);
            VERIFY_ARE_EQUAL(static_cast<uint32_t>(42), winrt::unbox_value<uint32_t>(val2));

            // Remove
            values.Remove(L"Key2");
            VERIFY_ARE_EQUAL(1u, values.Size());
            VERIFY_IS_FALSE(values.HasKey(L"Key2"));
            VERIFY_IS_TRUE(values.HasKey(L"Key1"));

            // GetView
            values.Insert(L"ViewKey", winrt::box_value(L"ViewValue"));
            auto view{ values.GetView() };
            VERIFY_ARE_EQUAL(2u, view.Size());
            VERIFY_IS_TRUE(view.HasKey(L"Key1"));
            VERIFY_IS_TRUE(view.HasKey(L"ViewKey"));

            // First / iteration
            auto iter{ values.First() };
            VERIFY_IS_TRUE(iter.HasCurrent());
            uint32_t iterCount{ 0 };
            while (iter.HasCurrent())
            {
                auto kvp{ iter.Current() };
                VERIFY_IS_TRUE(values.HasKey(kvp.Key()));
                ++iterCount;
                iter.MoveNext();
            }
            VERIFY_ARE_EQUAL(2u, iterCount);

            // Clear
            values.Clear();
            VERIFY_ARE_EQUAL(0u, values.Size());
            VERIFY_IS_FALSE(values.HasKey(L"Key1"));
            VERIFY_IS_FALSE(values.HasKey(L"ViewKey"));
        }

        TEST_METHOD(Values_MapChangedEvent)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(L"TestApplicationData_Contoso", L"SupermarketPointOfSale") };
            auto localSettings{ applicationData.LocalSettings() };
            auto values{ localSettings.Values() };
            values.Clear();

            auto observableMap{ values.as<winrt::Windows::Foundation::Collections::IObservableMap<winrt::hstring, winrt::Windows::Foundation::IInspectable>>() };
            VERIFY_IS_NOT_NULL(observableMap);

            winrt::Windows::Foundation::Collections::CollectionChange lastChange{};
            winrt::hstring lastKey;
            int callCount{ 0 };

            auto token{ observableMap.MapChanged([&](auto const&, auto const& args)
            {
                lastChange = args.CollectionChange();
                lastKey = args.Key();
                ++callCount;
            }) };

            // Insert fires ItemInserted
            values.Insert(L"EventKey", winrt::box_value(L"EventValue"));
            VERIFY_ARE_EQUAL(1, callCount);
            VERIFY_ARE_EQUAL(winrt::Windows::Foundation::Collections::CollectionChange::ItemInserted, lastChange);
            VERIFY_ARE_EQUAL(L"EventKey", lastKey);

            // Replace fires ItemChanged
            values.Insert(L"EventKey", winrt::box_value(L"UpdatedValue"));
            VERIFY_ARE_EQUAL(2, callCount);
            VERIFY_ARE_EQUAL(winrt::Windows::Foundation::Collections::CollectionChange::ItemChanged, lastChange);
            VERIFY_ARE_EQUAL(L"EventKey", lastKey);

            // Remove fires ItemRemoved
            values.Remove(L"EventKey");
            VERIFY_ARE_EQUAL(3, callCount);
            VERIFY_ARE_EQUAL(winrt::Windows::Foundation::Collections::CollectionChange::ItemRemoved, lastChange);
            VERIFY_ARE_EQUAL(L"EventKey", lastKey);

            // Clear fires Reset
            values.Insert(L"A", winrt::box_value(L"1"));
            values.Insert(L"B", winrt::box_value(L"2"));
            callCount = 0;
            values.Clear();
            VERIFY_ARE_EQUAL(1, callCount);
            VERIFY_ARE_EQUAL(winrt::Windows::Foundation::Collections::CollectionChange::Reset, lastChange);

            // Unregister event
            observableMap.MapChanged(token);
            values.Insert(L"NoEvent", winrt::box_value(L"NoEvent"));
            VERIFY_ARE_EQUAL(1, callCount); // Should not have changed
            values.Clear();
        }

        TEST_METHOD(Close_ThrowsAfterClose)
        {
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForUnpackaged(L"TestApplicationData_Contoso", L"SupermarketPointOfSale") };
            auto localSettings{ applicationData.LocalSettings() };

            // Create a child container to test Close on
            auto child{ localSettings.CreateContainer(L"CloseTest", winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition::Always) };
            VERIFY_IS_NOT_NULL(child);
            VERIFY_ARE_EQUAL(L"CloseTest", child.Name());
            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Local, child.Locality());

            child.Close();

            // After Close, all member accesses should throw RO_E_CLOSED
            try
            {
                [[maybe_unused]] auto name{ child.Name() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                [[maybe_unused]] auto locality{ child.Locality() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                [[maybe_unused]] auto vals{ child.Values() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                [[maybe_unused]] auto containers{ child.Containers() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                child.CreateContainer(L"Sub", winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition::Always);
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            try
            {
                child.DeleteContainer(L"Sub");
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            // Cleanup
            localSettings.DeleteContainer(L"CloseTest");
        }
    };
}
