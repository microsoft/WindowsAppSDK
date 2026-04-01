// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include <Microsoft.Security.Authentication.OAuth.TokenResponse.g.h>

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    struct TokenResponse : TokenResponseT<TokenResponse>
    {
        TokenResponse(const json::JsonObject& jsonObject);

        winrt::hstring AccessToken();
        winrt::hstring TokenType();
        double ExpiresIn();
        winrt::hstring RefreshToken();
        winrt::hstring Scope();
        collections::IMapView<winrt::hstring, json::IJsonValue> AdditionalParams();

    private:
        winrt::hstring m_accessToken;
        winrt::hstring m_tokenType;
        double m_expiresIn;
        winrt::hstring m_refreshToken;
        winrt::hstring m_scope;
        collections::IMapView<winrt::hstring, json::IJsonValue> m_additionalParams;
    };
}
