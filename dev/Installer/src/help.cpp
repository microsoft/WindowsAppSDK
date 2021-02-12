#include "pch.h"
#include "help.h"

void show_help()
{
    std::wcout << L"Installs the Microsoft Project Reunion framework." << std::endl;

    // Get the program name for the module, since argv[0] is unreliable if launched from CreateProcess.
    wchar_t programName[MAX_PATH];
    if (::GetModuleFileNameW(GetModuleHandle(NULL), programName, MAX_PATH))
    {
        printf("%ls\n", programName);
    }

    printf("Usage:\n");
    printf("  [-quiet] : Suppress all console output.\n");
    printf("  [-?] or [-help] : Show this text.\n");
}