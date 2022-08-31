// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

namespace Test::FileSystem
{
    std::filesystem::path GetModulePath(HMODULE hmodule = nullptr);

    std::filesystem::path GetModuleFileName(HMODULE hmodule = nullptr);

    std::filesystem::path GetTestAbsoluteFilename();

    std::filesystem::path GetTestAbsolutePath();

    std::filesystem::path GetSolutionOutDirPath();

    std::filesystem::path GetBootstrapAbsoluteFilename();

    std::filesystem::path GetWindowsAppRuntimeDllAbsoluteFilename();
}
