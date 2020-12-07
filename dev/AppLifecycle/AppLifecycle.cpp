// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <AppLifecycle.h>
#include <AppLifecycle.g.cpp>
#include <iostream>
#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "FileActivatedEventArgs.h"
#include "Association.h"

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
        std::cout << "Starting" << std::endl;
        if (HasIdentity())
        {
            std::cout << "HasIdentity" << std::endl;
            return Windows::ApplicationModel::AppInstance::GetActivatedEventArgs();
        }
        else
        {
            // Generate IActivatedEventArgs for non-Packaged applications.
            std::wstring contractId;
            std::wstring contractData;
            auto commandLine = std::wstring(GetCommandLine());
            std::tie(contractId, contractData) = ParseCommandLine(commandLine);
            std::cout << "Has NO Identity" << std::endl;
            if (!contractId.empty())
            {
                if (contractId == c_protocolArgumentString)
                {
                    std::cout << "ProtocolActivatedEventArgs" << std::endl;
                    return make<ProtocolActivatedEventArgs>(contractData);
                }
                else if (contractId == c_fileArgumentString)
                {
                    std::cout << "FileActivatedEventArgs" << std::endl;
                    return make<FileActivatedEventArgs>(contractData);
                }
            }
            std::cout << "LaunchActivatedEventArgs" << std::endl;
            return make<LaunchActivatedEventArgs>(commandLine);
        }
    }
}
