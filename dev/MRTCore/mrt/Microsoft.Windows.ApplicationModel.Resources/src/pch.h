// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include <unknwn.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include "..\..\core\src\MRM.h"

struct StringResourceFreer
{
    void operator()(wchar_t* resource) { MrmFreeResource(resource); }
};

struct EmbeddedResourceFreer
{
    void operator()(void* resource) { MrmFreeResource(resource); }
};

using string_resoure_ptr = std::unique_ptr<wchar_t, StringResourceFreer>;
using embedded_resoure_ptr = std::unique_ptr<void, EmbeddedResourceFreer>;
