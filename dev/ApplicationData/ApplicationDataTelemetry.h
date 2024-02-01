// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>

DECLARE_TRACELOGGING_CLASS(ApplicationDataTelemetryProvider,
    "Microsoft.WindowsAppSDK.Notifications.ApplicationDataTelemetry",
    // {cb014b10-5b3b-4117-a837-07b138bb519f}
    (0xcb014b10, 0x5b3b, 0x4117, 0xa8, 0x37, 0x07, 0xb1, 0x38, 0xbb, 0x51, 0x9f));

class ApplicationDataTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(ApplicationDataTelemetry, ApplicationDataTelemetryProvider);

public:

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(ClearMachineFolderAsync, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& path) noexcept try
        {
            TraceLoggingClassWriteStart(
                ClearMachineFolderAsync,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(path.c_str(), "Path"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
};
