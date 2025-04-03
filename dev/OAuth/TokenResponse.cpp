// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "common.h"

#include "TokenResponse.h"

#include <Microsoft.Security.Authentication.OAuth.TokenResponse.g.cpp>

using namespace winrt::Microsoft::Security::Authentication::OAuth;
using namespace winrt::Windows::Data::Json;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    TokenResponse::TokenResponse(const json::JsonObject& jsonObject)
    {
        std::map<winrt::hstring, IJsonValue> additionalParams;

        // NOTE: Functions like 'GetString' will throw if the value is not the requested type. It might be worth
        // revisiting this in the future
        for (auto&& pair : jsonObject)
        {
            auto name = pair.Key();
            if (name == L"access_token")
            {
                m_accessToken = pair.Value().GetString();
            }
            else if (name == L"token_type")
            {
                m_tokenType = pair.Value().GetString();
            }
            else if (name == L"expires_in")
            {
                m_expiresIn = pair.Value().GetNumber();
            }
            else if (name == L"refresh_token")
            {
                m_refreshToken = pair.Value().GetString();
            }
            else if (name == L"scope")
            {
                m_scope = pair.Value().GetString();
            }
            else
            {
                additionalParams.emplace(std::move(name), pair.Value());
            }
        }

        m_additionalParams = winrt::single_threaded_map(std::move(additionalParams)).GetView();
    }

    winrt::hstring TokenResponse::AccessToken()
    {
        return m_accessToken;
    }

    winrt::hstring TokenResponse::TokenType()
    {
        return m_tokenType;
    }

    double TokenResponse::ExpiresIn()
    {
        return m_expiresIn;
    }

    winrt::hstring TokenResponse::RefreshToken()
    {
        return m_refreshToken;
    }

    winrt::hstring TokenResponse::Scope()
    {
        return m_scope;
    }

    IMapView<winrt::hstring, IJsonValue> TokenResponse::AdditionalParams()
    {
        return m_additionalParams;
    }
}
