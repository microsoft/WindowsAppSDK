// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

void SignalPhase(const std::wstring& phaseEventName);
bool NeedDynamicDependencies();
HRESULT BootstrapInitialize();
void BootstrapShutdown();
