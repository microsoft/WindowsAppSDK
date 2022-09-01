// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "pch.h"

namespace WindowsAppRuntimeInstallerTests
{
    wil::unique_handle Execute(const std::wstring& command, const std::wstring& args);
    HRESULT RunInstaller(const std::wstring& args=L"");
    void RemovePackage(const std::wstring& packageFullName, bool ignoreFailures=true);
    void TryRemoveProvisionedPackage(const std::wstring& packageFamilyName);
    void RemoveAllPackages(bool ignoreFailures=true);
    bool IsPackageRegistered(const std::wstring& packageFullName);
    winrt::Windows::System::ProcessorArchitecture GetSystemArchitecture();
    std::filesystem::path GetModulePath(HMODULE hmodule = nullptr);
    std::filesystem::path GetModuleFileName(HMODULE hmodule = nullptr);
    std::filesystem::path GetCommonRootPath();
    std::filesystem::path GetInstallerPath();
}
