// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "pch.h"

#include "utf8.h"

#include "PackageDependency.h"

namespace JSON = winrt::Windows::Data::Json;

void MddCore::PackageDependency::GenerateId()
{
    GUID id{};
    THROW_IF_FAILED(CoCreateGuid(&id));
    const size_t idAsStringLength{ ARRAYSIZE(L"{33221100-5544-7766-8899-aabbccddeeff}") - 1 };
    WCHAR idAsString[idAsStringLength + 1]{};
    FAIL_FAST_HR_IF(HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER), StringFromGUID2(id, idAsString, idAsStringLength + 1) != idAsStringLength + 1);
    idAsString[idAsStringLength - 1] = L'\0';
    m_packageDependencyId.assign(idAsString + 1);
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

std::wstring MddCore::PackageDependency::ToJSON() const
{
    JSON::JsonObject json;
    json.SetNamedValue(winrt::hstring(L"PackageFamilyName"), JSON::JsonValue::CreateStringValue(winrt::hstring(m_packageFamilyName)));
    json.SetNamedValue(winrt::hstring(L"MinVersion"), JSON::JsonValue::CreateStringValue(winrt::hstring(std::to_wstring(m_minVersion.Version))));
    json.SetNamedValue(winrt::hstring(L"ProcessorArchitectures"), JSON::JsonValue::CreateStringValue(std::wstring(L"0x") + std::to_wstring(static_cast<uint32_t>(m_packageDependencyProcessorArchitectures))));
    json.SetNamedValue(winrt::hstring(L"LifetimeKind"), JSON::JsonValue::CreateStringValue(winrt::hstring(ToString(m_lifetimeKind))));
    json.SetNamedValue(winrt::hstring(L"LifetimeArtifact"), JSON::JsonValue::CreateStringValue(winrt::hstring(m_lifetimeArtifact)));
    json.SetNamedValue(winrt::hstring(L"Options"), JSON::JsonValue::CreateStringValue(std::wstring(L"0x") + std::to_wstring(static_cast<uint32_t>(m_options))));
    return std::wstring(json.ToString());
}

std::string MddCore::PackageDependency::ToJSONUtf8() const
{
    return to_utf8(ToJSON());
}

MddCore::PackageDependency MddCore::PackageDependency::FromJSON(const winrt::hstring& json)
{
    MddCore::PackageDependency packageDependency;

    JSON::JsonObject object{ JSON::JsonObject::Parse(json) };
    packageDependency.m_packageFamilyName = object.GetNamedString(winrt::hstring(L"PackageFamilyName"));
    packageDependency.m_minVersion = PACKAGE_VERSION{ uint64_from_string(object.GetNamedString(winrt::hstring(L"MinVersion")).c_str()) };
    packageDependency.m_packageDependencyProcessorArchitectures = static_cast<MddPackageDependencyProcessorArchitectures>(uint32_from_string(object.GetNamedString(winrt::hstring(L"ProcessorArchitectures")).c_str()));
    packageDependency.LifetimeKind(object.GetNamedString(winrt::hstring(L"LifetimeKind")));
    packageDependency.m_lifetimeArtifact = object.GetNamedString(winrt::hstring(L"LifetimeArtifact"));
    packageDependency.m_options = static_cast<MddCreatePackageDependencyOptions>(uint32_from_string(object.GetNamedString(winrt::hstring(L"Options")).c_str()));

    return packageDependency;
}

MddCore::PackageDependency MddCore::PackageDependency::FromJSON(PCSTR jsonUtf8)
{
    return FromJSON(utf8_to_hstring(jsonUtf8));
}

bool MddCore::PackageDependency::IsExpired() const
{
    switch (m_lifetimeKind)
    {
    case MddPackageDependencyLifetimeKind::Process:
        return false;
    case MddPackageDependencyLifetimeKind::FilePath:
        return !std::filesystem::exists(m_lifetimeArtifact);
    case MddPackageDependencyLifetimeKind::RegistryKey:
        return !IsRegistryKeyExists(m_lifetimeArtifact);
    default:
        FAIL_FAST_HR(E_UNEXPECTED);
    }
}

