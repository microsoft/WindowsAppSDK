// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include <PackagePathUtilities.h>
#include <windows.h>
#include <wil/resource.h>

namespace WindowsAppRuntime::Deployment::PackagePathUtilities
{
    std::wstring GetPackagePath(std::wstring const& packageFullName)
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
}