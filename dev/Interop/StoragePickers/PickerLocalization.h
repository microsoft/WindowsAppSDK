// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "PickerCommon.h"

namespace PickerLocalization {
    winrt::hstring GetStoragePickersLocalizationText(winrt::hstring key, winrt::hstring fallback);
    
    bool IsInFrameworkPackage(winrt::hstring& frameworkPackageInstallLocation);
}

