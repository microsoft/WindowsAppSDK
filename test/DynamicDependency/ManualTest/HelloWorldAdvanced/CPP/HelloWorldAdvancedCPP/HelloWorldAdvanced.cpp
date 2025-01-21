// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <windows.h>

#include <iostream>

#include <MddBootstrap.h>

int Help()
{
    std::cout << "Usage: HelloWorldAdvancedCPP.exe [options] <majorminor> [<tag> [<minversion>]]\n"
        "options:\n"
        "  --onerror:debugbreak                    = DebugBreak() if error\n"
        "  --onerror:debugbreak:ifdebuggerattached = DebugBreak() if error and IsDebuggerAttached()\n"
        "  --onerror:failfast                      = FailFast if error\n"
        "  --onnomatch:showui                      = Show UI if no match\n"
        "  --onpackageidentity:noop                = No error if process has package identity\n"
        "  -?, --help                              = Display help\n"
        "  --                                      = Stop processing options\n"
        "where:\n"
        "  majorminor = Windows App SDK release Major.Minor version (default=1.0)\n"
        "               Can be...\n"
        "                   0xMMMMNNNN (base-16)\n"
        "                   M[.N] (dot-notation)\n"
        "                   UInt32 (base-10)\n"
        "                   * (use build time version info)"
        "         tag = Project Reunion version Tag (default=experimental1)\n"
        "  minversion = Project Reunion minimum version (default=0)\n"
        "\n"
        "Examples:\n"
        "\n"
        "Use Windows App SDK 1.0-experimental1, minVersion=0.218.840.0\n"
        "  HelloWorldAdvancedCPP.exe 1.0 experimental 0.218.840.0\n"
        "Use Windows App SDK 1.0 (stable), minVersion=0 (any)\n"
        "  HelloWorldAdvancedCPP.exe 0x00010000 0\"\"\n"
        "Use Windows App SDK 1.1-experimental2, minVersion=0 (any)\n"
        "  HelloWorldAdvancedCPP.exe 1.1 experimental2 0\n"
        "  or\n"
        "  HelloWorldAdvancedCPP.exe 1.1 experimental\n";
    return 1;
}

int wmain(int argc, wchar_t* argv[])
{
    if (argc < 2)
    {
        return Help();
    }

    // Parse the command line
    UINT32 majorMinorVersion{};
    auto options{ MddBootstrapInitializeOptions_None };
    int argn = 1;
    PCWSTR arg{};
    while (argn < argc)
    {
        arg = argv[argn];
        if ((CompareStringOrdinal(arg, -1, L"-?", -1, FALSE) == CSTR_EQUAL) ||
            (CompareStringOrdinal(arg, -1, L"--help", -1, FALSE) == CSTR_EQUAL))
        {
            return Help();
        }
        else if (CompareStringOrdinal(arg, -1, L"--onerror:debugbreak", -1, FALSE) == CSTR_EQUAL)
        {
            options |= MddBootstrapInitializeOptions_OnError_DebugBreak;
        }
        else if (CompareStringOrdinal(arg, -1, L"--onerror:debugbreak:ifdebuggerattached", -1, FALSE) == CSTR_EQUAL)
        {
            options |= MddBootstrapInitializeOptions_OnError_DebugBreak_IfDebuggerAttached;
        }
        else if (CompareStringOrdinal(arg, -1, L"--onerror:failfast", -1, FALSE) == CSTR_EQUAL)
        {
            options |= MddBootstrapInitializeOptions_OnError_FailFast;
        }
        else if (CompareStringOrdinal(arg, -1, L"--onnomatch:showui", -1, FALSE) == CSTR_EQUAL)
        {
            options |= MddBootstrapInitializeOptions_OnNoMatch_ShowUI;
        }
        else if (CompareStringOrdinal(arg, -1, L"--onpackageidentity:noop", -1, FALSE) == CSTR_EQUAL)
        {
            options |= MddBootstrapInitializeOptions_OnPackageIdentity_NOOP;
        }
        else if (CompareStringOrdinal(arg, -1, L"--", -1, FALSE) == CSTR_EQUAL)
        {
            break;
        }
        else if (arg[0] == L'-' && arg[1] == L'-')
        {
            // Unknown option
            return Help();
        }
        else
        {
            break;
        }
        ++argn;
    }

    if (argn > argc)
    {
        return Help();
    }
    arg = argv[argn++];
    if (arg[0] == L'0' && arg[1] == L'x')
    {
        majorMinorVersion = std::wcstoul(arg + 2, nullptr, 16);
    }
    else
    {
        UINT16 versionMajor{};
        UINT16 versionMinor{};
        if (swscanf_s(arg, L"%hu.%hu", &versionMajor, &versionMinor) == 2)
        {
            majorMinorVersion = (static_cast<UINT32>(versionMajor) << 16) | static_cast<UINT32>(versionMinor);
        }
        else
        {
            majorMinorVersion = std::wcstoul(arg, nullptr, 10);
        }
    }
    if (majorMinorVersion == 0)
    {
        return Help();
    }

    PCWSTR versionTag{ L"" };
    if (argn < argc)
    {
        arg = argv[argn++];
        versionTag = arg;
    }

    PACKAGE_VERSION minVersion{};
    if (argn < argc)
    {
        arg = argv[argn++];
        if (arg[0] == L'0' && arg[1] == L'x')
        {
            minVersion.Version = std::wcstoull(arg, nullptr, 16);
        }
        else if ((swscanf_s(arg, L"%hu.%hu.%hu.%hu", &minVersion.Major, &minVersion.Minor, &minVersion.Build, &minVersion.Revision) != 4) &&
                 (swscanf_s(arg, L"%hu.%hu.%hu", &minVersion.Major, &minVersion.Minor, &minVersion.Build) != 3) &&
                 (swscanf_s(arg, L"%hu.%hu", &minVersion.Major, &minVersion.Minor) != 2) &&
                 (swscanf_s(arg, L"%hu", &minVersion.Major) != 1))
        {
            std::wcout << "Invalid parameter: " << arg << std::endl;
            return E_INVALIDARG;
        }
    }

    // Initialize access to the Windows App SDK Framework package
    PCWSTR versionTagQuote{ versionTag ? L"\"" : L"" };
    wprintf(L"MddBootstrapInitialize2(0x%08X, %s%s%s, %hu.%hu.%hu.%hu, 0x%X)...\n",
            majorMinorVersion, versionTagQuote, versionTag, versionTagQuote,
            minVersion.Major, minVersion.Minor, minVersion.Build, minVersion.Revision, options);
    const HRESULT hr{ MddBootstrapInitialize2(majorMinorVersion, versionTag, minVersion, options) };
    if (FAILED(hr))
    {
        wprintf(L"Error 0x%X in MddBootstrapInitialize(0x%08X, %s%s%s, %hu.%hu.%hu.%hu, 0x%X)\n",
                hr, majorMinorVersion, versionTagQuote, versionTag, versionTagQuote,
                minVersion.Major, minVersion.Minor, minVersion.Build, minVersion.Revision, options);
        return hr;
    }

    // Do interesting stuff...
    std::cout << "Hello World!\n";

    // Cleanup
    MddBootstrapShutdown();
    return 0;
}
