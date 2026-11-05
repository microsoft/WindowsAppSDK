// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "pch.h"
#include "WindowsAppRuntime-License.h"

#include <algorithm>
#include <fstream>
#include <initializer_list>
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
            TEST_CLASS_PROPERTY(L"Parallel", L"false") // The methods share the module's MSIX directory.
        END_TEST_CLASS()

        TEST_METHOD_SETUP(MethodInit)
        {
            LicenseInstaller::InstallCallback = {};
            m_requestedFiles.clear();
            m_installResult = S_OK;
            m_ownsDirectory = false;

            m_licensePath = ::Test::FileSystem::GetModulePath(wil::GetModuleInstanceHandle()) / L"MSIX";
            if (!std::filesystem::create_directory(m_licensePath))
            {
                VERIFY_FAIL(L"The test requires a fresh MSIX directory beside its module.");
                return false;
            }
            m_ownsDirectory = true;
            LicenseInstaller::InstallCallback = [this](PCWSTR filename)
            {
                m_requestedFiles.emplace_back(filename);
                return m_installResult;
            };
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            LicenseInstaller::InstallCallback = {};
            if (!m_ownsDirectory)
            {
                return true;
            }

            std::error_code error;
            std::filesystem::remove_all(m_licensePath, error);
            m_ownsDirectory = false;
            VERIFY_ARE_EQUAL(0, error.value());
            return !error;
        }

        TEST_METHOD(InstallsMatchingLicenseFiles)
        {
            VERIFY_SUCCEEDED(MsixInstallLicenses());
            VERIFY_IS_TRUE(m_requestedFiles.empty());

            CreateFiles({ L"main_license.xml", L"singleton_license.xml", L"unrelated.xml" });
            VERIFY_IS_TRUE(std::filesystem::create_directory(m_licensePath / L"directory_license.xml"));

            VERIFY_SUCCEEDED(MsixInstallLicenses());
            VERIFY_ARE_EQUAL(size_t{ 2 }, m_requestedFiles.size());
            VERIFY_IS_TRUE(std::find(m_requestedFiles.begin(), m_requestedFiles.end(), m_licensePath / L"main_license.xml") != m_requestedFiles.end());
            VERIFY_IS_TRUE(std::find(m_requestedFiles.begin(), m_requestedFiles.end(), m_licensePath / L"singleton_license.xml") != m_requestedFiles.end());
        }

        TEST_METHOD(StopsAfterInstallerFailure)
        {
            CreateFiles({ L"main_license.xml", L"singleton_license.xml" });
            m_installResult = E_ACCESSDENIED;

            VERIFY_ARE_EQUAL(E_ACCESSDENIED, MsixInstallLicenses());
            VERIFY_ARE_EQUAL(size_t{ 1 }, m_requestedFiles.size());
        }

    private:
        void CreateFiles(std::initializer_list<PCWSTR> filenames)
        {
            for (const auto filename : filenames)
            {
                std::ofstream file{ m_licensePath / filename };
                VERIFY_IS_TRUE(file.is_open());
                file << "test license";
                VERIFY_IS_TRUE(file.good());
            }
        }

        std::filesystem::path m_licensePath;
        std::vector<std::filesystem::path> m_requestedFiles;
        HRESULT m_installResult{};
        bool m_ownsDirectory{};
    };
}
