// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "PushNotificationReceivedEventArgs.h"
#include <winrt/Windows.ApplicationModel.Core.h>
#include "externs.h"

constexpr PCWSTR c_pushContractId = L"Windows.Push";

namespace winrt::Microsoft::Windows::PushNotifications
{
    static winrt::Windows::Foundation::IInspectable Deserialize(winrt::Windows::Foundation::Uri const& uri)
    {
        // Verify if the uri contains a background notification payload.
        // Otherwise, we expect to process the notification in a background task.
        std::wstring uriAsString{ uri.AbsoluteUri() };
        if (uriAsString._Starts_with(L"-payload:"))
        {
            // 10 = the size of "-payload:" + the starting character of the payload
            // 11 = 10 + the ending quote of the payload argument.
            std::wstring payloadString = uriAsString.substr(10, uriAsString.size() - 11);
            return winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(payloadString);
        }

        const DWORD receiveArgsTimeoutInMSec{ 2000 };
        THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_TIMEOUT), !GetWaitHandleForArgs().wait(receiveArgsTimeoutInMSec));
        return winrt::Windows::ApplicationModel::Core::CoreApplication::Properties().TryLookup(ACTIVATED_EVENT_ARGS_KEY).as<PushNotificationReceivedEventArgs>();
    }
}
