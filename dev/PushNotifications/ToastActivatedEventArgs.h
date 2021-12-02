#pragma once
#include "Microsoft.Windows.ToastNotifications.ToastActivatedEventArgs.g.h"

namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    struct ToastActivatedEventArgs : ToastActivatedEventArgsT<ToastActivatedEventArgs>
    {
        ToastActivatedEventArgs() = default;

        hstring ActivationArgs();
        winrt::Windows::Foundation::Collections::IMapView<hstring, hstring> UserInput();
    };
}
