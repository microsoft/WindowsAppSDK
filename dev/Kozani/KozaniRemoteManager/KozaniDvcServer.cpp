// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include <wtsapi32.h>

#include "KozaniDvcProtocol.h"
#include "KozaniDvcServer.h"
#include "ConnectionManager.h"
#include "Logging.h"

using namespace Microsoft::Kozani::DvcProtocol;

namespace Microsoft::Kozani::KozaniRemoteManager
{
    KozaniDvcServer* KozaniDvcServer::Create()
    {
        std::unique_ptr<KozaniDvcServer> dvcServer(new KozaniDvcServer);

        dvcServer->OpenDvc();
        dvcServer->StartDvcListenerThread();

        return dvcServer.release();
    }

    KozaniDvcServer::~KozaniDvcServer()
    {
        if (m_dvcListenerThread.joinable())
        {
            m_dvcThreadExit.SetEvent();
            try
            {
                m_dvcListenerThread.join();
            }
            catch (std::invalid_argument)
            {
                // std::invalid_argument will be thrown if the thread has exited (no longer joinable). It may happen if the thread is exiting while join() is called.
                // It is not an issue as we want the thread to exit.
            }
            CATCH_LOG()
        }

        {
            // Acquire lock to make sure no other threads are using the m_dvcHandle so we can safely close it. 
            auto lock{ std::unique_lock<std::recursive_mutex>(m_dvcLock) };
            m_dvcHandle.reset();
        }
    }

    void KozaniDvcServer::OpenDvc()
    {
        auto lock{ std::unique_lock<std::recursive_mutex>(m_dvcLock) };

        using unique_channel_handle = wil::unique_any_handle_null<decltype(&::WTSVirtualChannelClose), ::WTSVirtualChannelClose>;
        using unique_channel_memory = wil::unique_any<void*, decltype(&::WTSFreeMemory), ::WTSFreeMemory>;

        unique_channel_handle wtsHandle(::WTSVirtualChannelOpenEx(
            WTS_CURRENT_SESSION,
            const_cast<LPSTR>(DvcChannelName),
            WTS_CHANNEL_OPTION_DYNAMIC));

        if (wtsHandle == nullptr)
        {
            // DVC channel didn't exist - the current session is not a remote session or the client of this remote session has not
            // created a listener of this DVC channel. It is required that the client has created a DVC channel listener to listen
            // to this specific channel name before the server can open the named DVC channle. Otherwise, ERROR_GEN_FAILURE (31) 
            // may be returned.
            LogDebugMessage("WTSVirtualChannelOpenEx failed with error: %u", GetLastError());
            winrt::throw_last_error();
        }

        unique_channel_memory fileHandle;
        DWORD len{};

        THROW_LAST_ERROR_IF(!::WTSVirtualChannelQuery(
            wtsHandle.get(),
            WTSVirtualFileHandle,
            fileHandle.put(),
            &len));
        THROW_HR_IF(E_UNEXPECTED, (len != sizeof(HANDLE)));

        THROW_IF_WIN32_BOOL_FALSE(::DuplicateHandle(
            ::GetCurrentProcess(),
            *reinterpret_cast<HANDLE*>(fileHandle.get()),
            ::GetCurrentProcess(),
            m_dvcHandle.put(),
            0,
            FALSE,
            DUPLICATE_SAME_ACCESS));
    }

