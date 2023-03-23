// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

namespace Microsoft::Kozani::Manager
{
    // Max amount of time we will wait for the DVC plugin to be loaded by the remote desktop client (RDC) since we launches it.
    // RDC will load DVC plugins for any new connections that are not already established, by activating the plugin's COM server and 
    // calling IWTSPlugin::Initialize() method. It should happen right away before making any network connections.
    // 5 seconds.
    const UINT32 MaxDvcPluginLoadingTime = 5 * 1000;

    // Max amount of time we will wait for DVC initial connection acknowlegement to come in from server side, if there is already an 
    // existing remote desktop connection.
    // 30 seconds - give enough time for user to respond to pop-up message dialog warning first time connection to remote app.
    const UINT32 MaxConnectionWaitTime = 30 * 1000;

    enum RequestStatus
    {
        Connecting = 0,
        Connected,
        RequestMade,
        Succeeded,
        Failed,
        Closed
    };

    class ActivationRequestStatusReporter
    {
    public:
        ActivationRequestStatusReporter()
        {
            m_eventStatusChanged.create();
        }

        void SetStatus(RequestStatus status)
        {
            auto lock{ m_accessLock.lock_exclusive() };
            if (m_status != status)
            {
                m_status = status;
                m_eventStatusChanged.SetEvent();
            }
        }

        RequestStatus GetStatus()
        {
            auto lock{ m_accessLock.lock_shared() };
            return m_status;
        }

        bool WaitForStatusChange(DWORD milliseconds = INFINITE)
        {
            return m_eventStatusChanged.wait(milliseconds);
        }
        
    private:
        RequestStatus m_status{};
        wil::srwlock m_accessLock;
        wil::unique_event m_eventStatusChanged;
    };

    struct ActivationRequestInfo
    {
        RequestStatus status{};
        std::string connectionId;
        std::wstring appUserModelId;
        UINT32 appInstanceId{};
        winrt::Windows::ApplicationModel::Activation::ActivationKind activationKind{};
        winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs args;
        wil::com_ptr<IKozaniStatusCallback> statusCallback;
        wil::com_ptr<IWTSVirtualChannelManager> dvcChannelManager;
        wil::com_ptr<IWTSVirtualChannel> dvcChannel;
        std::list<ActivationRequestInfo>::iterator listPosition;
        std::shared_ptr<ActivationRequestStatusReporter> statusReporter;
    };

    class ConnectionManager
    {
    public:
        ConnectionManager() = default;
        ~ConnectionManager() = default;

        std::shared_ptr<ActivationRequestStatusReporter> AddNewActivationRequest(
            std::string& connectionId,
            winrt::Windows::ApplicationModel::Activation::ActivationKind activationKind,
            PCWSTR appUserModelId,
            winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs activatedEventArgs,
            _In_ IKozaniStatusCallback* statusCallback,
            DWORD associatedLocalProcessId);

        void Close();

        void ProcessProtocolDataUnit(
            _In_reads_(size) BYTE* data, 
            UINT32 size,
            _In_ IWTSVirtualChannelManager* channelManager,
            _In_ IWTSVirtualChannel* channel);

        void OnDvcChannelClose(IWTSVirtualChannel* channel);

        void OnRemoteDesktopInitializeConnection(_In_ IWTSVirtualChannelManager* channelManager);
        void OnRemoteDesktopDisconnect(_In_ IWTSVirtualChannelManager* channelManager);

    private:
        void ProcessConnectionAck(
            _In_ const Dvc::ProtocolDataUnit& pdu,
            _In_ IWTSVirtualChannelManager* channelManager,
            _In_ IWTSVirtualChannel* channel);

        void ProcessActivateAppResult(_In_ const Dvc::ProtocolDataUnit& pdu);

        void ProcessAppActivationFailure(
            HRESULT hrActivation, 
            UINT64 activityId, 
            _In_ ActivationRequestInfo* requestInfo,
            _In_ PCWSTR errorMessage);

        HRESULT SendActivateAppRequest(
            _In_ IWTSVirtualChannel* channel, 
            UINT64 activityId,
            _In_ ActivationRequestInfo* requestInfo) noexcept;

    private:
        std::list<ActivationRequestInfo> m_activationRequests;
        std::list<ActivationRequestInfo*> m_requestsPendingConnection;
        wil::srwlock m_requestsLock;
        UINT64 m_newActivityId{};
        std::map<UINT64, ActivationRequestInfo*> m_activityMap;
    };
}