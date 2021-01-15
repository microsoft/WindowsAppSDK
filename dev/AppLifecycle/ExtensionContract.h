// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "FileActivatedEventArgs.h"
#include "StartupActivatedEventArgs.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    // Extension contract ids.
    static LPCWSTR c_launchContractId = L"Windows.Launch";
    static LPCWSTR c_fileContractId = L"Windows.File";
    static LPCWSTR c_protocolContractId = L"Windows.Protocol";
    static LPCWSTR c_startupTaskContractId = L"Windows.StartupTask";

    // This array holds the mapping between a class factory and it's extension contract Id.
    static const struct ExtensionMap
    {
        std::wstring contractId;
        Windows::ApplicationModel::Activation::IActivatedEventArgs(*factory)(
            Windows::ApplicationModel::Activation::IProtocolActivatedEventArgs const& args);
    }
    c_extensionMap[] =
    {
        { c_launchContractId, &LaunchActivatedEventArgs::CreateFromProtocol },
        { c_fileContractId, &FileActivatedEventArgs::CreateFromProtocol },
        { c_protocolContractId, &ProtocolActivatedEventArgs::CreateFromProtocol },
        { c_startupTaskContractId, &StartupActivatedEventArgs::CreateFromProtocol },
    };
}
