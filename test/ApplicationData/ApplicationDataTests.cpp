// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

static const winrt::hstring null_hstring;

namespace WEX::TestExecution
{
    // Teach TAEF how to format a winrt::hstring
    template <>
    class VerifyOutputTraits<winrt::hstring>
    {
    public:
        static WEX::Common::NoThrowString ToString(winrt::hstring const& value)
        {
            const auto s{ value.c_str() };
            if (!s)
            {
                return WEX::Common::NoThrowString(L"nullptr");
            }
            else
            {
                return WEX::Common::NoThrowString().Format(L"\"%s\"", s);
            }
        }
    };

    // Teach TAEF how to compare a winrt::hstring
    template <>
    class VerifyCompareTraits<winrt::hstring, winrt::hstring>
    {
    public:
        static bool AreEqual(winrt::hstring const& expected, winrt::hstring const& actual)
        {
            return Compare(expected, actual) == 0;
        }

        static bool AreSame(winrt::hstring const& expected, winrt::hstring const& actual)
        {
            return &expected == &actual;
        }

        static bool IsLessThan(winrt::hstring const& expectedLess, winrt::hstring const& expectedGreater)
        {
            return Compare(expectedLess, expectedGreater) < 0;
        }

        static bool IsGreaterThan(winrt::hstring const& expectedGreater, winrt::hstring const& expectedLess)
        {
            return Compare(expectedGreater, expectedLess) > 0;
        }

        static bool IsNull(winrt::hstring const& object)
        {
            return object.c_str() == nullptr;
        }
    private:
        static int Compare(winrt::hstring const& left, winrt::hstring const& right)
        {
            if (left == right)
            {
                return 0;
            }
            else if (left.c_str() == nullptr)
            {
                return -1;
            }
            else if (right.c_str() == nullptr)
            {
                return 1;
            }
            else
            {
                return CompareStringOrdinal(left .c_str(), -1, right.c_str(), -1, FALSE) - CSTR_EQUAL;
            }
        }
    };
}

namespace Test::PackageManager::Tests
{
    const auto Main_PackageFamilyName{ ::TP::DynamicDependencyDataStore::c_PackageFamilyName };
    const auto Framework_PackageFamilyName{ ::TP::WindowsAppRuntimeFramework::c_PackageFamilyName };

    std::filesystem::path GetExpectedMachinePath(winrt::hstring const& packageFamilyName)
    {
        // Expected Path = HKLM\...apprepository...\ApplicationData\...pkgfamilyname...\Machine
        // This is typically %ProgramData%\Microsoft\Windows\AppRepository\ApplicationData\...pkgfamilyname...\Machine
        // and by 'typically' we mean 'all current Windows editions' so we'll assume it's true for ease of testing
        // and use this test as a canary to detect if/when this is ever not true on any supported platform.
        wil::unique_cotaskmem_string path;
        THROW_IF_FAILED(::SHGetKnownFolderPath(FOLDERID_ProgramData, 0, nullptr, wil::out_param(path)));
        const std::filesystem::path programData{ path.get() };
        const auto packageRepositoryRoot{ programData / L"Microsoft\\Windows\\AppRepository\\ApplicationData" };
        const auto packageFamilyRoot{ packageRepositoryRoot / packageFamilyName.c_str() };
        const auto expectedMachinePath{ packageFamilyRoot / L"Machine" };
        return expectedMachinePath;
    }

    class ApplicationDataTests
    {
    public:
        BEGIN_TEST_CLASS(ApplicationDataTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!::WindowsVersion::IsWindows11_21H2OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageDeploymentManager requires Win11 >= 21H2 (SV1). Skipping tests");
                return true;
            }
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

            const auto roamingFolder{ applicationData.RoamingFolder() };
            const auto roamingPath{ applicationData.RoamingPath() };
            VERIFY_ARE_EQUAL(roamingFolder.Path(), roamingPath);
            const auto expectedRoamingFolder{ systemApplicationData.RoamingFolder() };
            const auto expectedRoamingPath{ expectedRoamingFolder.Path() };
            VERIFY_ARE_EQUAL(roamingPath, expectedRoamingPath);

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
            const auto roamingFolder{ applicationData.RoamingFolder() };
            VERIFY_IS_NULL(roamingFolder);
            const auto roamingPath{ applicationData.RoamingPath() };
            VERIFY_ARE_EQUAL(roamingPath, null_hstring);
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
                auto locality{ container.Locality() };
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
                auto locality{ systemContainer.Locality() };
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
                auto locality{ localSettings.Locality() };
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
                auto locality{ systemLocalSettings.Locality() };
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

