// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "PushNotificationReceivedEventArgs.h"
#include <winrt/Windows.ApplicationModel.Core.h>
#include "externs.h"

constexpr PCWSTR c_pushContractId = L"Windows.Push";

using namespace winrt::Windows::ApplicationModel::Core;
namespace winrt::Microsoft::Windows::PushNotifications
{
    static winrt::Windows::Foundation::IInspectable Deserialize(winrt::Windows::Foundation::Uri const&)
    {
        if (WaitForSingleObject(g_waitHandleForArgs.get(), 2000) == WAIT_OBJECT_0)
        {
            auto appProperties = CoreApplication::Properties();
            if (auto foundActivatedEventArgs = appProperties.TryLookup(ACTIVATED_EVENT_ARGS_KEY))
            {
                return foundActivatedEventArgs.as<PushNotificationReceivedEventArgs>();
            }
            else
            {
                return nullptr;
            }
        }

        winrt::throw_hresult(HRESULT_FROM_WIN32(ERROR_TIMEOUT));
    }
}
