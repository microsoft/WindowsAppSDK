// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "common.h"

#include "AuthResponse.h"
#include "TokenRequestParams.h"

#include <Microsoft.Security.Authentication.OAuth.TokenRequestParams.g.cpp>

using namespace winrt::Microsoft::Security::Authentication::OAuth;
using namespace winrt::Windows::Foundation;
using namespace Collections;

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    TokenRequestParams::TokenRequestParams(const winrt::hstring& grantType) : m_grantType(grantType)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled());
    }

    oauth::TokenRequestParams TokenRequestParams::CreateForAuthorizationCodeRequest(
        const oauth::AuthResponse& authResponse)
    {
        auto result = winrt::make_self<TokenRequestParams>(L"authorization_code");
        result->m_code = authResponse.Code();

        auto implResponse = winrt::get_self<AuthResponse>(authResponse);
        auto requestParams = implResponse->request_params();
        if (auto redirectUri = requestParams->RedirectUri())
        {
            result->m_redirectUri = std::move(redirectUri);
        }

        if (auto clientId = requestParams->ClientId(); !clientId.empty())
        {
            result->m_clientId = std::move(clientId);
        }

        if (auto codeVerifier = requestParams->CodeChallenge(); !codeVerifier.empty())
        {
            result->m_codeVerifier = std::move(codeVerifier);
        }

        return *result;
    }

    oauth::TokenRequestParams TokenRequestParams::CreateForClientCredentials()
    {
        return winrt::make<TokenRequestParams>(L"client_credentials");
    }

    oauth::TokenRequestParams TokenRequestParams::CreateForExtension(const Uri& extensionUri)
    {
        return winrt::make<TokenRequestParams>(extensionUri.RawUri());
    }

    oauth::TokenRequestParams TokenRequestParams::CreateForRefreshToken(const winrt::hstring& refreshToken)
    {
        auto result = winrt::make_self<TokenRequestParams>(L"refresh_token");
        result->m_refreshToken = refreshToken;

        return *result;
    }

    winrt::hstring TokenRequestParams::GrantType()
    {
        std::shared_lock guard{ m_mutex };
        return m_grantType;
    }

    void TokenRequestParams::GrantType(const winrt::hstring& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_grantType = value;
    }

    winrt::hstring TokenRequestParams::Code()
    {
        std::shared_lock guard{ m_mutex };
        return m_code;
    }

    void TokenRequestParams::Code(const winrt::hstring& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_code = value;
    }

    Uri TokenRequestParams::RedirectUri()
    {
        std::shared_lock guard{ m_mutex };
        return m_redirectUri;
    }

    void TokenRequestParams::RedirectUri(const Uri& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_redirectUri = value;
    }

    winrt::hstring TokenRequestParams::CodeVerifier()
    {
        std::shared_lock guard{ m_mutex };
        return m_codeVerifier;
    }

    void TokenRequestParams::CodeVerifier(const winrt::hstring& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_codeVerifier = value;
    }

    winrt::hstring TokenRequestParams::ClientId()
    {
        std::shared_lock guard{ m_mutex };
        return m_clientId;
    }

    void TokenRequestParams::ClientId(const winrt::hstring& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_clientId = value;
    }

    winrt::hstring TokenRequestParams::Username()
    {
        std::shared_lock guard{ m_mutex };
        return m_username;
    }

    void TokenRequestParams::Username(const winrt::hstring& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_username = value;
    }

    winrt::hstring TokenRequestParams::Password()
    {
        std::shared_lock guard{ m_mutex };
        return m_password;
    }

    void TokenRequestParams::Password(const winrt::hstring& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_password = value;
    }

    winrt::hstring TokenRequestParams::Scope()
    {
        std::shared_lock guard{ m_mutex };
        return m_scope;
    }

    void TokenRequestParams::Scope(const winrt::hstring& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_scope = value;
    }

    winrt::hstring TokenRequestParams::RefreshToken()
    {
        std::shared_lock guard{ m_mutex };
        return m_refreshToken;
    }

    void TokenRequestParams::RefreshToken(const winrt::hstring& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_refreshToken = value;
    }

    IMap<winrt::hstring, winrt::hstring> TokenRequestParams::AdditionalParams()
    {
        std::shared_lock guard{ m_mutex };
        return *m_additionalParams;
    }

    void TokenRequestParams::finalize()
    {
        std::lock_guard guard{ m_mutex };
        if (m_finalized)
        {
            throw winrt::hresult_illegal_method_call(L"TokenRequestParams can only be used for a single request call");
        }

        m_finalized = true;
        m_additionalParams->lock();
    }

    std::map<winrt::hstring, winrt::hstring> TokenRequestParams::params()
    {
        // HttpFormUrlEncodedContent requires an IIterable<IKeyValuePair<String, String>> as input. In theory we can
        // make the TokenRequestParams implement this type to save on some work, however this may be a little tricky
        std::map<winrt::hstring, winrt::hstring> result;
        auto addIfSet = [&](std::wstring_view key, const winrt::hstring& value) {
            if (!value.empty())
            {
                result.emplace(key, value);
            }
        };

        std::shared_lock guard{ m_mutex };
        addIfSet(L"grant_type", m_grantType);
        addIfSet(L"code", m_code);
        if (m_redirectUri) result.emplace(L"redirect_uri", m_redirectUri.RawUri());
        addIfSet(L"code_verifier", m_codeVerifier);
        addIfSet(L"client_id", m_clientId);
        addIfSet(L"username", m_username);
        addIfSet(L"password", m_password);
        addIfSet(L"scope", m_scope);
        addIfSet(L"refresh_token", m_refreshToken);
        for (auto&& pair : IMap<winrt::hstring, winrt::hstring>{ *m_additionalParams })
        {
            result.emplace(pair.Key(), pair.Value());
        }

        return result;
    }
}
