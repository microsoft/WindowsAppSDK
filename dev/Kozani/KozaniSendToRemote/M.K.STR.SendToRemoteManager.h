// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.Kozani.SendToRemote.SendToRemoteManager.g.h"

namespace winrt::Microsoft::Kozani::SendToRemote::implementation
{
    struct SendToRemoteManager : SendToRemoteManagerT<SendToRemoteManager>
    {
        SendToRemoteManager() = default;

        static winrt::Microsoft::Kozani::SendToRemote::SendToRemoteManager Open();
        void TODO_ReplaceMeWithRealContent();
    };
}
namespace winrt::Microsoft::Kozani::SendToRemote::factory_implementation
{
    struct SendToRemoteManager : SendToRemoteManagerT<SendToRemoteManager, implementation::SendToRemoteManager>
    {
    };
}