    // This function will be executed in a separate thread from the main thread and shouldn't throw any exceptions.
    // Any uncaught exceptions will cause the process to terminate.
    void KozaniDvcServer::ProcessDvcIncomingData() noexcept try
    {
        bool exitThread = false;
        wil::unique_event_nothrow readComplete;
        HRESULT hr = readComplete.create();
        if (FAILED(hr))
        {
            DvcListenerThreadExiting(hr, "Failed to create readComplete event");
            return;
        }

        std::unique_ptr<BYTE> readBuffer{ new (std::nothrow) BYTE[MaxProtocolDataUnitSize]};
        if (readBuffer == nullptr)
        {
            DvcListenerThreadExiting(E_OUTOFMEMORY, "Failed to allocate readBuffer");
            return;
        }

        OVERLAPPED overlappedRead{};
        overlappedRead.hEvent = readComplete.get();

        while (!exitThread)
        {
            DWORD error{};

            // Set up async read on the DVC.
            if (!ReadFile(m_dvcHandle.get(), readBuffer.get(), MaxProtocolDataUnitSize, nullptr, &overlappedRead) 
                && ((error = GetLastError()) != ERROR_IO_PENDING))
            {
                DvcListenerThreadExiting(HRESULT_FROM_WIN32(error), "[DVC] read failure");
                return;
            }

            HANDLE events[] = { m_dvcThreadExit.get(), readComplete.get() };
            LogDebugMessage("[DVC] Listener thread starting to wait");

            // When we reach this point, the DVC listener thread has passed setup phase and is running.
            m_dvcThreadStarted.SetEvent();

            DWORD result = WaitForMultipleObjects(ARRAYSIZE(events), events, FALSE, INFINITE);
            LogDebugMessage("[DVC] Listener thread wait completed (result=0x%x)", result);
            if (result == WAIT_FAILED)
            {
                DvcListenerThreadExiting(HRESULT_FROM_WIN32(GetLastError()), "[DVC] WaitForMultipleObjects failure");
                return;
            }

            switch (result)
            {
                case WAIT_OBJECT_0:
                    // Thread exit handle signaled.
                    LogDebugMessage("[DVC] Thread exit event handled");
                    return;

                case WAIT_OBJECT_0 + 1:
                {
                    // DVC read completion.
                    DWORD bytesRead{};
                    if (GetOverlappedResult(m_dvcHandle.get(), &overlappedRead, &bytesRead, FALSE))
                    {
                        
                    }
                    else
                    {
                        DvcListenerThreadExiting(HRESULT_FROM_WIN32(GetLastError()), "[DVC] GetOverlappedResult() failed");
                        return;
                    }
                    break;
                }

                default:
                    LogDebugMessage("[DVC] Unexpected WaitForMultipleObjects() result: 0x%x. Ignored", result);
            }
        }
    }
    catch (std::exception& e)
    {
        DvcListenerThreadExiting(E_UNEXPECTED, e.what());
        return;
    }
    catch (...)
    {
        DvcListenerThreadExiting(E_UNEXPECTED, "Caught unknown exception");
        return;
    }

    void KozaniDvcServer::StartDvcListenerThread()
    {
        if (!m_dvcThreadExit)
        {
            m_dvcThreadExit.create(wil::EventOptions::ManualReset);
        }

        if (!m_dvcThreadStarted)
        {
            m_dvcThreadStarted.create(wil::EventOptions::ManualReset);
        }

        m_dvcThreadExit.ResetEvent();
        m_dvcThreadStarted.ResetEvent();

        m_dvcListenerThread = std::thread(&KozaniDvcServer::ProcessDvcIncomingData, this);

        HANDLE events[] = { m_dvcThreadStarted.get(), m_dvcThreadExit.get() };
        LogDebugMessage("[StartDvcListenerThread] Waiting for listener thread starting status");

        // Wait for listerner thread to start successfully. Wait no longer than 5s. 
        DWORD result = WaitForMultipleObjects(ARRAYSIZE(events), events, FALSE, 5000);
        THROW_LAST_ERROR_IF_MSG(result == WAIT_FAILED, "[StartDvcListenerThread] WaitForMultipleObjects() failed.");

        switch (result)
        {
            case WAIT_OBJECT_0:
                // Thread successfully started and is running.
                LogDebugMessage("[StartDvcListenerThread] Listener thread successfully started");
                return;

            case WAIT_OBJECT_0 + 1:
            {
                // Thread exits.
                THROW_HR_MSG(m_errorFromDvcListener, "[StartDvcListenerThread] Listener thread failed to start.");
                break;
            }

            case WAIT_TIMEOUT:
                THROW_HR_MSG(WS_E_OPERATION_TIMED_OUT, "[StartDvcListenerThread] Listener thread failed to start within required time limit.");
                break;

            default:
                THROW_HR_MSG(E_UNEXPECTED, "[StartDvcListenerThread] Unexpected WaitForMultipleObjects() result: 0x%x.", result);
        }
    }

