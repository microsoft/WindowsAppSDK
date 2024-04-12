// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

using namespace WindowsAppRuntimeInstaller::InstallActivity;

void WindowsAppRuntimeInstaller::Console::DisplayHeader()
{
    std::wcout << L"WindowsAppRuntimeInstaller -- Installs the Microsoft Windows App SDK runtime"
        << "version: " << WINDOWSAPPSDK_RELEASE_VERSION;
    if (CompareStringOrdinal(WINDOWSAPPSDK_RELEASE_CHANNEL_W, -1, L"", -1, TRUE) == CSTR_EQUAL)
    {
        std::wcout << "-" << WINDOWSAPPSDK_RELEASE_CHANNEL_W;
    }
    std::wcout << std::endl;
    std::wcout << L"Copyright(c) Microsoft Corporation. All rights reserved." << std::endl << std::endl;
}

void WindowsAppRuntimeInstaller::Console::DisplayHelp()
{
    DisplayHeader();
    std::wcout << L"  " << wil::GetModuleFileNameW(nullptr).get() << std::endl << std::endl;
    std::wcout << "Options: (append - to disable e.g. --license- to not install licenses)" << std::endl;
    std::wcout << "  --dry-run    Dry run (report but don't execute install operations)" << std::endl;
    std::wcout << "  --license    Install licenses for WindowsAppSDK MSIX packages" << std::endl;
    std::wcout << "  --msix       Install WindowsAppSDK MSIX packages. Cannot be used in combination with -r or --repair option" << std::endl;
    std::wcout << "  -q, --quiet  Perform no user interaction and suppress all text output" << std::endl;
    std::wcout << "  -f, --force  Force shutdown WindowsAppSDK's processes if necessary to update WinAppSDK's MSIX packages" << std::endl;
    std::wcout << "  -r, --repair Repair WindowsAppSDK.Cannot be used in combination with --msix option" << std::endl;
    std::wcout << "  -?, --help   Show help information" << std::endl;
    std::wcout << "  --info       Display general information and disclosures of the installer" << std::endl;
    std::wcout << std::endl;
    std::wcout << "Consult the Windows App SDK documentation for additional guidance on installation and command line syntax." << std::endl;
    std::wcout << "Documentation URI: https://aka.ms/windowsappsdkinstall" << std::endl;
}

void WindowsAppRuntimeInstaller::Console::DisplayInfo()
{
    DisplayHeader();
    std::wcout << "Privacy Statement:   https://aka.ms/windowsappsdk-privacy" << std::endl;
    std::wcout << "License Statement:   https://aka.ms/windowsappsdk-license" << std::endl;
}

void WindowsAppRuntimeInstaller::Console::DisplayError(const HRESULT hr)
{
    auto& installActivityContext{ WindowsAppRuntimeInstaller::InstallActivity::Context::Get() };

    HRESULT hResult = hr;

    if (FAILED(installActivityContext.GetDeploymentErrorHresult()) &&
        (installActivityContext.GetInstallStage() == InstallStage::StagePackage ||
        installActivityContext.GetInstallStage() == InstallStage::AddPackage ||
        installActivityContext.GetInstallStage() == InstallStage::RegisterPackage))
    {
        hResult = installActivityContext.GetDeploymentErrorHresult();
    }

    if (SUCCEEDED(hResult))
    {
        std::wcout << std::endl;
        return;
    }

    wil::unique_hlocal_ptr<WCHAR[]> message;
    if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                      nullptr, hResult, 0, reinterpret_cast<PWSTR>(&message), 0, nullptr) != 0)
    {
        std::wcout << message.get();
    }

    // Don't log redundant Hr information
    if (FAILED(installActivityContext.GetDeploymentErrorExtendedHResult()) &&
        (installActivityContext.GetDeploymentErrorExtendedHResult() != hResult) &&
        (installActivityContext.GetInstallStage() == InstallStage::StagePackage ||
            installActivityContext.GetInstallStage() == InstallStage::AddPackage ||
            installActivityContext.GetInstallStage() == InstallStage::RegisterPackage))
    {
        std::wcout << "ExtendedError: 0x" << std::hex << installActivityContext.GetDeploymentErrorExtendedHResult() << " ";

        if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            nullptr, installActivityContext.GetDeploymentErrorExtendedHResult(), 0, reinterpret_cast<PWSTR>(&message), 0, nullptr) != 0)
        {
            std::wcout << message.get();
        }
    }

    if (!installActivityContext.GetDeploymentErrorText().empty() &&
        (installActivityContext.GetInstallStage() == InstallStage::StagePackage ||
            installActivityContext.GetInstallStage() == InstallStage::AddPackage ||
            installActivityContext.GetInstallStage() == InstallStage::RegisterPackage))
    {
        std::wcout << "ErrorMessage: " << installActivityContext.GetDeploymentErrorText();
    }
}
