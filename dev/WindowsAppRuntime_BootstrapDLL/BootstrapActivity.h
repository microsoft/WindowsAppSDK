// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"
#include "tracelogging.h"

namespace WindowsAppRuntime::Bootstrap::Activity
{
    class Context
    {
        GUID m_lifetimeActivityId{};
        WindowsAppRuntimeBootStrap_TraceLogger::Initialize m_bootstrapInitializeActivity;
        WindowsAppRuntimeBootStrap_TraceLogger::Shutdown m_bootstrapShutdownActivity;

    public:
        Context()
        {
            std::ignore = CoCreateGuid(&m_lifetimeActivityId);
        }

        static WindowsAppRuntime::Bootstrap::Activity::Context& Get();

        WindowsAppRuntimeBootStrap_TraceLogger::Initialize GetInitializeActivity()
        {
            return m_bootstrapInitializeActivity;
        }

        WindowsAppRuntimeBootStrap_TraceLogger::Shutdown GetShutdownActivity()
        {
            return m_bootstrapShutdownActivity;
        }
    };

    static WindowsAppRuntime::Bootstrap::Activity::Context g_bootstrapActivityContext;

    WindowsAppRuntime::Bootstrap::Activity::Context& WindowsAppRuntime::Bootstrap::Activity::Context::Get()
    {
        return g_bootstrapActivityContext;
    }
}
