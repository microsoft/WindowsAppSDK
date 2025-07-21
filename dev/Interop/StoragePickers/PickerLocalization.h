// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

namespace PickerLocalization {
    winrt::hstring GetStoragePickersLocalizationText(winrt::hstring key, winrt::hstring fallback);
    
    bool IsInFrameworkPackage(winrt::hstring& frameworkPackageInstallLocation);
}

