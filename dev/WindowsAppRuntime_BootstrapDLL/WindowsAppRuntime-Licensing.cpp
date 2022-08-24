// Copyright (c) Microsoft Corporation.

#include "pch.h"

#include "WindowsAppRuntime-Licensing.h"

#include <msixlicensing.h>

STDAPI WindowsAppRuntime_InstallLicenses() noexcept try
{
    RETURN_IF_FAILED(MsixInstallLicenses());
    return S_OK;
}
CATCH_RETURN();
