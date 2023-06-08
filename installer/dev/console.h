// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

namespace WindowsAppRuntimeInstaller::Console
{
    void DisplayHeader();
    void DisplayHelp();
    void DisplayInfo();
    void DisplayError(const HRESULT hr);
}
