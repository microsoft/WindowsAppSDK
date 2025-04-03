// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include <Microsoft.Security.Authentication.OAuth.AuthRequestResult.g.h>

#include "AuthRequestParams.h"

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    struct AuthRequestResult : AuthRequestResultT<AuthRequestResult>
    {
        AuthRequestResult(AuthRequestParams* params, const foundation::Uri& responseUri);

        foundation::Uri ResponseUri();
        oauth::AuthResponse Response();
        oauth::AuthFailure Failure();

    private:
        foundation::Uri m_responseUri;
        oauth::AuthResponse m_response{ nullptr };
        oauth::AuthFailure m_failure{ nullptr };
    };
}
