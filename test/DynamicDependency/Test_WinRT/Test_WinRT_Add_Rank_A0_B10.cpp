// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <MsixDynamicDependency.h>

#include <Math.Add.h>
#include <Math.Multiply.h>

#include "Test_WinRT.h"

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

void Test::DynamicDependency::Test_WinRT::Add_Rank_A0_B10()
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

    auto packageDependency_FrameworkMathAdd{ _Create_FrameworkMathAdd() };
    VERIFY_IS_FALSE(!packageDependency_FrameworkMathAdd);
    auto packageDependencyId_FrameworkMathAdd{ packageDependency_FrameworkMathAdd.Id() };
    VERIFY_IS_FALSE(packageDependencyId_FrameworkMathAdd.empty());

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd, S_OK, winrt::hstring{});

    // -- Add

    winrt::Microsoft::Windows::ApplicationModel::DynamicDependency::AddPackageDependencyOptions addOptions{};
    addOptions.Rank(10);
    auto packageDependencyContext_FrameworkMathAdd{ packageDependency_FrameworkMathAdd.Add(addOptions) };
    VERIFY_IS_FALSE(!packageDependencyContext_FrameworkMathAdd);
    VERIFY_ARE_EQUAL(std::wstring(packageDependencyContext_FrameworkMathAdd.PackageFullName()), std::wstring(expectedPackageFullName_FrameworkMathAdd));

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    auto packagePath_FrameworkMathAdd{ TP::GetPackagePath(expectedPackageFullName_FrameworkMathAdd) };
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
