// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <Shlobj.h>
#include "KozaniDvcProtocol.h"
#include "KozaniRemoteManagerTraceLogging.h"

namespace Microsoft::Kozani::KozaniRemoteManager
{
    class ConnectionManager;

    enum AppActivationStatus
    {
        ActivationPending = 0,
        ActivationSucceeded,
        ActivationFailed,
        TerminationRequestedFromClient
    };

    typedef wil::unique_any_handle_null<decltype(&::UnregisterWait), ::UnregisterWait> unique_wait_handle;

    struct AppActivationInfo
    {
        AppActivationInfo(uint64_t activityId) : activityId(activityId)
        {
        }

        uint64_t activityId{};
        AppActivationStatus activationStatus{};
        DWORD pid{};
        wil::unique_handle processHandle;
        unique_wait_handle processLifetimeTrackerHandle;
    };

    class KozaniDvcServer
    {
    public:
        static KozaniDvcServer* Create();

        ~KozaniDvcServer();

        // Enable error reporting to ConnectionManager. Called only after ConnectionManager has successfully created this object.
        HRESULT EnableConnectionManagerReporting();

        void SendConnectionAck(PCSTR connectionId);
        void SendAppTerminationNotice(uint64_t activityId);

    private:
        KozaniDvcServer() = default;

        static void CALLBACK ProcessTerminationCallback(_In_ PVOID parameter, _In_ BOOLEAN timerOrWaitFired) noexcept;

        HRESULT ProcessDvcIncomingData() noexcept;
        void ProcessDvcIncomingDataThreadFunc() noexcept;
        HRESULT ProcessDvcDataChunk(
            _In_reads_(size) const BYTE* data, 
            UINT32 size,
            bool& isPartialData,
            std::vector<BYTE>& pduBuffer,
            UINT32& pduSize,
            _Outptr_result_maybenull_  const BYTE** pdu) noexcept;

        HRESULT ProcessProtocolDataUnit(_In_reads_(size) const BYTE* data, UINT32 size) noexcept;

        void ProcessActivateAppRequestThreadFunc(_In_ Dvc::ProtocolDataUnit pdu) noexcept;

        HRESULT ProcessActivateAppRequest(
            _In_ Dvc::ProtocolDataUnit& pdu, 
            _Out_ bool& appActivatedAndTracked, 
            _Out_ std::string& errorMessage) noexcept;

        HRESULT ProcessFileActivationRequest(
            _In_ IApplicationActivationManager* aam,
            const std::wstring& appUserModelId,
            const Dvc::ActivateAppRequest& activateAppRequest,
            _Out_ DWORD& processId,
            _Out_ std::string& errorMessage) noexcept;

        HRESULT ProcessAppTerminationNotice(_In_ Dvc::ProtocolDataUnit& pdu) noexcept;

        std::wstring GetRedirectedClientPath(const std::wstring& localPath);

        bool IsActivationKindSupported(Dvc::ActivationKind kind);

        void OpenDvc();
        void StartDvcListenerThread();
        void DvcListenerThreadExiting(HRESULT errorCode, PCSTR erroMessage = "") noexcept;
        void ReportDvcWriterError(HRESULT errorCode);
        
        void SendDvcProtocolData(const char* data, UINT32 size);
        void SendActivateAppResult(
            uint64_t activityId,
            HRESULT hr,
            DWORD appProcessId,
            bool isNewInstance,
            _In_ const std::string& errorMessage = std::string());

    private:
        wil::srwlock m_errorReportingLock;
        std::recursive_mutex m_dvcLock;
        wil::unique_handle m_dvcHandle;
        wil::unique_event m_dvcThreadExit;
        wil::unique_event m_dvcThreadStarted;
        std::thread m_dvcListenerThread;
        bool m_errorReportingEnabled{};
        HRESULT m_errorFromDvcListener{};
        HRESULT m_errorFromDvcWriter{};
    };
}
