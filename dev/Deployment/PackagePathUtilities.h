// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <string>

namespace WindowsAppRuntime::Deployment::PackagePathUtilities
{
    /// @brief Gets the package path, which is a fast and reliable way to check if the package is
    /// at least staged on the device, even without package query capabilities.
    /// @param packageFullName The full name of the package
    /// @return The package path, or empty string if package not found
    std::wstring GetPackagePath(std::wstring const& packageFullName);
}