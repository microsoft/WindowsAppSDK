#pragma once
#include <Microsoft.Security.Authentication.OAuth.AuthRequestParams.g.h>

#include <shared_mutex>

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
        winrt::hstring CodeVerifier();
        void CodeVerifier(const winrt::hstring& value);
        oauth::CodeChallengeMethodKind CodeChallengeMethod();
        void CodeChallengeMethod(oauth::CodeChallengeMethodKind value);
        collections::IMap<hstring, winrt::hstring> AdditionalParams();
        void AdditionalParams(const collections::IMap<winrt::hstring, winrt::hstring>& value);

        // Implementation functions
        void finalize();
        void set_state(winrt::hstring value);
        void set_code_verifier(winrt::hstring value);
        std::wstring create_url(const foundation::Uri& authEndpoint);

    private:
        void check_not_finalized();

        std::shared_mutex m_mutex;
        bool m_finalized = false;
        winrt::hstring m_responseType;
        winrt::hstring m_clientId;
        foundation::Uri m_redirectUri{ nullptr };
        winrt::hstring m_state;
        winrt::hstring m_scope;
        winrt::hstring m_codeVerifier;
        oauth::CodeChallengeMethodKind m_codeChallengeMethod;
        collections::IMap<winrt::hstring, winrt::hstring> m_additionalParams =
            winrt::multi_threaded_map<winrt::hstring, winrt::hstring>();
    };
}

namespace winrt::Microsoft::Security::Authentication::OAuth::factory_implementation
{
    struct AuthRequestParams : AuthRequestParamsT<AuthRequestParams, implementation::AuthRequestParams>
    {
    };
}
