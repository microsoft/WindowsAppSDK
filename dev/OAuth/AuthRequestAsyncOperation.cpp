#include <pch.h>
#include "common.h"

#include "AuthManager.h"
#include "AuthRequestAsyncOperation.h"
#include "AuthRequestResult.h"

#include <shellapi.h>

using namespace std::literals;
using namespace winrt::Microsoft::Windows::Security::Authentication::OAuth;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Security::Cryptography;

AuthRequestAsyncOperation::AuthRequestAsyncOperation(const Uri& authEndpoint,
    implementation::AuthRequestParams* params) :
    m_params(params->get_strong())
{
    try
    {
        // Calling 'finalize' will (1) prevent subsequent changes from being made to the params, (2) validate
        // consistency in the parameters that are set, and (3) throw an exception if 'finalize' was previously called by
        // someone else. If no exception is thrown, it signals that this object effectively owns the request parameters
        // and is able to read and set necessary properties without fear of them being modified by another call
        m_params->finalize();

        if ((m_params->CodeChallengeMethod() != CodeChallengeMethodKind::None) && m_params->CodeVerifier().empty())
        {
            m_params->set_code_verifier(winrt::hstring{ random_base64urlencoded_string(32) });
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

        m_ptp = ::CreateThreadpoolWait(async_callback, this, nullptr);
        connect_to_new_client();
    }
    catch (...)
    {
        // Throwing in a constructor will cause the destructor not to run...
        close_pipe();
        throw;
    }
}

AuthRequestAsyncOperation::~AuthRequestAsyncOperation()
{
    close_pipe();
}

void AuthRequestAsyncOperation::close_pipe()
{
    if (m_state == state::reading)
    {
        // TODO: Might this trigger a callback? If so, we may end up trying to perform more operations... Might need
        // some synchronization and another state value here.
        ::CancelIoEx(m_pipe, &m_overlapped);
    }

    if (m_ptp)
    {
        if (!::SetThreadpoolWaitEx(m_ptp, nullptr, nullptr, nullptr))
        {
            // False here means that there's a callback in progress. This would realistically only happen if there was
            // a race between the client calling 'Cancel' and someone connecting to the pipe
            ::WaitForThreadpoolWaitCallbacks(m_ptp, true);
        }

        ::CloseThreadpoolWait(m_ptp);
        m_ptp = nullptr;
    }

    if (m_overlapped.hEvent)
    {
        ::CloseHandle(m_overlapped.hEvent);
        m_overlapped.hEvent = nullptr;
    }

    if (m_pipe != INVALID_HANDLE_VALUE)
    {
        ::CloseHandle(m_pipe);
        m_pipe = INVALID_HANDLE_VALUE;
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
    winrt::make_self<factory_implementation::AuthManager>()->cancel(this);
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

        if (m_status != AsyncStatus::Started)
        {
            shouldInvoke = true;
        }
        else if (handler.try_as<::IAgileObject>())
        {
            m_handler = handler;
        }
        else
        {
            try
            {
                auto ref = winrt::make_agile(handler);
                m_handler = [ref = std::move(ref)](const IAsyncOperation<AuthRequestResult>& op, AsyncStatus status) {
                    ref.get()(op, status);
                };
            }
            catch (...)
            {
                m_handler = handler;
            }
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
    if (m_status == AsyncStatus::Completed)
    {
        return m_result;
    }
    else if (m_error < 0)
    {
        throw winrt::hresult_error(m_error);
    }

    WINRT_ASSERT(m_status == AsyncStatus::Started);
    throw winrt::hresult_illegal_method_call();
}

void AuthRequestAsyncOperation::complete(const Uri& responseUri)
{
    transition_state(AsyncStatus::Completed, responseUri);
}

void AuthRequestAsyncOperation::cancel()
{
    transition_state(AsyncStatus::Canceled, nullptr, HRESULT_FROM_WIN32(ERROR_CANCELLED));
}

void AuthRequestAsyncOperation::error(winrt::hresult hr)
{
    transition_state(AsyncStatus::Error, nullptr, hr);
}

void AuthRequestAsyncOperation::transition_state(AsyncStatus status, const Uri& responseUri, winrt::hresult hr)
{
    AsyncOperationCompletedHandler<AuthRequestResult> handler;
    {
        std::lock_guard guard{ m_mutex };
        // TODO: Should probably close pipe, however we might be in a callback which would deadlock...

        // State change is initiated by AuthManager and should never happen twice
        WINRT_ASSERT(m_status == AsyncStatus::Started);
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

    try
    {
        DWORD bytes = 0;
        DWORD overlappedError = ERROR_SUCCESS;
        if (waitResult == WAIT_OBJECT_0)
        {
            if (!::GetOverlappedResult(pThis->m_pipe, &pThis->m_overlapped, &bytes, false))
            {
                overlappedError = ::GetLastError();
            }
        }

        switch (pThis->m_state)
        {
        case state::connecting: {
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

            pThis->initiate_read();
        }
        break;

        case state::reading: {
            if (overlappedError == ERROR_MORE_DATA)
            {
                pThis->m_pipeReadData.insert(pThis->m_pipeReadData.end(), pThis->m_pipeReadBuffer,
                    pThis->m_pipeReadBuffer + pThis->m_overlapped.InternalHigh);
                pThis->initiate_read(); // Need more data before we can complete
            }
            else if ((waitResult != WAIT_OBJECT_0) || (overlappedError != ERROR_SUCCESS))
            {
                // Ideally we could assume that read timeouts/failures are fatal, however we don't know if the client is
                // trustworthy and we don't want some arbitrary process to bait us into terminating the request
                [[maybe_unused]] auto disconnectResult = ::DisconnectNamedPipe(pThis->m_pipe);
                WINRT_ASSERT(disconnectResult); // TODO: What if the client disconnected from us?
                pThis->connect_to_new_client();
            }
            else
            {
                pThis->on_read_complete();
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
        winrt::make_self<factory_implementation::AuthManager>()->error(pThis, winrt::to_hresult());
    }
}

bool AuthRequestAsyncOperation::try_create_pipe(const winrt::hstring& state)
{
    auto name = request_pipe_name(state);
    m_pipe =
        ::CreateNamedPipeW(name.c_str(), PIPE_ACCESS_INBOUND | FILE_FLAG_FIRST_PIPE_INSTANCE | FILE_FLAG_OVERLAPPED,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_REJECT_REMOTE_CLIENTS, 1, 1024, 1024, 0, nullptr);

    if (m_pipe != INVALID_HANDLE_VALUE)
    {
        m_pipeName = std::move(name);
        return true;
    }

    return false;
}

void AuthRequestAsyncOperation::connect_to_new_client()
{
    m_pipeReadData.clear();

    [[maybe_unused]] auto connectResult = ::ConnectNamedPipe(m_pipe, &m_overlapped);
    WINRT_ASSERT(!connectResult); // Only non-zero in synchronous mode, even if already connected
    if (auto err = ::GetLastError(); err == ERROR_PIPE_CONNECTED)
    {
        // Client already connected
        initiate_read();
    }
    else if (err != ERROR_IO_PENDING)
    {
        throw winrt::hresult_error(HRESULT_FROM_WIN32(err), L"Failed to listen for clients on the pipe");
    }
    else
    {
        m_state = state::connecting;
        ::SetThreadpoolWait(m_ptp, m_overlapped.hEvent, nullptr);
    }
}

void AuthRequestAsyncOperation::initiate_read()
{
    while (true)
    {
        if (::ReadFile(m_pipe, m_pipeReadBuffer, sizeof(m_pipeReadBuffer), nullptr, &m_overlapped))
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
            m_state = state::reading;
            std::int64_t timeout = std::chrono::duration_cast<TimeSpan>(-50ms).count(); // 50ms timeout
            ::SetThreadpoolWait(m_ptp, m_overlapped.hEvent, reinterpret_cast<PFILETIME>(&timeout));
            break;
        }
        else
        {
            // Ideally we could assume that read timeouts/failures are fatal, however we don't know if the client is
            // trustworthy and we don't want some arbitrary process to bait us into terminating the request
            [[maybe_unused]] auto disconnectResult = ::DisconnectNamedPipe(m_pipe);
            WINRT_ASSERT(disconnectResult); // TODO: What if the client disconnected from us?
            connect_to_new_client();
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
        Uri responseUri(uriString);

        // An exception is unlikely (we needed the state from the URI to open the pipe in the first place), but could
        // happen if someone is connecting and sending garbage data. We'll catch below, so all is okay
        auto state = responseUri.QueryParsed().GetFirstValueByName(L"state");
        if (state == expectedState)
        {
            if (winrt::make_self<factory_implementation::AuthManager>()->try_complete_local(state, responseUri))
            {
                shouldReconnect = false;
            }
        }
    }
    catch (...)
    {
        // Likely handed bad data; just disconnect and attempt a reconnect
    }

    // The client will only ever send a single message, so disconnect and form a new connection
    [[maybe_unused]] auto disconnectResult = ::DisconnectNamedPipe(m_pipe);
    WINRT_ASSERT(disconnectResult); // TODO

    if (shouldReconnect)
    {
        connect_to_new_client();
    }
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
