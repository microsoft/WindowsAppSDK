// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "KozaniRemoteManagerTraceLogging.h"
#include "KozaniDvcServer.h"

namespace Microsoft::Kozani::KozaniRemoteManager
{
    class ConnectionManager
    {
    public:
        friend class KozaniDvcServer;

        ConnectionManager() = default;
        ~ConnectionManager() noexcept;

        void Connect(PCSTR connectionId);
        void ReportDvcServerError(HRESULT hr);

    private:
        void WaitForFailedDvcServerDeletionThread();
        UINT64 GetNewActivityId();
        void ProcessAppTermination(AppActivationInfo* appActivationInfo);

    private:
        bool m_closing{};
        bool m_isModuleObjectCountAdded{};

        // Do not use wil::srwlock as it does not support recursive locking, which may be needed in this object.
        std::recursive_mutex m_dvcServerLock;
        std::unique_ptr<KozaniDvcServer> m_dvcServer;
        std::unique_ptr<KozaniDvcServer> m_failedDvcServerToBeDeleted;

        std::thread m_failedDvcServerDeletionThread;

        wil::srwlock m_newActivityIdLock;
        
        // New activity Id starts from 1. 0 means the activity Id is not set.
        UINT64 m_newActivityId{ 1 };

        std::map<UINT64, AppActivationInfo> m_activityMap;
        std::map<DWORD, UINT64> m_processIdMap;
        wil::srwlock m_activityMapLock;
    };
}
