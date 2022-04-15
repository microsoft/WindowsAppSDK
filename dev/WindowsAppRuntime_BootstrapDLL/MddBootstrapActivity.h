// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "MddBootstrapTracelogging.h"

namespace WindowsAppRuntime::MddBootstrap::Activity
{
    enum class MddBootstrapAPI
    {
        None = 0,
        Initialize = 1,
        Shutdown = 2,
    };

    enum class IntegrityFlags : uint32_t
    {
        None = 0,
        IsHighIL = 0x0001,
        IsMediumIL = 0x0002,
        IsLowIL = 0x0003,
        IsAppContainer = 0x0004,
    };
    DEFINE_ENUM_FLAG_OPERATORS(IntegrityFlags)

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
        MddBootstrapAPI m_mddBootstrapAPI{};
        WindowsAppRuntimeBootstrap_TraceLogger::Initialize m_bootstrapInitializeActivity;
        std::atomic<uint32_t> g_initializationCount;
        wil::unique_cotaskmem_string g_initializationPackageFullName;
        WindowsAppRuntimeBootstrap_TraceLogger::Shutdown m_bootstrapShutdownActivity;
        WilFailure m_lastFailure;

    public:
        static WindowsAppRuntime::MddBootstrap::Activity::Context& Get();

        static const WindowsAppRuntime::MddBootstrap::Activity::IntegrityFlags& GetIntegrityFlags(HANDLE token = nullptr);

        const MddBootstrapAPI& GetMddBootstrapAPI() const
        {
            return m_mddBootstrapAPI;
        }

        const uint32_t GetInitializeData(PWSTR& initializationPackageFullName) const
        {
            initializationPackageFullName = g_initializationPackageFullName.get();
            return g_initializationCount;
        }

        wil::unique_cotaskmem_string& GetInitializationPackageFullName()
        {
            return g_initializationPackageFullName;
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

        void SetMddBootstrapAPI(MddBootstrapAPI mddBootstrapAPI)
        {
            m_mddBootstrapAPI = mddBootstrapAPI;
        }

        void SetInitializeData()
        {
            ++g_initializationCount;
        }

        // Returns a boolean to indicate to the caller if MddBootstrap should be shutdown
        bool ShouldShutdownNow()
        {
            if (g_initializationCount > 1)
            {
                // Multiply initialized. Just decrement our count
                --g_initializationCount;
                return false;
            }
            else if (g_initializationCount == 0)
            {
                // Not initialized. Nothing to do
                return false;
            }
            return true;
        }

        void SetLastFailure(const wil::FailureInfo& failure);

        void SetShutdownData()
        {
            g_initializationPackageFullName = {};
            --g_initializationCount;
        }

        void SetInitializationPackageFullName(PWSTR initializationPackageFullName)
        {
            g_initializationPackageFullName.reset(initializationPackageFullName);
        }
    };

    static WindowsAppRuntime::MddBootstrap::Activity::Context g_bootstrapActivityContext;
}
