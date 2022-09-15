// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Security::Cryptography;

IMapView<winrt::hstring, winrt::hstring> MockRawNotification::Headers()
{
    return IMapView<winrt::hstring, winrt::hstring>{};
}

winrt::hstring MockRawNotification::ChannelId()
{
    return winrt::hstring(L"SampleChannelId");
}

winrt::hstring MockRawNotification::Content()
{
    return winrt::hstring(c_rawNotificationPayload);
}

winrt::Windows::Storage::Streams::IBuffer MockRawNotification::ContentBytes()
{
    return CryptographicBuffer::ConvertStringToBinary(
        c_rawNotificationPayload,
        BinaryStringEncoding::Utf8);
}
