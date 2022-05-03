// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <filesystem>
#include <fstream>

#include <PushNotificationsLongRunningPlatform-Startup.h>
void Help();
HRESULT JustDoIt(PCWSTR path, bool forceDeployment) noexcept;
void AddPackageIfNecessary(PCWSTR path, const std::wstring& filename, const std::wstring& packageFullName, bool forceDeployment);
bool NeedToRegisterPackage(const std::wstring& packageFullName);
bool NeedToRegisterPackage(PCWSTR packageFullName);
HRESULT AddPackage(PCWSTR path, const std::wstring& filename, bool forceDeployment);

class PackageId
{
public:
    static PackageId FromPackageFullName(const std::wstring& packageFullName)
    {
        return FromPackageFullName(packageFullName.c_str());
    }

    static PackageId FromPackageFullName(PCWSTR packageFullName)
    {
        PackageId packageId;
        uint32_t bufferLength{ sizeof(packageId.m_buffer) };
        THROW_IF_WIN32_ERROR(PackageIdFromFullName(packageFullName, PACKAGE_INFORMATION_BASIC, &bufferLength, packageId.m_buffer));
        packageId.m_packageId = reinterpret_cast<PACKAGE_ID*>(packageId.m_buffer);
        packageId.m_packageFullName = packageFullName;
        return packageId;
    }

    PackageId() = default;

    PackageId(PackageId&& other) :
        m_packageFullName(std::move(other.m_packageFullName))
    {
        memcpy(m_buffer, other.m_buffer, sizeof(m_buffer));
        m_packageId = reinterpret_cast<PACKAGE_ID*>(m_buffer);

        other.m_packageId = nullptr;
        memset(other.m_buffer, 0, sizeof(other.m_buffer));
    }

    ~PackageId() = default;

    PackageId& operator=(PackageId&& other)
    {
        if (this != &other)
        {
            m_packageFullName = std::move(other.m_packageFullName);
            memcpy(m_buffer, other.m_buffer, sizeof(m_buffer));
            m_packageId = reinterpret_cast<PACKAGE_ID*>(m_buffer);

            other.m_packageId = nullptr;
            memset(other.m_buffer, 0, sizeof(other.m_buffer));
        }
        return *this;
    }

    const std::wstring& PackageFullName() const
    {
        return m_packageFullName;
    }

    PCWSTR Name() const
    {
        return m_packageId->name;
    }

    PACKAGE_VERSION Version() const
    {
        return m_packageId->version;
    }

    winrt::Windows::System::ProcessorArchitecture Architecture() const
    {
        return static_cast<winrt::Windows::System::ProcessorArchitecture>(m_packageId->processorArchitecture);
    }

    PCWSTR ResourceId() const
    {
        return m_packageId->resourceId;
    }

    PCWSTR PublisherId() const
    {
        return m_packageId->publisherId;
    }

    PCWSTR PackageFamilyName() const
    {
        if (m_packageFamilyName.empty())
        {
            wchar_t packageFamilyName[PACKAGE_FAMILY_NAME_MAX_LENGTH + 1]{};
            uint32_t packageFamilyNameLength{ ARRAYSIZE(packageFamilyName) };
            THROW_IF_WIN32_ERROR_MSG(::PackageFamilyNameFromFullName(m_packageFullName.c_str(), &packageFamilyNameLength, packageFamilyName), "PackageFullName:%ls", m_packageFullName.c_str());
            m_packageFamilyName = packageFamilyName;
        }
        return m_packageFamilyName.c_str();
    }

    explicit operator bool() const
    {
        return m_packageId != nullptr;
    }

private:
    std::wstring m_packageFullName;
    mutable std::wstring m_packageFamilyName;
    const PACKAGE_ID * m_packageId{};
    BYTE m_buffer[sizeof(PACKAGE_ID) + (PACKAGE_NAME_MAX_LENGTH + 1 +
                                        PACKAGE_RESOURCEID_MAX_LENGTH + 1 +
                                        PACKAGE_PUBLISHERID_MAX_LENGTH + 1) * sizeof(WCHAR)]{};
};

void Help()
{
    wprintf(L"WindowsAppRuntime_MSIXInstallFromPath [options] <path>\n"
        L"options:\n"
        L"  -f, --force = Force shutdown WinAppSDK's processes if necessary to update WinAppSDK's MSIX packages\n"
        L"  -?, --help  = Display help\n"
        L"          --  = End of options\n"
        L"where:\n"
        L"  path = Path where Windows App SDK's MSIX packages can be found\n"
        L"           => Microsoft.WindowsAppRuntime.*.msix\n"
        L"           => Microsoft.WindowsAppRuntime.DDLM.*.msix\n"
        L"           => Microsoft.WindowsAppRuntime.Main.*.msix\n"
        L"           => Microsoft.WindowsAppRuntime.Singleton.*.msix\n");
}
HRESULT JustDoIt(PCWSTR path, bool forceDeployment) noexcept try
{
    wprintf(L"path: %s\n", path);

    // Install packages
    auto fpath{ std::filesystem::path(path) };
    auto inventory{ fpath / L"MSIX.inventory" };
    std::string lineUtf8;
    std::ifstream f{ inventory };
    
    THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), std::filesystem::exists(inventory), "%ls", inventory.c_str());

    while (getline(f, lineUtf8))
    {
        // Skip blank lines
        if (lineUtf8.empty())
        {
            continue;
        }

        // Skip comments
        if (lineUtf8[0] == '#')
        {
            continue;
        }

        // Parse the line
        auto line{ Microsoft::Utf8::ToUtf16<std::wstring>(lineUtf8.c_str()) };
        auto offset{ line.find(L'=') };
        THROW_HR_IF_MSG(E_UNEXPECTED, offset == std::wstring::npos, "line:%s", lineUtf8.c_str());
        auto filename{ line.substr(0, offset) };
        THROW_HR_IF_MSG(E_UNEXPECTED, filename.empty(), "line:%s", lineUtf8.c_str());
        auto packageFullName{ std::wstring(line.c_str() + offset + 1) };
        THROW_HR_IF_MSG(E_UNEXPECTED, packageFullName.empty(), "line:%s", lineUtf8.c_str());

        AddPackageIfNecessary(path, filename, packageFullName, forceDeployment);
    }

    // Restart Push Notifications Long Running Platform when ForceDeployment option is applied.
    if (forceDeployment)
    {
        // wil callback will be set up to log telemetry events for LRP.
        THROW_IF_FAILED_MSG(StartupNotificationsLongRunningPlatform(), "Restarting Push Notifications LRP failed after 3 attempts.");
    }

    return 0;
}
CATCH_RETURN();

