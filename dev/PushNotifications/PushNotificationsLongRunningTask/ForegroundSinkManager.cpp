// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"

using namespace Microsoft::WRL;

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

bool ForegroundSinkManager::InvokeForegroundHandlers(
    std::wstring const& appId,
    winrt::com_array<uint8_t> const& payload,
    HSTRING correlationVector,
    ULONG const& payloadSize)
{
    auto lock = m_lock.lock_exclusive();

    auto it = m_foregroundMap.find(appId);
    if (it != m_foregroundMap.end())
    {
        // IWpnForegroundSink2 declares InvokeAll expecting a correlation vector.
        // The SDK may not know about this interface, so we make sure
        // if the foreground sink implements it, then route the payload appropriately.
        BOOL foregroundHandled = true;
        auto foregroundSink = it->second;
        ComPtr<IWpnForegroundSink2> foregroundSink2;
        HRESULT foregroundSinkCastResult = foregroundSink.As(&foregroundSink2);

        HRESULT invokeOperationResult = S_OK;

        if (SUCCEEDED(foregroundSinkCastResult))
        {
            invokeOperationResult = foregroundSink2->InvokeAllWithCorrelationVector(
                payloadSize,
                payload.data(),
                wil::str_raw_ptr(correlationVector),
                &foregroundHandled);
        }
        else
        {
            invokeOperationResult = foregroundSink->InvokeAll(payloadSize, payload.data(), &foregroundHandled);
        }

        if (FAILED(invokeOperationResult))
        {
            m_foregroundMap.erase(appId);
            return false;
        }

        return foregroundHandled;
    }
    return false;
}
