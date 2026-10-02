// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "common.h"

#include "OAuth2Manager.h"
#include "AuthRequestAsyncOperation.h"
#include "AuthRequestResult.h"

using namespace std::literals;
using namespace winrt::Microsoft::Security::Authentication::OAuth;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Security::Cryptography;

AuthRequestAsyncOperation::AuthRequestAsyncOperation(implementation::AuthRequestParams* params) :
    m_params(params->get_strong())
{
    try
    {
        // Calling 'finalize' will (1) prevent subsequent changes from being made to the params, (2) validate
        // consistency in the parameters that are set, and (3) throw an exception if 'finalize' was previously called by
        // someone else. If no exception is thrown, it signals that this object effectively owns the request parameters
        // and is able to read and set necessary properties without fear of them being modified by another call
        m_params->finalize();

        if ((m_params->CodeChallengeMethod() != CodeChallengeMethodKind::None) && m_params->CodeChallenge().empty())
        {
            m_params->set_code_challenge(winrt::hstring{ random_base64urlencoded_string(32) });
        }

        if (m_params->State().empty())
        {
            while (true)
            {
                winrt::hstring state{ random_base64urlencoded_string(32) };
                if (try_create_pipe(state))
                {
                    m_params->set_state(state);
                    break;
                }

                // 'FILE_FLAG_FIRST_PIPE_INSTANCE' is documented as failing with 'ERROR_ACCESS_DENIED' if a pipe
                // with the same name has already been created.
                if (auto err = ::GetLastError(); err != ERROR_ACCESS_DENIED)
                {
                    throw winrt::hresult_error(HRESULT_FROM_WIN32(err),
                        L"Generation of a unique state value unexpectedly failed");
                }
            }
        }
        else if (!try_create_pipe(m_params->State()))
        {
            auto err = ::GetLastError();
            auto msg =
                (err == ERROR_ACCESS_DENIED) ? L"Provided state value is not unique" : L"Failed to create named pipe";
            throw winrt::hresult_error(HRESULT_FROM_WIN32(err), msg);
        }

        m_overlapped.hEvent = ::CreateEventW(nullptr, true, false, nullptr);
        if (!m_overlapped.hEvent)
        {
            throw winrt::hresult_error(HRESULT_FROM_WIN32(::GetLastError()), L"Failed to create an event");
        }

        m_ptp.reset(::CreateThreadpoolWait(async_callback, this, nullptr)); // Use reset() to initialize
        if (!m_ptp)
        {
            throw winrt::hresult_error(HRESULT_FROM_WIN32(::GetLastError()), L"Failed to create threadpool wait");
        }
        connect_to_new_client();
    }
    catch (...)
    {
        // Throwing in a constructor will cause the destructor not to run...
        destroy();
        throw;
    }
}

AuthRequestAsyncOperation::~AuthRequestAsyncOperation()
{
    destroy();
}

void AuthRequestAsyncOperation::destroy()
{
    {
        // Expects lock to be held and is required since we haven't ensured all callbacks have completed
        std::unique_lock guard{ m_mutex };
        close_pipe();
    }

    // Note that we don't hold the lock here for two reasons. The big reason is that 'WaitForThreadpoolWaitCallbacks may
    // wait on a callback trying to acquire the lock. The second reason - and the reason we get away with this - is that
    // this code path only gets called on destruction, meaning nothing except callbacks (which we wait for) will access
    // or modify object state
    if (m_ptp)
    {
        if (!::SetThreadpoolWaitEx(m_ptp.get(), nullptr, nullptr, nullptr))
        {
            // False here means that there's a callback in progress. This would realistically only happen if there was
            // a race between the client calling 'Cancel' and someone connecting to the pipe
            ::WaitForThreadpoolWaitCallbacks(m_ptp.get(), true);
        }

        m_ptp.reset();
    }

    if (m_overlapped.hEvent)
    {
        ::CloseHandle(m_overlapped.hEvent);
        m_overlapped.hEvent = nullptr;
    }
}

