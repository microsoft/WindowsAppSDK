// Copyright (c) Microsoft Corporation and Contributors.

#include "pch.h"

#include "msixlicensing.h"

#include <WindowsAppRuntime-License.h>

STDAPI MsixInstallLicenses() noexcept try
{
    //TODO
    // FOREACH file IN pkgdir\MSIX\*_license.xml
    //  InstallLicenseFile(file)
    return S_OK;
}
CATCH_RETURN();
