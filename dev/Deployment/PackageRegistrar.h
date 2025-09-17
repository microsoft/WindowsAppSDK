// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <string>
#include <filesystem>
#include <windows.h>

namespace winrt::Microsoft::Windows::ApplicationModel::WindowsAppRuntime::implementation
{
    static PCWSTR c_deploymentAgentFilename{ L"DeploymentAgent.exe" };

    /// @brief Handles package registration operations including both direct registration and breakaway process registration
    class PackageRegistrar
    {
    public:
        /// @brief Registers or adds a package using PackageManager API
        /// @param path Path to the package or manifest file
        /// @param useExistingPackageIfHigherVersion If false, adds the current version package. If true, registers the higher version package using the path as manifest path
        /// @param forceDeployment Whether to force deployment (will shutdown target application if needed)
        /// @return HRESULT indicating success or failure
        /// @remarks This requires the 'packageManagement' or 'runFullTrust' capabilities
        static HRESULT AddOrRegisterPackage(const std::filesystem::path& path, const bool useExistingPackageIfHigherVersion, const bool forceDeployment);

        /// @brief Registers or adds a package using a breakaway process (for processes with package identity)
        /// @param path Path to the package or manifest file
        /// @param useExistingPackageIfHigherVersion If false, adds the current version package. If true, registers the higher version package using the path as manifest path
        /// @param forceDeployment Whether to force deployment (will shutdown target application if needed)
        /// @return HRESULT indicating success or failure
        /// @warning This function is ONLY for processes with package identity. It's the caller's responsibility to ensure this.
        static HRESULT AddOrRegisterPackageInBreakAwayProcess(const std::filesystem::path& path, const bool useExistingPackageIfHigherVersion, const bool forceDeployment);

    private:
        /// @brief Generates the path to the deployment agent executable
        /// @return Path to the deployment agent
        static std::wstring GenerateDeploymentAgentPath();
    };
}