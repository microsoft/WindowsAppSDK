// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "externs.h"
#include "AppNotificationFactory.h"
#include "AppNotificationBuilderTelemetry.h"
#include <winrt/Windows.Globalization.h>
#include <winrt/Windows.Globalization.DateTimeFormatting.h>
#include "Microsoft.Windows.AppNotifications.Builder.AppNotificationFactory.g.cpp"
#include "AppNotificationBuilderUtility.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include <IsWindowsVersion.h>

using namespace winrt::Windows::Globalization;
using namespace winrt::Windows::Globalization::DateTimeFormatting;

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationFactory::MakeSnoozeButton(winrt::hstring const& id)
    {
        auto snoozeButton{ winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton(L"") };
        snoozeButton.ButtonType(AppNotificationButtonType::Snooze);
        snoozeButton.InputId(id);

        return snoozeButton;
    }

    winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton AppNotificationFactory::MakeDismissButton()
    {
        auto dismissButton{ winrt::Microsoft::Windows::AppNotifications::Builder::AppNotificationButton(L"") };
        dismissButton.ButtonType(AppNotificationButtonType::Dismiss);

        return dismissButton;
    }
}
