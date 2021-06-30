#include "pch.h"
#include "console.h"

void ShowHelp()
{
    std::wcout << L"Installs Microsoft Project Reunion." << std::endl;
    std::wcout << L"  " << wil::GetModuleFileNameW(nullptr).get() << std::endl;
    std::wcout << "Command line parameters: " << std::endl;
    std::wcout << "  [-q] or [--quiet] : Runs the installer with no user interaction and suppresses all text output." << std::endl;
    std::wcout << "  [-?] or [--help] : Show help information." << std::endl;
    std::wcout << std::endl;
    std::wcout << "Consult the Project Reunion documentation for additional guidance on installation and command line syntax." << std::endl;
    std::wcout << "Documentation URI: https://aka.ms/ProjectReunionInstaller" << std::endl;
}
