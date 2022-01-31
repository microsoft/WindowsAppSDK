// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "console.h"
#include "install.h"
#include "resource.h"

using namespace winrt;

int wmain(int argc, wchar_t *argv[])
{
    init_apartment();

    wil::SetResultLoggingCallback(wilResultLoggingCallback);

    auto options{ WindowsAppRuntimeInstaller::Options::InstallPackages |
                  WindowsAppRuntimeInstaller::Options::InstallLicenses };

    std::stringstream args{};

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
            ShowHelp();
            return 0;
        }
        else
        {
            std::wcerr << "Unknown argument: " << arg.data() << std::endl;
            ShowHelp();
            return ERROR_BAD_ARGUMENTS;
        }

        // Capture valid arguments only
        args << argv[i] << " ";
    }

    activity = WindowsAppRuntimeInstaller_TraceLogger::Install::Start(args.str().c_str(), (UINT32)options);
    args.clear();

    const HRESULT deployPackagesResult{ WindowsAppRuntimeInstaller::Deploy(options) };
    if (WI_IsFlagClear(options, WindowsAppRuntimeInstaller::Options::Quiet))
    {
        if (SUCCEEDED(deployPackagesResult))
        {
            activity.Stop();
            std::wcout << "All install operations successful." << std::endl;
        }
        else
        {
            activity.Stop(
                deployPackagesResult,
                (UINT32)g_installStage,
                g_currentPackageFullName,
                g_deploymentErrorExtendedHresult,
                g_deploymentErrorText,
                g_deploymentErrorActivityId);
            std::wcerr << "One or more install operations failed. Result: 0x" << std::hex << deployPackagesResult << std::endl;
        }
    }
    return deployPackagesResult;
}

