// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __PACKAGETESTS_PACKAGES_H
#define __PACKAGETESTS_PACKAGES_H

namespace Test::Package::Tests{}
//
namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;

namespace Test::Packages
{
namespace Framework
{
    constexpr PCWSTR c_packageDirName = L"Package.Test.Framework.msix";
    constexpr PCWSTR c_packageFamilyName = L"Test.Package.Framework_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName = L"Test.Package.Framework_1.2.3.4_neutral__8wekyb3d8bbwe";
}
namespace Main
{
    constexpr PCWSTR c_packageDirName = L"Package.Test.Main.msix";
    constexpr PCWSTR c_packageFamilyName = L"Test.Package.Main_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName = L"Test.Package.Main_1.2.3.4_neutral__8wekyb3d8bbwe";
}
namespace Mutable
{
    constexpr PCWSTR c_packageDirName = L"Package.Test.Mutable.msix";
    constexpr PCWSTR c_packageFamilyName = L"Test.Package.Mutable_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName = L"Test.Package.Mutable_1.2.3.4_neutral__8wekyb3d8bbwe";
}
namespace UserExternal
{
    constexpr PCWSTR c_packageDirName = L"Package.Test.UserExternal.msix";
    constexpr PCWSTR c_packageFamilyName = L"Test.Package.UserExternal_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName = L"Test.Package.UserExternal_1.2.3.4_neutral__8wekyb3d8bbwe";
}
namespace MachineExternal
{
    constexpr PCWSTR c_packageDirName = L"Package.Test.MachineExternal.msix";
    constexpr PCWSTR c_packageFamilyName = L"Test.Package.MachineExternal_8wekyb3d8bbwe";
    constexpr PCWSTR c_packageFullName = L"Test.Package.MachineExternal_1.2.3.4_neutral__8wekyb3d8bbwe";
}
}

namespace Test::Package::Tests
{
    namespace TP = ::Test::Packages;

    inline bool IsPackageRegistered_Framework()
    {
        return TP::IsPackageRegistered(TP::Framework::c_packageFullName);
    }
    inline bool IsPackageStaged_Framework()
    {
        return TP::IsPackageStaged(TP::Framework::c_packageFullName);
    }
    inline winrt::Windows::ApplicationModel::PackageStatus GetPackageStatus_Framework()
    {
        return TP::GetPackageStatus(TP::Framework::c_packageFullName);
    }
    inline void AddPackage_Framework()
    {
        TP::AddPackageIfNecessary(TP::Framework::c_packageDirName, TP::Framework::c_packageFullName);
    }
    inline void AddPackageDefer_Framework()
    {
        TP::AddPackageDeferIfNecessary(TP::Framework::c_packageDirName, TP::Framework::c_packageFullName);
    }
    inline void StagePackage_Framework()
    {
        TP::StagePackageIfNecessary(TP::Framework::c_packageDirName, TP::Framework::c_packageFullName);
    }
    inline void RegisterPackage_Framework()
    {
        TP::RegisterPackageIfNecessary(TP::Framework::c_packageFullName);
    }
    inline void RemovePackage_Framework()
    {
        if (IsPackageRegistered_Framework())
        {
            TP::RemovePackage(TP::Framework::c_packageFullName);
        }
        else if (IsPackageStaged_Framework())
        {
            // We can't directly remove a Stage package not registered for current user
            // w/o admin privilege but we can add it to make it registered and then remove it.
            AddPackage_Framework();
            TP::RemovePackage(TP::Framework::c_packageFullName);
        }
    }
    inline void RemovePackageFamily_Framework()
    {
        RemovePackage_Framework();
    }
    inline bool IsPackageProvisioned_Framework()
    {
        return TP::IsPackageProvisioned(TP::Framework::c_packageFamilyName);
    }
    inline void ProvisionPackage_Framework()
    {
        TP::ProvisionPackage(TP::Framework::c_packageFamilyName);
    }
    inline void DeprovisionPackage_Framework()
    {
        TP::DeprovisionPackageIfNecessary(TP::Framework::c_packageFamilyName);
    }

