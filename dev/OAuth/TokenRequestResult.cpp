// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "common.h"

#include "TokenFailure.h"
#include "TokenRequestResult.h"
#include "TokenResponse.h"

#include <Microsoft.Security.Authentication.OAuth.TokenRequestResult.g.cpp>

using namespace winrt::Microsoft::Security::Authentication::OAuth;
using namespace winrt::Windows::Data::Json;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Web::Http;

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    TokenRequestResult::TokenRequestResult(HttpResponseMessage responseMessage, oauth::TokenResponse response,
        oauth::TokenFailure failure) :
        m_responseMessage(std::move(responseMessage)),
        m_response(std::move(response)),
        m_failure(std::move(failure))
    {
    }

    oauth::TokenRequestResult TokenRequestResult::MakeFailure(HttpResponseMessage response,
        TokenFailureKind failureKind, winrt::hresult failureCode)
    {
        return winrt::make<TokenRequestResult>(std::move(response), nullptr,
            winrt::make<TokenFailure>(failureKind, failureCode));
    }

    HttpResponseMessage TokenRequestResult::ResponseMessage()
    {
        return m_responseMessage;
    }

    oauth::TokenResponse TokenRequestResult::Response()
    {
        return m_response;
    }

    oauth::TokenFailure TokenRequestResult::Failure()
    {
        return m_failure;
    }
}
