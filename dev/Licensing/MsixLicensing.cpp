// Copyright (c) Microsoft Corporation. All rights reserved.

#include "pch.h"

#include "msixlicensing.h"

#include <WindowsAppRuntime-License.h>

STDAPI MsixInstallLicenses() noexcept try
{
    //TODO
    // FOREACH file IN pkgdir\MSIX\*-license.xml
    //  InstallLicenseFile(file)
    return S_OK;
}
CATCH_RETURN();
