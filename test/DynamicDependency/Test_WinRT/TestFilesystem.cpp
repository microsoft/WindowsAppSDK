// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test::FileSystem
{
    std::filesystem::path GetModulePath(HMODULE hmodule)
    {
        auto path = GetModuleFileName(hmodule);
        return path.remove_filename();
    }

    std::filesystem::path GetModuleFileName(HMODULE hmodule)
    {
        auto moduleFileName = wil::GetModuleFileNameW(hmodule);
        return std::filesystem::path(moduleFileName.get());
    }


    std::filesystem::path GetTestAbsoluteFilename()
    {
        wil::unique_hmodule dll(LoadLibrary(L"DynamicDependency_Test_WinRT.dll"));
        const auto lastError{ GetLastError() };
        Assert::IsNotNull(dll.get());
        return GetModulePath(dll.get());
    }

    std::filesystem::path GetTestAbsolutePath()
    {
        auto path = GetTestAbsoluteFilename();
        path = path.remove_filename();
        path = path.parent_path();
        return path;
    }

    std::filesystem::path GetSolutionOutDirPath()
    {
        // We can't lookup the location of project outputs in our solution
        // but we can infer them relative to our test dll's location
        // as we all share a common $(OutDir), as Visual Studio calls it
        //
        // \...
        //    \DynamicDependency_Test_WinRT
        //        DynamicDependency_Test_WinRT.dll      <== This test .dll
        //    \<project>.Msix
        //        <project>.Msix
        //    \ProjectReunion_BootstrapDLL
        //        Microsoft.ProjectReunion.Bootstrap.dll

        // Find the test dll's directory
        auto testPath = GetTestAbsoluteFilename();

        // Find the common parent directory
        auto path = testPath.parent_path().parent_path();
        return path;
    }

    std::filesystem::path GetBootstrapAbsoluteFilename()
    {
        // Determine the location of the bootstrap dll. See GetSolutionOutDirPath() for more details.
        auto path = GetSolutionOutDirPath();
        path /= L"ProjectReunion_BootstrapDLL";
        path /= L"Microsoft.ProjectReunion.Bootstrap.dll";
        return path;
    }

    std::filesystem::path GetProjectReunionDllAbsoluteFilename()
    {
        // Determine the location of the dll. See GetSolutionOutDirPath() for more details.
        auto path = GetSolutionOutDirPath();
        path /= L"ProjectReunion_DLL";
        path /= L"Microsoft.ProjectReunion.dll";
        return path;
    }
}