    inline bool IsPackageRegistered_Main()
    {
        return TP::IsPackageRegistered(TP::Main::c_packageFullName);
    }
    inline bool IsPackageStaged_Main()
    {
        return TP::IsPackageStaged(TP::Main::c_packageFullName);
    }
    inline winrt::Windows::ApplicationModel::PackageStatus GetPackageStatus_Main()
    {
        return TP::GetPackageStatus(TP::Main::c_packageFullName);
    }
    inline void AddPackage_Main()
    {
        TP::AddPackageIfNecessary(TP::Main::c_packageDirName, TP::Main::c_packageFullName);
    }
    inline void AddPackageDefer_Main()
    {
        TP::AddPackageDeferIfNecessary(TP::Main::c_packageDirName, TP::Main::c_packageFullName);
    }
    inline void StagePackage_Main()
    {
        TP::StagePackageIfNecessary(TP::Main::c_packageDirName, TP::Main::c_packageFullName);
    }
    inline void RegisterPackage_Main()
    {
        TP::RegisterPackageIfNecessary(TP::Main::c_packageFullName);
    }
    inline void RemovePackage_Main()
    {
        if (IsPackageRegistered_Main())
        {
            TP::RemovePackage(TP::Main::c_packageFullName);
        }
        else if (IsPackageStaged_Main())
        {
            // We can't directly remove a Stage package not registered for current user
            // w/o admin privilege but we can add it to make it registered and then remove it.
            AddPackage_Main();
            TP::RemovePackage(TP::Main::c_packageFullName);
        }
    }
    inline void RemovePackageFamily_Main()
    {
        RemovePackage_Main();
    }
    inline bool IsPackageProvisioned_Main()
    {
        return TP::IsPackageProvisioned(TP::Main::c_packageFamilyName);
    }
    inline void ProvisionPackage_Main()
    {
        TP::ProvisionPackage(TP::Main::c_packageFamilyName);
    }
    inline void DeprovisionPackage_Main()
    {
        TP::DeprovisionPackageIfNecessary(TP::Main::c_packageFamilyName);
    }

    inline bool IsPackageRegistered_Mutable()
    {
        return TP::IsPackageRegistered(TP::Mutable::c_packageFullName);
    }
    inline bool IsPackageStaged_Mutable()
    {
        return TP::IsPackageStaged(TP::Mutable::c_packageFullName);
    }
    inline winrt::Windows::ApplicationModel::PackageStatus GetPackageStatus_Mutable()
    {
        return TP::GetPackageStatus(TP::Mutable::c_packageFullName);
    }
    inline void AddPackage_Mutable()
    {
        TP::AddPackageIfNecessary(TP::Mutable::c_packageDirName, TP::Mutable::c_packageFullName);
    }
    inline void AddPackageDefer_Mutable()
    {
        TP::AddPackageDeferIfNecessary(TP::Mutable::c_packageDirName, TP::Mutable::c_packageFullName);
    }
    inline void StagePackage_Mutable()
    {
        TP::StagePackageIfNecessary(TP::Mutable::c_packageDirName, TP::Mutable::c_packageFullName);
    }
    inline void RegisterPackage_Mutable()
    {
        TP::RegisterPackageIfNecessary(TP::Mutable::c_packageFullName);
    }
    inline void RemovePackage_Mutable()
    {
        if (IsPackageRegistered_Mutable())
        {
            TP::RemovePackage(TP::Mutable::c_packageFullName);
        }
        else if (IsPackageStaged_Mutable())
        {
            // We can't directly remove a Stage package not registered for current user
            // w/o admin privilege but we can add it to make it registered and then remove it.
            AddPackage_Mutable();
            TP::RemovePackage(TP::Mutable::c_packageFullName);
        }
    }
    inline void RemovePackageFamily_Mutable()
    {
        RemovePackage_Mutable();
    }
    inline bool IsPackageProvisioned_Mutable()
    {
        return TP::IsPackageProvisioned(TP::Mutable::c_packageFamilyName);
    }
    inline void ProvisionPackage_Mutable()
    {
        TP::ProvisionPackage(TP::Mutable::c_packageFamilyName);
    }
    inline void DeprovisionPackage_Mutable()
    {
        TP::DeprovisionPackageIfNecessary(TP::Mutable::c_packageFamilyName);
    }

