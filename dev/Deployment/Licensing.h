// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include "DeploymentActivityContext.h"

namespace WindowsAppRuntime::Deployment::Licensing
{
    // Proxy/Wrapper for license installer. Open possibility to add more methods if needed.
    struct ILicenseInstaller
    {
        virtual HRESULT InstallLicenseFile(const std::wstring& licenseFilename) = 0;
    };

    // Get license files from the specified path pattern
    HRESULT GetLicenseFiles(const std::wstring& licenseFileSpec, std::vector<std::wstring>& licenseFiles);

    // Install license files
    HRESULT InstallLicenses(
        const std::vector<std::wstring>& licenseFiles,
        const std::filesystem::path& licensePath,
        ILicenseInstaller& licenseInstaller,
        ::WindowsAppRuntime::Deployment::Activity::Context& initializeActivityContext);
}
