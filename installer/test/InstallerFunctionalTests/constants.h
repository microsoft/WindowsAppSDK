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

#define BASE_PATH L"..\\..\\..\\"
#define INSTALLER_DIR L"ProjectReunionInstall"
#define INSTALLER_FILENAME L"ProjectReunionInstall.exe"
#define INSTALLER_EXE_PATH BASE_PATH CONFIGURATION L"\\" ARCH L"\\" INSTALLER_DIR L"\\" INSTALLER_FILENAME

namespace ProjectReunionInstallerTests
{
    static const int c_phaseTimeout = (30 * 1000); // 30 seconds

    static const std::wstring c_x86FrameworkName = L"Microsoft.ProjectReunion.Test.InstallerFramework_1.0.0.0_x86__8wekyb3d8bbwe";
    static const std::wstring c_x64FrameworkName = L"Microsoft.ProjectReunion.Test.InstallerFramework_1.0.0.0_x64__8wekyb3d8bbwe";
    static const std::wstring c_arm64FrameworkName = L"Microsoft.ProjectReunion.Test.InstallerFramework_1.0.0.0_arm64__8wekyb3d8bbwe";

    static const std::wstring c_packages[] = {
        c_x86FrameworkName,
        c_x64FrameworkName,
        c_arm64FrameworkName,
    };
}
