#pragma once
#include "TestCommon.h"

inline void WriteProcessEV()
{
    BOOL setResult = SetEnvironmentVariable(c_evKeyName, c_evValueName);

    if (!setResult)
    {
        FAILED(HRESULT_FROM_WIN32(GetLastError()));
    }
}

inline void WriteUserEV()
{
    wil::unique_hkey userEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_CURRENT_USER, c_userEvRegLocation, 0, KEY_WRITE, userEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(userEnvironmentVariablesHKey.get(), c_evKeyName, 0, REG_SZ, (LPBYTE)c_evValueName, static_cast<DWORD>(wcslen(c_evValueName) * sizeof(wchar_t))));
}

inline void RemoveUserEV()
{
    wil::unique_hkey userEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_CURRENT_USER, c_userEvRegLocation, 0, KEY_WRITE, userEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegDeleteValueW(userEnvironmentVariablesHKey.get(), c_evKeyName));
}

inline void WriteMachineEV()
{
    wil::unique_hkey machineEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_machineEvRegLocation, 0, KEY_WRITE, machineEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegSetValueExW(machineEnvironmentVariablesHKey.get(), c_evKeyName, 0, REG_SZ, (LPBYTE)c_evValueName, static_cast<DWORD>(wcslen(c_evValueName) * sizeof(wchar_t))));
}

inline void RemoveMachineEV()
{
    wil::unique_hkey machineEnvironmentVariablesHKey{};
    VERIFY_WIN32_SUCCEEDED(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_machineEvRegLocation, 0, KEY_WRITE, machineEnvironmentVariablesHKey.addressof()));
    VERIFY_WIN32_SUCCEEDED(RegDeleteValueW(machineEnvironmentVariablesHKey.get(), c_evKeyName));
}
