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

bool g_quit = false;
std::wstring g_channelUri = L"";
std::wstring g_payload = L"";

void cleanInputBuffer()
{
    std::string trash;
    std::getline(std::cin, trash, '\n');
}

std::wstring BuildNotificationPayload(bool isToast)
{
    std::wstring x_wns_type = isToast ? L"\"wns/toast\"" : L"\"wns/raw\"";
    std::wstring contentType = isToast ? L"\"text/xml\"" : L"\"application/octet-stream\"";
    if (g_channelUri.empty())
    {
        std::cout << "Please set the channel uri before sending notification." << std::endl << std::endl;
        return L"";
    }
    else if (g_channelUri.empty())
    {
        std::cout << "Please set the payload before sending notification." << std::endl << std::endl;
        return L"";
    }
    
    std::wstring channelUri = L"\"ChannelUri\":\"" + g_channelUri + L"\"";
    std::wstring x_wns_typeJson = L"\"X_WNS_Type\": " + x_wns_type;
    std::wstring contentTypeJson = L"\"Content_Type\": " + contentType;
    std::wstring payload = L"\"Payload\": \"" + g_payload + L"\"";
    std::wstring delay = L"\"Delay\": \"false\"";
    return { L"{" + channelUri + L"," + x_wns_typeJson + L"," + contentTypeJson + L"," + payload + L"," + delay + L"}" };
}

void SendPushNotification(bool isToast) {
    cleanInputBuffer();
    HttpResponseMessage httpResponseMessage;
    std::wstring httpResponseBody;
    std::wstring notificationPayload = BuildNotificationPayload(isToast);
    if (notificationPayload.empty())
    {
        return;
    }

    try {
        // Construct the HttpClient and Uri. This endpoint is for test purposes only.
        HttpClient httpClient;
        Uri requestUri{ L"http://localhost:7071/api/PostPushNotification" };

        // Construct the JSON to post.
        HttpStringContent jsonContent(
            notificationPayload,
            UnicodeEncoding::Utf8,
            L"application/json");

        // Post the JSON, and wait for a response.
        httpResponseMessage = httpClient.PostAsync(
            requestUri,
            jsonContent).get();

        // Make sure the post succeeded, and write out the response.
        httpResponseMessage.EnsureSuccessStatusCode();
        httpResponseBody = httpResponseMessage.Content().ReadAsStringAsync().get();
        std::wcout << httpResponseBody.c_str() << std::endl << std::endl;
    }
    catch (winrt::hresult_error const& ex)
    {
        std::wcout << ex.message().c_str() << std::endl << std::endl;
    }
}

int menuSelect()
{
    std::cout << "Select action to perform: " << std::endl;
    std::cout << "(1) Set Channel URI" << std::endl;
    std::cout << "(2) Set Payload" << std::endl;
    std::cout << "(3) Send raw notification" << std::endl;
    std::cout << "(4) Send Toast" << std::endl;
    std::cout << "(5) Quit" << std::endl << std::endl;
    std::cout << "Choice: ";
    char choice = std::getchar();
    return choice;
}

void SetChannelUri()
{
    cleanInputBuffer();
    std::string channelUri;
    std::cout << "Insert Channel URI: ";
    std::getline(std::cin, channelUri, '\n');
    std::wstring str(channelUri.begin(), channelUri.end());
    g_channelUri = str;
    std::cout << std::endl;
}

void SetPayload()
{
    cleanInputBuffer();
    std::string payload;
    std::cout << "Insert Payload: ";
    std::getline(std::cin, payload, '\n');
    std::wstring str(payload.begin(), payload.end());
    g_payload = str;
    std::cout << std::endl;
}

int main()
{
    std::cout << "Project Reunion Push Notification App" << std::endl << std::endl;
    while (!g_quit)
    {
        char choice = menuSelect();
        std::cout << std::endl;

        switch (choice) {
            case '1':
                SetChannelUri();
                break;
            case '2':
                SetPayload();
                break;
            case '3':
                SendPushNotification(false);
                break;
            case '4':
                SendPushNotification(true);
                break;
            case '5':
                g_quit = true;
                break;
            default:
                std::cout << "Invalid input." << std::endl << std::endl;
                cleanInputBuffer();
        }
    }
    return 0;
}
