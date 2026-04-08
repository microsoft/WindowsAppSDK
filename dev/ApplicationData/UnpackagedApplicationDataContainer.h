// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "M.W.S.ApplicationDataContainer.h"

namespace Microsoft::Windows::Storage
{
    struct UnpackagedApplicationDataContainer
    {
        UnpackagedApplicationDataContainer() = default;
        UnpackagedApplicationDataContainer(wil::shared_hkey key, winrt::hstring const& name, winrt::Microsoft::Windows::Storage::ApplicationDataLocality locality);

        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::Microsoft::Windows::Storage::ApplicationDataContainer> Containers();
        winrt::hstring Name();
        winrt::Microsoft::Windows::Storage::ApplicationDataLocality Locality();
        winrt::Windows::Foundation::Collections::IPropertySet Values();
        void Close();
        winrt::Microsoft::Windows::Storage::ApplicationDataContainer CreateContainer(winrt::hstring const& name, winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition const& disposition);
        void DeleteContainer(winrt::hstring const& name);

    private:
        void _VerifyNotClosed();
        void _VerifyContainerName(winrt::hstring const& name);

    private:
        wil::shared_hkey m_key;
        winrt::hstring m_name;
        winrt::Microsoft::Windows::Storage::ApplicationDataLocality m_locality{};
    };
}
