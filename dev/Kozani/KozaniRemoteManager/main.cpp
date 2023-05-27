// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "..\KozaniRemoteManager\KozaniRemoteManager-Constants.h"

#include <KozaniRemoteManager_h.h>

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

#include <wrl\module.h>

#include "Module.h"

using namespace Microsoft::WRL;
using namespace Microsoft::Kozani::KozaniRemoteManager;

// Implement the LifetimeManager as a classic COM Out-of-Proc server, via WRL
// See https://docs.microsoft.com/cpp/cppcx/wrl/how-to-create-a-classic-com-component-using-wrl?redirectedfrom=MSDN&view=vs-2019 for more details

static constexpr GUID KozaniRemoteManager_guid { PR_KOZANIREMOTEMANAGER_CLSID_GUID };

Microsoft::WRL::Details::DefaultModule<OutOfProc>* g_module{};
ConnectionManager g_connectionManager;

namespace KozaniRemoteManagerModule
{
    void IncrementObjectCount()
    {
        g_module->IncrementObjectCount();
    }

    void DecrementObjectCount()
    {
        g_module->DecrementObjectCount();
    }

    Microsoft::Kozani::KozaniRemoteManager::ConnectionManager& GetConnectionManagerInstance()
    {
        return g_connectionManager;
    }
};

struct __declspec(uuid(PR_KOZANIREMOTEMANAGER_CLSID_STRING)) KozaniRemoteManagerImpl WrlFinal : RuntimeClass<RuntimeClassFlags<ClassicCom>, IKozaniRemoteManager>
{
    STDMETHODIMP Connect(_In_ PCSTR connectionId) noexcept try
    {
        g_connectionManager.Connect(connectionId);    
        return S_OK;
    }
    CATCH_RETURN()
};
CoCreatableClass(KozaniRemoteManagerImpl);

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
    g_module = &module;
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
