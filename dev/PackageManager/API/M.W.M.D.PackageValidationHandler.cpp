#include "pch.h"
#include "M.W.M.D.PackageValidationHandler.h"
#include "Microsoft.Windows.Management.Deployment.PackageValidationHandler.g.cpp"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageValidationHandler::PackageValidationHandler(winrt::Microsoft::Windows::Management::Deployment::IPackageValidator const& validator)
    {
        m_validator = validator;
    }

    winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventSource, winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventArgs> PackageValidationHandler::Handler()
    {
        return [this](winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventSource const& sender, winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventArgs const& args)
        {
            auto deferral = args.GetDeferral();

            if (m_validator && !m_validator.IsPackageValid(args.AppxPackagingObject()))
            {
                args.Cancel(true);
            }

            deferral.Complete();
        };
    }
}
