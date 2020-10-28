// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include <ActivationRegistrationManager.h>
#include <ActivationRegistrationManager.g.cpp>

#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "AssocCommon.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    void ActivationRegistrationManager::RegisterForFileTypeActivation(hstring const& groupName,
        hstring const& logo, array_view<hstring const> supportedFileTypes,
        array_view<hstring const> supportedVerbs)
    {
        throw hresult_not_implemented();
    }

    void ActivationRegistrationManager::RegisterForProtocolActivation(hstring const& scheme,
        hstring const& displayName)
    {
        if (scheme.empty() || displayName.empty())
        {
            throw winrt::hresult_invalid_argument();
        }

        register_protocol(scheme.c_str(), displayName.c_str());
    }

    void ActivationRegistrationManager::RegisterForStartupActivation(hstring const& taskId,
        bool isEnabled, hstring const& displayName)
    {
        throw hresult_not_implemented();
    }

    void ActivationRegistrationManager::RegisterForToastActivation(hstring const& displayName)
    {
        throw hresult_not_implemented();
    }

    void ActivationRegistrationManager::UnregisterForFileTypeActivation(hstring const& groupName)
    {
        throw hresult_not_implemented();
    }

    void ActivationRegistrationManager::UnregisterForProtocolActivation(hstring const& scheme)
    {
        if (scheme.empty())
        {
            throw winrt::hresult_invalid_argument();
        }

        unregister_protocol(scheme.c_str());
    }

    void ActivationRegistrationManager::UnregisterForStartupActivation()
    {
        throw hresult_not_implemented();
    }

    void ActivationRegistrationManager::UnregisterForToastActivation()
    {
        throw hresult_not_implemented();
    }
}
