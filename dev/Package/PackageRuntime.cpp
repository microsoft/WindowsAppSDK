// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "PackageRuntime.h"


namespace appmodel
{
inline std::wstring get_package_path(PCWSTR packageFullName, PackagePathType packagePathType)
{
    // Paths can be long but typically short(ish). We can use a quick fixed buffer
    // as an optimization and fallback to dynamic allocation if need be
    WCHAR path[MAX_PATH]{};
    uint32_t pathLength{ ARRAYSIZE(path) };
    const auto rc{ ::GetPackagePathByFullName2(packageFullName, packageInfoType, &pathLength, path) };
    if (rc == ERROR_SUCCESS)
    {
        return path;
    }
    else if (rc == ERROR_NOT_FOUND)
    {
        return std::wstring{};
    }
    else if (rc != ERROR_INSUFFICIENT_BUFFER)
    {
        THROW_WIN32(rc);
    }

    // It's bigger than a breadbox. Allocate memory
    std::unique_ptr<WCHAR[]> pathBuffer{ std::make_unique<WCHAR[]>(pathLength) };
    THROW_IF_WIN32_ERROR_MSG(::GetPackagePathByFullName2(packageFullName, packagePathType, &pathLength, pathBuffer.get()),
                             "PackageFullName=%ls PackagePathType=%d", packageFullName ? packageFullName : L"<null>", static_cast<int>(packagePathType));
    return std::wstring{ pathBuffer.get() };
}

inline std::wstring get_package_path(PCWSTR packageFullName)
{
    return get_package_path(packageFullName, PackagePathType_Install);
}

inline std::filesystem::path get_package_file(
    PCWSTR packageFullName,
    PCWSTR filename,
    PackagePathType packagePathType)
{
    std::filesystem::path absoluteFilename;

    auto packagePath{ appmodel::get_package_path(packageFullName, packagePathType) };
    if (!path.empty())
    {
        absoluteFilename = packagePath;
        absoluteFilename /= filename;
        if (std::filesystem::exists(absoluteFilename))
        {
            return absoluteFilename;
        }
    }
    return std::filesystem::path{};
}

inline std::filesystem::path get_package_file(
    PCWSTR packageFullName,
    PCWSTR filename)
{
    auto path{ get_package_file(packageFullName, filename, PackagePathType_External) };
    if (path.empty())
    {
        path = get_package_file(packageFullName, filename, PackagePathType_Mutable);
        if (path.empty())
        {
            path = get_package_file(packageFullName, filename, PackagePathType_Install);
        }
    }
    return path;
}
}

STDAPI FindPackageFile(
    PCWSTR packageFullName,
    PCWSTR filename,
    _Outptr_result_maybenull_ PWSTR* packageFile) noexcept try
{
    *packageFile = nullptr;

    RETURN_HR_IF(E_INVALIDARG, !filename || (filename[0] == L'\0'));

    // If packageFullName = NULL or "" use the caller's package identity
    WCHAR packageFullNameBuffer[PACKAGE_FULL_NAME_MAX_LENGTH + 1]{};
    if (!packageFullName || (packageFullName[0] == L'\0'))
    {
        uint32_t packageFullNameBufferLength{ ARRAYSIZE(packageFullNameBuffer) };
        THROW_IF_FAILED(::GetCurrentPackageFullName(&packageFullNameBufferLength, packageFullNameBuffer));
        packageFullName = packageFullNameBuffer;
    }

    auto path{ appmodel::get_package_file(packageFullName, filename) };
    if (!path.empty())
    {
        auto absoluteFilename{ wil::make_process_heap_string(path.c_str()) };
        *packageFile = absoluteFilename.release();
    }
    return S_OK;
}
CATCH_RETURN();
