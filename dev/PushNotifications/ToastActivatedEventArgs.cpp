#include "pch.h"
#include "ToastActivatedEventArgs.h"
#include "Microsoft.Windows.ToastNotifications.ToastActivatedEventArgs.g.cpp"


namespace winrt::Microsoft::Windows::ToastNotifications::implementation
{
    hstring ToastActivatedEventArgs::ActivationArgs()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IMapView<hstring, hstring> ToastActivatedEventArgs::UserInput()
    {
        throw hresult_not_implemented();
    }
}
