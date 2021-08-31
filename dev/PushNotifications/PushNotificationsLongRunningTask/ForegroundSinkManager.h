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

    void Add(std::wstring processName, IWpnForegroundSink* sink);

    void Remove(std::wstring processName);

    bool InvokeForegroundHandlers(std::wstring processName, byte* payload, ULONG payloadSize);

private:
    std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<IWpnForegroundSink>> m_foregroundMap = {};

};
