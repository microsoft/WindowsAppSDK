// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include "DeploymentActivityContext.h"
#include "Licensing.h"

using namespace winrt;

namespace WindowsAppRuntime::Deployment::Licensing
{
    // licenseFileSpec: This parameter specifies the file specification (e.g., path and pattern) for the license files to be retrieved.
    // licenseFiles: This is an output parameter that will be populated with the names of the license files found matching the specified file specification.
    HRESULT GetLicenseFiles(const std::wstring& licenseFileSpec, std::vector<std::wstring>& licenseFiles)
    {
        licenseFiles.clear();

        WIN32_FIND_DATA findFileData{};
        wil::unique_hfind hfind{ FindFirstFileW(licenseFileSpec.c_str(), &findFileData) };
        if (!hfind)
        {
            const auto lastError{ GetLastError() };
            RETURN_HR_IF_MSG(HRESULT_FROM_WIN32(lastError), (lastError != ERROR_FILE_NOT_FOUND) && (lastError != ERROR_PATH_NOT_FOUND),
                             "FindFirstFile:%ls", licenseFileSpec.c_str());
            return S_OK;
        }
        for (;;)
        {
            // Add the license file
            licenseFiles.push_back(findFileData.cFileName);

            // Next! (if any)
            if (!FindNextFileW(hfind.get(), &findFileData))
            {
                const auto lastError{ GetLastError() };
                RETURN_HR_IF(HRESULT_FROM_WIN32(lastError), lastError != ERROR_NO_MORE_FILES);
                break;
            }
        }
        return S_OK;
    }

    HRESULT InstallLicenses(
        const std::vector<std::wstring>& licenseFiles,
        const std::filesystem::path& licensePath,
        ILicenseInstaller& licenseInstaller,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext)
    {
        initializeActivityContext.Reset();
        initializeActivityContext.SetInstallStage(::WindowsAppRuntime::Deployment::Activity::DeploymentStage::InstallLicense);

        // Deploy the licenses (if any)
        for (const auto& licenseFileName : licenseFiles)
        {
            // Install the license file
            auto licenseFileFullName{ licensePath };
            licenseFileFullName /= licenseFileName;

            initializeActivityContext.SetCurrentResourceId(licenseFileFullName);

            RETURN_IF_FAILED_MSG(licenseInstaller.InstallLicenseFile(licenseFileFullName.c_str()),
                                 "LicenseFile:%ls", licenseFileFullName.c_str());
        }
        return S_OK;
    }
}
