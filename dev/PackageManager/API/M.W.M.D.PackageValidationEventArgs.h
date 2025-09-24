#pragma once
#include "Microsoft.Windows.Management.Deployment.PackageValidationEventArgs.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageValidationEventArgs : PackageValidationEventArgsT<PackageValidationEventArgs>, winrt::deferrable_event_args<PackageValidationEventArgs>
    {
    public:
        PackageValidationEventArgs(winrt::Windows::Foundation::Uri const& packageUri, winrt::Windows::Foundation::IInspectable const& appxObject);

        winrt::Windows::Foundation::Uri PackageUri();
        winrt::Windows::Foundation::IInspectable AppxPackagingObject();

        bool Cancel();
        void Cancel(bool value);

    private:
        winrt::Windows::Foundation::Uri m_packageUri{ nullptr };
        winrt::Windows::Foundation::IInspectable m_appxObject{};
        bool m_cancel{};
    };
}
