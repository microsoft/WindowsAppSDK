// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <AppModel.PackageGraph.h>

#include "WindowsAppRuntime.VersionInfo.h"
#include "WindowsAppRuntime.SelfContained.h"

STDAPI WindowsAppRuntime_IsSelfContained(
    BOOL* isSelfContained) noexcept try
{
    *isSelfContained = FALSE;

    return S_OK;
}
CATCH_RETURN();
