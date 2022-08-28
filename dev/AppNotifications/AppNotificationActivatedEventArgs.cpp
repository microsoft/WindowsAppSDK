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
        size_t pos{ 0 };

        // Separate the key/value pairs by ';' as the delimiter
        while ((pos = arguments.find(L';')) != std::wstring::npos)
        {
            pairs.push_back(arguments.substr(0, pos));
            arguments.erase(0, pos + 1);
        }

        // Need to push back final string
        pairs.push_back(arguments);

        for (auto pair : pairs)
        {
            // Get the key/value individual values separated by '='
            pos = pair.find(L'=');
            if (pos == std::wstring::npos)
            {
                result.Insert(Decode(pair).c_str(), L"");
            }
            else
            {
                result.Insert(Decode(pair.substr(0, pos)).c_str(), Decode(pair.substr(pos + 1)).c_str());
            }
        }
        return result;
    }
}
