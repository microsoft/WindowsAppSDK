// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "M.W.S.ApplicationDataContainer.h"
#include "Microsoft.Windows.Storage.ApplicationDataContainer.g.cpp"

#include "UnpackagedApplicationDataContainer.h"

namespace winrt::Microsoft::Windows::Storage::implementation
{
    ApplicationDataContainer::ApplicationDataContainer(winrt::Windows::Storage::ApplicationDataContainer const& value) :
        m_applicationDataContainer(value)
    {
    }
    ApplicationDataContainer::ApplicationDataContainer(std::shared_ptr<::Microsoft::Windows::Storage::UnpackagedApplicationDataContainer> const& value) :
        m_unpackagedApplicationDataContainer(value),
        m_applicationDataContainer(nullptr)
    {
    }
    winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Microsoft::Windows::Storage::ApplicationDataContainer> ApplicationDataContainer::Containers()
    {
        if (m_unpackagedApplicationDataContainer)
        {
            return m_unpackagedApplicationDataContainer->Containers();
        }

        winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Microsoft::Windows::Storage::ApplicationDataContainer> map{ winrt::single_threaded_map<winrt::hstring, winrt::Microsoft::Windows::Storage::ApplicationDataContainer>() };
        auto containers{ m_applicationDataContainer.Containers() };
        for (auto container : containers)
        {
            auto value{ winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationDataContainer>(container.Value()) };
            map.Insert(container.Key(), value);
        }
        return map;
    }
    hstring ApplicationDataContainer::Name()
    {
        if (m_unpackagedApplicationDataContainer)
        {
            return m_unpackagedApplicationDataContainer->Name();
        }

        return m_applicationDataContainer.Name();
    }
    winrt::Microsoft::Windows::Storage::ApplicationDataLocality ApplicationDataContainer::Locality()
    {
        if (m_unpackagedApplicationDataContainer)
        {
            return m_unpackagedApplicationDataContainer->Locality();
        }

        static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Local) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::Local));
        static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::LocalCache) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::LocalCache));
        static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataLocality::Temporary) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataLocality::Temporary));

        return static_cast<winrt::Microsoft::Windows::Storage::ApplicationDataLocality>(m_applicationDataContainer.Locality());
    }
    winrt::Windows::Foundation::Collections::IPropertySet ApplicationDataContainer::Values()
    {
        if (m_unpackagedApplicationDataContainer)
        {
            return m_unpackagedApplicationDataContainer->Values();
        }

        return m_applicationDataContainer.Values();
    }
    void ApplicationDataContainer::Close()
    {
        if (m_unpackagedApplicationDataContainer)
        {
            return m_unpackagedApplicationDataContainer->Close();
        }

        return m_applicationDataContainer.Close();
    }
    winrt::Microsoft::Windows::Storage::ApplicationDataContainer ApplicationDataContainer::CreateContainer(hstring const& name, winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition const& disposition)
    {
        if (m_unpackagedApplicationDataContainer)
        {
            return m_unpackagedApplicationDataContainer->CreateContainer(name, disposition);
        }

        static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition::Always) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataCreateDisposition::Always));
        static_assert(static_cast<int32_t>(winrt::Microsoft::Windows::Storage::ApplicationDataCreateDisposition::Existing) == static_cast<int32_t>(winrt::Windows::Storage::ApplicationDataCreateDisposition::Existing));

        auto container{ m_applicationDataContainer.CreateContainer(name, static_cast<winrt::Windows::Storage::ApplicationDataCreateDisposition>(disposition)) };
        return winrt::make<winrt::Microsoft::Windows::Storage::implementation::ApplicationDataContainer>(container);
    }
    void ApplicationDataContainer::DeleteContainer(hstring const& name)
    {
        if (m_unpackagedApplicationDataContainer)
        {
            return m_unpackagedApplicationDataContainer->DeleteContainer(name);
        }

        m_applicationDataContainer.DeleteContainer(name);
    }
}
