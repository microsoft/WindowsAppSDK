// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.AppNotifications.AppNotificationProgressData.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    struct AppNotificationProgressData : AppNotificationProgressDataT<AppNotificationProgressData>
    {
        AppNotificationProgressData() = default;
        AppNotificationProgressData(uint32_t sequenceNumber);
        uint32_t SequenceNumber();
        void SequenceNumber(uint32_t sequenceNumber);
        hstring Title();
        void Title(hstring const& title);
        double Value();
        void Value(double progressValue);
        hstring ValueStringOverride();
        void ValueStringOverride(hstring const& progressValueString);
        hstring Status();
        void Status(hstring const& progressStatus);

    private:
        uint32_t m_sequenceNumber = 1;
        hstring m_title;
        double m_progressValue{};
        hstring m_progressValueString;
        hstring m_progressStatus;
        wil::srwlock m_lock;
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::factory_implementation
{
    struct AppNotificationProgressData : AppNotificationProgressDataT<AppNotificationProgressData, implementation::AppNotificationProgressData>
    {
    };
}