void AuthRequestAsyncOperation::close_pipe()
{
    auto lastState = std::exchange(m_state, request_state::closed);
    if (lastState == request_state::closed)
    {
        return;
    }

    if (m_pipe)
    {
        ::CancelIoEx(m_pipe.get(), &m_overlapped);
        m_pipe.reset();
    }
}

winrt::hresult AuthRequestAsyncOperation::ErrorCode()
{
    std::shared_lock guard{ m_mutex };
    return m_error;
}

uint32_t AuthRequestAsyncOperation::Id()
{
    return 1; // NOTE: This is copying the C++/WinRT implementation
}

winrt::Windows::Foundation::AsyncStatus AuthRequestAsyncOperation::Status()
{
    std::shared_lock guard{ m_mutex };
    return m_status;
}

void AuthRequestAsyncOperation::Cancel()
{
    winrt::make_self<factory_implementation::OAuth2Manager>()->cancel(this);
}

void AuthRequestAsyncOperation::Close()
{
    // TODO? C++/WinRT does a noop here
}

AsyncOperationCompletedHandler<AuthRequestResult> AuthRequestAsyncOperation::Completed()
{
    std::shared_lock guard{ m_mutex };
    return m_handler;
}

void AuthRequestAsyncOperation::Completed(const AsyncOperationCompletedHandler<AuthRequestResult>& handler)
{
    bool shouldInvoke = false;
    {
        std::lock_guard guard{ m_mutex };
        if (m_handlerSet)
        {
            throw winrt::hresult_illegal_delegate_assignment();
        }

        m_handlerSet = true;
        if (!handler)
        {
            WINRT_ASSERT(!m_handler);
            return;
        }

        if (m_status != winrt::Windows::Foundation::AsyncStatus::Started)
        {
            shouldInvoke = true;
        }
        else
        {
            m_handler = handler;
        }
    }

    if (shouldInvoke)
    {
        invoke_handler(handler);
    }
}

AuthRequestResult AuthRequestAsyncOperation::GetResults()
{
    std::shared_lock guard{ m_mutex };
    if (m_status == winrt::Windows::Foundation::AsyncStatus::Completed)
    {
        return m_result;
    }
    else if (m_error < 0)
    {
        throw winrt::hresult_error(m_error);
    }

    WINRT_ASSERT(m_status == winrt::Windows::Foundation::AsyncStatus::Started);
    throw winrt::hresult_illegal_method_call();
}

void AuthRequestAsyncOperation::complete(const Uri& responseUri)
{
    transition_state(winrt::Windows::Foundation::AsyncStatus::Completed, responseUri);
}

void AuthRequestAsyncOperation::cancel()
{
    transition_state(winrt::Windows::Foundation::AsyncStatus::Canceled, nullptr, HRESULT_FROM_WIN32(ERROR_CANCELLED));
}

void AuthRequestAsyncOperation::error(winrt::hresult hr)
{
    transition_state(winrt::Windows::Foundation::AsyncStatus::Error, nullptr, hr);
}

void AuthRequestAsyncOperation::transition_state(winrt::Windows::Foundation::AsyncStatus status, const Uri& responseUri, winrt::hresult hr)
{
    AsyncOperationCompletedHandler<AuthRequestResult> handler;
    {
        std::lock_guard guard{ m_mutex };
        close_pipe();

        // State change is initiated by OAuth2Manager and should never happen twice
        WINRT_ASSERT(m_status == winrt::Windows::Foundation::AsyncStatus::Started);
        m_status = status;
        m_error = hr;

        if (responseUri)
        {
            WINRT_ASSERT(hr >= 0);
            m_result = winrt::make<implementation::AuthRequestResult>(m_params.get(), responseUri);
        }
        else
        {
            WINRT_ASSERT(hr < 0);
        }

        handler = m_handler;
    }

    if (handler)
    {
        invoke_handler(handler);
    }
}

void CALLBACK AuthRequestAsyncOperation::async_callback(PTP_CALLBACK_INSTANCE, PVOID context, PTP_WAIT,
    TP_WAIT_RESULT waitResult)
{
    auto pThis = static_cast<AuthRequestAsyncOperation*>(context);
    pThis->callback(waitResult);
}

