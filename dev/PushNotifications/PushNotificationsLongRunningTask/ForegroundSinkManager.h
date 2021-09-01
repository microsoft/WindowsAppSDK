// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <vector>

class ForegroundSinkManager
{
public:
    ForegroundSinkManager() = default;

    void Add(std::wstring const& processName, IWpnForegroundSink* const& sink);

    void Remove(std::wstring const& processName);

    bool InvokeForegroundHandlers(std::wstring const& processName, winrt::com_array<uint8_t> const& payload, ULONG const& payloadSize);

private:
    // An app can only have one activate foreground sink with Long Running Process. Event handlers in
    // the sink are managed by the WindowsAppSDK.
    std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<IWpnForegroundSink>> m_foregroundMap = {};
    wil::srwlock m_lock;
};
