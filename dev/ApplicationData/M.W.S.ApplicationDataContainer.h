// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Storage.ApplicationDataContainer.g.h"

namespace winrt::Microsoft::Windows::Storage::implementation
{
    struct ApplicationDataContainer : ApplicationDataContainerT<ApplicationDataContainer>
    {
        ApplicationDataContainer() = default;

        winrt::Windows::Foundation::Collections::IMapView<hstring, winrt::Microsoft::Windows::Storage::ApplicationDataContainer> Containers();
        hstring Name();
        winrt::Microsoft::Windows::Storage::ApplicationDataLocality Locality();
        winrt::Windows::Foundation::Collections::PropertySet Values();
        void Close();
        void Dispose();
        winrt::Microsoft::Windows::Storage::ApplicationDataContainer CreateContainer(hstring const& name, winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition const& disposition);
        void DeleteContainer(hstring const& name);
    };
}
