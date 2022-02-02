#pragma once

#include "pch.h"

void ForegroundSinkManager::Add(std::wstring const& appId, IWpnForegroundSink* const& sink)
{
    auto lock = m_lock.lock_exclusive();
    m_foregroundMap[appId] = sink;
}

void ForegroundSinkManager::Remove(std::wstring const& appId)
{
    auto lock = m_lock.lock_exclusive();
    m_foregroundMap.erase(appId);
}
// test
bool ForegroundSinkManager::InvokeForegroundHandlers(std::wstring const& appId, winrt::com_array<uint8_t> const& payload, ULONG const& payloadSize)
{
    auto lock = m_lock.lock_exclusive();

    auto it = m_foregroundMap.find(appId);
    if (it != m_foregroundMap.end())
    {
        BOOL foregroundHandled = true;
        if (FAILED(it->second->InvokeAll(payloadSize, payload.data(), &foregroundHandled)))
        {
            m_foregroundMap.erase(appId);
            return false;
        }
        return foregroundHandled;
    }
    return false;
}
