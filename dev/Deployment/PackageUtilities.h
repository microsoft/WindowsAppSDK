// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <windows.h>
#include <appmodel.h>
#include <string>
#include <vector>
#include <wil/result_macros.h>

namespace WindowsAppRuntime::Deployment::Package
{
    /// @brief Gets the package path, which is a fast and reliable way to check if the package is
    /// at least staged on the device, even without package query capabilities.
    /// @param packageFullName The full name of the package
    /// @return The package path, or empty string if package not found
    std::wstring GetPackagePath(std::wstring const& packageFullName);

    /// @brief Finds all packages registered for a given package family name
    /// @param packageFamilyName The package family name to search for
    /// @return Vector of package full names, or empty vector if none found
    std::vector<std::wstring> FindPackagesByFamily(std::wstring const& packageFamilyName);

    /// @brief Verifies if a package with the specified version or higher is available
    /// @param packageFamilyName The package family name to verify
    /// @param targetVersion The minimum required version
    /// @param packageIdentifier The package identifier for tracking
    /// @return S_OK if package is found with sufficient version, ERROR_NOT_FOUND otherwise
    HRESULT VerifyPackage(const std::wstring& packageFamilyName, const PACKAGE_VERSION targetVersion, const std::wstring& packageIdentifier);
}
