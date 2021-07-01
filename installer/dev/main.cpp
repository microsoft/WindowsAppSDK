#include "pch.h"
#include "console.h"
#include "install.h"
#include "resource.h"

using namespace winrt;

int wmain(int argc, wchar_t *argv[])
{
    init_apartment();

    bool quiet = false;

    for (int i = 1; i < argc; ++i)
    {
        auto arg = std::wstring_view(argv[i]);
        if ((arg == L"-q") || (arg == L"--quiet"))
        {
            quiet = true;
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
    }

    const HRESULT deployPackagesResult{ ProjectReunionInstaller::DeployPackages(quiet) };
    if (!quiet)
    {
        if (SUCCEEDED(deployPackagesResult))
        {
            std::wcout << "All packages were installed successfully." << std::endl;
        }
        else
        {
            std::wcerr << "One or more packages failed to install. Result: 0x" << std::hex << deployPackagesResult << std::endl;
        }
    }

    return deployPackagesResult;
}

