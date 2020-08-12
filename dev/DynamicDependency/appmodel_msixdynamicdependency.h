// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <appmodel.h>

// Modern variants of appmodel.h
namespace appmodel
{
inline std::wstring GetPackagePath(PCWSTR packageFullName)
{
    // Paths can be long but typically short(ish). We can use a quick fixed buffer
    // as an optimization and fallback to dynamic allocation if need be
    WCHAR path[MAX_PATH];
    UINT32 pathLength{ ARRAYSIZE(path) };
    const auto rc{ ::GetPackagePathByFullName(packageFullName, &pathLength, path) };
    if (rc == ERROR_SUCCESS)
    {
        return std::wstring(path);
    }
    else if (rc != ERROR_INSUFFICIENT_BUFFER)
    {
        THROW_WIN32(rc);
    }

    // It's bigger than a breadbox. Allocate memory
    std::unique_ptr<WCHAR[]> pathBuffer(new WCHAR[pathLength]);
    THROW_IF_NULL_ALLOC(pathBuffer);
    THROW_IF_WIN32_ERROR(::GetPackagePathByFullName(packageFullName, &pathLength, pathBuffer.get()));
    return std::wstring(pathBuffer.get());
}
}
