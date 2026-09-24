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

// Optimizing string encoding by replacing unordered_map with a switch statement.
// This avoids hashing overhead and potential heap allocations.
inline PCWSTR GetXmlEscapeEncoding(wchar_t ch)
{
    switch (ch)
    {
    case L'&': return L"&amp;";
    case L'\"': return L"&quot;";
    case L'<': return L"&lt;";
    case L'>': return L"&gt;";
    case L'\'': return L"&apos;";
    default: return nullptr;
    }
}

// Optimizing string encoding by replacing unordered_map with a switch statement.
// This avoids hashing overhead and potential heap allocations.
inline PCWSTR GetPercentEncoding(wchar_t ch)
{
    switch (ch)
    {
    case L'%': return L"%25";
    case L';': return L"%3B";
    case L'=': return L"%3D";
    default: return nullptr;
    }
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
    encodedValue.reserve(value.size());

    for (auto ch : value)
    {
        auto percentEncoding{ GetPercentEncoding(ch) };
        if (percentEncoding)
        {
            encodedValue.append(percentEncoding);
        }
        else
        {
            auto xmlEncoding{ GetXmlEscapeEncoding(ch) };
            if (xmlEncoding)
            {
                encodedValue.append(xmlEncoding);
            }
            else
            {
                encodedValue.push_back(ch);
            }
        }
    }

    return encodedValue;
}

inline std::wstring EncodeXml(winrt::hstring const& value)
{
    std::wstring encodedValue{};
    encodedValue.reserve(value.size());

    for (auto ch : value)
    {
        auto xmlEncoding{ GetXmlEscapeEncoding(ch) };
        if (xmlEncoding)
        {
            encodedValue.append(xmlEncoding);
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
// Optimized to avoid temporary string allocations from substr() and map lookups.
inline std::wstring Decode(std::wstring const& value)
{
    std::wstring result{};
    result.reserve(value.size());

    // Need to unescape special characters
    for (size_t index = 0; index < value.size();)
    {
        if (value[index] == L'%' && index + 2 < value.size())
        {
            if (value[index + 1] == L'2' && value[index + 2] == L'5')
            {
                result.push_back(L'%');
                index += 3;
                continue;
            }
            else if (value[index + 1] == L'3' && value[index + 2] == L'B')
            {
                result.push_back(L';');
                index += 3;
                continue;
            }
            else if (value[index + 1] == L'3' && value[index + 2] == L'D')
            {
                result.push_back(L'=');
                index += 3;
                continue;
            }
        }

        result.push_back(value.at(index));
        index++;
    }
    return result;
}
