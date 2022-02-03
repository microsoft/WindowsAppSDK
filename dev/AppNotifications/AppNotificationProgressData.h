#pragma once
#include "Microsoft.Windows.AppNotifications.AppNotificationProgressData.g.h"

namespace winrt::Microsoft::Windows::AppNotifications::implementation
{
    struct AppNotificationProgressData : AppNotificationProgressDataT<AppNotificationProgressData>
    {
        AppNotificationProgressData() = default;

        uint32_t SequenceNumber();
        void SequenceNumber(uint32_t value);
        hstring Title();
        void Title(hstring const& value);
        double Value();
        void Value(double value);
        hstring ValueStringOverride();
        void ValueStringOverride(hstring const& value);
        hstring Status();
        void Status(hstring const& value);
    };
}
namespace winrt::Microsoft::Windows::AppNotifications::factory_implementation
{
    struct AppNotificationProgressData : AppNotificationProgressDataT<AppNotificationProgressData, implementation::AppNotificationProgressData>
    {
    };
}
