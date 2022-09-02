// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "winrt/Microsoft.Windows.AppNotifications.Builder.h"
#include <algorithm>
#include <regex>
#include <map>
#include <iostream>

constexpr size_t c_maxAppNotificationPayload{ 5120 };
constexpr uint8_t c_maxTextElements{ 3 };
constexpr uint8_t c_maxButtonElements{ 5 };
constexpr size_t c_maxEncodingSize{ 3 };
constexpr uint8_t c_maxTextInputElements{ 5 };
constexpr uint8_t c_maxSelectionElements{ 5 };
constexpr uint8_t c_offsetIndexValue{ 2 };

namespace AppNotificationBuilder
{
    using namespace winrt::Microsoft::Windows::AppNotifications::Builder;
}

inline std::unordered_map<wchar_t, std::wstring> GetXmlEscapeEncodings()
{
    static std::unordered_map<wchar_t, std::wstring> encodings = { { L'&', L"&amp;"}, { L'\"', L"&quot;"}, {L'<', L"&lt;"}, {L'>', L"&gt;"}, {L'\'', L"&apos;"}};
    return encodings;
}

inline std::unordered_map<wchar_t, std::wstring> GetPercentEncodings()
{
    static std::unordered_map<wchar_t, std::wstring> encodings = {{ L'%', L"%25"}, {L';', L"%3B"}, {L'=', L"%3D"} };
    return encodings;
}

inline std::unordered_map<std::wstring, wchar_t> GetPercentEncodingsReverse()
{
    static std::unordered_map<std::wstring, wchar_t> encodings = { { L"%25", L'%' }, {L"%3B", L';' }, { L"%3D", L'=' } };
    return encodings;
}

inline PCWSTR GetWinSoundEventString(AppNotificationBuilder::AppNotificationSoundEvent soundEvent)
{
    switch (soundEvent)
    {
    case AppNotificationBuilder::AppNotificationSoundEvent::IM:
        return L"ms-winsoundevent:Notification.IM";
    case AppNotificationBuilder::AppNotificationSoundEvent::Mail:
        return L"ms-winsoundevent:Notification.Mail";
    case AppNotificationBuilder::AppNotificationSoundEvent::Reminder:
        return L"ms-winsoundevent:Notification.Reminder";
    case AppNotificationBuilder::AppNotificationSoundEvent::SMS:
        return L"ms-winsoundevent:Notification.SMS";
    case AppNotificationBuilder::AppNotificationSoundEvent::Alarm:
        return L"ms-winsoundevent:Notification.Looping.Alarm";
    case AppNotificationBuilder::AppNotificationSoundEvent::Alarm2:
        return L"ms-winsoundevent:Notification.Looping.Alarm2";
    case AppNotificationBuilder::AppNotificationSoundEvent::Alarm3:
        return L"ms-winsoundevent:Notification.Looping.Alarm3";
    case AppNotificationBuilder::AppNotificationSoundEvent::Alarm4:
        return L"ms-winsoundevent:Notification.Looping.Alarm4";
    case AppNotificationBuilder::AppNotificationSoundEvent::Alarm5:
        return L"ms-winsoundevent:Notification.Looping.Alarm5";
    case AppNotificationBuilder::AppNotificationSoundEvent::Alarm6:
        return L"ms-winsoundevent:Notification.Looping.Alarm6";
    case AppNotificationBuilder::AppNotificationSoundEvent::Alarm7:
        return L"ms-winsoundevent:Notification.Looping.Alarm7";
    case AppNotificationBuilder::AppNotificationSoundEvent::Alarm8:
        return L"ms-winsoundevent:Notification.Looping.Alarm8";
    case AppNotificationBuilder::AppNotificationSoundEvent::Alarm9:
        return L"ms-winsoundevent:Notification.Looping.Alarm9";
    case AppNotificationBuilder::AppNotificationSoundEvent::Alarm10:
        return L"ms-winsoundevent:Notification.Looping.Alarm10";
    case AppNotificationBuilder::AppNotificationSoundEvent::Call:
        return L"ms-winsoundevent:Notification.Looping.Call";
    case AppNotificationBuilder::AppNotificationSoundEvent::Call2:
        return L"ms-winsoundevent:Notification.Looping.Call2";
    case AppNotificationBuilder::AppNotificationSoundEvent::Call3:
        return L"ms-winsoundevent:Notification.Looping.Call3";
    case AppNotificationBuilder::AppNotificationSoundEvent::Call4:
        return L"ms-winsoundevent:Notification.Looping.Call4";
    case AppNotificationBuilder::AppNotificationSoundEvent::Call5:
        return L"ms-winsoundevent:Notification.Looping.Call5";
    case AppNotificationBuilder::AppNotificationSoundEvent::Call6:
        return L"ms-winsoundevent:Notification.Looping.Call6";
    case AppNotificationBuilder::AppNotificationSoundEvent::Call7:
        return L"ms-winsoundevent:Notification.Looping.Call7";
    case AppNotificationBuilder::AppNotificationSoundEvent::Call8:
        return L"ms-winsoundevent:Notification.Looping.Call8";
    case AppNotificationBuilder::AppNotificationSoundEvent::Call9:
        return L"ms-winsoundevent:Notification.Looping.Call9";
    case AppNotificationBuilder::AppNotificationSoundEvent::Call10:
        return L"ms-winsoundevent:Notification.Looping.Call10";
    default:
        return L"ms-winsoundevent:Notification.Default";
    }
}

inline std::wstring EncodeArgument(std::wstring const& value)
{
    std::wstring encodedValue{};

    auto percentEncodings{ GetPercentEncodings() };
    auto xmlEncodings{ GetXmlEscapeEncodings() };
    for (auto ch : value)
    {
        if (percentEncodings.find(ch) != percentEncodings.end())
        {
            encodedValue.append(percentEncodings[ch]);
        }
        else if (xmlEncodings.find(ch) != xmlEncodings.end())
        {
            encodedValue.append(xmlEncodings[ch]);
        }
        else
        {
            encodedValue.push_back(ch);
        }
    }

    return encodedValue;
}

inline std::wstring EncodeXml(winrt::hstring const& value)
{
    std::wstring encodedValue{};

    auto xmlEncodings{ GetXmlEscapeEncodings() };
    for (auto ch : value)
    {
        if (xmlEncodings.find(ch) != xmlEncodings.end())
        {
            encodedValue.append(xmlEncodings[ch]);
        }
        else
        {
            encodedValue.push_back(ch);
        }
    }

    return encodedValue;
}

// Decoding process based off the Windows Community Toolkit:
// https://github.com/CommunityToolkit/WindowsCommunityToolkit/blob/rel/7.1.0/Microsoft.Toolkit.Uwp.Notifications/Toasts/ToastArguments.cs#L389inline
inline std::wstring Decode(std::wstring const& value)
{
    std::wstring result{};
    auto percentEncodings{ GetPercentEncodingsReverse() };

    // Need to unescape special characters
    for (size_t index = 0; index < value.size();)
    {
        std::wstring curr{ value.substr(index, c_maxEncodingSize) };
        if (percentEncodings.find(curr) != percentEncodings.end())
        {
            result.push_back(percentEncodings[curr]);
            index += c_maxEncodingSize;
        }
        else
        {
            result.push_back(value.at(index));
            index++;
        }
    }
    return result;
}
