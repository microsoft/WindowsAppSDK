
#pragma once

#include "pch.h"
#include <winrt/Windows.Security.Cryptography.h>

winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::hstring> PushRawNotification::Headers()
{
    return winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::hstring>{};
}

winrt::hstring PushRawNotification::ChannelId()
{
    return winrt::hstring();
}

winrt::hstring PushRawNotification::Content()
{
    return winrt::hstring(m_payload);
}

winrt::Windows::Storage::Streams::IBuffer PushRawNotification::ContentBytes()
{
    return winrt::Windows::Security::Cryptography::CryptographicBuffer::ConvertStringToBinary(
        m_payload,
        winrt::Windows::Security::Cryptography::BinaryStringEncoding::Utf8);
}
