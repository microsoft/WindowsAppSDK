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

void Test::DynamicDependency::Test_WinRT::Create_RegistryLifetime_NoExist()
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

    std::wstring lifetimeArtifactRegistryKey{ L"HKCU\\SOFTWARE\\TestProjectReunion-DynamicDependency" };
    Registry_DeleteKey(lifetimeArtifactRegistryKey);

    try
    {
        const auto lifetimeKind{ winrt::Microsoft::ApplicationModel::DynamicDependency::PackageDependencyLifetimeArtifactKind::RegistryKey };
        auto packageDependency_FrameworkMathAdd{ _Create_FrameworkMathAdd(HRESULT_FROM_WIN32(ERROR_CONTEXT_EXPIRED), lifetimeKind, lifetimeArtifactRegistryKey.c_str()) };
        auto message{ wil::str_printf<wil::unique_process_heap_string>(L"Expected exception (value=0x%X ERROR_CONTEXT_EXPIRED) didn't occur", HRESULT_FROM_WIN32(ERROR_CONTEXT_EXPIRED)) };
        Assert::Fail(message.get());
    }
    catch (const winrt::hresult_error& e)
    {
        const int32_t expectedHR{ HRESULT_FROM_WIN32(ERROR_CONTEXT_EXPIRED) };
        Assert::AreEqual(expectedHR, e.code().value, e.message().c_str());
    }

    VerifyPackageInPackageGraph(expectedPackageFullName_ProjectReunionFramework, S_OK);
    VerifyPackageNotInPackageGraph(expectedPackageFullName_FrameworkMathAdd, S_OK);
    VerifyPathEnvironmentVariable(packagePath_ProjectReunionFramework, pathEnvironmentVariable.c_str());
}
