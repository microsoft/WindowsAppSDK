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

    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM1(ActivatedEventAdd, PDT_ProductAndServiceUsage, uint32_t processId);
    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM1(ActivatedEventRemove, PDT_ProductAndServiceUsage, uint32_t processId);

    DEFINE_COMPLIANT_MEASURES_EVENT_PARAM1(EnqueueRedirectionRequestId, PDT_ProductAndServiceUsage, GUID, requestId);
    DEFINE_COMPLIANT_MEASURES_EVENT(DequeueRedirectionRequestId, PDT_ProductAndServiceUsage);

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(ProcessRedirectionRequests, PDT_ProductAndServicePerformance);
        DEFINE_ACTIVITY_START(uint32_t processId, bool isCurrent) noexcept try
        {
            TraceLoggingClassWriteStart(
                ProcessRedirectionRequests,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingUInt32(processId, "processId"),
                TraceLoggingBool(isCurrent, "isCurrent"));
        }
        CATCH_LOG()

        DEFINE_TAGGED_COMPLIANT_MEASURES_EVENT_PARAM1(DequeueRedirectionRequest, PDT_ProductAndServicePerformance, GUID, requestId);
        DEFINE_TAGGED_COMPLIANT_MEASURES_EVENT_PARAM1(ActivatedEvent, PDT_ProductAndServicePerformance, GUID, requestId);
        DEFINE_TAGGED_COMPLIANT_MEASURES_EVENT_PARAM1(RequestCleanupEvent, PDT_ProductAndServicePerformance, GUID, requestId);
    END_ACTIVITY_CLASS();

    BEGIN_COMPLIANT_MEASURES_ACTIVITY_CLASS(QueueRequest, PDT_ProductAndServicePerformance)
        DEFINE_ACTIVITY_START(uint32_t processId, bool isCurrent, GUID requestId) noexcept try
        {
            TraceLoggingClassWriteStart(
                QueueRequest,
                _GENERIC_PARTB_FIELDS_ENABLED,
                TraceLoggingUInt32(processId, "processId"),
                TraceLoggingBool(isCurrent, "isCurrent"),
                TraceLoggingGuid(requestId, "requestId"));
        }
        CATCH_LOG()

        DEFINE_TAGGED_COMPLIANT_MEASURES_EVENT_PARAM1(InnerActivatedEvent, PDT_ProductAndServicePerformance, GUID, requestId);
    END_ACTIVITY_CLASS()

};
