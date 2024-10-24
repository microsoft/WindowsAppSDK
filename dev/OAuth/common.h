// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <winrt/Microsoft.Security.Authentication.OAuth.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Security.Cryptography.Core.h>
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Web.Http.Headers.h>

#include <TerminalVelocityFeatures-OAuth.h>

namespace collections = winrt::Windows::Foundation::Collections;
namespace crypto = winrt::Windows::Security::Cryptography;
namespace foundation = winrt::Windows::Foundation;
namespace http = winrt::Windows::Web::Http;
namespace json = winrt::Windows::Data::Json;
namespace oauth = winrt::Microsoft::Security::Authentication::OAuth;
namespace streams = winrt::Windows::Storage::Streams;

#include "Crypto.h"

inline winrt::hstring fragment_component(const foundation::Uri& uri)
{
    auto fragment = uri.Fragment();
    std::wstring_view fragmentStr = fragment;
    if (!fragmentStr.empty())
    {
        WINRT_ASSERT(fragmentStr.front() == '#');
        fragmentStr = fragmentStr.substr(1);
    }

    return winrt::hstring(fragmentStr);
}
