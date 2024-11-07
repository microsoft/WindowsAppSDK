// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <IsWindowsVersion.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace Test::ApplicationData::Tests
{
    const auto Main_PackageFamilyName{ ::TP::DynamicDependencyDataStore::c_PackageFamilyName };
    const auto Framework_PackageFamilyName{ ::TP::WindowsAppRuntimeFramework::c_PackageFamilyName };

    inline std::filesystem::path GetExpectedMachinePath(winrt::hstring const& packageFamilyName)
    {
        // Expected Path = HKLM\...apprepository...\Families\ApplicationData\...pkgfamilyname...\Machine
        // This is typically %ProgramData%\Microsoft\Windows\AppRepository\Families\ApplicationData\...pkgfamilyname...\Machine
        // and by 'typically' we mean 'all current Windows editions' so we'll assume it's true for ease of testing
        // and use this test as a canary to detect if/when this is ever not true on any supported platform.
        wil::unique_cotaskmem_string path;
        THROW_IF_FAILED(::SHGetKnownFolderPath(FOLDERID_ProgramData, 0, nullptr, wil::out_param(path)));
        const std::filesystem::path programData{ path.get() };
        const auto packageRepositoryRoot{ programData / L"Microsoft\\Windows\\AppRepository\\Families\\ApplicationData" };
        const auto packageFamilyRoot{ packageRepositoryRoot / packageFamilyName.c_str() };
        const auto expectedMachinePath{ packageFamilyRoot / L"Machine" };
        return expectedMachinePath;
    }

    class ApplicationDataTests_Elevated
    {
    public:
        BEGIN_TEST_CLASS(ApplicationDataTests_Elevated)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Class")
            TEST_CLASS_PROPERTY(L"RunAs", L"ElevatedUser")
            TEST_CLASS_PROPERTY(L"RunFixtureAs", L"System")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            if (!::WindowsVersion::IsWindows11_21H2OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageDeploymentManager requires Win11 >= 21H2 (SV1). Skipping tests");
                return true;
            }

            ::TD::DumpExecutionContext();

            CreateMachinePathIfNecessary(Framework_PackageFamilyName);
            CreateMachinePathIfNecessary(Main_PackageFamilyName);
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            RemoveMachinePathIfNecessary(Main_PackageFamilyName);
            RemoveMachinePathIfNecessary(Framework_PackageFamilyName);
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

        TEST_METHOD(MachineFolderAndPath_Main_Supported)
        {
            ::TB::Setup();

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

            ::TB::Cleanup();
        }

        TEST_METHOD(MachineFolderAndPath_Framework_Supported)
        {
            ::TB::Setup();

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

            ::TB::Cleanup();
        }
    };
}
