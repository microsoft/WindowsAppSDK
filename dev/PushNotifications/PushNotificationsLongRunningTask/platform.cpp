#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>

#include "platform.h"
#include "platformfactory.h"

wil::unique_event s_event(wil::EventOptions::None);
wil::unique_threadpool_timer s_timer;

void NotificationsLongRunningPlatformImpl::Initialize()
{
    auto lock = m_lock.lock_exclusive();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    if (m_initialized)
    {
        return;
    }

    // Schedule event signaling after 30 seconds. This is in case we don't have any apps to track in the LRP.
    // If we realize that we need to persist the LRP, timer should be canceled.
    SetupTimer();

    /* Verify registry and UDK list and make sure we have apps to be tracked */

    /* Load your components */

    m_initialized = true;
}

void NotificationsLongRunningPlatformImpl::Shutdown()
{
    auto lock = m_lock.lock_exclusive();
    if (m_shutdown)
    {
        return;
    }

    /* Shut down your components */

    m_shutdown = true;
}

void NotificationsLongRunningPlatformImpl::SignalEvent()
{
    s_event.SetEvent();
}

void NotificationsLongRunningPlatformImpl::WaitForEvent()
{
    s_event.wait();
}

void NotificationsLongRunningPlatformImpl::SetupTimer()
{
    try
    {
        s_timer.reset(CreateThreadpoolTimer(
            [](PTP_CALLBACK_INSTANCE, _Inout_ PVOID, _Inout_ PTP_TIMER)
            {
                SignalEvent();
            },
            reinterpret_cast<PVOID>(GetCurrentThreadId()),
                nullptr));

        THROW_LAST_ERROR_IF_NULL(s_timer);

        // Negative times in SetThreadpoolTimer are relative. Allow 30 seconds to fire.
        FILETIME dueTime{};
        *reinterpret_cast<PLONGLONG>(&dueTime) = -static_cast<LONGLONG>(30000 * 10000);
        SetThreadpoolTimer(s_timer.get(), &dueTime, 0, 0);
    }
    catch (...)
    {
        LOG_IF_FAILED(wil::ResultFromCaughtException());
    }
}

void CancelTimer()
{
    s_timer.reset();
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterActivator(/*[in]*/ PCWSTR /*processName*/)
{
    auto lock = m_lock.lock_shared();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::UnregisterActivator(/*[in]*/ PCWSTR /*processName*/)
{
    auto lock = m_lock.lock_shared();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterForegroundActivator(/*[in]*/ PCWSTR /*processName*/)
{
    auto lock = m_lock.lock_shared();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::UnregisterForegroundActivator(/*[in]*/ PCWSTR /*processName*/)
{
    auto lock = m_lock.lock_shared();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterFullTrustApplication(/*[in]*/ PCWSTR /*processName*/, /*[in]*/ GUID /*remoteId*/, /*[out]*/ GUID* /*appId*/)
{
    auto lock = m_lock.lock_shared();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    return E_NOTIMPL;
}

