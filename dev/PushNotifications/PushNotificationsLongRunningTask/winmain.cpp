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
    RETURN_IF_FAILED(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));

    ComPtr<NotificationsLongRunningProcessFactory> platformFactory;
    RETURN_IF_FAILED(MakeAndInitialize<NotificationsLongRunningProcessFactory>(&platformFactory));

    ComPtr<NotificationsLongRunningPlatformImpl> platform;
    // Get an initialized instance of the LRP platform
    RETURN_IF_FAILED(platformFactory->CreateInstance(nullptr, __uuidof(INotificationsLongRunningPlatform), &platform));

    auto& module = Module<OutOfProc>::Create();

    ComPtr<IClassFactory> platformFactoryAsClassFactory;
    RETURN_IF_FAILED(platformFactory.As<IClassFactory>(&platformFactoryAsClassFactory));

    CLSID clsid = __uuidof(NotificationsLongRunningPlatformImpl);
    DWORD cookie = 0;
    RETURN_IF_FAILED(module.RegisterCOMObject(
        nullptr,
        &clsid,
        platformFactoryAsClassFactory.GetAddressOf(),
        &cookie,
        1));

    // Wait returns if the platform realizes there are no more apps to be tracked.
    // It also returns if the timer initialized at the process start fires (see NotificationsLongRunningPlatformImpl::Initialize).
    platform->WaitForWinMainEvent();

    RETURN_IF_FAILED(module.UnregisterCOMObject(nullptr, &cookie, 1));

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
