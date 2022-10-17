#pragma once

#include <cassert>
#include <string_view>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

// Strings associated with errors
namespace strings::error
{
    inline constexpr std::wstring_view invalid_request = L"invalid_request";
    inline constexpr std::wstring_view unauthorized_client = L"unauthorized_client";
    inline constexpr std::wstring_view access_denied = L"access_denied";
    inline constexpr std::wstring_view unsupported_response_type = L"unsupported_response_type";
    inline constexpr std::wstring_view invalid_scope = L"invalid_scope";
    inline constexpr std::wstring_view server_error = L"server_error";
    inline constexpr std::wstring_view temporarily_unavailable = L"temporarily_unavailable";
}

// Strings associated with the request
namespace strings::request
{
    inline constexpr std::wstring_view response_type = L"response_type";
    inline constexpr std::wstring_view client_id = L"client_id";
    inline constexpr std::wstring_view redirect_uri = L"redirect_uri";
    inline constexpr std::wstring_view scope = L"scope";
    inline constexpr std::wstring_view state = L"state";
    inline constexpr std::wstring_view code_challenge = L"code_challenge";
    inline constexpr std::wstring_view code_challenge_method = L"code_challenge_method";
}

namespace strings::response_type
{

    inline constexpr std::wstring_view code = L"code";
    inline constexpr std::wstring_view token = L"token";
}

// Test parameters that we embed in the client_id
namespace strings::client_id
{
    inline constexpr std::wstring_view scenario = L"scenario";
    //inline constexpr std::wstring_view expect_success = L"expect_success";
    //inline constexpr std::wstring_view expect_additional_params = L"expect_additional_params";
    //inline constexpr std::wstring_view report_expires_in = L"report_expires_in";
    //inline constexpr std::wstring_view limit_scope = L"limit_scope";
}

// We're not issuing real tokens, so use a predictable string for validation. This string is specifically formulated to
// ensure that we escape/encode characters properly
inline constexpr std::wstring_view token = L"tacos=yummy&location=\"my tummy\"";

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

// Each test has its own "client id" so that we can differentiate which test is running. Note that this intentionally
// uses characters that need to be urlencoded
// #define TEST_CLIENT_ID(test) L"client:test=" ##test
//
//#define INCORRECT_STATE_CLIENT_ID TEST_CLIENT_ID(IncorrectState)
//#define COMPLETE_TWICE_CLIENT_ID TEST_CLIENT_ID(CompleteTwice)
//
//// We control the behavior of the fake user agent and authorization server through the client id
//#define TEST_CLIENT_ID(expectSuccess, expectAdditionalParams, reportExpiresIn, limitScope) \
//    L"expect_success=" ##expectSuccess "&expect_additional_params=" ##expectAdditionalParams \
//    "&report_expires_in=" ##reportExpiresIn L"&limit_scope=" ##limitScope
