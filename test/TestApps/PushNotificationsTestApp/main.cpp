// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <testdef.h>

#include <wil/win32_helpers.h>
#include <iostream>

using namespace winrt::Microsoft::ApplicationModel::Activation;
using namespace winrt::Microsoft::ProjectReunion;
using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace Windows::Web::Http;

void SignalPhase(const std::wstring& phaseEventName)
{
    wil::unique_event phaseEvent;
    if (phaseEvent.try_open(phaseEventName.c_str(), EVENT_MODIFY_STATE, false))
    {
        phaseEvent.SetEvent();
    }
}

std::wstring BuildNotificationPayload(std::wstring channel)
{
    std::wstring channelUri = L"\"ChannelUri\":\"" + channel + L"\"";
    std::wstring x_wns_type = L"\"X_WNS_Type\": \"wns/raw\"";
    std::wstring contentType = L"\"Content_Type\": \"application/octet-stream\"";
    std::wstring payload = L"\"Payload\": \"<toast></toast>\"";
    std::wstring delay = L"\"Delay\": \"false\"";
    return { L"{" + channelUri + L"," + x_wns_type + L"," + contentType + L"," + payload + L"," + delay + L"}" };
}

void sendRequestToServer(winrt::hstring channel)
{
    HttpResponseMessage httpResponseMessage;
    std::wstring httpResponseBody;
    try {
        // Construct the HttpClient and Uri. This endpoint is for test purposes only.
        HttpClient httpClient;
        Uri requestUri{ L"http://localhost:7071/api/PostPushNotification" };

        // Construct the JSON to post.
        HttpStringContent jsonContent(
            BuildNotificationPayload(channel.c_str()),
            UnicodeEncoding::Utf8,
            L"application/json");

        // Post the JSON, and wait for a response.
        httpResponseMessage = httpClient.PostAsync(
            requestUri,
            jsonContent).get();

        // Make sure the post succeeded, and write out the response.
        httpResponseMessage.EnsureSuccessStatusCode();
        httpResponseBody = httpResponseMessage.Content().ReadAsStringAsync().get();
        std::wcout << httpResponseBody.c_str() << std::endl;
    }
    catch (winrt::hresult_error const& ex)
    {
        std::wcout << ex.message().c_str() << std::endl;
    }
}

int main()
{
    SignalPhase(c_testProtocolScheme_Packaged);
    return 0;
};
