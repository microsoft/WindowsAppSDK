#pragma once

#include "AuthRequestParams.h"

struct AuthRequestAsyncOperation :
    winrt::implements<AuthRequestAsyncOperation, foundation::IAsyncOperation<oauth::AuthRequestResult>,
        foundation::IAsyncInfo>
{
    AuthRequestAsyncOperation(const foundation::Uri& authEndpoint, oauth::implementation::AuthRequestParams* params);
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
    enum class state
    {
        connecting,
        reading,
    };

    static void CALLBACK async_callback(PTP_CALLBACK_INSTANCE, PVOID context, PTP_WAIT, TP_WAIT_RESULT waitResult);

    bool try_create_pipe(const winrt::hstring& state);
    void close_pipe();
    void connect_to_new_client();
    void initiate_read();
    void on_read_complete();

    void transition_state(foundation::AsyncStatus status, const foundation::Uri& responseUri = nullptr,
        winrt::hresult hr = {});
    void invoke_handler(const foundation::AsyncOperationCompletedHandler<oauth::AuthRequestResult>& handler);

    std::shared_mutex m_mutex;

    winrt::com_ptr<oauth::implementation::AuthRequestParams> m_params;
    std::wstring m_pipeName;
    HANDLE m_pipe = INVALID_HANDLE_VALUE;
    state m_state = state::connecting;
    OVERLAPPED m_overlapped = {};
    PTP_WAIT m_ptp = nullptr;
    std::vector<std::uint8_t> m_pipeReadData;
    std::uint8_t m_pipeReadBuffer[128];

    // IAsyncOperation state
    oauth::AuthRequestResult m_result{ nullptr };
    bool m_handlerSet = false;
    foundation::AsyncOperationCompletedHandler<oauth::AuthRequestResult> m_handler;
    foundation::AsyncStatus m_status = foundation::AsyncStatus::Started;
    winrt::hresult m_error = {};
};
