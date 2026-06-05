// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __WINDOWSAPPRUNTIME_TEST_BOOTSTRAP_H
#define __WINDOWSAPPRUNTIME_TEST_BOOTSTRAP_H

#include <MddBootstrap.h>
#include <MddBootstrapTest.h>

#include <WindowsAppRuntime.Test.AppModel.h>
#include <WindowsAppRuntime.Test.Package.h>

#include <WexTestClass.h>

namespace Test::Bootstrap
{
    enum class Packages
    {
        None         = 0,
        Framework    = 0x0001,
        Main         = 0x0002,
        DDLM         = 0x0004,
        Singleton    = 0x0008,

        Default = Framework | Main | DDLM | Singleton,
    };
}
DEFINE_ENUM_FLAG_OPERATORS(Test::Bootstrap::Packages)

namespace Test::Bootstrap
{
    namespace TA = ::Test::AppModel;
    namespace TF = ::Test::FileSystem;
    namespace TP = ::Test::Packages;

    static wil::unique_hmodule s_bootstrapDll;

    inline bool NeedDynamicDependencies()
    {
        return !TA::IsPackagedProcess();
    }

    inline void SetupPackages(Test::Bootstrap::Packages packagesToSetup = Test::Bootstrap::Packages::Default)
    {
        // Remove our packages in case they were previously installed and incompletely removed
        if (WI_IsFlagSet(packagesToSetup, Test::Bootstrap::Packages::Singleton))
        {
            TP::RemovePackage_WindowsAppRuntimeSingleton();
        }
        if (WI_IsFlagSet(packagesToSetup, Test::Bootstrap::Packages::DDLM))
        {
            TP::RemovePackage_DynamicDependencyLifetimeManager();
        }
        if (WI_IsFlagSet(packagesToSetup, Test::Bootstrap::Packages::Main))
        {
            TP::RemovePackage_DynamicDependencyDataStore();
        }
        if (WI_IsFlagSet(packagesToSetup, Test::Bootstrap::Packages::Framework))
        {
            TP::RemovePackage_WindowsAppRuntimeFramework();
        }

        // Install our needed packages
        if (WI_IsFlagSet(packagesToSetup, Test::Bootstrap::Packages::Framework))
        {
            TP::AddPackage_WindowsAppRuntimeFramework();
        }
        if (WI_IsFlagSet(packagesToSetup, Test::Bootstrap::Packages::Main))
        {
            TP::AddPackage_DynamicDependencyDataStore();
        }
        if (WI_IsFlagSet(packagesToSetup, Test::Bootstrap::Packages::DDLM))
        {
            TP::AddPackage_DynamicDependencyLifetimeManager();
        }
        if (WI_IsFlagSet(packagesToSetup, Test::Bootstrap::Packages::Singleton))
        {
            TP::AddPackage_WindowsAppRuntimeSingleton();
        }
    }

    inline void CleanupPackages(Test::Bootstrap::Packages packagesToSetup = Test::Bootstrap::Packages::Default)
    {
        // Remove our packages in case they were previously installed and incompletely removed
        if (WI_IsFlagSet(packagesToSetup, Test::Bootstrap::Packages::Singleton))
        {
            TP::RemovePackage_WindowsAppRuntimeSingleton();
        }
        if (WI_IsFlagSet(packagesToSetup, Test::Bootstrap::Packages::DDLM))
        {
            TP::RemovePackage_DynamicDependencyLifetimeManager();
        }
        if (WI_IsFlagSet(packagesToSetup, Test::Bootstrap::Packages::Main))
        {
            TP::RemovePackage_DynamicDependencyDataStore();
        }
        if (WI_IsFlagSet(packagesToSetup, Test::Bootstrap::Packages::Framework))
        {
            TP::RemovePackage_WindowsAppRuntimeFramework();
        }
    }

