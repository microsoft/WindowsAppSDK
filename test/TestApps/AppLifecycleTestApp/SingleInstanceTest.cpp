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

wil::unique_event g_activated;

IAsyncAction WaitForActivations()
{
    if (!(co_await resume_on_signal(g_activated.get(), 3000s)))
    {
        // We timed out waiting for our redirection.
        THROW_WIN32(ERROR_TIMEOUT);
    }
}

void OnActivated(const winrt::Windows::Foundation::IInspectable&, const AppActivationArguments& args)
{
    auto launchArgs = args.Data().as<IProtocolActivatedEventArgs>();
    SignalPhase(c_testInstanceRedirectedPhaseEventName);
    g_activated.SetEvent();
}

bool SingleInstanceTestSucceeded(const AppActivationArguments& args)
{
    g_activated.create();

    auto keyInstance = AppInstance::FindOrRegisterForKey(c_testInstanceRedirectedPhaseEventName);
    if (!keyInstance)
    {
        return false;
    }

    if (keyInstance.IsCurrent())
    {
        auto token = keyInstance.Activated(auto_revoke, [&keyInstance](const auto& sender, const AppActivationArguments& args) { OnActivated(sender, args); });

        // Launch a second instance and test that it redirects to us.
        auto launchResult{ Launcher::LaunchUriAsync(args.Data().as<IProtocolActivatedEventArgs>().Uri()).get() };
        if (!launchResult)
        {
            return false;
        }

        WaitForActivations().get();
    }
    else
    {
        keyInstance.RedirectActivationToAsync(args).get();
    }

    return true;
}
