// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <AppLifecycle.h>
#include <AppLifecycle.g.cpp>

#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "Shared.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    std::tuple<std::wstring, std::wstring> AppLifecycle::ParseCommandLine(std::wstring commandLine)
    {
        auto argsStart = commandLine.rfind(L"----") + 4;

        // We explicitly use find_first_of here, so that the resulting data may contain : as a valid character.
        auto argsEnd = commandLine.find_first_of(L":", argsStart);
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

            if (contractId.compare(MS_PROTOCOL_ARG_STR) == 0)
            {
                return winrt::make<ProtocolActivatedEventArgs>(contractData);
            }

            return winrt::make<LaunchActivatedEventArgs>(commandLine);
        }
    }
}
