// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include <ActivationRegistrationManager.h>
#include <Microsoft.ApplicationModel.Activation.ActivationRegistrationManager.g.cpp>

#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "FileActivatedEventArgs.h"
#include "Association.h"

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    void ActivationRegistrationManager::RegisterForFileTypeActivation(
        array_view<hstring const> supportedFileTypes, array_view<hstring const> supportedVerbs,
        hstring const& applicationDisplayName, hstring const& logo)
    {
        if (HasIdentity())
        {
            throw hresult_illegal_method_call();
        }

        auto appId = ComputeAppId();
        auto type = AssociationType::File;
        auto progId = ComputeProgId(appId, type);

        if (supportedFileTypes.size())
        {
            RegisterProgId(progId.c_str(), L"", applicationDisplayName.c_str(), logo.c_str());
            RegisterApplication(appId.c_str());
        }

        for (auto extension : supportedFileTypes)
        {
            RegisterFileExtension(extension.c_str());
            
            for (auto verb : supportedVerbs)
            {
                auto command = GetModulePath();
                command += L" ----" + c_fileArgumentString + L":" + verb.c_str() + L",%1";
                RegisterVerb(progId, verb.c_str(), command);
            }

            RegisterAssociationHandler(appId, extension.c_str(), type);
        }
    }

    void ActivationRegistrationManager::RegisterForProtocolActivation(hstring const& scheme,
        hstring const& applicationDisplayName, hstring const& logo)
    {
        if (scheme.empty())
        {
            throw hresult_invalid_argument();
        }

        if (HasIdentity())
        {
            throw hresult_illegal_method_call();
        }

        RegisterProtocol(scheme.c_str());

        auto appId = ComputeAppId();
        auto type = AssociationType::Protocol;
        auto progId = ComputeProgId(appId, type);

        RegisterProgId(progId.c_str(), L"", applicationDisplayName.c_str(), logo.c_str());

        auto command = GetModulePath();
        command += L" ----" + c_protocolArgumentString + L":%1";
        RegisterVerb(progId.c_str(), L"open", command);

        RegisterApplication(appId.c_str());
        RegisterAssociationHandler(appId, scheme.c_str(), type);
    }

    void ActivationRegistrationManager::UnregisterForFileTypeActivation(hstring const& fileType)
    {
        if (HasIdentity())
        {
            throw hresult_illegal_method_call();
        }

        auto appId = ComputeAppId();
        auto type = AssociationType::File;
        auto progId = ComputeProgId(appId, type);
        UnregisterAssociationHandler(appId, fileType.c_str(), type);
        UnregisterProgId(progId);
    }

    void ActivationRegistrationManager::UnregisterForProtocolActivation(hstring const& scheme)
    {
        if (scheme.empty())
        {
            throw hresult_invalid_argument();
        }

        if (HasIdentity())
        {
            throw hresult_illegal_method_call();
        }

        auto appId = ComputeAppId();
        auto type = AssociationType::Protocol;
        auto progId = ComputeProgId(appId, type);
        UnregisterAssociationHandler(appId, scheme.c_str(), type);
        UnregisterProgId(progId);
    }
}
