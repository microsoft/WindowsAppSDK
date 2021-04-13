// MessageTrigger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <string>
#include <iostream>
#include <sstream>
#include <winrt/Windows.Networking.PushNotifications.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Web.Http.Headers.h>
#include <Windows.h>
#include <sddl.h>

using namespace WEX::Common;
using namespace WEX::Logging;
using namespace WEX::TestExecution;

using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace Windows::Web::Http;

std::wstring BuildNotificationPayload(std::wstring channel)
{
    std::wstring channelUri = L"\"ChannelUri\":\"" + channel + L"\"";
    std::wstring x_wns_type = L"\"X_WNS_Type\": \"wns/raw\"";
    std::wstring contentType = L"\"Content_Type\": \"application/octet-stream\"";
    std::wstring payload = L"\"Payload\": \"<toast></toast>\"";
    std::wstring delay = L"\"Delay\": \"false\"";
    return { L"{" + channelUri + L"," + x_wns_type + L"," + contentType + L"," + payload + L"," + delay + L"}" };
}

void SendRequestToServer(std::wstring channelUri) {
    HttpResponseMessage httpResponseMessage;
    std::wstring httpResponseBody;
    try {
        // Construct the HttpClient and Uri. This endpoint is for test purposes only.
        HttpClient httpClient;
        Uri requestUri{ L"http://localhost:7071/api/PostPushNotification" };

        // Construct the JSON to post.
        HttpStringContent jsonContent(
            BuildNotificationPayload(channelUri),
            UnicodeEncoding::Utf8,
            L"application/json");

        // Post the JSON, and wait for a response.
        httpResponseMessage = httpClient.PostAsync(
            requestUri,
            jsonContent).get();

        // Make sure the post succeeded, and write out the response.
        httpResponseMessage.EnsureSuccessStatusCode();
        httpResponseBody = httpResponseMessage.Content().ReadAsStringAsync().get();
        std::wcout << httpResponseBody.c_str() << L": ";
    }
    catch (winrt::hresult_error const& ex)
    {
        std::wcout << ex.message().c_str() << std::endl;
    }
}

wil::unique_event CreateTestEvent(const std::wstring& eventName)
{
    bool alreadyExists = false;
    SECURITY_ATTRIBUTES attributes = {};
    wil::unique_hlocal_security_descriptor descriptor;

    // Grant access to world and appcontainer.
    THROW_IF_WIN32_BOOL_FALSE(ConvertStringSecurityDescriptorToSecurityDescriptor(
        L"D:(A;;GA;;;WD)(A;;GA;;;AC)", SDDL_REVISION_1, &descriptor, nullptr));
    attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    attributes.lpSecurityDescriptor = descriptor.get();

    wil::unique_event event;
    event.create(wil::EventOptions::None, eventName.c_str(), &attributes, &alreadyExists);
    return event;
}

bool WaitForEvent(const wil::unique_event& successEvent, const wil::unique_event& failedEvent)
{
    bool result = true;
    HANDLE waitEvents[2] = { successEvent.get(), failedEvent.get() };
    auto waitResult = WaitForMultipleObjects(_countof(waitEvents), waitEvents, FALSE,
        10000);

    // If waitResult == failureEventIndex, it means the remote test process signaled a
    // failure event while we were waiting for a different event.
    auto failureEventIndex = WAIT_OBJECT_0 + 1;
    if (waitResult == failureEventIndex)
    {
        result = false;
    }
    else if (waitResult == WAIT_TIMEOUT)
    {
        result = false;
    }
    else if (waitResult == WAIT_FAILED)
    {
        result = false;
    }

    successEvent.ResetEvent();
    failedEvent.ResetEvent();
    return result;
}


int main()
{
    /*while (true)
    {
        std::string channelUri;
        std::cout << "Insert Channel URI: ";
        std::getline(std::cin, channelUri);
        std::wstring str(channelUri.begin(), channelUri.end());
        SendRequestToServer(str);
    }*/
    std::string channelUri;
    std::cout << "Insert Channel URI: ";
    std::getline(std::cin, channelUri);
    std::wstring str(channelUri.begin(), channelUri.end());
    for (int i = 0; i < 100; i++) {
        Sleep(2000);
        std::wstring successEventName = L"BackgroundActivation";
        std::wstring failedEventName = L"BackgroundActivationFailed";
        wil::unique_event successEvent = CreateTestEvent(successEventName);
        wil::unique_event failedEvent = CreateTestEvent(failedEventName);
        SendRequestToServer(str);

        if (WaitForEvent(successEvent, failedEvent))
        {
            std::wcout << L"Success!" << std::endl;
        }
        else
        {
            std::wcout << L"Failed." << std::endl;
            break;
        }
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
