// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "AppNotificationActivatedEventArgs.h"
#include "Microsoft.Windows.AppNotifications.AppNotificationActivatedEventArgs.g.cpp"
#include "AppNotificationBuilder/AppNotificationBuilderUtility.h"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    winrt::Windows::Foundation::Collections::IMap<hstring, hstring> AppNotificationActivatedEventArgs::DecodeArguments(std::wstring arguments)
    {
        auto result{ winrt::single_threaded_map<winrt::hstring, winrt::hstring>() };

        std::vector<std::wstring> pairs{};

        wchar_t delimiter{ L';'};
        LPWSTR context{};
        auto token{ wcstok_s(arguments.data(), &delimiter, &context) };
        // Separate the key/value pairs by ';' as the delimiter
        while (token != nullptr)
        {
            pairs.push_back(token);
            token = wcstok_s(nullptr, &delimiter, &context);
        }

        for (auto pair : pairs)
        {
            // Get the key/value individual values separated by '='
            size_t pos{ pair.find(L'=') };
            if (pos == std::wstring::npos)
            {
                result.Insert(Decode(pair), L"");
            }
            else
            {
                result.Insert(Decode(pair.substr(0, pos)), Decode(pair.substr(pos + 1)));
            }
        }
        return result;
    }
}
