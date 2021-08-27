// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <unordered_map>
#include <unordered_set>
#include <algorithm>

class ForegroundSinkManager
{
public:
    ForegroundSinkManager() = default;

    void AddSink(std::string processName, IWpnForegroundSink* sink);

    void Remove(std::string processName, IWpnForegroundSink* sink);

    void InvokeAllHandlers(byte* payload, ULONG payloadSize); // for testing

    bool InvokeForegroundHandlersOfProc(std::string processName, byte* payload, ULONG payloadSize);

private:
    std::unordered_map<std::string, std::unordered_set<IWpnForegroundSink*>> m_foregroundMap = {};

};
