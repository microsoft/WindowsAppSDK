// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "common.h"

#include "TokenFailure.h"

#include <Microsoft.Security.Authentication.OAuth.TokenFailure.g.cpp>

using namespace std::literals;
using namespace winrt::Microsoft::Security::Authentication::OAuth;
using namespace winrt::Windows::Data::Json;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Microsoft::Security::Authentication::OAuth::implementation
{
    TokenFailure::TokenFailure(TokenFailureKind kind, winrt::hresult code) : m_kind(kind), m_errorCode(code) {}

    TokenFailure::TokenFailure(const JsonObject& jsonObject) :
        m_kind(TokenFailureKind::ErrorResponse),
        m_errorCode(E_FAIL)
    {
        std::map<winrt::hstring, IJsonValue> additionalParams;

        // NOTE: Functions like 'GetString' will throw if the value is not the requested type, so the calling code must
        // be ready to handle such failures
        for (auto&& pair : jsonObject)
        {
            auto name = pair.Key();
            if (name == L"error"sv)
            {
                m_error = pair.Value().GetString();
                // TODO: Use the error string to set a more accurate HRESULT?
            }
            else if (name == L"error_description"sv)
            {
                m_errorDescription = pair.Value().GetString();
            }
            else if (name == L"error_uri"sv)
            {
                m_errorUri = Uri(pair.Value().GetString());
            }
            else
            {
                additionalParams.emplace(std::move(name), pair.Value());
            }
        }

        m_additionalParams = winrt::single_threaded_map(std::move(additionalParams)).GetView();
    }

    TokenFailureKind TokenFailure::Kind()
    {
        return m_kind;
    }

    winrt::hresult TokenFailure::ErrorCode()
    {
        return m_errorCode;
    }

    winrt::hstring TokenFailure::Error()
    {
        return m_error;
    }

    winrt::hstring TokenFailure::ErrorDescription()
    {
        return m_errorDescription;
    }

    Uri TokenFailure::ErrorUri()
    {
        return m_errorUri;
    }

    IMapView<winrt::hstring, IJsonValue> TokenFailure::AdditionalParams()
    {
        return m_additionalParams;
    }
}
