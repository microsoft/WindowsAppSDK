// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __PROJECTREUNION_TEST_FILESYSTEM_H
#define __PROJECTREUNION_TEST_FILESYSTEM_H

#include <filesystem>

#include <wil/win32_helpers.h>
#include <wil/resource.h>
#include <wil/result_macros.h>

namespace Test::FileSystem
{
    inline std::filesystem::path GetModuleFileName(HMODULE hmodule)
    {
        auto moduleFileName = wil::GetModuleFileNameW(hmodule);
        return std::filesystem::path(moduleFileName.get());
    }

    inline std::filesystem::path GetModulePath(HMODULE hmodule)
    {
        auto path = GetModuleFileName(hmodule);
        return path.remove_filename();
    }

    inline std::filesystem::path GetTestAbsoluteFilename()
    {
        // Get the handle of the module containing this code, not the module of the process hosting it.
        wil::unique_hmodule dll;
        THROW_IF_WIN32_BOOL_FALSE(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
            reinterpret_cast<PCWSTR>(GetTestAbsoluteFilename), &dll));

        VERIFY_IS_NOT_NULL(dll.get());
        return GetModulePath(dll.get());
    }

    inline std::filesystem::path GetTestAbsolutePath()
    {
        auto path = GetTestAbsoluteFilename();
        path = path.remove_filename();
        path = path.parent_path();
        return path;
    }

    inline std::filesystem::path GetSolutionOutDirPath()
    {
        // We can't lookup the location of project outputs in our solution
        // but we can infer them relative to our test dll's location
        // as we all share a common $(OutDir), as Visual Studio calls it
        //
        // \BuildOutput
        //     \<Configuration>                                 <== Debug|Release
        //         \<Configuration>                             <== ARM64|X64|X86
        //             \<project>.Msix
        //                 <project>.Msix
        //             \ProjectReunion_BootstrapDLL
        //                 Microsoft.ProjectReunion.Bootstrap.dll
        //             \<TestProjectName>
        //                 <TestProjectName>.dll                <== Test .dll

        // Find the test dll's directory
        auto testPath = GetTestAbsoluteFilename();

        // Find the common parent directory
        auto path = testPath.parent_path().parent_path();
        return path;
    }

    inline std::filesystem::path GetBootstrapAbsoluteFilename()
    {
        // Determine the location of the bootstrap dll. See GetSolutionOutDirPath() for more details.
        auto path = GetSolutionOutDirPath();
        path /= L"ProjectReunion_BootstrapDLL";
        path /= L"Microsoft.ProjectReunion.Bootstrap.dll";
        return path;
    }

    inline std::filesystem::path GetProjectReunionDllAbsoluteFilename()
    {
        // Determine the location of the dll. See GetSolutionOutDirPath() for more details.
        auto path = GetSolutionOutDirPath();
        path /= L"ProjectReunion_DLL";
        path /= L"Microsoft.ProjectReunion.dll";
        return path;
    }
}

#endif // __PROJECTREUNION_TEST_FILESYSTEM_H
