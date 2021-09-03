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
        for (auto const& pair : uri.QueryParsed())
        {
            if (pair.Name() == L"payload")
            {
                std::wstring payloadAsWstring{pair.Value()};
                return winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(payloadAsWstring);
            }
        }

        const DWORD receiveArgsTimeoutInMSec{ 2000 };
        THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_TIMEOUT), !GetWaitHandleForArgs().wait(receiveArgsTimeoutInMSec));
        return winrt::Windows::ApplicationModel::Core::CoreApplication::Properties().TryLookup(ACTIVATED_EVENT_ARGS_KEY).as<PushNotificationReceivedEventArgs>();
    }
}
