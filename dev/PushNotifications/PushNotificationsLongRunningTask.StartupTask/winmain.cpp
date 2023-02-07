// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <windows.h>
#include "pch.h"

#include "PushNotificationsLongRunningPlatform-Startup.h"

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    RETURN_IF_FAILED(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));

    auto scopeExit = wil::scope_exit(
        [&]() { CoUninitialize(); });

    return StartupNotificationsLongRunningPlatform();
}
