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
    void ActivationRegistrationManager::RegisterForFileTypeActivation(hstring const& logo,
        array_view<hstring const> supportedFileTypes, array_view<hstring const> supportedVerbs)
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
                auto progId = ComputeProgId();
                RegisterProgId(progId, L"");

                auto command = GetModulePath();
                command += L" ----" + c_fileArgumentString + L":" + verb.c_str() + L",%1";
                RegisterVerb(progId, verb.c_str(), command);
                RegisterProgidAsHandler(extension.c_str(), progId);
            }
        }
    }

    void ActivationRegistrationManager::RegisterForProtocolActivation(hstring const& scheme,
        hstring const& displayName)
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

        auto progId = ComputeProgId();
        RegisterApplication(ComputeProgId());

        // TODO: Register the generated progId and capabilities.
        auto command = GetModulePath();
        command += L" ----" + c_protocolArgumentString + L":%1";
        RegisterVerb(scheme.c_str(), L"open", command);
    }

    void ActivationRegistrationManager::UnregisterForFileTypeActivation(hstring const& fileType)
    {
        if (HasIdentity())
        {
            throw hresult_illegal_method_call();
        }

        auto progId = ComputeProgId();
        UnregisterProgidAsHandler(fileType.c_str(), progId);
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

        UnregisterProgId(scheme.c_str());
    }
}
