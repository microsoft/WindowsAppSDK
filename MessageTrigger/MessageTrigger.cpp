// MessageTrigger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <sstream>
#include <winrt/Windows.Networking.PushNotifications.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Web.Http.Headers.h>

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
    std::wstring payload = L"\"Payload\": \"Hello World! Another foreground payload coming :v\"";
    std::wstring delay = L"\"Delay\": \"false\"";
    return { L"{" + channelUri + L"," + x_wns_type + L"," + contentType + L"," + payload + L"," + delay + L"}" };
}

int main()
{
    HttpResponseMessage httpResponseMessage;
    std::wstring httpResponseBody;
    try {
        // Construct the HttpClient and Uri. This endpoint is for test purposes only.
        HttpClient httpClient;
        Uri requestUri{ L"http://localhost:7071/api/PostPushNotification" };

        // Construct the JSON to post.
        HttpStringContent jsonContent(
            BuildNotificationPayload(L"https://dm3p.notify.windows.com/?token=AwYAAAC2%2bcbmsAWE5U3NNU%2b0USmGxdffpX8UYw9pBzAp3XEY%2bhLsijzZK8VcYPAr%2f78m8OB%2btDQEqZ50h%2bfuyYCHRnaX%2fs%2bvmrlfQyHAKMeHL66MRTvL8x0oo4WFlkVz%2bzMJKW9EA7UNfeccHuSP2GDQXcOT"),
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
