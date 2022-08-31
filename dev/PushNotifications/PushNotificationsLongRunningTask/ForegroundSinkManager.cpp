// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

void ForegroundSinkManager::Add(std::wstring const& appId, IWpnForegroundSink* const& sink)
{
    auto lock = m_lock.lock_exclusive();
    Remove(appId);
    m_foregroundMap[appId] = sink;
}

void ForegroundSinkManager::Add(std::wstring const& appId, IWpnForegroundSink2* const& sink)
{
    auto lock = m_lock.lock_exclusive();
    Remove(appId);
    m_foregroundMap2[appId] = sink;
}

void ForegroundSinkManager::Remove(std::wstring const& appId)
{
    auto lock = m_lock.lock_exclusive();
    m_foregroundMap2.erase(appId);
    m_foregroundMap.erase(appId);
}

bool ForegroundSinkManager::InvokeForegroundHandlers(std::wstring const& appId, winrt::com_array<uint8_t> const& payload, ULONG const& payloadSize, HSTRING correlationVector)
{
    auto lock = m_lock.lock_exclusive();

    auto it2 = m_foregroundMap2.find(appId);
    if (it2 != m_foregroundMap2.end())
    {
        BOOL foregroundHandled = true;
        if (FAILED(it2->second->InvokeAllWithCorrelationVector(payloadSize, payload.data(), wil::str_raw_ptr(correlationVector), &foregroundHandled)))
        {
            m_foregroundMap.erase(appId);
            return false;
        }
        return foregroundHandled;
    }

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
