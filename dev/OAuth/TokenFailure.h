#pragma once
#include <Microsoft.Windows.Security.Authentication.OAuth.TokenFailure.g.h>

namespace winrt::Microsoft::Windows::Security::Authentication::OAuth::implementation
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
