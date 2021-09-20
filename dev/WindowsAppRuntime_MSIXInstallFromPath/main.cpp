// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <Microsoft.Utf8.h>

#include <filesystem>
#include <fstream>

void Help();
HRESULT JustDoIt(PCWSTR path) noexcept;
void AddPackageIfNecessary(PCWSTR path, const std::wstring& filename, const std::wstring& packageFullName);
HRESULT AddPackage(PCWSTR path, const std::wstring& filename);

void Help()
{
    wprintf(L"WindowsAppRuntime_MSIXInstallFromPath <path>\n"
            L"where:\n"
            L"  path = Path where Windows App SDK's MSIX packages can be found\n"
            L"           => Microsoft.WindowsAppRuntime.*.msix\n"
            L"           => Microsoft.WindowsAppRuntime.DDLM.*.msix\n"
            L"           => Microsoft.WindowsAppRuntime.Main.*.msix\n"
            L"           => Microsoft.WindowsAppRuntime.Singleton.*.msix\n");
}

HRESULT JustDoIt(PCWSTR path) noexcept try
{
    wprintf(L"path: %s\n", path);

    // Install packages
    auto fpath{ std::filesystem::path(path) };
    auto inventory{ fpath / L"msix.txt" };
    std::string lineUtf8;
    std::ifstream f{ inventory };
    while (getline(f, lineUtf8))
    {
        auto line{ Microsoft::Utf8::ToUtf16<std::wstring>(lineUtf8.c_str()) };
        auto offset{ line.find(L'=') };
        THROW_HR_IF_MSG(E_UNEXPECTED, offset == std::wstring::npos, "line:%s", lineUtf8.c_str());
        auto filename{ line.substr(0, offset) };
        THROW_HR_IF_MSG(E_UNEXPECTED, filename.empty(), "line:%s", lineUtf8.c_str());
        auto packageFullName{ std::wstring(line.c_str() + offset + 1) };
        THROW_HR_IF_MSG(E_UNEXPECTED, packageFullName.empty(), "line:%s", lineUtf8.c_str());

        AddPackageIfNecessary(path, filename, packageFullName);
    }

    return 0;
}
CATCH_RETURN();

void AddPackageIfNecessary(PCWSTR path, const std::wstring& filename, const std::wstring& packageFullName)
{
    wprintf(L"Path: %s\n", path);
    wprintf(L"Filename: %s\n", filename.c_str());
    wprintf(L"PackageFullName: %s\n", packageFullName.c_str());
    //TODO: is packageFullName already registered?
    auto hr{ AddPackage(path, filename) };
    if (FAILED(hr))
    {
        wprintf(L"AddPackage(): 0x%X Path:%ls Filename:%ls PackageFullName:%ls", hr, path, filename.c_str(), packageFullName.c_str());
        THROW_HR_MSG(hr, "Path:%ls Filename:%ls PackageFullName:%ls", path, filename.c_str(), packageFullName.c_str());
    }
}

HRESULT AddPackage(PCWSTR path, const std::wstring& filename)
{
    auto packagePath{ std::filesystem::path(path) / filename };
    auto packagePathUri{ winrt::Windows::Foundation::Uri(packagePath.c_str()) };
    winrt::Windows::Management::Deployment::PackageManager packageManager;
    auto options{ winrt::Windows::Management::Deployment::DeploymentOptions::None };
    auto deploymentResult{ packageManager.AddPackageAsync(packagePathUri, nullptr, options).get() };
    return deploymentResult.ExtendedErrorCode();
}

int wmain(int argc, wchar_t *argv[])
{
    printf("Hello\n");
    try
    {
        winrt::init_apartment();

        // Parse the command line
        int index{ 1 };
        for (; index < argc; ++index)
        {
            auto arg{ argv[index] };
            if ((CompareStringOrdinal(arg, -1, L"-?", -1, FALSE) == CSTR_EQUAL) ||
                (CompareStringOrdinal(arg, -1, L"--help", -1, FALSE) == CSTR_EQUAL))
            {
                Help();
                return ERROR_BAD_ARGUMENTS;
            }
            else
            {
                Help();
                return ERROR_BAD_ARGUMENTS;
            }
        }

        if (index >= argc)
        {
            Help();
            return ERROR_BAD_ARGUMENTS;
        }
        auto path{ argv[index++] };

        if (index < argc)
        {
            Help();
            return ERROR_BAD_ARGUMENTS;
        }

        return JustDoIt(path);
    }
    catch (...)
    {
        const auto e{ winrt::hresult_error(winrt::to_hresult(), winrt::take_ownership_from_abi) };
        const auto hr{ e.code() };
        const auto message{ e.message() };
        (void) LOG_HR_MSG(hr, "%ls", message.c_str());
        wprintf(L"%s", message.c_str());
        return hr;
    }
}
