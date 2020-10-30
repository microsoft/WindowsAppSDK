// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MsixDynamicDependency.h>

#include <Math.Add.h>
#include <Math.Multiply.h>

#include "Test_Win32.h"

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void Test::DynamicDependency::Test_Win32::Create_FilePathLifetime_NoExist()
{
    // Setup our dynamic dependencies

    std::wstring expectedPackageFullName_ProjectReunionFramework{ TP::ProjectReunionFramework::c_PackageFullName };
    std::wstring expectedPackageFullName_FrameworkMathAdd{ TP::FrameworkMathAdd::c_PackageFullName };

    VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
    VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
    auto pathEnvironmentVariable{ wil::TryGetEnvironmentVariableW(L"PATH") };
    VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());

    // -- TryCreate

    wil::unique_process_heap_string packageDependencyId_ProjectReunionFramework{ Mdd_TryCreate_ProjectReunionFramework() };

    VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
    VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
    VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
    VerifyPackageDependency(packageDependencyId_ProjectReunionFramework.get(), S_OK, expectedPackageFullName_ProjectReunionFramework);

    auto lifetimeArtifactPath{ std::filesystem::temp_directory_path() };
    auto lifetimeArtifactFilename{ lifetimeArtifactPath / L"Test-MathAdd-LifetimeArtifact.tmp" };
    std::filesystem::remove(lifetimeArtifactFilename);
    auto packageDependencyId_FrameworkMathAdd{ Mdd_TryCreate_FrameworkMathAdd(HRESULT_FROM_WIN32(ERROR_CONTEXT_EXPIRED), MddPackageDependencyLifetimeKind::FilePath, lifetimeArtifactFilename.c_str()) };
    Assert::IsNull(packageDependencyId_FrameworkMathAdd.get());

    VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
    VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
    VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
    VerifyPackageDependency(packageDependencyId_ProjectReunionFramework.get(), S_OK, expectedPackageFullName_ProjectReunionFramework);
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), E_INVALIDARG);

    // -- Delete

    MddDeletePackageDependency(packageDependencyId_ProjectReunionFramework.get());

    VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
    VerifyPackageInPackageGraph(expectedPackageFullName_FrameworkMathAdd, HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_PACKAGE));
    VerifyPathEnvironmentVariable(pathEnvironmentVariable.get());
    VerifyPackageDependency(packageDependencyId_ProjectReunionFramework.get(), HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
    VerifyPackageDependency(packageDependencyId_FrameworkMathAdd.get(), E_INVALIDARG);
}
