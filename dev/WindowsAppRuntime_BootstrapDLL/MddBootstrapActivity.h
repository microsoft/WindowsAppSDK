// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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
        unsigned int lineNumber;
        std::wstring message;
        std::string module;
    };

    class Context
    {
        MddBootstrapAPI m_mddBootstrapAPI{};
        WindowsAppRuntimeBootstrap_TraceLogger::Initialize m_bootstrapInitializeActivity;
        GUID m_bootstrapInitializeActivityId{};
        std::atomic<uint32_t> m_initializationCount;
        wil::unique_cotaskmem_string m_initializationPackageFullName;
        WindowsAppRuntimeBootstrap_TraceLogger::Shutdown m_bootstrapShutdownActivity;
        GUID m_bootstrapShutdownActivityId{};
        WilFailure m_lastFailure{};
        bool m_stopActivityForWilReturnHR{};

    public:
        static WindowsAppRuntime::MddBootstrap::Activity::Context& Get();

        static const WindowsAppRuntime::MddBootstrap::Activity::IntegrityFlags GetIntegrityFlags(HANDLE token = nullptr);

        const MddBootstrapAPI& GetMddBootstrapAPI() const
        {
            return m_mddBootstrapAPI;
        }

        const uint32_t GetInitializeCount() const
        {
            return m_initializationCount;
        }

        const uint32_t GetInitializeData(PCWSTR& initializationPackageFullName) const
        {
            initializationPackageFullName = m_initializationPackageFullName.get();
            return GetInitializeCount();
        }

        wil::unique_cotaskmem_string& GetInitializationPackageFullName()
        {
            return m_initializationPackageFullName;
        }

        WindowsAppRuntimeBootstrap_TraceLogger::Initialize& GetInitializeActivity()
        {
            return m_bootstrapInitializeActivity;
        }

        WindowsAppRuntimeBootstrap_TraceLogger::Shutdown& GetShutdownActivity()
        {
            return m_bootstrapShutdownActivity;
        }

        const WilFailure& GetLastFailure() const
        {
            return m_lastFailure;
        }

        const bool& ShouldStopActivityForWilReturnHR() const
        {
            return m_stopActivityForWilReturnHR;
        }

        const GUID* GetSavedInitializeActivityId() const
        {
            return &m_bootstrapInitializeActivityId;
        }

        const GUID* GetSavedShutdownActivityId() const
        {
            return &m_bootstrapShutdownActivityId;
        }

        void SetMddBootstrapAPI(MddBootstrapAPI mddBootstrapAPI)
        {
            m_mddBootstrapAPI = mddBootstrapAPI;
        }

        uint32_t IncrementInitializationCount()
        {
            return ++m_initializationCount;
        }

        void DecrementInitializationCount();

        void SetLastFailure(const wil::FailureInfo& failure);

        void SetInitializationPackageFullName(PWSTR initializationPackageFullName)
        {
            if (initializationPackageFullName)
            {
                auto packageFullName{ wil::make_cotaskmem_string(initializationPackageFullName) };
                m_initializationPackageFullName = std::move(packageFullName);
            }
            else
            {
                m_initializationPackageFullName.reset();
            }
        }

        void StopActivityForWilReturnHR(const bool stopActivityForWilReturnHR)
        {
            m_stopActivityForWilReturnHR = stopActivityForWilReturnHR;
        }

        void SaveInitializeActivityId(const GUID bootstrapInitializeActivityId)
        {
            m_bootstrapInitializeActivityId = bootstrapInitializeActivityId;
        }

        void SaveShutdownActivityId(const GUID bootstrapShutdownActivityId)
        {
            m_bootstrapShutdownActivityId = bootstrapShutdownActivityId;
        }
    };

    static WindowsAppRuntime::MddBootstrap::Activity::Context g_bootstrapActivityContext;
}
