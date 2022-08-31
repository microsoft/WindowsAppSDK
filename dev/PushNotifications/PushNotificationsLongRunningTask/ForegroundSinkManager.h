// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <vector>

class ForegroundSinkManager
{
public:
    ForegroundSinkManager() = default;

    void Add(std::wstring const& appId, IWpnForegroundSink* const& sink);

    void Add(std::wstring const& appId, IWpnForegroundSink2* const& sink);

    void Remove(std::wstring const& appId);

    bool InvokeForegroundHandlers(std::wstring const& appId, winrt::com_array<uint8_t> const& payload, ULONG const& payloadSize, HSTRING correlationVector);

private:
    // An app can only have one activate foreground sink with Long Running Process.
    // Event handlers in the sink are managed by the WindowsAppSDK.
    std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<IWpnForegroundSink>> m_foregroundMap = {};
    std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<IWpnForegroundSink2>> m_foregroundMap2 = {};
    wil::srwlock m_lock;
};