    // Poll for the precondition MddBootstrapInitialize -> FindDDLMViaEnumeration
    // actually checks (not just package enumerability via PackageManager).
    // The bootstrap does:
    //   1. FindPackagesForUserWithPackageTypes(currentUser, Main) - UNSCOPED enumeration
    //      (no family filter). Returns ALL Main packages for the user; the
    //      bootstrap then filters by Name prefix. This is a different OS query
    //      from the family-scoped enumeration in AddPackage's wait - it can
    //      return 0 packages while the family-scoped path returns our DDLM.
    //   2. GetPackagePathByFullName(packageFullName) - filesystem-backed.
    //   3. FindFirstFile(<packagePath>\Microsoft.WindowsAppRuntime.Release!*) -
    //      the DDLM's release-marker payload file; not visible until the .msix
    //      payload is fully staged.
    // If any of these are transiently empty/stale, the bootstrap silently skips
    // our DDLM (or sees zero candidates) and throws
    // STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED (0x80270254). Poll all three.
    inline void WaitForDDLMBootstrapReady(PCWSTR ddlmPackageFullName, PCWSTR ddlmPackageNamePrefix)
    {
        constexpr DWORD c_pollIntervalMs{ 100 };
        constexpr DWORD c_timeoutMs{ 30000 };
        const DWORD startTick{ GetTickCount() };
        winrt::Windows::Management::Deployment::PackageManager packageManager;
        const auto c_packageTypes{ winrt::Windows::Management::Deployment::PackageTypes::Main };
        const std::wstring ddlmNamePrefix{ ddlmPackageNamePrefix };
        for (;;)
        {
            bool unscopedEnumReady{ false };
            bool pathReady{ false };
            bool markerReady{ false };

            // Check 1: unscoped Main-package enumeration includes a package whose
            // Name starts with the DDLM prefix - matches the bootstrap's enumeration.
            try
            {
                auto packages{ packageManager.FindPackagesForUserWithPackageTypes(winrt::hstring{}, c_packageTypes) };
                if (packages)
                {
                    for (const auto& candidate : packages)
                    {
                        const auto name{ candidate.Id().Name() };
                        if (name.size() >= ddlmNamePrefix.size() &&
                            CompareStringOrdinal(name.c_str(), static_cast<int>(ddlmNamePrefix.size()),
                                                 ddlmNamePrefix.c_str(), static_cast<int>(ddlmNamePrefix.size()),
                                                 TRUE) == CSTR_EQUAL)
                        {
                            unscopedEnumReady = true;
                            break;
                        }
                    }
                }
            }
            catch (...)
            {
                // PackageManager occasionally throws transient access errors;
                // treat as not-yet-ready.
            }

            // Check 2 + 3: GetPackagePathByFullName + FindFirstFile for the release marker.
            std::wstring packagePath;
            uint32_t packagePathLength{};
            const auto sizeProbeRc{ GetPackagePathByFullName(ddlmPackageFullName, &packagePathLength, nullptr) };
            if (sizeProbeRc == ERROR_INSUFFICIENT_BUFFER && packagePathLength > 0)
            {
                packagePath.resize(packagePathLength);
                const auto fetchRc{ GetPackagePathByFullName(ddlmPackageFullName, &packagePathLength, packagePath.data()) };
                if (fetchRc == ERROR_SUCCESS)
                {
                    pathReady = true;
                    if (!packagePath.empty() && packagePath.back() == L'\0')
                    {
                        packagePath.pop_back();
                    }
                    std::wstring fileSpec{ packagePath };
                    fileSpec += L"\\Microsoft.WindowsAppRuntime.Release!*";
                    WIN32_FIND_DATA findFileData{};
                    const HANDLE hfind{ FindFirstFile(fileSpec.c_str(), &findFileData) };
                    if (hfind != INVALID_HANDLE_VALUE)
                    {
                        markerReady = true;
                        FindClose(hfind);
                    }
                }
            }

            if (unscopedEnumReady && pathReady && markerReady)
            {
                return;
            }

            const DWORD elapsed{ GetTickCount() - startTick };
            if (elapsed >= c_timeoutMs)
            {
                WEX::Logging::Log::Warning(WEX::Common::String().Format(
                    L"WaitForDDLMBootstrapReady('%s') timed out after %u ms (unscopedEnum=%d pathReady=%d markerReady=%d); MddBootstrapInitialize may race",
                    ddlmPackageFullName, elapsed,
                    unscopedEnumReady ? 1 : 0, pathReady ? 1 : 0, markerReady ? 1 : 0));
                return;
            }
            Sleep(c_pollIntervalMs);
        }
    }

