
#include <memory>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#include <Windows.h>

#include <detours.h>
#include <http.h>
#include <OAuthTestValues.h>
#include <shellapi.h>
#include <WexTestClass.h>
#include <WindowsAppRuntime.Test.Bootstrap.h>
#include <WinSock2.h>

#include <winrt/Microsoft.Windows.Security.Authentication.OAuth.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Storage.Streams.h>

#include <wil/resource.h> // Included last to enable the most features

#define VERIFY_WINSOCK_SUCCEEDED(expr) \
    do { \
        auto wsaResultCode = (expr); \
        if (wsaResultCode == SOCKET_ERROR) { \
            auto wsaLastError = ::WSAGetLastError(); \
            std::wstring msg = L"WSASucceeded(" #expr ") - Error (" + std::to_wstring(wsaLastError) + L")"; \
            WEX::TestExecution::Verify::Fail(msg.c_str(), WEX::TestExecution::ErrorInfo{ __WFILE__, __WFUNCTION__, __LINE__ }); \
        } \
    } while(0, 0)

using namespace std::literals;
using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;
using namespace winrt::Microsoft::Windows::Security::Authentication::OAuth;
using namespace winrt::Windows::Data::Json;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Security::Cryptography;
using namespace winrt::Windows::Storage::Streams;

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

struct OAuthTests
{
    BEGIN_TEST_CLASS(OAuthTests)
        TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
    END_TEST_CLASS()

    TEST_CLASS_SETUP(Setup)
    {
        Test::Bootstrap::Setup();

        // Detour ShellExecuteW
        ::DetourTransactionBegin();
        ::DetourUpdateThread(::GetCurrentThread());
        if (auto err = ::DetourAttach(reinterpret_cast<void**>(&RealShellExecuteW), &DetouredShellExecuteW))
        {
            Log::Error(WEX::Common::String().Format(L"DetourAttach failed: %d", err));
            ::DetourTransactionAbort();
            return false;
        }
        ::DetourTransactionCommit();

        // Initialize the HTTP server we use for token requests
        VERIFY_WIN32_SUCCEEDED(::HttpInitialize(HTTPAPI_VERSION_2, HTTP_INITIALIZE_SERVER, nullptr));
        VERIFY_WIN32_SUCCEEDED(::HttpCreateRequestQueue(HTTPAPI_VERSION_2, nullptr, nullptr, 0, &m_requestQueue));
        VERIFY_WIN32_SUCCEEDED(::HttpCreateServerSession(HTTPAPI_VERSION_2, &m_serverSessionId, 0));
        VERIFY_WIN32_SUCCEEDED(::HttpCreateUrlGroup(m_serverSessionId, &m_urlGroup, 0));

        HTTP_BINDING_INFO bindingInfo = {};
        bindingInfo.Flags.Present = 1;
        bindingInfo.RequestQueueHandle = m_requestQueue;
        VERIFY_WIN32_SUCCEEDED(::HttpSetUrlGroupProperty(m_urlGroup, HttpServerBindingProperty, &bindingInfo,
            static_cast<ULONG>(sizeof(bindingInfo))));

        // Find an open port; note that ports in the low 50000s are frequently claimed, hence the large iteration bounds
        ULONG err = 0;
        for (std::uint16_t i = 0; i < 500; ++i)
        {
            wchar_t buffer[18 + 5 + 1];
            std::swprintf(buffer, std::size(buffer), L"http://127.0.0.1:%d/", m_serverPort);

            err = ::HttpAddUrlToUrlGroup(m_urlGroup, buffer, 0, 0);
            if (err == NO_ERROR)
            {
                m_serverUrlBase = buffer;
                break;
            }

            ++m_serverPort;
        }

        VERIFY_WIN32_SUCCEEDED(err, L"Failed to find an open port");
        m_httpServerThread = std::thread([this] {
            RunHttpServer();
        });

        return true;
    }

