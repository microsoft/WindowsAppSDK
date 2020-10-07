// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

#include "PackageDependency.h"

void MddCore::PackageDependency::GenerateId()
{
    GUID id{};
    THROW_IF_FAILED(CoCreateGuid(&id));
    const size_t idAsStringLength{ ARRAYSIZE(L"{33221100-5544-7766-8899-aabbccddeeff}") - 1 };
    WCHAR idAsString[idAsStringLength + 1]{};
    FAIL_FAST_HR_IF(HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), StringFromGUID2(id, idAsString, idAsStringLength + 1) != idAsStringLength + 1);
    m_packageDependencyId.assign(idAsString);
}

std::vector<std::wstring> MddCore::PackageDependency::FindPackagesByFamily() const
{
    UINT32 count{};
    UINT32 bufferLength{};
    const LONG rc{ FindPackagesByPackageFamily(m_packageFamilyName.c_str(), PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT, &count, nullptr, &bufferLength, nullptr, nullptr) };
    if (rc == ERROR_SUCCESS)
    {
        // The package family has no packages registered to the user
        return std::vector<std::wstring>();
    }
    else if (rc != ERROR_INSUFFICIENT_BUFFER)
    {
        THROW_WIN32(rc);
    }

    auto packageFullNames{ wil::make_unique_cotaskmem<PWSTR[]>(count) };
    auto buffer{ wil::make_unique_cotaskmem<WCHAR[]>(bufferLength) };
    THROW_IF_WIN32_ERROR(FindPackagesByPackageFamily(m_packageFamilyName.c_str(), PACKAGE_FILTER_HEAD | PACKAGE_FILTER_DIRECT, &count, packageFullNames.get(), &bufferLength, buffer.get(), nullptr));

    std::vector<std::wstring> packageFullNamesList;
    auto packageFullName{ *packageFullNames.get() };
    for (UINT32 index=0; index < count; ++index, ++packageFullName)
    {
        packageFullNamesList.push_back(std::wstring(packageFullName));
    }
    return packageFullNamesList;
}
