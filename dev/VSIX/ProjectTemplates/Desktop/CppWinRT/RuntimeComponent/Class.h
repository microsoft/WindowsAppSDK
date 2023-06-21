#pragma once

#include "Class.g.h"

namespace winrt::$safeprojectname$::implementation
{
    struct Class : ClassT<Class>
    {
        Class() = default;
    };
}

namespace winrt::$safeprojectname$::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
