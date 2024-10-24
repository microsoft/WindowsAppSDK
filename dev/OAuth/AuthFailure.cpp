// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "common.h"

#include "AuthFailure.h"

#include <Microsoft.Security.Authentication.OAuth.AuthFailure.g.cpp>

using namespace std::literals;
using namespace winrt::Microsoft::Security::Authentication::OAuth;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    AuthFailure::AuthFailure(const Uri& responseUri)
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
                if (name == L"error"sv)
                {
                    m_error = entry.Value();
                }
                else if (name == L"error_description"sv)
                {
                    m_errorDescription = entry.Value();
                }
                else if (name == L"error_uri"sv)
                {
                    m_errorUri = Uri(entry.Value());
                }
                else if (name == L"state"sv)
                {
                    m_state = entry.Value();
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

    winrt::hstring AuthFailure::Error()
    {
        return m_error;
    }

    winrt::hstring AuthFailure::ErrorDescription()
    {
        return m_errorDescription;
    }

    Uri AuthFailure::ErrorUri()
    {
        return m_errorUri;
    }

    winrt::hstring AuthFailure::State()
    {
        return m_state;
    }

    IMapView<winrt::hstring, winrt::hstring> AuthFailure::AdditionalParams()
    {
        return m_additionalParams;
    }
}
