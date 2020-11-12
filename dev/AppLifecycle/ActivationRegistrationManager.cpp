// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include <ActivationRegistrationManager.h>
#include <Activation.ActivationRegistrationManager.g.cpp>

#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "FileActivatedEventArgs.h"
#include "Association.h"

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    void ActivationRegistrationManager::RegisterForFileTypeActivation(
        array_view<hstring const> supportedFileTypes, array_view<hstring const> supportedVerbs,
        hstring const& logo)
    {
        if (HasIdentity())
        {
            throw hresult_illegal_method_call();
        }

        for (auto extension : supportedFileTypes)
        {
            RegisterFileExtension(extension.c_str());

            for (auto verb : supportedVerbs)
            {
                // TODO: Add support for the logo
                auto type = AssociationType::File;
                auto progId = ComputeProgId(type);
                RegisterApplication(progId);

                auto command = GetModulePath();
                command += L" ----" + c_fileArgumentString + L":" + verb.c_str() + L",%1";
                RegisterVerb(progId, verb.c_str(), command);
                RegisterAssociationHandler(extension.c_str(), type, progId);
            }
        }
    }

    void ActivationRegistrationManager::RegisterForProtocolActivation(hstring const& scheme,
        hstring const& displayName, hstring const& logo)
    {
        if (scheme.empty() || displayName.empty())
        {
            throw hresult_invalid_argument();
        }

        if (HasIdentity())
        {
            throw hresult_illegal_method_call();
        }

        RegisterProtocol(scheme.c_str(), displayName.c_str());

        auto type = AssociationType::Protocol;
        auto progId = ComputeProgId(type);
        RegisterApplication(progId);
        RegisterAssociationHandler(scheme.c_str(), type, progId);

        // TODO: Set logo

        auto command = GetModulePath();
        command += L" ----" + c_protocolArgumentString + L":%1";
        RegisterVerb(progId.c_str(), L"open", command);
        
    }

    void ActivationRegistrationManager::UnregisterForFileTypeActivation(hstring const& fileType)
    {
        if (HasIdentity())
        {
            throw hresult_illegal_method_call();
        }

        auto type = AssociationType::File;
        auto progId = ComputeProgId(type);
        UnregisterAssociationHandler(fileType.c_str(), type, progId);
        UnregisterProgId(progId);
        UnregisterFileExtension(fileType.c_str());
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

        // TODO: Fix this
        UnregisterProgId(scheme.c_str());
    }
}
