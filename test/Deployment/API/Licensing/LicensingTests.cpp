// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "pch.h"
#include "WindowsAppRuntime-License.h"

#include <algorithm>
#include <fstream>
#include <WexTestClass.h>

#include <MsixLicensing.h>
#include <WindowsAppRuntime.Test.FileSystem.h>

namespace Test::Deployment
{
    class LicensingTests
    {
    public:
        BEGIN_TEST_CLASS(LicensingTests)
            TEST_CLASS_PROPERTY(L"IsolationLevel", L"Method")
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
        END_TEST_CLASS()

        TEST_METHOD(InstallsMatchingLicenseFiles)
        {
            namespace Licensing = ::Microsoft::Windows::ApplicationModel::Licensing;
            auto& installedFiles{ Licensing::Installer::InstalledFiles };
            installedFiles.clear();

            const auto licensePath{ ::Test::FileSystem::GetModulePath(wil::GetModuleInstanceHandle()) / L"MSIX" };
            if (!std::filesystem::create_directory(licensePath))
            {
                VERIFY_FAIL(L"The test requires a fresh MSIX directory beside its module.");
                return;
            }
            auto cleanup{ wil::scope_exit([&]
            {
                std::error_code ignored;
                std::filesystem::remove_all(licensePath, ignored);
                installedFiles.clear();
            }) };

            VERIFY_SUCCEEDED(MsixInstallLicenses());
            VERIFY_IS_TRUE(installedFiles.empty());

            for (const auto filename : { L"main_license.xml", L"singleton_license.xml", L"unrelated.xml" })
            {
                std::ofstream file{ licensePath / filename };
                VERIFY_IS_TRUE(file.is_open());
                file << "test license";
                VERIFY_IS_TRUE(file.good());
            }
            VERIFY_IS_TRUE(std::filesystem::create_directory(licensePath / L"directory_license.xml"));

            VERIFY_SUCCEEDED(MsixInstallLicenses());
            VERIFY_ARE_EQUAL(size_t{ 2 }, installedFiles.size());
            VERIFY_IS_TRUE(std::find(installedFiles.begin(), installedFiles.end(), licensePath / L"main_license.xml") != installedFiles.end());
            VERIFY_IS_TRUE(std::find(installedFiles.begin(), installedFiles.end(), licensePath / L"singleton_license.xml") != installedFiles.end());
        }
    };
}
