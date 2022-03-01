// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "PushNotificationReceivedEventArgs.h"
#include <winrt/Windows.ApplicationModel.Core.h>
#include "externs.h"

constexpr PCWSTR c_pushContractId = L"Windows.Push";
constexpr PCWSTR c_appNotificationContractId = L"Windows.Toast";

namespace winrt::Microsoft::Windows::PushNotifications
{
    static winrt::Windows::Foundation::IInspectable PushDeserialize(winrt::Windows::Foundation::Uri const& uri)
    {
        // Verify if the uri contains a background notification payload.
        // Otherwise, we expect to process the notification in a background task.
        for (auto const& pair : uri.QueryParsed())
        {
            if (pair.Name() == L"payload")
            {
                // Convert escaped components to its normal content
                // from the conversion done in the LRP (see NotificationListener.cpp)
                std::wstring payloadAsEscapedWstring{ pair.Value() };
                std::wstring payloadAsWstring{ winrt::Windows::Foundation::Uri::UnescapeComponent(payloadAsEscapedWstring) };
                return winrt::make<winrt::Microsoft::Windows::PushNotifications::implementation::PushNotificationReceivedEventArgs>(payloadAsWstring);
            }
        }

        const DWORD receiveArgsTimeoutInMSec{ 2000 };
        THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_TIMEOUT), !GetWaitHandleForArgs().wait(receiveArgsTimeoutInMSec));

        // If COM static store was uninit, let it throw
        if (PushNotificationHelpers::IsPackagedAppScenario())
        {
            return winrt::Windows::ApplicationModel::Core::CoreApplication::Properties().Lookup(ACTIVATED_EVENT_ARGS_KEY);
        }
        else
        {
            // Need to mock a RawNotification object instead of winrt boxing: https://github.com/microsoft/WindowsAppSDK/issues/2075
            return winrt::Windows::ApplicationModel::Core::CoreApplication::Properties().Lookup(LRP_ACTIVATED_EVENT_ARGS_KEY);
        }
    }

    static winrt::Windows::Foundation::IInspectable ToastDeserialize(winrt::Windows::Foundation::Uri const& /* uri */)
    {
        const DWORD receiveArgsTimeoutInMSec{ 2000 };
        THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_TIMEOUT), !GetWaitHandleForArgs().wait(receiveArgsTimeoutInMSec));

        return winrt::Windows::ApplicationModel::Core::CoreApplication::Properties().Lookup(ACTIVATED_EVENT_ARGS_KEY);
    }
}
