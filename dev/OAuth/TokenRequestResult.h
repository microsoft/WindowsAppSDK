// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include <Microsoft.Security.Authentication.OAuth.TokenRequestResult.g.h>

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    struct TokenRequestResult : TokenRequestResultT<TokenRequestResult>
    {
        TokenRequestResult(http::HttpResponseMessage responseMessage, oauth::TokenResponse resposne,
            oauth::TokenFailure failure);

        static oauth::TokenRequestResult MakeFailure(http::HttpResponseMessage response, TokenFailureKind failureKind,
            winrt::hresult failureCode);

        http::HttpResponseMessage ResponseMessage();
        oauth::TokenResponse Response();
        oauth::TokenFailure Failure();

    private:
        http::HttpResponseMessage m_responseMessage;
        oauth::TokenResponse m_response{ nullptr };
        oauth::TokenFailure m_failure{ nullptr };
    };
}
