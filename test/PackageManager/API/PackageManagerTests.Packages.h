// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __PACKAGEMANAGERTESTS_PACKAGES_H
#define __PACKAGEMANAGERTESTS_PACKAGES_H

namespace Test::Packages::Framework{}
namespace Test::Packages::Main{}
namespace Test::PackageManager::Tests{}
//
namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TPF = ::Test::Packages::Framework;
namespace TPM = ::Test::Packages::Main;
namespace TPMT = ::Test::PackageManager::Tests;


namespace Test::Packages
{
namespace Framework
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
namespace Main
{
namespace Black
{
    constexpr PCWSTR c_packageDirName = L"PackageManager.Test.M.Black.msix";
    constexpr PCWSTR c_packageFamilyName = L"Test.PackageManager.M.Black_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x86 = L"Test.PackageManager.M.Black_1.2.3.4_x86__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x64 = L"Test.PackageManager.M.Black_1.2.3.4_x64__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_arm64 = L"Test.PackageManager.M.Black_1.2.3.4_arm64__8wekyb3d8bbwe";
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
    constexpr PCWSTR c_appUserModelId = L"Test.PackageManager.M.Black_8wekyb3d8bbwe!App";
}
namespace Blacker
{
    constexpr PCWSTR c_packageDirName = L"PackageManager.Test.M.Blacker.msix";
    constexpr PCWSTR c_packageFamilyName = L"Test.PackageManager.M.Black_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x86 = L"Test.PackageManager.M.Black_2.4.6.8_x86__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x64 = L"Test.PackageManager.M.Black_2.4.6.8_x64__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_arm64 = L"Test.PackageManager.M.Black_2.4.6.8_arm64__8wekyb3d8bbwe";
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
    constexpr PCWSTR c_appUserModelId = L"Test.PackageManager.M.Black_8wekyb3d8bbwe!App";
}
namespace White
{
    constexpr PCWSTR c_packageDirName = L"PackageManager.Test.M.White.msix";
    constexpr PCWSTR c_packageFamilyName = L"Test.PackageManager.M.White_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x86 = L"Test.PackageManager.M.White_1.2.3.4_x86__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x64 = L"Test.PackageManager.M.White_1.2.3.4_x64__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_arm64 = L"Test.PackageManager.M.White_1.2.3.4_arm64__8wekyb3d8bbwe";
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
    constexpr PCWSTR c_appUserModelId = L"Test.PackageManager.M.White_8wekyb3d8bbwe!App";
}
namespace Whiter
{
    constexpr PCWSTR c_packageDirName = L"PackageManager.Test.M.Whiter.msix";
    constexpr PCWSTR c_packageFamilyName = L"Test.PackageManager.M.White_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x86 = L"Test.PackageManager.M.White_2.4.6.8_x86__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_x64 = L"Test.PackageManager.M.White_2.4.6.8_x64__8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName_arm64 = L"Test.PackageManager.M.White_2.4.6.8_arm64__8wekyb3d8bbwe";
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
    constexpr PCWSTR c_appUserModelId = L"Test.PackageManager.M.White_8wekyb3d8bbwe!App";
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
        const winrt::Windows::Foundation::Uri* packageUri)
    {
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageSetItem: PackageFullName:%s Path:%s", packageFullName, (packageUri ? packageUri->ToString().c_str() : L"<null>")));
        const auto [packageName, packageVersion, packageArchitecture, packageResourceId, packagePublisherId, packageFamilyName]{ ::AppModel::Package::ParsePackageFullName(packageFullName) };

        winrt::Microsoft::Windows::Management::Deployment::PackageSetItem psi;
        psi.PackageFamilyName(packageFamilyName);
        if (packageUri)
        {
            psi.PackageUri(*packageUri);
        }
        const ::AppModel::Identity::PackageVersion version{ packageVersion };
        psi.MinVersion(version.ToWinrtPackageVersion());
        return psi;
    }

