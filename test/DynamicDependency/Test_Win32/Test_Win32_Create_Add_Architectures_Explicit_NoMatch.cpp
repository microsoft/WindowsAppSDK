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
    const HRESULT expectedHR{ HRESULT_FROM_WIN32(ERROR_NOT_FOUND) };
    wil::unique_process_heap_string packageDependencyId_FrameworkMathAdd{ Mdd_TryCreate_FrameworkMathAdd(expectedHR, architectures) };

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VERIFY_IS_NULL(packageDependencyId_FrameworkMathAdd.get(), WEX::Common::String().Format(L"PackageDependencyId=%s Expected=<null>", !packageDependencyId_FrameworkMathAdd ? L"<null>" : packageDependencyId_FrameworkMathAdd.get()));

    // -- Delete

    WEX::Logging::Log::Comment(WEX::Common::String().Format(L"MddDeletePackageDependency(%s)...", packageDependencyId_FrameworkMathAdd.get()));
    MddDeletePackageDependency(packageDependencyId_FrameworkMathAdd.get());

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
    VERIFY_IS_NULL(packageDependencyId_FrameworkMathAdd.get(), WEX::Common::String().Format(L"PackageDependencyId=%s Expected=<null>", !packageDependencyId_FrameworkMathAdd ? L"<null>" : packageDependencyId_FrameworkMathAdd.get()));
}
