// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "KozaniDvcProtocol.h"
#include "KozaniRemoteManagerTraceLogging.h"

namespace Microsoft::Kozani::KozaniRemoteManager
{
    class ConnectionManager;

    struct ActivatedAppInfo
    {
        DWORD pid;
    };

    class KozaniDvcServer
    {
    public:
        static KozaniDvcServer* Create();

        ~KozaniDvcServer();

        void SendConnectionAck(PCSTR connectionId);

        HRESULT SetConnectionManger(ConnectionManager* connectionManager);

    private:
        KozaniDvcServer() = default;

        HRESULT ProcessDvcIncomingData() noexcept;
        void ProcessDvcIncomingDataThreadFunc() noexcept;
        HRESULT ProcessDvcDataChunk(
            _In_reads_(size) const BYTE* data, 
            UINT32 size,
            _Inout_ bool& isPartialData,
            _Inout_ std::vector<BYTE>& pduBuffer,
            _Inout_ UINT32& pduSize,
            _Outptr_result_maybenull_  const BYTE** pdu) noexcept;

        HRESULT ProcessProtocolDataUnit(_In_reads_(size) const BYTE* data, UINT32 size) noexcept;

        void ProcessActivateAppRequestThreadFunc(_In_ Dvc::ProtocolDataUnit pdu) noexcept;
        HRESULT ProcessActivateAppRequest(_In_ Dvc::ProtocolDataUnit& pdu, _Out_ std::string& errorMessage) noexcept;

        bool IsActivationKindSupported(Dvc::ActivationKind kind);

        void RemoveActivity(UINT64 activityId);

        void OpenDvc();
        void StartDvcListenerThread();
        void DvcListenerThreadExiting(HRESULT errorCode, PCSTR erroMessage = "") noexcept;
        void ReportDvcWriterError(HRESULT errorCode);
        
        void SendDvcProtocolData(const char* data, UINT32 size);
        void SendActivateAppResult(
            UINT64 activityId,
            HRESULT hr,
            DWORD appProcessId,
            _In_ const std::string& errorMessage = std::string());

    private:
        UINT64 m_newActivityId{};
        ConnectionManager* m_connectionManager{};
        wil::srwlock m_newActivityIdLock;
        wil::srwlock m_connectionManagerLock;
        std::recursive_mutex m_dvcLock;
        wil::unique_handle m_dvcHandle;
        wil::unique_event m_dvcThreadExit;
        wil::unique_event m_dvcThreadStarted;
        std::thread m_dvcListenerThread;
        HRESULT m_errorFromDvcListener{};
        HRESULT m_errorFromDvcWriter{};
        std::map<UINT64, ActivatedAppInfo> m_activityMap;   // ToDo: move to ConnectionManager so even if the DVC server shuts down, the state is still kept.
        wil::srwlock m_activityMapLock;
    };
}
