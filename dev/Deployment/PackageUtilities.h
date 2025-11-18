// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <windows.h>
#include <appmodel.h>
#include <string>
#include <vector>
#include <wil/result_macros.h>
#include <winrt/base.h>
#include <PackageInfo.h>

namespace WindowsAppRuntime::Deployment::Package
{
    std::wstring GetPackagePath(std::wstring const& packageFullName);

    std::vector<std::wstring> FindPackagesByFamily(std::wstring const& packageFamilyName);

    HRESULT VerifyPackage(const std::wstring& packageFamilyName, const PACKAGE_VERSION targetVersion, const std::wstring& packageIdentifier);

    MddCore::PackageInfo GetPackageInfoForPackage(std::wstring const& packageFullName);

    winrt::hstring GetCurrentFrameworkPackageFullName();
}
