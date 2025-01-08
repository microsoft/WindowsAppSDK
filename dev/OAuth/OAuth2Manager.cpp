// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "common.h"
#include "windows.h"
#include <wil/resource.h>

#include "OAuth2Manager.h"
#include "AuthRequestParams.h"
#include "TokenFailure.h"
#include "TokenRequestParams.h"
#include "TokenRequestResult.h"
#include "TokenResponse.h"
#include "OAuth2ManagerTelemetry.h"

#include <Microsoft.Security.Authentication.OAuth.OAuth2Manager.g.cpp>

using namespace winrt::Microsoft::Security::Authentication::OAuth;
using namespace winrt::Windows::Data::Json;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Web::Http;

namespace winrt::Microsoft::Security::Authentication::OAuth::factory_implementation
{

    IAsyncOperation<AuthRequestResult> OAuth2Manager::RequestAuthWithParamsAsync(winrt::Microsoft::UI::WindowId const& parentWindowId,
        const Uri& authEndpoint,
        const oauth::AuthRequestParams& params)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled());


        bool isAppPackaged = m_telemetryHelper.IsPackagedApp();
        PCWSTR appName = m_telemetryHelper.GetAppName().c_str();

        auto paramsImpl = winrt::get_self<implementation::AuthRequestParams>(params);
        auto asyncOp = winrt::make_self<AuthRequestAsyncOperation>(paramsImpl);
        OAuth2ManagerTelemetry::RequestAuthWithParamsAsyncTriggered(isAppPackaged, appName, paramsImpl->ResponseType().c_str());


        {
            std::lock_guard guard{ m_mutex };
            m_pendingAuthRequests.push_back(AuthRequestState{ params.State(), asyncOp });
        }

        try
        {
            // Pipe server has been successfully set up. Initiate the launch
            auto url = paramsImpl->create_url(authEndpoint);

            // Launch browser
            execute_shell(parentWindowId, url);
        }
        catch (...)
        {
            try_remove(asyncOp.get());
            throw;
        }

        return *asyncOp;
    }

    bool OAuth2Manager::CompleteAuthRequest(const Uri& responseUri)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled());

        bool isAppPackaged = m_telemetryHelper.IsPackagedApp();
        PCWSTR appName = m_telemetryHelper.GetAppName().c_str();
        OAuth2ManagerTelemetry::CompleteAuthRequestTriggered(isAppPackaged, appName);
        // We need to extract the state in order to find the original request
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

            // Don't throw an error. It could be the case that the application just blindly calls this function first
            if (state.empty())
            {
                return false;
            }
        }

        // First check in our local pending list
        if (try_complete_local(state, responseUri))
        {
            return true;
        }

        // Not found locally; we need to check to see if the request originated in another process
        auto pipeName = request_pipe_name(state);

        // We encrypt the URI using the state as the key. This accomplishes a couple things: (1) it helps protect the
        // server from another process attaching and sending bogus data, and (2) it helps protect against sending the
        // authorization grant information to the wrong client. Both of these points of course become moot if the bad
        // party intercepts the state value, and because the state value is somewhat exposed through the browser launch/
        // URL, these steps are intended more as a defense in depth. Other features such as PKCE should be used to
        // ensure that codes/tokens are safe in the event that the state is compromised.
        auto encryptedUri = encrypt(responseUri.RawUri(), state);

        // When we create the named pipe, we only allow a single pipe instance. This should be fine under normal
        // circumstances, however it might be the case that another process attaches to the pipe. This may be
        // innocuous - e.g. the browser did multiple redirects - or it could be a bad actor - e.g. a process sending
        // random garbage to any pipe it can open or another process specifically targeting oauth. Therefore we make
        // multiple attempts to connect to the pipe
        wil::unique_handle pipe;
        while (true) // TODO: Bound this? Need to remember to return false if we do
        {
            pipe.reset(::CreateFileW(pipeName.c_str(), GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr));
            if (pipe) break;

            if (auto err = ::GetLastError(); err != ERROR_PIPE_BUSY)
            {
                // The pipe no longer exist; e.g. flow already completed, client cancelled, etc.
                return false;
            }

            if (!::WaitNamedPipeW(pipeName.c_str(), 100))
            {
                // 100ms should be enough time to wrap up any business. So either the system is bogged down (perhaps too
                // many requests to open the pipe), the pipe was closed, or the pipe was closed and opened by another
                // process who isn't being responsive.
                return false;
            }
        }

        ULONG serverPid = 0;
        if (::GetNamedPipeServerProcessId(pipe.get(), &serverPid))
        {
            ::AllowSetForegroundWindow(serverPid);

            // TODO: We can also possibly verify other things about the server process (exe path, etc.)
        }

        DWORD bytesToWrite = encryptedUri.Length();
        DWORD bytesWritten = 0;
        if (!::WriteFile(pipe.get(), encryptedUri.data(), bytesToWrite, &bytesWritten, nullptr) ||
            (bytesWritten != bytesToWrite))
        {
            // TODO: Actual error? This could be because the server timed us out...
            return false;
        }

        // The client should have the URI and the operation should be considered handled
        return true;
    }

    IAsyncOperation<oauth::TokenRequestResult> OAuth2Manager::RequestTokenAsync(Uri tokenEndpoint,
        oauth::TokenRequestParams params)
    {
        return RequestTokenAsync(std::move(tokenEndpoint), std::move(params), nullptr);
    }

    IAsyncOperation<oauth::TokenRequestResult> OAuth2Manager::RequestTokenAsync(Uri tokenEndpoint,
        oauth::TokenRequestParams params, oauth::ClientAuthentication clientAuth)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled());

        bool isAppPackaged = m_telemetryHelper.IsPackagedApp();
        PCWSTR appName = m_telemetryHelper.GetAppName().c_str();

        auto paramsImpl = winrt::get_self<implementation::TokenRequestParams>(params);
        paramsImpl->finalize();
        OAuth2ManagerTelemetry::RequestTokenAsyncTriggered(isAppPackaged, appName, paramsImpl->GrantType().c_str(), clientAuth ? true : false);
        HttpResponseMessage response{ nullptr };
        winrt::hstring responseString;
        try
        {
            HttpClient httpClient;
            HttpFormUrlEncodedContent content(winrt::single_threaded_map(paramsImpl->params()));
            HttpRequestMessage request(HttpMethod::Post(), tokenEndpoint);
            request.Content(content);

            auto headers = request.Headers();
            headers.Accept().ParseAdd(L"application/json");

            if (clientAuth)
            {
                if (auto auth = clientAuth.Authorization())
                {
                    headers.Authorization(auth);
                }

                if (auto proxyAuth = clientAuth.ProxyAuthorization())
                {
                    headers.ProxyAuthorization(proxyAuth);
                }

                if (auto map = clientAuth.AdditionalHeaders())
                {
                    for (auto&& pair : map)
                    {
                        if (!headers.TryAppendWithoutValidation(pair.Key(), pair.Value()))
                        {
                            // TODO? Why might this fail? Throw?
                        }
                    }
                }
            }

            auto lifetime{ get_strong() };
            auto cancellation = co_await winrt::get_cancellation_token();
            cancellation.enable_propagation();

            response = co_await httpClient.SendRequestAsync(request);
            // TODO: Check status code?
            if (!response.IsSuccessStatusCode())
            {
                auto status = response.StatusCode();
                HRESULT hr = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_HTTP, static_cast<HRESULT>(status));
                co_return implementation::TokenRequestResult::MakeFailure(std::move(response),
                    TokenFailureKind::HttpFailure, hr);
            }

            auto responseContentType = response.Content().Headers().ContentType().MediaType();
            if (responseContentType != L"application/json")
            {
                co_return implementation::TokenRequestResult::MakeFailure(std::move(response),
                    TokenFailureKind::InvalidResponse, WEB_E_UNSUPPORTED_FORMAT);
            }

            responseString = co_await response.Content().ReadAsStringAsync();
        }
        catch (...)
        {
            LOG_CAUGHT_EXCEPTION();
            co_return implementation::TokenRequestResult::MakeFailure(std::move(response),
                TokenFailureKind::HttpFailure, winrt::to_hresult());
        }

        JsonObject jsonObject{ nullptr };
        if (!JsonObject::TryParse(responseString, jsonObject))
        {
            co_return implementation::TokenRequestResult::MakeFailure(std::move(response),
                TokenFailureKind::InvalidResponse, WEB_E_INVALID_JSON_STRING);
        }
        else
        {
            try
            {
                // Determine if it's a success or error response based on the presence of 'error'
                if (jsonObject.HasKey(L"error"))
                {
                    auto failure = winrt::make<implementation::TokenFailure>(jsonObject);
                    co_return winrt::make<implementation::TokenRequestResult>(std::move(response), nullptr,
                        std::move(failure));
                }
                else
                {
                    auto success = winrt::make<implementation::TokenResponse>(jsonObject);
                    co_return winrt::make<implementation::TokenRequestResult>(std::move(response), std::move(success),
                        nullptr);
                }
            }
            catch (...)
            {
                LOG_CAUGHT_EXCEPTION();
                co_return implementation::TokenRequestResult::MakeFailure(std::move(response),
                    TokenFailureKind::InvalidResponse, winrt::to_hresult());
            }
        }
    }

    bool OAuth2Manager::try_complete_local(const winrt::hstring& state, const foundation::Uri& responseUri)
    {
        AuthRequestState requestState;
        {
            std::lock_guard guard{ m_mutex };
            auto itr = std::find_if(m_pendingAuthRequests.begin(), m_pendingAuthRequests.end(),
                [&](auto&& entry) { return entry.state == state; });

            if (itr != m_pendingAuthRequests.end())
            {
                requestState = std::move(*itr);
                *itr = std::move(m_pendingAuthRequests.back());
                m_pendingAuthRequests.pop_back();
            }
        }

        if (requestState.async_op)
        {
            // Found locally
            requestState.async_op->complete(responseUri);
            return true;
        }

        return false;
    }

    void OAuth2Manager::cancel(AuthRequestAsyncOperation* op)
    {
        auto requestState = try_remove(op);
        if (requestState.async_op)
        {
            requestState.async_op->cancel();
        }
    }

    void OAuth2Manager::error(AuthRequestAsyncOperation* op, winrt::hresult hr)
    {
        auto requestState = try_remove(op);
        if (requestState.async_op)
        {
            requestState.async_op->error(hr);
        }
    }

    AuthRequestState OAuth2Manager::try_remove(AuthRequestAsyncOperation* op)
    {
        std::lock_guard guard{ m_mutex };
        auto itr = std::find_if(m_pendingAuthRequests.begin(), m_pendingAuthRequests.end(),
            [&](auto&& entry) { return entry.async_op.get() == op; });

        AuthRequestState result;
        if (itr != m_pendingAuthRequests.end())
        {
            result = std::move(*itr);
            *itr = std::move(m_pendingAuthRequests.back());
            m_pendingAuthRequests.pop_back();
        }

        return result;
    }

    void OAuth2Manager::execute_shell(winrt::Microsoft::UI::WindowId const& parentWindowId, const std::wstring& url)
    {
        // Convert parentWindowId to HWND
        HWND hwndParent = reinterpret_cast<HWND>(parentWindowId.Value);

        SHELLEXECUTEINFO sei = { sizeof(sei) };
        sei.fMask = SEE_MASK_NOCLOSEPROCESS;
        sei.hwnd = hwndParent;
        sei.lpVerb = L"open";
        sei.lpFile = url.c_str();
        sei.lpParameters = nullptr;
        sei.lpDirectory = nullptr;
        sei.nShow = SW_SHOWDEFAULT;
        sei.hInstApp = nullptr;

        if (!ShellExecuteExW(&sei))
        {
            throw winrt::hresult_error(HRESULT_FROM_WIN32(::GetLastError()), L"Failed to launch browser");
        }
    }
}
