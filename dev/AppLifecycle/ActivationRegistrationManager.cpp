// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include <ActivationRegistrationManager.h>
#include <ActivationRegistrationManager.g.cpp>

#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "FileActivatedEventArgs.h"
#include "Shared.h"

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    void ActivationRegistrationManager::RegisterForFileTypeActivation(hstring const& groupName,
        hstring const& logo, array_view<hstring const> supportedFileTypes,
        array_view<hstring const> supportedVerbs)
    {
        if (groupName.empty())
        {
            throw hresult_invalid_argument();
        }

        if (HasIdentity())
        {
            throw hresult_illegal_method_call();
        }

        for (auto extension : supportedFileTypes)
        {
            RegisterFileExtension(extension.c_str());

            for (auto verb : supportedVerbs)
            {
                // TODO: Add support for the logo and groupName
                RegisterFileHandler(extension.c_str(), verb.c_str());
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
    }

    void ActivationRegistrationManager::UnregisterForFileTypeActivation(hstring const& groupName,
        hstring const& fileType)
    {
        if (groupName.empty())
        {
            throw hresult_invalid_argument();
        }

        if (HasIdentity())
        {
            throw hresult_illegal_method_call();
        }

        // TODO: Support groups
        UnregisterFileHandler(fileType.c_str());
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

        UnregisterProtocol(scheme.c_str());
    }
}
