// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include <wil/resource.h>
#include <wil/result_macros.h>
#include <WindowsAppRuntimeInsights.h>

class AppLifecycleTelemetry : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(AppLifecycleTelemetry, "Microsoft.Windows.AppLifecycle",
        // {129A9300-9EA3-40B1-922B-43D46349BB91}
        (0x129a9300, 0x9ea3, 0x40b1, 0x92, 0x2b, 0x43, 0xd4, 0x63, 0x49, 0xbb, 0x91));

public:
    DEFINE_COMPLIANT_MEASURES_EVENT(GetActivatedEventArgs, PDT_ProductAndServiceUsage);
    DEFINE_COMPLIANT_MEASURES_EVENT(RedirectActivationToAsync, PDT_ProductAndServiceUsage);
    DEFINE_COMPLIANT_MEASURES_EVENT(ActivationRegistrationManager, PDT_ProductAndServiceUsage);
    DEFINE_COMPLIANT_MEASURES_EVENT(Restart, PDT_ProductAndServiceUsage);
};
