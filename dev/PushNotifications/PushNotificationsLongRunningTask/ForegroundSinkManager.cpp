#pragma once

#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>
#include <ForegroundSinkManager.h>

void ForegroundSinkManager::AddSink(std::string processName, IWpnForegroundSink* sink)
{
    if (!m_foregroundMap.contains(processName))
    {
        m_foregroundMap[processName] = std::unordered_set<IWpnForegroundSink*>();
    }
    m_foregroundMap[processName].insert(sink);
}

void ForegroundSinkManager::Remove(std::string processName, IWpnForegroundSink* sink)
{
    //THROW_HR_IF(E_INVALIDARG, !m_foregroundMap.contains(processName));

    std::unordered_set<IWpnForegroundSink*> sinks = m_foregroundMap[processName];
    sinks.erase(sink);
    if (sinks.empty())
    {
        m_foregroundMap.erase(processName);
    }
}

void ForegroundSinkManager::InvokeAllHandlers(byte* payload, ULONG payloadSize)
{
    for (std::pair<std::string, std::unordered_set<IWpnForegroundSink*>> pair : m_foregroundMap)
    {
        for (IWpnForegroundSink* sink : pair.second)
        {
            sink->InvokeAll(payload, payloadSize);
        }
    }
}

bool ForegroundSinkManager::InvokeForegroundHandlersOfProc(std::string processName, byte* payload, ULONG payloadSize)
{
    if (!m_foregroundMap.contains(processName))
    {
        return false;
    }

    std::unordered_set<IWpnForegroundSink*> sinks = m_foregroundMap[processName];
    std::for_each(sinks.begin(), sinks.end(), [&](IWpnForegroundSink* sink) { sink->InvokeAll(payload, payloadSize); });
    return true;
}
