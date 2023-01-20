// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.Kozani.AppGraph.AppGraphManager.g.h"

namespace winrt::Microsoft::Kozani::AppGraph::implementation
{
    struct AppGraphManager : AppGraphManagerT<AppGraphManager>
    {
        AppGraphManager() = default;

        static winrt::Microsoft::Kozani::AppGraph::AppGraphManager Open();
        void TODO_ReplaceMeWithRealContent();
    };
}
namespace winrt::Microsoft::Kozani::AppGraph::factory_implementation
{
    struct AppGraphManager : AppGraphManagerT<AppGraphManager, implementation::AppGraphManager>
    {
    };
}
