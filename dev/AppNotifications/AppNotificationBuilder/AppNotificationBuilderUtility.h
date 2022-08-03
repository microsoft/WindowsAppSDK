// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "winrt/Microsoft.Windows.AppNotifications.Builder.h"
#include <algorithm>
#include <regex>
#include <map>

constexpr size_t c_maxAppNotificationPayload{ 5120 };
constexpr uint8_t c_maxTextElements{ 3 };
constexpr uint8_t c_maxButtonElements{ 5 };

namespace AppNotificationBuilder
{
    using namespace winrt::Microsoft::Windows::AppNotifications::Builder;
}

inline std::map<PCWSTR, PCWSTR> GetCharacterEncodings()
{
    static std::map<PCWSTR, PCWSTR> encodings = { { L"%", L"%25"}, {L";", L"%3B"}, {L"=", L"%3D"}};
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

inline std::wstring Encode(std::wstring const& value)
{
    std::wstring encodedValue{ value };

    auto encodings{ GetCharacterEncodings() };
    for (auto encoding : encodings)
    {
        // Replace literal special chars with encoding
        encodedValue = std::regex_replace(encodedValue, std::wregex(encoding.first), encoding.second);
    }

    return encodedValue;
}

// Decoding process based off the Windows Community Toolkit:
// https://github.com/CommunityToolkit/WindowsCommunityToolkit/blob/rel/7.1.0/Microsoft.Toolkit.Uwp.Notifications/Toasts/ToastArguments.cs#L389inline
inline std::wstring Decode(std::wstring const& value)
{
    std::wstring result{ value };

    // Need to unescape special characters
    for (auto encoding : GetCharacterEncodings())
    {
        // Replace encoding with literal special chars
        result = std::regex_replace(result, std::wregex(encoding.second), encoding.first);
    }

    return result;
}
