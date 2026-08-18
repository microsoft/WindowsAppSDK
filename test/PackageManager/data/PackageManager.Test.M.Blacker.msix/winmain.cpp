// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    // Usage: This.Exe <eventname>
    // where
    //     eventname = event name signaling we should quit.

    // Parse the command line
    const auto commandLine{ GetCommandLineW() };
    int argc{};
    PWSTR* argv{ CommandLineToArgvW(commandLine, &argc) };
    RETURN_HR_IF_NULL(E_INVALIDARG, argv);
    if (argc >= 2)
    {
        PCWSTR eventName{ argv[1] };

        // OpenEventW can transiently fail to find the caller's event if this process starts
        // running before that event's CreateEventW() has fully landed system-wide (e.g. broker/
        // activation scheduling variance). A caller that relies on this process staying alive
        // until it's signaled -- e.g. to hold a package "in use" for a deployment test -- would
        // otherwise see this process exit almost instantly, with no visible symptom other than
        // "the thing I expected to happen didn't happen". Retry briefly instead of failing on the
        // very first attempt.
        wil::unique_event_nothrow endOfTheLine{ ::OpenEventW(SYNCHRONIZE, FALSE, eventName) };
        constexpr DWORD c_openEventRetryBudgetMilliseconds{ 5000 };
        constexpr DWORD c_openEventRetryIntervalMilliseconds{ 50 };
        for (DWORD elapsedMilliseconds = 0; !endOfTheLine && (elapsedMilliseconds < c_openEventRetryBudgetMilliseconds); elapsedMilliseconds += c_openEventRetryIntervalMilliseconds)
        {
            ::Sleep(c_openEventRetryIntervalMilliseconds);
            endOfTheLine.reset(::OpenEventW(SYNCHRONIZE, FALSE, eventName));
        }
        RETURN_LAST_ERROR_IF_NULL(endOfTheLine);

        auto rc{ WaitForSingleObject(endOfTheLine.get(), INFINITE) };
        if (rc != WAIT_OBJECT_0)
        {
            if (rc == WAIT_FAILED)
            {
                LOG_LAST_ERROR();
            }
            else
            {
                LOG_HR_MSG(E_UNEXPECTED, "%u", rc);
            }
            return rc;
        }
    }
    return 0;
}
