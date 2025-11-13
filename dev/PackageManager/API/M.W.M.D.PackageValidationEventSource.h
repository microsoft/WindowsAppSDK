#pragma once
#include "Microsoft.Windows.Management.Deployment.PackageValidationEventSource.g.h"

#include "M.W.M.D.PackageValidationEventArgs.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageValidationEventSource : PackageValidationEventSourceT<PackageValidationEventSource>
    {
    public:
        PackageValidationEventSource() = default;

        bool Run(winrt::Windows::Foundation::Uri const& packageUri, winrt::Windows::Foundation::Collections::IMap<winrt::Windows::Foundation::Uri, hstring>& expectedDigests);

        winrt::event_token ValidationRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventSource, winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventArgs> const& handler);
        void ValidationRequested(winrt::event_token const& token) noexcept;

    private:
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventSource, winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventArgs>> m_validationRequested{};
    };
}