    TEST_CLASS_CLEANUP(Cleanup)
    {
        // Tear down the HTTP server
        m_serverShutdownEvent.SetEvent();
        m_httpServerThread.join();

        if (m_urlGroup)
        {
            ::HttpCloseUrlGroup(m_urlGroup);
            m_urlGroup = 0;
        }

        if (m_serverSessionId)
        {
            ::HttpCloseServerSession(m_serverSessionId);
            m_serverSessionId = 0;
        }

        if (m_requestQueue)
        {
            ::HttpCloseRequestQueue(m_requestQueue);
            m_requestQueue = nullptr;
        }

        ::HttpTerminate(HTTP_INITIALIZE_SERVER, nullptr);

        // Clean up our detours
        ::DetourTransactionBegin();
        ::DetourUpdateThread(::GetCurrentThread());
        ::DetourDetach(reinterpret_cast<void**>(&RealShellExecuteW), &DetouredShellExecuteW);
        ::DetourTransactionCommit();

        Test::Bootstrap::Cleanup();

        return true;
    }

    template <typename T>
    static bool WaitWithTimeout(const IAsyncOperation<T>& op)
    {
        wil::unique_event event(wil::EventOptions::None);
        op.Completed([&](const IAsyncOperation<T>&, AsyncStatus) {
            event.SetEvent();
        });

        // 10 seconds is beyond 
        if (::WaitForSingleObject(event.get(), 10000) == WAIT_OBJECT_0)
        {
            return true;
        }

        op.Cancel();
        return false;
    }

    static inline constexpr std::wstring_view auth_url = L"http://oauthtests.com/oauth"sv;
    static inline constexpr std::wstring_view localhost_redirect_url = L"http://127.0.0.1/oauth"sv;

    TEST_METHOD(Localhost_BasicEndToEnd)
    {
        static constexpr std::wstring_view client_id = L"scenario=Localhost_BasicEndToEnd"sv;

        auto params = AuthRequestParams::CreateForAuthorizationCodeRequest(client_id, Uri{ localhost_redirect_url });
        auto asyncOp = AuthManager::InitiateAuthRequestAsync(Uri{ auth_url }, params);
        VERIFY_IS_TRUE(WaitWithTimeout(asyncOp));
        VERIFY_ARE_EQUAL(AsyncStatus::Completed, asyncOp.Status());

        auto result = asyncOp.GetResults();
        auto response = result.Response();
        VERIFY_IS_NOT_NULL(response);
        VERIFY_IS_NULL(result.Failure());

        VERIFY_ARE_EQUAL(params.State(), response.State());
    }