        TEST_METHOD(RoamingSettings_Main)
        {
            winrt::hstring packageFamilyName{ Main_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            auto systemApplicationData{ winrt::Windows::Management::Core::ApplicationDataManager::CreateForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(systemApplicationData);

            const auto roamingSettings{ applicationData.RoamingSettings() };
            const auto systemRoamingSettings{ systemApplicationData.RoamingSettings() };
            VERIFY_ARE_EQUAL(static_cast<int32_t>(roamingSettings.Locality()), static_cast<int32_t>(systemRoamingSettings.Locality()));

            auto containers{ roamingSettings.Containers() };
            VERIFY_ARE_EQUAL(0u, containers.Size());
            auto systemContainers{ systemRoamingSettings.Containers() };
            VERIFY_ARE_EQUAL(0u, systemContainers.Size());
            VERIFY_ARE_EQUAL(containers.Size(), systemContainers.Size());

            const winrt::hstring foodAndStuff{ L"FoodAndStuff" };
            VERIFY_IS_FALSE(containers.HasKey(foodAndStuff));
            VERIFY_IS_FALSE(systemContainers.HasKey(foodAndStuff));

            auto container{ roamingSettings.CreateContainer(foodAndStuff, winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition::Always) };
            VERIFY_ARE_EQUAL(foodAndStuff, container.Name());
            //
            VERIFY_ARE_EQUAL(0u, containers.Size());
            VERIFY_IS_FALSE(containers.HasKey(foodAndStuff));
            containers = roamingSettings.Containers();
            VERIFY_ARE_EQUAL(1u, containers.Size());
            VERIFY_IS_TRUE(containers.HasKey(foodAndStuff));
            container = containers.Lookup(foodAndStuff);
            VERIFY_IS_NOT_NULL(container);
            VERIFY_ARE_EQUAL(foodAndStuff, container.Name());
            //
            VERIFY_ARE_EQUAL(0u, systemContainers.Size());
            VERIFY_IS_FALSE(systemContainers.HasKey(foodAndStuff));
            systemContainers = systemRoamingSettings.Containers();
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

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Roaming, container.Locality());
            container.Close();
            try
            {
                auto roamingity{ container.Locality() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
            VERIFY_ARE_EQUAL(winrt::Windows::Storage::ApplicationDataLocality::Roaming, systemContainer.Locality());
            systemContainer.Close();
            try
            {
                auto roamingity{ systemContainer.Locality() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }

            VERIFY_ARE_EQUAL(1u, roamingSettings.Containers().Size());
            VERIFY_ARE_EQUAL(1u, systemRoamingSettings.Containers().Size());
            roamingSettings.DeleteContainer(foodAndStuff);
            VERIFY_ARE_EQUAL(0u, roamingSettings.Containers().Size());
            VERIFY_ARE_EQUAL(0u, systemRoamingSettings.Containers().Size());

            VERIFY_ARE_EQUAL(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Roaming, roamingSettings.Locality());
            roamingSettings.Close();
            try
            {
                auto roamingity{ roamingSettings.Locality() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
            VERIFY_ARE_EQUAL(winrt::Windows::Storage::ApplicationDataLocality::Roaming, systemRoamingSettings.Locality());
            systemRoamingSettings.Close();
            try
            {
                auto roamingity{ systemRoamingSettings.Locality() };
                VERIFY_FAIL(L"Success is not expected");
            }
            catch (winrt::hresult_error& e)
            {
                VERIFY_ARE_EQUAL(RO_E_CLOSED, e.code(), WEX::Common::String().Format(L"0x%X %s", e.code(), e.message().c_str()));
            }
        }

        TEST_METHOD(RoamingSettings_Framework)
        {
            winrt::hstring packageFamilyName{ Framework_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);
            const auto roamingSettings{ applicationData.RoamingSettings() };
            VERIFY_IS_NULL(roamingSettings);

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

        TEST_METHOD(ClearAllAsync_Main)
        {
            //TODO
        }

        TEST_METHOD(ClearAllAsync_Framework)
        {
            //TODO
        }

        TEST_METHOD(ClearAsync_Main)
        {
            //TODO
        }

        TEST_METHOD(ClearAsync_Framework)
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

        TEST_METHOD(ClearMachineFolderAsync_Main)
        {
            //TODO
        }

        TEST_METHOD(ClearMachineFolderAsync_Framework)
        {
            //TODO
        }
    };


    class ApplicationDataTests_Elevated
    {
    public:
        BEGIN_TEST_CLASS(ApplicationDataTests_Elevated)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"RunAs", L"RestrictedUser")
            TEST_CLASS_PROPERTY(L"RunFixtureAs", L"RestrictedUser")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!::WindowsVersion::IsWindows11_21H2OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageDeploymentManager requires Win11 >= 21H2 (SV1). Skipping tests");
                return true;
            }
            ::TB::Setup();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            ::TB::Cleanup();
            return true;
        }

        static void CreateMachinePathIfNecessary(PCWSTR packageFamilyName)
        {
            const auto expectedMachinePath{ GetExpectedMachinePath(packageFamilyName) };
            const std::filesystem::path path{ expectedMachinePath.c_str() };
            VERIFY_ARE_EQUAL(path.filename(), L"Machine");
            if (std::filesystem::exists(path))
            {
                WEX::Logging::Log::Comment(WEX::Common::String().Format(L"MachinePath exists: %s", path.c_str()));
            }
            else
            {
                WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Creating MachinePath: %s", path.c_str()));
                wil::CreateDirectoryDeep(path.c_str());
            }
        }

        static void RemoveMachinePathIfNecessary(PCWSTR packageFamilyName)
        {
            const auto expectedMachinePath{ GetExpectedMachinePath(packageFamilyName) };
            const std::filesystem::path path{ expectedMachinePath.c_str() };
            VERIFY_ARE_EQUAL(path.filename(), L"Machine");
            const auto packageFamilyPath{ path.parent_path() };
            if (std::filesystem::exists(packageFamilyPath))
            {
                WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Removing MachinePath's PackageFamily: %s", packageFamilyPath.c_str()));
                wil::RemoveDirectoryRecursive(packageFamilyPath.c_str(), wil::RemoveDirectoryOptions::RemoveReadOnly);
            }
            else
            {
                WEX::Logging::Log::Comment(WEX::Common::String().Format(L"MachinePath's PackageFamily does not exist: %s", packageFamilyPath.c_str()));
            }
        }

        TEST_METHOD(CreateMachinePathIfNecessary_Framework)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"System")
            END_TEST_METHOD_PROPERTIES()

            const auto packageFamilyName{ Framework_PackageFamilyName };
            CreateMachinePathIfNecessary(packageFamilyName);
        }

        TEST_METHOD(CreateMachinePathIfNecessary_Main)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"System")
            END_TEST_METHOD_PROPERTIES()

            const auto packageFamilyName{ Main_PackageFamilyName };
            CreateMachinePathIfNecessary(packageFamilyName);
        }

