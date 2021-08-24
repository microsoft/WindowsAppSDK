#pragma once

#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>



#include <ForegroundSinkManager.h>

void ForegroundSinkManager::AddSink(LPCSTR processName, IWpnForegroundSink* sink)
{
    if (!m_foregroundMap.contains(processName))
    {
        m_foregroundMap[processName] = std::unordered_set<IWpnForegroundSink*>();
    }

    m_foregroundMap[processName].insert(sink);
}

void ForegroundSinkManager::Remove(LPCSTR processName, IWpnForegroundSink* sink)
{
    THROW_HR_IF(E_INVALIDARG, !m_foregroundMap.contains(processName));

    std::unordered_set<IWpnForegroundSink*> sinks = m_foregroundMap[processName];
    sinks.erase(sink);
    if (sinks.empty())
    {
        m_foregroundMap.erase(processName);
    }
}

bool ForegroundSinkManager::InvokeForegroundHandlers(LPCSTR processName, byte* payload, ULONG payloadSize)
{
    std::unordered_set<IWpnForegroundSink*> sinks = m_foregroundMap[processName];
    if (!m_foregroundMap.contains(processName))
    {
        return false;
    }

    std::unordered_set<IWpnForegroundSink*> sinks2 = m_foregroundMap[processName];
    std::for_each(sinks.begin(), sinks.end(), [&](IWpnForegroundSink* sink) { sink->InvokeAll(payload, payloadSize); });
    return true;
}
