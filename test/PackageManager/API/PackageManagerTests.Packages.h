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
    constexpr inline PCWSTR GetPackageFullName()
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
    constexpr PCWSTR c_packageFamilyName = L"Test.PackageManager.F.Red_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x86 = L"Test.PackageManager.F.Red_2.4.6.8_x86__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x64 = L"Test.PackageManager.F.Red_2.4.6.8_x64__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_arm64 = L"Test.PackageManager.F.Red_2.4.6.8_arm64__8wekyb3d8bbwe";
    constexpr inline PCWSTR GetPackageFullName()
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
    constexpr inline PCWSTR GetPackageFullName()
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
    constexpr inline PCWSTR GetPackageFullName()
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

namespace Test::PackageManager::Tests
{
    namespace TP = ::Test::Packages;
    namespace TPF = ::Test::Packages::Framework;

    inline winrt::Microsoft::Windows::Management::Deployment::PackageSetItem Make_PackageSetItem(
        PCWSTR packageFullName,
        PCWSTR packageDirName)
    {
        const auto [packageName, packageVersion, packageArchitecture, packageResourceId, packagePublisherId, packageFamilyName]{ ::AppModel::Package::ParsePackageFullName(packageFullName) };

        winrt::Microsoft::Windows::Management::Deployment::PackageSetItem psi;
        psi.PackageFamilyName(packageFamilyName);
        psi.PackageUri(TP::GetMsixPackageUri(packageDirName));
        const ::AppModel::Identity::PackageVersion version{ packageVersion };
        psi.MinVersion(version.ToWinrtPackageVersion());
        return psi;
    }

    inline void AddPackage_Red()
    {
        TP::AddPackageIfNecessary(Test::Packages::Framework::Red::c_packageDirName, TPF::Red::GetPackageFullName());
    }
    inline void StagePackage_Red()
    {
        TP::StagePackageIfNecessary(Test::Packages::Framework::Red::c_packageDirName, TPF::Red::GetPackageFullName());
    }
    inline void RemovePackage_Red()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        TP::RemovePackageIfNecessary(TPF::Red::GetPackageFullName());
    }

    inline void AddPackage_Redder()
    {
        TP::AddPackageIfNecessary(Test::Packages::Framework::Redder::c_packageDirName, TPF::Redder::GetPackageFullName());
    }
    inline void StagePackage_Redder()
    {
        TP::StagePackageIfNecessary(Test::Packages::Framework::Redder::c_packageDirName, TPF::Redder::GetPackageFullName());
    }
    inline void RemovePackage_Redder()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        TP::RemovePackageIfNecessary(TPF::Redder::GetPackageFullName());
    }

    inline void AddPackage_Green()
    {
        TP::AddPackageIfNecessary(Test::Packages::Framework::Green::c_packageDirName, TPF::Green::GetPackageFullName());
    }
    inline void StagePackage_Green()
    {
        TP::StagePackageIfNecessary(Test::Packages::Framework::Green::c_packageDirName, TPF::Green::GetPackageFullName());
    }
    inline void RemovePackage_Green()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        TP::RemovePackageIfNecessary(TPF::Green::GetPackageFullName());
    }

    inline void AddPackage_Blue()
    {
        TP::AddPackageIfNecessary(Test::Packages::Framework::Blue::c_packageDirName, TPF::Blue::GetPackageFullName());
    }
    inline void StagePackage_Blue()
    {
        TP::StagePackageIfNecessary(Test::Packages::Framework::Blue::c_packageDirName, TPF::Blue::GetPackageFullName());
    }
    inline void RemovePackage_Blue()
    {
        // Best-effort removal. PackageManager.RemovePackage errors if the package
        // is not registered, but if it's not registered we're good. "'Tis the destination
        // that matters, not the journey" so regardless how much or little work
        // we need do, we're happy as long as the package isn't registered when we're done
        //
        // Thus, do a *IfNecessary removal
        TP::RemovePackageIfNecessary(TPF::Blue::GetPackageFullName());
    }

    inline void SetPackageStatus(winrt::Windows::Management::Deployment::PackageManager packageManager, PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
    {
        const auto packageTypes{ winrt::Windows::Management::Deployment::PackageTypes::Framework };
        auto packages{ packageManager.FindPackagesForUserWithPackageTypes(winrt::hstring(), packageFamilyName, packageTypes) };
        for (const winrt::Windows::ApplicationModel::Package& package : packages)
        {
            packageManager.SetPackageStatus(package.Id().FullName(), status);
        }
    }

    inline void ClearPackageStatus(winrt::Windows::Management::Deployment::PackageManager packageManager, PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
    {
        const auto packageTypes{ winrt::Windows::Management::Deployment::PackageTypes::Framework };
        auto packages{ packageManager.FindPackagesForUserWithPackageTypes(winrt::hstring(), packageFamilyName, packageTypes) };
        for (const winrt::Windows::ApplicationModel::Package& package : packages)
        {
            packageManager.ClearPackageStatus(package.Id().FullName(), status);
        }
    }
}

#endif // __PACKAGEMANAGERTESTS_PACKAGES_H
