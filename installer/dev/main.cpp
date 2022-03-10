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

    installActivityContext.SetActivity(WindowsAppRuntimeInstaller_TraceLogger::Install::Start(args.str().c_str(), static_cast<UINT32>(options)));
    args.clear();

    const HRESULT deployPackagesResult{ WindowsAppRuntimeInstaller::Deploy(options) };
    if (WI_IsFlagClear(options, WindowsAppRuntimeInstaller::Options::Quiet))
    {
        if (SUCCEEDED(deployPackagesResult))
        {
            std::wcout << "All install operations successful." << std::endl;

            if (!Security::IntegrityLevel::IsElevated())
            {
                std::wcout << "WARNING: Since WindowsAppRuntimeInstaller.exe is not run elevated, WindowsAppSDK packages are not provisioned for all users on your machine." << std::endl;
            }
        }
        else
        {
            installActivityContext.GetActivity().StopWithResult(
                deployPackagesResult,
                static_cast<UINT32>(installActivityContext.GetInstallStage()),
                installActivityContext.GetCurrentResourceId().c_str(),
                installActivityContext.GetDeploymentErrorExtendedHResult(),
                installActivityContext.GetDeploymentErrorText().c_str(),
                installActivityContext.GetDeploymentErrorActivityId());

            std::wcerr << "One or more install operations failed. Result: 0x" << std::hex << deployPackagesResult << std::endl;
        }
    }

    return deployPackagesResult;
}
