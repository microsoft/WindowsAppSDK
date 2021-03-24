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
