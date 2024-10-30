// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include <Microsoft.Security.Authentication.OAuth.ClientAuthentication.g.h>

#include <shared_mutex>

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    struct ClientAuthentication : ClientAuthenticationT<ClientAuthentication>
    {
        ClientAuthentication();
        ClientAuthentication(http::Headers::HttpCredentialsHeaderValue const& authorization);

        static oauth::ClientAuthentication CreateForBasicAuthorization(const winrt::hstring& clientId,
            const winrt::hstring& clientSecret);

        http::Headers::HttpCredentialsHeaderValue Authorization();
        void Authorization(http::Headers::HttpCredentialsHeaderValue const& value);
        http::Headers::HttpCredentialsHeaderValue ProxyAuthorization();
        void ProxyAuthorization(http::Headers::HttpCredentialsHeaderValue const& value);
        collections::IMap<winrt::hstring, winrt::hstring> AdditionalHeaders();

    private:
        std::shared_mutex m_mutex;
        http::Headers::HttpCredentialsHeaderValue m_authorization{ nullptr };
        http::Headers::HttpCredentialsHeaderValue m_proxyAuthorization{ nullptr };
        collections::IMap<winrt::hstring, winrt::hstring> m_additionalHeaders =
            winrt::multi_threaded_map<winrt::hstring, winrt::hstring>();
    };
}
namespace winrt::Microsoft::Security::Authentication::OAuth::factory_implementation
{
    struct ClientAuthentication : ClientAuthenticationT<ClientAuthentication, implementation::ClientAuthentication>
    {
    };
}
