// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <testdef.h>

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Microsoft::ApplicationModel::Activation;

int main()
{
    auto args = AppLifecycle::GetActivatedEventArgs();
    auto kind = args.Kind();
    if (kind == ActivationKind::Launch)
    {
        auto launchArgs = args.as<ILaunchActivatedEventArgs>();
        auto commandLine = std::wstring(launchArgs.Arguments().c_str());
        auto argStart = commandLine.rfind(L"/");
        if (argStart != std::wstring::npos)
        {
            auto argument = commandLine.substr(argStart);

            if (argument.compare(L"RegisterProtocol"))
            {
                // TODO: Figure out how to properly test the logo icon support.
                ActivationRegistrationManager::RegisterForProtocolActivation(c_testProtocolScheme,
                    L"Project Reunion Test Protocol", L"logo");
            }
            else if (argument.compare(L"UnregisterProtocol"))
            {
                ActivationRegistrationManager::UnregisterForProtocolActivation(c_testProtocolScheme);
            }
            else if (argument.compare(L"RegisterFile"))
            {
                // TODO: Figure out how to properly test the logo icon support.
                ActivationRegistrationManager::RegisterForFileTypeActivation({ c_testFileExtension.c_str() },
                    { L"open" }, L"Project Reunion Test File Type", L"logo");
            }
            else if (argument.compare(L"UnregisterFile"))
            {
                ActivationRegistrationManager::UnregisterForFileTypeActivation(c_testFileExtension);
            }
        }
    }
    else if (kind == ActivationKind::Protocol)
    {
        // Signal even that file was activated.
        wil::unique_event activatedEvent;
        activatedEvent.open(c_testProtocolActivatedEventName.c_str(), EVENT_MODIFY_STATE, false);
        activatedEvent.SetEvent();
    }
    else if (kind == ActivationKind::File)
    {
        // TODO: Validate access to the files on the arguments.

        // Signal even that file was activated.
        wil::unique_event activatedEvent;
        activatedEvent.open(c_testFileActivatedEventName.c_str(), EVENT_MODIFY_STATE, false);
        activatedEvent.SetEvent();
    }

    return 0;
}
