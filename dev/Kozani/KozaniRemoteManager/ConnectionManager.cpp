// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ConnectionManager.h"

#include "Logging.h"

using namespace Microsoft::WRL;

extern Microsoft::WRL::Details::DefaultModule<OutOfProc>* g_module;

namespace Microsoft::Kozani::KozaniRemoteManager
{
    ConnectionManager::~ConnectionManager() noexcept try
    {
        WaitForFailedDvcServerDeletionThread();

        {
            auto lock{ std::unique_lock<std::recursive_mutex>(m_dvcServerLock) };
            m_dvcServer.reset();
        }

        {
            auto lock{ m_activityMapLock.lock_exclusive() };

            // Set m_closing to true so process lifetime tracker thread callback function will immediately return after acquiring the m_activityMapLock.
            m_closing = true;
        }

        // Unregister process lifetime tracker wait handle and wait for the threads to finish before destructing the m_activityMap.
        // Otherwise, the lifetime tracker thread may try to access deleted resource. Do not call blocking UnregisterWaitEx holding
        // the m_activityMapLock as it will cause deadlock if lifetime tracker thread callback tries to get the lock. We are safe without
        // locking as m_closing is set to true above, preventing any modification to the m_activityMap in  other threads.
        for (auto iter = m_activityMap.begin(); iter != m_activityMap.end(); iter++)
        {
            auto& waitHandle{ iter->second.processLifetimeTrackerHandle };
            if (waitHandle)
            {
                // Call UnregisterWaitEx with INVALID_HANDLE_VALUE so it will wait for any pending callback to finish before returning
                // to avoid AV issues when a callback function is using the objects that are going to be released.
                LOG_IF_WIN32_BOOL_FALSE(UnregisterWaitEx(waitHandle.get(), INVALID_HANDLE_VALUE));
                waitHandle.release();
            }
        }
    }
    CATCH_LOG_RETURN()

    void ConnectionManager::Connect(PCSTR connectionId)
    {   
        auto lock{ std::unique_lock<std::recursive_mutex>(m_dvcServerLock) };

        if (m_dvcServer == nullptr)
        {
            try
            {
                m_dvcServer.reset(KozaniDvcServer::Create());

                // After successfully creating the KozaniDvcServer object, enable error reporting from this object so it can communicate 
                // errors from the DVC server's operation.
                HRESULT hrEnableReporting{ LOG_IF_FAILED(m_dvcServer->EnableConnectionManagerReporting()) };
                if (FAILED(hrEnableReporting))
                {
                    // Failure has happened in the DVC server right after its creation. Treated as fatal.
                    m_dvcServer.reset();
                    THROW_HR(hrEnableReporting);
                }

                // After successfully created the DVC server the first time, increment the module object count to account for this 
                // object so this module will not exit after COM call is finished. The lifetime of this module now is also tied to 
                // the lifetime of this ConnectionManager object, which has the DVC server listening and responding to incoming 
                // DVC traffic.
                if (!m_isModuleObjectCountAdded)
                {
                    g_module->IncrementObjectCount();
                    m_isModuleObjectCountAdded = true;
                }
            }
            catch (...)
            {
                // Failing to create DVC server is fatal and we should shut down this COM server and let a new instance to be 
                // started the next COM call comes in. 
                if (m_isModuleObjectCountAdded)
                {
                    // By decementing the object count of this module to remove the count for this object, the object count will
                    // be reduced to 0 after the current active COM call is finished and the COM server can be shut down. Any new
                    // COM calls will be routed to a new instance of the COM server.
                    g_module->DecrementObjectCount();
                    m_isModuleObjectCountAdded = false;
                }
                throw;
            }
        }
        
        m_dvcServer->SendConnectionAck(connectionId);
    }

    // Report error from DVC server object. Called from the DVC server object encounting error.
    void ConnectionManager::ReportDvcServerError(HRESULT hr)
    {
        auto lock{ std::unique_lock<std::recursive_mutex>(m_dvcServerLock) };

        LogDebugMessage("DVC server reported error: 0x%x. Will shut down the server and create a new one for the next connection.", hr);

        if (m_dvcServer == nullptr)
        {
            // Already deleted previously. Nothing to do.
            return;
        }

        WaitForFailedDvcServerDeletionThread();

        m_failedDvcServerToBeDeleted.reset();
        m_failedDvcServerToBeDeleted.swap(m_dvcServer);

        // Start a separate thread to delete the failed DVC server object as the current thread is from the DVC server object.
        m_failedDvcServerDeletionThread = std::thread([this] { m_failedDvcServerToBeDeleted.reset(); });
    }

    void ConnectionManager::WaitForFailedDvcServerDeletionThread()
    {
        if (m_failedDvcServerDeletionThread.joinable())
        {
            try
            {
                m_failedDvcServerDeletionThread.join();
            }
            catch (std::invalid_argument)
            {
                // std::invalid_argument will be thrown if the thread has exited (no longer joinable). It may happen if the thread is exiting while join() is called.
                // It is not an issue as we want the thread to exit.
            }
        }
    }

    UINT64 ConnectionManager::GetNewActivityId()
    {
        auto lock{ m_newActivityIdLock.lock_exclusive() };
        return m_newActivityId++;
    }

    void ConnectionManager::ProcessAppTermination(AppActivationInfo* appActivationInfo)
    {
        auto lock{ m_activityMapLock.lock_exclusive() };
        if (m_closing)
        {
            return;
        }

        UINT64 activityId{ appActivationInfo->activityId };
        
        // If the termiation is not requested from client, we will send AppTerminationNotice to client to notify the app is terminated.
        bool sendAppTerminationNotice{ appActivationInfo->activationStatus != AppActivationStatus::TerminationRequestedFromClient };

        appActivationInfo->processLifetimeTrackerHandle.reset();
        m_processIdMap.erase(appActivationInfo->pid);
        m_activityMap.erase(appActivationInfo->activityId);

        // Unlock m_activityMapLock before sending AppTerminationNotice as it does not use any resources protected by the lock.
        lock.reset();

        if (sendAppTerminationNotice)
        {
            auto dvcServerLock{ std::unique_lock<std::recursive_mutex>(m_dvcServerLock) };

            if (m_dvcServer)
            {
                m_dvcServer->SendAppTerminationNotice(activityId);
            }
        }
    }
}
