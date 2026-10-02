// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MockRawNotification.h"

winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::hstring> MockRawNotification::Headers()
{
    return winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::hstring>{};
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
    return winrt::Windows::Security::Cryptography::CryptographicBuffer::ConvertStringToBinary(
        c_rawNotificationPayload,
        winrt::Windows::Security::Cryptography::BinaryStringEncoding::Utf8);
}
