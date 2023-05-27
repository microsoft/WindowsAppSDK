// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include <pchannel.h>
#include <Kozani.DVC.pb.h>

#include "KozaniDvcServer.h"
#include "Module.h"

using namespace Microsoft::Kozani::DvcProtocol;

namespace Microsoft::Kozani::KozaniRemoteManager
{
    void CALLBACK KozaniDvcServer::ProcessTerminationCallback(_In_ PVOID parameter, _In_ BOOLEAN timerOrWaitFired) noexcept try
    {
        if (timerOrWaitFired)
        {
            // Timer timed out. This shouldn't happen as we wait infinite time. 
            LOG_HR_MSG(E_UNEXPECTED, "Wait timed out tracking process lifetime.");
            return;
        }

        AppActivationInfo* appInfo{ reinterpret_cast<AppActivationInfo*>(parameter) };
        KozaniRemoteManagerModule::GetConnectionManagerInstance().ProcessAppTermination(appInfo);
    }
    CATCH_LOG_RETURN()

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

    HRESULT KozaniDvcServer::EnableConnectionManagerReporting()
    {
        auto lock{ m_errorReportingLock.lock_exclusive() };

        if (FAILED(m_errorFromDvcListener))
        {
            // DVC listener thread has encountered error before ConnectionManager reporting is enabled. Return the failure right away.
            return m_errorFromDvcListener;
        }

        if (FAILED(m_errorFromDvcWriter))
        {
            // DVC writer has encountered error before ConnectionManager reporting is enabled. Return the failure right away.
            return m_errorFromDvcWriter;
        }

        m_errorReportingEnabled = true;
        return S_OK;
    }

    void KozaniDvcServer::OpenDvc()
    {
        auto lock{ std::unique_lock<std::recursive_mutex>(m_dvcLock) };

        wil::unique_channel_handle wtsHandle{ 
            ::WTSVirtualChannelOpenEx(WTS_CURRENT_SESSION, const_cast<LPSTR>(DvcChannelName), WTS_CHANNEL_OPTION_DYNAMIC) };

        // If wtsHandle is nullptr, the DVC channel doesn't exist. It could mean the current session is not a remote session or 
        // the client of this remote session has not created a listener of this DVC channel. It is required that the client has 
        // created a DVC channel listener to listen to this specific channel name before the server can open the named DVC channel. 
        // Otherwise, ERROR_GEN_FAILURE (31) may be returned.
        THROW_LAST_ERROR_IF_NULL(wtsHandle);

        wil::unique_wtsmem_ptr<void> fileHandleBuffer;
        DWORD len{};
        THROW_IF_WIN32_BOOL_FALSE(::WTSVirtualChannelQuery(wtsHandle.get(), WTSVirtualFileHandle, wil::out_param(fileHandleBuffer), &len));
        THROW_HR_IF(E_UNEXPECTED, (len != sizeof(HANDLE)));

        THROW_IF_WIN32_BOOL_FALSE(::DuplicateHandle(::GetCurrentProcess(), *reinterpret_cast<HANDLE*>(fileHandleBuffer.get()),
            ::GetCurrentProcess(), m_dvcHandle.put(), 0, FALSE, DUPLICATE_SAME_ACCESS));
    }

    // This function will be executed in a separate thread from the main thread and shouldn't throw any exceptions.
    // Any uncaught exceptions will cause the process to terminate.
    void KozaniDvcServer::ProcessDvcIncomingDataThreadFunc() noexcept try
    {
        const HRESULT hr{ LOG_IF_FAILED(ProcessDvcIncomingData()) };
        if (FAILED(hr))
        {
            DvcListenerThreadExiting(hr, "Failed to process incoming DVC data");
        }
    }
    CATCH_LOG_RETURN()

