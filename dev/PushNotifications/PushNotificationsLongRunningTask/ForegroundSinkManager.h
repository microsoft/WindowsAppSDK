// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <unordered_map>
#include <unordered_set>
#include <algorithm>

class ForegroundSinkManager
{
public:
    ForegroundSinkManager() = default;

    void AddSink(LPCSTR processName, IWpnForegroundSink* sink);

    void Remove(LPCSTR processName, IWpnForegroundSink* sink);

    bool InvokeForegroundHandlers(LPCSTR processName, byte* payload, ULONG payloadSize);

private:
    std::unordered_map<LPCSTR, std::unordered_set<IWpnForegroundSink*>> m_foregroundMap = {};

};
