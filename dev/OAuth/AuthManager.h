#pragma once
#include <Microsoft.Security.Authentication.OAuth.AuthManager.g.h>

#include "AuthRequestAsyncOperation.h"

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    struct AuthManager;
}

namespace winrt::Microsoft::Security::Authentication::OAuth::factory_implementation
{
    struct AuthRequestState
    {
        winrt::hstring state;
        winrt::com_ptr<AuthRequestAsyncOperation> async_op;
    };

    struct AuthManager : AuthManagerT<AuthManager, implementation::AuthManager, winrt::static_lifetime>
    {
        foundation::IAsyncOperation<oauth::AuthRequestResult> InitiateAuthRequestAsync(
            const foundation::Uri& authEndpoint, const oauth::AuthRequestParams& params);
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

        std::shared_mutex m_mutex;
        std::vector<AuthRequestState> m_pendingAuthRequests;
    };
}

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    struct AuthManager
    {
        static foundation::IAsyncOperation<oauth::AuthRequestResult> InitiateAuthRequestAsync(
            foundation::Uri authEndpoint, oauth::AuthRequestParams params)
        {
            return winrt::make_self<factory_implementation::AuthManager>()->InitiateAuthRequestAsync(authEndpoint,
                params);
        }

        static bool CompleteAuthRequest(const foundation::Uri& responseUri)
        {
            return winrt::make_self<factory_implementation::AuthManager>()->CompleteAuthRequest(responseUri);
        }

        static foundation::IAsyncOperation<oauth::TokenRequestResult> RequestTokenAsync(foundation::Uri tokenEndpoint,
            oauth::TokenRequestParams params)
        {
            return winrt::make_self<factory_implementation::AuthManager>()->RequestTokenAsync(std::move(tokenEndpoint),
                std::move(params));
        }

        static foundation::IAsyncOperation<oauth::TokenRequestResult> RequestTokenAsync(foundation::Uri tokenEndpoint,
            oauth::TokenRequestParams params, oauth::ClientAuthentication clientAuth)
        {
            return winrt::make_self<factory_implementation::AuthManager>()->RequestTokenAsync(std::move(tokenEndpoint),
                std::move(params), std::move(clientAuth));
        }
    };
}
