#pragma once

#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>
#include <ForegroundSinkManager.h>

void ForegroundSinkManager::AddSink(std::wstring processName, IWpnForegroundSink* sink)
{
    // Maybe check if exists?
    m_foregroundMap[processName] = sink;
}

void ForegroundSinkManager::Remove(std::wstring processName)
{
    // Check if it exists
    m_foregroundMap.erase(processName);
}

void ForegroundSinkManager::InvokeForegroundHandlers(ULONG payloadSize, byte* payload)
{
    for (std::pair<std::wstring, Microsoft::WRL::ComPtr<IWpnForegroundSink>> sink : m_foregroundMap)
    {
        sink.second->InvokeAll(payloadSize, payload);
    }
}

//***
// Waiting for NotificationListener to be finished
// ***
//void ForegroundSinkManager::InvokeForegroundHandlers(std::string processName, byte* payload, ULONG payloadSize)
//{
//    THROW_HR_IF(E_INVALIDARG, !m_foregroundMap.contains(processName));
//
//    std::vector<std::pair<GUID, Microsoft::WRL::ComPtr <IWpnForegroundSink>>> sinkContainer = m_foregroundMap[processName];
//    for (std::pair<GUID, Microsoft::WRL::ComPtr <IWpnForegroundSink>> sink : sinkContainer)
//    {
//        sink.second->InvokeAll(payload, payloadSize);
//    }
//}