void AuthRequestAsyncOperation::callback(TP_WAIT_RESULT waitResult)
{
    try
    {
        request_state currentState;
        DWORD bytes = 0;
        DWORD overlappedError = ERROR_SUCCESS;
        {
            std::shared_lock guard{ m_mutex };
            currentState = m_state;
            if (currentState == request_state::closed)
            {
                // Nothing productive we can do if the pipe was closed. This also likely means the result was an error
                return;
            }

            if (waitResult == WAIT_OBJECT_0)
            {
                if (!::GetOverlappedResult(m_pipe.get(), &m_overlapped, &bytes, false))
                {
                    overlappedError = ::GetLastError();
                }
            }
        }

        switch (currentState)
        {
        case request_state::connecting:
        {
            WINRT_ASSERT(waitResult == WAIT_OBJECT_0); // TODO: Is this valid? Maybe when we cancelled? Error?
            if (waitResult != WAIT_OBJECT_0)
            {
                WINRT_ASSERT(waitResult == WAIT_TIMEOUT);
                throw winrt::hresult_error(HRESULT_FROM_WIN32(ERROR_TIMEOUT),
                    L"Timed out waiting for a client to connect to the pipe");
            }
            else if (overlappedError != ERROR_SUCCESS)
            {
                // If ConnectNamedClient failed, assume we hit an unrecoverable failure
                throw winrt::hresult_error(HRESULT_FROM_WIN32(overlappedError),
                    L"Failed waiting for a client to connect to the pipe");
            }

            initiate_read();
        }
        break;

        case request_state::reading:
        {
            if (overlappedError == ERROR_MORE_DATA)
            {
                // NOTE: Pipe server is effectively single threaded, hence no synchronization needed here
                m_pipeReadData.insert(m_pipeReadData.end(), m_pipeReadBuffer,
                    m_pipeReadBuffer + m_overlapped.InternalHigh);
                initiate_read(); // Need more data before we can complete
            }
            else if ((waitResult != WAIT_OBJECT_0) || (overlappedError != ERROR_SUCCESS))
            {
                // Ideally we could assume that read timeouts/failures are fatal, however we don't know if the client is
                // trustworthy and we don't want some arbitrary process to bait us into terminating the request
                connect_to_new_client(true);
            }
            else
            {
                on_read_complete();
            }
        }
        break;

        default:
            WINRT_ASSERT(false);
            throw winrt::hresult_error(E_UNEXPECTED, L"Unexpected failure waiting for AuthRequest result");
            break;
        }
    }
    catch (...)
    {
        winrt::make_self<factory_implementation::OAuth2Manager>()->error(this, winrt::to_hresult());
    }
}

bool AuthRequestAsyncOperation::try_create_pipe(const winrt::hstring& state)
{
    // NOTE: Called on construction where no synchronization is needed
    auto name = request_pipe_name(state);
    m_pipe.reset(::CreateNamedPipeW(name.c_str(), PIPE_ACCESS_INBOUND | FILE_FLAG_FIRST_PIPE_INSTANCE | FILE_FLAG_OVERLAPPED,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_REJECT_REMOTE_CLIENTS, 1, 1024, 1024, 0, nullptr));

    if (m_pipe)
    {
        m_pipeName = std::move(name);
        return true;
    }

    return false;
}

void AuthRequestAsyncOperation::connect_to_new_client(bool disconnect)
{
    m_pipeReadData.clear();

    DWORD lastError;
    {
        std::shared_lock guard{ m_mutex };
        if (m_state == request_state::closed)
        {
            return;
        }

        if (disconnect)
        {
            [[maybe_unused]] auto disconnectResult = ::DisconnectNamedPipe(m_pipe.get());
            WINRT_ASSERT(disconnectResult); // TODO: Correct if the client disconnected from us?
        }

        [[maybe_unused]] auto connectResult = ::ConnectNamedPipe(m_pipe.get(), &m_overlapped);
        WINRT_ASSERT(!connectResult); // Only non-zero in asynchronous mode, even if already connected
        lastError = ::GetLastError();
    }

    if (lastError == ERROR_PIPE_CONNECTED)
    {
        // Client already connected
        initiate_read();
    }
    else if (lastError != ERROR_IO_PENDING)
    {
        throw winrt::hresult_error(HRESULT_FROM_WIN32(lastError), L"Failed to listen for clients on the pipe");
    }
    else
    {
        {
            std::lock_guard guard{ m_mutex };
            if (m_state == request_state::closed)
            {
                // Don't set the threadpool wait again as we may have just cleared it!
                return;
            }

            m_state = request_state::connecting;
        }
        ::SetThreadpoolWait(m_ptp.get(), m_overlapped.hEvent, nullptr);
    }
}