    // Detoured Functions
    static HINSTANCE __stdcall DetouredShellExecuteW(_In_opt_ HWND hwnd, _In_opt_ LPCWSTR operation, _In_ LPCWSTR file,
        _In_opt_ LPCWSTR params, _In_opt_ LPCWSTR directory, _In_ INT showCmd) try
    {
        std::wstring_view fileStr = file;
        if (fileStr.substr(0, auth_url.size()) == auth_url)
        {
            // There's no point in launching the browser and trying to fake an authorization flow as that would do
            // nothing to test the API. Instead, perform the logic of the browser and authorization flow here in-proc
            winrt::hstring responseType;
            winrt::hstring clientId;
            Uri redirectUri{ nullptr };
            winrt::hstring scope;
            winrt::hstring state;
            winrt::hstring codeChallenge;
            winrt::hstring codeChallengeMethod;

            winrt::hstring scenario;

            Uri uri{ fileStr };
            winrt::hstring errorString;
            winrt::hstring errorMessage;
            for (auto&& entry : uri.QueryParsed())
            {
                auto name = entry.Name();
                auto value = entry.Value();
                if (name == strings::request::response_type)
                {
                    responseType = value;
                }
                else if (name == strings::request::client_id)
                {
                    clientId = value;
                }
                else if (name == strings::request::redirect_uri)
                {
                    redirectUri = Uri{ value };
                }
                else if (name == strings::request::scope)
                {
                    scope = value;
                }
                else if (name == strings::request::state)
                {
                    state = value;
                }
                else if (name == strings::request::code_challenge)
                {
                    codeChallenge = value;
                }
                else if (name == strings::request::code_challenge_method)
                {
                    codeChallengeMethod = value;
                }
                else
                {
                    // TODO: Respond with error? We might not have the redirect URI or state yet...
                    errorString = strings::error::invalid_request;
                    errorMessage = L"Unrecognized query parameter '"s + name + L"'";
                }
            }

            for (auto&& entry : WwwFormUrlDecoder{ Uri::UnescapeComponent(clientId) })
            {
                auto name = entry.Name();
                auto value = entry.Value();
                if (name == strings::client_id::scenario)
                {
                    scenario = value;
                }
                else
                {
                    errorString = strings::error::invalid_request;
                    errorMessage = L"Unrecognized client_id parameter '"s + name + L"'";
                }
            }

            if (state.empty())
            {
                // If no state is provided, we'll be unable to correlate the response to the request. The best we can
                // really do here is to fail the launch which will fail the test early and reliably
                Log::Error(L"No 'state' value provided in the URI");
                ::SetLastError(ERROR_INVALID_PARAMETER);
                return nullptr;
            }
            else if (responseType.empty())
            {
                errorString = strings::error::invalid_request;
                errorMessage = L"Missing 'response_type'";
            }
            else if (clientId.empty())
            {
                errorString = strings::error::invalid_request;
                errorMessage = L"Missing 'client_id'";
            }

            if (!redirectUri)
            {
                // TODO: Some tests will want to test us not providing a URI
                // If we aren't given a URI and we didn't expect to not be given a URI, then we can't reliably return
                // back an error response
                Log::Error(L"No 'redirect_uri' value provided in the URI");
                ::SetLastError(ERROR_INVALID_PARAMETER);
                return nullptr;
            }

            Uri responseUri{ nullptr };
            if (responseType == strings::response_type::code)
            {
                std::wstring code = L"client=";
                code += Uri::EscapeComponent(clientId);
                if (codeChallengeMethod.empty())
                {
                    code += L"&challenge_method=none";
                }
                else
                {
                    code += L"&challenge_method=";
                    code += codeChallengeMethod;
                    code += L"&challenge=";
                    code += codeChallenge;
                }

                uri_builder builder{ redirectUri };
                builder.add(L"code", code);
                builder.add(L"state", state);
                responseUri = builder.get();
            }
            else if (responseType == strings::response_type::token)
            {
                // TODO
            }
            else
            {
                errorString = strings::error::unsupported_response_type;
                errorMessage = L"Unknown response type '"s + responseType + L"'";
            }

            if (!errorString.empty())
            {
                // NOTE: We may have created a response URI already, in which case we want to overwrite it here
                uri_builder builder(redirectUri, responseType != strings::response_type::token);
                builder.add(L"state", state);
                builder.add(L"error", errorString);
                builder.add_optional(L"error_description", errorMessage);
                // TODO: error_uri
                responseUri = builder.get();
            }

            if (responseUri.SchemeName() != L"http")
            {
                // Protocol activation
                return RealShellExecuteW(hwnd, L"open", responseUri.RawUri().c_str(), nullptr, nullptr, SW_SHOWDEFAULT);
            }

            // Simulating a localhost server. This would give the response back in-proc so we can just go ahead and
            // do that directly. Note that we do this in the same callstack as that will test more interesting code
            // paths
            if (!AuthManager::CompleteAuthRequest(responseUri))
            {
                Log::Warning(L"Failed to complete auth request");
            }

            return reinterpret_cast<HINSTANCE>(42); // Value doesn't really matter; must be greater than 32
        }

        // Not intercepting. Let this "fall through" to the implementation
        return RealShellExecuteW(hwnd, operation, file, params, directory, showCmd);
    }
    catch (...)
    {
        ::SetLastError(ERROR_FILE_NOT_FOUND);
        return reinterpret_cast<HMODULE>(ERROR_FILE_NOT_FOUND);
    }

