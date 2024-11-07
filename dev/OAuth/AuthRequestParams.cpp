// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "common.h"

#include "AuthRequestParams.h"

#include <Microsoft.Security.Authentication.OAuth.AuthRequestParams.g.cpp>

using namespace winrt::Microsoft::Security::Authentication::OAuth;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Security::Cryptography;
using namespace winrt::Windows::Security::Cryptography::Core;

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    AuthRequestParams::AuthRequestParams(const winrt::hstring& responseType, const winrt::hstring& clientId) :
        m_responseType(responseType),
        m_clientId(clientId)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled());
    }

    AuthRequestParams::AuthRequestParams(const winrt::hstring& responseType, const winrt::hstring& clientId,
        const Uri& redirectUri) :
        m_responseType(responseType),
        m_clientId(clientId),
        m_redirectUri(redirectUri)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Security::Authentication::OAuth::Feature_OAuth::IsEnabled());
    }

    oauth::AuthRequestParams AuthRequestParams::CreateForAuthorizationCodeRequest(const winrt::hstring& clientId)
    {
        return CreateForAuthorizationCodeRequest(clientId, nullptr);
    }

    oauth::AuthRequestParams AuthRequestParams::CreateForAuthorizationCodeRequest(const winrt::hstring& clientId,
        const Uri& redirectUri)
    {
        auto result = winrt::make_self<AuthRequestParams>(L"code", clientId, redirectUri);
        result->m_codeChallengeMethod = CodeChallengeMethodKind::S256;
        return *result;
    }

    oauth::AuthRequestParams AuthRequestParams::CreateForImplicitRequest(const winrt::hstring& clientId)
    {
        return winrt::make<AuthRequestParams>(L"token", clientId);
    }

    oauth::AuthRequestParams AuthRequestParams::CreateForImplicitRequest(const winrt::hstring& clientId,
        const Uri& redirectUri)
    {
        return winrt::make<AuthRequestParams>(L"token", clientId, redirectUri);
    }

    winrt::hstring AuthRequestParams::ResponseType()
    {
        std::shared_lock guard{ m_mutex };
        return m_responseType;
    }

    void AuthRequestParams::ResponseType(const winrt::hstring& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_responseType = value;
    }

    winrt::hstring AuthRequestParams::ClientId()
    {
        std::shared_lock guard{ m_mutex };
        return m_clientId;
    }

    void AuthRequestParams::ClientId(const winrt::hstring& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_clientId = value;
    }

    Uri AuthRequestParams::RedirectUri()
    {
        std::shared_lock guard{ m_mutex };
        return m_redirectUri;
    }

    void AuthRequestParams::RedirectUri(const Uri& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_redirectUri = value;
    }

    winrt::hstring AuthRequestParams::State()
    {
        std::shared_lock guard{ m_mutex };
        return m_state;
    }

    void AuthRequestParams::State(const winrt::hstring& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_state = value;
    }

    winrt::hstring AuthRequestParams::Scope()
    {
        std::shared_lock guard{ m_mutex };
        return m_scope;
    }

    void AuthRequestParams::Scope(const winrt::hstring& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_scope = value;
    }

    winrt::hstring AuthRequestParams::CodeChallenge()
    {
        std::shared_lock guard{ m_mutex };
        return m_codeChallenge;
    }

    void AuthRequestParams::CodeChallenge(const winrt::hstring& value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_codeChallenge = value;
    }

    CodeChallengeMethodKind AuthRequestParams::CodeChallengeMethod()
    {
        std::shared_lock guard{ m_mutex };
        return m_codeChallengeMethod;
    }

    void AuthRequestParams::CodeChallengeMethod(CodeChallengeMethodKind value)
    {
        std::lock_guard guard{ m_mutex };
        check_not_finalized();
        m_codeChallengeMethod = value;
    }

    IMap<winrt::hstring, winrt::hstring> AuthRequestParams::AdditionalParams()
    {
        std::shared_lock guard{ m_mutex };
        return *m_additionalParams;
    }

    void AuthRequestParams::finalize()
    {
        std::lock_guard guard{ m_mutex };
        if (m_finalized)
        {
            throw winrt::hresult_illegal_method_call(L"AuthRequestParams can only be used for a single request call");
        }

        m_finalized = true;
        m_additionalParams->lock();

        if (!m_codeChallenge.empty() && (m_codeChallengeMethod == CodeChallengeMethodKind::None))
        {
            throw winrt::hresult_illegal_method_call(
                L"'CodeChallenge' cannot be set when 'CodeChallengeMethod' is set to 'None'");
        }
    }

    void AuthRequestParams::set_state(winrt::hstring value)
    {
        std::lock_guard guard{ m_mutex };
        WINRT_ASSERT(m_state.empty());
        m_state = std::move(value);
    }

    void AuthRequestParams::set_code_challenge(winrt::hstring value)
    {
        std::lock_guard guard{ m_mutex };
        WINRT_ASSERT(m_codeChallenge.empty());
        WINRT_ASSERT(m_codeChallengeMethod != CodeChallengeMethodKind::None);
        m_codeChallenge = std::move(value);
    }

    std::wstring AuthRequestParams::create_url(const Uri& authEndpoint)
    {
        std::shared_lock guard{ m_mutex };
        WINRT_ASSERT(m_finalized);

        // Per RFC 6749 section 3.1, the auth endpoint URI *MAY* contain a query string, which must be retained
        std::wstring result{ authEndpoint.RawUri() };
        if (authEndpoint.Query().empty())
        {
            result += L"?state=";
        }
        else
        {
            result += L"&state=";
        }

        result += Uri::EscapeComponent(m_state);

        if (!m_responseType.empty())
        {
            result += L"&response_type=";
            result += Uri::EscapeComponent(m_responseType);
        }

        if (!m_clientId.empty())
        {
            result += L"&client_id=";
            result += Uri::EscapeComponent(m_clientId);
        }

        if (m_redirectUri)
        {
            result += L"&redirect_uri=";
            result += Uri::EscapeComponent(m_redirectUri.RawUri());
        }

        if (!m_scope.empty())
        {
            result += L"&scope=";
            result += Uri::EscapeComponent(m_scope);
        }

        if (m_codeChallengeMethod == CodeChallengeMethodKind::S256)
        {
            result += L"&code_challenge_method=S256&code_challenge=";
            result += base64urlencode(sha256(m_codeChallenge));
        }
        else if (m_codeChallengeMethod == CodeChallengeMethodKind::Plain)
        {
            result += L"&code_challenge_method=plain&code_challenge=";
            result += Uri::EscapeComponent(m_codeChallenge);
        }

        if (m_additionalParams)
        {
            for (auto&& pair : IMap<winrt::hstring, winrt::hstring>{ *m_additionalParams })
            {
                result += L"&";
                result += Uri::EscapeComponent(pair.Key());
                result += L"=";
                result += Uri::EscapeComponent(pair.Value());
            }
        }

        return result;
    }
}
