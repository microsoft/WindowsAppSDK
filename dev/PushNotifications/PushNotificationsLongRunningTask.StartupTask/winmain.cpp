#include <windows.h>
#include "pch.h"

#include "../PushNotifications-Constants.h"

#include <NotificationsLongRunningProcess_h.h>
#include <wil/resource.h>

inline bool isRetriableRpcError(HRESULT hr)
{
    return (hr == HRESULT_FROM_WIN32(EPT_S_NOT_REGISTERED)) ||
        (hr == HRESULT_FROM_WIN32(RPC_S_SERVER_UNAVAILABLE)) ||
        (hr == HRESULT_FROM_WIN32(RPC_S_CALL_FAILED)) ||
        (hr == HRESULT_FROM_WIN32(RPC_S_CALL_FAILED_DNE)) ||
        (hr == HRESULT_FROM_WIN32(RPC_S_UNKNOWN_IF));
}

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    RETURN_IF_FAILED(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));

    auto scopeExit = wil::scope_exit(
        [&]() { CoUninitialize(); });

    unsigned int retries = 0;
    HRESULT hr = S_OK;

    while (retries < 3)
    {
        try
        {
            wil::com_ptr<INotificationsLongRunningPlatform> longRunningProcessPlatform
                { wil::CoCreateInstance<NotificationsLongRunningPlatform, INotificationsLongRunningPlatform>(CLSCTX_LOCAL_SERVER) };

            break;
        }
        catch (...)
        {
            hr = wil::ResultFromCaughtException();

            if (!isRetriableRpcError(hr))
            {
                break;
            }

            retries++;
        }
    }

    return hr;
}
