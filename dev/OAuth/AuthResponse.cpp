// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "common.h"

#include "AuthResponse.h"

#include <Microsoft.Security.Authentication.OAuth.AuthResponse.g.cpp>

using namespace std::literals;
using namespace winrt::Microsoft::Security::Authentication::OAuth;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    AuthResponse::AuthResponse(AuthRequestParams* requestParams, const Uri& responseUri) :
        m_requestParams(requestParams->get_strong())
    {
        std::map<winrt::hstring, winrt::hstring> additionalParams;
        auto parseComponents = [&](const winrt::hstring& str) {
            if (str.empty())
            {
                return; // Avoid unnecessary construction/activation
            }

            for (auto&& entry : WwwFormUrlDecoder(str))
            {
                auto name = entry.Name();
                if (name == L"state"sv)
                {
                    m_state = entry.Value();
                }
                else if (name == L"code"sv)
                {
                    m_code = entry.Value();
                }
                else if (name == L"access_token"sv)
                {
                    m_accessToken = entry.Value();
                }
                else if (name == L"token_type"sv)
                {
                    m_tokenType = entry.Value();
                }
                else if (name == L"expires_in"sv)
                {
                    m_expiresIn = entry.Value();
                }
                else if (name == L"scope"sv)
                {
                    m_scope = entry.Value();
                }
                else
                {
                    additionalParams.emplace(std::move(name), entry.Value());
                }
            }
        };

        parseComponents(responseUri.Query());
        parseComponents(fragment_component(responseUri));

        m_additionalParams = winrt::single_threaded_map(std::move(additionalParams)).GetView();
    }

    winrt::hstring AuthResponse::State()
    {
        return m_state;
    }

    winrt::hstring AuthResponse::Code()
    {
        return m_code;
    }

    winrt::hstring AuthResponse::AccessToken()
    {
        return m_accessToken;
    }

    winrt::hstring AuthResponse::TokenType()
    {
        return m_tokenType;
    }

    winrt::hstring AuthResponse::ExpiresIn()
    {
        return m_expiresIn;
    }

    winrt::hstring AuthResponse::Scope()
    {
        return m_scope;
    }

    IMapView<winrt::hstring, winrt::hstring> AuthResponse::AdditionalParams()
    {
        return m_additionalParams;
    }
}
