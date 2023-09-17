// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

namespace Test::FileSystem
{
    std::filesystem::path GetModulePath(HMODULE hmodule)
    {
        auto path{ GetModuleFileName(hmodule) };
        const auto modulePath{ path.remove_filename() };
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"GetModulePath(%p): %s", hmodule, modulePath.c_str()));
        return modulePath;
    }

    std::filesystem::path GetModuleFileName(HMODULE hmodule)
    {
        auto moduleFileName{ wil::GetModuleFileNameW(hmodule) };
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"GetModuleFileName(%p): %s", hmodule, moduleFileName.get()));
        return std::filesystem::path(moduleFileName.get());
    }


    std::filesystem::path GetTestAbsoluteFilename()
    {
        wil::unique_hmodule dll(LoadLibrary(L"DynamicDependency_Test_Win32.dll"));
        const auto lastError{ GetLastError() };
        VERIFY_IS_NOT_NULL(dll.get(), WEX::Common::String().Format(L"LastError: %d (0x%X)", lastError, lastError));
        return GetModulePath(dll.get());
    }

    std::filesystem::path GetTestAbsolutePath()
    {
        auto path{ GetTestAbsoluteFilename() };
        path = path.remove_filename();
        path = path.parent_path();
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"GetTestAbsolutePath(): %s", path.c_str()));
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
        auto testPath{ GetTestAbsoluteFilename() };

        // Find the common parent directory
        auto path{ testPath.parent_path().parent_path() };
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"GetSolutionOutDirPath(): %s", path.c_str()));
        return path;
    }

    std::filesystem::path GetBootstrapAbsoluteFilename()
    {
        // Determine the location of the bootstrap dll. See GetSolutionOutDirPath() for more details.
        auto path{ GetSolutionOutDirPath() };
        path /= L"WindowsAppRuntime_BootstrapDLL";
        path /= L"Microsoft.WindowsAppRuntime.Bootstrap.dll";
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"GetBootstrapAbsoluteFilename(): %s", path.c_str()));
        return path;
    }

    std::filesystem::path GetWindowsAppRuntimeDllAbsoluteFilename()
    {
        // Determine the location of the dll. See GetSolutionOutDirPath() for more details.
        auto path{ GetSolutionOutDirPath() };
        path /= L"WindowsAppRuntime_DLL";
        path /= L"Microsoft.WindowsAppRuntime.dll";
        WEX::Logging::Log::Comment(WEX::Common::String().Format(L"GetWindowsAppRuntimeDllAbsoluteFilename(): %s", path.c_str()));
        return path;
    }
}
