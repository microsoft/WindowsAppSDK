// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <AppLifecycle.h>
#include <Microsoft.ApplicationModel.Activation.AppLifecycle.g.cpp>

#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "FileActivatedEventArgs.h"
#include "StartupActivatedEventArgs.h"
#include "Association.h"

namespace winrt
{
    using namespace Windows::Foundation;
    using Windows::ApplicationModel::Activation::IActivatedEventArgs;
}

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    std::tuple<std::wstring, std::wstring> ParseCommandLine(std::wstring commandLine)
    {
        auto argsStart = commandLine.rfind(c_argumentPrefix);
        if (argsStart == std::wstring::npos)
        {
            return {L"", L""};
        }

        argsStart += 4;

        // We explicitly use find_first_of here, so that the resulting data may contain : as a valid character.
        auto argsEnd = commandLine.find_first_of(c_argumentSuffix, argsStart);
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

    IActivatedEventArgs AppLifecycle::GetActivatedEventArgs()
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
                else if (contractId == c_startupArgumentString)
                {
                    return make<StartupActivatedEventArgs>(contractData);
                }
            }

            return make<LaunchActivatedEventArgs>(commandLine);
        }
    }
}