    inline winrt::Microsoft::Windows::Management::Deployment::PackageSetItem Make_PackageSetItem(
        PCWSTR packageFullName,
        PCWSTR packageDirName)
    {
        const auto packageUri{ TP::GetMsixPackageUri(packageDirName) };
        return _Make_PackageSetItem(packageFullName, &packageUri);
    }

    inline winrt::Microsoft::Windows::Management::Deployment::PackageSetItem Make_PackageSetItem_ForRegister(
        PCWSTR packageFullName)
    {
        const auto appxManifestUri{ TP::GetAppxManifestPackageUri(packageFullName) };
        return _Make_PackageSetItem(packageFullName, &appxManifestUri);
    }

    inline winrt::Microsoft::Windows::Management::Deployment::PackageSetItem Make_PackageSetItem_NoPackageUri(
        PCWSTR packageFullName)
    {
        return _Make_PackageSetItem(packageFullName, nullptr);
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
        TP::AddPackageIfNecessary(TPF::Red::c_packageDirName, TPF::Red::GetPackageFullName());
    }
    inline void StagePackage_Red()
    {
        TP::StagePackageIfNecessary(TPF::Red::c_packageDirName, TPF::Red::GetPackageFullName());
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
    }
    inline bool IsPackageProvisioned_Red()
    {
        return TP::IsPackageProvisioned(TPF::Red::c_packageFamilyName);
    }
    inline void ProvisionPackage_Red()
    {
        TP::ProvisionPackage(TPF::Red::c_packageFamilyName);
    }
    inline void DeprovisionPackage_Red()
    {
        TP::DeprovisionPackageIfNecessary(TPF::Red::c_packageFamilyName);
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
        TP::AddPackageIfNecessary(TPF::Redder::c_packageDirName, TPF::Redder::GetPackageFullName());
    }
    inline void StagePackage_Redder()
    {
        TP::StagePackageIfNecessary(TPF::Redder::c_packageDirName, TPF::Redder::GetPackageFullName());
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
    }
    inline bool IsPackageProvisioned_Redder()
    {
        return TP::IsPackageProvisioned(TPF::Redder::c_packageFamilyName);
    }
    inline void ProvisionPackage_Redder()
    {
        TP::ProvisionPackage(TPF::Redder::c_packageFamilyName);
    }
    inline void DeprovisionPackage_Redder()
    {
        TP::DeprovisionPackageIfNecessary(TPF::Redder::c_packageFamilyName);
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
        TP::AddPackageIfNecessary(TPF::Green::c_packageDirName, TPF::Green::GetPackageFullName());
    }
    inline void StagePackage_Green()
    {
        TP::StagePackageIfNecessary(TPF::Green::c_packageDirName, TPF::Green::GetPackageFullName());
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
    }
    inline bool IsPackageProvisioned_Green()
    {
        return TP::IsPackageProvisioned(TPF::Green::c_packageFamilyName);
    }
    inline void ProvisionPackage_Green()
    {
        TP::ProvisionPackage(TPF::Green::c_packageFamilyName);
    }
    inline void DeprovisionPackage_Green()
    {
        TP::DeprovisionPackageIfNecessary(TPF::Green::c_packageFamilyName);
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
        TP::AddPackageIfNecessary(TPF::Blue::c_packageDirName, TPF::Blue::GetPackageFullName());
    }
    inline void StagePackage_Blue()
    {
        TP::StagePackageIfNecessary(TPF::Blue::c_packageDirName, TPF::Blue::GetPackageFullName());
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
    }
    inline bool IsPackageProvisioned_Blue()
    {
        return TP::IsPackageProvisioned(TPF::Blue::c_packageFamilyName);
    }
    inline void ProvisionPackage_Blue()
    {
        TP::ProvisionPackage(TPF::Blue::c_packageFamilyName);
    }
    inline void DeprovisionPackage_Blue()
    {
        TP::DeprovisionPackageIfNecessary(TPF::Blue::c_packageFamilyName);
    }

