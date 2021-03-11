// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <AppLifecycle.h>
#include <Microsoft.Windows.AppLifecycle.AppLifecycle.g.cpp>

#include "ActivationRegistrationManager.h"
#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "FileActivatedEventArgs.h"
#include "StartupActivatedEventArgs.h"
#include "Association.h"
#include "ExtensionContract.h"

namespace winrt
{
    using namespace Windows::Foundation;
    using Windows::ApplicationModel::Activation::IActivatedEventArgs;
}

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
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

    bool IsEncodedLaunch(IProtocolActivatedEventArgs const& args)
    {
        return CompareStringOrdinal(args.Uri().SchemeName().c_str(), -1, c_encodedLaunchSchemeName,
            -1, TRUE) == CSTR_EQUAL;
    }

    IActivatedEventArgs GetEncodedLaunchActivatedEventArgs(IProtocolActivatedEventArgs const& args)
    {
        for (auto const& pair : args.Uri().QueryParsed())
        {
            if (CompareStringOrdinal(pair.Name().c_str(), -1, c_contractIdKeyName, -1, TRUE)
                == CSTR_EQUAL)
            {
                for (int index = 0; index < _countof(c_extensionMap); index++)
                {
                    std::wstring contractId = pair.Value().c_str();
                    if (CompareStringOrdinal(contractId.c_str(), -1,
                        c_extensionMap[index].contractId.c_str(), -1, TRUE) == CSTR_EQUAL)
                    {
                        return c_extensionMap[index].factory(args);
                    }
                }
            }
        }

        // Let the caller args pass through if nothing was determined here.
        return args;
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

            // All specific launch types are encoded as a URI and transported as a
            // protocol, except the catch-all LaunchActivatedEventArgs case.
            if (!contractId.empty() && (CompareStringOrdinal(contractId.c_str(), -1,
                c_protocolArgumentString, -1, TRUE) == CSTR_EQUAL))
            {
                auto args = make<ProtocolActivatedEventArgs>(contractData);
                auto protocolArgs = args.as<IProtocolActivatedEventArgs>();

                // Encoded launch is a protocol launch where the argument data is
                // encapsulated in the Uri Query data.  We handle that here and
                // try to return the correct IActivatedEventArgs type that is
                // encoded in the data rather than the IProtocolActivatedEventArgs
                // itself.
                if (IsEncodedLaunch(protocolArgs))
                {
                    return GetEncodedLaunchActivatedEventArgs(protocolArgs);
                }

                return args;
            }

            return make<LaunchActivatedEventArgs>(commandLine);
        }
    }
}
