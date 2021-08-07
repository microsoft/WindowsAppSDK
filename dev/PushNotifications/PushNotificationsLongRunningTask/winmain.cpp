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
#include "externs.h"

using namespace Microsoft::WRL;

void SignalEvent()
{
    GetWinMainEvent().SetEvent();
}

wil::unique_threadpool_timer g_timer;

void SetTimerForEvent()
{
    try
    {
        g_timer.reset(CreateThreadpoolTimer(
            [](PTP_CALLBACK_INSTANCE, _Inout_ PVOID, _Inout_ PTP_TIMER)
            {
                SignalEvent();
            },
            reinterpret_cast<PVOID>(GetCurrentThreadId()),
            nullptr));

        THROW_LAST_ERROR_IF_NULL(g_timer);

        // Negative times in SetThreadpoolTimer are relative. Allow 30 seconds to fire.
        FILETIME dueTime{};
        *reinterpret_cast<PLONGLONG>(&dueTime) = -static_cast<LONGLONG>(30000 * 10000);
        SetThreadpoolTimer(g_timer.get(), &dueTime, 0, 0);
    }
    catch (...)
    {
        LOG_IF_FAILED(wil::ResultFromCaughtException());
    }
}

// This function has to be called after we realized that we want to persist the LRP.
void CancelTimerForEvent()
{
    g_timer.reset();
}

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, PSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
    Sleep(20000);

    // Schedule event signaling after 30 seconds. This is in case we don't have any apps to track in the LRP.
    // If we realize that we need to persist the LRP, timer will be canceled.
    //SetTimerForEvent();

    RETURN_IF_FAILED(::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED));

    // Callback to be signaled by COM if it considers that the process should exit.
    auto& module = Module<OutOfProc>::Create(SignalEvent);

    unsigned long count = module.IncrementObjectCount();

    DWORD cookie = 0;
    ComPtr<IClassFactory> platformFactory;
    THROW_IF_FAILED(MakeAndInitialize<WpnLrpPlatformFactory>(&platformFactory));

    CLSID clsid = __uuidof(NotificationsLongRunningPlatformImpl);

    THROW_IF_FAILED(module.RegisterCOMObject(
        nullptr,
        &clsid,
        platformFactory.GetAddressOf(),
        &cookie,
        1));

    //InitializePlatform();

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
