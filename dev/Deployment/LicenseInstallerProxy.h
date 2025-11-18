// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include "Licensing.h"
#include "WindowsAppRuntime-License.h"

namespace WindowsAppRuntime::Deployment::Licensing
{
    class LicenseInstallerProxy : public ::WindowsAppRuntime::Deployment::Licensing::ILicenseInstaller
    {
        ::Microsoft::Windows::ApplicationModel::Licensing::Installer& m_installer;

    public:
        LicenseInstallerProxy(::Microsoft::Windows::ApplicationModel::Licensing::Installer& installer) : m_installer(installer) {}

        HRESULT InstallLicenseFile(const std::wstring& licenseFilename) override
        {
            return m_installer.InstallLicenseFile(licenseFilename.c_str());
        }
    };
}
