// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __MICROSOFT_ROAPI_H
#define __MICROSOFT_ROAPI_H

#include <roapi.h>
#include <wrl.h>
#include <wil/resource.h>

namespace Microsoft::RoApi
{
    // WinAppSDK Components that activate a class registered via windows.activatableClass.proxyStub
    // in manifest should call this function before due to a RoActivateInstance caching bug.
    inline void ClearRoActivateInstanceCache()
    {
        // Activating a nonexistent class clears the cache enables the proxyStub to be found for elevated scenarios
        auto activatableClass{ wil::make_unique_string_nothrow<wil::unique_hstring>(L"FakeClass.ClassName") };
        winrt::com_ptr<::IInspectable> ptr{};

        // Function is expected fail and if anything else happens we should throw.
        winrt::hresult hr{ RoActivateInstance(activatableClass.get(), ptr.put()) };
        THROW_HR_IF_MSG(E_FAIL, hr == S_OK, "Cache fix failed: Found class name FakeClass.ClassName");
        THROW_HR_IF(hr, hr != REGDB_E_CLASSNOTREG);
    }
}

#endif // __MICROSOFT_ROAPI_H
