#include "pch.h"
#include "Microsoft.Windows.Management.Deployment.PackageValidationEventSource.g.cpp"

#include "AppxPackaging.h"
#include "AppxPackagingObject.h"
#include "M.W.M.D.PackageValidationEventSource.h"

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    bool PackageValidationEventSource::Run(winrt::Windows::Foundation::Uri const& packageUri, winrt::Windows::Foundation::Collections::IMap<winrt::Windows::Foundation::Uri, hstring>& expectedDigests)
    {
        auto packageUriString{ packageUri.AbsoluteCanonicalUri().c_str() };
        auto expectedDigest{ expectedDigests.TryLookup(packageUri) };
        auto expectedDigestString{ expectedDigest.has_value() ? expectedDigest.value().c_str() : nullptr };

        auto appxFactory{ wil::CoCreateInstance<AppxFactory, IAppxFactory4, wil::err_exception_policy>() };
        auto bundleFactory{ wil::CoCreateInstance<AppxBundleFactory, IAppxBundleFactory3, wil::err_exception_policy>() };

        IInspectable appxObject{};
        winrt::com_ptr<IAppxPackageReader> packageReader{};
        winrt::com_ptr<IAppxBundleReader> bundleReader{};
        winrt::com_ptr<IAppxDigestProvider> digestProvider{};

        if (SUCCEEDED(appxFactory->CreatePackageReaderFromSourceUri(packageUriString, expectedDigestString, packageReader.put())))
        {
            appxObject = winrt::make<AppxPackagingObject>(packageReader.get()).as<IInspectable>();
            digestProvider = packageReader.as<IAppxDigestProvider>();
        }
        else if (SUCCEEDED(bundleFactory->CreateBundleReaderFromSourceUri(packageUriString, expectedDigestString, bundleReader.put())))
        {
            appxObject = winrt::make<AppxPackagingObject>(bundleReader.get()).as<IInspectable>();
            digestProvider = bundleReader.as<IAppxDigestProvider>();
        }
        else
        {
            THROW_WIN32(ERROR_INSTALL_OPEN_PACKAGE_FAILED);
        }

        auto args{ winrt::make<PackageValidationEventArgs>(packageUri, appxObject) };
        m_validationRequested(*this, args);
        args.as<PackageValidationEventArgs>()->wait_for_deferrals().get();

        if (args.Cancel())
        {
            return false;
        }
        else
        {
            if (!expectedDigestString)
            {
                wil::unique_cotaskmem_string digest;
                THROW_IF_FAILED(digestProvider->GetDigest(&digest));

                expectedDigests.Insert(packageUri, digest.get());
            }
            return true;
        }
    }

    winrt::event_token PackageValidationEventSource::ValidationRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventSource, winrt::Microsoft::Windows::Management::Deployment::PackageValidationEventArgs> const& handler)
    {
        return m_validationRequested.add(handler);
    }

    void PackageValidationEventSource::ValidationRequested(winrt::event_token const& token) noexcept
    {
        m_validationRequested.remove(token);
    }
}
