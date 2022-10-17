#pragma once
#include <Microsoft.Windows.Security.Authentication.OAuth.AuthRequestResult.g.h>

#include "AuthRequestParams.h"

namespace winrt::Microsoft::Windows::Security::Authentication::OAuth::implementation
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
