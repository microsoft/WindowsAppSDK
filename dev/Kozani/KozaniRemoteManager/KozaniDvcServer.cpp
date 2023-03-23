// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include <shobjidl.h>
#include <wtsapi32.h>
#include <pchannel.h>
#include <Kozani.DVC.pb.h>

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
    void KozaniDvcServer::ProcessDvcIncomingDataThreadFunc() noexcept try
    {
        HRESULT hr{ LOG_IF_FAILED(ProcessDvcIncomingData()) };
        if (FAILED(hr))
        {
            DvcListenerThreadExiting(hr, "Failed to process incoming DVC data");
        }
    }
    CATCH_LOG_RETURN()

    HRESULT KozaniDvcServer::ProcessDvcIncomingData() noexcept try
    {
        bool exitThread = false;
        wil::unique_event_nothrow readComplete;
        HRESULT hr = readComplete.create();
        if (FAILED(hr))
        {
            DvcListenerThreadExiting(hr, "Failed to create readComplete event");
            RETURN_HR(hr);
        }

        // CHANNEL_PDU_LENGTH is the max amount of data sent/received in one DVC operation. Data larger than that is segmented into chunks of 
        // that size and sent/received as multiple operations.
        BYTE readBuffer[CHANNEL_PDU_LENGTH];
        std::vector<BYTE> pduBuffer;
        UINT32 pduSize{};
        bool isPartialData{};
        OVERLAPPED overlappedRead{};
        overlappedRead.hEvent = readComplete.get();

        while (!exitThread)
        {
            DWORD error{};

            // Set up async read on the DVC.
            if (!ReadFile(m_dvcHandle.get(), readBuffer, sizeof(readBuffer), nullptr, &overlappedRead)
                && ((error = GetLastError()) != ERROR_IO_PENDING))
            {
                hr = HRESULT_FROM_WIN32(error);
                DvcListenerThreadExiting(hr, "[DVC] read failure");
                RETURN_HR(hr);
            }

            HANDLE events[] = { m_dvcThreadExit.get(), readComplete.get() };
            LogDebugMessage("[DVC] Listener thread starting to wait");

            // When we reach this point, the DVC listener thread has passed setup phase and is running.
            m_dvcThreadStarted.SetEvent();

            DWORD result = WaitForMultipleObjects(ARRAYSIZE(events), events, FALSE, INFINITE);
            LogDebugMessage("[DVC] Listener thread wait completed (result=0x%x)", result);
            if (result == WAIT_FAILED)
            {
                hr = HRESULT_FROM_WIN32(GetLastError());
                DvcListenerThreadExiting(hr, "[DVC] WaitForMultipleObjects failure");
                RETURN_HR(hr);
            }

            switch (result)
            {
                case WAIT_OBJECT_0:
                    // Thread exit handle signaled.
                    LogDebugMessage("[DVC] Thread exit event handled");
                    return S_OK;

                case WAIT_OBJECT_0 + 1:
                {
                    // DVC read completion.
                    DWORD bytesRead{};
                    if (GetOverlappedResult(m_dvcHandle.get(), &overlappedRead, &bytesRead, FALSE))
                    {
                        const BYTE* pdu{};
                        // Failing to process DVC data will not bubble up the failure, which will end the DVC listener thread. 
                        // As a server, it should be robust to mal-formatted data.
                        if (SUCCEEDED_LOG(ProcessDvcDataChunk(readBuffer, bytesRead, isPartialData, pduBuffer, pduSize, &pdu)))
                        {
                            LOG_IF_FAILED_MSG(ProcessProtocolDataUnit(pdu, pduSize), "Failed to process PDU. Ignore failure.");
                        }
                    }
                    else
                    {
                        hr = HRESULT_FROM_WIN32(GetLastError());
                        DvcListenerThreadExiting(hr, "[DVC] GetOverlappedResult() failed");
                        RETURN_HR(hr);
                    }
                    break;
                }

                default:
                    LOG_HR_MSG(E_UNEXPECTED, "[DVC] Unexpected WaitForMultipleObjects() result: 0x%x. Ignored", result);
            }
        }

        return S_OK;
    }
    CATCH_RETURN()

    HRESULT KozaniDvcServer::ProcessDvcDataChunk(
        _In_reads_(size) const BYTE* data,
        UINT32 size,
        _Inout_ bool& isPartialData,
        _Inout_ std::vector<BYTE>& pduBuffer,
        _Inout_ UINT32& pduSize,
        _Outptr_result_maybenull_ const BYTE** pdu) noexcept try
    {
        *pdu = nullptr;

        // Each DVC data chunk received consists of a header and payload data following it.
        const CHANNEL_PDU_HEADER* header{ reinterpret_cast<const CHANNEL_PDU_HEADER*>(data) };
        const BYTE* chunkPayload{ reinterpret_cast<const BYTE*>(header + 1) };

        auto chunkFlags{ header->flags & CHANNEL_FLAG_ONLY };
        bool isLastChunk{};
        bool copyChunk{};
        switch (chunkFlags)
        {
        case CHANNEL_FLAG_ONLY:
            // Entire Kozani PDU was delivered in a single chunk.
            // The chunk header length field is the total length in bytes of the uncompressed channel data, excluding the header.
            // It cannot be greater than the chunk size excluding the header in this case.
            RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_DATA), header->length > size - sizeof(CHANNEL_PDU_HEADER));

            isPartialData = false;
            pduSize = header->length;
            *pdu = chunkPayload;
            return S_OK;

        case CHANNEL_FLAG_FIRST:
            // First chunk of the Kozani PDU - the data can span multiple Virtual Channel data chunks and the individual chunks will need 
            // to be reassembled in that case. The pduBuffer is used to reassemble the Kozani PDU. Reserve the total size needed.
            pduSize = header->length;
            pduBuffer.clear();
            pduBuffer.reserve(pduSize);
            isPartialData = true;
            copyChunk = true;
            break;

        case CHANNEL_FLAG_MIDDLE:
            // Middle chunk - just needs to be copied. isPartialData must be true to indicate that we saw and copied the first chunk already.
            RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_DATA), !isPartialData);
            copyChunk = true;
            break;

        case CHANNEL_FLAG_LAST:
            // Last chunk - needs to be copied and complete the Kozani PDU.
            // isPartialData must be true to indicate that we saw and copied the first chunk already.
            RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_DATA), !isPartialData);
            copyChunk = true;
            isLastChunk = true;
            isPartialData = false;
            break;

        default:
            FAIL_FAST_MSG("Logic error - should have covered all cases for chunkFlags");
        }

        if (copyChunk)
        {
            auto startingSize = pduBuffer.size();
            auto bytesToCopy = size - sizeof(CHANNEL_PDU_HEADER); // Skip the header.

            // The partial PDU size should not be greater than the total PDU size recorded in the first data chunk.
            RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_DATA), startingSize + bytesToCopy > pduSize);

            pduBuffer.resize(startingSize + bytesToCopy);
            RtlCopyMemory(pduBuffer.data() + startingSize, chunkPayload, bytesToCopy);

            if (isLastChunk)
            {
                // The completed PDU should have a size consistent with the total size of segmented data in the first chunk header.
                RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_DATA), pduBuffer.size() != pduSize);
                *pdu = pduBuffer.data();
            }
        }

        return S_OK;
    }
    CATCH_RETURN()

    HRESULT KozaniDvcServer::ProcessProtocolDataUnit(_In_reads_(size) const BYTE* data, UINT32 size) noexcept try
    {
        Dvc::ProtocolDataUnit pdu;
        if (!pdu.ParseFromArray(data, size))
        {
            RETURN_HR_MSG(E_FAIL, "Failed to parse PDU. size: %u.", size);
        }

        Dvc::ProtocolDataUnit::DataType type{ pdu.type() };
        switch (type)
        {
            case Dvc::ProtocolDataUnit::ActivateAppRequest:
                {
                    // Process the ActivateAppRequest in a separate thread so a long activation will not block subsequent activation requests.
                    auto activateAppThread{ std::thread(&KozaniDvcServer::ProcessActivateAppRequestThreadFunc, this, std::move(pdu)) };
                    activateAppThread.detach();
                }
            
                break;

            default:
                // ToDo: Unsupported PDU type. Return GenericResult message with failure code to client side.
                break;
        }

        return S_OK;
    }
    CATCH_RETURN()

    void KozaniDvcServer::ProcessActivateAppRequestThreadFunc(_In_ Dvc::ProtocolDataUnit pdu) noexcept try
    {
        std::string errorMessage;
        HRESULT hr = LOG_IF_FAILED(ProcessActivateAppRequest(pdu, errorMessage));
        if (FAILED(hr))
        {
            SendActivateAppResult(pdu.activity_id(), hr, 0, errorMessage);
            if (hr != HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS))
            {
                RemoveActivity(pdu.activity_id());
            }
        }
    }
    CATCH_LOG_RETURN()

    HRESULT KozaniDvcServer::ProcessActivateAppRequest(_In_ Dvc::ProtocolDataUnit& pdu, _Out_ std::string& errorMessage) noexcept try
    {
        errorMessage.clear();

        Dvc::ActivateAppRequest activateAppRequest;
        if (!activateAppRequest.ParseFromString(pdu.data()))
        {
            errorMessage = "Failed to parse ActivateAppRequest message";
            RETURN_WIN32(ERROR_INVALID_DATA);
        }

        if (!IsActivationKindSupported(activateAppRequest.activation_kind()))
        {
            errorMessage = "Unsupported activation kind: " + std::to_string(activateAppRequest.activation_kind());
            RETURN_WIN32(ERROR_NOT_SUPPORTED);
        }

        ActivatedAppInfo* appInfo{};
        {
            auto lock{ m_activityMapLock.lock_exclusive() };
            auto inserted{ m_activityMap.emplace(pdu.activity_id(), ActivatedAppInfo()) };
            if (!inserted.second)
            {
                errorMessage = "Activity ID of the new activate app request is already used for a previous request. Each new request must use a new activity ID.";
                RETURN_WIN32(ERROR_ALREADY_EXISTS);
            }

            appInfo = &(inserted.first->second);
        }


        wil::com_ptr<IApplicationActivationManager> aam;
        HRESULT hrCoCreateInstance{ CoCreateInstance(CLSID_ApplicationActivationManager, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&aam)) };
        if (FAILED(hrCoCreateInstance))
        {
            errorMessage = "Failed to CoCreateInstance CLSID_ApplicationActivationManager.";
            RETURN_HR(hrCoCreateInstance);
        }

        std::wstring appUserModelId{ ::Microsoft::Utf8::ToUtf16(activateAppRequest.app_user_model_id()) };

        switch (activateAppRequest.activation_kind())
        {
            case Dvc::ActivationKind::Launch:
                {
                    std::wstring launchArgs;
                    if (!activateAppRequest.arguments().empty())
                    {
                        Dvc::LaunchActivationArgs args;
                        if (!args.ParseFromString(activateAppRequest.arguments()))
                        {
                            errorMessage = "Failed to parse launch arguments";
                            RETURN_WIN32(ERROR_INVALID_DATA);
                        }

                        launchArgs = ::Microsoft::Utf8::ToUtf16(args.arguments());
                    }
                    
                    DWORD processId{};
                    HRESULT hrActivateApp{ aam->ActivateApplication(appUserModelId.c_str(), launchArgs.c_str(), AO_NONE, &processId) };
                    if (FAILED(hrActivateApp))
                    {
                        errorMessage = "Failed to Activate app.";
                        RETURN_HR(hrActivateApp);
                    }

                    appInfo->pid = processId;
                }
                break;

            default:
                break;
        }
        
        SendActivateAppResult(pdu.activity_id(), S_OK, appInfo->pid);
        return S_OK;
    }
    CATCH_RETURN()

    bool KozaniDvcServer::IsActivationKindSupported(Dvc::ActivationKind kind)
    {
        switch (kind)
        {
            case Dvc::ActivationKind::Launch:
            case Dvc::ActivationKind::File:
            case Dvc::ActivationKind::Protocol:
                return true;
        }
        return false;
    }

    void KozaniDvcServer::RemoveActivity(UINT64 activityId)
    {
        auto lock{ m_activityMapLock.lock_exclusive() };
        m_activityMap.erase(activityId);
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

        m_dvcListenerThread = std::thread(&KozaniDvcServer::ProcessDvcIncomingDataThreadFunc, this);

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

    void KozaniDvcServer::DvcListenerThreadExiting(HRESULT errorCode, PCSTR erroMessage) noexcept try
    {
        auto lock{ m_connectionManagerLock.lock_exclusive() };

        if (FAILED(m_errorFromDvcListener))
        {
            // Error has been reported before already.
            return;
        }

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
    CATCH_LOG_RETURN()

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

    void KozaniDvcServer::SendDvcProtocolData(const char* data, UINT32 size)
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
            THROW_HR_MSG(E_UNEXPECTED, "DVC WriteFile only writes %u bytes while %u bytes are expected.", bytesWritten, size);
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

    void KozaniDvcServer::SendConnectionAck(PCSTR connectionId)
    {
        UINT64 activityId{};
        {
            auto lock{ m_newActivityIdLock.lock_exclusive() };
            activityId = m_newActivityId;
            m_newActivityId++;
        }
        
        std::string pdu{ CreateConnectionAckPDU(connectionId, activityId) };
        SendDvcProtocolData(pdu.c_str(), static_cast<UINT32>(pdu.size()));
    }

    void KozaniDvcServer::SendActivateAppResult(
            UINT64 activityId,
            HRESULT hr,
            DWORD appProcessId,
            _In_ const std::string& errorMessage)
    {
        std::string pdu{ CreateActivateAppResultPDU(activityId, hr, appProcessId, errorMessage) };
        SendDvcProtocolData(pdu.c_str(), static_cast<UINT32>(pdu.size()));
    }
}
