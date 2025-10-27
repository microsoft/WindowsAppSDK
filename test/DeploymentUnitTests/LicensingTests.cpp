// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <windows.h>
#include <string>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <TestDef.h>
#include <Licensing.h>
#include <DeploymentActivityContext.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

namespace Test::Deployment::Licensing
{
    constexpr HRESULT c_unhandledExceptionHResult = 0x8007023E;

    // Mock implementation of ILicenseInstaller for testing
    struct MockLicenseInstaller : public WindowsAppRuntime::Deployment::Licensing::ILicenseInstaller
    {
        std::vector<std::wstring> m_installedFiles;
        std::unordered_map<std::wstring, HRESULT> m_expectedFailureMap;
        bool m_shouldTrhowException = false;

        MockLicenseInstaller() = default;

        // Set up the mock to fail on a specific file
        void SetupFailureOnFile(const std::wstring& filename, HRESULT errorCode)
        {
            m_expectedFailureMap[filename] = errorCode;
        }

        void SetShouldThrowException(bool shouldThrow)
        {
            m_shouldTrhowException = shouldThrow;
        }

        HRESULT InstallLicenseFile(const std::wstring& licenseFilename) override
        {
            if (m_shouldTrhowException)
            {
                throw std::runtime_error("Test exception");
            }

            for (auto it : m_expectedFailureMap)
            {
                auto filename {it.first};
                if(licenseFilename.find(filename) != std::wstring::npos)
                {
                    return it.second;
                }
            }

            m_installedFiles.push_back(licenseFilename);
            return S_OK;
        }

        // Test helper methods
        const std::vector<std::wstring>& GetInstalledFiles() const
        {
            return m_installedFiles;
        }

        void Reset() {
            m_installedFiles.clear();
            m_expectedFailureMap.clear();
            m_shouldTrhowException = false;
        }

        size_t GetInstallCount() const {
            return m_installedFiles.size();
        }
    };

