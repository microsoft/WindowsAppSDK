// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <pch.h>
#include <AppxPackaging.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    struct AppxPackagingObject : winrt::implements<AppxPackagingObject, IInspectable>
    {
        AppxPackagingObject(IUnknown* object)
        {
            m_object.copy_from(object);
        }

        int32_t query_interface_tearoff(winrt::guid const& id, void** object) const noexcept override
        {
            return m_object.as(id, object);
        }

    private:
        winrt::com_ptr<IUnknown> m_object;
    };
}

namespace WindowsVersion
{
    inline bool SupportsIAppxFactory4()
    {
        return wil::CoCreateInstanceNoThrow<AppxFactory, IAppxFactory4>().get() != nullptr;
    }
}