void AuthRequestAsyncOperation::initiate_read()
{
    while (true)
    {
        BOOL readResult;
        {
            std::shared_lock guard{ m_mutex };
            if (m_state == request_state::closed)
            {
                // No pipe to read from
                return;
            }

            readResult = ::ReadFile(m_pipe.get(), m_pipeReadBuffer, sizeof(m_pipeReadBuffer), nullptr, &m_overlapped);
        }

        if (readResult)
        {
            // Immediate success. No need to wait
            on_read_complete();
            break;
        }

        auto err = ::GetLastError();
        if (err == ERROR_MORE_DATA)
        {
            // Partial read successful; save data and continue loop to try and read more data
            m_pipeReadData.insert(m_pipeReadData.end(), m_pipeReadBuffer, m_pipeReadBuffer + m_overlapped.InternalHigh);
        }
        else if (err == ERROR_IO_PENDING)
        {
            // Reading asynchronously
            std::lock_guard guard{ m_mutex };
            if (m_state == request_state::closed)
            {
                // Simultaneously closed; don't set the threadpool wait as we may have just cleared it!
                return;
            }

            m_state = request_state::reading;
            std::int64_t timeout = std::chrono::duration_cast<TimeSpan>(-50ms).count(); // 50ms timeout
            ::SetThreadpoolWait(m_ptp.get(), m_overlapped.hEvent, reinterpret_cast<PFILETIME>(&timeout));
            break;
        }
        else
        {
            connect_to_new_client(true);
            break;
        }
    }
}

void AuthRequestAsyncOperation::on_read_complete()
{
    m_pipeReadData.insert(m_pipeReadData.end(), m_pipeReadBuffer, m_pipeReadBuffer + m_overlapped.InternalHigh);

    bool shouldReconnect = true;
    try
    {
        auto expectedState = m_params->State();
        auto encryptedBuffer = CryptographicBuffer::CreateFromByteArray(m_pipeReadData);
        auto uriString = decrypt(encryptedBuffer, expectedState);

        // An exception is unlikely (we needed the state from the URI to open the pipe in the first place), but could
        // happen if someone is connecting and sending garbage data. We'll catch below, so all is okay
        Uri responseUri(uriString);
        winrt::hstring state;
        auto tryFindState = [&](const winrt::hstring& str)
        {
            if (str.empty())
            {
                return; // Avoid unnecessary construction/activation
            }

            for (auto&& entry : WwwFormUrlDecoder(str))
            {
                if (entry.Name() == L"state")
                {
                    state = entry.Value();
                    break;
                }
            }
        };

        tryFindState(responseUri.Query());
        if (state.empty())
        {
            tryFindState(fragment_component(responseUri));
        }

        if (state == expectedState)
        {
            shouldReconnect =
                winrt::make_self<factory_implementation::OAuth2Manager>()->try_complete_local(state, responseUri);
        }
    }
    catch (...)
    {
        // Likely handed bad data; just disconnect and attempt a reconnect
    }

    if (shouldReconnect)
    {
        connect_to_new_client(true);
    }
    // Otherwise the 'try_complete_local' call should have closed the pipe
}

void AuthRequestAsyncOperation::invoke_handler(const AsyncOperationCompletedHandler<AuthRequestResult>& handler)
{
    try
    {
        handler(*this, m_status);
    }
    catch (...)
    {
        // Just eat exceptions as they're not relevant to the caller at all
    }
}
