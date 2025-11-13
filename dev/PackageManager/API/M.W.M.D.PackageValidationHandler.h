#pragma once
#include "Microsoft.Windows.Management.Deployment.PackageValidationHandler.g.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct PackageValidationHandler : PackageValidationHandlerT<PackageValidationHandler>
    {
        PackageValidationHandler(winrt::Microsoft::Windows::Management::Deployment::IPackageValidator const& validator);

        winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventSource, winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventArgs> Handler();

    private:
        winrt::Microsoft::Windows::Management::Deployment::IPackageValidator m_validator{ nullptr };
    };
}
namespace winrt::Microsoft::Windows::Management::Deployment::factory_implementation
{
    struct PackageValidationHandler : PackageValidationHandlerT<PackageValidationHandler, implementation::PackageValidationHandler>
    {
    };
}
