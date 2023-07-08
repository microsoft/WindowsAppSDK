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

        ~ConnectionManager() noexcept;

        void Connect(_In_ PCSTR connectionId, _In_ IKozaniApplicationLauncher* appLauncher);
        void ReportDvcServerError(HRESULT hr);

    private:
        void WaitForFailedDvcServerDeletionThread();
        uint64_t GetNewActivityId();
        void ProcessAppTermination(AppActivationInfo* appActivationInfo);

    private:
        bool m_closing{};
        bool m_isModuleObjectCountAdded{};

        // Do not use wil::srwlock as it does not support recursive locking, which may be needed in this object.
        std::recursive_mutex m_dvcServerLock;
        std::unique_ptr<KozaniDvcServer> m_dvcServer;
        std::unique_ptr<KozaniDvcServer> m_failedDvcServerToBeDeleted;

        std::thread m_failedDvcServerDeletionThread;

        wil::srwlock m_nextActivityIdLock;
        
        // New activity Id starts from 1. 0 means the activity Id is not set.
        static const uint64_t c_activityId_Unknown{};
        uint64_t m_nextActivityId{ 1 };

        std::map<uint64_t, AppActivationInfo> m_activityMap;

        typedef uint64_t ActivityId;
        std::map<DWORD, ActivityId> m_processIdMap;

        wil::srwlock m_activityMapLock;
    };
}
