// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <MsixDynamicDependency.h>

#include <Math.Add.h>
#include <Math.Multiply.h>

#include "Test_WinRT.h"

namespace TF = ::Test::FileSystem;
namespace TP = ::Test::Packages;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void Test::DynamicDependency::Test_WinRT::Create_FilePathLifetime_NoExist()
{
    // Setup our dynamic dependencies

    winrt::hstring expectedPackageFullName_ProjectReunionFramework{ TP::ProjectReunionFramework::c_PackageFullName };
    winrt::hstring expectedPackageFullName_FrameworkMathAdd{ TP::FrameworkMathAdd::c_PackageFullName };

    VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    auto pathEnvironmentVariable{ GetPathEnvironmentVariableMinusProjectReunionFramework() };
    auto packagePath_ProjectReunionFramework{ TP::GetPackagePath(expectedPackageFullName_ProjectReunionFramework) };
    VerifyPathEnvironmentVariable(packagePath_ProjectReunionFramework, pathEnvironmentVariable.c_str());

    // -- Create

    auto lifetimeArtifactPath{ std::filesystem::temp_directory_path() };
    auto lifetimeArtifactFilename{ lifetimeArtifactPath / L"Test-MathAdd-LifetimeArtifact.tmp" };
    std::filesystem::remove(lifetimeArtifactFilename);

    const auto lifetimeKind{ winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::FilePath };
    auto packageDependency_FrameworkMathAdd{ _Create_FrameworkMathAdd(HRESULT_FROM_WIN32(ERROR_CONTEXT_EXPIRED), lifetimeKind, lifetimeArtifactFilename.c_str()) };
    Assert::IsTrue(!packageDependency_FrameworkMathAdd);
    auto packageDependencyId_FrameworkMathAdd{ packageDependency_FrameworkMathAdd.Id() };
    Assert::IsFalse(packageDependencyId_FrameworkMathAdd.empty());

    VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_ProjectReunionFramework, pathEnvironmentVariable.c_str());
}
