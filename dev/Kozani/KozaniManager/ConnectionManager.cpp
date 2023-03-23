// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include <KozaniManager_h.h>
#include "ConnectionManager.h"

namespace DvcProtocol = Microsoft::Kozani::DvcProtocol;

namespace Microsoft::Kozani::Manager
{
    void ConnectionManager::Close()
    {
        auto lock{ m_requestsLock.lock_exclusive() };

        for (auto& request : m_activationRequests)
        {
            if ((request.statusCallback != nullptr) && (request.status != RequestStatus::Closed))
            {
                LOG_IF_FAILED(request.statusCallback->OnClosed());
                request.statusCallback.reset();
            }
        }
    }

    std::shared_ptr<ActivationRequestStatusReporter> ConnectionManager::AddNewActivationRequest(
        std::string& connectionId,
        winrt::Windows::ApplicationModel::Activation::ActivationKind activationKind,
        PCWSTR appUserModelId,
        winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs activatedEventArgs,
        _In_ IKozaniStatusCallback* statusCallback,
        DWORD associatedLocalProcessId)
    {
        auto lock{ m_requestsLock.lock_exclusive() };

        // Allocate new ActivationRequestInfo object and append to the end of the m_activationRequests list. 
        m_activationRequests.emplace_back();

        // Retrive the pointer of the new ActivationRequestInfo object to be added to maps later. The object is owned by the 
        // m_activationRequests list and other references are by the pointer. 
        ActivationRequestInfo* requestInfo{ &m_activationRequests.back() };
        
        // Record the iterator of the new ActivationRequestInfo list entry for quick removal (O(1)) from the list if needed.
        requestInfo->listPosition = m_activationRequests.end();
        requestInfo->listPosition--;

        requestInfo->connectionId = std::move(connectionId);
        requestInfo->activationKind = activationKind;
        requestInfo->appUserModelId.assign(appUserModelId);
        requestInfo->args = activatedEventArgs;
        requestInfo->statusCallback = statusCallback;

        requestInfo->statusReporter = std::make_shared<ActivationRequestStatusReporter>();

        m_requestsPendingConnection.push_back(requestInfo);

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
            LOG_HR_MSG(E_FAIL, "Failed to parse PDU. size: %u. Ignore failure.", size);
            return;
        }

