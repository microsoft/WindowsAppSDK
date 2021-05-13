// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

void SignalPhase(const std::wstring& phaseEventName);
bool NeedDynamicDependencies();
HRESULT BootstrapInitialize();
void BootstrapShutdown();
