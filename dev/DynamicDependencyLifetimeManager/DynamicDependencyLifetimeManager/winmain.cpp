// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <DynamicDependencyLifetimeManager_h.h>

#include <wrl\module.h>

using namespace Microsoft::WRL;

// Implement the LifetimeManager as a classic COM Out-of-Proc server, via WRL
// See https://docs.microsoft.com/en-us/cpp/cppcx/wrl/how-to-create-a-classic-com-component-using-wrl?redirectedfrom=MSDN&view=vs-2019 for more details

static constexpr GUID DynamicDependencyLifetimeManager_guid // {32E7CF70-038C-429a-BD49-88850F1B4A11}
{
    0x32e7cf70, 0x038c, 0x429a, { 0xbd, 0x49, 0x88, 0x85, 0x0f, 0x1b, 0x4a, 0x11 }
};

struct __declspec(uuid("32E7CF70-038C-429a-BD49-88850F1B4A11")) DynamicDependencyLifetimeManagerImpl WrlFinal : RuntimeClass<RuntimeClassFlags<ClassicCom>, IDynamicDependencyLifetimeManager>
{
    STDMETHODIMP Initialize()
    {
        return S_OK;
    }

    STDMETHODIMP Shutdown()
    {
        return S_OK;
    }

    STDMETHODIMP GetPackageFullName(/*[out, retval]*/ PWSTR* packageFullName)
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
CoCreatableClass(DynamicDependencyLifetimeManagerImpl);

wil::unique_event g_endOfTheLine;

void EndOfTheLine()
{
    g_endOfTheLine.SetEvent();
}

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    ::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);

    wil::unique_event endOfTheLine(::CreateEventW(nullptr, TRUE, FALSE, nullptr));
    RETURN_LAST_ERROR_IF_NULL(endOfTheLine);
    g_endOfTheLine = std::move(endOfTheLine);

    auto& module = Module<OutOfProc>::Create(EndOfTheLine);
    RETURN_IF_FAILED(module.RegisterObjects());

    g_endOfTheLine.wait();

    (void)LOG_IF_FAILED(module.UnregisterObjects());
    module.Terminate();

    ::CoUninitialize();

    return 0;
}

STDAPI_(BOOL) DllMain(_In_opt_ HINSTANCE hinst, DWORD reason, _In_opt_ void*)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinst);
    }
    return TRUE;
}
