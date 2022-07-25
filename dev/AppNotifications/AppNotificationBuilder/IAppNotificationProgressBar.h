#pragma once
#include "pch.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    MIDL_INTERFACE("EACE42A5-F247-47E0-9A97-071C236C2F4d") IAppNotificationProgressBar : IInspectable
    {
        virtual hstring GetTitle() = 0;
        virtual hstring GetStatus() = 0;
        virtual double GetValue() = 0;
        virtual hstring GetValueStringOverride() = 0;
    };
}
