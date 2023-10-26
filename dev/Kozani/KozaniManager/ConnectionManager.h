// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <windows.applicationmodel.activation.h>

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
        AppActivationRequestMade,
        AppActivationSucceeded,
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

    typedef wil::unique_any_handle_null<decltype(&::UnregisterWait), ::UnregisterWait> unique_wait_handle;
    class ConnectionManager;

    struct ActivationRequestInfo
    {
        static const uint64_t ActivityId_Unknown{};

        // Minimum cleanup delay after the associated local process lifetime tracker is disabled: 60 seconds.
        // When the request status becomes Closed or Failed, we want to unregister the wait handle for tracking the associated local process.
        // However, the unregistration can fail with ERROR_IO_PENDING if there is an outstanding callback to be made. In such a case, we cannot
        // clean up the ActivationRequestInfo object as it will be accessed from the callback function. We will clean up the object later with
        // this minimum delay to allow the callbak to finish.
        static const int MinCleanupDelay{ 60 * 1000 };

        uint64_t activityId{};
        RequestStatus status{};
        std::string connectionId;
        std::wstring appUserModelId;
        winrt::Windows::ApplicationModel::Activation::ActivationKind activationKind{};
        std::string serializedActivationArgs;
        wil::com_ptr<IKozaniStatusCallback> statusCallback;
        wil::com_ptr<IWTSVirtualChannelManager> dvcChannelManager;
        wil::com_ptr<IWTSVirtualChannel> dvcChannel;
        std::list<ActivationRequestInfo>::iterator listPosition;
        std::shared_ptr<ActivationRequestStatusReporter> statusReporter;
        ConnectionManager* connectionManager{};
        DWORD associatedLocalProcessId{};
        unique_wait_handle processLifetimeTrackerHandle;
        bool processLifetimeTrackerDisabled{};
        uint64_t processLifetimeTrackerDisabledTime{};
    };

    class ConnectionManager
    {
    public:
        std::shared_ptr<ActivationRequestStatusReporter> AddNewActivationRequest(
            std::string& connectionId,
            winrt::Windows::ApplicationModel::Activation::ActivationKind activationKind,
            PCWSTR appUserModelId,
            winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs activatedEventArgs,
            _In_ IKozaniStatusCallback* statusCallback,
            DWORD associatedLocalProcessId);

        void CleanupActivationRequest(_In_ const ActivationRequestStatusReporter* statusReporter);

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
        static void CALLBACK ProcessTerminationCallback(_In_ PVOID parameter, _In_ BOOLEAN timerOrWaitFired) noexcept;

        HRESULT OnDvcServerConnected(
            uint64_t activityId,
            ActivationRequestInfo* requestInfo,
            _In_ IWTSVirtualChannelManager* channelManager,
            _In_ IWTSVirtualChannel* channel,
            _Out_ std::wstring& errorMessage) noexcept;

        void ProcessConnectionAck(
            _In_ const Dvc::ProtocolDataUnit& pdu,
            _In_ IWTSVirtualChannelManager* channelManager,
            _In_ IWTSVirtualChannel* channel);

        void ProcessActivateAppResult(_In_ const Dvc::ProtocolDataUnit& pdu);

        void ProcessAppActivationFailure(
            HRESULT hrActivation, 
            _In_ ActivationRequestInfo* requestInfo,
            _In_ PCWSTR errorMessage);

        HRESULT DisableProcessLifetimeTracker(ActivationRequestInfo* requestInfo, _Out_ bool& callbackPending) noexcept;

        void ProcessAppTerminationNotice(_In_ const Dvc::ProtocolDataUnit& pdu);

        HRESULT SendActivateAppRequest(_In_ ActivationRequestInfo* requestInfo) noexcept;

        HRESULT SendAppTerminationNotice(_In_ ActivationRequestInfo* requestInfo) noexcept;

        void CloseRequest(std::list<ActivationRequestInfo>::iterator& it);

        void RemoveRequestFromPendingConnectionList(_In_ const ActivationRequestInfo* request);
        void RemoveRequest(_In_ const ActivationRequestInfo* request, bool removeFromMainList);
        void CleanupOutdatedRequests();

    private:
        std::list<ActivationRequestInfo> m_activationRequests;
        std::list<ActivationRequestInfo*> m_requestsPendingConnection;
        wil::srwlock m_requestsLock;

        // New activity Id starts from 1. 0 means the activity Id is not set.
        static const uint64_t c_activityId_Unknown{};
        uint64_t m_nextActivityId{ 1 };
        std::map<uint64_t, ActivationRequestInfo*> m_activityMap;

        bool m_closing{};
    };
}
