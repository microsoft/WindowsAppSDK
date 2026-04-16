// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __MICROSOFT_FILESYSTEM_PATH_H
#define __MICROSOFT_FILESYSTEM_PATH_H

#include <filesystem>

#include <wil/win32_helpers.h>

#include <Security.User.h>

namespace Microsoft::FileSystem::Path
{
inline std::filesystem::path GetTempDirectory()
{
    // GetTempPath2() returns ...windir...\SystemTemp if the caller is LocalSystem
    // else it's the same as GetTempPath(). However, GetTempPath2() is only available
    // on Windows 11 >=10.0.22000.0 (aka 21H2) and we support Windows 10. So handle it...
    if (::Security::User::IsLocalSystem())
    {
        const auto windowsPath{ wil::GetWindowsDirectoryW() };
        std::filesystem::path path{ windowsPath.get() };
        return path / L"SystemTemp";
    }
    else
    {
        // The Standard C++ Library (on Windows) is equivalent to GetTempPath()
        return std::filesystem::temp_directory_path();
    }
}
}

#endif // __MICROSOFT_FILESYSTEM_PATH_H
