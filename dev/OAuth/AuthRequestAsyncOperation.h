// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include <wil/resource.h>

#include "AuthRequestParams.h"

struct AuthRequestAsyncOperation :
    winrt::implements<AuthRequestAsyncOperation, foundation::IAsyncOperation<oauth::AuthRequestResult>,
    foundation::IAsyncInfo>
{
    AuthRequestAsyncOperation(oauth::implementation::AuthRequestParams* params);
    ~AuthRequestAsyncOperation();

    // IAsyncInfo
    winrt::hresult ErrorCode();
    uint32_t Id();
    foundation::AsyncStatus Status();
    void Cancel();
    void Close();

    // IAsyncOperation
    foundation::AsyncOperationCompletedHandler<oauth::AuthRequestResult> Completed();
    void Completed(const foundation::AsyncOperationCompletedHandler<oauth::AuthRequestResult>& handler);
    oauth::AuthRequestResult GetResults();

    // Internal functions
    void complete(const foundation::Uri& responseUri);
    void cancel();
    void error(winrt::hresult hr);

private:
    enum class request_state
    {
        closed,
        connecting,
        reading,
    };

    static void CALLBACK async_callback(PTP_CALLBACK_INSTANCE, PVOID context, PTP_WAIT, TP_WAIT_RESULT waitResult);
    void callback(TP_WAIT_RESULT waitResult);

    bool try_create_pipe(const winrt::hstring& state);
    void close_pipe();
    void connect_to_new_client(bool disconnect = false);
    void initiate_read();
    void on_read_complete();

    void transition_state(foundation::AsyncStatus status, const foundation::Uri& responseUri = nullptr,
        winrt::hresult hr = {});
    void invoke_handler(const foundation::AsyncOperationCompletedHandler<oauth::AuthRequestResult>& handler);

    void destroy();

    std::shared_mutex m_mutex;

    winrt::com_ptr<oauth::implementation::AuthRequestParams> m_params;
    std::wstring m_pipeName;
    wil::unique_handle m_pipe;
    request_state m_state = request_state::connecting;
    OVERLAPPED m_overlapped = {};
    wil::unique_threadpool_wait m_ptp;
    std::vector<std::uint8_t> m_pipeReadData;
    std::uint8_t m_pipeReadBuffer[128];

    // IAsyncOperation state
    oauth::AuthRequestResult m_result{ nullptr };
    bool m_handlerSet = false;
    foundation::AsyncOperationCompletedHandler<oauth::AuthRequestResult> m_handler;
    foundation::AsyncStatus m_status = foundation::AsyncStatus::Started;
    winrt::hresult m_error = {};
};
