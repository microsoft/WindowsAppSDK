// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
#pragma once

void SignalPhase(const std::wstring& phaseEventName);
bool NeedDynamicDependencies();
HRESULT BootstrapInitialize();
void BootstrapShutdown();
