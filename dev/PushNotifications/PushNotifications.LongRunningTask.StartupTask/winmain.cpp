// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <windows.h>
#include "pch.h"
#include "../PushNotifications-Constants.h"
#include <NotificationsEndpoint_h.h>
#include <wil/resource.h>
#include <winrt/base.h>

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    wil::com_ptr<INotificationsReunionEndpoint> reunionEndpoint{
        wil::CoCreateInstance<NotificationsReunionEndpoint,
        INotificationsReunionEndpoint>(CLSCTX_LOCAL_SERVER) };
    return 0;
}
