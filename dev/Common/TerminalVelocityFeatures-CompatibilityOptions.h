﻿// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// THIS FILE IS AUTOMATICALLY GENERATED; DO NOT EDIT IT

// INPUT FILE: .\dev\common\TerminalVelocityFeatures-CompatibilityOptions.xml
// OPTIONS: -Channel Experimental -Language C++ -Namespace Microsoft.Windows.ApplicationModel.WindowsAppRuntime -Path .\dev\common\TerminalVelocityFeatures-CompatibilityOptions.xml -Output dev\common\TerminalVelocityFeatures-CompatibilityOptions.h

#if defined(__midlrt)
namespace features
{
    feature_name Feature_CompatibilityOptions = { DisabledByDefault, FALSE };
}
#endif // defined(__midlrt)

// Feature constants
#define WINDOWSAPPRUNTIME_MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_FEATURE_COMPATIBILITYOPTIONS_ENABLED 1

#if defined(__cplusplus)

namespace Microsoft::Windows::ApplicationModel::WindowsAppRuntime
{

__pragma(detect_mismatch("ODR_violation_WINDOWSAPPRUNTIME_MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_FEATURE_COMPATIBILITYOPTIONS_ENABLED_mismatch", "AlwaysEnabled"))
struct Feature_CompatibilityOptions
{
    static constexpr bool IsEnabled() { return WINDOWSAPPRUNTIME_MICROSOFT_WINDOWS_APPLICATIONMODEL_WINDOWSAPPRUNTIME_FEATURE_COMPATIBILITYOPTIONS_ENABLED == 1; }
};

} // namespace Microsoft.Windows.ApplicationModel.WindowsAppRuntime

#endif // defined(__cplusplus)