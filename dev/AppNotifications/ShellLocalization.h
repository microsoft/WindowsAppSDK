// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

// In this file we define methods that write/return Shell assets, like DisplayName and icon URI.

namespace Microsoft::Windows::AppNotifications::ShellLocalization
{
    const PCWSTR c_localWindowsAppSDKFolder{ LR"(Microsoft\WindowsAppSDK\)" };
    const PCWSTR c_pngExtension{ LR"(.png)" };

    struct AppNotificationAssets {
        std::wstring displayName;
        std::wstring iconFilePath;
    };

    HRESULT RetrieveAssetsFromProcess(_Out_ Microsoft::Windows::AppNotifications::ShellLocalization::AppNotificationAssets& assets) noexcept;

    HRESULT RetrieveAssetsFromShortcut(_Out_ Microsoft::Windows::AppNotifications::ShellLocalization::AppNotificationAssets& assets) noexcept;

    HRESULT DeleteIconFromCache() noexcept;

    bool IsIconFileExtensionSupported(std::filesystem::path const& iconFilePath);
}
