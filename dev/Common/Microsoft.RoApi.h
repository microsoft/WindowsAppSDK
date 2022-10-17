// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __MICROSOFT_ROAPI_H
#define __MICROSOFT_ROAPI_H

namespace Microsoft::RoApi
{
    inline void ClearRoActivateInstanceCache()
    {
        // Activating a nonexistent class clears the cache enables the proxyStub to be found for elevated scenarios
        auto activatableClass{ wil::make_unique_string_nothrow<wil::unique_hstring>(L"FakeClass.ClassName") };
        winrt::com_ptr<::IInspectable> ptr{};

        // Function is expected fail and if anything else happens we should throw.
        winrt::hresult hr{ RoActivateInstance(activatableClass.get(), ptr.put()) };
        THROW_HR_IF(hr, hr != REGDB_E_CLASSNOTREG);
    }
}

#endif // __MICROSOFT_ROAPI_H
