// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <winrt/base.h>
#include <NotificationActivationCallback.h>

class __declspec(uuid("32EABF70-F9CC-4142-BFE6-F8D237B5FE0F")) NotificationActivationHandler :
    public winrt::implements<NotificationActivationHandler, INotificationActivationCallback>
{
    HRESULT STDMETHODCALLTYPE Activate(LPCWSTR app, LPCWSTR args, [[maybe_unused]] NOTIFICATION_USER_INPUT_DATA const* data,
        [[maybe_unused]] ULONG count) noexcept final;
};
