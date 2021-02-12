// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <testdef.h>

#include <MddBootstrap.h>
#include <MddBootstrapTest.h>

#include <wil/win32_helpers.h>

namespace TA = ::Test::AppModel;
namespace TB = ::Test::Bootstrap;

using namespace winrt::Microsoft::ApplicationModel::Activation;
using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;

HRESULT BootstrapInitialize()
{
    if (!TB::NeedDynamicDependencies())
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
    if (!TB::NeedDynamicDependencies())
    {
        return S_OK;
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
    auto args = AppLifecycle::GetActivatedEventArgs();
    auto kind = args.Kind();
    if (kind == ActivationKind::Launch)
    {
        auto launchArgs = args.as<ILaunchActivatedEventArgs>();
        auto commandLine = std::wstring(launchArgs.Arguments().c_str());
        auto argStart = commandLine.rfind(L"/") + 1;
        if (argStart != std::wstring::npos)
        {
            auto argument = commandLine.substr(argStart);

            if (argument.compare(L"RegisterProtocol") == 0)
            {
                ActivationRegistrationManager::RegisterForProtocolActivation(c_testProtocolScheme,
                    L"Project Reunion Test Protocol", L"logo");

                // Signal event that protocol was registered.
                SignalPhase(c_testProtocolPhaseEventName);
                succeeded = true;
            }
            else if (argument.compare(L"UnregisterProtocol") == 0)
            {
                ActivationRegistrationManager::UnregisterForProtocolActivation(c_testProtocolScheme);

                // Signal event that protocol was unregistered.
                SignalPhase(c_testProtocolPhaseEventName);
                succeeded = true;
            }
            else if (argument.compare(L"RegisterFile") == 0)
            {
                ActivationRegistrationManager::RegisterForFileTypeActivation({ c_testFileExtension.c_str() },
                    { L"open" }, L"Project Reunion Test File Type", L"logo");

                // Signal event that file was registered.
                SignalPhase(c_testFilePhaseEventName);
                succeeded = true;
            }
            else if (argument.compare(L"UnregisterFile") == 0)
            {
                ActivationRegistrationManager::UnregisterForFileTypeActivation(c_testFileExtension);

                // Signal event that file was unregistered.
                SignalPhase(c_testFilePhaseEventName);
                succeeded = true;
            }
        }
    }
    else if (kind == ActivationKind::Protocol)
    {
        auto protocolArgs = args.as<IProtocolActivatedEventArgs>();

        std::wstring expectedUri;
        if (TA::IsPackagedProcess())
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
    else if (kind == ActivationKind::File)
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

    if (!succeeded)
    {
        SignalPhase(c_testFailureEventName);
    }

    BootstrapShutdown();
    return 0;
}
