// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT license.

#pragma once

#include <WindowsAppRuntimeInsights.h>

DECLARE_TRACELOGGING_CLASS(DecimalTelemetryProvider,
    "Microsoft.WindowsAppSDK.DecimalTelemetry",
    // {a4ed7638-2f9b-4fdf-a06a-d6cd26ff309d}
    (0xa4ed7638, 0x2f9b, 0x4fdf, 0xa0, 0x6a, 0xd6, 0xcd, 0x26, 0xff, 0x30, 0x9d));

class DecimalTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TELEMETRY_CLASS(DecimalTelemetry, DecimalTelemetryProvider);

public:

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(ToDo, PDT_ProductAndServicePerformance);
    END_ACTIVITY_CLASS();
};