    inline bool IsPackageRegistered_UserExternal()
    {
        return TP::IsPackageRegistered(TP::UserExternal::c_packageFullName);
    }
    inline bool IsPackageStaged_UserExternal()
    {
        return TP::IsPackageStaged(TP::UserExternal::c_packageFullName);
    }
    inline winrt::Windows::ApplicationModel::PackageStatus GetPackageStatus_UserExternal()
    {
        return TP::GetPackageStatus(TP::UserExternal::c_packageFullName);
    }
    inline void AddPackage_UserExternal()
    {
        const auto path{ TP::GetMsixPackagePath(TP::UserExternal::c_packageDirName).parent_path()};
        TP::AddPackageIfNecessary(TP::UserExternal::c_packageDirName, TP::UserExternal::c_packageFullName, path.c_str());
    }
    inline void AddPackageDefer_UserExternal()
    {
        const auto path{ TP::GetMsixPackagePath(TP::UserExternal::c_packageDirName).parent_path() };
        TP::AddPackageDeferIfNecessary(TP::UserExternal::c_packageDirName, TP::UserExternal::c_packageFullName, path.c_str());
    }
    inline void StagePackage_UserExternal()
    {
        const auto path{ TP::GetMsixPackagePath(TP::UserExternal::c_packageDirName).parent_path() };
        TP::StagePackageIfNecessary(TP::UserExternal::c_packageDirName, TP::UserExternal::c_packageFullName, path.c_str());
    }
    inline void RegisterPackage_UserExternal()
    {
        TP::RegisterPackageIfNecessary(TP::UserExternal::c_packageFullName);
    }
    inline void RemovePackage_UserExternal()
    {
        if (IsPackageRegistered_UserExternal())
        {
            TP::RemovePackage(TP::UserExternal::c_packageFullName);
        }
        else if (IsPackageStaged_UserExternal())
        {
            // We can't directly remove a Stage package not registered for current user
            // w/o admin privilege but we can add it to make it registered and then remove it.
            AddPackage_UserExternal();
            TP::RemovePackage(TP::UserExternal::c_packageFullName);
        }
    }
    inline void RemovePackageFamily_UserExternal()
    {
        RemovePackage_UserExternal();
    }
    inline bool IsPackageProvisioned_UserExternal()
    {
        return TP::IsPackageProvisioned(TP::UserExternal::c_packageFamilyName);
    }
    inline void ProvisionPackage_UserExternal()
    {
        TP::ProvisionPackage(TP::UserExternal::c_packageFamilyName);
    }
    inline void DeprovisionPackage_UserExternal()
    {
        TP::DeprovisionPackageIfNecessary(TP::UserExternal::c_packageFamilyName);
    }

    inline bool IsPackageRegistered_MachineExternal()
    {
        return TP::IsPackageRegistered(TP::MachineExternal::c_packageFullName);
    }
    inline bool IsPackageStaged_MachineExternal()
    {
        return TP::IsPackageStaged(TP::MachineExternal::c_packageFullName);
    }
    inline winrt::Windows::ApplicationModel::PackageStatus GetPackageStatus_MachineExternal()
    {
        return TP::GetPackageStatus(TP::MachineExternal::c_packageFullName);
    }
    inline void AddPackage_MachineExternal()
    {
        const auto path{ TP::GetMsixPackagePath(TP::MachineExternal::c_packageDirName).parent_path()};
        TP::AddPackageIfNecessary(TP::MachineExternal::c_packageDirName, TP::MachineExternal::c_packageFullName, path.c_str());
    }
    inline void AddPackageDefer_MachineExternal()
    {
        const auto path{ TP::GetMsixPackagePath(TP::MachineExternal::c_packageDirName).parent_path() };
        TP::AddPackageDeferIfNecessary(TP::MachineExternal::c_packageDirName, TP::MachineExternal::c_packageFullName, path.c_str());
    }
    inline void StagePackage_MachineExternal()
    {
        const auto path{ TP::GetMsixPackagePath(TP::MachineExternal::c_packageDirName).parent_path() };
        TP::StagePackageIfNecessary(TP::MachineExternal::c_packageDirName, TP::MachineExternal::c_packageFullName, path.c_str());
    }
    inline void RegisterPackage_MachineExternal()
    {
        TP::RegisterPackageIfNecessary(TP::MachineExternal::c_packageFullName);
    }
    inline void RemovePackage_MachineExternal()
    {
        if (IsPackageRegistered_MachineExternal())
        {
            TP::RemovePackage(TP::MachineExternal::c_packageFullName);
        }
        else if (IsPackageStaged_MachineExternal())
        {
            // We can't directly remove a Stage package not registered for current user
            // w/o admin privilege but we can add it to make it registered and then remove it.
            AddPackage_MachineExternal();
            TP::RemovePackage(TP::MachineExternal::c_packageFullName);
        }
    }
    inline void RemovePackageFamily_MachineExternal()
    {
        RemovePackage_MachineExternal();
    }
    inline bool IsPackageProvisioned_MachineExternal()
    {
        return TP::IsPackageProvisioned(TP::MachineExternal::c_packageFamilyName);
    }
    inline void ProvisionPackage_MachineExternal()
    {
        TP::ProvisionPackage(TP::MachineExternal::c_packageFamilyName);
    }
    inline void DeprovisionPackage_MachineExternal()
    {
        TP::DeprovisionPackageIfNecessary(TP::MachineExternal::c_packageFamilyName);
    }
}

#endif // __PACKAGETESTS_PACKAGES_H
