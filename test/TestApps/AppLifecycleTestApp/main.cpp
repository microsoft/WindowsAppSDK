// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <testdef.h>

#include <MddBootstrap.h>
#include <MddBootstrapTest.h>

#include <wil/win32_helpers.h>

using namespace winrt::Microsoft::ApplicationModel::Activation;
using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;

bool IsPackagedProcess()
{
    UINT32 n{};
    return ::GetCurrentPackageFullName(&n, nullptr) == ERROR_INSUFFICIENT_BUFFER;;
}

bool NeedDynamicDependencies()
{
    return !IsPackagedProcess();
}

HRESULT BootstrapInitialize()
{
    if (!NeedDynamicDependencies())
    {
        return S_OK;
    }

    constexpr PCWSTR c_PackageNamePrefix{ L"ProjectReunion.Test.DDLM" };
    constexpr PCWSTR c_PackagePublisherId{ L"8wekyb3d8bbwe" };
    RETURN_IF_FAILED(MddBootstrapTestInitialize(c_PackageNamePrefix, c_PackagePublisherId));

    // Version <major>.0.0.0 to find any framework package for this major version
    const UINT64 c_Version_Major{ 4 };
    PACKAGE_VERSION minVersion{ static_cast<UINT64>(c_Version_Major) << 48 };
    RETURN_IF_FAILED(MddBootstrapInitialize(minVersion));

    return S_OK;
}

void BootstrapShutdown()
{
    if (!NeedDynamicDependencies())
    {
        return;
    }

    MddBootstrapShutdown();
}

void SignalPhase(const std::wstring& phaseEventName)
{
    wil::unique_event phaseEvent;
    if (phaseEvent.try_open(phaseEventName.c_str(), EVENT_MODIFY_STATE, false))
    {
        phaseEvent.SetEvent();
    }
}

int main()
{
    RETURN_IF_FAILED(BootstrapInitialize());

    auto succeeded = false;
    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();
    if (kind == ExtendedActivationKind::Launch)
    {
        auto launchArgs = args.as<ILaunchActivatedEventArgs>();
        auto commandLine = std::wstring(launchArgs.Arguments().c_str());
        auto argStart = commandLine.rfind(L"/") + 1;
        if (argStart != std::wstring::npos)
        {
            auto argument = commandLine.substr(argStart);

            if (argument.compare(L"RegisterProtocol") == 0)
            {
                ActivationRegistrationManager::RegisterForProtocolActivation(c_testProtocolScheme, L"logo",
                    L"Project Reunion Test Protocol", L"");

                // Signal event that protocol was registered.
                SignalPhase(c_testProtocolPhaseEventName);
                succeeded = true;
            }
            else if (argument.compare(L"UnregisterProtocol") == 0)
            {
                try
                {
                    ActivationRegistrationManager::UnregisterForProtocolActivation(c_testProtocolScheme, L"");

                    // Signal event that protocol was unregistered.
                    SignalPhase(c_testProtocolPhaseEventName);
                    succeeded = true;
                }
                catch (...)
                {
                    //TODO:Unregister should not fail if ERROR_FILE_NOT_FOUND | ERROR_PATH_NOT_FOUND
                }
            }
            else if (argument.compare(L"RegisterFile") == 0)
            {
                ActivationRegistrationManager::RegisterForFileTypeActivation({ c_testFileExtension.c_str() },
                    L"logo", L"Project Reunion Test File Type", { L"open" }, L"");

                // Signal event that file was registered.
                SignalPhase(c_testFilePhaseEventName);
                succeeded = true;
            }
            else if (argument.compare(L"UnregisterFile") == 0)
            {
                try
                {
                    ActivationRegistrationManager::UnregisterForFileTypeActivation({ c_testFileExtension.c_str() },
                        L"");

                    // Signal event that file was unregistered.
                    SignalPhase(c_testFilePhaseEventName);
                    succeeded = true;
                }
                catch (...)
                {
                    //TODO:Unregister should not fail if ERROR_FILE_NOT_FOUND | ERROR_PATH_NOT_FOUND
                }
            }
            else if (argument.compare(L"RegisterStartup") == 0)
            {
                ActivationRegistrationManager::RegisterForStartupActivation(L"this_is_a_test", L"");

                // Signal event that file was registered.
                SignalPhase(c_testStartupPhaseEventName);
                succeeded = true;
            }
            else if (argument.compare(L"UnregisterStartup") == 0)
            {
                ActivationRegistrationManager::UnregisterForStartupActivation(L"this_is_a_test");

                // Signal event that file was unregistered.
                SignalPhase(c_testStartupPhaseEventName);
                succeeded = true;
            }
        }
    }
    else if (kind == ExtendedActivationKind::Protocol)
    {
        auto protocolArgs = args.as<IProtocolActivatedEventArgs>();

        std::wstring expectedUri;
        if (IsPackagedProcess())
        {
            expectedUri = c_testProtocolScheme_Packaged + L"://this_is_a_test";
        }
        else
        {
            expectedUri = c_testProtocolScheme + L"://this_is_a_test";
        }

        auto actualUri = protocolArgs.Uri();
        if (actualUri.Equals(Uri(expectedUri)))
        {
            // Signal event that protocol was activated and valid.
            SignalPhase(c_testProtocolPhaseEventName);
            succeeded = true;
        }
    }
    else if (kind == ExtendedActivationKind::File)
    {
        // Validate access to the files on the arguments.
        auto fileArgs = args.as<IFileActivatedEventArgs>();
        for (auto const& item : fileArgs.Files())
        {
            auto file = item.as<StorageFile>();
            auto stream = file.OpenAsync(FileAccessMode::Read).get();

            const uint32_t streamSize = static_cast<unsigned int>(stream.Size());
            Buffer buffer(streamSize);

            stream.ReadAsync(buffer, streamSize, InputStreamOptions::None).get();
        }

        // Signal event that file was activated.
        SignalPhase(c_testFilePhaseEventName);
        succeeded = true;
    }
    else if (kind == ExtendedActivationKind::StartupTask)
    {
        auto startupArgs = args.as<IStartupTaskActivatedEventArgs>();
        if (startupArgs.TaskId() == L"this_is_a_test")
        {
            // Signal event that startuptask was activated.
            SignalPhase(c_testStartupPhaseEventName);
            succeeded = true;
        }
    }

    if (!succeeded)
    {
        SignalPhase(c_testFailureEventName);
    }

    BootstrapShutdown();
    return 0;
}
