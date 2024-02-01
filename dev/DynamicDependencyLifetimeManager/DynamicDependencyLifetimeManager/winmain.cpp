// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "..\DynamicDependencyLifetimeManager-Constants.h"

#include <DynamicDependencyLifetimeManager_h.h>

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

#include <wrl\module.h>

using namespace Microsoft::WRL;

// Implement the LifetimeManager as a classic COM Out-of-Proc server, via WRL
// See https://docs.microsoft.com/cpp/cppcx/wrl/how-to-create-a-classic-com-component-using-wrl?redirectedfrom=MSDN&view=vs-2019 for more details

static constexpr GUID DynamicDependencyLifetimeManager_guid { PR_DYNDEP_LIFETIMEMANAGER_CLSID_GUID };

struct __declspec(uuid(PR_DYNDEP_LIFETIMEMANAGER_CLSID_STRING)) DynamicDependencyLifetimeManagerImpl WrlFinal : RuntimeClass<RuntimeClassFlags<ClassicCom>, IDynamicDependencyLifetimeManager>
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
        RETURN_IF_FAILED(::GetCurrentPackageFullName(&fullNameLength, fullName));
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
    RETURN_IF_FAILED(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));

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

STDAPI_(BOOL) DllMain(_In_opt_ HINSTANCE hinst, DWORD reason, _In_opt_ void* reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinst);
    }

    // Give WIL a crack at DLLMain processing
    // See DLLMain() in wil/result_macros.h for why
    wil::DLLMain(hinst, reason, reserved);

    return TRUE;
}
