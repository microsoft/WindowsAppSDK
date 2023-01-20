// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.KozaniAbbreviation.ManagerRuntimeAbbreviation.ManagerRuntimeManager.g.h"

namespace winrt::Microsoft::Kozani::ManagerRuntime::implementation
{
    struct ManagerRuntimeManager : ManagerRuntimeManagerT<ManagerRuntimeManager>
    {
        ManagerRuntimeManager() = default;

        static winrt::Microsoft::Kozani::ManagerRuntime::ManagerRuntimeManager Open();
        void TODO_ReplaceMeWithRealContent();
    };
}
namespace winrt::Microsoft::Kozani::ManagerRuntime::factory_implementation
{
    struct ManagerRuntimeManager : ManagerRuntimeManagerT<ManagerRuntimeManager, implementation::ManagerRuntimeManager>
    {
    };
}