    HRESULT KozaniDvcServer::ProcessDvcIncomingData() noexcept try
    {
        bool exitThread{};
        wil::unique_event_nothrow readComplete;
        HRESULT hr{ LOG_IF_FAILED(readComplete.create()) };
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
            // Set up async read on the DVC.
            DWORD error{};
            if (!ReadFile(m_dvcHandle.get(), readBuffer, sizeof(readBuffer), nullptr, &overlappedRead)
                && ((error = GetLastError()) != ERROR_IO_PENDING))
            {
                hr = HRESULT_FROM_WIN32(error);
                DvcListenerThreadExiting(hr, "[DVC] read failure");
                RETURN_HR(hr);
            }

            HANDLE events[]{ m_dvcThreadExit.get(), readComplete.get() };
            LOG_HR_MSG(KOZANI_E_INFO, "[DVC] Listener thread starting to wait");

            // When we reach this point, the DVC listener thread has passed setup phase and is running.
            m_dvcThreadStarted.SetEvent();

            const DWORD result{ WaitForMultipleObjects(ARRAYSIZE(events), events, FALSE, INFINITE) };
            LOG_HR_MSG(KOZANI_E_INFO, "[DVC] Listener thread wait completed (result=0x%x)", result);
            if (result == WAIT_FAILED)
            {
                hr = HRESULT_FROM_WIN32(GetLastError());
                DvcListenerThreadExiting(hr, "[DVC] WaitForMultipleObjects failure");
                RETURN_HR(hr);
            }

            switch (result)
            {
                case WAIT_OBJECT_0:
                {
                    // Thread exit handle signaled.
                    LOG_HR_MSG(KOZANI_E_INFO, "[DVC] Thread exit event handled");
                    return S_OK;
                }

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
        bool& isPartialData,
        std::vector<BYTE>& pduBuffer,
        UINT32& pduSize,
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
            memcpy(pduBuffer.data() + startingSize, chunkPayload, bytesToCopy);

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
            RETURN_HR_MSG(KOZANI_E_BAD_PDU, "Failed to parse PDU. size: %u.", size);
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

            case Dvc::ProtocolDataUnit::AppTerminationNotice:
                RETURN_IF_FAILED(ProcessAppTerminationNotice(pdu));
                break;

            default:
                // ToDo: https://task.ms/43963854 Unsupported PDU type. Return GenericResult message with failure code to client side.
                break;
        }

        return S_OK;
    }
    CATCH_RETURN()

    void KozaniDvcServer::ProcessActivateAppRequestThreadFunc(_In_ Dvc::ProtocolDataUnit pdu) noexcept try
    {
        bool appActivatedAndTracked{};
        std::string errorMessage;
        const HRESULT hr{ LOG_IF_FAILED(ProcessActivateAppRequest(pdu, appActivatedAndTracked, errorMessage)) };

        // If ProcessActivateAppRequest failed but appActivatedAndTracked is true, it means there was failure after the app was activated and 
        // its process lifetime tracked. Such failure is benign and we should not send failure ActivateAppResult to client.
        if (FAILED(hr) && !appActivatedAndTracked)
        {
            SendActivateAppResult(pdu.activity_id(), hr, 0, false, errorMessage);

            // ERROR_ALREADY_EXISTS is due to the activity Id being the same as an existing activity already tracked in the m_activityMap. 
            // Do not remove it from the map. 
            if (hr != HRESULT_FROM_WIN32(ERROR_ALREADY_EXISTS))
            {
                ConnectionManager& connectionManager{ KozaniRemoteManagerModule::GetConnectionManagerInstance() };
                auto lock{ connectionManager.m_activityMapLock.lock_exclusive() };
                if (connectionManager.m_closing)
                {
                    return;
                }

                connectionManager.m_activityMap.erase(pdu.activity_id());
            }
        }
    }
    CATCH_LOG_RETURN()

    HRESULT KozaniDvcServer::ProcessActivateAppRequest(
        _In_ Dvc::ProtocolDataUnit& pdu, 
        _Out_ bool& appActivatedAndTracked, 
        _Out_ std::string& errorMessage) noexcept try
    {
        appActivatedAndTracked = false;
        errorMessage.clear();

        Dvc::ActivateAppRequest activateAppRequest;
        if (!activateAppRequest.ParseFromString(pdu.data()))
        {
            errorMessage = "Failed to parse ActivateAppRequest message";
            RETURN_HR(KOZANI_E_BAD_PDU);
        }

        if (!IsActivationKindSupported(activateAppRequest.activation_kind()))
        {
            errorMessage = "Unsupported activation kind: " + std::to_string(activateAppRequest.activation_kind());
            RETURN_HR(KOZANI_E_UNSUPPORTED_ACTIVATION_KIND);
        }

        {
            // Acquire lock before adding the activity Id to the m_activityMap but do not hold the lock while activating the app as 
            // that can take some time and we do not want one app activation to block others.
            ConnectionManager& connectionManager{ KozaniRemoteManagerModule::GetConnectionManagerInstance() };
            auto lock{ connectionManager.m_activityMapLock.lock_exclusive() };
            RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_STATE), connectionManager.m_closing);

