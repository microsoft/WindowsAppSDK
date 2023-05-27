// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include <KozaniManager_h.h>
#include "ConnectionManager.h"

namespace DvcProtocol = Microsoft::Kozani::DvcProtocol;

namespace Microsoft::Kozani::Manager
{
    void CALLBACK ConnectionManager::ProcessTerminationCallback(_In_ PVOID parameter, _In_ BOOLEAN timerOrWaitFired) noexcept try
    {
        if (timerOrWaitFired)
        {
            // Timer timed out. This shouldn't happen as we wait infinite time. 
            LOG_HR_MSG(E_UNEXPECTED, "Wait timed out tracking process lifetime.");
            return;
        }

        ActivationRequestInfo* requestInfo{ reinterpret_cast<ActivationRequestInfo*>(parameter) };
        ConnectionManager* connectionManager{ requestInfo->connectionManager };
        auto lock{ connectionManager->m_requestsLock.lock_exclusive() };

        if (connectionManager->m_closing || requestInfo->processLifetimeTrackerDisabled)
        {
            // We are closing down or the tracker is disabled. No more processing should be done.
            return;
        }

        // Unregister the process lifetime tracker wait handle in a non-blocking way as we no longer need to track the process lifetime.
        requestInfo->processLifetimeTrackerHandle.reset();

        if (requestInfo->statusCallback)
        {
            (void)requestInfo->statusCallback->OnClosed();
            requestInfo->statusCallback.reset();
        }

        switch (requestInfo->status)
        {
            case RequestStatus::Connecting:
                for (auto it = connectionManager->m_requestsPendingConnection.begin(); it != connectionManager->m_requestsPendingConnection.end(); it++)
                {
                    if (requestInfo == *it)
                    {
                        connectionManager->m_requestsPendingConnection.erase(it);
                        break;
                    }
                }
                break;

            case RequestStatus::Connected:
                __fallthrough;
            case RequestStatus::AppActivationRequestMade:
                __fallthrough;
            case RequestStatus::AppActivationSucceeded:
                connectionManager->SendAppTerminationNotice(requestInfo);
                break;

            case RequestStatus::Failed:
                __fallthrough;
            case RequestStatus::Closed:
                // Nothing to do.
                break;

            default:
                FAIL_FAST_MSG("Unhandled RequestStatus: %u", requestInfo->status);
        }

        // ActivityId_Unknown (0) is reserved for uninitialized state (ConnectionAck has not been received from DVC server yet) and will not be in m_activityMap.
        if (requestInfo->activityId != ActivationRequestInfo::ActivityId_Unknown)
        {
            connectionManager->m_activityMap.erase(requestInfo->activityId);
        }

        connectionManager->m_activationRequests.erase(requestInfo->listPosition);
    }
    CATCH_LOG_RETURN()

    void ConnectionManager::Close()
    {
        // Setting m_closing to true will cancel all other operations, which means no changes to member variables protected by the lock in other threads.
        {
            auto lock{ m_requestsLock.lock_exclusive() };
            m_closing = true;
        }

        // Do not hold the m_requestsLock while making blocking call to UnregisterWaitEx (with INVALID_HANDLE_VALUE as the CompletionEvent parameter),
        // as it will deadlock if there is a callback waiting for the m_requestsLock in another thread. We are safe without locking as setting m_closing
        // to true above will prevent any other threads from changing member variables of this class. 
        for (auto& request : m_activationRequests)
        {
            if (request.processLifetimeTrackerHandle)
            {
                // Unregister the process lifetime tracker as we know we are closing and will no longer track any associated local processes. 
                // This will also avoid triggering unnecessary processing once those processes are terminated when IKozaniStatusCallback::OnClose() is received. 
                //   Call UnregisterWaitEx with INVALID_HANDLE_VALUE so it will wait for any pending callback to finish before returning
                // to avoid AV issues when a callback function is using the objects that are going to be released. Since we set m_closing to true already, 
                // ProcessTerminationCallback should return right away.
                LOG_IF_WIN32_BOOL_FALSE(UnregisterWaitEx(request.processLifetimeTrackerHandle.get(), INVALID_HANDLE_VALUE));
                request.processLifetimeTrackerHandle.release();
            }

            if (request.statusCallback)
            {
                (void)request.statusCallback->OnClosed();
                request.statusCallback.reset();
            }
        }

        m_requestsPendingConnection.clear();
        m_activationRequests.clear();
    }

