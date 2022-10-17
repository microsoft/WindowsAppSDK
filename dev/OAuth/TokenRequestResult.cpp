#include <pch.h>
#include "common.h"

#include "TokenRequestResult.h"
#include <Microsoft.Windows.Security.Authentication.OAuth.TokenRequestResult.g.cpp>

#include "TokenFailure.h"
#include "TokenResponse.h"

using namespace winrt::Microsoft::Windows::Security::Authentication::OAuth;
using namespace winrt::Windows::Data::Json;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Web::Http;

namespace winrt::Microsoft::Windows::Security::Authentication::OAuth::implementation
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