        Dvc::ProtocolDataUnit::DataType type{ pdu.type() };
        switch (type)
        {
            case Dvc::ProtocolDataUnit::ConnectionAck:
                ProcessConnectionAck(pdu, channelManager, channel);
                break;

            case Dvc::ProtocolDataUnit::ActivateAppResult:
                ProcessActivateAppResult(pdu);
                break;

            default:
                // ToDo: Unknown PDU type. Return GenericResult message with failure code to server side.
                break;
        }
    }

    void ConnectionManager::ProcessConnectionAck(
        _In_ const Dvc::ProtocolDataUnit& pdu,
        _In_ IWTSVirtualChannelManager* channelManager,
        _In_ IWTSVirtualChannel* channel)
    {
        Dvc::ConnectionAck ackMessage;
        if (!ackMessage.ParseFromString(pdu.data()))
        {
            LOG_HR_MSG(E_FAIL, "Failed to parse connection ACK message. Ignore failure.");
            return;
        }

        auto lock{ m_requestsLock.lock_exclusive() };

        for (auto it = m_requestsPendingConnection.begin(); it != m_requestsPendingConnection.end(); it++)
        {
            ActivationRequestInfo* requestInfo{ *it };
            if (requestInfo->connectionId == ackMessage.connection_id())
            {
                m_requestsPendingConnection.erase(it);

                requestInfo->dvcChannelManager = channelManager;
                requestInfo->dvcChannel = channel;
                requestInfo->status = RequestStatus::Connected;
                requestInfo->statusReporter->SetStatus(RequestStatus::Connected);

                if (pdu.activity_id() > m_newActivityId)
                {
                    // Reconciliation between server and client side activity ID. Either one can crash and restart with new activity ID
                    // smaller than the other one. Always set to the larger of the two to reconcile.
                    m_newActivityId = pdu.activity_id();
                }

                UINT64 activityId{ m_newActivityId };
                m_newActivityId++;

                auto result{ m_activityMap.insert({ activityId , requestInfo }) };
                // activityId only increments. It will take hundreds of billion years for it to wrap around if it increments once every 1 second.
                // So if there is a duplicate, there must be logical error in this code and we want to find out.
                FAIL_FAST_IF_MSG(!result.second, "Activity ID should be unique for each request. Already existing ID: %I64u", activityId);
                
                // Now that we have connected to the DVC channel, send ActivateAppRequest PDU to the server to activate remote app.
                // Failure to send the request should be reported to IKozaniStatusCallback interface of the caller tracking the activation request.
                HRESULT hrSendRequest{ LOG_IF_FAILED(SendActivateAppRequest(channel, activityId, requestInfo)) };
                if (FAILED(hrSendRequest))
                {
                    ProcessAppActivationFailure(hrSendRequest, activityId, requestInfo, L"Failed to send activate app request through DVC");
                }
                else
                {
                    requestInfo->status = RequestStatus::RequestMade;
                    requestInfo->statusReporter->SetStatus(RequestStatus::RequestMade);
                }

                break;
            }
        }
    }

    void ConnectionManager::ProcessActivateAppResult(_In_ const Dvc::ProtocolDataUnit& pdu)
    {
        auto lock{ m_requestsLock.lock_exclusive() };

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
            requestInfo->status = RequestStatus::Succeeded;
            requestInfo->statusReporter->SetStatus(RequestStatus::Succeeded);

            if (requestInfo->statusCallback != nullptr)
            {
                (void)requestInfo->statusCallback->OnActivated(activateAppResult.process_id());
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
        UINT64 activityId,
        _In_ ActivationRequestInfo* requestInfo,
        _In_ PCWSTR errorMessage)
    {
        requestInfo->statusReporter->SetStatus(RequestStatus::Failed);
        if (requestInfo->statusCallback != nullptr)
        {
            (void)requestInfo->statusCallback->OnActivationFailed(hrActivation, errorMessage);
        }

        // Remove the request from all tracking mechanism.
        m_activityMap.erase(activityId);
        m_activationRequests.erase(requestInfo->listPosition);
    }

    HRESULT ConnectionManager::SendActivateAppRequest(
        _In_ IWTSVirtualChannel* channel,
        UINT64 activityId,
        _In_ ActivationRequestInfo* requestInfo) noexcept try
    {
        std::string pdu{ DvcProtocol::CreateActivateAppRequestPDU(
            activityId, requestInfo->appUserModelId.c_str(), requestInfo->activationKind, requestInfo->args) };
        RETURN_IF_FAILED(channel->Write(
            static_cast<ULONG>(pdu.size()), reinterpret_cast<BYTE*>(pdu.data()), nullptr /* pReserved - must be nullptr */));
        return S_OK;
    }
    CATCH_RETURN()

    void ConnectionManager::OnDvcChannelClose(_In_ IWTSVirtualChannel* channel)
    {
        auto lock{ m_requestsLock.lock_exclusive() };

        for (auto it = m_activationRequests.begin(); it != m_activationRequests.end();)
        {
            if (it->dvcChannel == channel)
            {
                if ((it->statusCallback != nullptr) && (it->status != RequestStatus::Closed))
                {
                    LOG_IF_FAILED(it->statusCallback->OnClosed());
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

        for (auto it = m_activationRequests.begin(); it != m_activationRequests.end();)
        {
            if (it->dvcChannelManager == channelManager)
            {
                if ((it->statusCallback != nullptr) && (it->status != RequestStatus::Closed))
                {
                    LOG_IF_FAILED(it->statusCallback->OnClosed());
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
