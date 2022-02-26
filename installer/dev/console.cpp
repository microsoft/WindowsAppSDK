// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "console.h"

void ShowHelp()
{
    DisplayInfoHeader();
    std::wcout << L"  " << wil::GetModuleFileNameW(nullptr).get() << std::endl << std::endl;
    std::wcout << "Options (append - to disable e.g. --license- to not install licenses)" << std::endl;
    std::wcout << "  --dry-run    Dry run (report but don't execute install operations)" << std::endl;
    std::wcout << "  --license    Install licenses" << std::endl;
    std::wcout << "  --msix       Install MSIX packages" << std::endl;
    std::wcout << "  -q, --quiet  Perform no user interaction and suppress all text output" << std::endl;
    std::wcout << "  -?, --help   Show help information" << std::endl;
    std::wcout << "  --info       Display general information and disclosures of the installer" << std::endl;
    std::wcout << std::endl;
    std::wcout << "Consult the Windows App SDK documentation for additional guidance on installation and command line syntax." << std::endl;
    std::wcout << "Documentation URI: https://aka.ms/windowsappsdkinstall" << std::endl;
}

void DisplayInfo()
{
    DisplayInfoHeader();
    std::wcout << "Privacy Statement:   https://go.microsoft.com/fwlink/?LinkID=824704" << std::endl;
    std::wcout << "License Statement:   https://github.com/microsoft/WindowsAppSDK#legal-notices" << std::endl;
}

void DisplayInfoHeader()
{
    std::wcout << L"WindowsAppRuntimeInstaller -- Install the Microsoft Windows App SDK runtime "
        << "version: " << WINDOWSAPPSDK_RELEASE_VERSION << " "
        << "channel: " << WINDOWSAPPSDK_RELEASE_CHANNEL << " "
        << std::endl;
    std::wcout << L"Copyright(c) Microsoft Corporation.All rights reserved." << std::endl;
}
