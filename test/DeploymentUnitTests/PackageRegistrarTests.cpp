// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <TestDef.h>
#include <PackageRegistrar.h>
#include <string>
#include <filesystem>
#include <windows.h>
#include <DeploymentActivityContext.h>
#include <winrt/Windows.Management.Deployment.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt;
using namespace winrt::Windows::Management::Deployment;

namespace Test::Deployment
{
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
        TEST_METHOD(PackageRegistrar_GenerateDeploymentAgentPath_PathExists)
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
        TEST_METHOD(PackageRegistrar_AddOrRegisterPackageInBreakAwayProcess_InvalidPath_ReturnsError)
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

        TEST_METHOD(PackageRegistrar_AddOrRegisterPackageInBreakAwayProcess_CustomDeploymentAgentPath)
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
            // The specific error will depend on what fails first (package not found vs agent not found)
        }
    };
}
