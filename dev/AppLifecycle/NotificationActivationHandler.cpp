// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include "NotificationActivationHandler.h"

HRESULT STDMETHODCALLTYPE NotificationActivationHandler::Activate(LPCWSTR app, LPCWSTR args,
    [[maybe_unused]] NOTIFICATION_USER_INPUT_DATA const* data, [[maybe_unused]] ULONG count) noexcept
{
    try
    {
        return E_FAIL;
    }
    catch (...)
    {
        return winrt::to_hresult();
    }
}
