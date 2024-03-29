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
        wil::unique_event_nothrow endOfTheLine{ ::OpenEventW(SYNCHRONIZE, FALSE, eventName) };
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
