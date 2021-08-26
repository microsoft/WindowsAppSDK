#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>

#include "platform.h"
#include "platformfactory.h"

void NotificationsLongRunningPlatformImpl::Initialize()
{
    auto lock = m_lock.lock_exclusive();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    if (m_initialized)
    {
        return;
    }

    // Schedule event signaling after 5 seconds. This is in case we don't have any apps to track in the LRP.
    // If we realize that we need to persist the LRP, timer should be canceled.
    m_shutdownTimerManager = std::make_unique<PlatformLifetimeTimerManager>();
    //m_shutdownTimerManager->Setup();

    /* TODO: Verify registry and UDK list and make sure we have apps to be tracked */

    /* TODO: Load platform components */

    m_initialized = true;
}

void NotificationsLongRunningPlatformImpl::Shutdown() noexcept
{
    auto lock = m_lock.lock_exclusive();
    if (m_shutdown)
    {
        return;
    }

    /* TODO: Shut down your components */

    m_shutdown = true;
}

void NotificationsLongRunningPlatformImpl::WaitForWinMainEvent()
{
    THROW_HR_IF_NULL(E_UNEXPECTED, m_shutdownTimerManager.get());
    m_shutdownTimerManager->Wait();
}

// Example of one function. We will add more as we need them.
STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterFullTrustApplication(_In_ PCWSTR /*processName*/, _In_ GUID /*remoteId*/, _Out_ GUID* /*appId*/) noexcept
{
    auto lock = m_lock.lock_shared();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    
    return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterForegroundActivator(/*[in]*/ IWpnForegroundSink* sink, /*[in]*/ LPCSTR processName)
{
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    auto lock = m_lock.lock_exclusive();

    m_foregroundSinkManager.AddSink(processName, sink);
    SetForegroundTimer();
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::UnregisterForegroundActivator(/*[out]*/ IWpnForegroundSink* sink, /*[in]*/ LPCSTR processName)
{
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    auto lock = m_lock.lock_exclusive();

    m_foregroundSinkManager.Remove(processName, sink);
    return S_OK;
}

void NotificationsLongRunningPlatformImpl::SetForegroundTimer()
{
    m_foregroundTimer.reset(CreateThreadpoolTimer(
        [](PTP_CALLBACK_INSTANCE, _Inout_ PVOID platformPtr, _Inout_ PTP_TIMER)
        {
            NotificationsLongRunningPlatformImpl* platform = reinterpret_cast<NotificationsLongRunningPlatformImpl*>(platformPtr);

            if (platform != nullptr)
            {
                platform->SendForegroundNotification();
            }
        },
        this,
        nullptr));

    THROW_LAST_ERROR_IF_NULL(m_foregroundTimer);

    // Negative times in SetThreadpoolTimer are relative. Allow 5 seconds to fire.
    FILETIME dueTime{};
    *reinterpret_cast<PLONGLONG>(&dueTime) = -static_cast<LONGLONG>(5000 * 10000);

    SetThreadpoolTimer(m_foregroundTimer.get(), &dueTime, 0, 0);
}

void NotificationsLongRunningPlatformImpl::SendForegroundNotification()
{
    auto lock = m_lock.lock_shared();

    byte samplePayload[] = { 0x50, 0x61, 0x79, 0x6c, 0x6f, 0x61, 0x64, 0x20,
                        0x66, 0x72, 0x6f, 0x6d, 0x20, 0x74, 0x68, 0x65,
                            0x20, 0x4c, 0x52, 0x50, 0x21 }; // Payload from the LRP!

    m_foregroundSinkManager.InvokeForegroundHandlers("PushNotificationsDemoApp.exe", samplePayload, sizeof(samplePayload));
}
