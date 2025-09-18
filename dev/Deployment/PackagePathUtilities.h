// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <string>
#include <windows.h>
#include <wil/resource.h>

namespace WindowsAppRuntime::Deployment
{
    /// @brief Utilities for package path operations
    class PackagePathUtilities
    {
    public:
        /// @brief Gets the package path, which is a fast and reliable way to check if the package is
        /// at least staged on the device, even without package query capabilities.
        /// @param packageFullName The full name of the package
        /// @return The package path, or empty string if package not found
        virtual std::wstring GetPackagePath(std::wstring const& packageFullName)
        {
            UINT32 pathLength{};
            const auto rc{ GetPackagePathByFullName(packageFullName.c_str(), &pathLength, nullptr) };
            if (rc == ERROR_NOT_FOUND)
            {
                return std::wstring();
            }
            else if (rc != ERROR_INSUFFICIENT_BUFFER)
            {
                THROW_WIN32(rc);
            }

            auto path{ wil::make_process_heap_string(nullptr, pathLength) };
            THROW_IF_WIN32_ERROR(GetPackagePathByFullName(packageFullName.c_str(), &pathLength, path.get()));
            return std::wstring{ path.get() };
        }
    };
}