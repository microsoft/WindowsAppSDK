// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

// include notifications constants file here

#include <PushNotificationsLRP_h.h>

// Temporarily disable C4324 because WRL generates a false (well, irrelevant) warning
//   'Microsoft::WRL::Details::StaticStorage<Microsoft::WRL::Details::OutOfProcModuleBase<ModuleT>::GenericReleaseNotifier<T>,Microsoft::WRL::Details::StorageInstance::OutOfProcCallbackBuffer1,ModuleT>': structure was padded due to alignment specifier
#pragma warning(push)
#pragma warning(disable:4324)
#include <wrl.h>
#pragma warning(pop)

#include "platform.h"
#include "platformfactory.h"
#include "externs.h"

using namespace Microsoft::WRL;

void SignalEvent()
{
    GetWinMainEvent().SetEvent();
}

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    // Time to connect to a debugger. Eventually should be removed.
    Sleep(20000);

    RETURN_IF_FAILED(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));

    // Callback to be signaled by COM if it considers that the event should exit.
    auto& module = Module<OutOfProc>::Create(SignalEvent);

    unsigned long count = module.IncrementObjectCount();

    DWORD cookie = 0;
    ComPtr<IClassFactory> platformFactory;
    THROW_IF_FAILED(MakeAndInitialize<WpnLrpPlatformFactory>(&platformFactory));

    CLSID clsid = __uuidof(WpnLrpPlatform);

    THROW_IF_FAILED(module.RegisterCOMObject(
        nullptr,
        &clsid,
        platformFactory.GetAddressOf(),
        &cookie,
        1
    ));

    InitializePlatform();

    GetWinMainEvent().wait();

    GetPlatform()->ShutdownPlatform();
    CleanPlatform();

    count = module.DecrementObjectCount();

    (void) LOG_IF_FAILED(module.UnregisterCOMObject(nullptr, &cookie, 1));
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
