// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __APPMODEL_PACKAGE_H
#define __APPMODEL_PACKAGE_H

#include <appmodel.h>

#include <filesystem>
#include <string>

#include <AppModel.Identity.h>
#include <ExportLoader.h>

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

namespace details
{
    // Helper: build the return type from PCWSTR
    template <typename TString>
    inline TString MakeFromPCWSTR(PCWSTR s)
    {
        if constexpr (std::is_same_v<TString, std::wstring>)
        {
            return s ? std::wstring{s} : std::wstring{};
        }
        else
        {
            // For WIL unique string wrappers, use WIL's maker.
            // WIL string maker functions accept PCWSTR and return a unique_*_string wrapper. [1](https://github-wiki-see.page/m/microsoft/wil/wiki/String-helpers)
            return wil::make_unique_string<TString>(s);
        }
    }

    // GetPackagePathByFullName2 requires >=19H1
    typedef LONG (WINAPI* GetPackagePathByFullName2Function)(
        PCWSTR packageFullName,
        PackagePathType packagePathType,
        UINT32* pathLength,
        PWSTR path);

    inline wil::unique_hmodule g_dll_apiset_appmodel_runtime_1_3;
    inline GetPackagePathByFullName2Function g_getPackagePathByFullName2{};
    inline std::once_flag g_onceFlag{};

    inline void initialize()
    {
        wil::unique_hmodule dll;
        if (::ExportLoader::Load(L"api-ms-win-appmodel-runtime-l1-1-3.dll", wil::out_param(dll)))
        {
            return;
        }
        if (dll)
        {
            GetPackagePathByFullName2Function getPackagePathByFullName2{};
            if (FAILED(::ExportLoader::GetFunctionIfExists<GetPackagePathByFullName2Function>(dll.get(), "GetPackagePathByFullName2", &getPackagePathByFullName2)))
            {
                return;
            }
            if (getPackagePathByFullName2)
            {
                g_dll_apiset_appmodel_runtime_1_3 = std::move(dll);
                g_getPackagePathByFullName2 = std::move(getPackagePathByFullName2);
            }
        }
    }

    /// Get the path for a package, if GetPackagePathByFullName2() is available.
    /// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getpackagepathbyfullname2
    inline HRESULT GetPackagePathByFullName2IfSupported(
        _In_ PCWSTR packageFullName,
        PackagePathType packagePathType,
        std::uint32_t* pathLength,
        _Out_writes_opt_(*pathLength) PWSTR path)
    {
        std::call_once(g_onceFlag, initialize);
        RETURN_HR_IF_NULL(E_NOTIMPL, g_getPackagePathByFullName2);

        return g_getPackagePathByFullName2(packageFullName, packagePathType, pathLength, path);
    }
}

/// Get the path for a package.
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/nf-appmodel-getcurrentpackagepath2
template <typename Tstring>
inline Tstring GetPath(_In_ PCWSTR packageFullName, PackagePathType packagePathType)
{
    // Paths can be long but typically short(ish). We can use a quick fixed buffer
    // as an optimization and fallback to dynamic allocation if need be
    WCHAR path[MAX_PATH]{};
    uint32_t pathLength{ ARRAYSIZE(path) };
    const auto hr{ details::GetPackagePathByFullName2IfSupported(packageFullName, packagePathType, &pathLength, path) };
    if (SUCCEEDED(hr))
    {
        return details::MakeFromPCWSTR<Tstring>(path);
    }
    else if ((hr == HRESULT_FROM_WIN32(ERROR_NOT_FOUND)) ||
             (hr == HRESULT_FROM_WIN32(APPMODEL_ERROR_NO_MUTABLE_DIRECTORY)) ||
             (hr == E_NOTIMPL))
    {
        return Tstring{};
    }
    else if (hr != HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER))
    {
        THROW_HR_MSG(hr, "PackageFullName=%ls PackagePathType=%d", packageFullName ? packageFullName : L"<null>", static_cast<int>(packagePathType));
    }

    // It's bigger than a breadbox. Allocate memory
    std::unique_ptr<WCHAR[]> pathBuffer{ std::make_unique<WCHAR[]>(pathLength) };
    THROW_IF_WIN32_ERROR_MSG(details::GetPackagePathByFullName2IfSupported(packageFullName, packagePathType, &pathLength, pathBuffer.get()),
                             "PackageFullName=%ls PackagePathType=%d", packageFullName ? packageFullName : L"<null>", static_cast<int>(packagePathType));
    return details::MakeFromPCWSTR<Tstring>(pathBuffer.get());
}

/// Get the install path for a package.
/// @return null or empty string if the package isn't visible.
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/ne-appmodel-packagepathtype
template <typename Tstring>
inline Tstring GetInstallPath(_In_ PCWSTR packageFullName)
{
    return GetPath<Tstring>(packageFullName, PackagePathType_Install);
}

/// Get the mutable path for a package.
/// @return null or empty string if the package isn't visible to the caller or has no mutable path.
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/ne-appmodel-packagepathtype
template <typename Tstring>
inline Tstring GetMutablePath(_In_ PCWSTR packageFullName)
{
    return GetPath<Tstring>(packageFullName, PackagePathType_Mutable);
}

/// Get the machine external path for a package.
/// @return null or empty string if the package isn't visible to the caller or has no machine external path.
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/ne-appmodel-packagepathtype
template <typename Tstring>
inline Tstring GetMachineExternalPath(_In_ PCWSTR packageFullName)
{
    return GetPath<Tstring>(packageFullName, PackagePathType_MachineExternal);
}

/// Get the user external path for a package.
/// @return null or empty string if the package isn't visible to the caller or has no user external path.
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/ne-appmodel-packagepathtype
template <typename Tstring>
inline Tstring GetUserExternalPath(_In_ PCWSTR packageFullName)
{
    return GetPath<Tstring>(packageFullName, PackagePathType_UserExternal);
}

/// Get the effective external path for a package.
/// @return null or empty string if the package isn't visible to the caller or has no effective external path.
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/ne-appmodel-packagepathtype
template <typename Tstring>
inline Tstring GetEffectiveExternalPath(_In_ PCWSTR packageFullName)
{
    return GetPath<Tstring>(packageFullName, PackagePathType_EffectiveExternal);
}

/// Get the effective path for a package.
/// @return null or empty string if the package isn't visible to the caller.
/// @see https://learn.microsoft.com/en-us/windows/win32/api/appmodel/ne-appmodel-packagepathtype
template <typename Tstring>
inline Tstring GetEffectivePath(_In_ PCWSTR packageFullName)
{
    return GetPath<Tstring>(packageFullName, PackagePathType_Effective);
}

inline std::filesystem::path GetAbsoluteFilename(
    PCWSTR packageFullName,
    PCWSTR filename,
    PackagePathType packageType)
{
    const auto path{ ::AppModel::Package::GetPath<std::wstring>(packageFullName, packageType) };
    std::filesystem::path pathName{ path };
    pathName /= filename;
    return std::filesystem::absolute(pathName);
}
}

#endif // __APPMODEL_PACKAGE_H
