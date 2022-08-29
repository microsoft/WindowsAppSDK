// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "PlatformLifetimeManager.h"

void PlatformLifetimeManager::Setup()
{
    auto lock = m_lock.lock_exclusive();

    m_timer.reset(CreateThreadpoolTimer(
        [](PTP_CALLBACK_INSTANCE, _Inout_ PVOID shutdownTimerManagerPtr, _Inout_ PTP_TIMER)
        {
            PlatformLifetimeManager* shutdownTimerManager = reinterpret_cast<PlatformLifetimeManager*>(shutdownTimerManagerPtr);
            shutdownTimerManager->SignalEvent();
        },
        this,
        nullptr));

    THROW_LAST_ERROR_IF_NULL(m_timer);

    // Negative times in SetThreadpoolTimer are relative. Allow 5 seconds to fire.
    FILETIME dueTime{};
    *reinterpret_cast<PLONGLONG>(&dueTime) = -static_cast<LONGLONG>(5000 * 10000);

    SetThreadpoolTimer(m_timer.get(), &dueTime, 0, 0);

    m_event.ResetEvent();
}

void PlatformLifetimeManager::Cancel()
{
    auto lock = m_lock.lock_exclusive();
    m_timer.reset();
}

void PlatformLifetimeManager::Wait()
{
    m_event.wait();
}

void PlatformLifetimeManager::SignalEvent()
{
    m_event.SetEvent();
}
