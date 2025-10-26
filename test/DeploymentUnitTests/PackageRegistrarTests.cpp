// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <windows.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <winrt/Windows.Management.Deployment.h>
#include <TestDef.h>
#include <PackageRegistrar.h>
#include <DeploymentActivityContext.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt::Windows::Management::Deployment;

namespace Test::Deployment
{
    constexpr HRESULT c_unhandledExceptionHResult = 0x8007023E;

    class PackageRegistrarTests
    {
    public:
        BEGIN_TEST_CLASS(PackageRegistrarTests)
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

        // Path validation tests
        TEST_METHOD(GenerateDeploymentAgentPath_PathExists)
        {
            Log::Comment(L"Test that generated path points to an existing location");

            auto path = WindowsAppRuntime::Deployment::PackageRegistrar::GenerateDeploymentAgentPath();
            std::filesystem::path fsPath(path);

            // The directory should exist (even if the exe doesn't)
            auto parentPath = fsPath.parent_path();
            VERIFY_IS_TRUE(std::filesystem::exists(parentPath));

            Log::Comment(String().Format(L"Parent directory exists: %s", parentPath.c_str()));
        }

        // AddOrRegisterPackageInBreakAwayProcess tests
        TEST_METHOD(AddOrRegisterPackageInBreakAwayProcess_InvalidPath_ReturnsError)
        {
            Log::Comment(L"Test AddOrRegisterPackageInBreakAwayProcess with invalid path");

            WindowsAppRuntime::Deployment::Activity::Context activityContext;
            std::filesystem::path invalidPath(L"C:\\NonExistent\\Invalid.msix");

            HRESULT hr = WindowsAppRuntime::Deployment::PackageRegistrar::AddOrRegisterPackageInBreakAwayProcess(
                invalidPath,
                false, // useExistingPackageIfHigherVersion
                false, // forceDeployment
                activityContext,
                WindowsAppRuntime::Deployment::PackageRegistrar::GenerateDeploymentAgentPath()
            );

            VERIFY_IS_TRUE(FAILED(hr));
        }

        TEST_METHOD(AddOrRegisterPackageInBreakAwayProcess_CustomDeploymentAgentPath)
        {
            Log::Comment(L"Test AddOrRegisterPackageInBreakAwayProcess with custom deployment agent path");

            WindowsAppRuntime::Deployment::Activity::Context activityContext;
            std::filesystem::path testPackagePath(L"C:\\test.msix");
            std::wstring customAgentPath = L"C:\\CustomPath\\DeploymentAgent.exe";

            // Should fail because neither package nor agent exist, but we're testing parameter handling
            HRESULT hr = WindowsAppRuntime::Deployment::PackageRegistrar::AddOrRegisterPackageInBreakAwayProcess(
                testPackagePath,
                false,
                false,
                activityContext,
                customAgentPath
            );

            VERIFY_IS_TRUE(FAILED(hr));
        }

        TEST_METHOD(AddOrRegisterPackage_InvalidPath_HandlesException)
        {
            // TODO: Maybe we should mock PackageManager to throw exceptions?
            auto packageManager = winrt::Windows::Management::Deployment::PackageManager{};
            ::WindowsAppRuntime::Deployment::Activity::Context activityContext{};

            // Test with invalid/malformed path that could cause unhandled exceptions
            std::filesystem::path invalidPath{ L"\\\\invalid-unc-path\\nonexistent\\path\\package.msix" };

            auto hr = ::WindowsAppRuntime::Deployment::PackageRegistrar::AddOrRegisterPackage(
                invalidPath, false, false, packageManager, activityContext);

            // Should return a proper HRESULT, not throw unhandled exception
            VERIFY_IS_TRUE(FAILED(hr));
            VERIFY_ARE_NOT_EQUAL(hr, c_unhandledExceptionHResult);
        }

        TEST_METHOD(AddOrRegisterPackage_CorruptedPackage_HandlesException)
        {
            auto packageManager = winrt::Windows::Management::Deployment::PackageManager{};
            ::WindowsAppRuntime::Deployment::Activity::Context activityContext{};

            // Create a corrupted/invalid MSIX file
            std::filesystem::path tempPath = std::filesystem::temp_directory_path() / L"corrupted.msix";
            std::ofstream corruptedFile(tempPath, std::ios::binary);
            corruptedFile << "This is not a valid MSIX file content";
            corruptedFile.close();

            auto hr = ::WindowsAppRuntime::Deployment::PackageRegistrar::AddOrRegisterPackage(
                tempPath, false, false, packageManager, activityContext);

            // Cleanup
            std::filesystem::remove(tempPath);

            // Should handle the corruption gracefully, not throw unhandled exception
            VERIFY_IS_TRUE(FAILED(hr));
            VERIFY_ARE_NOT_EQUAL(hr, c_unhandledExceptionHResult);
        }

        TEST_METHOD(AddOrRegisterPackageInBreakAwayProcess_InvalidAgentPath_HandlesException)
        {
            ::WindowsAppRuntime::Deployment::Activity::Context activityContext{};
            std::filesystem::path validPackagePath = std::filesystem::temp_directory_path() / L"test.msix";
            std::wstring invalidAgentPath = L"C:\\NonExistent\\deploymentagent.exe";

            auto hr = ::WindowsAppRuntime::Deployment::PackageRegistrar::AddOrRegisterPackageInBreakAwayProcess(
                validPackagePath, false, false, activityContext, invalidAgentPath);

            // Should fail gracefully, not throw unhandled exception
            VERIFY_IS_TRUE(FAILED(hr));
            VERIFY_ARE_NOT_EQUAL(hr, c_unhandledExceptionHResult);
        }
    };
}
