// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

namespace winrt::Microsoft::ProjectReunion::implementation
{
    enum WnpErrors
    {
        WNP_E_NOT_CONNECTED = 0x880403E8L,
        WNP_E_RECONNECTING = 0x880403E9L,
        WNP_E_BIND_USER_BUSY = 0x880403FEL,
    };
}
