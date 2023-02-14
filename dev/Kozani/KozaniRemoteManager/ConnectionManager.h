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
        ConnectionManager() = default;
        ~ConnectionManager() noexcept;

        void Connect(PCSTR connectionId);
        void ReportDvcServerError(HRESULT hr);

    private:
        void WaitForFailedDvcServerDeletionThread();

    private:
        bool m_isModuleObjectCountAdded{};

        // Do not use wil::srwlock as it does not support recursive locking, which may be needed in this object.
        std::recursive_mutex m_dvcServerLock;
        std::unique_ptr<KozaniDvcServer> m_dvcServer;
        std::unique_ptr<KozaniDvcServer> m_failedDvcServerToBeDeleted;

        std::thread m_failedDvcServerDeletionThread;
    };
}
