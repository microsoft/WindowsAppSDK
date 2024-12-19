// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <memory>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

#include <Windows.h>

#include <detours.h>
#include <http.h>
#include <shellapi.h>
#include <WexTestClass.h>
#include <WinSock2.h>

#include <TerminalVelocityFeatures-OAuth.h>
#include <winrt/Microsoft.Security.Authentication.OAuth.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Security.Cryptography.Core.h>
#include <winrt/Windows.Storage.Streams.h>

#include "OAuth2APITests.h"

// NOTE: Thise files don't include everything they need, hence they are here last
#include <WindowsAppRuntime.Test.Bootstrap.h>
#include <WindowsAppRuntime.Test.TAEF.h>

#include <wil/resource.h> // Included last to enable the most features

using namespace std::literals;
using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;
using namespace winrt::Microsoft::Security::Authentication::OAuth;
using namespace winrt::Windows::Data::Json;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Security::Cryptography;
using namespace winrt::Windows::Security::Cryptography::Core;
using namespace winrt::Windows::Storage::Streams;

namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace OAuth2ManagerTests
{
    class OAuth2APITests
    {
    public:
        BEGIN_TEST_CLASS(OAuth2APITests)
            TEST_CLASS_PROPERTY(L"ThreadingModel", L"MTA")
            END_TEST_CLASS()

        TEST_METHOD_SETUP(MethodInit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            return true;
        }

        TEST_METHOD_CLEANUP(MethodUninit)
        {
            VERIFY_IS_TRUE(TP::IsPackageRegistered_WindowsAppRuntimeFramework());
            return true;
        }

        TEST_CLASS_SETUP(Setup)
        {
            // Initialize the Windows Runtime
            winrt::init_apartment();
            Test::Bootstrap::Setup();
            Test::Packages::WapProj::AddPackage(Test::TAEF::GetDeploymentDir(), L"OAuthTestAppPackage", L".msix");

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
                wchar_t buffer[18 + 5 + 1]; // 18 for base URL, 5 for port number, 1 for null terminator
                std::swprintf(buffer, std::size(buffer), L"http://127.0.0.1:%d/", m_serverPort);

                err = ::HttpAddUrlToUrlGroup(m_urlGroup, buffer, 0, 0);
                if (err == NO_ERROR)
                {
                    m_serverUrlBase = std::wstring(buffer); // Copy the buffer to a std::wstring to avoid dangling pointer
                    break;
                }

                ++m_serverPort;
            }

            VERIFY_WIN32_SUCCEEDED(err, L"Looking for an open port");
            m_httpServerThread = std::thread([this]
            {
                RunHttpServer();
            });

            return true;
        }

        TEST_CLASS_CLEANUP(Cleanup)
        {
            ::Test::Bootstrap::CleanupPackages();
            Test::Packages::RemovePackage(L"OAuthTestAppPackage_1.0.0.0_" WINDOWSAPPRUNTIME_TEST_PACKAGE_DDLM_ARCHITECTURE L"__8wekyb3d8bbwe");

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
        static void WaitWithTimeout(const IAsyncOperation<T>& op, AsyncStatus expectedStatus)
        {
            wil::unique_event event(wil::EventOptions::None);
            op.Completed([event = event.get()](const IAsyncOperation<T>&, AsyncStatus)
            {
                ::SetEvent(event);
            });

            // 10 seconds is beyond
            if (::WaitForSingleObject(event.get(), 10000) == WAIT_OBJECT_0)
            {
                VERIFY_ARE_EQUAL(expectedStatus, op.Status());
                return;
            }

            Log::Warning(L"Timed out waiting for IAsyncOperation to complete; cancelling...");
            op.Cancel();

            // Cancel should cause the operation to complete with the cancellation
            if (::WaitForSingleObject(event.get(), 1000) != WAIT_OBJECT_0)
            {
                // Lambda holds a reference to the event. Best just to leak it here
                Log::Warning(L"Failed to cancel IAsyncOperation; leaking event");
                event.release();
            }

            VERIFY_FAIL(L"IAsyncOperation did not complete in a reasonable amount of time");
        }

        template <typename ErrorT>
        static void VerifyErrorNull(const ErrorT& error)
        {
            if (error)
            {
                Log::Error(WEX::Common::String().Format(L"Error object expected to be null! Message: %ls",
                    error.ErrorDescription().c_str()));
            }
            VERIFY_IS_NULL(error);
        }

        AuthResponse InitiateAndWaitForSuccessfulAuthResponse(const AuthRequestParams& params)
        {
            auto op = OAuth2Manager::RequestAuthWithParamsAsync(winrt::Microsoft::UI::WindowId(123456789), Uri{ auth_url }, params);
            auto par = params.CodeChallenge();
            WaitWithTimeout(op, AsyncStatus::Completed);

            auto result = op.GetResults();
            VerifyErrorNull(result.Failure());

            auto response = result.Response();
            VERIFY_IS_NOT_NULL(response);
            VERIFY_ARE_EQUAL(params.State(), response.State());

            return response;
        }

        TokenResponse RequestTokenAndWaitForSuccessfulResponse(const TokenRequestParams& params, const ClientAuthentication& auth = { nullptr })
        {
            IAsyncOperation<TokenRequestResult> op{ nullptr };
            if (auth)
            {
                op = OAuth2Manager::RequestTokenAsync(Uri{ m_serverUrlBase + L"token" }, params, auth);
            }
            else
            {
                op = OAuth2Manager::RequestTokenAsync(Uri{ m_serverUrlBase + L"token" }, params);
            }
            WaitWithTimeout(op, AsyncStatus::Completed);

            auto result = op.GetResults();
            VerifyErrorNull(result.Failure());

            auto response = result.Response();
            VERIFY_IS_NOT_NULL(response);
            VERIFY_ARE_EQUAL(token, response.AccessToken());
            VERIFY_ARE_EQUAL(L"Bearer", response.TokenType());
            VERIFY_ARE_EQUAL(3600, response.ExpiresIn());
            VERIFY_ARE_EQUAL(refresh_token, response.RefreshToken());
            VERIFY_ARE_EQUAL(L"all", response.Scope());

            return response;
        }

        static inline constexpr std::wstring_view auth_url = L"http://oauthtests.com/oauth"sv;

        // Redirect URIs
        static inline constexpr std::wstring_view localhost_redirect_uri = L"http://127.0.0.1/oauth"sv;
        static inline constexpr std::wstring_view protocol_redirect_uri = L"oauthtestapp:oauth"sv;

        void DoEndToEndAuthCodeTest(const AuthRequestParams& requestParams)
        {
            auto authResponse = InitiateAndWaitForSuccessfulAuthResponse(requestParams);
            VERIFY_IS_FALSE(authResponse.Code().empty());

            auto tokenParams = TokenRequestParams::CreateForAuthorizationCodeRequest(authResponse);
            RequestTokenAndWaitForSuccessfulResponse(tokenParams);
        }

        void DoBasicEndToEndAuthCodeTest(std::wstring_view clientId, std::wstring_view redirectUri)
        {
            auto requestParams = AuthRequestParams::CreateForAuthorizationCodeRequest(clientId, Uri{ redirectUri });
            DoEndToEndAuthCodeTest(requestParams);
        }

        TEST_METHOD(Protocol_AuthorizationCode_BasicEndToEnd)
        {
            if (!::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"OAuth2Manager API Features are not enabled.");
                return;
            }
            static constexpr std::wstring_view client_id = GRANT_TYPE_CODE REDIRECT_TYPE_PROTOCOL;
            DoBasicEndToEndAuthCodeTest(client_id, protocol_redirect_uri);
        }

        TEST_METHOD(AuthorizationCodeWithClientAuth)
        {
            if (!::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"OAuth2Manager API Features are not enabled.");
                return;
            }
            // NOTE: This is testing client auth, which is a token request only thing, hence only using a single redirection type
            static constexpr std::wstring_view client_id = GRANT_TYPE_CODE REDIRECT_TYPE_LOCALHOST AUTH_TYPE_HEADER;
            auto requestParams = AuthRequestParams::CreateForAuthorizationCodeRequest(client_id, Uri{ localhost_redirect_uri });
            auto authResponse = InitiateAndWaitForSuccessfulAuthResponse(requestParams);

            auto tokenParams = TokenRequestParams::CreateForAuthorizationCodeRequest(authResponse);
            auto auth = ClientAuthentication::CreateForBasicAuthorization(client_id, L"password");
            auto tokenAsyncOp = OAuth2Manager::RequestTokenAsync(Uri{ m_serverUrlBase + L"token" }, tokenParams, auth);
            WaitWithTimeout(tokenAsyncOp, AsyncStatus::Completed);

            auto tokenResult = tokenAsyncOp.GetResults();
            auto tokenResponse = tokenResult.Response();
            VerifyErrorNull(tokenResult.Failure());
            VERIFY_IS_NOT_NULL(tokenResponse);
            VERIFY_ARE_EQUAL(token, tokenResponse.AccessToken());
        }

        TEST_METHOD(ClientCredentialsTokenRequest)
        {
            if (!::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"OAuth2Manager API Features are not enabled.");
                return;
            }
            static constexpr std::wstring_view client_id = GRANT_TYPE_CLIENT AUTH_TYPE_HEADER;
            auto tokenParams = TokenRequestParams::CreateForClientCredentials();
            auto auth = ClientAuthentication::CreateForBasicAuthorization(client_id, L"password");
            RequestTokenAndWaitForSuccessfulResponse(tokenParams, auth);
        }

        TEST_METHOD(RefreshTokenRequest)
        {
            if (!::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"OAuth2Manager API Features are not enabled.");
                return;
            }
            static constexpr std::wstring_view client_id = GRANT_TYPE_REFRESH AUTH_TYPE_HEADER;
            auto tokenParams = TokenRequestParams::CreateForRefreshToken(refresh_token_old);
            auto auth = ClientAuthentication::CreateForBasicAuthorization(client_id, L"password");
            RequestTokenAndWaitForSuccessfulResponse(tokenParams, auth);
        }

        TEST_METHOD(ExtensionTokenRequest)
        {
            if (!::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"OAuth2Manager API Features are not enabled.");
                return;
            }
            static constexpr std::wstring_view client_id = GRANT_TYPE_EXTENSION AUTH_TYPE_HEADER;
            auto tokenParams = TokenRequestParams::CreateForExtension(Uri{ extension_grant_uri });
            auto auth = ClientAuthentication::CreateForBasicAuthorization(client_id, L"password");
            RequestTokenAndWaitForSuccessfulResponse(tokenParams, auth);
        }

        TEST_METHOD(TokenRequestErrorResponse)
        {
            if (!::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"OAuth2Manager API Features are not enabled.");
                return;
            }
            static constexpr std::wstring_view client_id = GRANT_TYPE_CLIENT TOKEN_ERROR_RESPONSE;
            auto tokenParams = TokenRequestParams::CreateForClientCredentials();
            auto auth = ClientAuthentication::CreateForBasicAuthorization(client_id, L"password");
            auto tokenAsyncOp = OAuth2Manager::RequestTokenAsync(Uri{ m_serverUrlBase + L"token" }, tokenParams, auth);
            WaitWithTimeout(tokenAsyncOp, AsyncStatus::Completed);

            auto tokenResult = tokenAsyncOp.GetResults();
            auto tokenError = tokenResult.Failure();
            VERIFY_IS_NULL(tokenResult.Response());
            VERIFY_IS_NOT_NULL(tokenError);
            auto additionalParams = tokenError.AdditionalParams();
            VERIFY_IS_NOT_NULL(additionalParams);

            VERIFY_ARE_EQUAL(E_FAIL, tokenError.ErrorCode().value);
            VERIFY_ARE_EQUAL(L"server_error", tokenError.Error());
            VERIFY_ARE_EQUAL(error_description, tokenError.ErrorDescription());
            VERIFY_IS_NOT_NULL(tokenError.ErrorUri());
            VERIFY_ARE_EQUAL(error_uri, tokenError.ErrorUri().RawUri());

            VERIFY_IS_TRUE(additionalParams.HasKey(additional_param_key));
            auto jsonValue = additionalParams.Lookup(additional_param_key);
            VERIFY_ARE_EQUAL(JsonValueType::String, jsonValue.ValueType());
            VERIFY_ARE_EQUAL(additional_param_value, jsonValue.GetString());
        }

        TEST_METHOD(AdditionalParams)
        {
            if (!::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"OAuth2Manager API Features are not enabled.");
                return;
            }
            static constexpr std::wstring_view client_id = GRANT_TYPE_CODE REDIRECT_TYPE_LOCALHOST ADDITIONAL_PARAMS;
            auto requestParams = AuthRequestParams::CreateForAuthorizationCodeRequest(client_id, Uri{ localhost_redirect_uri });
            auto additionalRequestParams = requestParams.AdditionalParams();
            additionalRequestParams.Insert(additional_param_key, additional_param_value);
            auto authResponse = InitiateAndWaitForSuccessfulAuthResponse(requestParams);

            auto tokenParams = TokenRequestParams::CreateForAuthorizationCodeRequest(authResponse);
            auto additionalTokenParams = tokenParams.AdditionalParams();
            additionalTokenParams.Insert(additional_param_key, additional_param_value);

            auto tokenAsyncOp = OAuth2Manager::RequestTokenAsync(Uri{ m_serverUrlBase + L"token" }, tokenParams);
            WaitWithTimeout(tokenAsyncOp, AsyncStatus::Completed);

            auto tokenResult = tokenAsyncOp.GetResults();
            auto tokenResponse = tokenResult.Response();
            VerifyErrorNull(tokenResult.Failure());
            VERIFY_IS_NOT_NULL(tokenResponse);
        }

        TEST_METHOD(CompleteInvalidState)
        {
            if (!::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled())
            {
                Log::Result(TestResults::Skipped, L"OAuth2Manager API Features are not enabled.");
                return;
            }
            VERIFY_IS_FALSE(OAuth2Manager::CompleteAuthRequest(Uri{ L"unknown-protocol:" })); // No query parameters at all
            VERIFY_IS_FALSE(OAuth2Manager::CompleteAuthRequest(Uri{ L"http://127.0.0.1/oauth?code=abc123" })); // Missing state
            VERIFY_IS_FALSE(OAuth2Manager::CompleteAuthRequest(Uri{ L"oauthtestapp:oauth?code=abc&state=invalid" }));
            VERIFY_IS_FALSE(OAuth2Manager::CompleteAuthRequest(Uri{ L"http://127.0.0.1/oauth?code=abc123&state=invalid" }));
        }

        // Detoured Functions
        static BOOL __stdcall DetouredShellExecuteW(SHELLEXECUTEINFO* sei) try
        {
            std::wstring_view fileStr = sei->lpFile;
            if (fileStr.substr(0, auth_url.size()) == auth_url)
            {
                winrt::hstring errorString;
                winrt::hstring errorMessage;
                auto assignInvalidRequestError = [&](std::wstring_view msg)
                {
                    if (errorString.empty())
                    {
                        errorString = L"invalid_request";
                        errorMessage = msg;
                    }
                };
                auto assignMismatchedArgsError = [&](std::wstring_view name, std::wstring_view expected, std::wstring_view actual)
                {
                    if (errorString.empty())
                    {
                        std::wstring msg = L"Unexpected value for '";
                        msg.append(name);
                        msg += L"'. Expected '";
                        msg.append(expected);
                        msg += L"' but got '";
                        msg.append(actual);
                        msg += L"'";
                        errorString = L"invalid_request";
                        errorMessage = msg;
                    }
                };

                // There's no point in launching the browser and trying to fake an authorization flow as that would do
                // nothing to test the API. Instead, perform the logic of the browser and authorization flow here in-proc
                winrt::hstring responseType;
                winrt::hstring clientId;
                Uri redirectUri{ nullptr };
                winrt::hstring scope;
                winrt::hstring state;
                winrt::hstring codeChallenge;
                winrt::hstring codeChallengeMethod;
                winrt::hstring additionalParam;
                for (auto&& entry : Uri(fileStr).QueryParsed())
                {
                    auto name = entry.Name();
                    auto value = entry.Value();
                    if (name == L"response_type")
                    {
                        responseType = value;
                    }
                    else if (name == L"client_id")
                    {
                        clientId = value;
                    }
                    else if (name == L"redirect_uri")
                    {
                        redirectUri = Uri{ value };
                    }
                    else if (name == L"scope")
                    {
                        scope = value;
                    }
                    else if (name == L"state")
                    {
                        state = value;
                    }
                    else if (name == L"code_challenge")
                    {
                        codeChallenge = value;
                    }
                    else if (name == L"code_challenge_method")
                    {
                        codeChallengeMethod = value;
                    }
                    else if (name == additional_param_key)
                    {
                        additionalParam = value;
                    }
                    else
                    {
                        assignInvalidRequestError(L"Unrecognized query parameter '"s + name + L"'");
                    }
                }

                // Some behavior is encoded in the client id
                winrt::hstring expectedGrantType;
                winrt::hstring expectedRedirectType;
                winrt::hstring expectedPkceType = L"S256";
                winrt::hstring expectedScopeType = L"none";
                winrt::hstring expectedError = L"none";
                bool completeRequest = true;
                bool expectAdditionalParams = false;
                for (auto&& entry : WwwFormUrlDecoder{ clientId })
                {
                    auto name = entry.Name();
                    auto value = entry.Value();
                    if (name == L"grant")
                    {
                        expectedGrantType = value;
                    }
                    else if (name == L"redirect")
                    {
                        expectedRedirectType = value;
                    }
                    else if (name == L"pkce")
                    {
                        expectedPkceType = value;
                    }
                    else if (name == L"scope")
                    {
                        expectedScopeType = value;
                    }
                    else if (name == L"error")
                    {
                        expectedError = value;
                    }
                    else if (name == L"complete")
                    {
                        completeRequest = (value == L"true");
                    }
                    else if (name == L"additional_params")
                    {
                        expectAdditionalParams = (value == L"true");
                    }
                    // Ignore other values as these are specific to the token request
                }

                if (state.empty())
                {
                    // If no state is provided, we'll be unable to correlate the response to the request. The best we can
                    // really do here is to fail the launch which will fail the test early and reliably
                    Log::Error(L"No 'state' value provided in the URI");
                    ::SetLastError(ERROR_INVALID_PARAMETER);
                    return false;
                }
                else if (responseType.empty())
                {
                    assignInvalidRequestError(L"Missing 'response_type'");
                }
                else if (clientId.empty())
                {
                    assignInvalidRequestError(L"Missing 'client_id'");
                }
                else if (expectedGrantType.empty())
                {
                    assignInvalidRequestError(L"Client id is missing the expected grant type");
                }
                else if (expectedRedirectType.empty())
                {
                    assignInvalidRequestError(L"Client id is missing the expected redirect type");
                }

                if (responseType != expectedGrantType)
                {
                    assignMismatchedArgsError(L"response_type", expectedGrantType, responseType);
                }

                auto expectedUri = (expectedRedirectType == L"localhost") ? localhost_redirect_uri : protocol_redirect_uri;
                if (redirectUri.RawUri() != expectedUri)
                {
                    assignMismatchedArgsError(L"redirect_uri", expectedUri, redirectUri.RawUri());
                }

                if (expectedPkceType == L"none")
                {
                    if (!codeChallengeMethod.empty())
                    {
                        assignMismatchedArgsError(L"code_challenge_method", L"<empty>", codeChallengeMethod);
                    }
                }
                else if (expectedPkceType != codeChallengeMethod)
                {
                    assignMismatchedArgsError(L"code_challenge_method", expectedPkceType, codeChallengeMethod);
                }

                if (expectedScopeType == L"none")
                {
                    if (!scope.empty())
                    {
                        assignMismatchedArgsError(L"scope", L"<empty>", scope);
                    }
                }
                else if (scope.empty())
                {
                    assignInvalidRequestError(L"Expected a 'scope' parameter, but none provided");
                }

                if (expectAdditionalParams)
                {
                    if (additionalParam.empty())
                    {
                        assignInvalidRequestError(L"Expected additional params, but none provided");
                    }
                    else if (additionalParam != additional_param_value)
                    {
                        assignMismatchedArgsError(L"additional param", additional_param_value, additionalParam);
                    }
                }
                else if (!additionalParam.empty())
                {
                    assignInvalidRequestError(L"Expected no additional params, but one was provided");
                }

                Uri responseUri{ nullptr };
                if (expectedError == L"auth")
                {
                    uri_builder builder(redirectUri, responseType != L"token");
                    builder.add(L"state", state);
                    builder.add(L"error", L"server_error");
                    builder.add(L"error_description", error_description);
                    builder.add(L"error_uri", error_uri);
                    builder.add(additional_param_key, additional_param_value);
                    responseUri = builder.get();
                }
                else if (responseType == L"code")
                {
                    // For simplicity, encode the client id and PKCE info in the code
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

                    // NOTE: The 'scope' should be empty, but we should never indicate an expected 'scope' other than 'none'
                    // for tests that use the auth code grant type

                    uri_builder builder{ redirectUri };
                    builder.add(L"code", code);
                    builder.add(L"state", state);
                    responseUri = builder.get();
                }
                else
                {
                    assignInvalidRequestError(L"Unknown response type '"s + responseType + L"'");
                }

                if (!errorString.empty())
                {
                    // NOTE: We may have created a response URI already, in which case we want to overwrite it here
                    uri_builder builder(redirectUri, responseType != L"token");
                    builder.add(L"state", state);
                    builder.add(L"error", errorString);
                    builder.add_optional(L"error_description", errorMessage);
                    responseUri = builder.get();
                }
                SHELLEXECUTEINFO sei = { sizeof(sei) };
                sei.fMask = SEE_MASK_NOCLOSEPROCESS;
                sei.hwnd = nullptr;
                sei.lpVerb = L"open";
                sei.lpFile = responseUri.RawUri().c_str();
                sei.lpParameters = nullptr;
                sei.lpDirectory = nullptr;
                sei.nShow = SW_SHOWDEFAULT;
                sei.hInstApp = nullptr;
                if (responseUri.SchemeName() != L"http")
                {
                    // Protocol activation
                    return RealShellExecuteW(&sei);
                }

                // Simulating a localhost server. This would give the response back in-proc so we can just go ahead and
                // do that directly. Note that we do this in the same callstack as that will test more interesting code
                // paths. TODO: Async completion as a parameter? Or just let protocol activation test that path
                if (completeRequest && !OAuth2Manager::CompleteAuthRequest(responseUri))
                {
                    Log::Warning(L"Failed to complete auth request");
                }

                return TRUE;
            }

            // Not intercepting. Let this "fall through" to the implementation
            return RealShellExecuteW(sei);
        }
        catch (...)
        {
            ::SetLastError(ERROR_FILE_NOT_FOUND);
            return FALSE;
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
                case HttpVerbPOST:
                    HandlePostRequest(request);
                    break;

                default:
                    Log::Warning(L"Received an HTTP request with an unexpected verb");
                    break;
                }
            }
        }

        void HandlePostRequest(HTTP_REQUEST* request)
        {
            std::string body;
            for (USHORT i = 0; i < request->EntityChunkCount; ++i)
            {
                auto& chunk = request->pEntityChunks[i];
                WINRT_ASSERT(chunk.DataChunkType == HttpDataChunkFromMemory);
                auto& data = chunk.FromMemory;
                body.append(static_cast<char*>(data.pBuffer), data.BufferLength);
            }

            if (request->Flags & HTTP_REQUEST_FLAG_MORE_ENTITY_BODY_EXISTS)
            {
                ULONG bufferLength = 2048;
                auto buffer = std::make_unique<char[]>(bufferLength);
                while (true)
                {
                    ULONG bytes = 0;
                    auto result = ::HttpReceiveRequestEntityBody(m_requestQueue, request->RequestId, 0, buffer.get(),
                        bufferLength, &bytes, nullptr);
                    if ((result == NO_ERROR) || (result == ERROR_HANDLE_EOF))
                    {
                        body.append(buffer.get(), bytes);
                    }
                    else
                    {
                        Log::Warning(WEX::Common::String().Format(L"HttpReceiveRequestEntityBody failed: %d", result));
                        return; // TODO: Should we send a response here? Getting an error probably means we shouldn't?
                    }

                    if (result == ERROR_HANDLE_EOF) break;
                }
            }

            winrt::hstring errorString;
            winrt::hstring errorMessage;
            auto assignInvalidRequestError = [&](std::wstring_view msg)
            {
                if (errorString.empty())
                {
                    errorString = L"invalid_request";
                    errorMessage = msg;
                }
            };
            auto assignMismatchedArgsError = [&](std::wstring_view name, std::wstring_view expected, std::wstring_view actual)
            {
                if (errorString.empty())
                {
                    std::wstring msg = L"Unexpected value for '";
                    msg.append(name);
                    msg += L"'. Expected '";
                    msg.append(expected);
                    msg += L"' but got '";
                    msg.append(actual);
                    msg += L"'";
                    errorString = L"invalid_request";
                    errorMessage = msg;
                }
            };

            winrt::hstring grantType;
            winrt::hstring code;
            Uri redirectUri{ nullptr };
            winrt::hstring clientId;
            winrt::hstring codeVerifier;
            winrt::hstring scope;
            winrt::hstring refreshToken;
            winrt::hstring additionalParam;
            for (auto&& entry : WwwFormUrlDecoder(winrt::to_hstring(body)))
            {
                auto name = entry.Name();
                auto value = entry.Value();
                if (name == L"grant_type")
                {
                    grantType = value;
                }
                else if (name == L"code")
                {
                    code = value;
                }
                else if (name == L"redirect_uri")
                {
                    redirectUri = Uri{ value };
                }
                else if (name == L"client_id")
                {
                    clientId = value;
                }
                else if (name == L"code_verifier")
                {
                    codeVerifier = value;
                }
                else if (name == L"scope")
                {
                    scope = value;
                }
                else if (name == L"refresh_token")
                {
                    refreshToken = value;
                }
                else if (name == additional_param_key)
                {
                    additionalParam = value;
                }
                else
                {
                    assignInvalidRequestError(L"Unrecognized query parameter '"s + name + L"'");
                }
            }

            auto& authHeader = request->Headers.KnownHeaders[HttpHeaderAuthorization];
            if (authHeader.RawValueLength > 0)
            {
                // Should be of the form '<scheme> <params>'
                std::string_view authHeaderStr(authHeader.pRawValue, authHeader.RawValueLength);
                auto firstSpace = authHeaderStr.find_first_of(' ');
                if (firstSpace == authHeaderStr.npos)
                {
                    assignInvalidRequestError(L"Bad Authorization hedaer");
                }
                else
                {
                    auto scheme = authHeaderStr.substr(0, firstSpace);
                    auto value = authHeaderStr.substr(firstSpace + 1);
                    if (scheme != "Basic")
                    {
                        assignInvalidRequestError(L"Authorization must use 'Basic' type");
                    }
                    else
                    {
                        // 'value' is 'client_id:client_crednetials' base64urlencoded
                        auto credsBuffer = CryptographicBuffer::DecodeFromBase64String(winrt::to_hstring(value));
                        auto fullCreds = CryptographicBuffer::ConvertBinaryToString(BinaryStringEncoding::Utf8, credsBuffer);
                        std::wstring_view fullCredsStr = fullCreds;
                        auto colonPos = fullCredsStr.find_first_of(':');
                        if (colonPos == fullCredsStr.npos)
                        {
                            assignInvalidRequestError(L"Bad Authorization header");
                        }
                        else
                        {
                            auto credsClientId = fullCredsStr.substr(0, colonPos);
                            auto credsClientSecret = fullCredsStr.substr(colonPos + 1);
                            if (credsClientSecret != L"password")
                            {
                                assignMismatchedArgsError(L"Authorization client secret", L"password", credsClientSecret);
                            }
                            else if (clientId.empty())
                            {
                                clientId = credsClientId;
                            }
                            else if (credsClientId != clientId)
                            {
                                assignMismatchedArgsError(L"Authorization client id", clientId, credsClientId);
                            }
                        }
                    }
                }
            }

            if (clientId.empty())
            {
                assignInvalidRequestError(L"Client id not provided");
            }

            winrt::hstring expectedGrantType;
            winrt::hstring expectedRedirectType;
            winrt::hstring expectedPkceType = L"S256";
            winrt::hstring expectedScopeType = L"none";
            winrt::hstring expectedAuthType = L"none";
            winrt::hstring expectedError = L"none";
            bool expectAdditionalParams = false;
            for (auto&& entry : WwwFormUrlDecoder{ clientId })
            {
                auto name = entry.Name();
                auto value = entry.Value();
                if (name == L"grant")
                {
                    expectedGrantType = value;
                }
                else if (name == L"redirect")
                {
                    expectedRedirectType = value;
                }
                else if (name == L"pkce")
                {
                    expectedPkceType = value;
                }
                else if (name == L"scope")
                {
                    expectedScopeType = value;
                }
                else if (name == L"auth")
                {
                    expectedAuthType = value;
                }
                else if (name == L"error")
                {
                    expectedError = value;
                }
                else if (name == L"additional_params")
                {
                    expectAdditionalParams = (value == L"true");
                }
                // Ignore other values as these are specific to the authorization request
            }

            auto checkUnexpectedArg = [&](std::wstring_view name, const winrt::hstring& value)
            {
                if (!value.empty())
                {
                    assignMismatchedArgsError(name, L"<empty>", value);
                }
            };

            if (expectAdditionalParams)
            {
                if (additionalParam.empty())
                {
                    assignInvalidRequestError(L"Expected additional params, but none provided");
                }
                else if (additionalParam != additional_param_value)
                {
                    assignMismatchedArgsError(L"additional param", additional_param_value, additionalParam);
                }
            }
            else if (!additionalParam.empty())
            {
                assignInvalidRequestError(L"Expected no additional params, but one was provided");
            }

            if ((expectedAuthType == L"header") && (authHeader.RawValueLength == 0))
            {
                assignInvalidRequestError(L"Authorization header expected, but not provided");
            }

            std::wstring responseJson;
            if (expectedError == L"token")
            {
                errorString = L"server_error";
                errorMessage = json_escaped_error_description;
            }
            else if (grantType == L"authorization_code")
            {
                if (expectedGrantType != L"code")
                {
                    assignMismatchedArgsError(L"grant_type", expectedGrantType, grantType);
                }
                else if (code.empty())
                {
                    assignInvalidRequestError(L"Authorization code not provided");
                }

                if (redirectUri)
                {
                    auto expectedUri = (expectedRedirectType == L"protocol") ? protocol_redirect_uri : localhost_redirect_uri;
                    if (redirectUri.RawUri() != expectedUri)
                    {
                        assignMismatchedArgsError(L"redirect_uri", expectedUri, redirectUri.RawUri());
                    }
                }
                else if (expectedRedirectType != L"inferred")
                {
                    assignInvalidRequestError(L"Expected a 'redirect_uri', but none provided");
                }

                checkUnexpectedArg(L"scope", scope); // Only expected during auth request
                checkUnexpectedArg(L"refresh_token", refreshToken);

                winrt::hstring codeClientId;
                winrt::hstring codeChallengeMethod;
                winrt::hstring codeChallenge;
                for (auto&& entry : WwwFormUrlDecoder{ code })
                {
                    auto name = entry.Name();
                    auto value = entry.Value();
                    if (name == L"client")
                    {
                        codeClientId = value;
                    }
                    else if (name == L"challenge_method")
                    {
                        codeChallengeMethod = value;
                    }
                    else if (name == L"challenge")
                    {
                        codeChallenge = value;
                    }
                    else
                    {
                        assignInvalidRequestError(L"Unrecognized query parameter '" + name + L"' in code");
                    }
                }

                if (clientId != codeClientId)
                {
                    assignMismatchedArgsError(L"client_id", codeClientId, clientId);
                }

                if (expectedPkceType != codeChallengeMethod)
                {
                    assignMismatchedArgsError(L"code challenge method", expectedPkceType, codeChallengeMethod);
                }
                else if (codeChallengeMethod == L"none")
                {
                    if (!codeVerifier.empty())
                    {
                        assignMismatchedArgsError(L"code_verifier", L"<empty>", codeVerifier);
                    }
                }
                else if (codeVerifier.empty())
                {
                    assignInvalidRequestError(L"Expected 'code_verifier', but none provided");
                }

                if (codeChallengeMethod == L"S256")
                {
                    // We can't "unhash" the code challenge, so hash the code verifier and base64urlencode it
                    auto algo = HashAlgorithmProvider::OpenAlgorithm(HashAlgorithmNames::Sha256());
                    auto hash = algo.HashData(CryptographicBuffer::ConvertStringToBinary(codeVerifier, BinaryStringEncoding::Utf8));
                    auto base64Hash = CryptographicBuffer::EncodeToBase64String(hash);
                    std::wstring base64urlencodedHash;
                    base64urlencodedHash.reserve(base64Hash.size());
                    for (auto ch : base64Hash)
                    {
                        switch (ch)
                        {
                        case '+': base64urlencodedHash.push_back('-'); break;
                        case '/': base64urlencodedHash.push_back('_'); break;
                        case '=': break; // No padding
                        default: base64urlencodedHash.push_back(ch); break;
                        }
                    }

                    if (codeChallenge != base64urlencodedHash)
                    {
                        assignInvalidRequestError(L"The code verifier does not match the original code challenge");
                    }
                }
                else if (codeChallengeMethod == L"plain")
                {
                    if (codeChallenge != codeVerifier)
                    {
                        assignInvalidRequestError(L"Code verifier does not match the expected value");
                    }
                }
            }
            else if (grantType == L"client_credentials")
            {
                if (expectedGrantType != L"client")
                {
                    assignMismatchedArgsError(L"grant_type", expectedGrantType, grantType);
                }

                checkUnexpectedArg(L"code", code);
                checkUnexpectedArg(L"code_verifier", codeVerifier);
                checkUnexpectedArg(L"refresh_token", refreshToken);
            }
            else if (grantType == L"refresh_token")
            {
                if (expectedGrantType != L"refresh")
                {
                    assignMismatchedArgsError(L"grant_type", expectedGrantType, grantType);
                }
                else if (refreshToken != refresh_token_old)
                {
                    assignMismatchedArgsError(L"refresh_token", refresh_token_old, refreshToken);
                }

                checkUnexpectedArg(L"code", code);
                checkUnexpectedArg(L"code_verifier", codeVerifier);
            }
            else if (grantType == extension_grant_uri)
            {
                if (expectedGrantType != L"extension")
                {
                    assignMismatchedArgsError(L"grant_type", expectedGrantType, grantType);
                }

                checkUnexpectedArg(L"code", code);
                checkUnexpectedArg(L"code_verifier", codeVerifier);
                checkUnexpectedArg(L"refresh_token", refreshToken);
            }
            else
            {
                assignInvalidRequestError(L"Unrecognized grant type '"s + grantType + L"'");
            }

            if (errorString.empty())
            {
                // NOTE: All responses are the same
                responseJson = L"{\"access_token\":\"";
                responseJson += json_escaped_token;
                responseJson += L"\",\"token_type\":\"Bearer\",\"expires_in\":3600,\"refresh_token\":\"";
                responseJson += json_escaped_refresh_token;
                responseJson += L"\"";
                if (scope.empty())
                {
                    responseJson += L",\"scope\":\"all\"";
                }
                responseJson += L"}";
            }
            else
            {
                responseJson = L"{\"error\":\"" + errorString + L"\",\"error_description\":\"" + errorMessage +
                    L"\",\"error_uri\":\"" + error_uri + L"\",\"" + additional_param_key + L"\":\"" +
                    additional_param_value + L"\"}";
            }

            WINRT_ASSERT(!responseJson.empty());

            HTTP_RESPONSE response = {};
            response.StatusCode = 200;
            response.pReason = "OK";
            response.ReasonLength = 2;
            auto& contentTypeHeader = response.Headers.KnownHeaders[HttpHeaderContentType];
            contentTypeHeader.pRawValue = "application/json; charset=UTF-8";
            contentTypeHeader.RawValueLength = static_cast<USHORT>(::strlen(contentTypeHeader.pRawValue));

            auto responseJsonUtf8 = winrt::to_string(responseJson);
            HTTP_DATA_CHUNK dataChunk = {};
            dataChunk.DataChunkType = HttpDataChunkFromMemory;
            dataChunk.FromMemory.pBuffer = responseJsonUtf8.data();
            dataChunk.FromMemory.BufferLength = static_cast<ULONG>(responseJsonUtf8.size());

            response.EntityChunkCount = 1;
            response.pEntityChunks = &dataChunk;

            ULONG bytesSent;
            auto sendResult = ::HttpSendHttpResponse(m_requestQueue, request->RequestId, 0, &response, nullptr, &bytesSent,
                nullptr, 0, nullptr, nullptr);
            if (sendResult != NO_ERROR)
            {
                Log::Warning(WEX::Common::String().Format(L"HttpSendHttpResponse failed: %d", sendResult));
            }
        }

        // Detours Information
        static inline decltype(&ShellExecuteExW) RealShellExecuteW = &ShellExecuteExW;

        // Local server for performing the token exchange
        wil::unique_event m_serverShutdownEvent{ wil::EventOptions::None };
        std::thread m_httpServerThread;
        HANDLE m_requestQueue = nullptr;
        HTTP_SERVER_SESSION_ID m_serverSessionId = 0;
        HTTP_URL_GROUP_ID m_urlGroup = 0;
        std::uint16_t m_serverPort = 50001;
        std::wstring m_serverUrlBase;
    };
}
