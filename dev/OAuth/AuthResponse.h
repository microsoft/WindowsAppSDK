// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include <Microsoft.Security.Authentication.OAuth.AuthResponse.g.h>

#include "AuthRequestParams.h"

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    struct AuthResponse : AuthResponseT<AuthResponse>
    {
        AuthResponse(AuthRequestParams* params, const foundation::Uri& responseUri);

        winrt::hstring State();
        winrt::hstring Code();
        winrt::hstring AccessToken();
        winrt::hstring TokenType();
        winrt::hstring ExpiresIn();
        winrt::hstring Scope();
        collections::IMapView<winrt::hstring, winrt::hstring> AdditionalParams();

        // Implementation functions
        const winrt::com_ptr<AuthRequestParams>& request_params() const noexcept
        {
            return m_requestParams;
        }

    private:
        winrt::com_ptr<AuthRequestParams> m_requestParams;

        winrt::hstring m_state;
        winrt::hstring m_code;
        winrt::hstring m_accessToken;
        winrt::hstring m_tokenType;
        winrt::hstring m_expiresIn;
        winrt::hstring m_scope;
        collections::IMapView<winrt::hstring, winrt::hstring> m_additionalParams;
    };
}
