// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <IDynamicDependencyLifetimeManager.h>

using namespace winrt;

// Implement the LifetimeManager as a classic COM Out-of-Proc server, via C++/WinRT
// See https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/author-coclasses for more details

static constexpr GUID MyLifetimeManager_guid // {32E7CF70-038C-429a-BD49-88850F1B4A11}
{
    0x32e7cf70, 0x038c, 0x429a, { 0xbd, 0x49, 0x88, 0x85, 0x0f, 0x1b, 0x4a, 0x11 }
};

struct MyLifetimeManager : winrt::implements<MyLifetimeManager, IDynamicDependencyLifetimeManager>
{
    HRESULT __stdcall Initialize()
    {
        return S_OK;
    }

    HRESULT __stdcall Shutdown()
    {
        return S_OK;
    }

    HRESULT __stdcall GetPackageFullName(/*[out, retval]*/ PWSTR* packageFullName)
    {
        *packageFullName = nullptr;

        WCHAR fullName[PACKAGE_FULL_NAME_MAX_LENGTH + 1]{};
        UINT32 fullNameLength = ARRAYSIZE(fullName);
        RETURN_IF_FAILED(GetCurrentPackageFullName(&fullNameLength, fullName));
        auto fullNameCoTaskMem = wil::make_cotaskmem_string_nothrow(fullName);
        RETURN_IF_NULL_ALLOC(fullNameCoTaskMem);

        *packageFullName = fullNameCoTaskMem.release();
        return S_OK;
    }
};

struct MyLifetimeManager_factory : winrt::implements<MyLifetimeManager_factory, IClassFactory>
{
    HRESULT __stdcall CreateInstance(
        IUnknown* outer,
        GUID const& iid,
        void** result) noexcept final
    {
        *result = nullptr;

        if (outer)
        {
            return CLASS_E_NOAGGREGATION;
        }

        return make<MyLifetimeManager>()->QueryInterface(iid, result);
    }

    HRESULT __stdcall LockServer(BOOL) noexcept final
    {
        return S_OK;
    }
};

void register_MyLifetimeManager()
{
    DWORD registration{};

    winrt::check_hresult(::CoRegisterClassObject(
        MyLifetimeManager_guid,
        make<MyLifetimeManager_factory>().get(),
        CLSCTX_LOCAL_SERVER,
        REGCLS_SINGLEUSE,
        &registration));
}

int WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    winrt::init_apartment();

    register_MyLifetimeManager();

    return 0;
}
