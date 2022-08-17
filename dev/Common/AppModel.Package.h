// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#ifndef __APPMODEL_PACKAGE_H
#define __APPMODEL_PACKAGE_H

#include <appmodel.h>

namespace AppModel::Package
{
/// Find all Main+Framework packages in a package family registered to the current user
inline std::vector<std::wstring> FindByFamily(PCWSTR packageFamilyName)
{
    uint32_t count{};
    uint32_t bufferLength{};
    const LONG rc{ ::FindPackagesByPackageFamily(packageFamilyName, PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT, &count, nullptr, &bufferLength, nullptr, nullptr) };
    if (rc == ERROR_SUCCESS)
    {
        // The package family has no packages registered to the user
        return std::vector<std::wstring>();
    }
    else if (rc != ERROR_INSUFFICIENT_BUFFER)
    {
        THROW_WIN32(rc);
    }

    auto packageFullNames{ std::make_unique<PWSTR[]>(count) };
    auto buffer{ std::make_unique<WCHAR[]>(bufferLength) };
    THROW_IF_WIN32_ERROR(::FindPackagesByPackageFamily(packageFamilyName, PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT, &count, packageFullNames.get(), &bufferLength, buffer.get(), nullptr));

    std::vector<std::wstring> packageFullNamesList;
    for (UINT32 index = 0; index < count; ++index)
    {
        const auto packageFullName{ packageFullNames[index] };
        packageFullNamesList.push_back(std::wstring(packageFullName));
    }
    return packageFullNamesList;
}

/// Find all Main+Framework packages in a package family registered to the current user
inline std::vector<std::wstring> FindByFamily(const std::wstring& packageFamilyName)
{
    return FindByFamily(packageFamilyName.c_str());
}
}

#endif // __APPMODEL_PACKAGE_H