    inline void SetupBootstrapWithVersion(const UINT32 version_MajorMinor, const PACKAGE_VERSION minVersion, bool shouldTestInit = true)
    {
        // Bootstrapper's only needed for non-packaged processes to use Dynamic Dependencies
        if (!NeedDynamicDependencies())
        {
            return;
        }

        // We need to find Microsoft.WindowsAppRuntime.Bootstrap.dll.
        // Normally it's colocated with the application (i.e. same dir as the exe)
        // but that's not true of our test project (a dll) in our build environment
        // (different directories). So we'll explicitly find and load it so the
        // rest of our test is fine
        auto bootstrapDllAbsoluteFilename{ TF::GetBootstrapAbsoluteFilename() };
        wil::unique_hmodule bootstrapDll(LoadLibrary(bootstrapDllAbsoluteFilename.c_str()));
        if (!bootstrapDll)
        {
            const auto lastError{ GetLastError() };
            VERIFY_IS_NOT_NULL(bootstrapDll.get(), WEX::Common::String().Format(L"Error in LoadLibrary: %d (0x%X) loading %s", lastError, lastError, bootstrapDllAbsoluteFilename.c_str()));
        }

        if (shouldTestInit)
        {
            // Initialize the bootstrapper (for testing purposes)
            VERIFY_SUCCEEDED(MddBootstrapTestInitialize(TP::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                TP::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                TP::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                TP::WindowsAppRuntimeMain::c_PackageNamePrefix));
        }

        // Synchronise against MddBootstrapInitialize's actual precondition (the
        // unscoped Main enumeration + GetPackagePathByFullName + FindFirstFile
        // probe inside FindDDLMViaEnumeration) before calling it. Otherwise the
        // bootstrap silently skips our DDLM and returns
        // STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED (0x80270254).
        WaitForDDLMBootstrapReady(
            TP::DynamicDependencyLifetimeManager::c_PackageFullName,
            TP::DynamicDependencyLifetimeManager::c_PackageNamePrefix);

        VERIFY_SUCCEEDED(MddBootstrapInitialize(version_MajorMinor, nullptr, minVersion));
        s_bootstrapDll = std::move(bootstrapDll);
    }

    inline void SetupBootstrap()
    {
        // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
        const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
        const PACKAGE_VERSION minVersion{};

        SetupBootstrapWithVersion(c_Version_MajorMinor, minVersion);
    }

    inline void CleanupBootstrap()
    {
        // Bootstrapper's only needed for non-packaged processes to use Dynamic Dependencies
        if (!NeedDynamicDependencies())
        {
            return;
        }

        // Shutdown the bootstrapper
        MddBootstrapShutdown();

        // Release our reference to the bootstrapper DLL
        s_bootstrapDll.reset();
    }

    inline void Setup(Test::Bootstrap::Packages packagesToSetup = Test::Bootstrap::Packages::Default)
    {
        SetupPackages(packagesToSetup);
        SetupBootstrap();
    }

    inline void Cleanup(Test::Bootstrap::Packages packagesToSetup = Test::Bootstrap::Packages::Default)
    {
        CleanupBootstrap();
        CleanupPackages(packagesToSetup);
    }
}

#endif // __WINDOWSAPPRUNTIME_TEST_BOOTSTRAP_H
