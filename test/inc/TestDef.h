// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

constexpr static const int c_phaseTimeout = (30 * 1000); // 30 seconds
static const std::wstring c_genericTestMoniker = L"this_is_a_test";
static const std::wstring c_testFailureEventName = L"WindowsAppRuntimeTestFailureEventName";

static const std::wstring c_testProtocolScheme = L"windowsappruntimetestprotocol";
static const std::wstring c_testProtocolScheme_Packaged = L"windowsappruntimetestprotocol-packaged";
static const std::wstring c_testProtocolPhaseEventName = L"WindowsAppRuntimeTestProtocolPhaseEventName";

static const std::wstring c_testFileExtension = L".windowsappruntimetestfile";
static const std::wstring c_testFileExtension_Packaged = L".windowsappruntimetestfile-packaged";
static const std::wstring c_testFilePhaseEventName = L"WindowsAppRuntimeTestFilePhaseEventName";

static const std::wstring c_testStartupPhaseEventName = L"WindowsAppRuntimeTestStartupPhaseEventName";
static const std::wstring c_testInstanceRedirectedPhaseEventName = L"WindowsAppRuntimeTestInstanceRedirectedPhaseEventName";

static const std::wstring c_testRequestRestartNowPhaseEventName = L"WindowsAppRuntimeTestRequestRestartNowPhaseEventName";
static const std::wstring c_testRequestRestartNowRestartedPhaseEventName = L"WindowsAppRuntimeTestRequestRestartNowRestartedPhaseEventName";
static const std::wstring c_testRequestRestartNowRestartedPhasePackagedEventName = L"WindowsAppRuntimeTestRequestRestartNowRestartedPhasePackagedEventName";

static const std::wstring c_testPushPhaseEventName = L"WindowsAppRuntimeTestPushPhaseEventName";
inline IID c_remoteId = winrt::guid("A7652901-313C-4EFA-A303-95C371A00DAB");

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
