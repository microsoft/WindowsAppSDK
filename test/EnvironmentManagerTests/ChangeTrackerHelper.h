#pragma once

inline wil::unique_hkey GetKeyForTrackingChange(bool isUser)
{
    wil::unique_hkey keyToTrackChanges;
    if (isUser)
    {
        THROW_IF_FAILED(HRESULT_FROM_WIN32(RegCreateKeyEx(HKEY_CURRENT_USER
            , L"Software\\ChangeTracker"
            , 0
            , nullptr
            , REG_OPTION_NON_VOLATILE
            , KEY_ALL_ACCESS
            , nullptr
            , keyToTrackChanges.put()
            , nullptr)));
    }
    else //Machine level scope
    {
        THROW_IF_FAILED(HRESULT_FROM_WIN32(RegCreateKeyEx(HKEY_LOCAL_MACHINE
            , L"Software\\ChangeTracker"
            , 0
            , nullptr
            , REG_OPTION_NON_VOLATILE
            , KEY_WRITE
            , nullptr
            , keyToTrackChanges.put()
            , nullptr)));
    }

    return keyToTrackChanges;
}

inline wil::unique_hkey GetKeyForTrackingChange(bool isUser, LPCWSTR subKey)
{
    HKEY topLevelKey;

    if (isUser)
    {
        topLevelKey = HKEY_CURRENT_USER;
    }
    else
    {
        topLevelKey = HKEY_LOCAL_MACHINE;
    }

    wil::unique_hkey keyToTrackChanges;
    THROW_IF_FAILED(HRESULT_FROM_WIN32(RegCreateKeyEx(HKEY_CURRENT_USER
        , subKey
        , 0
        , nullptr
        , REG_OPTION_NON_VOLATILE
        , KEY_ALL_ACCESS
        , nullptr
        , keyToTrackChanges.put()
        , nullptr)));

    return keyToTrackChanges;
}

inline wil::unique_hkey GetKeyForEVTrackingChange(bool isUser, LPCWSTR packageFullName, LPCWSTR EVKeyName)
{
    auto subKey = wil::str_printf<wil::unique_cotaskmem_string>(
        L"Software\\ChangeTracker\\%ws\\%ws\\%ws\\", L"EnvironmentVariables", packageFullName, EVKeyName);

    return GetKeyForTrackingChange(isUser, subKey.get());
}

inline void RemoveUserChangeTracking()
{
    wil::unique_hkey hKey = GetKeyForTrackingChange(true);

    VERIFY_WIN32_SUCCEEDED(RegDeleteTree(hKey.get(), nullptr));
}

inline void RemoveMachineChangeTracking()
{
    wil::unique_hkey hKey = GetKeyForTrackingChange(false);

    VERIFY_WIN32_SUCCEEDED(RegDeleteTree(hKey.get(), nullptr));
}
