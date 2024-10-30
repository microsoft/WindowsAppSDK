// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include <Microsoft.Security.Authentication.OAuth.AuthFailure.g.h>

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    struct AuthFailure : AuthFailureT<AuthFailure>
    {
        AuthFailure(const foundation::Uri& responseUri);

        winrt::hstring Error();
        winrt::hstring ErrorDescription();
        foundation::Uri ErrorUri();
        winrt::hstring State();
        collections::IMapView<winrt::hstring, winrt::hstring> AdditionalParams();

    private:
        winrt::hstring m_error;
        winrt::hstring m_errorDescription;
        foundation::Uri m_errorUri{ nullptr };
        winrt::hstring m_state;
        collections::IMapView<winrt::hstring, winrt::hstring> m_additionalParams;
    };
}
