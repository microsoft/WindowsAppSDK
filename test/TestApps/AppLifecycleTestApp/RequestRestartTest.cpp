// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include "Helpers.h"
#include <TestDef.h>

using namespace winrt;
using namespace winrt::Windows::System;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace std::chrono;

bool RunRequestRestartTestSucceeded(const AppActivationArguments& /*args*/)
{
    SignalPhase(c_testRequestRestartNowPhaseEventName);

    // N.B. This process is terminated by the new instance.
    AppInstance::Restart(L"/RequestRestartNowCalled");

    return true;
}
