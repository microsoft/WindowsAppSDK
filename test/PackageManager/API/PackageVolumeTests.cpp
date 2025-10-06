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

namespace Test::PackageVolume::Tests
{
    class PackageVolumeTests_Stage_Elevated : TPMT::PackageDeploymentManagerTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageVolumeTests_Stage_Elevated)
            TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            //***SEEME***TD::DumpExecutionContext();

            ::TB::Setup();

            CreateTempDirectory();
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            RemoveTempDirectory();

            ::TB::Cleanup();
            return true;
        }

    private:
        winrt::hstring m_tempPath;

    private:
        void RemoveTempDirectory()
        {
            if (m_tempPath.empty())
            {
                return;
            }

            if (std::filesystem::is_directory(m_tempPath.c_str()))
            {
                VERIFY_SUCCESS(wil::RemoveDirectoryRecursiveNoThrow(m_tempPath.c_str()));
            }
            VERIFY_IS_TRUE(std::filesystem::create_directory(m_tempPath.c_str()));

            m_tempPath.clear();
        }

        void CreateTempDirectory()
        {
            if (m_tempPath.empty())
            {
                const auto tempDirectory{ std::filesystem::temp_directory_path() / L"PackageVolumeTests" };
                m_tempPath = tempDirectory.c_str();
            }

            RemoveTempDirectory();

            VERIFY_IS_TRUE(std::filesystem::create_directory(m_tempPath.c_str()));

            VERIFY_IS_TRUE(std::filesystem::is_directory(m_tempPath.c_str()));
        }

        bool TempDirectoryExists() const
        {
            return std::filesystem::is_directory(m_tempPath.c_str())

    public:

        TEST_METHOD(GetDefault)
        {
            const auto packageVolume{ winrt::Microsoft::Windows::Management::Deployment::PackageVolume::GetDefault() };
            const auto windowsPackageVolume{ winrt::Windows::Management::Deployment::PackageManager::GetDefaultPackageVolume() };
            Verify(packageVolume, windowsPackageVolume);
        }

        TEST_METHOD(Add_Online_Offline_Remove)
        {
            auto packageVolumeAdded{ winrt::Microsoft::Windows::Management::Deployment::PackageVolume::AddAsync(m_tempPath).get() };
            auto packageVolume{ winrt::Microsoft::Windows::Management::Deployment::PackageVolume::FindPackageVolumeByPath(m_tempPath) };
            Verify(packageVolumeAdded, packageVolume);

            VERIFY_IS_FALSE(packageVolumeAdded.IsOffline());

            {
                auto deploymentOperation{ packageVolumeAdded.SetOfflineAsync() };
                auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
                TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);
                auto packageVolume{ winrt::Microsoft::Windows::Management::Deployment::PackageVolume::FindPackageVolumeByPath(m_tempPath) };
                VERIFY_IS_TRUE(packageVolume.IsOffline());
            }

            {
                auto deploymentOperation{ packageVolumeAdded.SetOnlineAsync() };
                auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
                TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);
                auto packageVolume{ winrt::Microsoft::Windows::Management::Deployment::PackageVolume::FindPackageVolumeByPath(m_tempPath) };
                VERIFY_IS_FALSE(packageVolume.IsOffline());
            }

            {
                auto deploymentOperation{ winrt::Microsoft::Windows::Management::Deployment::PackageVolume::RemoveAsync(m_tempPath) };
                auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
                TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);
            }
        }

        TEST_METHOD(GetAvailableSpace)
        {
            const auto packageVolume{ winrt::Microsoft::Windows::Management::Deployment::PackageVolume::GetDefault() };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackgeVolume.Default: MountPoint=%ls Name=%ls PackageStorePath=%ls",
                                       packageVolume.MountPoint().c_str(), packageVolume.Name().c_str(), packageVolume.PackageStorePath().c_str()));
            std::uint64_t availableSpace{ packageVolume.GetAvailableSpaceAsync().get() };
            std::uint64_t kb{ availableSpace / 1024 };
            std::uint64_t mb{ kb / 1024 };
            std::uint64_t gb{ mb / 1024 };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"AvailableSpace=%llu bytes / %lluKB / %lluMB / %lluGB", availableSpace, kb, mb, gb));
        }
    };
}
