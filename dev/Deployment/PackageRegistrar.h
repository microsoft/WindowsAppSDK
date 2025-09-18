// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <string>
#include <filesystem>
#include <windows.h>
#include <DeploymentActivityContext.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    static PCWSTR c_deploymentAgentFilename{ L"DeploymentAgent.exe" };

    class PackageRegistrar
    {
    public:
        static HRESULT AddOrRegisterPackage(
            const std::filesystem::path& path,
            const bool useExistingPackageIfHigherVersion,
            const bool forceDeployment,
            winrt::Windows::Management::Deployment::IPackageManager& packageManager,
            ::WindowsAppRuntime::Deployment::Activity::Context& activityContext);

        static HRESULT AddOrRegisterPackageInBreakAwayProcess(
            const std::filesystem::path& path,
            const bool useExistingPackageIfHigherVersion,
            const bool forceDeployment,
            ::WindowsAppRuntime::Deployment::Activity::Context& activityContext,
            const std::wstring& deploymentAgentPath = GenerateDeploymentAgentPath());

        static std::wstring GenerateDeploymentAgentPath();
    };
}