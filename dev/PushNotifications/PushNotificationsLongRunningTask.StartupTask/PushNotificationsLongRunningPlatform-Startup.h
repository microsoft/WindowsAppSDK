// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <NotificationsLongRunningProcess_h.h>

#include <wil/com.h>
#include <wil/resource.h>
#include "Microsoft.RoApi.h"
#include "NotificationPlatformActivation.h"

inline bool isRetriableRpcError(HRESULT hr)
{
    return (hr == HRESULT_FROM_WIN32(EPT_S_NOT_REGISTERED)) ||
        (hr == HRESULT_FROM_WIN32(RPC_S_SERVER_UNAVAILABLE)) ||
        (hr == HRESULT_FROM_WIN32(RPC_S_CALL_FAILED)) ||
        (hr == HRESULT_FROM_WIN32(RPC_S_CALL_FAILED_DNE)) ||
        (hr == HRESULT_FROM_WIN32(RPC_S_UNKNOWN_IF));
}

inline HRESULT StartupNotificationsLongRunningPlatform()
{
    unsigned int retries = 0;
    HRESULT hr = S_OK;

    while (retries < 3)
    {
        try
        {
            ::Microsoft::RoApi::ClearRoActivateInstanceCache();
            NotificationPlatform::GetNotificationPlatform();
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
