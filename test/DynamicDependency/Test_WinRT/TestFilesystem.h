// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

namespace Test::FileSystem
{
    std::filesystem::path GetModulePath(HMODULE hmodule = nullptr);

    std::filesystem::path GetModuleFileName(HMODULE hmodule = nullptr);

    std::filesystem::path GetTestAbsoluteFilename();

    std::filesystem::path GetTestAbsolutePath();

    std::filesystem::path GetSolutionOutDirPath();

    std::filesystem::path GetBootstrapAbsoluteFilename();

    std::filesystem::path GetProjectReunionDllAbsoluteFilename();
}
