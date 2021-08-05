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

wil::unique_threadpool_timer SetTimerForEvent()
{
    wil::unique_threadpool_timer methodExecutionTimer;

    try
    {
        methodExecutionTimer.reset(CreateThreadpoolTimer(
            [](PTP_CALLBACK_INSTANCE, _Inout_ PVOID, _Inout_ PTP_TIMER)
            {
                SignalEvent();
            },
            reinterpret_cast<PVOID>(GetCurrentThreadId()),
            nullptr));

        THROW_LAST_ERROR_IF_NULL(methodExecutionTimer);

        // Negative times in SetThreadpoolTimer are relative. Allow 30 seconds to fire.
        FILETIME dueTime{};
        *reinterpret_cast<PLONGLONG>(&dueTime) = -static_cast<LONGLONG>(30000 * 10000);
        SetThreadpoolTimer(methodExecutionTimer.get(), &dueTime, 0, 0);
    }
    catch (...)
    {
        LOG_IF_FAILED(wil::ResultFromCaughtException());
    }

    return methodExecutionTimer;
}

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    // Time to connect to a debugger. Eventually should be removed.
    Sleep(20000);

    // Schedule event signaling after 30 seconds. This is in case we don't have any apps to track in the LRP.
    // If we realize that we need to persist the LRP, timer will be canceled.
    wil::unique_threadpool_timer timer = SetTimerForEvent();

    RETURN_IF_FAILED(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));

    // Callback to be signaled by COM if it considers that the process should exit.
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
        1));

    InitializePlatform();

    //timer.reset();

    GetWinMainEvent().wait();

    ShutdownPlatform();
    CleanPlatform();

    count = module.DecrementObjectCount();

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
