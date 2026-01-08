#pragma once

#include <winrt/base.h>
#include <wil/com.h>
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
