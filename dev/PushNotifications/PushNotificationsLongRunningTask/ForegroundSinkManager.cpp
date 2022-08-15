// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"
#include "PushNotificationLongRunningTaskTelemetry.h"

void ForegroundSinkManager::Add(std::wstring const& appId, IWpnForegroundSink* const& sink)
{
    PushNotificationLongRunningTaskTelemetry::LogSomethingSomething(1);

    auto lock = m_lock.lock_exclusive();
    m_foregroundMap[appId] = sink;
}

void ForegroundSinkManager::Remove(std::wstring const& appId)
{
    PushNotificationLongRunningTaskTelemetry::LogSomethingSomething(2);

    auto lock = m_lock.lock_exclusive();
    m_foregroundMap.erase(appId);
}

bool ForegroundSinkManager::InvokeForegroundHandlers(std::wstring const& appId, winrt::com_array<uint8_t> const& payload, ULONG const& payloadSize, HSTRING correlationVector)
{
    PushNotificationLongRunningTaskTelemetry::LogSomethingSomething(3);

    auto lock = m_lock.lock_exclusive();

    auto it = m_foregroundMap.find(appId);
    if (it != m_foregroundMap.end())
    {
        BOOL foregroundHandled = true;
        if (FAILED(it->second->InvokeAll(payloadSize, payload.data(), correlationVector, &foregroundHandled)))
        {
            m_foregroundMap.erase(appId);
            return false;
        }
        return foregroundHandled;
    }
    return false;
}