    class LicensingTests
    {
    public:
        BEGIN_TEST_CLASS(LicensingTests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_CLASS_SETUP(ClassInit)
        {
            return true;
        }

        TEST_CLASS_CLEANUP(ClassUninit)
        {
            return true;
        }

        // GetLicenseFiles Tests
        TEST_METHOD(GetLicenseFiles_NoFilesFound_ReturnsSuccessWithEmptyVector)
        {
            Log::Comment(L"Test GetLicenseFiles with non-existent path returns success with empty vector");

            std::vector<std::wstring> licenseFiles{};
            std::wstring nonExistentPath{L"C:\\NonExistent\\Path\\*_license.xml"};

            HRESULT hr = WindowsAppRuntime::Deployment::Licensing::GetLicenseFiles(nonExistentPath, licenseFiles);

            VERIFY_SUCCEEDED(hr);
            VERIFY_ARE_EQUAL(licenseFiles.size(), 0u);
            Log::Comment(L"GetLicenseFiles correctly handled non-existent path");
        }

        TEST_METHOD(GetLicenseFiles_EmptyFileSpec_Succeeds)
        {
            Log::Comment(L"Test GetLicenseFiles with empty file specification");

            std::vector<std::wstring> licenseFiles{};
            std::wstring emptyPath{L""};

            HRESULT hr = WindowsAppRuntime::Deployment::Licensing::GetLicenseFiles(emptyPath, licenseFiles);

            VERIFY_SUCCEEDED(hr);
            VERIFY_ARE_EQUAL(licenseFiles.size(), 0u);
            Log::Comment(L"GetLicenseFiles correctly handled empty file specification");
        }

        TEST_METHOD(GetLicenseFiles_InvalidPath_ReturnsError)
        {
            Log::Comment(L"Test GetLicenseFiles with invalid path characters");

            std::vector<std::wstring> licenseFiles{};
            std::wstring invalidPath{L"C:\\Invalid|Path\\*_license.xml"};

            HRESULT hr = WindowsAppRuntime::Deployment::Licensing::GetLicenseFiles(invalidPath, licenseFiles);

            VERIFY_IS_TRUE(FAILED(hr));
            Log::Comment(String().Format(L"GetLicenseFiles correctly failed with invalid path, HR: 0x%08X", hr));
        }

        TEST_METHOD(GetLicenseFiles_ClearsOutputVector)
        {
            Log::Comment(L"Test GetLicenseFiles clears the output vector");

            std::vector<std::wstring> licenseFiles {
                L"existing_file.xml",
                L"another_file.xml"
            };

            VERIFY_ARE_EQUAL(licenseFiles.size(), 2u);

            std::wstring nonExistentPath = L"C:\\NonExistent\\Path\\*_license.xml";
            HRESULT hr = WindowsAppRuntime::Deployment::Licensing::GetLicenseFiles(nonExistentPath, licenseFiles);

            VERIFY_SUCCEEDED(hr);
            VERIFY_ARE_EQUAL(licenseFiles.size(), 0u);
            Log::Comment(L"GetLicenseFiles correctly cleared the output vector");
        }

        TEST_METHOD(GetLicenseFiles_WithRealFiles_FindsAllLicenseFiles)
        {
            Log::Comment(L"Test GetLicenseFiles with real mock license files");

            std::vector<std::wstring> licenseFiles{};

            // Get the current test directory and construct the MSIX path
            wchar_t currentDir[MAX_PATH];
            GetCurrentDirectory(MAX_PATH, currentDir);
            std::wstring testPath = std::wstring(currentDir) + L"\\test\\DeploymentUnitTests\\MSIX\\*_license.xml";

            HRESULT hr = WindowsAppRuntime::Deployment::Licensing::GetLicenseFiles(testPath, licenseFiles);

            VERIFY_SUCCEEDED(hr);
            VERIFY_ARE_EQUAL(licenseFiles.size(), 3u);

            VERIFY_ARE_EQUAL(licenseFiles[0], L"a_license.xml");
            VERIFY_ARE_EQUAL(licenseFiles[1], L"b_license.xml");
            // Note: preserves case of original name
            VERIFY_ARE_EQUAL(licenseFiles[2], L"c_License.xml");

            Log::Comment(L"GetLicenseFiles correctly found all 3 license files");
        }

        // InstallLicenses Tests
        TEST_METHOD(InstallLicenses_EmptyLicenseList_ReturnsSuccess)
        {
            Log::Comment(L"Test InstallLicenses with empty license file list");

            std::vector<std::wstring> licenseFiles{};
            std::filesystem::path licensePath{L"C:\\TestPath"};
            MockLicenseInstaller mockInstaller{};
            WindowsAppRuntime::Deployment::Activity::Context activityContext{};

            HRESULT hr = WindowsAppRuntime::Deployment::Licensing::InstallLicenses(
                licenseFiles, licensePath, mockInstaller, activityContext);

            VERIFY_SUCCEEDED(hr);
            VERIFY_ARE_EQUAL(mockInstaller.GetInstallCount(), 0u);
            Log::Comment(L"InstallLicenses correctly handled empty license list");
        }

        TEST_METHOD(InstallLicenses_SingleLicenseFile_InstallsSuccessfully)
        {
            Log::Comment(L"Test InstallLicenses with single license file");

            std::vector<std::wstring> licenseFiles{L"test_license.xml"};
            std::filesystem::path licensePath{L"C:\\TestPath"};
            MockLicenseInstaller mockInstaller{};
            WindowsAppRuntime::Deployment::Activity::Context activityContext{};

            HRESULT hr = WindowsAppRuntime::Deployment::Licensing::InstallLicenses(
                licenseFiles, licensePath, mockInstaller, activityContext);

            VERIFY_SUCCEEDED(hr);
            VERIFY_ARE_EQUAL(mockInstaller.GetInstallCount(), 1u);

            const auto& installedFiles = mockInstaller.GetInstalledFiles();
            VERIFY_IS_TRUE(installedFiles[0].find(L"test_license.xml") != std::wstring::npos);
            VERIFY_IS_TRUE(installedFiles[0].find(L"C:\\TestPath") != std::wstring::npos);

            Log::Comment(String().Format(L"Successfully installed: %s", installedFiles[0].c_str()));
        }

        TEST_METHOD(InstallLicenses_MultipleLicenseFiles_InstallsAll)
        {
            Log::Comment(L"Test InstallLicenses with multiple license files");

            std::vector<std::wstring> licenseFiles {
                L"license1.xml",
                L"license2.xml",
                L"license3.xml"
            };
            std::filesystem::path licensePath{L"C:\\TestPath"};
            MockLicenseInstaller mockInstaller{};
            WindowsAppRuntime::Deployment::Activity::Context activityContext{};

            HRESULT hr = WindowsAppRuntime::Deployment::Licensing::InstallLicenses(
                licenseFiles, licensePath, mockInstaller, activityContext);

            VERIFY_SUCCEEDED(hr);
            VERIFY_ARE_EQUAL(mockInstaller.GetInstallCount(), 3u);

            const auto& installedFiles = mockInstaller.GetInstalledFiles();
            for (size_t i = 0; i < licenseFiles.size(); ++i)
            {
                VERIFY_IS_TRUE(installedFiles[i].find(licenseFiles[i]) != std::wstring::npos);
                Log::Comment(String().Format(L"Installed file %zu: %s", i + 1, installedFiles[i].c_str()));
            }
        }

        TEST_METHOD(InstallLicenses_InstallerFails_ReturnsError)
        {
            Log::Comment(L"Test InstallLicenses when installer fails");

            std::vector<std::wstring> licenseFiles{L"failing_license.xml"};
            std::filesystem::path licensePath{L"C:\\TestPath"};
            MockLicenseInstaller mockInstaller{};
            mockInstaller.SetupFailureOnFile(L"failing_license.xml", E_ACCESSDENIED);
            WindowsAppRuntime::Deployment::Activity::Context activityContext{};

            HRESULT hr = WindowsAppRuntime::Deployment::Licensing::InstallLicenses(
                licenseFiles, licensePath, mockInstaller, activityContext);

            VERIFY_ARE_EQUAL(hr, E_ACCESSDENIED);
            Log::Comment(String().Format(L"InstallLicenses correctly returned error: 0x%08X", hr));
        }

        TEST_METHOD(InstallLicenses_PartialFailure_StopsOnFirstError)
        {
            Log::Comment(L"Test InstallLicenses stops on first error in batch");

            std::vector<std::wstring> licenseFiles {
                L"good_license.xml",
                L"failing_license.xml",
                L"never_reached.xml"
            };
            std::filesystem::path licensePath{L"C:\\TestPath"};
            MockLicenseInstaller mockInstaller{};
            mockInstaller.SetupFailureOnFile(L"failing_license.xml", E_FAIL);
            WindowsAppRuntime::Deployment::Activity::Context activityContext{};

            HRESULT hr = WindowsAppRuntime::Deployment::Licensing::InstallLicenses(
                licenseFiles, licensePath, mockInstaller, activityContext);

            VERIFY_ARE_EQUAL(hr, E_FAIL);
            // Should have installed the first file before failing on the second
            VERIFY_ARE_EQUAL(mockInstaller.GetInstallCount(), 1u);

            const auto& installedFiles = mockInstaller.GetInstalledFiles();
            VERIFY_IS_TRUE(installedFiles[0].find(L"good_license.xml") != std::wstring::npos);

            Log::Comment(L"InstallLicenses correctly stopped after first failure");
        }

        TEST_METHOD(InstallLicenses_SetsActivityContext)
        {
            Log::Comment(L"Test InstallLicenses updates activity context properly");

            std::vector<std::wstring> licenseFiles{L"test_license.xml"};
            std::filesystem::path licensePath{L"C:\\TestPath"};
            MockLicenseInstaller mockInstaller{};
            WindowsAppRuntime::Deployment::Activity::Context activityContext{};

            // Reset context to initial state
            activityContext.Reset();

            HRESULT hr = WindowsAppRuntime::Deployment::Licensing::InstallLicenses(
                licenseFiles, licensePath, mockInstaller, activityContext);

            VERIFY_SUCCEEDED(hr);

            // The function should have set the install stage
            VERIFY_ARE_EQUAL(
                activityContext.GetInstallStage(),
                WindowsAppRuntime::Deployment::Activity::DeploymentStage::InstallLicense);

            // The current resource ID should be set to the installed license file
            std::wstring expectedResourceId = licensePath.wstring() + L"\\test_license.xml";
            VERIFY_ARE_EQUAL(activityContext.GetCurrentResourceId(), expectedResourceId);

            Log::Comment(L"InstallLicenses completed with activity context updates");
        }

        TEST_METHOD(InstallLicenses_CorrectPathCombination)
        {
            Log::Comment(L"Test InstallLicenses correctly combines path and filename");

            std::vector<std::wstring> licenseFiles{L"myapp_license.xml"};
            std::filesystem::path licensePath{L"C:\\Program Files\\TestApp\\Licenses"};
            MockLicenseInstaller mockInstaller{};
            WindowsAppRuntime::Deployment::Activity::Context activityContext{};

            HRESULT hr = WindowsAppRuntime::Deployment::Licensing::InstallLicenses(
                licenseFiles, licensePath, mockInstaller, activityContext);

            VERIFY_SUCCEEDED(hr);
            VERIFY_ARE_EQUAL(mockInstaller.GetInstallCount(), 1u);

            const auto& installedFiles = mockInstaller.GetInstalledFiles();
            std::wstring expectedPath = L"C:\\Program Files\\TestApp\\Licenses\\myapp_license.xml";

            // Normalize path separators for comparison
            std::wstring actualPath = installedFiles[0];
            VERIFY_IS_TRUE(actualPath.find(L"TestApp") != std::wstring::npos);
            VERIFY_IS_TRUE(actualPath.find(L"Licenses") != std::wstring::npos);
            VERIFY_IS_TRUE(actualPath.find(L"myapp_license.xml") != std::wstring::npos);

            Log::Comment(String().Format(L"Correct path combination: %s", actualPath.c_str()));
        }

        TEST_METHOD(InstallLicenses_CorruptedLicenseFile_HandlesException)
        {
            BEGIN_TEST_METHOD_PROPERTIES()
                TEST_METHOD_PROPERTY(L"Ignore", L"True") // Currently failing
            END_TEST_METHOD_PROPERTIES()

            std::vector<std::wstring> licenseFiles{L"corrupted_license.xml"};
            std::filesystem::path licensePath{L"C:\\Program Files\\TestApp\\Licenses"};
            MockLicenseInstaller mockInstaller{};
            ::WindowsAppRuntime::Deployment::Activity::Context activityContext{};

            // Mock the installer to simulate exception during license processing
            mockInstaller.SetShouldThrowException(true);

            auto hr = ::WindowsAppRuntime::Deployment::Licensing::InstallLicenses(
                licenseFiles, licensePath, mockInstaller, activityContext);

            // Should handle license processing exceptions gracefully
            VERIFY_IS_TRUE(FAILED(hr));
            VERIFY_ARE_NOT_EQUAL(hr, c_unhandledExceptionHResult);
        }

        TEST_METHOD(GetLicenseFiles_FileSystemException_HandlesGracefully)
        {
            // Test with path that could cause file system exceptions
            std::wstring problematicPath{L"\\\\?\\C:\\System Volume Information\\*_license.xml"}; // Restricted access
            std::vector<std::wstring> licenseFiles{};

            auto hr = ::WindowsAppRuntime::Deployment::Licensing::GetLicenseFiles(problematicPath, licenseFiles);

            // Should handle file system access issues gracefully
            VERIFY_IS_TRUE(FAILED(hr)); // Either way, shouldn't throw unhandled exception
            VERIFY_ARE_NOT_EQUAL(hr, c_unhandledExceptionHResult);
        }
    };
}