void AddPackageIfNecessary(PCWSTR path, const std::wstring& filename, const std::wstring& packageFullName, bool forceDeployment)
{
    wprintf(L"Path: %s\n", path);
    wprintf(L"Filename: %s\n", filename.c_str());
    wprintf(L"PackageFullName: %s\n", packageFullName.c_str());
    wprintf(L"forceDeployment:%s\n", forceDeployment ?  "true" : "false");

    if (!NeedToRegisterPackage(packageFullName))
    {
        return;
    }

    auto hr{ AddPackage(path, filename, forceDeployment) };
    if (FAILED(hr))
    {
        wprintf(L"AddPackage(): 0x%X Path:%ls Filename:%ls PackageFullName:%ls forceDeployment:%s", hr, path, filename.c_str(), packageFullName.c_str(), forceDeployment ? "true" : "false");
        THROW_HR_MSG(hr, "Path:%ls Filename:%ls PackageFullName:%ls forceDeployment:%s", path, filename.c_str(), packageFullName.c_str(), forceDeployment ? "true" : "false");
    }
}

bool NeedToRegisterPackage(const std::wstring& packageFullName)
{
    return NeedToRegisterPackage(packageFullName.c_str());
}

bool NeedToRegisterPackage(PCWSTR packageFullName)
{
    auto packageId{ PackageId::FromPackageFullName(packageFullName) };

    // Is there an equal-or-better package already registered?
    wprintf(L"Family: %s\n", packageId.PackageFamilyName());
    auto packageFullNames{ AppModel::Package::FindByFamily(packageId.PackageFamilyName()) };
    if (packageFullNames.empty())
    {
        wprintf(L"1 None found\n");
        return true;
    }
    for (auto registeredPackageFullName : packageFullNames)
    {
        auto registeredPackage{ PackageId::FromPackageFullName(registeredPackageFullName) };
        wprintf(L"C %ls %ls %d %d %I64X %I64X\n",
            packageId.PackageFullName().c_str(), registeredPackage.PackageFullName().c_str(),
            packageId.Architecture(), registeredPackage.Architecture(),
            packageId.Version().Version, registeredPackage.Version().Version);
        if (registeredPackage.Architecture() != packageId.Architecture())
        {
            continue;
        }
        if (registeredPackage.Version().Version >= packageId.Version().Version)
        {
            continue;
        }

        // This registered package is equal-or-better than the specified package.
        // No need to register the specified package
        wprintf(L"2 %ls not-needed because %ls\n", packageFullName, registeredPackage.PackageFullName().c_str());
        return false;
    }

    // Nope. The specified package is better than anything current registered
    wprintf(L"3 Nothing better\n");
    return true;
}

HRESULT AddPackage(PCWSTR path, const std::wstring& filename, bool forceDeployment)
{
    const auto packagePath{ std::filesystem::path(path) / filename };
    const auto packagePathUri{ winrt::Windows::Foundation::Uri(packagePath.c_str()) };
    winrt::Windows::Management::Deployment::PackageManager packageManager;

    const auto options{ forceDeployment ?
            winrt::Windows::Management::Deployment::DeploymentOptions::ForceTargetApplicationShutdown :
            winrt::Windows::Management::Deployment::DeploymentOptions::None };
    auto deploymentResult{ packageManager.AddPackageAsync(packagePathUri, nullptr, options).get() };
    return deploymentResult.ExtendedErrorCode();
}

int wmain(int argc, wchar_t *argv[])
{
    try
    {
        winrt::init_apartment();

        bool forceDeployment{};

        // Parse the command line
        int index{ 1 };
        for (; index < argc; ++index)
        {
            auto arg{ argv[index] };
            if (arg[0] != L'-')
            {
                // Options are -o (short form) or --option (long form)
                break;
            }
            else if ((CompareStringOrdinal(arg, -1, L"--", -1, TRUE) == CSTR_EQUAL))
            {
                // -- = end of options
                ++index;
                break;
            }
            else if ((CompareStringOrdinal(arg, -1, L"-f", -1, TRUE) == CSTR_EQUAL) ||
                     (CompareStringOrdinal(arg, -1, L"--force", -1, TRUE) == CSTR_EQUAL))
            {
                forceDeployment = true;
            }
            else if ((CompareStringOrdinal(arg, -1, L"-?", -1, FALSE) == CSTR_EQUAL) ||
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

        return JustDoIt(path, forceDeployment);
    }
    catch (...)
    {
        const auto e{ winrt::hresult_error(winrt::to_hresult(), winrt::take_ownership_from_abi) };
        const auto hr{ e.code() };
        const auto message{ e.message() };
        (void) LOG_HR_MSG(hr, "%ls", message.c_str());
        wprintf(L"0x%X %s", hr.value, message.c_str());
        return hr;
    }
}
