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

    // Forward declarations
    void RemovePackageFamily_Redder();

    inline winrt::Microsoft::Windows::Management::Deployment::PackageSetItem _Make_PackageSetItem(
        PCWSTR packageFullName,
        winrt::Windows::Foundation::Uri const& packageUri)
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageSetItem: PackageFullName:%s Path:%s", packageFullName, packageUri.ToString().c_str()));
        const auto [packageName, packageVersion, packageArchitecture, packageResourceId, packagePublisherId, packageFamilyName]{ ::AppModel::Package::ParsePackageFullName(packageFullName) };

        winrt::Microsoft::Windows::Management::Deployment::PackageSetItem psi;
        psi.PackageFamilyName(packageFamilyName);
        psi.PackageUri(packageUri);
        const ::AppModel::Identity::PackageVersion version{ packageVersion };
        psi.MinVersion(version.ToWinrtPackageVersion());
        return psi;
    }

    inline winrt::Microsoft::Windows::Management::Deployment::PackageSetItem Make_PackageSetItem(
        PCWSTR packageFullName,
        PCWSTR packageDirName)
    {
        const auto packageUri{ TP::GetMsixPackageUri(packageDirName) };
        return _Make_PackageSetItem(packageFullName, packageUri);
    }

    inline winrt::Microsoft::Windows::Management::Deployment::PackageSetItem Make_PackageSetItem_ForRegister(
        PCWSTR packageFullName)
    {
        const auto appxManifestUri{ TP::GetAppxManifestPackageUri(packageFullName) };
        return _Make_PackageSetItem(packageFullName, appxManifestUri);
    }

    inline bool IsPackageRegistered_Red()
    {
        return TP::IsPackageRegistered(TPF::Red::GetPackageFullName());
    }
    inline bool IsPackageStaged_Red()
    {
        return TP::IsPackageStaged(TPF::Red::GetPackageFullName());
    }
    inline void AddPackage_Red()
    {
        TP::AddPackageIfNecessary(Test::Packages::Framework::Red::c_packageDirName, TPF::Red::GetPackageFullName());
    }
    inline void StagePackage_Red()
    {
        TP::StagePackageIfNecessary(Test::Packages::Framework::Red::c_packageDirName, TPF::Red::GetPackageFullName());
    }
    inline void RegisterPackage_Red()
    {
        TP::RegisterPackageIfNecessary(TPF::Red::GetPackageFullName());
    }
    inline void RemovePackage_Red()
    {
        if (IsPackageRegistered_Red())
        {
            TP::RemovePackage(TPF::Red::GetPackageFullName());
        }
        else if (IsPackageStaged_Red())
        {
            // We can't directly remove a Stage package not registered for current user
            // w/o admin privilege but we can add it to make it registered and then remove it.
            AddPackage_Red();
            TP::RemovePackage(TPF::Red::GetPackageFullName());
        }
    }
    inline void RemovePackageFamily_Red()
    {
        // Same as RemovePackageFamily_Redder
        RemovePackageFamily_Redder();
#if 0
        // The package could be staged and not registered so checking
        // checking for registered packages in the family is insufficient,
        // and checking for staged packages not registered for the current user
        // requires admin privilege (which we may not have). So we'll rely on
        // remove for each package in the family handling it whether the packages
        // are staged or registered.
        TP::RemovePackageIfNecessary(TPF::Red::GetPackageFullName());
        TP::RemovePackageIfNecessary(TPF::Redder::GetPackageFullName());
#endif
    }

    inline bool IsPackageRegistered_Redder()
    {
        return TP::IsPackageRegistered(TPF::Redder::GetPackageFullName());
    }
    inline bool IsPackageStaged_Redder()
    {
        return TP::IsPackageStaged(TPF::Redder::GetPackageFullName());
    }
    inline void AddPackage_Redder()
    {
        TP::AddPackageIfNecessary(Test::Packages::Framework::Redder::c_packageDirName, TPF::Redder::GetPackageFullName());
    }
    inline void StagePackage_Redder()
    {
        TP::StagePackageIfNecessary(Test::Packages::Framework::Redder::c_packageDirName, TPF::Redder::GetPackageFullName());
    }
    inline void RegisterPackage_Redder()
    {
        TP::RegisterPackageIfNecessary(TPF::Redder::GetPackageFullName());
    }
    inline void RemovePackage_Redder()
    {
        if (IsPackageRegistered_Redder())
        {
            TP::RemovePackage(TPF::Redder::GetPackageFullName());
        }
        else if (IsPackageStaged_Redder())
        {
            // We can't directly remove a Stage package not registered for current user
            // w/o admin privilege but we can add it to make it registered and then remove it.
            AddPackage_Redder();
            TP::RemovePackage(TPF::Redder::GetPackageFullName());
        }
    }
    inline void RemovePackageFamily_Redder()
    {
        RemovePackage_Redder();
        RemovePackage_Red();
#if 0
        // The package could be staged and not registered so checking
        // checking for registered packages in the family is insufficient,
        // and checking for staged packages not registered for the current user
        // requires admin privilege (which we may not have). So we'll rely on
        // remove for each package in the family handling it whether the packages
        // are staged or registered.
        TP::RemovePackageIfNecessary(TPF::Red::GetPackageFullName());
        TP::RemovePackageIfNecessary(TPF::Redder::GetPackageFullName());
#endif
    }

    inline bool IsPackageRegistered_Green()
    {
        return TP::IsPackageRegistered(TPF::Green::GetPackageFullName());
    }
    inline bool IsPackageStaged_Green()
    {
        return TP::IsPackageStaged(TPF::Green::GetPackageFullName());
    }
    inline void AddPackage_Green()
    {
        TP::AddPackageIfNecessary(Test::Packages::Framework::Green::c_packageDirName, TPF::Green::GetPackageFullName());
    }
    inline void StagePackage_Green()
    {
        TP::StagePackageIfNecessary(Test::Packages::Framework::Green::c_packageDirName, TPF::Green::GetPackageFullName());
    }
    inline void RegisterPackage_Green()
    {
        TP::RegisterPackageIfNecessary(TPF::Green::GetPackageFullName());
    }
    inline void RemovePackage_Green()
    {
        if (IsPackageRegistered_Green())
        {
            TP::RemovePackage(TPF::Green::GetPackageFullName());
        }
        else if (IsPackageStaged_Green())
        {
            // We can't directly remove a Stage package not registered for current user
            // w/o admin privilege but we can add it to make it registered and then remove it.
            AddPackage_Green();
            TP::RemovePackage(TPF::Green::GetPackageFullName());
        }
    }
    inline void RemovePackageFamily_Green()
    {
        RemovePackage_Green();
#if 0
        // The package could be staged and not registered so checking
        // checking for registered packages in the family is insufficient,
        // and checking for staged packages not registered for the current user
        // requires admin privilege (which we may not have). So we'll rely on
        // remove for each package in the family handling it whether the packages
        // are staged or registered.
        TP::RemovePackageIfNecessary(TPF::Green::GetPackageFullName());
#endif
    }

    inline bool IsPackageRegistered_Blue()
    {
        return TP::IsPackageRegistered(TPF::Blue::GetPackageFullName());
    }
    inline bool IsPackageStaged_Blue()
    {
        return TP::IsPackageStaged(TPF::Blue::GetPackageFullName());
    }
    inline void AddPackage_Blue()
    {
        TP::AddPackageIfNecessary(Test::Packages::Framework::Blue::c_packageDirName, TPF::Blue::GetPackageFullName());
    }
    inline void StagePackage_Blue()
    {
        TP::StagePackageIfNecessary(Test::Packages::Framework::Blue::c_packageDirName, TPF::Blue::GetPackageFullName());
    }
    inline void RegisterPackage_Blue()
    {
        TP::RegisterPackageIfNecessary(TPF::Blue::GetPackageFullName());
    }
    inline void RemovePackage_Blue()
    {
        if (IsPackageRegistered_Blue())
        {
            TP::RemovePackage(TPF::Blue::GetPackageFullName());
        }
        else if (IsPackageStaged_Blue())
        {
            // We can't directly remove a Stage package not registered for current user
            // w/o admin privilege but we can add it to make it registered and then remove it.
            AddPackage_Blue();
            TP::RemovePackage(TPF::Blue::GetPackageFullName());
        }
    }
    inline void RemovePackageFamily_Blue()
    {
        RemovePackage_Blue();
#if 0
        // The package could be staged and not registered so checking
        // checking for registered packages in the family is insufficient,
        // and checking for staged packages not registered for the current user
        // requires admin privilege (which we may not have). So we'll rely on
        // remove for each package in the family handling it whether the packages
        // are staged or registered.
        TP::RemovePackageIfNecessary(TPF::Green::GetPackageFullName());
#endif
    }

    inline winrt::Windows::ApplicationModel::PackageStatus GetPackageStatus(winrt::Windows::Management::Deployment::PackageManager packageManager, PCWSTR packageFullName)
    {
        auto package{ packageManager.FindPackageForUser(winrt::hstring(), packageFullName) };
        return package.Status();
    }

    inline void SetPackageStatus(winrt::Windows::Management::Deployment::PackageManager packageManager, PCWSTR packageFullName, winrt::Windows::Management::Deployment::PackageStatus status)
    {
        packageManager.SetPackageStatus(packageFullName, status);
    }

    inline void SetPackageStatusByPackageFamilyName(winrt::Windows::Management::Deployment::PackageManager packageManager, PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
    {
        const auto packageTypes{ winrt::Windows::Management::Deployment::PackageTypes::Framework };
        auto packages{ packageManager.FindPackagesForUserWithPackageTypes(winrt::hstring(), packageFamilyName, packageTypes) };
        for (const winrt::Windows::ApplicationModel::Package& package : packages)
        {
            packageManager.SetPackageStatus(package.Id().FullName(), status);
        }
    }

    inline void ClearPackageStatus(winrt::Windows::Management::Deployment::PackageManager packageManager, PCWSTR packageFullName, winrt::Windows::Management::Deployment::PackageStatus status)
    {
        packageManager.ClearPackageStatus(packageFullName, status);
    }

    inline void ClearPackageStatusByPackageFamilyName(winrt::Windows::Management::Deployment::PackageManager packageManager, PCWSTR packageFamilyName, winrt::Windows::Management::Deployment::PackageStatus status)
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