    inline bool IsPackageRegistered_Black()
    {
        return TP::IsPackageRegistered(TPM::Black::GetPackageFullName());
    }
    inline bool IsPackageStaged_Black()
    {
        return TP::IsPackageStaged(TPM::Black::GetPackageFullName());
    }
    inline void AddPackage_Black()
    {
        TP::AddPackageIfNecessary(TPM::Black::c_packageDirName, TPM::Black::GetPackageFullName());
    }
    inline void AddPackageDefer_Black()
    {
        TP::AddPackageDeferIfNecessary(TPM::Black::c_packageDirName, TPM::Black::GetPackageFullName());
    }
    inline void StagePackage_Black()
    {
        TP::StagePackageIfNecessary(TPM::Black::c_packageDirName, TPM::Black::GetPackageFullName());
    }
    inline void RegisterPackage_Black()
    {
        TP::RegisterPackageIfNecessary(TPM::Black::GetPackageFullName());
    }
    inline void RemovePackage_Black()
    {
        if (IsPackageRegistered_Black())
        {
            TP::RemovePackage(TPM::Black::GetPackageFullName());
        }
        else if (IsPackageStaged_Black())
        {
            // We can't directly remove a Stage package not registered for current user
            // w/o admin privilege but we can add it to make it registered and then remove it.
            AddPackage_Black();
            TP::RemovePackage(TPM::Black::GetPackageFullName());
        }
    }
    inline void RemovePackageFamily_Black()
    {
        RemovePackage_Black();
    }
    inline bool IsPackageProvisioned_Black()
    {
        return TP::IsPackageProvisioned(TPM::Black::c_packageFamilyName);
    }
    inline void ProvisionPackage_Black()
    {
        TP::ProvisionPackage(TPM::Black::c_packageFamilyName);
    }
    inline void DeprovisionPackage_Black()
    {
        TP::DeprovisionPackageIfNecessary(TPM::Black::c_packageFamilyName);
    }

    inline bool IsPackageRegistered_Blacker()
    {
        return TP::IsPackageRegistered(TPM::Blacker::GetPackageFullName());
    }
    inline bool IsPackageStaged_Blacker()
    {
        return TP::IsPackageStaged(TPM::Blacker::GetPackageFullName());
    }
    inline void AddPackage_Blacker()
    {
        TP::AddPackageIfNecessary(TPM::Blacker::c_packageDirName, TPM::Blacker::GetPackageFullName());
    }
    inline void AddPackageDefer_Blacker()
    {
        TP::AddPackageDeferIfNecessary(TPM::Blacker::c_packageDirName, TPM::Blacker::GetPackageFullName());
    }
    inline void StagePackage_Blacker()
    {
        TP::StagePackageIfNecessary(TPM::Blacker::c_packageDirName, TPM::Blacker::GetPackageFullName());
    }
    inline void RegisterPackage_Blacker()
    {
        TP::RegisterPackageIfNecessary(TPM::Blacker::GetPackageFullName());
    }
    inline void RemovePackage_Blacker()
    {
        if (IsPackageRegistered_Blacker())
        {
            TP::RemovePackage(TPM::Blacker::GetPackageFullName());
        }
        else if (IsPackageStaged_Blacker())
        {
            // We can't directly remove a Stage package not registered for current user
            // w/o admin privilege but we can add it to make it registered and then remove it.
            AddPackage_Blacker();
            TP::RemovePackage(TPM::Blacker::GetPackageFullName());
        }
    }
    inline void RemovePackageFamily_Blacker()
    {
        RemovePackage_Blacker();
    }
    inline bool IsPackageProvisioned_Blacker()
    {
        return TP::IsPackageProvisioned(TPM::Blacker::c_packageFamilyName);
    }
    inline void ProvisionPackage_Blacker()
    {
        TP::ProvisionPackage(TPM::Blacker::c_packageFamilyName);
    }
    inline void DeprovisionPackage_Blacker()
    {
        TP::DeprovisionPackageIfNecessary(TPM::Blacker::c_packageFamilyName);
    }

