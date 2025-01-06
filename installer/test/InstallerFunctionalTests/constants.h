// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#if defined(_M_IX86)
    #define ARCH L"x86"
#elif defined(_M_AMD64)
    #define ARCH L"x64"
#elif defined(_M_ARM64)
    #define ARCH L"arm64"
#else
    #error "Unknown architcture"
#endif

#if defined(_DEBUG)
    #define CONFIGURATION L"Debug"
#else
    #define CONFIGURATION L"Release"
#endif

#define INSTALLER_DIR L"WindowsAppRuntimeInstall"
#define INSTALLER_FILENAME L"WindowsAppRuntimeInstall-" ARCH L".exe"
#define INSTALLER_EXE_PATH INSTALLER_DIR L"\\" INSTALLER_FILENAME

namespace WindowsAppRuntimeInstallerTests
{
    static const int c_phaseTimeout{ (30 * 1000) }; // 30 seconds

    static const std::wstring c_x86FrameworkName{ L"WindowsAppRuntime.Test.InstallerFramework_1.0.0.0_x86__8wekyb3d8bbwe" };
    static const std::wstring c_x64FrameworkName{ L"WindowsAppRuntime.Test.InstallerFramework_1.0.0.0_x64__8wekyb3d8bbwe" };
    static const std::wstring c_arm64FrameworkName{ L"WindowsAppRuntime.Test.InstallerFramework_1.0.0.0_arm64__8wekyb3d8bbwe" };

    static const std::wstring c_x86MainName{ L"WindowsAppRuntime.Test.InstallerMain_1.0.0.0_x86__8wekyb3d8bbwe" };
    static const std::wstring c_x64MainName{ L"WindowsAppRuntime.Test.InstallerMain_1.0.0.0_x64__8wekyb3d8bbwe" };
    static const std::wstring c_arm64MainName{ L"WindowsAppRuntime.Test.InstallerMain_1.0.0.0_arm64__8wekyb3d8bbwe" };
    static const std::wstring c_mainFamilyName{ L"WindowsAppRuntime.Test.InstallerMain_8wekyb3d8bbwe" };

    static const std::wstring c_x86SingletonName{ L"WindowsAppRuntime.Test.InstallerSingleton_1.0.0.0_x86__8wekyb3d8bbwe" };
    static const std::wstring c_x64SingletonName{ L"WindowsAppRuntime.Test.InstallerSingleton_1.0.0.0_x64__8wekyb3d8bbwe" };
    static const std::wstring c_arm64SingletonName{ L"WindowsAppRuntime.Test.InstallerSingleton_1.0.0.0_arm64__8wekyb3d8bbwe" };
    static const std::wstring c_singletonFamilyName{ L"WindowsAppRuntime.Test.InstallerSingleton_8wekyb3d8bbwe" };

    static const std::wstring c_x86DDLMName{ L"WindowsAppRuntime.Test.InstallerDDLM-x86_1.0.0.0_x86__8wekyb3d8bbwe" };
    static const std::wstring c_x64DDLMName{ L"WindowsAppRuntime.Test.InstallerDDLM-x64_1.0.0.0_x64__8wekyb3d8bbwe" };
    static const std::wstring c_arm64DDLMName{ L"WindowsAppRuntime.Test.InstallerDDLM-arm64_1.0.0.0_arm64__8wekyb3d8bbwe" };
    static const std::wstring c_x86DDLMFamilyName{ L"WindowsAppRuntime.Test.InstallerDDLM-arm64_8wekyb3d8bbwe" };
    static const std::wstring c_x64DDLMFamilyName{ L"WindowsAppRuntime.Test.InstallerDDLM-arm64_8wekyb3d8bbwe" };
    static const std::wstring c_arm64DDLMFamilyName{ L"WindowsAppRuntime.Test.InstallerDDLM-arm64_8wekyb3d8bbwe" };

    static const std::wstring c_packages[] = {
        c_x86MainName,
        c_x64MainName,
        c_arm64MainName,
        c_x86SingletonName,
        c_x64SingletonName,
        c_arm64SingletonName,
        c_x86DDLMName,
        c_x64DDLMName,
        c_arm64DDLMName,
        c_x86FrameworkName,
        c_x64FrameworkName,
        c_arm64FrameworkName,
    };

    static const std::wstring c_mainPackageFamilies[] = {
        c_x86DDLMFamilyName,
        c_x64DDLMFamilyName,
        c_arm64DDLMFamilyName,
        c_mainFamilyName,
        c_singletonFamilyName
    };
}
