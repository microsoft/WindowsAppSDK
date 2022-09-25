// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __WINDOWSAPPRUNTIME_LICENSE_H
#define __WINDOWSAPPRUNTIME_LICENSE_H

namespace Microsoft::Windows::ApplicationModel::Licensing
{
    class Installer
    {
    public:
        Installer() = default;

        ~Installer() = default;

        HRESULT Open()
        {
            return S_OK;
        }

        void Close()
        {
        }

        HRESULT InstallLicense(HMODULE /*module*/, const std::wstring& /*licenseName*/)
        {
            return S_OK;
        }

        HRESULT InstallLicense(HMODULE /*module*/, PCWSTR /*licenseName*/)
        {
            return S_OK;
        }

        HRESULT InstallLicenses(HMODULE /*module*/, size_t /*licenseCount*/, PCWSTR* /*licenseNames*/)
        {
            return S_OK;
        }

        HRESULT InstallLicenseFile(const std::wstring& /*licenseFilename*/)
        {
            return S_OK;
        }

        HRESULT InstallLicenseFile(PCWSTR /*licenseFilename*/)
        {
            return S_OK;
        }

        HRESULT InstallLicenseFiles(size_t /*licenseCount*/, PCWSTR* /*licenseFilenames*/)
        {
            return S_OK;
        }
    };
}

#endif // __WINDOWSAPPRUNTIME_LICENSE_H