        TEST_METHOD(MachineFolderAndPath_Main_Supported)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"RestrictedUser")
            END_TEST_METHOD_PROPERTIES()

            winrt::hstring packageFamilyName{ Main_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            VERIFY_IS_TRUE(applicationData.IsMachinePathSupported());

            const auto machineFolder{ applicationData.MachineFolder() };
            VERIFY_IS_NOT_NULL(machineFolder);
            const auto machinePath{ applicationData.MachinePath() };
            VERIFY_ARE_EQUAL(machineFolder.Path(), machinePath);

            const auto expectedMachinePath{ GetExpectedMachinePath(packageFamilyName) };
            VERIFY_ARE_EQUAL(machinePath, winrt::hstring(expectedMachinePath.c_str()));
        }

        TEST_METHOD(MachineFolderAndPath_Framework_Supported)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"RestrictedUser")
            END_TEST_METHOD_PROPERTIES()

            winrt::hstring packageFamilyName{ Framework_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            VERIFY_IS_TRUE(applicationData.IsMachinePathSupported());

            const auto machineFolder{ applicationData.MachineFolder() };
            VERIFY_IS_NOT_NULL(machineFolder);
            const auto machinePath{ applicationData.MachinePath() };
            VERIFY_ARE_EQUAL(machineFolder.Path(), machinePath);

            const auto expectedMachinePath{ GetExpectedMachinePath(packageFamilyName) };
            VERIFY_ARE_EQUAL(machinePath, winrt::hstring(expectedMachinePath.c_str()));
        }

        TEST_METHOD(RemoveMachinePathIfNecessary_Main)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"System")
            END_TEST_METHOD_PROPERTIES()

            const auto packageFamilyName{ Main_PackageFamilyName };
            RemoveMachinePathIfNecessary(packageFamilyName);
        }

        TEST_METHOD(RemoveMachinePathIfNecessary_Framework)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"RunAs", L"System")
            END_TEST_METHOD_PROPERTIES()

            const auto packageFamilyName{ Framework_PackageFamilyName };
            RemoveMachinePathIfNecessary(packageFamilyName);
        }
    };
}
