// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MsixDynamicDependency.h>

#include <Math.Add.h>
#include <Math.Multiply.h>

#include "Test_WinRT.h"

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

void Test::DynamicDependency::Test_WinRT::FullLifecycle_RegistryLifetime_Frameworks_WindowsAppRuntime_MathAdd()
{
    // Setup our dynamic dependencies

    winrt::hstring expectedPackageFullName_WindowsAppRuntimeFramework{ TP::WindowsAppRuntimeFramework::c_PackageFullName };
    winrt::hstring expectedPackageFullName_FrameworkMathAdd{ TP::FrameworkMathAdd::c_PackageFullName };

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    auto pathEnvironmentVariable{ GetPathEnvironmentVariableMinusWindowsAppRuntimeFramework() };
    auto packagePath_WindowsAppRuntimeFramework{ TP::GetPackagePath(expectedPackageFullName_WindowsAppRuntimeFramework) };
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());

    // -- Create

    std::wstring lifetimeArtifactRegistryKey{ L"HKCU\\SOFTWARE\\TestWindowsAppRuntime-DynamicDependency" };
    {
        wil::unique_hkey lifetimeArtifactKey{ Registry_CreateKey(lifetimeArtifactRegistryKey) };
        VERIFY_IS_TRUE(lifetimeArtifactKey.is_valid());
    }

    const auto lifetimeArtifactKind{ winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::RegistryKey};
    auto packageDependency_FrameworkMathAdd{ _Create_FrameworkMathAdd(lifetimeArtifactKind, lifetimeArtifactRegistryKey.c_str()) };
    VERIFY_IS_FALSE(!packageDependency_FrameworkMathAdd);
    auto packageDependencyId_FrameworkMathAdd{ packageDependency_FrameworkMathAdd.Id() };
    VERIFY_IS_FALSE(packageDependencyId_FrameworkMathAdd.empty());

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd, S_OK, winrt::hstring{});

    // -- Add

    auto packageDependencyContext_FrameworkMathAdd{ packageDependency_FrameworkMathAdd.Add() };
    VERIFY_IS_FALSE(!packageDependencyContext_FrameworkMathAdd);
    VERIFY_ARE_EQUAL(std::wstring(packageDependencyContext_FrameworkMathAdd.PackageFullName()), std::wstring(expectedPackageFullName_FrameworkMathAdd));

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    auto packagePath_FrameworkMathAdd{ TP::GetPackagePath(expectedPackageFullName_FrameworkMathAdd) };
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, packagePath_FrameworkMathAdd, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd, S_OK, expectedPackageFullName_FrameworkMathAdd);

    // -- Delete the lifetime artifact

    Registry_DeleteKey(lifetimeArtifactRegistryKey);

    // Add it a 2nd time. The package dependency is deleted but still resolved so this should succeed. PackageGraph = [ Fwk, MathAdd, MathAdd ]
    auto context{ packageDependency_FrameworkMathAdd.Add() };
    VERIFY_IS_FALSE(!context);
    VERIFY_ARE_EQUAL(std::wstring(context.PackageFullName()), std::wstring(expectedPackageFullName_FrameworkMathAdd));

    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, packagePath_FrameworkMathAdd, packagePath_FrameworkMathAdd, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd, S_OK, expectedPackageFullName_FrameworkMathAdd);

    // Remove our 2nd instance. PackageGraph = [ Fwk, MathAdd ]
    context.Remove();

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, packagePath_FrameworkMathAdd, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd, S_OK, expectedPackageFullName_FrameworkMathAdd);

    // -- Use it

    // Let's use resources from the dynamically added package
    auto mathAddDllFilename{ L"Framework.Math.Add.dll" };
    wil::unique_hmodule mathAddDll(LoadLibrary(mathAddDllFilename));
    {
        const auto lastError{ GetLastError() };
        auto message{ wil::str_printf<wil::unique_process_heap_string>(L"Error in LoadLibrary: %d (0x%X) loading %s", lastError, lastError, mathAddDllFilename) };
        VERIFY_IS_NOT_NULL(mathAddDll.get(), message.get());
    }

    auto mathAdd{ GetProcAddressByFunctionDeclaration(mathAddDll.get(), Math_Add) };
    VERIFY_IS_NOT_NULL(mathAdd);

    const int expectedValue{ 2 + 3 };
    const auto actualValue{ mathAdd(2, 3) };
    VERIFY_ARE_EQUAL(expectedValue, actualValue);

    // Tear down our dynamic dependencies

    // -- Remove

    packageDependencyContext_FrameworkMathAdd.Remove();

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd, S_OK, expectedPackageFullName_FrameworkMathAdd);

    // -- Delete

    packageDependency_FrameworkMathAdd.Delete();

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd, HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
}
