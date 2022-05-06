// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

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
