// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <WindowsAppRuntimeInsights.h>

//TODO #include <evntrace.h>
//TODO #include <wil/resultmacros.h>
//TODO #include <traceloggingprovider.h>

// Common adapter for writing tracelogging failures in Windows App SDK, use like this:
//
//  class MyTraceProvider : public wil::TraceLoggingProvider
//  {
//      // Microsoft.Windows.YourTraceName - 1ded4f74-xxxx-xxxx-xxxx-4fd4e9bbe0a7
//      IMPLEMENT_TRACELOGGING_CLASS(
//          MyTraceProvider,
//          "Microsoft.Windows.YourTraceName",
//          (0x1ded4f74, 0xxxxx, 0xxxxx, 0xxx, 0xxx, 0x4f, 0xd4, 0xe9, 0xbb, 0xe0, 0xa7));
//  };
//
// STDAPI_(BOOL) DllMain(_In_opt_ HINSTANCE, DWORD reason, LPVOID)
// {
//     if (reason == DLL_PROCESS_ATTACH)
//     {
//         wil::SetResultLoggingCallback(&TraceFailureFromProvider<MyTraceProvider>);
//     }
//
//     return TRUE;
// }

#if RESULT_DIAGNOSTICS_LEVEL > 3

#define WINDOWSAPPRUNTIME_WIL_TRACELOGGING_FAILURE_CONTEXT(failure) \
    TraceLoggingHResult(failure.hr, "HResult"), \
    TraceLoggingString(failure.pszFile, "File"), \
    TraceLoggingUInt32(failure.uLineNumber, "LineNumber"), \
    TraceLoggingString(failure.pszFunction, "Function"), \
    TraceLoggingWideString(failure.pszMessage, "Message"), \
    TraceLoggingString(failure.pszCallContext, "CallingContext"), \
    TraceLoggingString(failure.pszModule, "Module"), \
    TraceLoggingPointer(failure.returnAddress, "Site"), \
    TraceLoggingString(failure.pszCode, "Code") \

#else

#define WINDOWSAPPRUNTIME_WIL_TRACELOGGING_FAILURE_CONTEXT(failure) \
    TraceLoggingHResult(failure.hr, "HResult"), \
    TraceLoggingString(failure.pszFile, "File"), \
    TraceLoggingUInt32(failure.uLineNumber, "LineNumber"), \
    TraceLoggingWideString(failure.pszMessage, "Message") \

#endif


namespace WindowsAppRuntime::TraceLogging
{
namespace wil
{
template<typename TProvider> void TraceFailureFromProvider(const wil::FailureInfo& failure) WI_NOEXCEPT
{
    TraceLoggingWrite(
        TProvider::Provider(),
        "Failure",
        WINDOWSAPPRUNTIME_WIL_TRACELOGGING_FAILURE_CONTEXT(failure),
        _GENERIC_PARTB_FIELDS_ENABLED,
        TraceLoggingLevel(TRACE_LEVEL_ERROR));
}
}

class WindowsAppRuntime_TraceLogger final : public wil::TraceLoggingProvider
{
    IMPLEMENT_TRACELOGGING_CLASS(
        WindowsAppRuntime_TraceLogger,
        "Microsoft.WindowsAppRuntime",
        // {4991d8c7-4f22-4427-ab3a-16552f4077e0}
        (0x4991d8c7, 0x4f22, 0x4427, 0xab, 0x3a, 0x16, 0x55, 0x2f, 0x40, 0x77, 0xe0));
};
}