    std::shared_ptr<ActivationRequestStatusReporter> ConnectionManager::AddNewActivationRequest(
        std::string& connectionId,
        winrt::Windows::ApplicationModel::Activation::ActivationKind activationKind,
        PCWSTR appUserModelId,
        winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs activatedEventArgs,
        _In_ IKozaniStatusCallback* statusCallback,
        DWORD associatedLocalProcessId)
    {
        wil::unique_handle associatedLocalProcessHandle;
        if (associatedLocalProcessId != 0)
        {
            associatedLocalProcessHandle.reset(OpenProcess(SYNCHRONIZE, FALSE, associatedLocalProcessId));
            THROW_LAST_ERROR_IF_NULL_MSG(associatedLocalProcessHandle, 
                "Failed to open associated local process to track its lifetime. pid=%u", associatedLocalProcessId);
        }

        auto lock{ m_requestsLock.lock_exclusive() };

        THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_STATE), m_closing);

        // Allocate new ActivationRequestInfo object and append to the end of the m_activationRequests list. 
        m_activationRequests.emplace_back();

        // If failure happened after this point, we will automatically remove the new requestInfo object added to m_activationRequests list.
        auto removeRequestOnFailure = wil::scope_exit([&]()
        {
            m_activationRequests.pop_back();
        });

        // Retrive the pointer of the new ActivationRequestInfo object to be added to maps later. The object is owned by the 
        // m_activationRequests list and other references are by the pointer. 
        ActivationRequestInfo* requestInfo{ &m_activationRequests.back() };
        
        // Record the iterator of the new ActivationRequestInfo list entry for quick removal (O(1)) from the list if needed.
        requestInfo->listPosition = m_activationRequests.end();
        requestInfo->listPosition--;

        requestInfo->associatedLocalProcessId = associatedLocalProcessId;
        requestInfo->connectionId = std::move(connectionId);
        requestInfo->activationKind = activationKind;
        requestInfo->appUserModelId.assign(appUserModelId);

        // Experiments showed that the IActivatedEventArgs COM object can only be safely used in the calling thread from the client. 
        // Saving it and used it later in a different thread can trigger CO_E_OBJNOTCONNECTED failure, or worse, AV. So serialize it to 
        // a string now and attach to ActivateAppRequest PDU later.
        requestInfo->serializedActivationArgs = DvcProtocol::SerializeActivatedEventArgs(activatedEventArgs);

        requestInfo->statusCallback = statusCallback;
        requestInfo->statusReporter = std::make_shared<ActivationRequestStatusReporter>();
        requestInfo->connectionManager = this;

        if (associatedLocalProcessHandle)
        {
            if (!RegisterWaitForSingleObject(
                &requestInfo->processLifetimeTrackerHandle, associatedLocalProcessHandle.get(), ProcessTerminationCallback, requestInfo, INFINITE, WT_EXECUTEONLYONCE))
            {
                THROW_LAST_ERROR_MSG("RegisterWaitForSingleObject failed. Cannot track lifetime of the associated local proess pid=%u", associatedLocalProcessId);
            }

            requestInfo->associatedLocalProcessHandle = std::move(associatedLocalProcessHandle);
        }

        m_requestsPendingConnection.push_back(requestInfo);

        // Now that we are successful, disable removeRequestOnFailure to keep the newly added requestInfo in m_activationRequests list.
        removeRequestOnFailure.release();
        return requestInfo->statusReporter;
    }

    void ConnectionManager::ProcessProtocolDataUnit(
            _In_reads_(size) BYTE* data,
            UINT32 size,
            _In_ IWTSVirtualChannelManager* channelManager,
            _In_ IWTSVirtualChannel* channel)
    {
        Dvc::ProtocolDataUnit pdu;
        if (!pdu.ParseFromArray(data, size))
        {
            LOG_HR_MSG(KOZANI_E_BAD_PDU, "Failed to parse PDU. size: %u. Ignore failure.", size);
            return;
        }

        const Dvc::ProtocolDataUnit::DataType type{ pdu.type() };
        switch (type)
        {
            case Dvc::ProtocolDataUnit::ConnectionAck:
                ProcessConnectionAck(pdu, channelManager, channel);
                break;

            case Dvc::ProtocolDataUnit::ActivateAppResult:
                ProcessActivateAppResult(pdu);
                break;

            case Dvc::ProtocolDataUnit::AppTerminationNotice:
                ProcessAppTerminationNotice(pdu);
                break;

            default:
                // ToDo: https://task.ms/43963854 Unknown PDU type. Return GenericResult message with failure code to server side.
                break;
        }
    }

    // Must be called with m_requestsLock.lock_exclusive() done from the caller.
    HRESULT ConnectionManager::OnDvcServerConnected(
        uint64_t activityId,
        ActivationRequestInfo* requestInfo,
        _In_ IWTSVirtualChannelManager* channelManager,
        _In_ IWTSVirtualChannel* channel,
        _Out_ std::wstring& errorMessage) noexcept try
    {
        requestInfo->activityId = activityId;
        requestInfo->dvcChannelManager = channelManager;
        requestInfo->dvcChannel = channel;
        requestInfo->status = RequestStatus::Connected;
        requestInfo->statusReporter->SetStatus(RequestStatus::Connected);

        auto result{ m_activityMap.insert({ activityId , requestInfo }) };
        // activityId only increments. It will take hundreds of billion years for it to wrap around if it increments once every 1 second.
        // So if there is a duplicate, there must be logical error in this code and we want to find out.
        FAIL_FAST_IF_MSG(!result.second, "Non-unique Activity ID: %llu", activityId);

        // Now that we have connected to the DVC channel, send ActivateAppRequest PDU to the server to activate remote app.
        // Failure to send the request should be reported to IKozaniStatusCallback interface of the caller tracking the activation request.
        const HRESULT hrSendRequest{ LOG_IF_FAILED(SendActivateAppRequest(requestInfo)) };
        if (FAILED(hrSendRequest))
        {
            errorMessage = L"Failed to send activate app request through DVC";
            RETURN_HR(hrSendRequest);
        }
        else
        {
            requestInfo->status = RequestStatus::AppActivationRequestMade;
            requestInfo->statusReporter->SetStatus(RequestStatus::AppActivationRequestMade);
        }
        return S_OK;
    }
    CATCH_RETURN()

    void ConnectionManager::ProcessConnectionAck(
        _In_ const Dvc::ProtocolDataUnit& pdu,
        _In_ IWTSVirtualChannelManager* channelManager,
        _In_ IWTSVirtualChannel* channel)
    {
        Dvc::ConnectionAck ackMessage;
        if (!ackMessage.ParseFromString(pdu.data()))
        {
            LOG_HR_MSG(KOZANI_E_BAD_PDU, "Failed to parse connection ACK message. Ignore failure.");
            return;
        }

        auto lock{ m_requestsLock.lock_exclusive() };

        if (m_closing)
        {
            // We are closing, no more processing.
            return;
        }

        for (auto it = m_requestsPendingConnection.begin(); it != m_requestsPendingConnection.end(); it++)
        {
            ActivationRequestInfo* requestInfo{ *it };
            if (requestInfo->connectionId == ackMessage.connection_id())
            {
                m_requestsPendingConnection.erase(it);

                if (pdu.activity_id() > m_nextActivityId)
                {
                    // Reconciliation between server and client side activity ID. Either one can crash or reboot and restart with new activity ID
                    // smaller than the other one. Always set to the larger of the two to reconcile.
                    m_nextActivityId = pdu.activity_id();
                }

                const uint64_t activityId{ m_nextActivityId };
                m_nextActivityId++;

                std::wstring errorMessage;
                HRESULT hrOnDvcServerConnected{ LOG_IF_FAILED(OnDvcServerConnected(activityId, requestInfo, channelManager, channel, errorMessage)) };
                if (FAILED(hrOnDvcServerConnected))
                {
                    if (requestInfo->status != RequestStatus::AppActivationRequestMade)
                    {
                        if (errorMessage.empty())
                        {
                            errorMessage = L"Failed to process DVC server connection.";
                        }

                        ProcessAppActivationFailure(hrOnDvcServerConnected, activityId, requestInfo, errorMessage.c_str());
                    }

                    THROW_HR(hrOnDvcServerConnected);
                }

                break;
            }
        }
    }

    void ConnectionManager::ProcessActivateAppResult(_In_ const Dvc::ProtocolDataUnit& pdu)
    {
        auto lock{ m_requestsLock.lock_exclusive() };

        THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_STATE), m_closing);

        auto iter{ m_activityMap.find(pdu.activity_id()) };
        if (iter == m_activityMap.end())
        {
            LOG_HR_MSG(E_UNEXPECTED, "ActivateAppResult from DVC server has unknown activity ID %I64u. Ignoring the PDU.", pdu.activity_id());
            return;
        }

        Dvc::ActivateAppResult activateAppResult;
        if (!activateAppResult.ParseFromString(pdu.data()))
        {
            LOG_HR_MSG(HRESULT_FROM_WIN32(ERROR_INVALID_DATA), "Unable to parse ActivateAppResult PDU. Ignoring the PDU.");
            return;
        }

        ActivationRequestInfo* requestInfo{ iter->second };
        if (SUCCEEDED(activateAppResult.hresult()))
        {
            requestInfo->status = RequestStatus::AppActivationSucceeded;
            requestInfo->statusReporter->SetStatus(RequestStatus::AppActivationSucceeded);

            if (requestInfo->statusCallback != nullptr)
            {
                LOG_IF_FAILED(requestInfo->statusCallback->OnActivated(activateAppResult.process_id(), activateAppResult.is_new_instance()));
            }
        }
        else
        {
            std::wstring errorMessage{ ::Microsoft::Utf8::ToUtf16(activateAppResult.error_message()) };
            ProcessAppActivationFailure(activateAppResult.hresult(), pdu.activity_id(), requestInfo, errorMessage.c_str());
        }
    }

    // Must be called with m_requestsLock.lock_exclusive() done in caller.
    void ConnectionManager::ProcessAppActivationFailure(
        HRESULT hrActivation,
        uint64_t activityId,
        _In_ ActivationRequestInfo* requestInfo,
        _In_ PCWSTR errorMessage)
    {
        requestInfo->statusReporter->SetStatus(RequestStatus::Failed);
        if (requestInfo->statusCallback != nullptr)
        {
            LOG_IF_FAILED(requestInfo->statusCallback->OnActivationFailed(hrActivation, errorMessage));
            requestInfo->statusCallback.reset();
        }

        // Remove the request from all tracking mechanism.
        m_activityMap.erase(activityId);
        m_activationRequests.erase(requestInfo->listPosition);
    }

    void ConnectionManager::DisableProcessLifetimeTracker(uint64_t activityId)
    {
        auto lock{ m_requestsLock.lock_exclusive() };
        if (m_closing)
        {
            // We are closing, no more processing.
            return;
        }

        auto iter{ m_activityMap.find(activityId) };
        if (iter == m_activityMap.end())
        {
            return;
        }

        ActivationRequestInfo* requestInfo{ iter->second };

        if (requestInfo->processLifetimeTrackerHandle)
        {
            requestInfo->processLifetimeTrackerDisabled = true;

            // Call UnregisterWaitEx with INVALID_HANDLE_VALUE so it will wait for any pending callback to finish before returning.
            // Release the m_requestsLock before calling blocking UnregisterWaitEx, which will deadlock if the other thread calling the
            // ProcessTerminationCallback function is trying to get the lock. We are safe here as requestInfo->processLifetimeTrackerDisabled
            // is set to true above, which will prevent the process lifetime tracker thread from modifying the requestInfo object.
            lock.reset();
            THROW_IF_WIN32_BOOL_FALSE(UnregisterWaitEx(requestInfo->processLifetimeTrackerHandle.get(), INVALID_HANDLE_VALUE));
            requestInfo->processLifetimeTrackerHandle.release();
        }
    }

    void ConnectionManager::DisableProcessLifetimeTracker(ActivationRequestInfo* requestInfo)
    {
        if (requestInfo->processLifetimeTrackerHandle)
        {
            requestInfo->processLifetimeTrackerDisabled = true;

            // Call UnregisterWaitEx with INVALID_HANDLE_VALUE so it will wait for any pending callback to finish before returning.
            // Release the m_requestsLock before calling blocking UnregisterWaitEx, which will deadlock if the other thread calling the
            // ProcessTerminationCallback function is trying to get the lock. We are safe here as requestInfo->processLifetimeTrackerDisabled
            // is set to true above, which will prevent the process lifetime tracker thread from modifying the requestInfo object.
            lock.reset();
            THROW_IF_WIN32_BOOL_FALSE(UnregisterWaitEx(requestInfo->processLifetimeTrackerHandle.get(), INVALID_HANDLE_VALUE));
            requestInfo->processLifetimeTrackerHandle.release();
        }
    }

    void ConnectionManager::ProcessAppTerminationNotice(_In_ const Dvc::ProtocolDataUnit& pdu)
    {
        // We no longer need to track the associated local process as we know the remote process has been terminated. 
        // Disabling the associated local process tracker also prevents unnecessary handling if the associated local process
        // is terminated due to us calling IKozaniStatusCallback::OnClosed() to report the remote app termination to our client,
        // which may cause it to terminate the associated local process.
        DisableProcessLifetimeTracker(pdu.activity_id());

        auto lock{ m_requestsLock.lock_exclusive() };
        if (m_closing)
        {
            // We are closing, no more processing.
            return;
        }

        auto iter{ m_activityMap.find(pdu.activity_id()) };
        if (iter == m_activityMap.end())
        {
            LOG_WIN32_MSG(ERROR_NO_MATCH, 
                "AppTerminationNotice from DVC server has unknown activity ID %I64u. The associated local process may have already been terminated. Ignoring the PDU.", 
                pdu.activity_id());
            return;
        }

        ActivationRequestInfo* requestInfo{ iter->second };

        requestInfo->status = RequestStatus::Closed;
        requestInfo->statusReporter->SetStatus(RequestStatus::Closed);

        if (requestInfo->statusCallback != nullptr)
        {
            (void)requestInfo->statusCallback->OnClosed();
            requestInfo->statusCallback.reset();
        }

        m_activityMap.erase(iter);
        m_activationRequests.erase(requestInfo->listPosition);
    }

    HRESULT ConnectionManager::SendActivateAppRequest(_In_ ActivationRequestInfo* requestInfo) noexcept try
    {
        std::string pdu{ DvcProtocol::CreateActivateAppRequestPdu(
            requestInfo->activityId, requestInfo->appUserModelId.c_str(), requestInfo->activationKind, requestInfo->serializedActivationArgs) };
        RETURN_IF_FAILED(requestInfo->dvcChannel->Write(
            static_cast<ULONG>(pdu.size()), reinterpret_cast<BYTE*>(pdu.data()), nullptr /* pReserved - must be nullptr */));
        return S_OK;
    }
    CATCH_RETURN()

    HRESULT ConnectionManager::SendAppTerminationNotice(_In_ ActivationRequestInfo* requestInfo) noexcept try
    {
        std::string pdu{ DvcProtocol::CreateAppTerminationNoticePdu(requestInfo->activityId) };
        RETURN_IF_FAILED(requestInfo->dvcChannel->Write(
            static_cast<ULONG>(pdu.size()), reinterpret_cast<BYTE*>(pdu.data()), nullptr /* pReserved - must be nullptr */));
        return S_OK;
    }
    CATCH_RETURN()

    void ConnectionManager::OnDvcChannelClose(_In_ IWTSVirtualChannel* channel)
    {
        auto lock{ m_requestsLock.lock_exclusive() };

        if (m_closing)
        {
            // We are closing, no more processing.
            return;
        }

        for (auto it = m_activationRequests.begin(); it != m_activationRequests.end();)
        {
            if (it->dvcChannel == channel)
            {
                if (it->statusCallback != nullptr)
                {
                    LOG_IF_FAILED(it->statusCallback->OnClosed());
                    it->statusCallback.reset();
                }
                it = m_activationRequests.erase(it);
            }
            else
            {
                it++;
            }
        }
    }

    void ConnectionManager::OnRemoteDesktopInitializeConnection(_In_ IWTSVirtualChannelManager* channelManager)
    {
        auto lock{ m_requestsLock.lock_exclusive() };

        if (m_closing)
        {
            // We are closing, no more processing.
            return;
        }

        if (m_requestsPendingConnection.empty())
        {
            // This can happen when the DVC is loaded in non-Kozani scenario, like launching remote desktop client to connect to full
            // remote desktop session.
            return;
        }

        // The latest request added to the m_requestsPendingConnection is associated with the new connection.
        auto request{ m_requestsPendingConnection.back() };
        if (request->dvcChannelManager == nullptr)
        {
            request->dvcChannelManager = channelManager;
        }
    }

    void ConnectionManager::OnRemoteDesktopDisconnect(_In_ IWTSVirtualChannelManager* channelManager)
    {
        auto lock{ m_requestsLock.lock_exclusive() };

        if (m_closing)
        {
            // We are closing, no more processing.
            return;
        }

        for (auto it = m_activationRequests.begin(); it != m_activationRequests.end();)
        {
            if (it->dvcChannelManager == channelManager)
            {
                if (it->statusCallback != nullptr)
                {
                    LOG_IF_FAILED(it->statusCallback->OnClosed());
                    it->statusCallback.reset();
                }
                it = m_activationRequests.erase(it);
            }
            else
            {
                it++;
            }
        }
    }
}
