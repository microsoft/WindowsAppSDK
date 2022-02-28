// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

using namespace WindowsAppRuntimeInstaller::InstallActivityContent;

void WindowsAppRuntimeInstaller::Console::DisplayInfoHeader()
{
    std::wcout << L"WindowsAppRuntimeInstaller -- Installs the Microsoft Windows App SDK runtime "
        << "version: " << WINDOWSAPPSDK_RELEASE_VERSION << "-" << WINDOWSAPPSDK_RELEASE_CHANNEL << std::endl;
    std::wcout << L"Copyright(c) Microsoft Corporation. All rights reserved." << std::endl << std::endl;
}

void WindowsAppRuntimeInstaller::Console::DisplayHelp()
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

void WindowsAppRuntimeInstaller::Console::DisplayInfo()
{
    DisplayInfoHeader();
    std::wcout << "Privacy Statement:   https://aka.ms/windowsappsdk-privacy" << std::endl;
    std::wcout << "License Statement:   https://aka.ms/windowsappsdk-license" << std::endl;
}

void WindowsAppRuntimeInstaller::Console::DisplayErrorMessage(const HRESULT hr)
{
    auto& context{ InstallActivityContext::Get() };

    if (SUCCEEDED(hr))
    {
        std::wcout << std::endl;
        return;
    }

    wil::unique_hlocal_ptr<WCHAR[]> message{};
    if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        nullptr, hr, 0, reinterpret_cast<PWSTR>(&message), 0, nullptr) != 0)
    {
        std::wcout << message.get();
    }

    // Don't log redundant Hr information
    if (context.GetDeploymentErrorExtendedHResult() &&
        context.GetDeploymentErrorExtendedHResult() != hr &&
        (context.GetInstallStage() == InstallStage::AddPackage ||
            context.GetInstallStage() == InstallStage::RegisterPackage))
    {
        std::wcout << "ExtendedError: 0x" << std::hex << context.GetDeploymentErrorExtendedHResult() << " ";

        if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            nullptr, context.GetDeploymentErrorExtendedHResult(), 0, reinterpret_cast<PWSTR>(&message), 0, nullptr) != 0)
        {
            std::wcout << message.get();
        }
    }

    if (context.GetDeploymentErrorText().empty() &&
        (context.GetInstallStage() == InstallStage::AddPackage ||
            context.GetInstallStage() == InstallStage::RegisterPackage))
    {
        std::wcout << "ErrorMessage: " << context.GetDeploymentErrorText();
    }
}

