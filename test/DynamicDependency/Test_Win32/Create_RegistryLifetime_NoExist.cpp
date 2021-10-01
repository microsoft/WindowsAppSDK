// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MsixDynamicDependency.h>

#include <Math.Add.h>
#include <Math.Multiply.h>

#include "Test_Win32.h"

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

void Test::DynamicDependency::Test_Win32::Create_RegistryLifetime_NoExist()
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

    std::wstring lifetimeArtifactRegistryKey{ L"HKCU\\SOFTWARE\\TestWindowsAppRuntime-DynamicDependency" };
    Registry_DeleteKey(lifetimeArtifactRegistryKey);
    auto packageDependencyId_FrameworkMathAdd{ Mdd_TryCreate_FrameworkMathAdd(HRESULT_FROM_WIN32(ERROR_CONTEXT_EXPIRED), MddPackageDependencyLifetimeKind::RegistryKey, lifetimeArtifactRegistryKey.c_str()) };
    VERIFY_IS_NULL(packageDependencyId_FrameworkMathAdd.get());

    VerifyPackageInPackageGraph(expectedPackageFullName_WindowsAppRuntimeFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_WindowsAppRuntimeFramework, pathEnvironmentVariable.c_str());
}
