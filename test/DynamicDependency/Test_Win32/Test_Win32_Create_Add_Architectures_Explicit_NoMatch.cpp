// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <MsixDynamicDependency.h>

#include <Math.Add.h>
#include <Math.Multiply.h>

#include "Test_Win32.h"

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

void Test::DynamicDependency::Test_Win32::Create_Add_Architectures_Explicit_NoMatch()
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

    // We exclude the Neutral architecture as that's our test package's defined architecture.
    // so we exercise the explicit architectures with no match codepath.
    auto architectures{
        MddPackageDependencyProcessorArchitectures::X86 |
        MddPackageDependencyProcessorArchitectures::X64 |
        MddPackageDependencyProcessorArchitectures::Arm |
        MddPackageDependencyProcessorArchitectures::Arm64
    };
    //
    // WinAppSDK resolves the package dependency in MddTryCreatePackageDependency
    // but Windows doesn't until AddPackageDependency. Handle the differing behavior
    //
    wil::unique_process_heap_string packageDependencyId_FrameworkMathAdd;
    if (MddCore::Win11::IsSupported())
    {
        packageDependencyId_FrameworkMathAdd = std::move(Mdd_TryCreate_FrameworkMathAdd(architectures));

        VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
        VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
        VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
        VerifyPackageDependency_Win11NotResolved(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);

        // -- Add

        const HRESULT expectedHR{ STATEREPOSITORY_E_DEPENDENCY_NOT_RESOLVED };
        wil::unique_process_heap_string packageFullName_FrameworkMathAdd;
        MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext_FrameworkMathAdd{ Mdd_Add(expectedHR, packageDependencyId_FrameworkMathAdd.get(), packageFullName_FrameworkMathAdd) };
        VERIFY_IS_NULL(packageDependencyContext_FrameworkMathAdd);
        VERIFY_IS_NULL(packageFullName_FrameworkMathAdd.get(), WEX::Common::String().Format(L"PackageFullName=%s Expected=not-<null>", !packageFullName_FrameworkMathAdd ? L"<null>" : packageFullName_FrameworkMathAdd.get()));
        VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
        VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
        VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
        VerifyPackageDependency_Win11NotResolved(packageDependencyId_FrameworkMathAdd.get(), S_OK, expectedPackageFullName_FrameworkMathAdd);

        // -- Delete

        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"MddDeletePackageDependency(%s)...", packageDependencyId_FrameworkMathAdd.get()));
        MddDeletePackageDependency(packageDependencyId_FrameworkMathAdd.get());
        VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
    }
    else
    {
        const HRESULT expectedHR{ HRESULT_FROM_WIN32(ERROR_NOT_FOUND) };
        wil::unique_process_heap_string packageDependencyId_FrameworkMathAdd2{ Mdd_TryCreate_FrameworkMathAdd(expectedHR, architectures) };

        VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
        VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
        VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
        VERIFY_IS_NULL(packageDependencyId_FrameworkMathAdd2.get(), WEX::Common::String().Format(L"PackageDependencyId=%s Expected=<null>", !packageDependencyId_FrameworkMathAdd ? L"<null>" : packageDependencyId_FrameworkMathAdd.get()));
    }

    // -- Delete

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
}
