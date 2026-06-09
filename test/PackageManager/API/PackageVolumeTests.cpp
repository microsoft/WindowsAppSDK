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
    class PackageVolumeTests_Base : protected PackageDeploymentManagerTests_Base
    {
    protected:
        const winrt::hstring& GetTempDirectory() const
        {
            return m_tempPath;
        }

        bool VerifyTestVolume(PCWSTR drive)
        {
            VERIFY_IS_NOT_NULL(drive);
            VERIFY_IS_TRUE(wcslen(drive) == 1, WEX::Common::String().Format(L"/p:PackageVolume.Drive=%s not valid", drive));
            VERIFY_IS_TRUE(CompareStringOrdinal(drive, -1, L"C", -1, TRUE) != CSTR_EQUAL, WEX::Common::String().Format(L"/p:PackageVolume.Drive=%s not valid (cannot be system drive)", drive));

            m_tempPath = std::format(L"{}:\\WindowsApps", drive).c_str();

            return VerifyTestVolume();
        }

        bool VerifyTestVolume()
        {
            if (m_tempPath.empty())
            {
                return false;
            }
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Path %sfound: %s", TempDirectoryExists() ? L"" : L"not ", m_tempPath.c_str()));

            winrt::Windows::Management::Deployment::PackageManager packageManager;
            try
            {
                auto packageVolume{ packageManager.FindPackageVolume(m_tempPath) };
                WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageVolume found: %s", m_tempPath.c_str()));

                VERIFY_IS_FALSE(packageVolume.IsSystemVolume(),
                                WEX::Common::String().Format(L"Invalid test path (%s) - cannot be system drive)", m_tempPath.c_str()));
                VERIFY_IS_TRUE(CompareStringOrdinal(packageVolume.PackageStorePath().c_str(), -1, m_tempPath.c_str(), -1, TRUE) == CSTR_EQUAL,
                               WEX::Common::String().Format(L"Invalid test path %s != PackageVolume.PackageStorePath %s", m_tempPath.c_str(), packageVolume.PackageStorePath().c_str()));
            }
            catch (winrt::hresult_error& e)
            {
                if (e.code() == HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
                {
                    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageVolume not found: %s", m_tempPath.c_str()));
                    return false;
                }
                else
                {
                    std::ignore = LOG_HR_MSG(e.code(),
                                             "PackageVolume.GetPackageVolumeByPath PackageStorePath:%ls : %ls",
                                             m_tempPath.c_str(), e.message().c_str());
                    throw;
                }
            }
            catch (...)
            {
                const auto exception{ winrt::hresult_error(winrt::to_hresult(), winrt::take_ownership_from_abi) };
                if (exception.code() == HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
                {
                    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageVolume not found: %s", m_tempPath.c_str()));
                    return false;
                }
                else
                {
                    std::ignore = LOG_HR_MSG(exception.code(),
                                             "PackageVolume.FindPackageVolumeByPath PackageStorePath:%ls : %ls",
                                             m_tempPath.c_str(), exception.message().c_str());
                    throw;
                }
            }

            return true;
        }

        bool BlockIfTestVolumeExists(PCWSTR drive)
        {
            const auto exists{ VerifyTestVolume(drive) };
            if (exists)
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Blocked,
                                          WEX::Common::String().Format(L"Test PackageVolume exists (%s). Blocking tests", m_tempPath.c_str()));
            }
            return exists;
        }

        bool TempDirectoryExists() const
        {
            return DirectoryExists(m_tempPath);
        }

        bool DirectoryExists(const winrt::hstring& path) const
        {
            return !path.empty() && std::filesystem::is_directory(path.c_str());
        }

    protected:
        void Dump(
            const winrt::Microsoft::Windows::Management::Deployment::PackageVolume& packageVolume) const
        {
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageVolume: Microsoft\n"
                                                                    L"                   MountPoint: %s\n"
                                                                    L"                         Name: %s\n"
                                                                    L"             PackageStorePath: %s\n"
                                                                    L"                        State:%s%s%s%s%s\n",
                                                                    packageVolume.MountPoint().c_str(),
                                                                    packageVolume.Name().c_str(),
                                                                    packageVolume.PackageStorePath().c_str(),
                                                                    packageVolume.IsSystemVolume() ? L" System" : L"",
                                                                    packageVolume.IsOffline() ? L" Offline" : L" Online",
                                                                    packageVolume.SupportsHardLinks() ? L" Hardlinks" : L"",
                                                                    packageVolume.IsAppxInstallSupported() ? L" AppxInstall" : L"",
                                                                    packageVolume.IsFullTrustPackageSupported() ? L" FullTrust" : L""));
            //TODO IsRepairNeeded
        }

        void Dump(
            const winrt::Windows::Management::Deployment::PackageVolume& packageVolume) const
        {
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageVolume: Windows\n"
                                                                    L"                   MountPoint: %s\n"
                                                                    L"                         Name: %s\n"
                                                                    L"             PackageStorePath: %s\n"
                                                                    L"                        State:%s%s%s%s%s\n",
                                                                    packageVolume.MountPoint().c_str(),
                                                                    packageVolume.Name().c_str(),
                                                                    packageVolume.PackageStorePath().c_str(),
                                                                    packageVolume.IsSystemVolume() ? L" System" : L"",
                                                                    packageVolume.IsOffline() ? L" Offline" : L" Online",
                                                                    packageVolume.SupportsHardLinks() ? L" Hardlinks" : L"",
                                                                    packageVolume.IsAppxInstallSupported() ? L" AppxInstall" : L"",
                                                                    packageVolume.IsFullTrustPackageSupported() ? L" FullTrust" : L""));
        }

        winrt::Microsoft::Windows::Management::Deployment::PackageVolume Dump(
            const winrt::hstring& path) const
        {
            auto packageVolume{ winrt::Microsoft::Windows::Management::Deployment::PackageVolume::GetPackageVolumeByPath(path) };
            Dump(packageVolume);
            return packageVolume;
        }

    protected:
        void Verify(
            const winrt::Microsoft::Windows::Management::Deployment::PackageVolume& packageVolume,
            const winrt::Windows::Management::Deployment::PackageVolume& windowsPackageVolume)
        {
            VERIFY_ARE_EQUAL(packageVolume.IsSystemVolume(), windowsPackageVolume.IsSystemVolume());
            VERIFY_ARE_EQUAL(packageVolume.MountPoint(), windowsPackageVolume.MountPoint());
            VERIFY_ARE_EQUAL(packageVolume.Name(), windowsPackageVolume.Name());
            VERIFY_ARE_EQUAL(packageVolume.PackageStorePath(), windowsPackageVolume.PackageStorePath());
            VERIFY_ARE_EQUAL(packageVolume.SupportsHardLinks(), windowsPackageVolume.SupportsHardLinks());
            VERIFY_ARE_EQUAL(packageVolume.IsAppxInstallSupported(), windowsPackageVolume.IsAppxInstallSupported());
            VERIFY_ARE_EQUAL(packageVolume.IsFullTrustPackageSupported(), windowsPackageVolume.IsFullTrustPackageSupported());
            VERIFY_ARE_EQUAL(packageVolume.IsOffline(), windowsPackageVolume.IsOffline());
        }

        void Verify(
            const winrt::Microsoft::Windows::Management::Deployment::PackageVolume& actual,
            const winrt::Microsoft::Windows::Management::Deployment::PackageVolume& expected)
        {
            VERIFY_ARE_EQUAL(expected.IsSystemVolume(), actual.IsSystemVolume());
            VERIFY_ARE_EQUAL(expected.MountPoint(), actual.MountPoint());
            VERIFY_ARE_EQUAL(expected.Name(), actual.Name());
            VERIFY_ARE_EQUAL(expected.PackageStorePath(), actual.PackageStorePath());
            VERIFY_ARE_EQUAL(expected.SupportsHardLinks(), actual.SupportsHardLinks());
            VERIFY_ARE_EQUAL(expected.IsAppxInstallSupported(), actual.IsAppxInstallSupported());
            VERIFY_ARE_EQUAL(expected.IsFullTrustPackageSupported(), actual.IsFullTrustPackageSupported());
            VERIFY_ARE_EQUAL(expected.IsOffline(), actual.IsOffline());
        }

    protected:
        bool RemovePackageVolumeIfNecessary()
        {
            if (m_tempPath.empty())
            {
                WEX::Common::String drive;
                if (!::Test::TAEF::TryGetOption(L"PackageVolume.Drive", drive))
                {
                    WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"/p:PackageVolume.Drive=<driveletter> not specified. Skipping tests");
                    return true;
                }
                const auto exists{ VerifyTestVolume(drive) };
                if (!exists)
                {
                    return true;
                }
            }

            winrt::Windows::Management::Deployment::PackageManager packageManager;
            try
            {
                auto packageVolume{ packageManager.FindPackageVolume(m_tempPath) };
                if (packageVolume)
                {
                    VERIFY_IS_FALSE(packageVolume.IsSystemVolume(),
                                    WEX::Common::String().Format(L"Invalid test path (%s) - cannot be system drive)", m_tempPath.c_str()));
                    VERIFY_IS_TRUE(CompareStringOrdinal(packageVolume.PackageStorePath().c_str(), -1, m_tempPath.c_str(), -1, TRUE) == CSTR_EQUAL,
                                   WEX::Common::String().Format(L"Invalid test path %s != PackageVolume.PackageStorePath %s", m_tempPath.c_str(), packageVolume.PackageStorePath().c_str()));

                    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"Removing PackageVolume %s", m_tempPath.c_str()));
                    auto deploymentOperation{ packageManager.RemovePackageVolumeAsync(packageVolume) };
                    auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
                    TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);
                }
            }
            catch (winrt::hresult_error& e)
            {
                if (e.code() == HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
                {
                    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageVolume not found: %s", m_tempPath.c_str()));
                }
                else
                {
                    std::ignore = LOG_HR_MSG(e.code(),
                                             "PackageVolume.GetPackageVolumeByPath PackageStorePath:%ls : %ls",
                                             m_tempPath.c_str(), e.message().c_str());
                    throw;
                }
            }
            catch (...)
            {
                const auto exception{ winrt::hresult_error(winrt::to_hresult(), winrt::take_ownership_from_abi) };
                if (exception.code() == HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
                {
                    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageVolume not found: %s", m_tempPath.c_str()));
                }
                else
                {
                    std::ignore = LOG_HR_MSG(exception.code(),
                                             "PackageVolume.FindPackageVolumeByPath PackageStorePath:%ls : %ls",
                                             m_tempPath.c_str(), exception.message().c_str());
                    throw;
                }
            }

            try
            {
                winrt::Windows::Management::Deployment::PackageVolume windowsPackageVolume{ packageManager.FindPackageVolume(m_tempPath) };
            }
            catch (winrt::hresult_error const& e)
            {
                if (e.code() == HRESULT_FROM_WIN32(ERROR_NOT_FOUND))
                {
                    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageVolume not defined for %s", m_tempPath.c_str()));
                }
                else
                {
                    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageManager.FindPackageVolume(%ls) = 0x%08X", m_tempPath.c_str(), e.code()));
                    throw;
                }
            }
            return true;
        }

    protected:
        winrt::hstring m_tempPath;
    };

    class PackageVolumeTests_Elevated : protected PackageVolumeTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageVolumeTests_Elevated)
            TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            ::TB::Setup();

            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            const auto exists{ VerifyTestVolume() };

            ::TB::Cleanup();
            return exists;
        }

    public:
        TEST_METHOD(GetDefault)
        {
            const auto packageVolume{ winrt::Microsoft::Windows::Management::Deployment::PackageVolume::GetDefault() };
            winrt::Windows::Management::Deployment::PackageManager packageManager;
            const auto windowsPackageVolume{ packageManager.GetDefaultPackageVolume() };
            Verify(packageVolume, windowsPackageVolume);
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

    class PackageVolumeTests_System : protected PackageVolumeTests_Base
    {
    public:
        BEGIN_TEST_CLASS(PackageVolumeTests_System)
            TEST_METHOD_PROPERTY(L"RunAs", L"ElevatedUser")
            TEST_METHOD_PROPERTY(L"RunFixtureAs", L"System")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassSetup)
        {
            return true;
        }

        TEST_CLASS_CLEANUP(ClassCleanup)
        {
            return RemovePackageVolumeIfNecessary();
        }

        TEST_METHOD(Add_Online_Offline_Remove)
        {
            ::TB::Setup();
            auto cleanup{ wil::scope_exit([this]{
                ::TB::Cleanup();
            }) };

            WEX::Common::String drive;
            if (!::Test::TAEF::TryGetOption(L"PackageVolume.Drive", drive))
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"/p:PackageVolume.Drive=<driveletter> not specified. Skipping tests");
                return;
            }
            if (BlockIfTestVolumeExists(drive))
            {
                return;
            }

            // Add a package volume
            auto asyncOperation{ winrt::Microsoft::Windows::Management::Deployment::PackageVolume::AddAsync(GetTempDirectory()) };
            const auto hr{ static_cast<HRESULT>(asyncOperation.ErrorCode()) };
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"AddAsync: Status=%d ErrorCode=0x%X", asyncOperation.Status(), hr));
            auto packageVolumeAdded{ asyncOperation.get() };
            Dump(packageVolumeAdded);
            //
            // NOTE: Newly created PackageVolumes are Online
            VERIFY_IS_FALSE(packageVolumeAdded.IsOffline());

            // Verify the new package volume is query'able
            {
                auto packageVolume{ Dump(GetTempDirectory()) };
                Verify(packageVolumeAdded, packageVolume);
            }

            VERIFY_IS_FALSE(packageVolumeAdded.IsOffline());

            // Set the package volume Offline (or 'Dismount-PackageVolume' in Powershell-speak)
            // FYI interactively: powershell -c "Get-AppxVolume -Path X: | Dismount-AppxVolume"
            {
                auto packageVolumeBefore{ Dump(GetTempDirectory()) };
                VERIFY_IS_FALSE(packageVolumeBefore.IsOffline());

                WEX::Logging::Log::Comment(WEX::Common::String().Format(L"SetOfflineAsync..."));
                auto deploymentOperation{ packageVolumeAdded.SetOfflineAsync() };
                auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
                TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

                auto packageVolumeAfter{ Dump(GetTempDirectory()) };
                VERIFY_IS_TRUE(packageVolumeAfter.IsOffline());
            }

            // Set the package volume Offline again (Offline->Offline == Offline (no change))
            {
                auto packageVolumeBefore{ Dump(GetTempDirectory()) };
                VERIFY_IS_TRUE(packageVolumeBefore.IsOffline());

                WEX::Logging::Log::Comment(WEX::Common::String().Format(L"SetOfflineAsync..."));
                auto deploymentOperation{ packageVolumeAdded.SetOfflineAsync() };
                auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
                TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

                auto packageVolumeAfter{ Dump(GetTempDirectory()) };
                VERIFY_IS_TRUE(packageVolumeAfter.IsOffline());
            }

            // Set the package volume Online (or 'Mount-PackageVolume' in Powershell-speak)
            // FYI interactively: powershell -c "Get-AppxVolume -Path X: | Mount-AppxVolume"
            {
                auto packageVolumeBefore{ Dump(GetTempDirectory()) };
                VERIFY_IS_TRUE(packageVolumeBefore.IsOffline());

                WEX::Logging::Log::Comment(WEX::Common::String().Format(L"SetOnlineAsync..."));
                auto deploymentOperation{ packageVolumeAdded.SetOnlineAsync() };
                auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
                TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

                auto packageVolumeAfter{ Dump(GetTempDirectory()) };
                VERIFY_IS_FALSE(packageVolumeAfter.IsOffline());
            }

            // Set the package volume Online again (Online->Online == Online (no change))
            {
                auto packageVolumeBefore{ Dump(GetTempDirectory()) };
                VERIFY_IS_FALSE(packageVolumeBefore.IsOffline());

                WEX::Logging::Log::Comment(WEX::Common::String().Format(L"SetOnlineAsync..."));
                auto deploymentOperation{ packageVolumeAdded.SetOnlineAsync() };
                auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
                TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);

                auto packageVolumeAfter{ Dump(GetTempDirectory()) };
                VERIFY_IS_FALSE(packageVolumeAfter.IsOffline());
            }

            // Remove the package volume
            //
            // FYI interactively: powershell -c "Get-AppxVolume -Path X: | Remove-AppxVolume"
            {
                auto packageVolume{ Dump(GetTempDirectory()) };
                VERIFY_IS_FALSE(packageVolume.IsOffline());

                auto deploymentOperation{ packageVolumeAdded.RemoveAsync() };
                auto deploymentResult{ WaitForDeploymentOperation(deploymentOperation) };
                TPMT::VerifyDeploymentSucceeded(deploymentResult, __FILE__, __LINE__, __FUNCTION__);
            }
        }
    };
}
