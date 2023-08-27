// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __APPMODEL_PACKAGE_H
#define __APPMODEL_PACKAGE_H

#include <appmodel.h>

#include <AppModel.Identity.h>

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

inline PACKAGE_VERSION ToPackageVersion(winrt::Windows::ApplicationModel::PackageVersion const& from)
{
    PACKAGE_VERSION to{};
    to.Major = from.Major;
    to.Minor = from.Minor;
    to.Build = from.Build;
    to.Revision = from.Revision;
    return to;
}

inline std::tuple<std::wstring, PACKAGE_VERSION, std::uint32_t, std::wstring, std::wstring, std::wstring> ParsePackageFullName(PCWSTR packageFullName)
{
    BYTE buffer[
        sizeof(PACKAGE_ID) +
        sizeof(WCHAR) * (PACKAGE_NAME_MAX_LENGTH + 1) +
        sizeof(WCHAR) * (PACKAGE_VERSION_MAX_LENGTH + 1) +
        sizeof(WCHAR) * (PACKAGE_ARCHITECTURE_MAX_LENGTH + 1) +
        sizeof(WCHAR) * (PACKAGE_RESOURCEID_MAX_LENGTH + 1) +
        sizeof(WCHAR) * (PACKAGE_PUBLISHERID_MAX_LENGTH + 1)]{};
    UINT32 bufferLength{ ARRAYSIZE(buffer) };
    THROW_IF_WIN32_ERROR_MSG(::PackageIdFromFullName(packageFullName, PACKAGE_INFORMATION_BASIC, &bufferLength, buffer), "%ls", packageFullName);
    const auto& packageId{ *reinterpret_cast<PACKAGE_ID*>(buffer) };

    WCHAR packageFamilyName[PACKAGE_FAMILY_NAME_MAX_LENGTH + 1]{};
    UINT32 packageFamilyNameLength{ ARRAYSIZE(packageFamilyName) };
    THROW_IF_WIN32_ERROR_MSG(::PackageFamilyNameFromId(&packageId, &packageFamilyNameLength, packageFamilyName), "%ls", packageFullName);

    return { std::wstring(packageId.name), packageId.version, packageId.processorArchitecture, std::wstring(packageId.resourceId ? packageId.resourceId : L""), std::wstring(packageId.publisherId), std::wstring(packageFamilyName) };
}

inline std::tuple<std::wstring, PACKAGE_VERSION, std::uint32_t, std::wstring, std::wstring, std::wstring> ParsePackageFullName(const std::wstring& packageFullName)
{
    return ParsePackageFullName(packageFullName.c_str());
}
}

#endif // __APPMODEL_PACKAGE_H
