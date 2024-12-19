// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once
#include "..\WindowsAppRuntime_Insights\WindowsAppRuntimeInsights.h"

class OAuth2ManagerTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS_WITH_MICROSOFT_TELEMETRY(OAuth2ManagerTelemetry, "Microsoft.WindowsAppSDK.OAuth2ManagerTelemetry",
        (0x27d8ee3f, 0xd704, 0x45d6, 0xb6, 0x6c, 0x1d, 0xad, 0x95, 0x79, 0x5c, 0xe5));
    //{27d8ee3f-d704-45d6-b66c-1dad95795ce5}
public:

    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM3(RequestAuthWithParamsAsyncTriggered, PDT_ProductAndServicePerformance,
        bool, IsAppPackaged, PCWSTR, AppName, PCWSTR, ResponseType);

    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM2(CompleteAuthRequestTriggered, PDT_ProductAndServiceUsage,
        bool, IsAppPackaged, PCWSTR, AppName);
    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM4(RequestTokenAsyncTriggered, PDT_ProductAndServiceUsage,
        bool, IsAppPackaged, PCWSTR, AppName, PCWSTR, GrantType, bool, IsClientAuthPassed);
};
