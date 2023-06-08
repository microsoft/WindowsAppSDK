// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.Kozani.SendToLocal.SendToLocalManager.g.h"

namespace winrt::Microsoft::Kozani::SendToLocal::implementation
{
    struct SendToLocalManager : SendToLocalManagerT<SendToLocalManager>
    {
        SendToLocalManager() = default;

        static winrt::Microsoft::Kozani::SendToLocal::SendToLocalManager Open();
        void TODO_ReplaceMeWithRealContent();
    };
}
namespace winrt::Microsoft::Kozani::SendToLocal::factory_implementation
{
    struct SendToLocalManager : SendToLocalManagerT<SendToLocalManager, implementation::SendToLocalManager>
    {
    };
}
