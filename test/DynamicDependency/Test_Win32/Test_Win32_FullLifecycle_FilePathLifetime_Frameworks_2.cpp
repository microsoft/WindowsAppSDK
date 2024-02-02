// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <MsixDynamicDependency.h>

#include <Math.Add.h>
#include <Math.Multiply.h>

#include "Test_Win32.h"

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

void Test::DynamicDependency::Test_Win32::FullLifecycle_FilePathLifetime_Frameworks_WindowsAppRuntime_MathAdd()
{
    // Setup our dynamic dependencies

    std::wstring expectedPackageFullName_WindowsAppRuntimeFramework{ TP::WindowsAppRuntimeFramework::c_PackageFullName };
    std::wstring expectedPackageFullName_FrameworkMathAdd{ TP::FrameworkMathAdd::c_PackageFullName };

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    auto pathEnvironmentVariable{ GetPathEnvironmentVariableMinusWindowsAppRuntimeFramework() };
    auto packagePath_WindowsAppRuntimeFramework{ TP::GetPackagePath(expectedPackageFullName_WindowsAppRuntimeFramework) };
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());

    // -- TryCreate

    auto lifetimeArtifactPath{ std::filesystem::temp_directory_path() };
    auto lifetimeArtifactFilename{ lifetimeArtifactPath / L"Test-MathAdd-LifetimeArtifact.tmp" };
    wil::unique_hfile lifetimeArtifactFile{ File_CreateTemporary(lifetimeArtifactFilename) };
    VERIFY_IS_TRUE(lifetimeArtifactFile.is_valid());
    VERIFY_IS_TRUE(std::filesystem::exists(lifetimeArtifactFilename));
    wil::unique_process_heap_string packageDependencyId_FrameworkMathAdd{ Mdd_TryCreate_FrameworkMathAdd(MddPackageDependencyLifetimeKind::FilePath, lifetimeArtifactFilename.c_str()) };

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);

    // -- Add

    wil::unique_process_heap_string packageFullName_FrameworkMathAdd;
    MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext_FrameworkMathAdd{ Mdd_Add(packageDependencyId_FrameworkMathAdd.get(), packageFullName_FrameworkMathAdd) };
    VERIFY_IS_NOT_NULL(packageFullName_FrameworkMathAdd.get(), WEX::Common::String().Format(L"PackageFullName=%s Expected=not-<null>", !packageFullName_FrameworkMathAdd ? L"<null>" : packageFullName_FrameworkMathAdd.get()));
    std::wstring actualPackageFullName_FrameworkMathAdd{ packageFullName_FrameworkMathAdd.get() };
    VERIFY_ARE_EQUAL(actualPackageFullName_FrameworkMathAdd, expectedPackageFullName_FrameworkMathAdd);

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    auto packagePath_FrameworkMathAdd{ TP::GetPackagePath(expectedPackageFullName_FrameworkMathAdd) };
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, packagePath_FrameworkMathAdd, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);

    // -- Delete the lifetime artifact

    lifetimeArtifactFile.reset();
    VERIFY_IS_FALSE(lifetimeArtifactFile.is_valid());
    VERIFY_IS_FALSE(std::filesystem::exists(lifetimeArtifactFilename));

    // Add it a 2nd time. The package dependency is deleted but still resolved so this should succeed. PackageGraph = [ Fwk, MathAdd, MathAdd ]
    wil::unique_process_heap_string packageFullName;
    auto context{ Mdd_Add(packageDependencyId_FrameworkMathAdd.get(), packageFullName) };
    VERIFY_IS_NOT_NULL(packageFullName.get());
    std::wstring actualPackageFullName{ packageFullName.get() };
    VERIFY_ARE_EQUAL(actualPackageFullName, expectedPackageFullName_FrameworkMathAdd);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, packagePath_FrameworkMathAdd, packagePath_FrameworkMathAdd, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);

    // Remove our 2nd instance. PackageGraph = [ Fwk, MathAdd ]
    MddRemovePackageDependency(context);
    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, packagePath_FrameworkMathAdd, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);

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

    MddRemovePackageDependency(packageDependencyContext_FrameworkMathAdd);

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);

    // -- Delete

    MddDeletePackageDependency(packageDependencyId_FrameworkMathAdd.get());

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
}
