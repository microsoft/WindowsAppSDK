// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <windows.h>
#include <filesystem>
#include <vector>
#include <TestDef.h>
#include <PackageDeployment.h>
#include <DeploymentActivityContext.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

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

        TEST_METHOD(GetDeploymentPackageArguments_WithHigherVersionPackage_UsesExistingPath)
        {
            std::wstring frameworkFullName{ L"Microsoft.WindowsAppRuntime.1.5_x64__8wekyb3d8bbwe" };
            std::wstring frameworkPath{ L"C:\\Program Files\\WindowsApps\\Framework.1.5" };

            std::map<std::wstring, WindowsAppRuntime::Deployment::PackageDeployment::PackagePathInfo> higherVersionMap{};
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

            auto& singletonPackage = args[1];
            VERIFY_ARE_EQUAL(singletonPackage.identifier, L"Singleton");
            VERIFY_IS_FALSE(singletonPackage.useExistingPackageIfHigherVersion);
            VERIFY_ARE_EQUAL(
                singletonPackage.packagePath.wstring(),
                L"C:\\Program Files\\WindowsApps\\Framework.1.5\\MSIX\\Singleton.msix");
        }
    };
}
