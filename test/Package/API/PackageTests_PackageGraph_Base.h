// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <IsWindowsVersion.h>

namespace TD = ::Test::Diagnostics;
namespace TB = ::Test::Bootstrap;
namespace TP = ::Test::Packages;
namespace TD = ::Test::Diagnostics;

namespace Test::Package::Tests
{
    constexpr auto Main_PackageFamilyName{ ::TP::WindowsAppRuntimeMain::c_PackageFamilyName };
    constexpr auto Main_PackageFullName{ ::TP::WindowsAppRuntimeMain::c_PackageFullName };
    constexpr auto Framework_PackageFamilyName{ ::TP::WindowsAppRuntimeFramework::c_PackageFamilyName };
    constexpr auto Framework_PackageFullName{ ::TP::WindowsAppRuntimeFramework::c_PackageFullName };
    constexpr auto Mutable_PackageFamilyName{ ::TP::Mutable::c_packageFamilyName };
    constexpr auto Mutable_PackageFullName{ ::TP::Mutable::c_packageFullName };
    constexpr auto UserExternal_PackageFamilyName{ ::TP::UserExternal::c_packageFamilyName };
    constexpr auto UserExternal_PackageFullName{ ::TP::UserExternal::c_packageFullName };
    constexpr auto MachineExternal_PackageFamilyName{ ::TP::MachineExternal::c_packageFamilyName };
    constexpr auto MachineExternal_PackageFullName{ ::TP::MachineExternal::c_packageFullName };

    class PackageTests_PackageGraph_Base
    {
    protected:
        bool ClassSetup()
        {
            if (!::WindowsVersion::IsWindows11_24H2OrGreater())
            {
                WEX::Logging::Log::Result(WEX::Logging::TestResults::Skipped, L"PackageGraph tests require >= 24H2. Skipping tests");
                return true;
            }

            ::TB::Setup();

            RemovePackage_MachineExternal();
            RemovePackage_UserExternal();
            RemovePackage_Mutable();

            AddPackage_Mutable();
            AddPackage_UserExternal();
            StagePackage_MachineExternal();
            AddPackage_MachineExternal();

            return true;
        }

        bool ClassCleanup()
        {
            RemovePackage_MachineExternal();
            RemovePackage_UserExternal();
            RemovePackage_Mutable();

            ::TB::Cleanup();

            return true;
        }

        PACKAGEDEPENDENCY_CONTEXT AddDynamicDependency(
            PCWSTR packageFamilyName)
        {
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"AddDynamicDependency(): %ls", packageFamilyName));

            const PACKAGE_VERSION minVersion{};
            const auto architectures{ PackageDependencyProcessorArchitectures_None };
            const auto lifetimeKind{ PackageDependencyLifetimeKind_Process };
            const auto tryCreateOptions{ CreatePackageDependencyOptions_None };
            wil::unique_process_heap_string packageDependencyId;
            VERIFY_SUCCEEDED(::TryCreatePackageDependency(nullptr, packageFamilyName, minVersion, architectures, lifetimeKind, nullptr, tryCreateOptions, wil::out_param(packageDependencyId)));
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageDependencyId: %ls", packageDependencyId.get()));

            PACKAGEDEPENDENCY_CONTEXT packageDependencyContext{};
            const std::int32_t rank{ -1000 };
            const auto addOptions{ AddPackageDependencyOptions_None };
            wil::unique_process_heap_string packageFullName;
            VERIFY_SUCCEEDED(::AddPackageDependency(packageDependencyId.get(), rank, addOptions, &packageDependencyContext, wil::out_param(packageFullName)));
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageDependencyContext: %p", packageDependencyId.get()));
            WEX::Logging::Log::Comment(WEX::Common::String().Format(L"PackageFullName: %ls", packageFullName.get()));

            VERIFY_SUCCEEDED(::DeletePackageDependency(packageDependencyId.get()));

            return packageDependencyContext;
        }

        PACKAGEDEPENDENCY_CONTEXT AddDynamicDependency(
            const std::wstring& packageFamilyName)
        {
            return AddDynamicDependency(packageFamilyName.c_str());
        }

        PACKAGEDEPENDENCY_CONTEXT AddDynamicDependency(
            const winrt::hstring& packageFamilyName)
        {
            return AddDynamicDependency(packageFamilyName.c_str());
        }
    };
}
