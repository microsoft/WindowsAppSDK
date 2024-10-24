// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include <Microsoft.Security.Authentication.OAuth.AuthRequestParams.g.h>

#include <shared_mutex>

#include "LockableMap.h"

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    struct AuthRequestParams : AuthRequestParamsT<AuthRequestParams>
    {
        AuthRequestParams(const winrt::hstring& responseType, const winrt::hstring& clientId);
        AuthRequestParams(const winrt::hstring& responseType, const winrt::hstring& clientId,
            const foundation::Uri& redirectUri);

        static oauth::AuthRequestParams CreateForAuthorizationCodeRequest(const winrt::hstring& clientId);
        static oauth::AuthRequestParams CreateForAuthorizationCodeRequest(const winrt::hstring& clientId,
            const foundation::Uri& redirectUri);
        static oauth::AuthRequestParams CreateForImplicitRequest(const winrt::hstring& clientId);
        static oauth::AuthRequestParams CreateForImplicitRequest(const winrt::hstring& clientId,
            const foundation::Uri& redirectUri);

        // Interface functions
        winrt::hstring ResponseType();
        void ResponseType(const winrt::hstring& value);
        winrt::hstring ClientId();
        void ClientId(const winrt::hstring& value);
        foundation::Uri RedirectUri();
        void RedirectUri(const foundation::Uri& value);
        winrt::hstring State();
        void State(const winrt::hstring& value);
        winrt::hstring Scope();
        void Scope(const winrt::hstring& value);
        winrt::hstring CodeChallenge();
        void CodeChallenge(const winrt::hstring& value);
        oauth::CodeChallengeMethodKind CodeChallengeMethod();
        void CodeChallengeMethod(oauth::CodeChallengeMethodKind value);
        collections::IMap<hstring, winrt::hstring> AdditionalParams();

        // Implementation functions
        void finalize();
        void set_state(winrt::hstring value);
        void set_code_challenge(winrt::hstring value);
        std::wstring create_url(const foundation::Uri& authEndpoint);

    private:
        void check_not_finalized()
        {
            // NOTE: Lock should be held when calling
            if (m_finalized)
            {
                throw winrt::hresult_illegal_method_call(
                    L"AuthRequestParams object cannot be modified after being used to initiate a request");
            }
        }

        std::shared_mutex m_mutex;
        bool m_finalized = false;
        winrt::hstring m_responseType;
        winrt::hstring m_clientId;
        foundation::Uri m_redirectUri{ nullptr };
        winrt::hstring m_state;
        winrt::hstring m_scope;
        winrt::hstring m_codeChallenge;
        oauth::CodeChallengeMethodKind m_codeChallengeMethod = oauth::CodeChallengeMethodKind::None;
        winrt::com_ptr<LockableMap<winrt::hstring, winrt::hstring>> m_additionalParams =
            winrt::make_self<LockableMap<winrt::hstring, winrt::hstring>>();
    };
}

namespace winrt::Microsoft::Security::Authentication::OAuth::factory_implementation
{
    struct AuthRequestParams : AuthRequestParamsT<AuthRequestParams, implementation::AuthRequestParams>
    {
    };
}
