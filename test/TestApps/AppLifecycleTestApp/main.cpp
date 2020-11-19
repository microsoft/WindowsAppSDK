// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <testdef.h>

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Microsoft::ProjectReunion;

std::wstring GetFullIdentityString()
{
    std::wstring identityString;
    WCHAR idNameBuffer[PACKAGE_FULL_NAME_MAX_LENGTH + 1];
    UINT32 idNameBufferLen = ARRAYSIZE(idNameBuffer);
    if (::GetCurrentPackageFullName(&idNameBufferLen, idNameBuffer) == ERROR_SUCCESS)
    {
        identityString = idNameBuffer;
    }

    return identityString;
}

bool HasIdentity()
{
    return !(GetFullIdentityString()).empty();
}

void SignalPhase(const std::wstring& phaseEventName)
{
    wil::unique_event phaseEvent;
    if(phaseEvent.try_open(phaseEventName.c_str(), EVENT_MODIFY_STATE, false))
    {
        phaseEvent.SetEvent();
    }
}

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

                // Signal event that protocol was registered.
                SignalPhase(c_testProtocolPhaseEventName);
            }
            else if (argument.compare(L"UnregisterProtocol"))
            {
                ActivationRegistrationManager::UnregisterForProtocolActivation(c_testProtocolScheme);

                // Signal event that protocol was unregistered.
                SignalPhase(c_testProtocolPhaseEventName);
            }
            else if (argument.compare(L"RegisterFile"))
            {
                // TODO: Figure out how to properly test the logo icon support.
                ActivationRegistrationManager::RegisterForFileTypeActivation({ c_testFileExtension.c_str() },
                    { L"open" }, L"Project Reunion Test File Type", L"logo");

                // Signal event that file was registered.
                SignalPhase(c_testFilePhaseEventName);
            }
            else if (argument.compare(L"UnregisterFile"))
            {
                ActivationRegistrationManager::UnregisterForFileTypeActivation(c_testFileExtension);

                // Signal event that file was unregistered.
                SignalPhase(c_testFilePhaseEventName);
            }
        }
    }
    else if (kind == ActivationKind::Protocol)
    {
        // Signal event that protocol was activated.
        if (HasIdentity())
        {
            SignalPhase(c_testProtocolPhaseEventName_Packaged);
        }
        else
        {
            SignalPhase(c_testProtocolPhaseEventName);
        }
    }
    else if (kind == ActivationKind::File)
    {
        // TODO: Validate access to the files on the arguments.

        // Signal event that file was activated.
        if (HasIdentity())
        {
            SignalPhase(c_testFilePhaseEventName_Packaged);
        }
        else
        {
            SignalPhase(c_testFilePhaseEventName);
        }
    }

    return 0;
}