    void KozaniDvcServer::DvcListenerThreadExiting(HRESULT errorCode, PCSTR erroMessage) noexcept
    {
        auto lock{ m_connectionManagerLock.lock_exclusive() };

        m_errorFromDvcListener = errorCode;
        LogDebugMessage("DVC listener thread exiting, error code: 0x%x, error message: %s", errorCode, erroMessage);

        m_dvcThreadExit.SetEvent();

        {
            // Close the DVC handle as this DVC server is going to be shut down without a functional listener thread.
            auto lockDvc{ std::unique_lock<std::recursive_mutex>(m_dvcLock) };
            m_dvcHandle.reset();
        }

        if (m_connectionManager != nullptr)
        {
            m_connectionManager->ReportDvcServerError(errorCode);
        }
    }

    HRESULT KozaniDvcServer::SetConnectionManger(ConnectionManager* connectionManager)
    {
        auto lock{ m_connectionManagerLock.lock_exclusive() };

        if (FAILED(m_errorFromDvcListener))
        {
            // DVC listener thread has encountered error before m_connectionManager is set. Return the failure right away.
            return m_errorFromDvcListener;
        }

        if (FAILED(m_errorFromDvcWriter))
        {
            // DVC writer has encountered error before m_connectionManager is set. Return the failure right away.
            return m_errorFromDvcWriter;
        }

        m_connectionManager = connectionManager;
        return S_OK;
    }

    void KozaniDvcServer::SendConnectionAck(PCSTR connectionId)
    {
        std::vector<BYTE> ackPDURaw{ CreateConnectionAckPDU(connectionId) };
        SendDvcProtocolData(ackPDURaw.data(), ackPDURaw.size());
    }

    void KozaniDvcServer::SendDvcProtocolData(BYTE* data, UINT32 size)
    {
        auto lockDvc{ std::unique_lock<std::recursive_mutex>(m_dvcLock) };

        if (!m_dvcHandle)
        {
            if (FAILED(m_errorFromDvcListener) || FAILED(m_errorFromDvcWriter))
            {
                // Error has been reported before - nothing to do.
                return;
            }

            THROW_WIN32_MSG(ERROR_INVALID_STATE, "DVC handle is closed.");
        }

        DWORD bytesWritten{};
        if (!::WriteFile(m_dvcHandle.get(), data, size, &bytesWritten, nullptr))
        {
            DWORD error = GetLastError();
            ReportDvcWriterError(HRESULT_FROM_WIN32(error));
            THROW_WIN32_MSG(error, "DVC WriteFile failed.");
        }
            
        if (bytesWritten != size)
        {
            ReportDvcWriterError(E_UNEXPECTED);
            THROW_WIN32_MSG(E_UNEXPECTED, "DVC WriteFile only writes %u bytes while %u bytes are expected.", bytesWritten, size);
        }
        
        return;
    }

    void KozaniDvcServer::ReportDvcWriterError(HRESULT errorCode)
    {
        auto lock{ m_connectionManagerLock.lock_exclusive() };

        m_errorFromDvcWriter = errorCode;

        // Failure to write to DVC channel is fatal. Will notify the DVC listener thread to exit.
        m_dvcThreadExit.SetEvent();

        {
            // Close the DVC handle as this DVC server is going to be shut down. 
            auto lockDvc{ std::unique_lock<std::recursive_mutex>(m_dvcLock) };
            m_dvcHandle.reset();
        }

        if (m_connectionManager != nullptr)
        {
            m_connectionManager->ReportDvcServerError(errorCode);
        }
    }
}
