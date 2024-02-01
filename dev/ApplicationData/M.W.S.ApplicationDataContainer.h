// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Storage.ApplicationDataContainer.g.h"

namespace winrt::Microsoft::Windows::Storage::implementation
{
    struct ApplicationDataContainer : ApplicationDataContainerT<ApplicationDataContainer>
    {
        ApplicationDataContainer() = default;
        ApplicationDataContainer(winrt::Windows::Storage::ApplicationDataContainer const& value);

        winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Microsoft::Windows::Storage::ApplicationDataContainer> Containers();
        hstring Name();
        winrt::Microsoft::Windows::Storage::ApplicationDataLocality Locality();
        winrt::Windows::Foundation::Collections::IPropertySet Values();
        void Close();
        winrt::Microsoft::Windows::Storage::ApplicationDataContainer CreateContainer(hstring const& name, winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition const& disposition);
        void DeleteContainer(hstring const& name);

    private:
        winrt::Windows::Storage::ApplicationDataContainer m_applicationDataContainer;
    };
}
