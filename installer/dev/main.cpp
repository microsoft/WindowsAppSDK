// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "console.h"
#include "install.h"
#include "resource.h"

#ifndef GUID_NULL
struct __declspec(uuid("00000000-0000-0000-0000-000000000000")) GUID_NULL;
#define GUID_NULL __uuidof(struct GUID_NULL)
#endif

using namespace winrt;

using namespace WindowsAppRuntimeInstaller::Console;

int wmain(int argc, wchar_t *argv[])
{
    init_apartment();

    auto& installActivityContext{ WindowsAppRuntimeInstaller::InstallActivity::Context::Get() };
    const bool isElevated{ Security::IntegrityLevel::IsElevated() };

    // Set a process-wide callback function for WIL to call each time it logs a failure.
    wil::SetResultLoggingCallback(wilResultLoggingCallback);

    // Register WindowsAppRuntime Installer event source to log it's events to %Windir%\System32\WinEvt\Logs\Application.Evtx
    LOG_LAST_ERROR_IF_NULL(WindowsAppRuntimeInstaller::InstallActivity::Context::Get().RegisterInstallerEventSourceW());

    WindowsAppRuntimeInstaller::Options options{};
    bool installAsDefaultOption{ true };

    std::wstringstream args{};

    for (int i = 1; i < argc; ++i)
    {
        auto arg{ std::wstring_view(argv[i]) };

        if (arg == L"--dry-run")
        {
            WI_SetFlag(options, WindowsAppRuntimeInstaller::Options::DryRun);
        }
        else if (arg == L"--license")
        {
            WI_SetFlag(options, WindowsAppRuntimeInstaller::Options::InstallLicenses);
            installAsDefaultOption = false;
        }
        else if (arg == L"--license-")
        {
            WI_ClearFlag(options, WindowsAppRuntimeInstaller::Options::InstallLicenses);
        }
        else if (arg == L"--msix")
        {
            WI_SetFlag(options, WindowsAppRuntimeInstaller::Options::InstallPackages);
            installAsDefaultOption = false;
        }
        else if (arg == L"--msix-")
        {
            WI_ClearFlag(options, WindowsAppRuntimeInstaller::Options::InstallPackages);
        }
        else if ((arg == L"-q") || (arg == L"--quiet"))
        {
            WI_SetFlag(options, WindowsAppRuntimeInstaller::Options::Quiet);
        }
        else if ((arg == L"-q-") || (arg == L"--quiet-"))
        {
            WI_ClearFlag(options, WindowsAppRuntimeInstaller::Options::Quiet);
        }
        else if ((arg == L"-f") || (arg == L"--force"))
        {
            WI_SetFlag(options, WindowsAppRuntimeInstaller::Options::ForceDeployment);
        }
        else if ((arg == L"-f-") || (arg == L"--force-"))
        {
            WI_ClearFlag(options, WindowsAppRuntimeInstaller::Options::ForceDeployment);
        }
        else if ((arg == L"-r") || (arg == L"--repair"))
        {
            WI_SetFlag(options, WindowsAppRuntimeInstaller::Options::Repair);
            installAsDefaultOption = false;
        }
        else if ((arg == L"-r-") || (arg == L"--repair-"))
        {
            WI_ClearFlag(options, WindowsAppRuntimeInstaller::Options::Repair);
        }
        else if ((arg == L"-?") || (arg == L"--help"))
        {
            DisplayHelp();
            return 0;
        }
        else if ((arg == L"--info"))
        {
            DisplayInfo();
            return 0;
        }
        else
        {
            if (WI_IsFlagClear(options, WindowsAppRuntimeInstaller::Options::Quiet))
            {
                std::wcerr << "Unknown argument: " << arg.data() << std::endl;
                DisplayHelp();
            }

            installActivityContext.SetActivity(WindowsAppRuntimeInstaller_TraceLogger::Install::Start(args.str().c_str(),
                                                                                                    static_cast<UINT32>(options),
                                                                                                    isElevated,
                                                                                                    installActivityContext.IsLocalSystemUser()));
            LOG_IF_WIN32_BOOL_FALSE(installActivityContext.LogInstallerCommandLineArgs(args.str().c_str()));
            LOG_IF_WIN32_BOOL_FALSE(installActivityContext.LogInstallerFailureEvent(HRESULT_FROM_WIN32(ERROR_BAD_ARGUMENTS)));
            installActivityContext.GetActivity().Stop(HRESULT_FROM_WIN32(ERROR_BAD_ARGUMENTS));
            return HRESULT_FROM_WIN32(ERROR_BAD_ARGUMENTS);
        }

        // Capture valid arguments only
        args << argv[i] << " ";
    }

    if (installAsDefaultOption)
    {
        options = options | WindowsAppRuntimeInstaller::Options::Install;
    }

    installActivityContext.SetActivity(WindowsAppRuntimeInstaller_TraceLogger::Install::Start(args.str().c_str(),
                                                                                        static_cast<UINT32>(options),
                                                                                        isElevated,
                                                                                        installActivityContext.IsLocalSystemUser()));
    LOG_IF_WIN32_BOOL_FALSE(installActivityContext.LogInstallerCommandLineArgs(args.str().c_str()));
    args.clear();

    const bool quiet{ WI_IsFlagSet(options, WindowsAppRuntimeInstaller::Options::Quiet) };
    if (!isElevated && !quiet)
    {
        std::wcout << "INFO: Provisioning of WindowsAppSDK packages will be skipped as it requires elevation." << std::endl;
    }

    const HRESULT deployPackagesResult{ WindowsAppRuntimeInstaller::Deploy(options) };

    if (SUCCEEDED(deployPackagesResult))
    {
        if (!quiet)
        {
            std::wcout << "All install operations successful." << std::endl;
        }
        LOG_IF_WIN32_BOOL_FALSE(installActivityContext.LogInstallerSuccess());

        installActivityContext.GetActivity().StopWithResult(
            deployPackagesResult,
            static_cast <UINT32>(0),
            static_cast<PCSTR>(nullptr),
            static_cast <unsigned int>(0),
            static_cast<PCWSTR>(nullptr),
            static_cast<UINT32>(WindowsAppRuntimeInstaller::InstallActivity::InstallStage::None),
            static_cast<PCWSTR>(nullptr),
            S_OK,
            static_cast<PCWSTR>(nullptr),
            GUID_NULL,
            static_cast<PCWSTR>(nullptr));
    }
    else
    {
        if (!quiet)
        {
            std::wcerr << "One or more install operations failed. Result: 0x" << std::hex << deployPackagesResult << std::endl;
        }
        LOG_IF_WIN32_BOOL_FALSE(installActivityContext.LogInstallerFailureEvent(deployPackagesResult));

        installActivityContext.GetActivity().StopWithResult(
            deployPackagesResult,
            static_cast<UINT32>(installActivityContext.GetLastFailure().type),
            installActivityContext.GetLastFailure().file.c_str(),
            installActivityContext.GetLastFailure().lineNumber,
            installActivityContext.GetLastFailure().message.c_str(),
            static_cast<UINT32>(installActivityContext.GetInstallStage()),
            installActivityContext.GetCurrentResourceId().c_str(),
            installActivityContext.GetDeploymentErrorHresult(),
            installActivityContext.GetDeploymentErrorText().c_str(),
            installActivityContext.GetDeploymentErrorActivityId(),
            installActivityContext.GetExistingPackageIfHigherVersion().c_str());
    }

    LOG_IF_WIN32_BOOL_FALSE(WindowsAppRuntimeInstaller::InstallActivity::Context::Get().DeregisterInstallerEventSourceW());
    return deployPackagesResult;
}
