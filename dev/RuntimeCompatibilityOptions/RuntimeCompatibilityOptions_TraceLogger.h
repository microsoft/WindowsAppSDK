// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include <../WindowsAppRuntime_Insights/WindowsAppRuntimeInsights.h>

class RuntimeCompatibilityOptions_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        RuntimeCompatibilityOptions_TraceLogger,
        "Microsoft.WindowsAppRuntime.RuntimeCompatibilityOptions",
        // {1741c54b-ba96-4540-867b-29830307d0cc}
        (0x1741c54b, 0xba96, 0x4540, 0x86, 0x7b, 0x29, 0x83, 0x03, 0x07, 0xd0, 0xcc));

public:

    DEFINE_COMPLIANT_CRITICAL_DATA_EVENT_PARAM1(
        ChangeDisabled,
        PDT_ProductAndServicePerformance,
        UINT32, changeId
    );

    DEFINE_COMPLIANT_CRITICAL_DATA_EVENT_PARAM2(
        ApplyCalled,
        PDT_ProductAndServicePerformance,
        PCWSTR, patchLevel1,
        PCWSTR, patchLevel2
    );

    DEFINE_COMPLIANT_CRITICAL_DATA_EVENT_PARAM2(
        ApplyFailed,
        PDT_ProductAndServicePerformance,
        HRESULT, hresult,
        PCWSTR, message
    );
};