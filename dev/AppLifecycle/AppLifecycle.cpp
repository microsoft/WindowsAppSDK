// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>

#include "../PushNotifications/PushNotificationReceivedEventArgs.h"

#include <AppLifecycle.h>
#include <AppLifecycle.g.cpp>

#include "ActivationArguments.h"

#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "FileActivatedEventArgs.h"
#include "Association.h"

extern wil::unique_handle g_waitHandleForArgs;
extern winrt::Microsoft::ProjectReunion::PushNotificationReceivedEventArgs g_activatedEventArgs;

namespace winrt
{
    using namespace Windows::Foundation;
    using Windows::ApplicationModel::Activation::IActivatedEventArgs;
}

namespace winrt::Microsoft::ProjectReunion::implementation
{
    std::tuple<std::wstring, std::wstring> ParseCommandLine(std::wstring commandLine)
    {
        auto argsStart = commandLine.rfind(L"----") + 4;
        if (argsStart == std::wstring::npos)
        {
            return {L"", L""};
        }

        // We explicitly use find_first_of here, so that the resulting data may contain : as a valid character.
        auto argsEnd = commandLine.find_first_of(L":", argsStart);
        if (argsEnd == std::wstring::npos)
        {
            return {L"", L""};
        }

        if (argsStart > argsEnd)
        {
            throw std::overflow_error("commandLine");
        }

        auto argsLength = argsEnd - argsStart;
        auto dataStart = argsEnd + 1;

        return {commandLine.substr(argsStart, argsLength), commandLine.substr(dataStart)};
    }

    Windows::ApplicationModel::Activation::IActivatedEventArgs AppLifecycle::GetActivatedEventArgs()
    {
        if (HasIdentity())
        {
            return Windows::ApplicationModel::AppInstance::GetActivatedEventArgs();
        }
        else
        {
            // Generate IActivatedEventArgs for non-Packaged applications.
            std::wstring contractId;
            std::wstring contractData;
            auto commandLine = std::wstring(GetCommandLine());
            std::tie(contractId, contractData) = ParseCommandLine(commandLine);

            if (!contractId.empty())
            {
                if (contractId == c_protocolArgumentString)
                {
                    return make<ProtocolActivatedEventArgs>(contractData);
                }
                else if (contractId == c_fileArgumentString)
                {
                    return make<FileActivatedEventArgs>(contractData);
                }
            }

            return make<LaunchActivatedEventArgs>(commandLine);
        }
    }

    Microsoft::ProjectReunion::ActivationArguments AppLifecycle::GetActivatedEventArgs2()
    {
        DWORD waitResult = 0;

        // Read command line args to determine ActivationKind
        std::wstring commandLineArgs = GetCommandLine();
        auto found = commandLineArgs.find(L"-ReunionPushServer", 0);

        if (found)
        {
            if (g_waitHandleForArgs == nullptr)
            {
                winrt::throw_hresult(E_UNEXPECTED);
            }

            waitResult = WaitForSingleObject(g_waitHandleForArgs.get(), 1000);

            if (waitResult != WAIT_OBJECT_0)
            {
                IInspectable data = make<LaunchActivatedEventArgs>(commandLineArgs).as<IInspectable>();
                return make<ActivationArguments>(ExtendedActivationKind::Launch, data);
            }

            IInspectable pushData = g_activatedEventArgs.as<IInspectable>();
            return make<ActivationArguments>(ExtendedActivationKind::Push, pushData);
        }
        else
        {
            IInspectable data = make<LaunchActivatedEventArgs>(commandLineArgs).as<IInspectable>();
            return make<ActivationArguments>(ExtendedActivationKind::Launch, data);
        }
    }
}
