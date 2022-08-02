// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "winrt/Microsoft.Windows.AppNotifications.Builder.h"
#include <algorithm>

constexpr size_t c_maxAppNotificationPayload{ 5120 };
constexpr uint8_t c_maxTextElements{ 3 };
constexpr uint8_t c_maxButtonElements{ 5 };
constexpr PCWSTR c_encodedPercent{ L"%25" };
constexpr PCWSTR c_encodedSemicolon{ L"%3B" };
constexpr PCWSTR c_encodedEquals{ L"%3D" };

namespace AppNotificationBuilder
{
    using namespace winrt::Microsoft::Windows::AppNotifications::Builder;
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

inline std::wstring Encode(winrt::hstring const& value)
{
    std::wstring encodedValue{};
    for (auto ch : value)
    {
        switch (ch) {
        case '%':
            encodedValue.append(c_encodedPercent);
            break;
        case ';':
            encodedValue.append(c_encodedSemicolon);
            break;
        case '=':
            encodedValue.append(c_encodedEquals);
            break;
        default:
            encodedValue.push_back(ch);
        }
    }
    return encodedValue;
}

// This function replaces the encoded values with the actual values
inline std::wstring DecodeString(std::wstring value, std::wstring const& encodedValue, char ch)
{
    std::wstring result{};
    size_t pos{};
    while ((pos = value.find(encodedValue)) != std::wstring::npos)
    {
        result.append(value.substr(0, pos));
        result.push_back(ch);
        value.erase(0, pos + encodedValue.size());
    }
    result.append(value);

    return result;
}

// Decoding process based off the Windows Community Toolkit:
// https://github.com/CommunityToolkit/WindowsCommunityToolkit/blob/rel/7.1.0/Microsoft.Toolkit.Uwp.Notifications/Toasts/ToastArguments.cs#L389inline
inline std::wstring Decode(std::wstring const& value)
{
    std::wstring result{ value };

    // Need to unescape special characters
    result = DecodeString(result, c_encodedPercent, L'%');
    result = DecodeString(result, c_encodedSemicolon, L';');
    result = DecodeString(result, c_encodedEquals, L'=');

    return result;
}
