// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

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
        wil::unique_hmodule dll(LoadLibrary(L"DynamicDependency_Test_Win32.dll"));
        const auto lastError{ GetLastError() };
        VERIFY_IS_NOT_NULL(dll.get());
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
        //    \DynamicDependency_Test_Win32
        //        DynamicDependency_Test_Win32.dll      <== This test .dll
        //    \<project>.Msix
        //        <project>.Msix
        //    \WindowsAppRuntime_BootstrapDLL
        //        Microsoft.WindowsAppRuntime.Bootstrap.dll

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
        path /= L"WindowsAppRuntime_BootstrapDLL";
        path /= L"Microsoft.WindowsAppRuntime.Bootstrap.dll";
        return path;
    }

    std::filesystem::path GetWindowsAppRuntimeDllAbsoluteFilename()
    {
        // Determine the location of the dll. See GetSolutionOutDirPath() for more details.
        auto path = GetSolutionOutDirPath();
        path /= L"WindowsAppRuntime_DLL";
        path /= L"Microsoft.WindowsAppRuntime.dll";
        return path;
    }
}
