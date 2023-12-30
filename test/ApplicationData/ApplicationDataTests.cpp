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

        std::filesystem::path GetExpectedMachinePath(winrt::hstring const& packageFamilyName)
        {
            // Expected Path = HKLM\...apprepository...\ApplicationData\...pkgfamilyname...\Machine
            // This is typically %ProgramData%\Microsoft\Windows\AppRepository\ApplicationData\...pkgfamilyname...\Machine
            // and by 'typically' we mean 'all current Windows editions' so we'll assume it's true for ease of testing
            // and use this test as a canary to detect if/when this is ever not true on any supported platform.
            const auto appDataPaths{ winrt::Windows::Storage::AppDataPaths::GetDefault() };
            const std::filesystem::path programData{ appDataPaths.ProgramData().c_str() };
            const auto packageRepositoryRoot{ programData / L"Microsoft\\Windows\\AppRepository\\ApplicationData" };
            const auto packageFamilyRoot{ packageRepositoryRoot / packageFamilyName.c_str() };
            const auto expectedMachinePath{ packageFamilyRoot / L"Machine" };
            return expectedMachinePath;
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

            const auto expectedMachinePath{ GetExpectedMachinePath(packageFamilyName) };
            VERIFY_ARE_EQUAL(machinePath, winrt::hstring(expectedMachinePath.c_str()));
        }

        TEST_METHOD(MachineFolderAndPath_Framework_NotSupported)
        {
            winrt::hstring packageFamilyName{ Framework_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            VERIFY_IS_TRUE(applicationData.IsMachinePathSupported());

            const auto machineFolder{ applicationData.MachineFolder() };
            const auto machinePath{ applicationData.MachinePath() };
            VERIFY_ARE_EQUAL(machineFolder.Path(), machinePath);

            const auto expectedMachinePath{ GetExpectedMachinePath(packageFamilyName) };
            VERIFY_ARE_EQUAL(machinePath, winrt::hstring(expectedMachinePath.c_str()));
        }

        TEST_METHOD(MachineFolderAndPath_Main_Supported)
        {
            winrt::hstring packageFamilyName{ Main_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            const auto machineFolder{ applicationData.MachineFolder() };
            const auto machinePath{ applicationData.MachinePath() };
            VERIFY_ARE_EQUAL(machineFolder.Path(), machinePath);

            const auto expectedMachinePath{ GetExpectedMachinePath(packageFamilyName) };
            VERIFY_ARE_EQUAL(machinePath, winrt::hstring(expectedMachinePath.c_str()));
        }

        TEST_METHOD(MachineFolderAndPath_Framework_Supported)
        {
            winrt::hstring packageFamilyName{ Framework_PackageFamilyName };
            auto applicationData{ winrt::Microsoft::Windows::Storage::ApplicationData::GetForPackageFamily(packageFamilyName) };
            VERIFY_IS_NOT_NULL(applicationData);

            const auto machineFolder{ applicationData.MachineFolder() };
            const auto machinePath{ applicationData.MachinePath() };
            VERIFY_ARE_EQUAL(machineFolder.Path(), machinePath);

            const auto expectedMachinePath{ GetExpectedMachinePath(packageFamilyName) };
            VERIFY_ARE_EQUAL(machinePath, winrt::hstring(expectedMachinePath.c_str()));
        }

        TEST_METHOD(LocalSettings_Main)
        {
            //TODO
        }

        TEST_METHOD(LocalSettings_Framework)
        {
            //TODO
        }

        TEST_METHOD(RoamingSettings_Main)
        {
            //TODO
        }

        TEST_METHOD(RoamingSettings_Framework)
        {
            //TODO
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

        TEST_METHOD(ClearMachineAsync_Main)
        {
            //TODO
        }

        TEST_METHOD(ClearMachineAsync_Framework)
        {
            //TODO
        }
    };
}
