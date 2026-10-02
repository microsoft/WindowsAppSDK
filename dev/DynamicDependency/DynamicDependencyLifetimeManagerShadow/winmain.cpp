// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

const HRESULT WINDOWSAPPSDK_DDLM_SHUTDOWN{ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x8000) };
const HRESULT WINDOWSAPPSDK_DDLM_CALLER_TERMINATED{ MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x8001) };
const HRESULT WINDOWSAPPSDK_DDLM_CALLER_NOT_FOUND{ MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_ITF, 0x8002) };

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    // Usage: This.Exe <eventname>
    // where
    //     eventname = event name signaling we should quit. Syntax: "<processid>;<packagefullname>;<uniqueid>"

    // Parse the command line
    const auto commandLine{ GetCommandLineW() };
    RETURN_HR_IF_NULL(E_INVALIDARG, commandLine);
    int argc{};
    PWSTR* argv{ CommandLineToArgvW(commandLine, &argc) };
    RETURN_HR_IF_NULL(E_INVALIDARG, argv);
    wil::unique_hlocal argvBuffer{ argv };
    RETURN_HR_IF(E_INVALIDARG, argc < 2);
    PCWSTR eventName{ argv[1] };
    PWSTR endPtr{};
    uint32_t callerProcessId{ wcstoul(eventName, &endPtr, 10) };
    // We'll never have ProcessId=0
    RETURN_HR_IF_MSG(E_INVALIDARG, (callerProcessId == 0) || (endPtr == nullptr) || (*endPtr != L';'), "CommandLine=%ls", eventName);

    // Open the named event created by the process calling the Bootstrap API (the process that caused us to run)
    // If we can't it's because the process has terminated (or already called MddBootstrapShutdown())
    // so we have nothing to do and we're out.
    wil::unique_event_nothrow endOfTheLine;
    RETURN_HR_IF_MSG(WINDOWSAPPSDK_DDLM_CALLER_NOT_FOUND, !endOfTheLine.try_open(eventName), "DDLM EventName=%ls", eventName);

    // Open a handle to the calling process so we can watch for its termination
    // (in case the process terminates without calling MddBootstrapShutdown())
    wil::unique_handle callerProcessHandle{ OpenProcess(SYNCHRONIZE, FALSE, callerProcessId) };
    RETURN_LAST_ERROR_IF_NULL(callerProcessHandle);

    // Wait for our calling process to tell us to quit OR our calling process terminates.
    // Either way, we've served our purpose and should quit.
    HANDLE waitForHandles[]{ endOfTheLine.get(), callerProcessHandle.get() };
    auto rc{ WaitForMultipleObjects(ARRAYSIZE(waitForHandles), waitForHandles, FALSE, INFINITE) };
    if (rc == WAIT_OBJECT_0)
    {
        //TODO:Replace with Telemetry
        (void) LOG_HR_MSG(WINDOWSAPPSDK_DDLM_SHUTDOWN, "DDLM.Shutdown: %ls", eventName);
    }
    else if (rc == WAIT_OBJECT_0 + 1)
    {
        //TODO:Replace with Telemetry
        (void) LOG_HR_MSG(WINDOWSAPPSDK_DDLM_CALLER_TERMINATED, "DDLM.CallerTerminated: %ls", eventName);
    }
    else if (rc == WAIT_FAILED)
    {
        RETURN_LAST_ERROR_MSG("DDLM.Wait: %ls", eventName);
    }
    else
    {
        RETURN_HR_MSG(E_UNEXPECTED, "DDLM.Wait.Unexpected: %ls", eventName);
    }
    return 0;
}
