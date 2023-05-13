// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

// HRESULT used for logging non-error related information for tracing and debugging purpose with LOG_HR_MSG wil logging macro. 
// According to https://learn.microsoft.com/en-us/windows/win32/com/codes-in-facility-itf, all the COM-defined FACILITY_ITF codes have a code value 
// in the range of 0x0000-0x01FF. It is recommended that only code values in the range of 0x0200-0xFFFF be used for 3rd party FACILITY_ITF codes.

// HRESULT used for Kozani information logging purpose. Note that it does NOT mean there is an error. WIL logging requires a failure HRESULT as the input 
// to the LOG_HR_MSG() macro. Passing in a successful HRESULT to the macro will cause fail fast crash in Debug build, or it will log XS_STATUS_ASSERTION_FAILURE 
// in released build. So it has to be a failure HRESULT, although it does not mean failure in this case.
// 0x80040201 (-2147220991)
constexpr HRESULT KOZANI_E_INFO{ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0201) };

// Bad/malformatted PDU that cannot be parsed successfully.
// 0x80040202 (-2147220990)
constexpr HRESULT KOZANI_E_BAD_PDU{ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0202) };

// Unsupported ActivationKind enum value
// 0x80040203 (-2147220989)
constexpr HRESULT KOZANI_E_UNSUPPORTED_ACTIVATION_KIND{ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0203) };

// Bad/malformatted PDU that cannot be parsed successfully.
// 0x80040204 (-2147220988)
constexpr HRESULT KOZANI_E_PDU_SERIALIZATION{ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0204) };

#if RESULT_DIAGNOSTICS_LEVEL > 3

#define TRACELOGGING_FAILURE_CONTEXT(failure) \
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

#define TRACELOGGING_FAILURE_CONTEXT(failure) \
    TraceLoggingHResult(failure.hr, "HResult"), \
    TraceLoggingString(failure.pszFile, "File"), \
    TraceLoggingUInt32(failure.uLineNumber, "LineNumber"), \
    TraceLoggingWideString(failure.pszMessage, "Message") \

#endif

template<typename TProvider> void TraceFailureFromProvider(const wil::FailureInfo& failure) WI_NOEXCEPT
{
    if (failure.hr == KOZANI_E_INFO)
    {
        TraceLoggingWrite(
            TProvider::Provider(),
            "Info",
            TRACELOGGING_FAILURE_CONTEXT(failure));
    }
    else
    {
        TraceLoggingWrite(
            TProvider::Provider(),
            "Failure",
            TRACELOGGING_FAILURE_CONTEXT(failure));
    }
}
