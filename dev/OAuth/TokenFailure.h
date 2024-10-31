// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once
#include <Microsoft.Security.Authentication.OAuth.TokenFailure.g.h>

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    struct TokenFailure : TokenFailureT<TokenFailure>
    {
        TokenFailure(TokenFailureKind kind, winrt::hresult code);
        TokenFailure(const json::JsonObject& jsonObject);

        TokenFailureKind Kind();
        winrt::hresult ErrorCode();
        winrt::hstring Error();
        winrt::hstring ErrorDescription();
        foundation::Uri ErrorUri();
        collections::IMapView<winrt::hstring, json::IJsonValue> AdditionalParams();

    private:
        TokenFailureKind m_kind;
        winrt::hresult m_errorCode;
        winrt::hstring m_error;
        winrt::hstring m_errorDescription;
        foundation::Uri m_errorUri{ nullptr };
        collections::IMapView<winrt::hstring, json::IJsonValue> m_additionalParams;
    };
}
