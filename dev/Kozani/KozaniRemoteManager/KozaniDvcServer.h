// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "KozaniRemoteManagerTraceLogging.h"

namespace Microsoft::Kozani::KozaniRemoteManager
{
    class ConnectionManager;

    class KozaniDvcServer
    {
    public:
        static KozaniDvcServer* Create();

        ~KozaniDvcServer();

        void SendConnectionAck(PCSTR connectionId);

        HRESULT SetConnectionManger(ConnectionManager* connectionManager);

    private:
        KozaniDvcServer() = default;

        void ProcessDvcIncomingData() noexcept;

        void OpenDvc();
        void StartDvcListenerThread();
        void DvcListenerThreadExiting(HRESULT errorCode, PCSTR erroMessage = "") noexcept;
        void SendDvcProtocolData(BYTE* data, UINT32 size);
        void ReportDvcWriterError(HRESULT errorCode);

    private:
        ConnectionManager* m_connectionManager{};
        wil::srwlock m_connectionManagerLock;
        std::recursive_mutex m_dvcLock;
        wil::unique_handle m_dvcHandle;
        wil::unique_event m_dvcThreadExit;
        wil::unique_event m_dvcThreadStarted;
        std::thread m_dvcListenerThread;
        HRESULT m_errorFromDvcListener{};
        HRESULT m_errorFromDvcWriter{};
    };
}
