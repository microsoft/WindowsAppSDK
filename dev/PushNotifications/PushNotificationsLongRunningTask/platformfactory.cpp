#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>

#include "platform.h"
#include <wrl/implements.h>
#include <wrl/module.h>
#include "platformfactory.h"

using namespace Microsoft::WRL;

wil::unique_event g_event(wil::EventOptions::None);
wil::unique_threadpool_timer g_timer;

HRESULT WpnLrpPlatformFactory::MakeAndInitialize()
{
     return S_OK;
}

IFACEMETHODIMP WpnLrpPlatformFactory::CreateInstance(
    _In_opt_ IUnknown* /*outer*/,
    _In_ REFIID /*riid*/,
    _COM_Outptr_ void** obj)
{
    *obj = nullptr;

    std::call_once(m_platformInitializedFlag,
        [&] {
            m_platform = Microsoft::WRL::Make<NotificationsLongRunningPlatformImpl>();
            m_platform->Initialize();            
        });

    *obj = m_platform.Get();
    // Add one ref per platform instance request. Deref occurs automatically.
    m_platform->AddRef();

    return S_OK;
}

void WpnLrpPlatformFactory::SignalEvent()
{
    g_event.SetEvent();
}

void WpnLrpPlatformFactory::WaitForEvent()
{
    g_event.wait();
}

void WpnLrpPlatformFactory::SetupTimer()
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
        *reinterpret_cast<PLONGLONG>(&dueTime) = -static_cast<LONGLONG>(60000 * 10000);
        SetThreadpoolTimer(g_timer.get(), &dueTime, 0, 0);
    }
    catch (...)
    {
        LOG_IF_FAILED(wil::ResultFromCaughtException());
    }
}

void WpnLrpPlatformFactory::CancelTimer()
{
    g_timer.reset();
}
