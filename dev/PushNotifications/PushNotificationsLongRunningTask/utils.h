#pragma once

#include "pch.h"

const std::wstring ConvertByteArrayToWideString(unsigned int payloadLength, byte* payload)
{
    int size = MultiByteToWideChar(
        CP_UTF8,
        0,
        reinterpret_cast<PCSTR>(payload),
        payloadLength,
        nullptr,
        0);
    THROW_LAST_ERROR_IF(size == 0);

    std::wstring payloadAsWideString(size, 0);
    size = MultiByteToWideChar(
        CP_UTF8,
        0,
        reinterpret_cast<PCSTR>(payload),
        payloadLength,
        &payloadAsWideString[0],
        size);
    THROW_LAST_ERROR_IF(size == 0);

    return payloadAsWideString;
}
