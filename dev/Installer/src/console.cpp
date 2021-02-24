#include "pch.h"
#include "console.h"

void ShowHelp()
{
    std::wcout << L"Installs the Microsoft Project Reunion framework." << std::endl;

    // Get the program name for the module, since argv[0] is unreliable if launched from CreateProcess.
    wchar_t programName[MAX_PATH];
    if (::GetModuleFileNameW(GetModuleHandle(NULL), programName, MAX_PATH))
    {
        std::wcout << L"  " << programName << std::endl;
    }

    std::wcout << "Usage: " << std::endl;
    std::wcout << "  [--quiet] : Suppress all console output." << std::endl;
    std::wcout << "  [--?] or [--help] : Show this text." << std::endl;
}
