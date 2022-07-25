// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "Class.g.h"

namespace winrt::$safeprojectname$::implementation
{
    struct Class : ClassT<Class>
    {
        Class() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::$safeprojectname$::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
