#include "pch.h"
#include "console.h"

void ShowHelp()
{
    std::wcout << L"Installs the Microsoft Project Reunion framework." << std::endl;
    std::wcout << L"  " << wil::GetModuleFileNameW(nullptr).get() << std::endl;
    std::wcout << "Usage: " << std::endl;
    std::wcout << "  [--quiet] : Suppress all output." << std::endl;
    std::wcout << "  [-?] or [--help] : Show this text." << std::endl;
}
