// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.S.ApplicationDataContainer.h"
#include "Microsoft.Windows.Storage.ApplicationDataContainer.g.cpp"

namespace winrt::Microsoft::Windows::Storage::implementation
{
    winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Microsoft::Windows::Storage::ApplicationDataContainer> ApplicationDataContainer::Containers()
    {
        throw hresult_not_implemented();
    }
    hstring ApplicationDataContainer::Name()
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::Storage::ApplicationDataLocality ApplicationDataContainer::Locality()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::PropertySet ApplicationDataContainer::Values()
    {
        throw hresult_not_implemented();
    }
    void ApplicationDataContainer::Close()
    {
        throw hresult_not_implemented();
    }
    void ApplicationDataContainer::Dispose()
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::Storage::ApplicationDataContainer ApplicationDataContainer::CreateContainer(hstring const& name, winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition const& disposition)
    {
        throw hresult_not_implemented();
    }
    void ApplicationDataContainer::DeleteContainer(hstring const& name)
    {
        throw hresult_not_implemented();
    }
}
