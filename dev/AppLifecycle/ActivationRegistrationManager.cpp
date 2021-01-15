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
    std::wstring GenerateCommandLine(std::wstring const& modulePath, std::wstring const& contractType)
    {
        std::wstring command = modulePath;

        if (modulePath.empty())
        {
            command = GetModulePath();
        }

        command += L" " + c_argumentPrefix + contractType + c_argumentSuffix;
        return command;
    }

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
                auto command = GenerateCommandLine(L"", c_fileArgumentString) + verb.c_str() + L",%1";
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

        auto command = GenerateCommandLine(L"", c_protocolArgumentString) + L"%1";
        RegisterVerb(progId.c_str(), L"open", command);

        RegisterApplication(appId.c_str());
        RegisterAssociationHandler(appId, scheme.c_str(), type);
    }

    void ActivationRegistrationManager::RegisterForStartupActivation(hstring const& taskId,
        bool isEnabled)
    {
        if (HasIdentity())
        {
            throw hresult_illegal_method_call();
        }

        // Example: HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
        wil::unique_hkey key;
        THROW_IF_WIN32_ERROR(::RegOpenKeyEx(HKEY_CURRENT_USER, c_runKeyPath.c_str(), 0, KEY_WRITE,
            key.put()));

        // Pass a command line that will make sense while constructing the args object.
        auto command = GenerateCommandLine(L"", c_startupArgumentString) + taskId;

        // Name: taskId
        // Value: commandLine
        THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), taskId.c_str(), 0, REG_SZ,
            reinterpret_cast<BYTE const*>(command.c_str()),
            static_cast<uint32_t>((command.size() + 1) * sizeof(wchar_t))));

        if (!isEnabled)
        {
            // The enabled state is the system default, and so we only write out data
            // in the case of disabled.
            BlockedItem itemState{};

            itemState.flags = BlockedItemStatus::Blocked | BlockedItemStatus::Seen;
            ::GetSystemTimeAsFileTime(&itemState.disabledTime);

            // Example: HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Explorer\StartupApproved\Run
            wil::unique_hkey approvedKey;
            THROW_IF_WIN32_ERROR(::RegOpenKeyEx(HKEY_CURRENT_USER, c_startupApprovedKeyPath.c_str(),
                0, KEY_WRITE, approvedKey.put()));

            THROW_IF_WIN32_ERROR(::RegSetValueEx(approvedKey.get(), taskId.c_str(), 0, REG_BINARY,
                reinterpret_cast<BYTE const*>(&itemState),
                sizeof(BlockedItem)));
        }
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

    void ActivationRegistrationManager::UnregisterForStartupActivation(hstring const& taskId)
    {
        if (HasIdentity())
        {
            throw hresult_illegal_method_call();
        }

        // Example: HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
        wil::unique_hkey key;
        if (::RegOpenKeyEx(HKEY_CURRENT_USER, c_runKeyPath.c_str(), 0, KEY_WRITE, key.put())
            == ERROR_SUCCESS)
        {
            ::RegDeleteValue(key.get(), taskId.c_str());
        }

        // TODO: Cleanup disabled value -- Maybe...
    }

}
