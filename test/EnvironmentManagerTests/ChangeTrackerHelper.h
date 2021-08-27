#pragma once

inline wil::unique_hkey GetKeyForTrackingChange(bool isUser)
{
    wil::unique_hkey keyToTrackChanges{};
    if (isUser)
    {
        THROW_IF_WIN32_ERROR(RegCreateKeyEx(HKEY_CURRENT_USER
            , L"Software\\ChangeTracker"
            , 0
            , nullptr
            , REG_OPTION_NON_VOLATILE
            , KEY_ALL_ACCESS | KEY_WOW64_64KEY
            , nullptr
            , keyToTrackChanges.put()
            , nullptr));
    }
    else //Machine level scope
    {
        THROW_IF_WIN32_ERROR(RegCreateKeyEx(HKEY_LOCAL_MACHINE
            , L"Software\\ChangeTracker"
            , 0
            , nullptr
            , REG_OPTION_NON_VOLATILE
            , KEY_ALL_ACCESS | KEY_WOW64_64KEY
            , nullptr
            , keyToTrackChanges.put()
            , nullptr));
    }

    return keyToTrackChanges;
}

inline wil::unique_hkey GetKeyForTrackingChange(bool isUser, LPCWSTR subKey)
{
    HKEY topLevelKey{ isUser ? HKEY_CURRENT_USER : HKEY_LOCAL_MACHINE };

    wil::unique_hkey keyToTrackChanges{};
    THROW_IF_WIN32_ERROR(RegCreateKeyEx(HKEY_CURRENT_USER,
        subKey, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_64KEY,
        nullptr, keyToTrackChanges.put(), nullptr));

    return keyToTrackChanges;
}

inline wil::unique_hkey GetKeyForPathTrackingChange(bool isUser, std::wstring packageFullName)
{
    auto subKey{ wil::str_printf<wil::unique_cotaskmem_string>(
    L"Software\\ChangeTracker\\%ws\\%ws\\", L"PATH", packageFullName.c_str())};

    return GetKeyForTrackingChange(isUser, subKey.get());
}

inline wil::unique_hkey GetKeyForPathExtTrackingChange(bool isUser, std::wstring packageFullName)
{
    auto subKey{ wil::str_printf<wil::unique_cotaskmem_string>(
    L"Software\\ChangeTracker\\%ws\\%ws\\", L"PATHEXT", packageFullName.c_str()) };

    return GetKeyForTrackingChange(isUser, subKey.get());
}

inline wil::unique_hkey GetKeyForEVTrackingChange(bool isUser, std::wstring packageFullName, LPCWSTR EVKeyName)
{
    auto subKey{ wil::str_printf<wil::unique_cotaskmem_string>(
        L"Software\\ChangeTracker\\%ws\\%ws\\%ws\\", L"EnvironmentVariables", packageFullName.c_str(), EVKeyName)};

    return GetKeyForTrackingChange(isUser, subKey.get());
}

inline void RemoveUserChangeTracking()
{
    wil::unique_hkey hKey{ GetKeyForTrackingChange(true) };

    VERIFY_WIN32_SUCCEEDED(RegDeleteTree(hKey.get(), nullptr));
}

inline void RemoveMachineChangeTracking()
{
    wil::unique_hkey hKey{ GetKeyForTrackingChange(false) };

    VERIFY_WIN32_SUCCEEDED(RegDeleteTree(hKey.get(), nullptr));
}
