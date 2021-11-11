#include "pch.h"
#include "console.h"

void ShowHelp()
{
    std::wcout << L"Installs Microsoft Windows App SDK." << std::endl;
    std::wcout << L"  " << wil::GetModuleFileNameW(nullptr).get() << std::endl;
    std::wcout << "Command line parameters (append - to disable)" << std::endl;
    std::wcout << "  --license    Install licenses" << std::endl;
    std::wcout << "  --msix       Install MSIX packages" << std::endl;
    std::wcout << "  -q, --quiet  Perform no user interaction and suppress all text output" << std::endl;
    std::wcout << "  -?, --help   Show help information" << std::endl;
    std::wcout << std::endl;
    std::wcout << "Consult the Windows App SDK documentation for additional guidance on installation and command line syntax." << std::endl;
    std::wcout << "Documentation URI: https://aka.ms/ProjectReunionInstaller" << std::endl;
}
