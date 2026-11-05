// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#ifndef __WINDOWSAPPRUNTIME_LICENSE_H
#define __WINDOWSAPPRUNTIME_LICENSE_H

#include "pch.h"
#include <functional>

// Keep the test copy distinct from the runtime DLL linked by DeploymentTests.
#define MsixInstallLicenses TestMsixInstallLicenses

// Keep the production header guard so this test double cannot load the real licensing implementation.
namespace Test::Deployment
{
class LicenseInstaller
{
public:
    inline static std::function<HRESULT(PCWSTR)> InstallCallback;

    HRESULT InstallLicenseFile(PCWSTR filename)
    {
        return InstallCallback ? InstallCallback(filename) : E_UNEXPECTED;
    }
};
}

namespace Microsoft::Windows::ApplicationModel::Licensing
{
    using Installer = ::Test::Deployment::LicenseInstaller;
}

#endif // __WINDOWSAPPRUNTIME_LICENSE_H
