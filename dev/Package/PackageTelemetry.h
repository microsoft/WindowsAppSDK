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

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(GetPackageFilePath, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(PCWSTR filename, GetPackageFilePathOptions options, PCWSTR packageFullName) noexcept try
        {
            TraceLoggingClassWriteStart(
                GetPackageFilePath,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(filename ? filename : L"<null>", "Filename"),
                TraceLoggingHexInt32(static_cast<std::uint32_t>(options), "Options"),
                TraceLoggingWideString(packageFullName ? packageFullName : L"<null>", "PackageFullName"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(GetPackageFilePathInPackageGraph, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(PCWSTR filename, GetPackageFilePathOptions options) noexcept try
        {
            TraceLoggingClassWriteStart(
                GetPackageFilePathInPackageGraph,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingWideString(filename ? filename : L"<null>", "Filename"),
                TraceLoggingHexInt32(static_cast<std::uint32_t>(options), "Options"));
        }
        CATCH_LOG()
    END_ACTIVITY_CLASS();
};
