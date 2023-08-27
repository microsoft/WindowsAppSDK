// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __PACKAGEMANAGERTESTS_PACKAGES_H
#define __PACKAGEMANAGERTESTS_PACKAGES_H

namespace Test::Packages::Framework
{
namespace Red
{
    constexpr PCWSTR c_packageDirName = L"PackageManager.Test.F.Red";
    constexpr PCWSTR c_packageFamilyName = L"Test.PackageManager.F.Red_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x86 = L"Test.PackageManager.F.Red_1.2.3.4_x86__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x64 = L"Test.PackageManager.F.Red_1.2.3.4_x64__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_arm64 = L"Test.PackageManager.F.Red_1.2.3.4_arm64__8wekyb3d8bbwe";
    constexpr static PCWSTR GetPackageFullName()
    {
#if defined(_M_ARM64)
        return c_packageFullName_arm64;
#elif defined(_M_IX86)
        return c_packageFullName_x86;
#elif defined(_M_X64)
        return c_packageFullName_x64;
#else
#   error "Unknown processor architecture"
#endif
    }
}
namespace Redder
{
    constexpr PCWSTR c_packageDirName = L"PackageManager.Test.F.Redder";
    constexpr PCWSTR c_packageFamilyName = L"Test.PackageManager.F.Redder_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x86 = L"Test.PackageManager.F.Redder_2.4.6.8_x86__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x64 = L"Test.PackageManager.F.Redder_2.4.6.8_x64__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_arm64 = L"Test.PackageManager.F.Redder_2.4.6.8_arm64__8wekyb3d8bbwe";
    constexpr static PCWSTR GetPackageFullName()
    {
#if defined(_M_ARM64)
        return c_packageFullName_arm64;
#elif defined(_M_IX86)
        return c_packageFullName_x86;
#elif defined(_M_X64)
        return c_packageFullName_x64;
#else
#   error "Unknown processor architecture"
#endif
    }
}
namespace Green
{
    constexpr PCWSTR c_packageDirName = L"PackageManager.Test.F.Green";
    constexpr PCWSTR c_packageFamilyName = L"Test.PackageManager.F.Green_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x86 = L"Test.PackageManager.F.Green_1.2.3.4_x86__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x64 = L"Test.PackageManager.F.Green_1.2.3.4_x64__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_arm64 = L"Test.PackageManager.F.Green_1.2.3.4_arm64__8wekyb3d8bbwe";
    constexpr static PCWSTR GetPackageFullName()
    {
#if defined(_M_ARM64)
        return c_packageFullName_arm64;
#elif defined(_M_IX86)
        return c_packageFullName_x86;
#elif defined(_M_X64)
        return c_packageFullName_x64;
#else
#   error "Unknown processor architecture"
#endif
    }
}
namespace Blue
{
    constexpr PCWSTR c_packageDirName = L"PackageManager.Test.F.Blue";
    constexpr PCWSTR c_packageFamilyName = L"Test.PackageManager.F.Blue_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x86 = L"Test.PackageManager.F.Blue_1.2.3.4_x86__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x64 = L"Test.PackageManager.F.Blue_1.2.3.4_x64__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_arm64 = L"Test.PackageManager.F.Blue_1.2.3.4_arm64__8wekyb3d8bbwe";
    constexpr static PCWSTR GetPackageFullName()
    {
#if defined(_M_ARM64)
        return c_packageFullName_arm64;
#elif defined(_M_IX86)
        return c_packageFullName_x86;
#elif defined(_M_X64)
        return c_packageFullName_x64;
#else
#   error "Unknown processor architecture"
#endif
    }
}
}

#endif // __PACKAGEMANAGERTESTS_PACKAGES_H
