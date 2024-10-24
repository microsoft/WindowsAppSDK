// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "common.h"

#include "AuthFailure.h"
#include "AuthRequestResult.h"
#include "AuthResponse.h"

#include <Microsoft.Security.Authentication.OAuth.AuthRequestResult.g.cpp>

using namespace winrt::Microsoft::Security::Authentication::OAuth;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    AuthRequestResult::AuthRequestResult(AuthRequestParams* params, const Uri& responseUri) : m_responseUri(responseUri)
    {
        // We first need to figure out if this is a success or failure response
        bool isError = false;
        bool isSuccess = false;
        auto checkComponent = [&](const winrt::hstring& str) {
            if (str.empty())
            {
                return; // Avoid unnecessary construction/activation
            }

            for (auto&& entry : WwwFormUrlDecoder(str))
            {
                auto name = entry.Name();
                if ((name == L"code") || (name == L"access_token"))
                {
                    isSuccess = true;
                    break;
                }
                else if (name == L"error")
                {
                    isError = true;
                    break;
                }
            }
        };

        checkComponent(responseUri.Query());
        if (!isError && !isSuccess)
        {
            checkComponent(fragment_component(responseUri));
        }

        // If we don't recognize the response as an error, interpret it as success. The application may be using an
        // extension that we don't recognize
        if (isError)
        {
            m_failure = winrt::make<AuthFailure>(m_responseUri);
        }
        else
        {
            m_response = winrt::make<AuthResponse>(params, m_responseUri);
        }
    }

    Uri AuthRequestResult::ResponseUri()
    {
        return m_responseUri;
    }

    oauth::AuthResponse AuthRequestResult::Response()
    {
        return m_response;
    }

    oauth::AuthFailure AuthRequestResult::Failure()
    {
        return m_failure;
    }
}
