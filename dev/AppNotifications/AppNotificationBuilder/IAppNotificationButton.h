#pragma once
#include "pch.h"

namespace winrt::Microsoft::Windows::AppNotifications::Builder::implementation
{
    MIDL_INTERFACE("4A6CB5C0-6169-4CF7-9577-7C1BD8BC4974") IAppNotificationButton : IInspectable
    {
        virtual AppNotificationButtonStyle GetButtonStyle() = 0;
    };
}
