// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Microsoft.Kozani.Package.PackageManager.g.h"

namespace winrt::Microsoft::Kozani::Package::implementation
{
    struct PackageManager : PackageManagerT<PackageManager>
    {
        PackageManager() = default;

        static winrt::Microsoft::Kozani::Package::PackageManager Open();
        void TODO_ReplaceMeWithRealContent();
    };
}
namespace winrt::Microsoft::Kozani::Package::factory_implementation
{
    struct PackageManager : PackageManagerT<PackageManager, implementation::PackageManager>
    {
    };
}
