// Copyright (c) Microsoft Corporation. All rights reserved.

#include "pch.h"

#include "msixlicensing.h"

#include <WindowsAppRuntime-License.h>

STDAPI MsixInstallLicenses(
    UINT32 majorMinorVersion,
    PCWSTR versionTag) noexcept try
{
    // Licenses are only needed for Stable releases (versionTag=null or "")
    if (versionTag && (versionTag[0] != L'\0'))
    {
        return S_OK;
    }

    const UINT16 majorVersion{ HIWORD(majorMinorVersion) };
    const UINT16 minorVersion{ LOWORD(majorMinorVersion) };
    WCHAR packageFamilyName[PACKAGE_FAMILY_NAME_MAX_LENGTH + 1]{};
    wsprintf(packageFamilyName, L"Microsoft.WindowsAppRuntime.%hu.%hu_8wekyb3d8bbwe", majorVersion, minorVersion);

    // Find a framework package in the family (any will do)
    winrt::Windows::Management::Deployment::PackageManager packageManager;
    winrt::hstring currentUser;
    const auto c_packageTypes{ winrt::Windows::Management::Deployment::PackageTypes::Framework };
    for (auto package : packageManager.FindPackagesForUserWithPackageTypes(currentUser, packageFamilyName, c_packageTypes))
    {
        // Install the license(s)
        const auto packageId{ package.Id() };
        const auto packageFullName{ packageId.FullName() };
        RETURN_IF_FAILED(MsixInstallLicensesInPackage(packageFullName.c_str()));
        return S_OK;
    }

    // No framework package found in the family
    RETURN_HR_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), "PackageFamilyName:%ls", packageFamilyName);
}
CATCH_RETURN();

STDAPI MsixInstallLicensesInPackage(PCWSTR frameworkPackageFullName) noexcept try
{
    // Get the package's path
    //
    // NOTE: Use GetStagedPackagePathByFullName as don't care if the package is registered.
    //
    // NOTE: Don't use GetStagedPackagePathByFullName2 as we want the *install* location
    //       (not e.g. modifiable location). Plus Get...2() is new in 20H1 (too new for us)
    //       where Get...() exists down to Win81. In this case simplest is bestest.
    wil::unique_cotaskmem_string packagePathBufferDynamic;
    uint32_t packagePathLength{};
    const auto rc{ GetStagedPackagePathByFullName(frameworkPackageFullName, &packagePathLength, nullptr) };
    if (rc != ERROR_INSUFFICIENT_BUFFER)
    {
        RETURN_HR_MSG(HRESULT_FROM_WIN32(rc), "PackageFullName:%ls", frameworkPackageFullName);
    }
    auto packagePath{ wil::make_cotaskmem_string(nullptr, packagePathLength) };
    RETURN_IF_WIN32_ERROR(GetStagedPackagePathByFullName(frameworkPackageFullName, &packagePathLength, packagePath.get()));

    // Build path for licenses
    std::filesystem::path licensePath{ packagePath.get() };
    const auto c_packageRelativeLicensePath{ L"MSIX" };
    licensePath /= c_packageRelativeLicensePath;
    auto licenseFilespec{ licensePath };
    licenseFilespec /= L"*_license.xml";

    // Deploy the licenses (if any)
    ::Microsoft::Windows::ApplicationModel::Licensing::Installer licenseInstaller;
    WIN32_FIND_DATA findFileData{};
    wil::unique_hfind hfind{ FindFirstFileW(licenseFilespec.c_str(), &findFileData) };
    if (!hfind)
    {
        const auto lastError{ GetLastError() };
        RETURN_HR_IF_MSG(HRESULT_FROM_WIN32(lastError), (lastError != ERROR_FILE_NOT_FOUND) && (lastError != ERROR_PATH_NOT_FOUND),
                         "FindFirstFile:%ls", licenseFilespec.c_str());
        return S_OK;
    }
    for (;;)
    {
        // Install the license file
        auto licenseFilename{ licensePath };
        licenseFilename /= findFileData.cFileName;
        RETURN_IF_FAILED_MSG(licenseInstaller.InstallLicenseFile(licenseFilename.c_str()),
                             "LicenseFile:%ls", licenseFilename.c_str());

        // Next! (if any)
        if (!FindNextFileW(hfind.get(), &findFileData))
        {
            const auto lastError{ GetLastError() };
            RETURN_HR_IF(HRESULT_FROM_WIN32(lastError), lastError != ERROR_NO_MORE_FILES);
            break;
        }
    }
    return S_OK;
}
CATCH_RETURN()
