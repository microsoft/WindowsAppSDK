// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

void Help();
int JustDoIt(PCWSTR path, PCWSTR release);

void Help()
{
    wprintf(L"WindowsAppRuntime_MSIXInstallFromPath <path> <release>\n"
            L"where:\n"
            L"  path = Path where Windows App SDK's MSIX packages can be found\n"
            L"           => Microsoft.WindowsAppRuntime.*.msix\n"
            L"           => Microsoft.WindowsAppRuntime.DDLM.*.msix\n"
            L"           => Microsoft.WindowsAppRuntime.Main.*.msix\n"
            L"           => Microsoft.WindowsAppRuntime.Singleton.*.msix\n");
}

int JustDoIt(PCWSTR path, PCWSTR release)
{
    wprintf(L"path: %s\n", path);
    wprintf(L"release: %s\n", release);

    // Install packages

    return 0;
}

int wmain(int argc, wchar_t *argv[])
{
    // Parse the command line
    int index { 1 };
    for (; index < argc; ++index)
    {
        auto arg{ argv[index] };
        if ((CompareStringOrdinal(arg, -1, L"-?", -1, FALSE) == CSTR_EQUAL) ||
            (CompareStringOrdinal(arg, -1, L"--help", -1, TRUE) == CSTR_EQUAL))
        {
            Help();
            return ERROR_BAD_ARGUMENTS;
        }
        else
        {
            std::wcerr << "Unknown argument: " << arg.data() << std::endl;
            ShowHelp();
            return ERROR_BAD_ARGUMENTS;
        }
    }

    if (index >= argc)
    {
        ShowHelp();
        return ERROR_BAD_ARGUMENTS;
    }
    auto path{ argv[index++] };

    if (index >= argc)
    {
        ShowHelp();
        return ERROR_BAD_ARGUMENTS;
    }
    auto release{ argv[index++] };

    if (index < argc)
    {
        ShowHelp();
        return ERROR_BAD_ARGUMENTS;
    }

    return JustDoIt(path);
}
