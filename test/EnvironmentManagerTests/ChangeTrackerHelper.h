#pragma once

inline wil::unique_hkey GetKeyForTrackingChange()
{
    wil::unique_hkey keyToTrackChanges{};
    THROW_IF_WIN32_ERROR(RegCreateKeyEx(HKEY_CURRENT_USER
        , L"Software\\ChangeTracker"
        , 0
        , nullptr
        , REG_OPTION_NON_VOLATILE
        , KEY_ALL_ACCESS | KEY_WOW64_64KEY
        , nullptr
        , keyToTrackChanges.put()
        , nullptr));

    return keyToTrackChanges;
}

inline wil::unique_hkey GetKeyForTrackingChange(PCWSTR subKey)
{
    wil::unique_hkey keyToTrackChanges{};
    THROW_IF_WIN32_ERROR(RegCreateKeyEx(HKEY_CURRENT_USER,
        subKey, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_64KEY,
        nullptr, keyToTrackChanges.put(), nullptr));

    return keyToTrackChanges;
}

inline wil::unique_hkey GetKeyForPathTrackingChange(std::wstring packageFullName)
{
    auto subKey{ wil::str_printf<wil::unique_cotaskmem_string>(
    L"Software\\ChangeTracker\\%ws\\%ws\\", L"PATH", packageFullName.c_str()) };

    return GetKeyForTrackingChange(subKey.get());
}

inline wil::unique_hkey GetKeyForPathExtTrackingChange(std::wstring packageFullName)
{
    auto subKey{ wil::str_printf<wil::unique_cotaskmem_string>(
    L"Software\\ChangeTracker\\%ws\\%ws\\", L"PATHEXT", packageFullName.c_str()) };

    return GetKeyForTrackingChange(subKey.get());
}

inline wil::unique_hkey GetKeyForEVTrackingChange(bool isUser, std::wstring packageFullName, PCWSTR EVKeyName)
{
    std::wstring scope{};

    if (isUser)
    {
        scope = L"user";
    }
    else
    {
        scope = L"machine";
    }

    std::filesystem::path subKey = std::filesystem::path{ L"Software\\ChangeTracker" }
    / L"EnvironmentVariables" / packageFullName / scope / EVKeyName;

    return GetKeyForTrackingChange(subKey.c_str());
}

inline void RemoveUserChangeTracking()
{
    wil::unique_hkey hKey{ GetKeyForTrackingChange() };

    VERIFY_WIN32_SUCCEEDED(RegDeleteTree(hKey.get(), nullptr));
}

inline void RemoveMachineChangeTracking()
{
    wil::unique_hkey hKey{ GetKeyForTrackingChange() };

    VERIFY_WIN32_SUCCEEDED(RegDeleteTree(hKey.get(), nullptr));
}