bool MddCore::PackageDependency::IsRegistryKeyExists(
    const std::wstring& key)
{
    PCWSTR subkey{};
    auto root{ ParseRegistryKey(key, subkey) };

    wil::unique_hkey hkey;
    auto rc{ ::RegOpenKeyExW(root, subkey, 0, KEY_READ, wil::out_param(hkey)) };
    if (rc == ERROR_SUCCESS)
    {
        return true;
    }
    else if ((rc == ERROR_FILE_NOT_FOUND) || (rc == ERROR_PATH_NOT_FOUND))
    {
        return false;
    }
    THROW_HR_MSG(HRESULT_FROM_WIN32(rc), "RegOpenKey failed %d", rc);
}

HKEY MddCore::PackageDependency::ParseRegistryKey(
    const std::wstring& key,
    PCWSTR& subkey)
{
    size_t offset{};
    auto root{ ParseRegistryKey(key, offset) };
    subkey = key.c_str() + offset;
    return root;
}

HKEY MddCore::PackageDependency::ParseRegistryKey(
    const std::wstring& key,
    size_t& offsetToSubkey)
{
    HKEY root{};
    auto offset{ key.find(L'\\') };
    THROW_HR_IF_MSG(E_INVALIDARG, offset == std::wstring::npos, "Invalid RegistryKey %ls", key.c_str());
    THROW_HR_IF_MSG(E_INVALIDARG, offset == 0, "Invalid RegistryKey %ls", key.c_str());
    auto prefix{ key.substr(0, offset) };
    if (prefix == L"HKCR")
    {
        root = HKEY_CLASSES_ROOT;
    }
    else if (prefix == L"HKCU")
    {
        root = HKEY_CURRENT_USER;
    }
    else if (prefix == L"HKLM")
    {
        root = HKEY_LOCAL_MACHINE;
    }
    else if (prefix == L"HKU")
    {
        root = HKEY_USERS;
    }
    else
    {
        THROW_HR_MSG(E_INVALIDARG, "Invalid RegistryKey %ls", key.c_str());
    }
    THROW_HR_IF_MSG(E_INVALIDARG, key.length() == prefix.length(), "Invalid RegistryKey %ls", key.c_str());

    offsetToSubkey = ++offset;
    return root;
}

winrt::hstring MddCore::PackageDependency::ToString(const MddPackageDependencyLifetimeKind lifetimeKind)
{
    switch (lifetimeKind)
    {
    case MddPackageDependencyLifetimeKind::Process:     return winrt::hstring(L"Process");
    case MddPackageDependencyLifetimeKind::FilePath:    return winrt::hstring(L"FilePath");
    case MddPackageDependencyLifetimeKind::RegistryKey: return winrt::hstring(L"RegistryKey");
    default: FAIL_FAST_HR(E_UNEXPECTED);
    }
}

void MddCore::PackageDependency::LifetimeKind(const winrt::hstring& lifetimeKind)
{
    auto s{ lifetimeKind.c_str() };
    if (CompareStringOrdinal(s, -1, L"Process", -1, TRUE) == CSTR_EQUAL)
    {
        m_lifetimeKind = MddPackageDependencyLifetimeKind::Process;
    }
    else if (CompareStringOrdinal(s, -1, L"FilePath", -1, TRUE) == CSTR_EQUAL)
    {
        m_lifetimeKind = MddPackageDependencyLifetimeKind::FilePath;
    }
    else if (CompareStringOrdinal(s, -1, L"RegistryKey", -1, TRUE) == CSTR_EQUAL)
    {
        m_lifetimeKind = MddPackageDependencyLifetimeKind::RegistryKey;
    }
    else
    {
        THROW_WIN32(ERROR_INVALID_DATA);
    }
}