    // HTTP Server Thread Callback
    void RunHttpServer()
    {
        wil::unique_event event{ wil::EventOptions::None };
        OVERLAPPED overlapped = {};
        overlapped.hEvent = event.get();

        ULONG bufferSize = 0x1000; // 4 KB
        auto buffer = std::make_unique<std::uint8_t[]>(bufferSize);
        auto request = reinterpret_cast<HTTP_REQUEST*>(buffer.get());
        while (true)
        {
            auto err = ::HttpReceiveHttpRequest(m_requestQueue, HTTP_NULL_ID, HTTP_RECEIVE_REQUEST_FLAG_COPY_BODY,
                request, bufferSize, nullptr, &overlapped);
            if (err == ERROR_IO_PENDING)
            {
                // Wait for either shutdown or a request to come in
                HANDLE handles[] = { event.get(), m_serverShutdownEvent.get() };
                auto waitResult = ::WaitForMultipleObjects(2, handles, false, INFINITE);
                if (waitResult == (WAIT_OBJECT_0 + 1))
                {
                    // Shutdown
                    ::CancelIo(m_requestQueue);
                    break;
                }
                else if (waitResult != WAIT_OBJECT_0)
                {
                    Log::Warning(WEX::Common::String().Format(
                        L"WaitForMultipleObjects failed in the HTTP server thread: %d", ::GetLastError()));
                    ::CancelIo(m_requestQueue);
                    break;
                }
            }

            // We have a request; we'll block here until we have all data, if needed
            DWORD bytes;
            ::GetOverlappedResult(m_requestQueue, &overlapped, &bytes, false);
            err = ::GetLastError();
            if (err == ERROR_MORE_DATA)
            {
                bufferSize = bytes;
                buffer = std::make_unique<std::uint8_t[]>(bufferSize);
                request = reinterpret_cast<HTTP_REQUEST*>(buffer.get());
                err = ::HttpReceiveHttpRequest(m_requestQueue, request->RequestId, HTTP_RECEIVE_REQUEST_FLAG_COPY_BODY,
                    request, bufferSize, &bytes, nullptr);
            }

            if (err == ERROR_CONNECTION_INVALID)
            {
                // Connection corrupted by peer
                continue;
            }
            else if (err != ERROR_SUCCESS)
            {
                Log::Warning(WEX::Common::String().Format(L"HttpReceiveHttpRequest failed: %d", err));
                break;
            }

            switch (request->Verb)
            {
            case HttpVerbGET:
                HandleGetRequest(request);
                break;

            case HttpVerbPOST:
                HandlePostRequest(request);
                break;

            default:
                Log::Warning(L"Received an HTTP request with an unexpected verb");
                break;
            }
        }
    }

    void HandleGetRequest(HTTP_REQUEST* request)
    {
        (void)request; // TODO
    }

    void HandlePostRequest(HTTP_REQUEST* request)
    {
        WINRT_ASSERT(request->EntityChunkCount == 1);
        WINRT_ASSERT(request->pEntityChunks->DataChunkType == HttpDataChunkFromMemory);
        auto& data = request->pEntityChunks->FromMemory;
        std::string_view body{ static_cast<char*>(data.pBuffer), data.BufferLength };

        for (auto&& entry : WwwFormUrlDecoder(winrt::to_hstring(body)))
        {
            (void)entry; // TODO
        }
    }

    // Detours Information
    static inline decltype(&::ShellExecuteW) RealShellExecuteW = &::ShellExecuteW;

    // Local server for performing the token exchange
    wil::unique_event m_serverShutdownEvent{ wil::EventOptions::None };
    std::thread m_httpServerThread;
    HANDLE m_requestQueue = nullptr;
    HTTP_SERVER_SESSION_ID m_serverSessionId = 0;
    HTTP_URL_GROUP_ID m_urlGroup = 0;
    std::uint16_t m_serverPort = 50001;
    std::wstring m_serverUrlBase;
};
