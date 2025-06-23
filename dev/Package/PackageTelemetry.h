// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>

DECLARE_TRACELOGGING_CLASS(PackageTelemetryProvider,
    "Microsoft.WindowsAppSDK.Package",
    // {95308938-292a-46ea-9ea4-4d729ab287a6}
    (0x95308938, 0x292a, 0x46ea, 0x9e, 0xa4, 0x4d, 0x72, 0x9a, 0xb2, 0x87, 0xa6));

class PackageTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(PackageTelemetry, PackageTelemetryProvider);

public:

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(FindPackageFile, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(winrt::hstring const& packageFullName, winrt::hstring const& filename) noexcept try
        {
            TraceLoggingClassWriteStart(
                FindPackageFile,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(packageFullName.c_str(), "PackageFullName"),
                TraceLoggingWideString(filename.c_str(), "Filename"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
};
