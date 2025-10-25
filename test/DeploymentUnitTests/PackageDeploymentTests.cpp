// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <TestDef.h>
#include <PackageDeployment.h>
#include <DeploymentActivityContext.h>
#include <filesystem>
#include <vector>
#include <windows.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt;

namespace Test::Deployment::PackageDeployment
{
    class PackageDeploymentTests
    {
    public:
        BEGIN_TEST_CLASS(PackageDeploymentTests)
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

        TEST_METHOD(DeployPackages_PackageManagerException_HandlesGracefully)
        {
            std::vector<WindowsAppRuntime::Deployment::PackageDeployment::DeploymentPackageArguments> args;
            ::WindowsAppRuntime::Deployment::Activity::Context activityContext{};

            // Add invalid package argument that could cause exceptions
            args.push_back({
                L"TestPackage",
                std::filesystem::path(L"\\\\invalid\\path\\package.msix"),
                false,
                false
            });

            auto hr = ::WindowsAppRuntime::Deployment::PackageDeployment::DeployPackages(
                args, false, activityContext);

            // Should handle package deployment exceptions gracefully
            VERIFY_IS_TRUE(FAILED(hr));
            VERIFY_ARE_NOT_EQUAL(hr, static_cast<HRESULT>(0x8007023E));
        }

        TEST_METHOD(GetDeploymentPackageArguments_WithHigherVersionPackage_UsesExistingPath)
        {
            std::wstring frameworkFullName = L"Microsoft.WindowsAppRuntime.1.5_x64__8wekyb3d8bbwe";
            std::wstring frameworkPath = L"C:\\Program Files\\WindowsApps\\Framework.1.5";

            std::map<std::wstring, WindowsAppRuntime::Deployment::PackageDeployment::PackagePathInfo> higherVersionMap;
            higherVersionMap[L"Main"] = {
                L"Main.2.0_x64__8wekyb3d8bbwe",
                L"C:\\Program Files\\WindowsApps\\Main.2.0"
            };

            ::WindowsAppRuntime::Deployment::Activity::Context context{};

            auto args = WindowsAppRuntime::Deployment::PackageDeployment::GetDeploymentPackageArguments(
                frameworkPath,
                context,
                higherVersionMap);

            VERIFY_ARE_EQUAL(args.size(), 2u);  // Main and Singleton

            auto& mainPackage = args[0];
            VERIFY_ARE_EQUAL(mainPackage.identifier, L"Main");
            VERIFY_IS_TRUE(mainPackage.useExistingPackageIfHigherVersion);
            VERIFY_ARE_EQUAL(
                mainPackage.packagePath.wstring(),
                L"C:\\Program Files\\WindowsApps\\Main.2.0\\AppxManifest.xml");
        }
    };
}
