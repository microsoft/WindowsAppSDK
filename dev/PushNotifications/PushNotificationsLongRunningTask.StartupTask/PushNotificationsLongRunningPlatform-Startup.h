// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <NotificationsLongRunningProcess_h.h>

#include <wil/com.h>
#include <wil/resource.h>

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
            wil::com_ptr<INotificationsLongRunningPlatform> platform;
            THROW_IF_FAILED(CoCreateInstance(CLSID_NotificationsLongRunningPlatform, nullptr, (CLSCTX_LOCAL_SERVER | CLSCTX_ALLOW_LOWER_TRUST_REGISTRATION), IID_PPV_ARGS(&platform)));
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
