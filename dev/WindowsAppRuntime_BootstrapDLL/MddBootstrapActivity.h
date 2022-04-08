// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "tracelogging.h"

namespace WindowsAppRuntime::MddBootstrap::Activity
{
    enum class MddBootStrapAPI
    {
        None = 0,
        Initialize = 1,
        Shutdown = 2,
    };

    enum class DDLMFindMethod
    {
        None                = 0,
        ViaAppExtension     = 1,
        ViaAppEnumeration   = 2,
    };

    struct WilFailure
    {
        wil::FailureType type;
        HRESULT hr;
        std::string file;
        unsigned int lineNumer;
        std::wstring message;
        std::string module;
    };

    class Context
    {
        MddBootStrapAPI m_mddBootStrapAPI{ MddBootStrapAPI::None };
        DDLMFindMethod m_ddlmFindMethodUsed{ DDLMFindMethod::None };

        WindowsAppRuntimeBootstrap_TraceLogger::Initialize m_bootstrapInitializeActivity;
        WindowsAppRuntimeBootstrap_TraceLogger::Shutdown m_bootstrapShutdownActivity;
        WilFailure m_lastFailure;

    public:
        static WindowsAppRuntime::MddBootstrap::Activity::Context& Get();

        void Reset()
        {
            m_ddlmFindMethodUsed = WindowsAppRuntime::MddBootstrap::Activity::DDLMFindMethod::None;
        }

        const MddBootStrapAPI& GetMddBootStrapAPI() const
        {
            return m_mddBootStrapAPI;
        }

        const DDLMFindMethod& GetDDLMFindMethodUsed() const
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

        const WilFailure& GetLastFailure() const
        {
            return m_lastFailure;
        }

        void SetMddBootStrapAPI(MddBootStrapAPI mddBootStrapAPI)
        {
            m_mddBootStrapAPI = mddBootStrapAPI;
        }

        void SetDDLMFindMethodUsed(DDLMFindMethod ddlmFindMethodUsed)
        {
            m_ddlmFindMethodUsed = ddlmFindMethodUsed;
        }

        void SetLastFailure(const wil::FailureInfo& failure);
    };

    static WindowsAppRuntime::MddBootstrap::Activity::Context g_bootstrapActivityContext;
}
