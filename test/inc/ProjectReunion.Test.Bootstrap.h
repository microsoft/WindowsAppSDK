// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __PROJECTREUNION_TEST_BOOTSTRAP_H
#define __PROJECTREUNION_TEST_BOOTSTRAP_H

#include <MddBootstrap.h>
#include <MddBootstrapTest.h>

#include <ProjectReunion.Test.AppModel.h>
#include <ProjectReunion.Test.Package.h>

#include <WexTestClass.h>

namespace Test::Bootstrap
{
    namespace TA = ::Test::AppModel;
    namespace TF = ::Test::FileSystem;
    namespace TP = ::Test::Packages;

    static wil::unique_hmodule s_bootstrapDll;

    bool NeedDynamicDependencies()
    {
        return !TA::IsPackagedProcess();
    }

    void SetupPackages()
    {
        // Remove our packages in case they were previously installed and incompletely removed
        TP::RemovePackage_DynamicDependencyLifetimeManager();
        TP::RemovePackage_DynamicDependencyDataStore();
        TP::RemovePackage_ProjectReunionFramework();

        // Install our needed packages
        TP::AddPackage_ProjectReunionFramework();
        TP::AddPackage_DynamicDependencyDataStore();
        TP::AddPackage_DynamicDependencyLifetimeManager();
    }

    void CleanupPackages()
    {
        // Uninstall the packages we installed via SetupPackages()
        TP::RemovePackage_DynamicDependencyLifetimeManager();
        TP::RemovePackage_DynamicDependencyDataStore();
        TP::RemovePackage_ProjectReunionFramework();
    }

    void SetupBootstrap()
    {
        // Bootstrapper's only needed for non-packaged processes to use Dynamic Dependencies
        if (!NeedDynamicDependencies())
        {
            return;
        }

        // We need to find Microsoft.ProjectReunion.Bootstrap.dll.
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
        VERIFY_SUCCEEDED(MddBootstrapTestInitialize(TP::DynamicDependencyLifetimeManager::c_PackageNamePrefix, TP::DynamicDependencyLifetimeManager::c_PackagePublisherId));

        // Version <major>.0.0.0 to find any framework package for this major version
        PACKAGE_VERSION minVersion{ static_cast<UINT64>(Test::Packages::DynamicDependencyLifetimeManager::c_Version.Major) << 48 };
        VERIFY_SUCCEEDED(MddBootstrapInitialize(minVersion));
        s_bootstrapDll = std::move(bootstrapDll);
    }

    void CleanupBootstrap()
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

    void Setup()
    {
        SetupPackages();
        SetupBootstrap();
    }

    void Cleanup()
    {
        CleanupPackages();
        CleanupBootstrap();
    }
}

#endif // __PROJECTREUNION_TEST_BOOTSTRAP_H
