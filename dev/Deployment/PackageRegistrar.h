// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <string>
#include <filesystem>
#include <windows.h>
#include <DeploymentActivityContext.h>
#include <winrt/Windows.Management.Deployment.h>

namespace WindowsAppRuntime::Deployment::PackageRegistrar
{
    static constexpr PCWSTR c_deploymentAgentFilename{ L"DeploymentAgent.exe" };

    std::wstring GenerateDeploymentAgentPath();

    HRESULT AddOrRegisterPackage(
        const std::filesystem::path& path,
        const bool useExistingPackageIfHigherVersion,
        const bool forceDeployment,
        winrt::Windows::Management::Deployment::IPackageManager& packageManager,
        ::WindowsAppRuntime::Deployment::Activity::Context& activityContext);

    HRESULT AddOrRegisterPackageInBreakAwayProcess(
        const std::filesystem::path& path,
        const bool useExistingPackageIfHigherVersion,
        const bool forceDeployment,
        ::WindowsAppRuntime::Deployment::Activity::Context& activityContext,
        const std::wstring& deploymentAgentPath);
}
