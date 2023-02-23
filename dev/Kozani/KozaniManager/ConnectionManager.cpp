// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include <KozaniManager_h.h>
#include "ConnectionManager.h"

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
        IKozaniStatusCallback* statusCallback,
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

        return requestInfo->statusReporter;
    }
}