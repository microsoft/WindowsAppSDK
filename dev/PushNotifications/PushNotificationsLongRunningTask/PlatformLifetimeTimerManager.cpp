#include "pch.h"

#include "PlatformLifetimeTimerManager.h"

void PlatformLifetimeTimerManager::Setup()
{
    auto lock = m_lock.lock_exclusive();

    m_timer.reset(CreateThreadpoolTimer(
        [](PTP_CALLBACK_INSTANCE, _Inout_ PVOID shutdownTimerManagerPtr, _Inout_ PTP_TIMER)
        {
            PlatformLifetimeTimerManager* shutdownTimerManager = reinterpret_cast<PlatformLifetimeTimerManager*>(shutdownTimerManagerPtr);

            if (shutdownTimerManager != nullptr)
            {
                shutdownTimerManager->SignalWinMainEvent();
            }
        },
        this,
        nullptr));

    THROW_LAST_ERROR_IF_NULL(m_timer);

    // Negative times in SetThreadpoolTimer are relative. Allow 5 seconds to fire.
    FILETIME dueTime{};
    *reinterpret_cast<PLONGLONG>(&dueTime) = -static_cast<LONGLONG>(5000 * 10000);

    SetThreadpoolTimer(m_timer.get(), &dueTime, 0, 0);
}

void PlatformLifetimeTimerManager::Cancel()
{
    auto lock = m_lock.lock_exclusive();
    m_timer.reset();
}

void PlatformLifetimeTimerManager::Wait()
{
    m_event.wait();
}

void PlatformLifetimeTimerManager::SignalWinMainEvent()
{
    m_event.SetEvent();
}
