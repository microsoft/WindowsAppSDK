// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

constexpr static const int c_phaseTimeout = (30 * 1000); // 30 seconds
static const std::wstring c_genericTestMoniker = L"this_is_a_test";
static const std::wstring c_testFailureEventName = L"ReunionTestFailureEventName";

static const std::wstring c_testProtocolScheme = L"reuniontestprotocol";
static const std::wstring c_testProtocolScheme_Packaged = L"reuniontestprotocol-packaged";
static const std::wstring c_testProtocolPhaseEventName = L"ReunionTestProtocolPhaseEventName";

static const std::wstring c_testFileExtension = L".reuniontestfile";
static const std::wstring c_testFileExtension_Packaged = L".reuniontestfile-packaged";
static const std::wstring c_testFilePhaseEventName = L"ReunionTestFilePhaseEventName";

static const std::wstring c_testStartupPhaseEventName = L"ReunionTestStartupPhaseEventName";
static const std::wstring c_testInstanceRedirectedPhaseEventName = L"ReunionTestInstanceRedirectedPhaseEventName";

inline const winrt::hstring c_rawNotificationPayload = L"<toast></toast>";
inline IID c_comServerId = winrt::guid("ccd2ae3f-764f-4ae3-be45-9804761b28b2"); // Value from PushNotificationsTestAppPackage ComActivator in appxmanifest.
inline IID c_fakeComServerId = winrt::guid("00000000-0000-0000-0000-000000000001");

#ifndef WIDEN2
#define WIDEN2(x) L ## x
#endif

#ifndef WIDEN
#define WIDEN(x) WIDEN2(x)
#endif

#ifndef __WFILE__
#define __WFILE__ WIDEN(__FILE__)
#endif

#ifndef __WFUNCTION__
#if defined(_WIN32)
#define __WFUNCTION__ WIDEN(__FUNCTION__)
#else
#define __WFUNCTION__ L""
#endif
#endif

inline std::wstring StripNS(PCWSTR symbolAsString)
{
    std::wstring result{ symbolAsString };
    return result.substr(result.rfind(L':') + 1);
}

#define TESTNAME() \
    StripNS(__WFUNCTION__) \