            auto inserted{ connectionManager.m_activityMap.emplace(pdu.activity_id(), AppActivationInfo(pdu.activity_id())) };
            if (!inserted.second)
            {
                errorMessage = "Activity ID of the new activate app request is already used for a previous request. Each new request must use a new activity ID.";
                RETURN_WIN32(ERROR_ALREADY_EXISTS);
            }
        }

        wil::com_ptr<IApplicationActivationManager> aam;
        HRESULT hrCoCreateInstance{ CoCreateInstance(CLSID_ApplicationActivationManager, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&aam)) };
        if (FAILED(hrCoCreateInstance))
        {
            errorMessage = "Failed to CoCreateInstance CLSID_ApplicationActivationManager.";
            RETURN_HR(hrCoCreateInstance);
        }

        std::wstring appUserModelId{ ::Microsoft::Utf8::ToUtf16(activateAppRequest.app_user_model_id()) };
        DWORD processId{};
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
                    
                    HRESULT hrActivateApp{ aam->ActivateApplication(appUserModelId.c_str(), launchArgs.c_str(), AO_NONE, &processId) };
                    if (FAILED(hrActivateApp))
                    {
                        errorMessage = "Failed to Activate app.";
                        RETURN_HR(hrActivateApp);
                    }
                }
                break;

            case Dvc::ActivationKind::File:
                RETURN_IF_FAILED(ProcessFileActivationRequest(aam.get(), appUserModelId, activateAppRequest, processId, errorMessage));
                break;

            case Dvc::ActivationKind::Protocol:
                // ToDo: https://task.ms/43963854 support protocol launch.
                break;

            default:
                FAIL_FAST_MSG("Logic error - should have handled all supported launch contracts.");
                break;
        }
        
        // When we reach here, activation is successful.
        bool isNewInstance{};
        {
            ConnectionManager& connectionManager{ KozaniRemoteManagerModule::GetConnectionManagerInstance() };
            auto lock{ connectionManager.m_activityMapLock.lock_exclusive() };
            RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_STATE), connectionManager.m_closing);

            auto iter{ connectionManager.m_activityMap.find(pdu.activity_id()) };
            if (iter == connectionManager.m_activityMap.end())
            {
                // Rare case - the app is terminated right after launch and the activity has been removed from the map from the other thread tracking 
                // the lifetime of the process, before reaching here. There is nothing to do after that.
                return S_OK;
            }

            AppActivationInfo& appInfo{ iter->second };
            if (appInfo.activationStatus == AppActivationStatus::TerminationRequestedFromClient)
            {
                // The client has already requested termination of the app. Honor it now. 
                wil::unique_handle process{ OpenProcess(PROCESS_TERMINATE, FALSE, processId) };
                if (process)
                {
                    LOG_IF_WIN32_BOOL_FALSE_MSG(TerminateProcess(process.get(), 0), "Failed to terminate process %u", processId);
                }
                else
                {
                    LOG_LAST_ERROR_MSG("Failed to open process %u with PROCESS_TERMINATE access right.", processId);
                }

                // Remove the activity entry from the m_activityMap as we no longer track it.
                connectionManager.m_activityMap.erase(iter);
                return S_OK;
            }

            auto pidAdded{ connectionManager.m_processIdMap.emplace(processId, pdu.activity_id()) };
            if (pidAdded.second)
            {
                // New process Id in the tracking map. The activation creates a new process.
                isNewInstance = true;
                appInfo.pid = processId;

                // Track lifetime of the process.
                appInfo.processHandle.reset(OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, FALSE, processId));
                if (!appInfo.processHandle)
                {
                    const DWORD errorOpenProcess{ LOG_LAST_ERROR_MSG("ProcessId: %u", processId) };

                    connectionManager.m_activityMap.erase(iter);
                    errorMessage = "Failed to OpenProcess after the app is activated. The app may have crashed. Process Id: " + std::to_string(processId);
                    RETURN_WIN32(errorOpenProcess);
                }

                appInfo.activationStatus = AppActivationStatus::ActivationSucceeded;

                // Failure to register wait handle tracking the new process lifetime is not fatal and should ot send failed ActivateAppResult back to client.
                HRESULT hrRegisterWait{ LOG_IF_WIN32_BOOL_FALSE_MSG(RegisterWaitForSingleObject(
                    &appInfo.processLifetimeTrackerHandle, appInfo.processHandle.get(), ProcessTerminationCallback, &appInfo, INFINITE, WT_EXECUTEONLYONCE),
                    "Failed to register process lifetime tracking thread after the app is activated. Process Id: %u", processId) };
                if (SUCCEEDED(hrRegisterWait))
                {
                    appActivatedAndTracked = true;
                }
            }
            else
            {
                // The process Id is already in the m_processIdMap, which means the app activation does not create a new process.
                // Apps can be single instance, which will use the same process to respond to multiple activations. 
                // Remove the activity entry from the m_activityMap as we will not track duplicated activities backed by the same process.
                connectionManager.m_activityMap.erase(iter);
            }
        }

        SendActivateAppResult(pdu.activity_id(), S_OK, processId, isNewInstance);
        return S_OK;
    }
    CATCH_RETURN()

    HRESULT KozaniDvcServer::ProcessFileActivationRequest(
        _In_ IApplicationActivationManager* aam,
        const std::wstring& appUserModelId,
        const Dvc::ActivateAppRequest& activateAppRequest,
        _Out_ DWORD& processId,
        _Out_ std::string& errorMessage) noexcept try
    {
        if (activateAppRequest.arguments().empty())
        {
            errorMessage = "Arguments for File activation cannot be empty";
            RETURN_WIN32(ERROR_INVALID_DATA);
        }

        Dvc::FileActivationArgs args;
        if (!args.ParseFromString(activateAppRequest.arguments()))
        {
            errorMessage = "Failed to parse File activation arguments";
            RETURN_WIN32(ERROR_INVALID_DATA);
        }

        int filePathsCount{ args.file_paths_size() };

        // There should be at least 1 file path in the FileActivationArgs for file activation to work.
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_DATA), filePathsCount <= 0);

        wistd::unique_ptr<PIDLIST_ABSOLUTE> filePaths(new PIDLIST_ABSOLUTE[filePathsCount]);
        RETURN_IF_NULL_ALLOC(filePaths);

        PIDLIST_ABSOLUTE* pidlistFilePaths{ filePaths.get() };
        ZeroMemory(pidlistFilePaths, sizeof(PIDLIST_ABSOLUTE) * filePathsCount);

        auto freeFilePaths{ wil::scope_exit([&]()
        {
            for (int i = 0; i < filePathsCount; i++)
            {
                if (pidlistFilePaths[i])
                {
                    CoTaskMemFree(pidlistFilePaths[i]);
                }
            }
        }) };

        for (int i = 0; i < filePathsCount; i++)
        {
            std::wstring clientLocalPath{ ::Microsoft::Utf8::ToUtf16(args.file_paths(i)) };
            std::wstring redirectedClientPath{ GetRedirectedClientPath(clientLocalPath) };
            RETURN_IF_FAILED(SHParseDisplayName(redirectedClientPath.c_str(), nullptr, &pidlistFilePaths[i], 0, nullptr));
        }

        wil::com_ptr<IShellItemArray> filePathArray;
        RETURN_IF_FAILED(SHCreateShellItemArrayFromIDLists(filePathsCount, const_cast<LPCITEMIDLIST*>(pidlistFilePaths), &filePathArray));
        
        std::wstring verb{ ::Microsoft::Utf8::ToUtf16(args.verb()) };
        HRESULT hrActivateApp{ aam->ActivateForFile(appUserModelId.c_str(), filePathArray.get(), verb.c_str(), &processId)};
        if (FAILED(hrActivateApp))
        {
            errorMessage = "Failed to Activate app for file.";
            RETURN_HR(hrActivateApp);
        }

        return S_OK;
    }
    CATCH_RETURN()

    HRESULT KozaniDvcServer::ProcessAppTerminationNotice(_In_ Dvc::ProtocolDataUnit& pdu) noexcept try
    {
        ConnectionManager& connectionManager{ KozaniRemoteManagerModule::GetConnectionManagerInstance() };
        auto lock{ connectionManager.m_activityMapLock.lock_exclusive() };
        RETURN_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_STATE), connectionManager.m_closing);

        auto iter{ connectionManager.m_activityMap.find(pdu.activity_id()) };
        if (iter == connectionManager.m_activityMap.end())
        {
            RETURN_HR_MSG(HRESULT_FROM_WIN32(ERROR_NOT_FOUND), "The activity Id %I64u does not exist in the activity map", pdu.activity_id());
        }

        auto& appInfo{ iter->second };
        appInfo.activationStatus = AppActivationStatus::TerminationRequestedFromClient;

        if (appInfo.pid == 0)
        {
            // The app activation has not finished yet. It will be terminated immediately upon activation since it is 
            // marked with AppActivationStatus::TerminationRequestedFromClient. 
            return S_OK;
        }

        FAIL_FAST_IF_MSG(!appInfo.processHandle, "Process handle should be valid when pid is not zero");

        const HRESULT hrTerminateProcess{ LOG_IF_WIN32_BOOL_FALSE_MSG(TerminateProcess(appInfo.processHandle.get(), 0), "Failed to terminate process %u", appInfo.pid) };

        if (!appInfo.processLifetimeTrackerHandle)
        {
            // No process lifetime tracker to handle at ProcessTerminationCallback - we should clean up the maps here.
            connectionManager.m_processIdMap.erase(appInfo.pid);
            connectionManager.m_activityMap.erase(iter);
        }

        RETURN_HR(hrTerminateProcess);
    }
    CATCH_RETURN()

    // Convert local path from the remote client to a path that can be addressed by the remote desktop server. Local drives of the client have been 
    // rediected to the server so the server can directly access them. For example, local path "C:\data\MyFile.txt" will be redirected to the server
    // side with addressable path "\\tsclient\C\data\MyFile.txt"
    std::wstring KozaniDvcServer::GetRedirectedClientPath(const std::wstring& localPath)
    {
        // UNC paths are not redirected so we return it as it is.
        if (localPath.starts_with(L"\\\\"))
        {
            return localPath;
        }

        std::wstring redirectedPath{ L"\\\\tsclient\\" };
        redirectedPath += localPath[0];
        redirectedPath += localPath.substr(2);
        return redirectedPath;
    }

    bool KozaniDvcServer::IsActivationKindSupported(Dvc::ActivationKind kind)
    {
        switch (kind)
        {
            case Dvc::ActivationKind::Launch:
                [[fallthrough]];
            case Dvc::ActivationKind::File:
                [[fallthrough]];
            case Dvc::ActivationKind::Protocol:
                return true;
        }
        return false;
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
        LOG_HR_MSG(KOZANI_E_INFO, "[StartDvcListenerThread] Waiting for listener thread starting status");

        // Wait for listerner thread to start successfully. Wait no longer than 5s. 
        DWORD result = WaitForMultipleObjects(ARRAYSIZE(events), events, FALSE, 5000);
        THROW_LAST_ERROR_IF_MSG(result == WAIT_FAILED, "[StartDvcListenerThread] WaitForMultipleObjects() failed.");

        switch (result)
        {
            case WAIT_OBJECT_0:
                // Thread successfully started and is running.
                LOG_HR_MSG(KOZANI_E_INFO, "[StartDvcListenerThread] Listener thread successfully started");
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
        auto lock{ m_errorReportingLock.lock_exclusive() };

        if (FAILED(m_errorFromDvcListener))
        {
            // Error has been reported before already.
            return;
        }

        m_errorFromDvcListener = errorCode;
        LOG_HR_MSG(errorCode, "DVC listener thread exiting. Error message: %s", erroMessage);

        m_dvcThreadExit.SetEvent();

        {
            // Close the DVC handle as this DVC server is going to be shut down without a functional listener thread.
            auto lockDvc{ std::unique_lock<std::recursive_mutex>(m_dvcLock) };
            m_dvcHandle.reset();
        }

        if (m_errorReportingEnabled)
        {
            KozaniRemoteManagerModule::GetConnectionManagerInstance().ReportDvcServerError(errorCode);
        }
    }
    CATCH_LOG_RETURN()

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
        auto lock{ m_errorReportingLock.lock_exclusive() };

        m_errorFromDvcWriter = errorCode;

        // Failure to write to DVC channel is fatal. Will notify the DVC listener thread to exit.
        m_dvcThreadExit.SetEvent();

        {
            // Close the DVC handle as this DVC server is going to be shut down. 
            auto lockDvc{ std::unique_lock<std::recursive_mutex>(m_dvcLock) };
            m_dvcHandle.reset();
        }

        if (m_errorReportingEnabled)
        {
            KozaniRemoteManagerModule::GetConnectionManagerInstance().ReportDvcServerError(errorCode);
        }
    }

    void KozaniDvcServer::SendConnectionAck(PCSTR connectionId)
    {
        uint64_t activityId{ KozaniRemoteManagerModule::GetConnectionManagerInstance().GetNewActivityId() };
        
        std::string pdu{ CreateConnectionAckPdu(connectionId, activityId) };
        SendDvcProtocolData(pdu.c_str(), static_cast<UINT32>(pdu.size()));
    }

    void KozaniDvcServer::SendActivateAppResult(
            uint64_t activityId,
            HRESULT hr,
            DWORD appProcessId,
            bool isNewInstance,
            _In_ const std::string& errorMessage)
    {
        std::string pdu{ CreateActivateAppResultPdu(activityId, hr, appProcessId, isNewInstance, errorMessage) };
        SendDvcProtocolData(pdu.c_str(), static_cast<UINT32>(pdu.size()));
    }

    void KozaniDvcServer::SendAppTerminationNotice(uint64_t activityId)
    {
        std::string pdu{ CreateAppTerminationNoticePdu(activityId) };
        SendDvcProtocolData(pdu.c_str(), static_cast<UINT32>(pdu.size()));
    }
}
