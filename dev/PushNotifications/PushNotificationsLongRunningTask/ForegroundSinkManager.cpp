#pragma once

#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>
#include <ForegroundSinkManager.h>

void ForegroundSinkManager::Add(std::wstring processName, IWpnForegroundSink* sink)
{
    m_foregroundMap[processName] = sink;
}

void ForegroundSinkManager::Remove(std::wstring processName)
{
    m_foregroundMap.erase(processName);
}

bool ForegroundSinkManager::InvokeForegroundHandlers(std::wstring processName, byte* payload, ULONG payloadSize)
{
    if (m_foregroundMap.find(processName) != m_foregroundMap.end())
    {
        LOG_IF_FAILED(m_foregroundMap[processName]->InvokeAll(payloadSize, payload));
        return true;
    }
    return false;
}
