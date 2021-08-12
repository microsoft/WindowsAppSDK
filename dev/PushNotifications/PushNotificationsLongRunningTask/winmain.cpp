// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

// include notifications constants file here

#include <NotificationsLongRunningProcess_h.h>

// Temporarily disable C4324 because WRL generates a false (well, irrelevant) warning
//   'Microsoft::WRL::Details::StaticStorage<Microsoft::WRL::Details::OutOfProcModuleBase<ModuleT>::GenericReleaseNotifier<T>,Microsoft::WRL::Details::StorageInstance::OutOfProcCallbackBuffer1,ModuleT>': structure was padded due to alignment specifier
#pragma warning(push)
#pragma warning(disable:4324)
#include <wrl.h>
#pragma warning(pop)

#include "platform.h"
#include "platformfactory.h"

using namespace Microsoft::WRL;

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    Sleep(20000);

    THROW_IF_FAILED(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));

    ComPtr<WpnLrpPlatformFactory> platformFactory;
    THROW_IF_FAILED(MakeAndInitialize<WpnLrpPlatformFactory>(&platformFactory));

    ComPtr<IClassFactory> platformFactoryAsClassFactory;
    THROW_IF_FAILED(platformFactory.As<IClassFactory>(&platformFactoryAsClassFactory));

    // Schedule event signaling after 30 seconds. This is in case we don't have any apps to track in the LRP.
    // If we realize that we need to persist the LRP, timer will be canceled.
    platformFactory->SetupTimer();

    auto& module = Module<OutOfProc>::Create();

    CLSID clsid = __uuidof(NotificationsLongRunningPlatformImpl);
    DWORD cookie = 0;
    THROW_IF_FAILED(module.RegisterCOMObject(
        nullptr,
        &clsid,
        platformFactoryAsClassFactory.GetAddressOf(),
        &cookie,
        1));    

    ComPtr<NotificationsLongRunningPlatformImpl> platform;
    // Get an initialized instance of the LRP platform
    THROW_IF_FAILED(platformFactory->CreateInstance(nullptr, __uuidof(INotificationsLongRunningPlatform), &platform));

    WpnLrpPlatformFactory::WaitForEvent();

    (void)LOG_IF_FAILED(module.UnregisterCOMObject(nullptr, &cookie, 1));

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
