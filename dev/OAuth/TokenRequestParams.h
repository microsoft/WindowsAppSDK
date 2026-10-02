// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include <Microsoft.Security.Authentication.OAuth.TokenRequestParams.g.h>

#include <shared_mutex>

#include "LockableMap.h"

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    struct TokenRequestParams : TokenRequestParamsT<TokenRequestParams>
    {
        TokenRequestParams() = default;
        TokenRequestParams(const winrt::hstring& grantType);

        static oauth::TokenRequestParams CreateForAuthorizationCodeRequest(const oauth::AuthResponse& authResponse);
        static oauth::TokenRequestParams CreateForClientCredentials();
        static oauth::TokenRequestParams CreateForExtension(const foundation::Uri& extensionUri);
        static oauth::TokenRequestParams CreateForRefreshToken(const winrt::hstring& refreshToken);

        winrt::hstring GrantType();
        void GrantType(const winrt::hstring& value);
        winrt::hstring Code();
        void Code(const winrt::hstring& value);
        foundation::Uri RedirectUri();
        void RedirectUri(const foundation::Uri& value);
        winrt::hstring CodeVerifier();
        void CodeVerifier(const winrt::hstring& value);
        winrt::hstring ClientId();
        void ClientId(const winrt::hstring& value);
        winrt::hstring Username();
        void Username(const winrt::hstring& value);
        winrt::hstring Password();
        void Password(const winrt::hstring& value);
        winrt::hstring Scope();
        void Scope(const winrt::hstring& value);
        winrt::hstring RefreshToken();
        void RefreshToken(const winrt::hstring& value);
        collections::IMap<winrt::hstring, winrt::hstring> AdditionalParams();

        // Implementation functions
        void finalize();
        std::map<winrt::hstring, winrt::hstring> params();

    private:
        void check_not_finalized()
        {
            // NOTE: Lock should be held when calling
            if (m_finalized)
            {
                throw winrt::hresult_illegal_method_call(
                    L"TokenRequestParams object cannot be modified after being used to initiate a request");
            }
        }

        std::shared_mutex m_mutex;
        bool m_finalized = false;
        winrt::hstring m_grantType;
        winrt::hstring m_code;
        foundation::Uri m_redirectUri{ nullptr };
        winrt::hstring m_codeVerifier;
        winrt::hstring m_clientId;
        winrt::hstring m_username;
        winrt::hstring m_password;
        winrt::hstring m_scope;
        winrt::hstring m_refreshToken;
        winrt::com_ptr<LockableMap<winrt::hstring, winrt::hstring>> m_additionalParams =
            winrt::make_self<LockableMap<winrt::hstring, winrt::hstring>>();
    };
}

namespace winrt::Microsoft::Security::Authentication::OAuth::factory_implementation
{
    struct TokenRequestParams : TokenRequestParamsT<TokenRequestParams, implementation::TokenRequestParams>
    {
    };
}
