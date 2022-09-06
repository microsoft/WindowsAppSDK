// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#include <pch.h>
#include <ActivationRegistrationManager.h>
#include <Microsoft.Windows.AppLifecycle.ActivationRegistrationManager.g.cpp>

#include "AppLifecycleTelemetry.h"
#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "FileActivatedEventArgs.h"
#include "Association.h"
#include "ExtensionContract.h"
#include "EncodedLaunchExecuteCommand.h"

using namespace AppModel::Identity;

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    using namespace winrt::Windows::Foundation;

    std::wstring GenerateCommandLine(std::wstring const& modulePath, std::wstring const& argumentData)
    {
        std::wstring exePath{ modulePath.empty() ? wil::GetModuleFileNameW<std::wstring>(nullptr) : modulePath };

        // Example: C:\some\path\App.exe "----ms-protocol:myscheme:some=data&some=other"
        return wil::str_printf<std::wstring>(L"%s \"%s%s%s%s\"", exePath.c_str(), c_argumentPrefix,
            c_msProtocolArgumentString, c_argumentSuffix, argumentData.c_str());
    }

    void ActivationRegistrationManager::ReportFeatureUsage()
    {
        static bool reported{ false };

        if (!reported)
        {
            AppLifecycleTelemetry::ActivationRegistrationManager();
            reported = true;
        }
    }

    void ActivationRegistrationManager::RegisterForFileTypeActivation(
        array_view<hstring const> supportedFileTypes, hstring const& logo, hstring const& displayName,
        array_view<hstring const> supportedVerbs, hstring const& exePath)
    {
        THROW_HR_IF(E_ILLEGAL_METHOD_CALL, IsPackagedProcess());
        THROW_HR_IF(E_INVALIDARG, !supportedFileTypes.size());

        auto appId = ComputeAppId(exePath.c_str());
        auto type = AssociationType::File;
        auto progId = ComputeProgId(appId, type);

        RegisterProgId(progId.c_str(), L"", L"", displayName.c_str(), logo.c_str());
        RegisterApplication(appId.c_str());

        for (auto fileType : supportedFileTypes)
        {
            RegisterFileExtension(fileType.c_str());
            
            for (auto verb : supportedVerbs)
            {
                auto args = winrt::make<FileActivatedEventArgs>(verb.c_str(), c_commandLineArgumentFormat, true).as<IInternalValueMarshalable>();
                auto command = GenerateCommandLine(exePath.c_str(), args->Serialize().AbsoluteUri().c_str());
                RegisterVerb(progId, verb.c_str(), command);
            }

            RegisterAssociationHandler(appId, fileType.c_str(), type);
        }

        // Notify Shell that an association has changed.
        NotifyShellAssocChanged();
    }

    void ActivationRegistrationManager::RegisterForProtocolActivation(hstring const& schemeName,
        hstring const& logo, hstring const& displayName, hstring const& exePath)
    {
        THROW_HR_IF(E_ILLEGAL_METHOD_CALL, IsPackagedProcess());
        THROW_HR_IF(E_INVALIDARG, schemeName.empty());

        RegisterForProtocolActivationInternal(schemeName.c_str(), L"", logo.c_str(),
            displayName.c_str(), exePath.c_str());

        // Notify Shell that an association has changed.
        NotifyShellAssocChanged();
    }

    void ActivationRegistrationManager::RegisterForStartupActivation(hstring const& taskId,
        hstring const& exePath)
    {
        THROW_HR_IF(E_ILLEGAL_METHOD_CALL, IsPackagedProcess());
        THROW_HR_IF(E_INVALIDARG, taskId.empty());

        // Example: HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
        wil::unique_hkey key;
        THROW_IF_WIN32_ERROR(::RegOpenKeyEx(HKEY_CURRENT_USER, c_runKeyPath, 0, KEY_WRITE,
            key.put()));

        // Pass a value serialized version of the arguments on the command-line.
        auto args = winrt::make<StartupActivatedEventArgs>(taskId.c_str()).as<IInternalValueMarshalable>();
        auto command = GenerateCommandLine(exePath.c_str(), args->Serialize().AbsoluteUri().c_str());

        // Name: taskId
        // Value: commandLine
        THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), taskId.c_str(), 0, REG_SZ,
            reinterpret_cast<BYTE const*>(command.c_str()),
            static_cast<uint32_t>((command.size() + 1) * sizeof(wchar_t))));
    }

    void ActivationRegistrationManager::UnregisterForFileTypeActivation(array_view<hstring const> fileTypes,
        hstring const& exePath)
    {
        THROW_HR_IF(E_ILLEGAL_METHOD_CALL, IsPackagedProcess());
        THROW_HR_IF(E_INVALIDARG, !fileTypes.size());

        auto appId = ComputeAppId(exePath.c_str());
        auto type = AssociationType::File;
        auto progId = ComputeProgId(appId, type);

        for (auto fileType : fileTypes)
        {
            UnregisterAssociationHandler(appId, fileType.c_str(), type);
            UnregisterProgId(progId);
        }

        // Notify Shell that an association has changed.
        NotifyShellAssocChanged();
    }

    void ActivationRegistrationManager::UnregisterForProtocolActivation(hstring const& schemeName,
        hstring const& exePath)
    {
        THROW_HR_IF(E_ILLEGAL_METHOD_CALL, IsPackagedProcess());
        THROW_HR_IF(E_INVALIDARG, schemeName.empty());

        auto appId = ComputeAppId(exePath.c_str());
        auto type = AssociationType::Protocol;
        auto progId = ComputeProgId(appId, type);
        UnregisterAssociationHandler(appId, schemeName.c_str(), type);
        UnregisterProgId(progId);

        // Notify Shell that an association has changed.
        NotifyShellAssocChanged();
    }

    void ActivationRegistrationManager::UnregisterForStartupActivation(hstring const& taskId)
    {
        THROW_HR_IF(E_ILLEGAL_METHOD_CALL, IsPackagedProcess());
        THROW_HR_IF(E_INVALIDARG, taskId.empty());

        // Example: HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
        wil::unique_hkey key;
        if (::RegOpenKeyEx(HKEY_CURRENT_USER, c_runKeyPath, 0, KEY_WRITE, key.put()) == ERROR_SUCCESS)
        {
            ::RegDeleteValue(key.get(), taskId.c_str());
        }
    }

    void ActivationRegistrationManager::RegisterForProtocolActivationInternal(std::wstring const& schemeName,
        std::wstring const& appUserModelId, std::wstring const& logo, std::wstring const& displayName,
        std::wstring const& exePath)
    {
        THROW_HR_IF(E_ILLEGAL_METHOD_CALL, IsPackagedProcess());
        THROW_HR_IF(E_INVALIDARG, schemeName.empty());

        RegisterProtocol(schemeName.c_str());

        auto appId = ComputeAppId(exePath.c_str());
        auto type = AssociationType::Protocol;
        auto progId = ComputeProgId(appId, type);

        RegisterProgId(progId.c_str(), L"", appUserModelId.c_str(), displayName.c_str(),
            logo.c_str());

        auto command = GenerateCommandLine(exePath.c_str(), c_commandLineArgumentFormat);
        RegisterVerb(progId.c_str(), c_openVerbName, command);

        RegisterApplication(appId.c_str());
        RegisterAssociationHandler(appId, schemeName.c_str(), type);
    }

    void ActivationRegistrationManager::RegisterEncodedLaunchCommand()
    {
        RegisterProtocol(c_launchSchemeName);

        auto delegateExecute = __uuidof(EncodedLaunchExecuteCommandFactory);
        RegisterVerb(c_launchSchemeName, c_openVerbName, L"", &delegateExecute);
    }

    void ActivationRegistrationManager::RegisterEncodedLaunchSupport(std::wstring const& appUserModelId,
        std::wstring const& exePath)
    {
        // Make sure the encoded launch delegate execute command is registered on the system.
        RegisterEncodedLaunchCommand();

        // Register the current app to receive launch requests.
        RegisterForProtocolActivationInternal(c_encodedLaunchSchemeName, appUserModelId,
            L"", L"Encoded Launch Target", exePath);
    }
}
