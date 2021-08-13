#include <windows.h>
#include "pch.h"

#include "../PushNotifications-Constants.h"

#include <NotificationsLongRunningProcess_h.h>
#include <wil/resource.h>

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    RETURN_IF_FAILED(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));

    auto scopeExit = wil::scope_exit(
        [&]() { CoUninitialize(); });

    try
    {
        wil::com_ptr<INotificationsLongRunningPlatform> longRunningProcessPlatform
            { wil::CoCreateInstance<NotificationsLongRunningPlatform, INotificationsLongRunningPlatform>(CLSCTX_LOCAL_SERVER) };
    }
    CATCH_RETURN()

    return 0;
}
