// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include <Microsoft.Security.Authentication.OAuth.OAuth2Manager.g.h>

#include "AuthRequestAsyncOperation.h"
#include "TelemetryHelper.h"

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    struct OAuth2Manager;
}

namespace winrt::Microsoft::Security::Authentication::OAuth::factory_implementation
{
    struct AuthRequestState
    {
        winrt::hstring state;
        winrt::com_ptr<AuthRequestAsyncOperation> async_op;
    };

    struct OAuth2Manager : OAuth2ManagerT<OAuth2Manager, implementation::OAuth2Manager, winrt::static_lifetime>
    {
        foundation::IAsyncOperation<oauth::AuthRequestResult> RequestAuthWithParamsAsync(
            winrt::Microsoft::UI::WindowId const& parentWindowId, const foundation::Uri& authEndpoint, const oauth::AuthRequestParams& params);
        bool CompleteAuthRequest(const foundation::Uri& responseUri);
        foundation::IAsyncOperation<oauth::TokenRequestResult> RequestTokenAsync(foundation::Uri tokenEndpoint,
            oauth::TokenRequestParams params);
        foundation::IAsyncOperation<oauth::TokenRequestResult> RequestTokenAsync(foundation::Uri tokenEndpoint,
            oauth::TokenRequestParams params, oauth::ClientAuthentication clientAuth);

        // Implementation functions
        bool try_complete_local(const winrt::hstring& state, const foundation::Uri& responseUri);
        void cancel(AuthRequestAsyncOperation* op);
        void error(AuthRequestAsyncOperation* op, winrt::hresult hr);

    private:
        AuthRequestState try_remove(AuthRequestAsyncOperation* op);

        void execute_shell(winrt::Microsoft::UI::WindowId const& parentWindowId, const std::wstring& url);
        std::shared_mutex m_mutex;
        TelemetryHelper m_telemetryHelper;
        std::vector<AuthRequestState> m_pendingAuthRequests;
    };
}

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    struct OAuth2Manager
    {

        static foundation::IAsyncOperation<oauth::AuthRequestResult> RequestAuthWithParamsAsync(
            winrt::Microsoft::UI::WindowId const& parentWindowId,
            foundation::Uri authEndpoint, oauth::AuthRequestParams params)
        {
            return winrt::make_self<factory_implementation::OAuth2Manager>()->RequestAuthWithParamsAsync(parentWindowId,
                authEndpoint,
                params);
        }

        static bool CompleteAuthRequest(const foundation::Uri& responseUri)
        {
            return winrt::make_self<factory_implementation::OAuth2Manager>()->CompleteAuthRequest(responseUri);
        }

        static foundation::IAsyncOperation<oauth::TokenRequestResult> RequestTokenAsync(foundation::Uri tokenEndpoint,
            oauth::TokenRequestParams params)
        {
            return winrt::make_self<factory_implementation::OAuth2Manager>()->RequestTokenAsync(std::move(tokenEndpoint),
                std::move(params));
        }

        static foundation::IAsyncOperation<oauth::TokenRequestResult> RequestTokenAsync(foundation::Uri tokenEndpoint,
            oauth::TokenRequestParams params, oauth::ClientAuthentication clientAuth)
        {
            return winrt::make_self<factory_implementation::OAuth2Manager>()->RequestTokenAsync(std::move(tokenEndpoint),
                std::move(params), std::move(clientAuth));
        }
    };
}
