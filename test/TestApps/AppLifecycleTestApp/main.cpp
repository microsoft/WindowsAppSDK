// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include "pch.h"
#include <testdef.h>
#include "Helpers.h"
#include "SingleInstanceTest.h"
#include "RequestRestartTest.h"

using namespace AppModel::Identity;

using namespace winrt::Microsoft::Windows::AppLifecycle;
using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::ApplicationModel::Activation;

bool ProtocolLaunchSucceeded(const AppActivationArguments& appArgs)
{
    auto expectedScheme = Test::AppModel::IsPackagedProcess() ? c_testProtocolScheme_Packaged : c_testProtocolScheme;
    auto actualUri = appArgs.Data().as<IProtocolActivatedEventArgs>().Uri();

    // We only support our test protocol.
    if (expectedScheme.compare(actualUri.SchemeName().c_str()) != 0)
    {
        return false;
    }

    if (c_genericTestMoniker.compare(actualUri.Host().c_str()) != 0)
    {
        return false;
    }

    // Just succeed for the protocol activation tests, as that is the proof we needed.
    std::wstring actualTestName = actualUri.QueryParsed().GetFirstValueByName(L"TestName").c_str();
    if (actualTestName.compare(L"GetActivatedEventArgsForProtocol_Win32") == 0 || actualTestName.compare(L"GetActivatedEventArgsForProtocol_PackagedWin32") == 0)
    {
        return true;
    }

    if ((actualTestName.compare(L"SingleInstanceTest_Win32") == 0 || actualTestName.compare(L"SingleInstanceTest_PackagedWin32") == 0) &&
        SingleInstanceTestSucceeded(appArgs))
    {
        return true;
    }

    if ((actualTestName.compare(L"RequestRestart_Win32") == 0 || actualTestName.compare(L"RequestRestart_PackagedWin32") == 0) &&
        RunRequestRestartTestSucceeded(appArgs))
    {
        // N.B. This test is actually terminated by the new process spawned by RunRequestRestartTestSucceeded().  So we don't make it to this code.
        return true;
    }

    return false;
}

int main()
{
    RETURN_IF_FAILED(BootstrapInitialize());

    auto succeeded = false;
    auto args = AppInstance::GetCurrent().GetActivatedEventArgs();
    auto kind = args.Kind();
    if (kind == ExtendedActivationKind::Launch)
    {
        auto launchArgs = args.Data().as<ILaunchActivatedEventArgs>();
        auto commandLine = std::wstring(launchArgs.Arguments().c_str());
        auto argStart = commandLine.rfind(L"/") + 1;
        if (argStart != std::wstring::npos)
        {
            auto argument = commandLine.substr(argStart);

            if (argument.compare(L"RegisterProtocol") == 0)
            {
                ActivationRegistrationManager::RegisterForProtocolActivation(c_testProtocolScheme, L"logo",
                    L"Windows App SDK Test Protocol", L"");

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
                    L"logo", L"Windows App SDK Test File Type", { L"open" }, L"");

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
                ActivationRegistrationManager::RegisterForStartupActivation(c_genericTestMoniker.c_str(), L"");

                // Signal event that file was registered.
                SignalPhase(c_testStartupPhaseEventName);
                succeeded = true;
            }
            else if (argument.compare(L"UnregisterStartup") == 0)
            {
                ActivationRegistrationManager::UnregisterForStartupActivation(c_genericTestMoniker.c_str());

                // Signal event that file was unregistered.
                SignalPhase(c_testStartupPhaseEventName);
                succeeded = true;
            }
            else if (argument.compare(L"RequestRestartNowCalled") == 0)
            {
                if (IsPackagedProcess())
                {
                    SignalPhase(c_testRequestRestartNowRestartedPhasePackagedEventName);
                }
                else
                {
                    SignalPhase(c_testRequestRestartNowRestartedPhaseEventName);
                }

                succeeded = true;
            }
        }
    }
    else if (kind == ExtendedActivationKind::Protocol)
    {
        if (ProtocolLaunchSucceeded(args))
        {
            // Signal event that protocol was activated and valid.
            SignalPhase(c_testProtocolPhaseEventName);
            succeeded = true;
        }
    }
    else if (kind == ExtendedActivationKind::File)
    {
        // Validate access to the files on the arguments.
        auto fileArgs = args.Data().as<IFileActivatedEventArgs>();
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
        auto startupArgs = args.Data().as<IStartupTaskActivatedEventArgs>();
        if (c_genericTestMoniker.compare(startupArgs.TaskId().c_str()) == 0)
        {
            // Signal event that startuptask was activated.
            SignalPhase(c_testStartupPhaseEventName);
            succeeded = true;
        }
    }
    else if (kind == ExtendedActivationKind::Push)
    {
        if (args.Data() != nullptr)
        {
            // Signal event that the was correctly activated through push.
            SignalPhase(c_testPushPhaseEventName);
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
