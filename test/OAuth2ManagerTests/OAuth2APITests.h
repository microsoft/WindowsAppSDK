// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <cassert>
#include <string_view>


// The 'client_id' describes the behavior and expectations of our mocked authorization server
// Specifying grant type is required
#define GRANT_TYPE_CODE L"grant=code"
#define GRANT_TYPE_TOKEN L"grant=token"
#define GRANT_TYPE_CLIENT L"grant=client"
#define GRANT_TYPE_REFRESH L"grant=refresh"
#define GRANT_TYPE_EXTENSION L"grant=extension"

// Specifying redirect type is required
#define REDIRECT_TYPE_LOCALHOST "&redirect=localhost"
#define REDIRECT_TYPE_PROTOCOL "&redirect=protocol"

// 'none' is the default if not specified
#define AUTH_TYPE_HEADER "&auth=header"

// 'none' is the default if not specified
#define TOKEN_ERROR_RESPONSE "&error=token"

// 'false' is the default if not specified
#define ADDITIONAL_PARAMS "&additional_params=true"

// Constants to validate expectations. The strings are specifically chosen to validate proper escaping of special characters
inline constexpr std::wstring_view error_description = L"This is an error & it contains characters like \"=\"";
inline constexpr std::wstring_view json_escaped_error_description = L"This is an error & it contains characters like \\\"=\\\"";
inline constexpr std::wstring_view error_uri = L"https://contoso.com/errors?foo=bar";

inline constexpr std::wstring_view additional_param_key = L"use=key&name=foo";
inline constexpr std::wstring_view additional_param_value = L"use=value&name=bar";

inline constexpr std::wstring_view extension_grant_uri = L"oauth:test:extension";

inline constexpr std::wstring_view token = L"tacos=yummy&location=\"my tummy\"";
inline constexpr std::wstring_view json_escaped_token = L"tacos=yummy&location=\\\"my tummy\\\"";
inline constexpr std::wstring_view refresh_token_old = L"~!@#$%^&*()_+`-=[]\\{};':\",./<>?-old";
inline constexpr std::wstring_view refresh_token = L"~!@#$%^&*()_+`-=[]\\{};':\",./<>?";
inline constexpr std::wstring_view json_escaped_refresh_token = L"~!@#$%^&*()_+`-=[]\\\\{};':\\\",./<>?";

struct uri_builder
{
    std::wstring uri;
    wchar_t prefix;

    uri_builder(const winrt::Windows::Foundation::Uri& uri, bool useQuery = true) :
        uri(uri.RawUri())
    {
        if (useQuery)
        {
            prefix = uri.Query().empty() ? L'?' : '&';
        }
        else
        {
            prefix = '#';
        }
    }

    void add(std::wstring_view name, std::wstring_view value)
    {
        assert(!name.empty() && !value.empty());

        uri.push_back(prefix);
        prefix = L'&';
        uri.append(winrt::Windows::Foundation::Uri::EscapeComponent(name));
        uri.push_back(L'=');
        uri.append(winrt::Windows::Foundation::Uri::EscapeComponent(value));
    }

    void add_optional(std::wstring_view name, std::wstring_view value)
    {
        if (!value.empty())
        {
            add(name, value);
        }
    }

    winrt::Windows::Foundation::Uri get()
    {
        return winrt::Windows::Foundation::Uri{ uri };
    }
};
