// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

// HRESULT used for logging non-error related information for tracing and debugging purpose with LOG_HR_MSG wil logging macro. 
// According to https://learn.microsoft.com/en-us/windows/win32/com/codes-in-facility-itf, all the COM-defined FACILITY_ITF codes have a code value 
// in the range of 0x0000-0x01FF. It is recommended that only code values in the range of 0x0200-0xFFFF be used for 3rd party FACILITY_ITF codes.

// Success HRESULT used for Kozani information logging purpose.
// 0x00040201 (262657)
constexpr HRESULT KOZANI_S_INFO{ MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_ITF, 0x0201) };

// Bad/malformatted PDU that cannot be parsed successfully.
// 0x80040202 (-2147220990)
constexpr HRESULT KOZANI_E_BAD_PDU{ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0202) };

// Unsupported ActivationKind enum value
// 0x80040203 (-2147220989)
constexpr HRESULT KOZANI_E_UNSUPPORTED_ACTIVATION_KIND{ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0203) };

// Bad/malformatted PDU that cannot be parsed successfully.
// 0x80040204 (-2147220988)
constexpr HRESULT KOZANI_E_PDU_SERIALIZATION{ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0204) };
