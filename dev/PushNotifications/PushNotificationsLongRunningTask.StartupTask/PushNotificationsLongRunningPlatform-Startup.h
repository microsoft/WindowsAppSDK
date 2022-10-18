// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <NotificationsLongRunningProcess_h.h>

#include <wil/com.h>
#include <wil/resource.h>
#include "../../Common/Microsoft.RoApi.h"

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

            // If supported, allow use of class registrations from less trusted sources.
            auto supportMarker{ wil::CoCreateInstanceNoThrow<ISupportAllowLowerTrustActivation>(CLSID_ActivationCapabilities) };
            if (supportMarker)
            {
                wil::CoCreateInstance<INotificationsLongRunningPlatform>(CLSID_NotificationsLongRunningPlatform, CLSCTX_LOCAL_SERVER |
                    CLSCTX_ALLOW_LOWER_TRUST_REGISTRATION);
            }
            else
            {
                // Even if we can't pass CLSCTX_ALLOW_LOWER_TRUST_REGISTRATION, we still want to attempt the activation.
                // This might fail to find the class when run elevated on a downlevel SKU, but it will work otherwise.
                wil::CoCreateInstance<INotificationsLongRunningPlatform>(CLSID_NotificationsLongRunningPlatform, CLSCTX_LOCAL_SERVER);
            }
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
