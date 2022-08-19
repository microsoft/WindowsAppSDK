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
        None = 0,
        Framework = 0x0001,
        Main = 0x0002,
        DDLM = 0x0004,
        Singleton = 0x0008,

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

    inline void SetupBootstrap()
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

        // Initialize the bootstrapper (for testing purposes)
        VERIFY_SUCCEEDED(MddBootstrapTestInitialize(TP::DynamicDependencyLifetimeManager::c_PackageNamePrefix,
                                                    TP::DynamicDependencyLifetimeManager::c_PackagePublisherId,
                                                    TP::WindowsAppRuntimeFramework::c_PackageNamePrefix,
                                                    TP::WindowsAppRuntimeMain::c_PackageNamePrefix));

        // Major.Minor version, MinVersion=0 to find any framework package for this major.minor version
        const UINT32 c_Version_MajorMinor{ Test::Packages::DynamicDependencyLifetimeManager::c_Version_MajorMinor };
        const PACKAGE_VERSION minVersion{};
        VERIFY_SUCCEEDED(MddBootstrapInitialize(c_Version_MajorMinor, nullptr, minVersion));
        s_bootstrapDll = std::move(bootstrapDll);
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

    inline void Setup()
    {
        SetupPackages();
        SetupBootstrap();
    }

    inline void Cleanup()
    {
        CleanupBootstrap();
        CleanupPackages();
    }
}

#endif // __WINDOWSAPPRUNTIME_TEST_BOOTSTRAP_H
