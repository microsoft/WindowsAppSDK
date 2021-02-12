#include "pch.h"
#include "help.h"
#include "install.h"
#include "resource.h"
#include "packages.h"

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::System;

int deploy_packages(bool quiet)
{
    for (const auto& package : c_packages)
    {
        auto result = deploy_package_from_resource(package, quiet);
        if (FAILED(result.value))
        {
            return result.value;
        }
    }
    return 0;
}

int wmain(int argc, wchar_t *argv[])
{
    init_apartment();

    bool quiet = false;

    for (int i = 1; i < argc; ++i)
    {
        auto arg = std::wstring_view(argv[i]);
        if ((arg == L"-q") || (arg == L"-quiet"))
        {
            quiet = true;
        }
        else if ((arg == L"-?") || (arg == L"-help"))
        {
            show_help();
            return 0;
        }
        else if ((arg == L"-a") || (arg == L"-add"))
        {
            show_help();
            return 0;
        }
        else
        {
            printf("Unknown argument: %ws\n", arg.data());
            show_help();
            return ERROR_BAD_ARGUMENTS;
        }
    }

    return deploy_packages(quiet);
}

