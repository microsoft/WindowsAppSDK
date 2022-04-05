// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "console.h"
#include "install.h"
#include "resource.h"

using namespace winrt;

using namespace WindowsAppRuntimeInstaller::Console;

int wmain(int argc, wchar_t *argv[])
{
    init_apartment();

    // Set a process-wide callback function for WIL to call each time it logs a failure.
    wil::SetResultLoggingCallback(wilResultLoggingCallback);

    auto options{ WindowsAppRuntimeInstaller::Options::InstallPackages |
                  WindowsAppRuntimeInstaller::Options::InstallLicenses };

    std::wstringstream args{};

    for (int i = 1; i < argc; ++i)
    {
        auto arg = std::wstring_view(argv[i]);

        if (arg == L"--dry-run")
        {
            WI_SetFlag(options, WindowsAppRuntimeInstaller::Options::DryRun);
        }
        else if (arg == L"--license")
        {
            WI_SetFlag(options, WindowsAppRuntimeInstaller::Options::InstallLicenses);
        }
        else if (arg == L"--license-")
        {
            WI_ClearFlag(options, WindowsAppRuntimeInstaller::Options::InstallLicenses);
        }
        else if (arg == L"--msix")
        {
            WI_SetFlag(options, WindowsAppRuntimeInstaller::Options::InstallPackages);
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
        else if ((arg == L"-?") || (arg == L"--help"))
        {
            DisplayHelp();
            return 1;
        }
        else if ((arg == L"--info"))
        {
            DisplayInfo();
            return 0;
        }
        else
        {
            std::wcerr << "Unknown argument: " << arg.data() << std::endl;
            DisplayHelp();
            return ERROR_BAD_ARGUMENTS;
        }

        // Capture valid arguments only
        args << argv[i] << " ";
    }

    auto& installActivityContext{ WindowsAppRuntimeInstaller::InstallActivity::Context::Get() };

    bool isElevated = Security::IntegrityLevel::IsElevated();
    installActivityContext.SetActivity(WindowsAppRuntimeInstaller_TraceLogger::Install::Start(args.str().c_str(), static_cast<UINT32>(options), isElevated));
    args.clear();

    if (!isElevated)
    {
        std::wcout << std::endl << "INFO: Provisioning of WindowsAppSDK packages will be skipped as it requires elevation." << std::endl;
    }

    const HRESULT deployPackagesResult{ WindowsAppRuntimeInstaller::Deploy(options) };
    if (WI_IsFlagClear(options, WindowsAppRuntimeInstaller::Options::Quiet))
    {
        if (SUCCEEDED(deployPackagesResult))
        {
            std::wcout << "All install operations successful." << std::endl;

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
                GUID_NULL);
        }
        else
        {
            std::wcerr << "One or more install operations failed. Result: 0x" << std::hex << deployPackagesResult << std::endl;

            installActivityContext.GetActivity().StopWithResult(
                deployPackagesResult,
                static_cast<UINT32>(installActivityContext.GetLastFailure().type),
                installActivityContext.GetLastFailure().file.c_str(),
                installActivityContext.GetLastFailure().lineNumer,
                installActivityContext.GetLastFailure().message.c_str(),
                static_cast<UINT32>(installActivityContext.GetInstallStage()),
                installActivityContext.GetCurrentResourceId().c_str(),
                installActivityContext.GetDeploymentErrorExtendedHResult(),
                installActivityContext.GetDeploymentErrorText().c_str(),
                installActivityContext.GetDeploymentErrorActivityId());
        }
    }

    return deployPackagesResult;
}
