#pragma once

#include "pch.h"

void ForegroundSinkManager::Add(std::wstring const& processName, IWpnForegroundSink* const& sink)
{
    auto lock = m_lock.lock_exclusive();
    m_foregroundMap[processName] = sink;
}

void ForegroundSinkManager::Remove(std::wstring const& processName)
{
    auto lock = m_lock.lock_exclusive();
    m_foregroundMap.erase(processName);
}

bool ForegroundSinkManager::InvokeForegroundHandlers(std::wstring const& processName, winrt::com_array<uint8_t> const& payload, ULONG const& payloadSize)
{
    auto lock = m_lock.lock_exclusive();

    auto it = m_foregroundMap.find(processName);
    if (it != m_foregroundMap.end())
    {
        BOOL foregroundHandled = true;
        if (FAILED(it->second->InvokeAll(payloadSize, payload.data(), &foregroundHandled)))
        {
            m_foregroundMap.erase(processName);
            return false;
        }
        return foregroundHandled;
    }
    return false;
}
