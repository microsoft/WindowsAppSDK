// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

std::string ConvertWideStringToUtf8String(_In_ std::wstring const& utf16string)
{
    int size = WideCharToMultiByte(
        CP_UTF8,
        0,
        utf16string.data(),
        static_cast<int>(utf16string.length()),
        nullptr,
        0,
        nullptr,
        nullptr);

    THROW_LAST_ERROR_IF(size == 0);

    std::string utf8string;
    utf8string.resize(size);

    size = WideCharToMultiByte(
        CP_UTF8,
        0,
        utf16string.data(),
        static_cast<int>(utf16string.length()),
        &utf8string[0],
        size,
        nullptr,
        nullptr);

    THROW_LAST_ERROR_IF(size == 0);

    return utf8string;
}
