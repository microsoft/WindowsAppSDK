// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "tracelogging.h"

namespace WindowsAppRuntime::MddBootstrap::Activity
{
    enum class DDLMFindMethod
    {
        None                = 0,
        ViaAppExtension     = 1,
        ViaAppEnumeration   = 2,
    };

    class Context
    {
        DDLMFindMethod m_ddlmFindMethodUsed{ WindowsAppRuntime::MddBootstrap::Activity::DDLMFindMethod::None };

        WindowsAppRuntimeBootstrap_TraceLogger::Initialize m_bootstrapInitializeActivity;
        WindowsAppRuntimeBootstrap_TraceLogger::Shutdown m_bootstrapShutdownActivity;

    public:
        static WindowsAppRuntime::MddBootstrap::Activity::Context& Get();

        void Reset()
        {
            m_ddlmFindMethodUsed = WindowsAppRuntime::MddBootstrap::Activity::DDLMFindMethod::None;
        }

        void SetDDLMFindMethodUsed(DDLMFindMethod ddlmFindMethodUsed)
        {
            m_ddlmFindMethodUsed = ddlmFindMethodUsed;
        }

        DDLMFindMethod& GetDDLMFindMethodUsed()
        {
            return m_ddlmFindMethodUsed;
        }

        WindowsAppRuntimeBootstrap_TraceLogger::Initialize GetInitializeActivity()
        {
            return m_bootstrapInitializeActivity;
        }

        WindowsAppRuntimeBootstrap_TraceLogger::Shutdown GetShutdownActivity()
        {
            return m_bootstrapShutdownActivity;
        }
    };

    static WindowsAppRuntime::MddBootstrap::Activity::Context g_bootstrapActivityContext;
}
