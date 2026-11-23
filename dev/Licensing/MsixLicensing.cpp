// Copyright (c) Microsoft Corporation and Contributors.

#include "pch.h"

#include "msixlicensing.h"

#include <WindowsAppRuntime-License.h>

STDAPI MsixInstallLicenses() noexcept try
{
    // The calling process may be unpackaged; locate licenses beside this runtime, not the caller.
    const auto runtimePath{ wil::GetModuleFileNameW<std::wstring>(wil::GetModuleInstanceHandle()) };
    const auto licensePath{ std::filesystem::path{ runtimePath }.parent_path() / L"MSIX" };
    const auto licenseFilespec{ licensePath / L"*_license.xml" };

    WIN32_FIND_DATAW findFileData{};
    wil::unique_hfind hfind{ FindFirstFileW(licenseFilespec.c_str(), &findFileData) };
    if (!hfind)
    {
        const auto lastError{ GetLastError() };
        RETURN_HR_IF_MSG(HRESULT_FROM_WIN32(lastError), (lastError != ERROR_FILE_NOT_FOUND) && (lastError != ERROR_PATH_NOT_FOUND),
                         "FindFirstFile:%ls", licenseFilespec.c_str());
        return S_OK;
    }

    ::Microsoft::Windows::ApplicationModel::Licensing::Installer licenseInstaller;
    do
    {
        if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
        {
            continue;
        }

        const auto licenseFilename{ licensePath / findFileData.cFileName };
        RETURN_IF_FAILED_MSG(licenseInstaller.InstallLicenseFile(licenseFilename.c_str()),
                             "LicenseFile:%ls", licenseFilename.c_str());
    } while (FindNextFileW(hfind.get(), &findFileData));

    const auto lastError{ GetLastError() };
    RETURN_HR_IF(HRESULT_FROM_WIN32(lastError), lastError != ERROR_NO_MORE_FILES);
    return S_OK;
}
CATCH_RETURN();
