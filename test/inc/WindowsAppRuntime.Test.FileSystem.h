// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __WINDOWSAPPRUNTIME_TEST_FILESYSTEM_H
#define __WINDOWSAPPRUNTIME_TEST_FILESYSTEM_H

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
        //             \WindowsAppRuntime_BootstrapDLL
        //                 Microsoft.WindowsAppRuntime.Bootstrap.dll
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
        path /= L"WindowsAppRuntime_BootstrapDLL";
        path /= L"Microsoft.WindowsAppRuntime.Bootstrap.dll";
        return path;
    }

    inline std::filesystem::path GetWindowsAppRuntimeDllAbsoluteFilename()
    {
        // Determine the location of the dll. See GetSolutionOutDirPath() for more details.
        auto path = GetSolutionOutDirPath();
        path /= L"WindowsAppRuntime_DLL";
        path /= L"Microsoft.WindowsAppRuntime.dll";
        return path;
    }
}

namespace WEX::TestExecution
{
    // Teach TAEF how to format a std::filesystem::path
    template <>
    class VerifyOutputTraits<std::filesystem::path>
    {
    public:
        static WEX::Common::NoThrowString ToString(std::filesystem::path const& value)
        {
            const auto s{ value.c_str() };
            if (!s)
            {
                return WEX::Common::NoThrowString(L"nullptr");
            }
            else
            {
                return WEX::Common::NoThrowString().Format(L"\"%s\"", s);
            }
        }
    };

    // Teach TAEF how to compare a std::filesystem::path
    template <>
    class VerifyCompareTraits<std::filesystem::path, std::filesystem::path>
    {
    public:
        static bool AreEqual(std::filesystem::path const& expected, std::filesystem::path const& actual)
        {
            return Compare(expected, actual) == 0;
        }

        static bool AreSame(std::filesystem::path const& expected, std::filesystem::path const& actual)
        {
            return &expected == &actual;
        }

        static bool IsLessThan(std::filesystem::path const& expectedLess, std::filesystem::path const& expectedGreater)
        {
            return Compare(expectedLess, expectedGreater) < 0;
        }

        static bool IsGreaterThan(std::filesystem::path const& expectedGreater, std::filesystem::path const& expectedLess)
        {
            return Compare(expectedGreater, expectedLess) > 0;
        }

        static bool IsNull(std::filesystem::path const& object)
        {
            return object.c_str() == nullptr;
        }
    private:
        static int Compare(std::filesystem::path const& left, std::filesystem::path const& right)
        {
            if (left == right)
            {
                return 0;
            }
            else if (left.c_str() == nullptr)
            {
                return -1;
            }
            else if (right.c_str() == nullptr)
            {
                return 1;
            }
            else
            {
                return CompareStringOrdinal(left .c_str(), -1, right.c_str(), -1, FALSE) - CSTR_EQUAL;
            }
        }
    };
}

#endif // __WINDOWSAPPRUNTIME_TEST_FILESYSTEM_H
