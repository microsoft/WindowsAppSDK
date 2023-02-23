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
    // 10 seconds.
    const UINT32 MaxConnectionWaitTime = 10 * 1000;

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
            IKozaniStatusCallback* statusCallback,
            DWORD associatedLocalProcessId);

        void Close();

    private:
        std::list<ActivationRequestInfo> m_activationRequests;
        wil::srwlock m_requestsLock;
    };
}