    inline bool IsPackageRegistered_White()
    {
        return TP::IsPackageRegistered(TPM::White::GetPackageFullName());
    }
    inline bool IsPackageStaged_White()
    {
        return TP::IsPackageStaged(TPM::White::GetPackageFullName());
    }
    inline void AddPackage_White()
    {
        TP::AddPackageIfNecessary(TPM::White::c_packageDirName, TPM::White::GetPackageFullName());
    }
    inline void AddPackageDefer_White()
    {
        TP::AddPackageDeferIfNecessary(TPM::White::c_packageDirName, TPM::White::GetPackageFullName());
    }
    inline void StagePackage_White()
    {
        TP::StagePackageIfNecessary(TPM::White::c_packageDirName, TPM::White::GetPackageFullName());
    }
    inline void RegisterPackage_White()
    {
        TP::RegisterPackageIfNecessary(TPM::White::GetPackageFullName());
    }
    inline void RemovePackage_White()
    {
        if (IsPackageRegistered_White())
        {
            TP::RemovePackage(TPM::White::GetPackageFullName());
        }
        else if (IsPackageStaged_White())
        {
            // We can't directly remove a Stage package not registered for current user
            // w/o admin privilege but we can add it to make it registered and then remove it.
            AddPackage_White();
            TP::RemovePackage(TPM::White::GetPackageFullName());
        }
    }
    inline void RemovePackageFamily_White()
    {
        RemovePackage_White();
    }
    inline bool IsPackageProvisioned_White()
    {
        return TP::IsPackageProvisioned(TPM::White::c_packageFamilyName);
    }
    inline void ProvisionPackage_White()
    {
        TP::ProvisionPackage(TPM::White::c_packageFamilyName);
    }
    inline void DeprovisionPackage_White()
    {
        TP::DeprovisionPackageIfNecessary(TPM::White::c_packageFamilyName);
    }

    inline bool IsPackageRegistered_Whiter()
    {
        return TP::IsPackageRegistered(TPM::Whiter::GetPackageFullName());
    }
    inline bool IsPackageStaged_Whiter()
    {
        return TP::IsPackageStaged(TPM::Whiter::GetPackageFullName());
    }
    inline void AddPackage_Whiter()
    {
        TP::AddPackageIfNecessary(TPM::Whiter::c_packageDirName, TPM::Whiter::GetPackageFullName());
    }
    inline void AddPackageDefer_Whiter()
    {
        TP::AddPackageDeferIfNecessary(TPM::Whiter::c_packageDirName, TPM::Whiter::GetPackageFullName());
    }
    inline void StagePackage_Whiter()
    {
        TP::StagePackageIfNecessary(TPM::Whiter::c_packageDirName, TPM::Whiter::GetPackageFullName());
    }
    inline void RegisterPackage_Whiter()
    {
        TP::RegisterPackageIfNecessary(TPM::Whiter::GetPackageFullName());
    }
    inline void RemovePackage_Whiter()
    {
        if (IsPackageRegistered_Whiter())
        {
            TP::RemovePackage(TPM::Whiter::GetPackageFullName());
        }
        else if (IsPackageStaged_Whiter())
        {
            // We can't directly remove a Stage package not registered for current user
            // w/o admin privilege but we can add it to make it registered and then remove it.
            AddPackage_Whiter();
            TP::RemovePackage(TPM::Whiter::GetPackageFullName());
        }
    }
    inline void RemovePackageFamily_Whiter()
    {
        RemovePackage_Whiter();
    }
    inline bool IsPackageProvisioned_Whiter()
    {
        return TP::IsPackageProvisioned(TPM::Whiter::c_packageFamilyName);
    }
    inline void ProvisionPackage_Whiter()
    {
        TP::ProvisionPackage(TPM::Whiter::c_packageFamilyName);
    }
    inline void DeprovisionPackage_Whiter()
    {
        TP::DeprovisionPackageIfNecessary(TPM::Whiter::c_packageFamilyName);
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
